#include "Puzzle.hpp"

int main(int ac, char **av){
    if (ac < 2){
        cerr << "Usage ./n_puzzle <puzzle_file> [heuristic : 1|2|3]" << endl;
        return 1;
    }
    Puzzle p;
    p.read_data(ac, av);
    if(!p.checkSolvability()){
        cout << "Puzzle is not solvable" << endl;
        exit(1);
    }
    p.solvePuzzle();
    
    return 0;
}