#pragma once

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
        // clock_t complexity;
        int heuristic;
        int size;
        vector<int> puzzle;
        vector<int> goal;
        vector<int> goalPositions;

        // size_t timeComplexity; 
        // size_t spaceComplexity;

        string strip_comments(const string &line);
    public:

        struct Node{      
                vector<int> state;
                int g; // cost to reach this node
                int h; // heuristic cost to reach goal from this node
                int f; // total cost (g + h)
                int zeroPos;
                shared_ptr<Node> parent;
        };
        
        struct CompareNodes {
            bool operator()(const shared_ptr<Node>& a, const shared_ptr<Node>& b) const {
                if(a->f != b->f)
                    return a->f > b->f;
                return a->h > b->h; // If f is equal, prioritize the node with lower h
            }
        };
        Puzzle();
        void read_data(int ac, char **av);
        void solvePuzzle();
        vector<int> generateSnailGoal();
        bool checkSolvability();
        int computeH();
        ~Puzzle();

};
