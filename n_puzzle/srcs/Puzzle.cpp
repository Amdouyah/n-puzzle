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
            else
                this->heuristic = heuristic;
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

// std::priority_queue<Node*, std::vector<Node*>, CompareNodes> open_set;
// Node : what to store
// Vector of nodes : where to store
// compare function : how to sort the nodes