#include "Puzzle.hpp"

int main(int ac, char **av){
    if (ac < 2){
        cerr << "Usage ./n_puzzle <puzzle_file> [heuristic : 1|2|3]" << endl;
        return 1;
    }
    Puzzle p;
    p.read_data(ac, av);
    
    return 0;
}