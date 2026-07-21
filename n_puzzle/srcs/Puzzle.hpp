#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <memory>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <algorithm>
using namespace std;


class Puzzle{
    private :
        int heuristic;
        int size;
        int searchMode;
        vector<int> puzzle;
        vector<int> goal;
        vector<int> goalPositions;

        double timeComplexity; 
        size_t spaceComplexity;
        size_t count;

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
                if(a->f == b->f)
                    return a->h > b->h;
                return a->f > b->f;
            }
        };
        Puzzle();
        void read_data(const string &filename, int heuristicChoice, int searchModeChoice);
        vector<shared_ptr<Puzzle::Node>> getNeighbors(const shared_ptr<Node> &current) const;
        void printPath(const shared_ptr<Node> &goalNode) const;
        void printGrid(const vector<int> &state) const;

        void solvePuzzle();
        vector<int> generateSnailGoal();
        bool checkSolvability();
        int computeH(const vector<int> &state) const;
        int computeF(int g, int h) const;
        ~Puzzle();

};
