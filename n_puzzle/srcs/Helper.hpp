#pragma once

#include "Puzzle.hpp"

vector<int> buildGoalRank(const vector<int> &goal);
vector<int> convertToRanks(const vector<int> &board, const vector<int> &goalRank);
int countInversions(const vector<int> &ranks);

vector<int> buildGoalPos(const vector <int> &goal);

int hammingDistance(const vector<int> &state, const vector<int> &goal);
int manhattanDistance(const vector<int> &state, const vector<int> &goalPositions, int size);
int linearConflict(const vector<int> &state, const vector<int> &goalPositions, int size);
int computeHeuristic(int heuristicType, const vector<int> &state, const vector<int> &goal, const vector<int> &goalPositions, int size);


struct VectorHash
{
    size_t operator()(const vector<int> &v) const
    {
        size_t seed = v.size();
        for (int x : v)
            seed ^= static_cast<size_t>(x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};