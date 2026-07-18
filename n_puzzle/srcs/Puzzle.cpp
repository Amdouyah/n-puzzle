#include "Puzzle.hpp"
#include "Helper.hpp"

Puzzle::Puzzle() : move_count(0), heuristic(0), size(0), timeComplexity(0), spaceComplexity(0) {}

// Puzzle::Puzzle() : move_count(0), heuristic(0), size(0) {}


Puzzle::~Puzzle() {}

string Puzzle::strip_comments(const string &line)
{
    size_t comment_pos = line.find('#');
    if (comment_pos != string::npos)
    {
        return line.substr(0, comment_pos);
    }
    return line;
}

void Puzzle::read_data(const string &filename, int heuristicChoice, int searchModeChoice)
{
    try
    {
        ifstream file(filename);
        string line;
        if (!file.is_open())
        {
            throw runtime_error("Error: Could not open file " + string(filename));
        }
        if (heuristicChoice < 1 || heuristicChoice > 3)
            throw std::runtime_error("Error: Invalid heuristic value. Must be 1, 2, or 3.");
        this->heuristic = heuristicChoice;

        if (searchModeChoice < 1 || searchModeChoice > 3)
            throw std::runtime_error("Error: Invalid search mode. Must be 1 (A*), 2 (greedy) or 3 (uniform-cost).");
        this->searchMode = searchModeChoice;

        int n = -1;
        vector<int> grid;
        while (getline(file, line))
        {
            line = strip_comments(line);
            istringstream iss(line);

            if (n == -1)
            {
                // first non-comment, non-blank line -> puzzle size
                if (!(iss >> n))
                    continue; // line was blank/comment-only, keep looking
                if (n < 3)
                    throw runtime_error("Error: puzzle size must be >= 3");
                continue;
            }

            // any following line: read as many ints as it has (subject
            // allows values to be spread however, but usually one row per line)
            int value;
            while (iss >> value)
                grid.push_back(value);
        }
        if (n == -1)
            throw runtime_error("Error: missing puzzle size");
        if (static_cast<int>(grid.size()) != n * n)
            throw runtime_error("Error: puzzle does not contain n*n values");

        std::vector<bool> seen(n * n, false);

        for (size_t i = 0; i < grid.size(); i++)
        {
            int value = grid[i];

            //valid range
            if (value < 0 || value >= n * n)
                throw std::runtime_error(
                    "Error: value " + std::to_string(value) +
                    " is out of range [0.." + std::to_string(n * n - 1) + "]");

            //duplicates
            if (seen[value])
                throw std::runtime_error(
                    "Error: duplicate value found: " + std::to_string(value));

            seen[value] = true;
        }

        this->size = n;
        this->puzzle = grid;
    }
    catch (std::exception &e)
    {
        cerr << e.what() << endl;
        exit(1);
    }
}

std::vector<int> Puzzle::generateSnailGoal()
{
    std::vector<int> goal(size * size, 0);
    // int size = this->size;

    int top = 0;
    int bottom = size - 1;
    int left = 0;
    int right = size - 1;

    int value = 1;

    while (left <= right && top <= bottom)
    {
        // left -> right
        for (int i = left; i <= right; i++)
        {
            if (value == size * size)
                goal[top * size + i] = 0;
            else
                goal[top * size + i] = value++;
        }
        top++;

        // top -> bottom
        for (int i = top; i <= bottom; i++)
        {
            if (value == size * size)
                goal[i * size + right] = 0;
            else
                goal[i * size + right] = value++;
        }
        right--;

        // right -> left
        if (top <= bottom)
        {
            for (int i = right; i >= left; i--)
            {
                if (value == size * size)
                    goal[bottom * size + i] = 0;
                else
                    goal[bottom * size + i] = value++;
            }
            bottom--;
        }

        // bottom -> top
        if (left <= right)
        {
            for (int i = bottom; i >= top; i--)
            {
                if (value == size * size)
                    goal[i * size + left] = 0;
                else
                    goal[i * size + left] = value++;
            }
            left++;
        }
    }
    return goal;
}


bool Puzzle::checkSolvability()
{

    this->goal = generateSnailGoal();

    this->goalPositions = buildGoalPos(this->goal);

    vector<int> rank = buildGoalRank(this->goal);

    vector<int> rankedBoard = convertToRanks(this->puzzle, rank);

    int inversions = countInversions(rankedBoard);

    if (size % 2 == 1)
        return (inversions % 2 == 0);

    int blankIndex = 0;
    while (this->puzzle[blankIndex] != 0)
        blankIndex++;
    // Find the blank's row
    int blankRow = blankIndex / size;
    // Find the blank's row from the bottom
    int blankRowFromBottom = this->goalPositions[0] / size ;
    return ((inversions + blankRow + blankRowFromBottom) % 2 == 0);
}

int Puzzle::computeH(const vector<int> &state) const
{
    return computeHeuristic(this->heuristic, state, this->goal, this->goalPositions, this->size);
}
int Puzzle::computeF(int g, int h) const
{
    if (this->searchMode == 2) // Greedy
        return h;
    else if (this->searchMode == 3) // Uniform-cost
        return g;
    return g + h; // A*
}

vector<shared_ptr<Puzzle::Node>> Puzzle::getNeighbors(const shared_ptr<Node> &current) const{
    vector <shared_ptr<Node>> neighbors;
    int row = current->zeroPos / size;
    int col = current->zeroPos % size;
    const int Drow[4] ={-1, 1, 0, 0};
    const int Dcol[4] ={0, 0, -1, 1};

    for (int i =0 ; i < 4; i++){
        int newRow = row + Drow[i];
        int newCol = col + Dcol[i];
        if (newRow < 0 || newRow >= size || newCol < 0 || newCol >= size)
            continue;
        
        int newZeroPos = newRow * size + newCol;
        auto node = make_shared<Node>(); 
        node->state = current->state;
        swap(node->state[current->zeroPos], node->state[newZeroPos]);
        node->zeroPos = newZeroPos;
        node->g = current->g + 1;
        node->h = computeH(node->state);
        node->f = computeF(node->g, node->h);
        node->parent = current;
        neighbors.push_back(node);
    }
    return neighbors;
}

void Puzzle::solvePuzzle()
{
    auto start = make_shared<Node>();
    start->state = this->puzzle;
    start->zeroPos = std::find(start->state.begin(), start->state.end(), 0) - start->state.begin();
    start->g = 0;
    start->h = computeH(start->state);
    start->f = computeF(start->g, start->h);
    start->parent = nullptr;
    priority_queue<shared_ptr<Node> , vector<shared_ptr<Node>>, CompareNodes> open_set;
    unordered_set<vector<int>, VectorHash> closed_set;
    unordered_map<vector<int>, int, VectorHash> bestG;


    open_set.push(start);
    bestG[start->state] = 0;

    while(!open_set.empty())
    {
        spaceComplexity = max(spaceComplexity, open_set.size() + closed_set.size());

        shared_ptr<Node> current = open_set.top();
        open_set.pop();
        if (current->g > bestG[current->state])
            continue;

        if(current->state == this->goal)
        {
            cout <<" done" << endl;
            // complexity = clock() - start_time;
            return;
        }
        closed_set.insert(current->state);

        for (const auto& neighbor : getNeighbors(current))
        {
            auto it = bestG.find(neighbor->state);
            bool undiscovered = (it == bestG.end());

            if (undiscovered || neighbor->g < it->second)
            {
                bestG[neighbor->state] = neighbor->g;
                open_set.push(neighbor);
                closed_set.erase(neighbor->state);
            }
        }
    }
}

// std::priority_queue<Node*, std::vector<Node*>, CompareNodes> open_set;
// Node : what to store
// Vector of nodes : where to store
// compare function : how to sort the nodes

// NP problems == Nondeterministic Polynomial time problems :These problems have the special property that, once a potential solution is provided, its correctness can be verified quickly. However, finding the solution itself may be computationally difficult.