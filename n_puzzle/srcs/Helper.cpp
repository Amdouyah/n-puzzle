#include "Helper.hpp"

vector<int> buildGoalRank(const vector<int> &goal)
{
    std::vector<int> rank(goal.size(), 0);

    int currentRank = 1;

    for (size_t i = 0; i < goal.size(); i++)
    {
        if (goal[i] == 0)
            continue;
        rank[goal[i]] = currentRank++;
    }
    return rank;
}

std::vector<int> convertToRanks(const std::vector<int> &board, const std::vector<int> &goalRank)
{
    std::vector<int> result;

    for (size_t i = 0; i < board.size(); i++)
    {
        if (board[i] == 0)
            continue;
        result.push_back(goalRank[board[i]]);
    }

    return result;
}
int countInversions(const vector<int> &ranks)
{
    int inversions = 0;
    for (size_t i = 0; i < ranks.size(); i++)
    {
        for (size_t j = i + 1; j < ranks.size(); j++)
        {
            if (ranks[i] > ranks[j])
                inversions++;
        }
    }
    return inversions;
}

vector<int> buildGoalPos(const vector <int> &goal)
{
    vector<int> goalPos(goal.size(), 0);
    for (size_t i = 0; i < goal.size(); i++)
        goalPos[goal[i]] = i;
    return goalPos;
}
//heuristic

int hammingDistance(const vector<int> &state, const vector<int> &goal)
{
    int count = 0;
    for (size_t i = 0; i < state.size(); i++)
    {
        if (state[i] != 0 && state[i] != goal[i])
            count++;
    }
    return count;
}

int manhattanDistance(const vector<int> &state, const vector<int> &goalPositions, int size)
{
    int total = 0;
    for (size_t i = 0; i < state.size(); i++)
    {
        int value = state[i];
        if (value == 0)
            continue;
        int goalIndex = goalPositions[value];
        int curRow = static_cast<int>(i) / size;
        int curCol = static_cast<int>(i) % size;
        int goalRow = goalIndex / size;
        int goalCol = goalIndex % size;
        total += abs(curRow - goalRow) + abs(curCol - goalCol);
    }
    return total;
}

int linearConflict(const vector<int> &state, const vector<int> &goalPositions, int size){
    int total = manhattanDistance(state, goalPositions, size);

    for (int row = 0; row < size; row++)
    {
        vector<int> tilesInRow;
        for (int col = 0; col < size; col++)
        {
            int value = state[row * size + col];
            if (value == 0)
                continue;
            int goalRow = goalPositions[value] / size;
            if (goalRow == row)
                tilesInRow.push_back(value);
        }
        for (size_t i = 0; i < tilesInRow.size(); i++)
        {
            for (size_t j = i + 1; j < tilesInRow.size(); j++)
            {
                if (goalPositions[tilesInRow[i]] > goalPositions[tilesInRow[j]])
                    total += 2;
            }
        }
    }

    for (int col = 0; col < size; col++)
    {
        vector<int> tilesInCol;
        for (int row = 0; row < size; row++)
        {
            int value = state[row * size + col];
            if (value == 0)
                continue;
            int goalCol = goalPositions[value] % size;
            if (goalCol == col)
                tilesInCol.push_back(value);
        }
        for (size_t i = 0; i < tilesInCol.size(); i++)
        {
            for (size_t j = i + 1; j < tilesInCol.size(); j++)
            {
                if (goalPositions[tilesInCol[i]] > goalPositions[tilesInCol[j]])
                    total += 2;
            }
        }
    }

    return total;
}

int computeHeuristic(int heuristicType, const vector<int> &state, const vector<int> &goal, const vector<int> &goalPositions, int size)
{
    if (heuristicType == 2)
        return hammingDistance(state, goal);
    if (heuristicType == 3)
        return linearConflict(state, goalPositions, size);
    return manhattanDistance(state, goalPositions, size);
}