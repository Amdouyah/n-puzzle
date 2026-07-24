#include "Puzzle.hpp"

static void printUsage(const char *prog)
{
    cerr << "Usage: " << prog << " <puzzle_file> [-h heuristic:1|2|3] [-s search:1= A* 2= greedy 3= uniform-cost]" << endl;
    cerr << "  -h  1 = Manhattan distance (default), 2 = Hamming distance, 3 = Linear conflict" << endl;
    cerr << "  -s  1 = A* (default), 2 = greedy best-first, 3 = uniform-cost" << endl;
}

static bool isNumber(const string &s)
{
    if (s.empty())
        return false;
    for (char c : s)
    {
        if (!std::isdigit(static_cast<unsigned char>(c)))
            return false;
    }
    return true;
}

int main(int ac, char **av){

    string filename;
    int heuristic = 1;
    int searchMode = 1;

    for (int i = 1; i < ac; i++)
    {
        string arg = av[i];

        if (arg == "-h" || arg == "-s")
        {
            if (i + 1 >= ac)
            {
                cerr << "Error: " << arg << " requires a value." << endl;
                printUsage(av[0]);
                return 1;
            }
            int value = std::atoi(av[++i]);
            if (arg == "-h"){
                if (value < 1 || value > 3)
                {
                    cerr << "Error: Invalid heuristic value. Must be 1, 2, or 3." << endl;
                    return 1;
                }
                heuristic = value;
            }
            else{
                if (value < 1 || value > 3)
                {
                    cerr << "Error: Invalid search mode value. Must be 1, 2, or 3." << endl;
                    return 1;
                }
                searchMode = value;
            }
        }
        else if (filename.empty())
        {
            filename = arg;
        }
        else
        {
            cerr << "Error: unexpected argument '" << arg << "'." << endl;
            printUsage(av[0]);
            return 1;
        }
    }

    if (filename.empty())
    {
        printUsage(av[0]);
        return 1;
    }
    
    Puzzle p;
    if (isNumber(filename))
        p.generatePuzzle(std::atoi(filename.c_str()), heuristic, searchMode);
    else
        p.read_data(filename, heuristic, searchMode);
    if(!p.checkSolvability()){
        cout << "Puzzle is not solvable" << endl;
        exit(1);
    }
    p.solvePuzzle();
    
    return 0;
}