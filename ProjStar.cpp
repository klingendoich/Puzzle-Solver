// provides implementation of the 4x4x4 Pyraminx,
// rotation functions, and a basic text-output
#include "mastarminx.h"
// provides implementation of IDA* algorithm to
// provide a puzzle solution and algorithms stats
#include "starpower.h"


int main() {
    // create a pre-solved 4x4x4 pyraminx
    Mastarminx HolyOfHolies;

    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~\n ";
    std::cout << " Before the Scramble:";
    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~\n";
    // print out what it looks like
    HolyOfHolies.pyraprint(0);
    
    // asks for k number of moves,
    // rotates pyraminx randomly k times
    HolyOfHolies.scramble();

    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~\n ";
    std::cout << " After the Scramble:";
    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~\n";
    HolyOfHolies.pyraprint(0);

    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~\n ";
    std::cout << " Solving the Puzzle";
    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << "\nPlease wait as the algorithm finds a solution.....\n";

    // hands over the scrambled puzzle config to the IDA* algorithm to solve
    PyrAStar Solver(HolyOfHolies.getconfig());
    // result of the solver is a vector containing ordered steps/rotations necessary to solve the puzzle
    std::vector<std::array<int, 3> > moves = Solver.asolve();

    // prints out the solution in action, solving the pyraminx step-by-step
    std::cout << "\nIt takes " << moves.size() << " moves to solve the puzzle!\n";
    for (int i = 0; i < moves.size(); i++) {
        std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n ";
        std::cout << " Step " << i + 1 << ": Rotate L" << moves[i][1];
        std::cout << " of Face " << moves[i][0] << " in the ";
        std::cout << (((char) moves[i][2]) == CC ? "counterclockwise " : "clockwise ") << "direction.";
        std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n ";
        HolyOfHolies.rotate(moves[i][0], moves[i][1], (char) moves[i][2]);
        HolyOfHolies.pyraprint(0);
    }

    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~\n ";
    std::cout << " After the Solve:";
    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~\n";
    HolyOfHolies.pyraprint(0);

    // provides stats of the IDA* algorithm's expanded nodes in the last iteration of IDA*
    // (as per professor's request)
    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    std::cout << " Nodes expanded in last iteration: " << Solver.expandednodes;
    std::cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

    return 0;
}