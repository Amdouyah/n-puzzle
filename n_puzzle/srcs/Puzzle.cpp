#include "Puzzle.hpp"

Puzzle::Puzzle() : move_count(0), complexity(0), heuristic(0), size(0) {}

Puzzle::~Puzzle() {}

string Puzzle::strip_comments(const string &line) {
    size_t comment_pos = line.find('#');
    if (comment_pos != string::npos) {
        return line.substr(0, comment_pos);
    }
    return line;
}

void Puzzle::read_data(int ac, char **av) {
    try {
        ifstream file(av[1]);
        string line;
        if (!file.is_open()) {
            throw runtime_error("Error: Could not open file " + string(av[1]));
        }
        if (ac == 3) {
            heuristic = std::stoi(av[2]);
            if (heuristic < 1 || heuristic > 3) {
                throw std::runtime_error("Error: Invalid heuristic value. Must be 1, 2, or 3.");
            }
        }
        else {
            heuristic = 1;
        }
        // here
        int n = -1;
        vector<int> grid;
        while(getline(file, line)){
            line = strip_comments(line); 
            // if (line.empty()) {
            //     continue;
            // } 
            istringstream iss(line);
 
            if (n == -1) {
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
 
        this->size = n;
        this->puzzle = grid;
    }
    catch (std::exception &e) {
        cerr << e.what() << endl;
    }
}

std::vector<int> Puzzle::generateSnailGoal()
{
    std::vector<int> goal(size * size, 0);
    int size = this->size;

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

bool Puzzle::checkSolvability(){
    

}

// std::priority_queue<Node*, std::vector<Node*>, CompareNodes> open_set;
// Node : what to store
// Vector of nodes : where to store
// compare function : how to sort the nodes

//NP problems == Nondeterministic Polynomial time problems :These problems have the special property that, once a potential solution is provided, its correctness can be verified quickly. However, finding the solution itself may be computationally difficult.