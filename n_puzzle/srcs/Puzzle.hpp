#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
using namespace std;

class Puzzle{
    private :
        int move_count;
        clock_t complexity;
        int heuristic;
        int size;
        vector<int> puzzle;;

        string strip_comments(const string &line);
    public:
        Puzzle();
        void read_data(int ac, char **av);
        void readPuzzle(string file);
        // void printPuzzle();
        void solvePuzzle(int heuristic);
        ~Puzzle();

};