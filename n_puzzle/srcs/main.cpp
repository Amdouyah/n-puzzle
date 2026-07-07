#include "Puzzle.hpp"

int main(int ac, char **av){
    if (ac < 1){
        try{
            Puzzle p;
        }
        catch (std::exception &e){
            std::cerr << e.what() << std::endl;
        }
    }
    return 0;
}