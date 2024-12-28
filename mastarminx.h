#ifndef MASTARMINX_H
#define MASTARMINX_H

#include <iostream> // for console input / output
#include <cstdlib> // for randomness (srand)
#include <time.h> // for randomnness (time, obv.)
#include <map> // for pyraminx struct

// for clarity in program
const char RED = 'R';
const char BLUE = 'B';
const char YELLOW = 'Y';
const char GREEN = 'G';
// for reference points in the puzzle
const int AX1 = 1;
const int AX2 = 2;
const int AX3 = 3;
const int AX4 = 4;
// puzzle specs
const int SIDE_STICKERS = 16;
const int NUM_SIDES = 4;
const int NUM_CORNERS = 4;
// directions for rotations
const char CW = 'C'; // (C for clockwise)
const char CC = 'B'; // (B for backwards)

class Mastarminx {
    public:
        // constructor
        Mastarminx();
        // special constructor with pre-made setup
        Mastarminx(std::map<int, std::array<char, 16> > config);

        // set the configuration
        // useful for using one object for controlling multiple configs
        void setconfig(std::map<int, std::array<char, 16> > config);
        // rotates based on the axis perpendicular to the side choice,
        // the level on the axis to rotate, and the direction
        // (clockwise or counter-clockwise)
        void rotate(int SIDE, int LVLS, char DIR);

        // print a side of the puzzle
        void pyraprint(int SIDE);
        // fetch a side of the puzzle as a std::array
        std::array<char, 16> getside(int SIDE);
        // fetch the whole puzzle config
        std::map<int, std::array<char, 16> > getconfig();

        /* 
        randomizer function for the puzzle
        takes the number of moves to scramble
        and uses functions from included c++
        libraries to randomize which rotation
        to perform on the puzzle 
        */
        void scramble();

    private:
        struct Corner{
            char* L1[3]; // the corner
            char* L2[9]; // layer below corner
            char* L3[15]; // the layer that is 2 layers below corner
            // L4 not necessary, as an L4 rotation is equivalent to rotating L1-L3.
            std::map<int, std::array<char, 16> >* PYRA_PTR; // might be useful later on?

            Corner(){} // default constructor
            Corner(std::map<int, std::array<char, 16> >& PUZZLE, int AXIS);
            void rotate(int LVLS, char DIR);
        };
        
        // the primary container of all stickers in the puzzle,
        // which all corner struct ptrs point to
        std::map<int, std::array<char, 16> > PYRAMINX;
        
        // the 4 AXIS corner structures
        Corner AXIS_1;
        Corner AXIS_2;
        Corner AXIS_3;
        Corner AXIS_4;
};

/*________________PRIVATE CORNER STRUCT CONTENTS________________*/
/* 
in my opinion, this is the most complex element of this program...

consider the possible rotations that can be made
on the 4x4x4 pyraminx to occur around four different
axes (since rotations are either clockwise or counter-c.,
pyraminx rotations work nicely around an axis).

each axis goes straight through one of the four corners.

this corner structure represents horizontal layers that
can be rotated about a respective axis.

four of these corner structs are made, representing the
axes that each have four rotatable layers

the layers consist of many pointers (27 per struct)
to the positions/stickers of the puzzle that make up
the three puzzle sides surrounding an axis

(
for example, the 2nd level on one of the axis
of a solved pyraminx would look like this as
an array:

L2[9] = {R, R, R,   B, B, B,   G, G, G}
where each letter is the memory retrieved 
from a dereferenced pointer.
)

what's the purpose of this? an extremely simple,
single, rotation function that takes few parameters
*/
Mastarminx::Corner::Corner(std::map<int, std::array<char, 16> >& PUZZLE, int AXIS) { 
    PYRA_PTR = &PUZZLE;
    if (AXIS == AX1) {

        L1[0] = &(PUZZLE[3][9]);
        L1[1] = &(PUZZLE[2][15]);
        L1[2] = &(PUZZLE[4][0]);

        L2[0] = &(PUZZLE[3][11]);L2[1] = &(PUZZLE[3][10]);L2[2] = &(PUZZLE[3][4]);
        L2[3] = &(PUZZLE[2][8]);L2[4] = &(PUZZLE[2][14]);L2[5] = &(PUZZLE[2][13]);
        L2[6] = &(PUZZLE[4][1]);L2[7] = &(PUZZLE[4][2]);L2[8] = &(PUZZLE[4][3]);

        L3[0] = &(PUZZLE[3][13]);L3[1] = &(PUZZLE[3][12]);L3[2] = &(PUZZLE[3][6]);L3[3] = &(PUZZLE[3][5]);L3[4] = &(PUZZLE[3][1]);
        L3[5] = &(PUZZLE[2][3]);L3[6] = &(PUZZLE[2][7]);L3[7] = &(PUZZLE[2][6]);L3[8] = &(PUZZLE[2][12]);L3[9] = &(PUZZLE[2][11]);
        L3[10] = &(PUZZLE[4][4]);L3[11] = &(PUZZLE[4][5]);L3[12] = &(PUZZLE[4][6]);L3[13] = &(PUZZLE[4][7]);L3[14] = &(PUZZLE[4][8]);

    }
    else if (AXIS == AX2) {

        L1[0] = &(PUZZLE[1][9]);
        L1[1] = &(PUZZLE[3][15]);
        L1[2] = &(PUZZLE[4][15]);

        L2[0] = &(PUZZLE[1][11]);L2[1] = &(PUZZLE[1][10]);L2[2] = &(PUZZLE[1][4]);
        L2[3] = &(PUZZLE[3][8]);L2[4] = &(PUZZLE[3][14]);L2[5] = &(PUZZLE[3][13]);
        L2[6] = &(PUZZLE[4][8]);L2[7] = &(PUZZLE[4][14]);L2[8] = &(PUZZLE[4][13]);

        L3[0] = &(PUZZLE[1][13]);L3[1] = &(PUZZLE[1][12]);L3[2] = &(PUZZLE[1][6]);L3[3] = &(PUZZLE[1][5]);L3[4] = &(PUZZLE[1][1]);
        L3[5] = &(PUZZLE[3][3]);L3[6] = &(PUZZLE[3][7]);L3[7] = &(PUZZLE[3][6]);L3[8] = &(PUZZLE[3][12]);L3[9] = &(PUZZLE[3][11]);
        L3[10] = &(PUZZLE[4][3]);L3[11] = &(PUZZLE[4][7]);L3[12] = &(PUZZLE[4][6]);L3[13] = &(PUZZLE[4][12]);L3[14] = &(PUZZLE[4][11]);

    }
    else if (AXIS == AX3) {

        L1[0] = &(PUZZLE[2][9]);
        L1[1] = &(PUZZLE[1][15]);
        L1[2] = &(PUZZLE[4][9]);

        L2[0] = &(PUZZLE[2][11]);L2[1] = &(PUZZLE[2][10]);L2[2] = &(PUZZLE[2][4]);
        L2[3] = &(PUZZLE[1][8]);L2[4] = &(PUZZLE[1][14]);L2[5] = &(PUZZLE[1][13]);
        L2[6] = &(PUZZLE[4][11]);L2[7] = &(PUZZLE[4][10]);L2[8] = &(PUZZLE[4][4]);

        L3[0] = &(PUZZLE[2][13]);L3[1] = &(PUZZLE[2][12]);L3[2] = &(PUZZLE[2][6]);L3[3] = &(PUZZLE[2][5]);L3[4] = &(PUZZLE[2][1]);
        L3[5] = &(PUZZLE[1][3]);L3[6] = &(PUZZLE[1][7]);L3[7] = &(PUZZLE[1][6]);L3[8] = &(PUZZLE[1][12]);L3[9] = &(PUZZLE[1][11]);
        L3[10] = &(PUZZLE[4][13]);L3[11] = &(PUZZLE[4][12]);L3[12] = &(PUZZLE[4][6]);L3[13] = &(PUZZLE[4][5]);L3[14] = &(PUZZLE[4][1]);

    }
    else if (AXIS == AX4) {

        L1[0] = &(PUZZLE[2][0]);
        L1[1] = &(PUZZLE[3][0]);
        L1[2] = &(PUZZLE[1][0]);

        L2[0] = &(PUZZLE[2][1]);L2[1] = &(PUZZLE[2][2]);L2[2] = &(PUZZLE[2][3]);
        L2[3] = &(PUZZLE[3][1]);L2[4] = &(PUZZLE[3][2]);L2[5] = &(PUZZLE[3][3]);
        L2[6] = &(PUZZLE[1][1]);L2[7] = &(PUZZLE[1][2]);L2[8] = &(PUZZLE[1][3]);

        L3[0] = &(PUZZLE[2][4]);L3[1] = &(PUZZLE[2][5]);L3[2] = &(PUZZLE[2][6]);L3[3] = &(PUZZLE[2][7]);L3[4] = &(PUZZLE[2][8]);
        L3[5] = &(PUZZLE[3][4]);L3[6] = &(PUZZLE[3][5]);L3[7] = &(PUZZLE[3][6]);L3[8] = &(PUZZLE[3][7]);L3[9] = &(PUZZLE[3][8]);
        L3[10] = &(PUZZLE[1][4]);L3[11] = &(PUZZLE[1][5]);L3[12] = &(PUZZLE[1][6]);L3[13] = &(PUZZLE[1][7]);L3[14] = &(PUZZLE[1][8]);

    }
}
/*
LVLS := L1-L3 to rotate, DIR := direction
--  rotations occur about the axis perpendicular
    to the chosen face to rotate a level on
--  rotations are simply made of many repeated swaps
    of each sticker on a LVL.
*/
void Mastarminx::Corner::rotate(int LVLS, char DIR) {
    if (DIR == CW) {
        rotate(LVLS, CC); 
        // since each rotation is clockwise 120" / 360" total,
        // a CW rotation == 2 CC rotations
        // this isnt exactly efficient, but its convenient...
    }
    if (LVLS == 1) {
        std::swap(*L1[2], *L1[1]);
        std::swap(*L1[1], *L1[0]);
    }
    if (LVLS == 2) {
        for (int i = 0; i < 3; i++) {
            std::swap(*L2[8], *L2[7]);
            std::swap(*L2[7], *L2[6]);
            std::swap(*L2[6], *L2[5]);
            std::swap(*L2[5], *L2[4]);
            std::swap(*L2[4], *L2[3]);
            std::swap(*L2[3], *L2[2]);
            std::swap(*L2[2], *L2[1]);
            std::swap(*L2[1], *L2[0]);
        }
    }
    if (LVLS == 3) {
        for (int i = 0; i < 5; i++) {
            std::swap(*L3[14], *L3[13]);
            std::swap(*L3[13], *L3[12]);
            std::swap(*L3[12], *L3[11]);
            std::swap(*L3[11], *L3[10]);
            std::swap(*L3[10], *L3[9]);
            std::swap(*L3[9], *L3[8]);
            std::swap(*L3[8], *L3[7]);
            std::swap(*L3[7], *L3[6]);
            std::swap(*L3[6], *L3[5]);
            std::swap(*L3[5], *L3[4]);
            std::swap(*L3[4], *L3[3]);
            std::swap(*L3[3], *L3[2]);
            std::swap(*L3[2], *L3[1]);
            std::swap(*L3[1], *L3[0]);
        }
    }
    if (LVLS == 4) {
        rotate(1, CW);
        rotate(2, CW);
        rotate(3, CW);
    }
};


/*________________CLASS CONTENTS________________*/
/*
constructs a pre-solved pyraminx and stores it in
a map of four 16-char std::arrays.

it then creates the four corner structs that point
to their respective locations on the four faces.
*/
Mastarminx::Mastarminx() {
    std::array<char, 16> TRUE_R = 
    {
            'R', /* front face */
        'R','R','R',
    'R','R','R','R','R',
'R','R','R','R','R','R','R'
    
    };

    std::array<char, 16> TRUE_B = {
            'B', /* right face */
        'B','B','B',
    'B','B','B','B','B',
'B','B','B','B','B','B','B'
    
    };

    std::array<char, 16> TRUE_G = {
            'G', /* left face */
        'G','G','G',
    'G','G','G','G','G',
'G','G','G','G','G','G','G'
    };

    std::array<char, 16> TRUE_Y = {
            'Y', /* bottom face */
        'Y','Y','Y',
    'Y','Y','Y','Y','Y',
'Y','Y','Y','Y','Y','Y','Y'
    };

    PYRAMINX[1] = TRUE_R;
    PYRAMINX[2] = TRUE_B;
    PYRAMINX[3] = TRUE_G;
    PYRAMINX[4] = TRUE_Y;

    AXIS_1 = Corner(PYRAMINX, AX1);
    AXIS_2 = Corner(PYRAMINX, AX2);
    AXIS_3 = Corner(PYRAMINX, AX3);
    AXIS_4 = Corner(PYRAMINX, AX4);
}

// the same as the default constructor, but config is not pre-solved
Mastarminx::Mastarminx(std::map<int, std::array<char, 16> > config) {
    PYRAMINX[1] = config[1];
    PYRAMINX[2] = config[2];
    PYRAMINX[3] = config[3];
    PYRAMINX[4] = config[4];
    AXIS_1 = Corner(PYRAMINX, AX1);
    AXIS_2 = Corner(PYRAMINX, AX2);
    AXIS_3 = Corner(PYRAMINX, AX3);
    AXIS_4 = Corner(PYRAMINX, AX4);
}

/*
accomplishes what the second constructor does but in the case that an
object already has been created and it wishes to have a new config
*/
void Mastarminx::setconfig(std::map<int, std::array<char, 16> > config) {
    PYRAMINX = config;
    AXIS_1 = Corner(PYRAMINX, AX1);
    AXIS_2 = Corner(PYRAMINX, AX2);
    AXIS_3 = Corner(PYRAMINX, AX3);
    AXIS_4 = Corner(PYRAMINX, AX4);
}

// parameters correspond with the parameters of Corner::rotate()
// read more about Corner::Corner and Corner::rotate for more details
void Mastarminx::rotate(int SIDE, int LVLS, char DIR) {
    if (SIDE == 1) {
        AXIS_1.rotate(LVLS, DIR);
    }
    if (SIDE == 2) {
        AXIS_2.rotate(LVLS, DIR);
    }
    if (SIDE == 3) {
        AXIS_3.rotate(LVLS, DIR);
    }
    if (SIDE == 4) {
        AXIS_4.rotate(LVLS, DIR);
    }
}
// returns an array from the PYRAMINX map
std::array<char, 16> Mastarminx::getside(int SIDE) {
    return PYRAMINX[SIDE];
}
// returns the entire PYRAMINX map
std::map<int, std::array<char, 16> > Mastarminx::getconfig() {
    return PYRAMINX;
}

/*
takes num_moves (k) and randomly rotates the puzzle k times.
--  random moves are achieved by having a randomizing seed
    (srand()) based on the current time (time(0))
--  the random numbers generated are minimized to be between
    1-4 and 0-1 for the purpose of randomizing which face,
    LVL, and direction to rotate the puzzle in each move
--  for the sake of the efficiency of the IDA* algorithm,
    directional randomness has been eliminated. this means
    that all random rotations will occur clockwise.
*/
void Mastarminx::scramble() {
    int num_moves;
    std::cout << "\nHow many moves would you like to scramble (integer only)? ";
    std::cin >> num_moves;
    // NOTE: CURRENTLY SET TO ALWAYS SCRAMBLE CLOCKWISE FOR PURPOSE OF EASIER SOLVING
    std::array<char, 2> DIRS = {CW, CW}; // for random choice based on random int index
    srand(time(0)); // random seeds for random numbers 
    for (int i = 0; i < num_moves; i++) {
        int rand_side = rand() % 4 + 1; // rand. int in interval [1, 4]
        int rand_dir = rand() % 2; // [0, 1]
        int rand_lvl = rand() % 4 + 1; // [1, 4]
        if (rand_side == 1) {
            AXIS_1.rotate(rand_lvl, DIRS[rand_dir]);
            std::cout << "\nRandomly rotated level " << rand_lvl;
            std::cout << " on axis 1";
            std::cout << " in the " << ((DIRS[rand_dir] == CW) ? "clockwise direction\n" : "counter-clockwise direction:\n");
        }
        else if (rand_side == 2) {
            AXIS_2.rotate(rand_lvl, DIRS[rand_dir]);
            std::cout << "\nRandomly rotated level " << rand_lvl;
            std::cout << " on axis 2";
            std::cout << " in the " << ((DIRS[rand_dir] == CW) ? "clockwise direction\n" : "counter-clockwise direction:\n");
        }
        else if (rand_side == 3) {
            AXIS_3.rotate(rand_lvl, DIRS[rand_dir]);
            std::cout << "\nRandomly rotated level " << rand_lvl;
            std::cout << " on axis 3";
            std::cout << " in the " << ((DIRS[rand_dir] == CW) ? "clockwise direction\n" : "counter-clockwise direction:\n");
        }
        else if (rand_side == 4) {
            AXIS_4.rotate(rand_lvl, DIRS[rand_dir]);
            std::cout << "\nRandomly rotated level " << rand_lvl;
            std::cout << " on axis 4";
            std::cout << " in the " << ((DIRS[rand_dir] == CW) ? "clockwise direction\n" : "counter-clockwise direction:\n");
        }
        pyraprint(0); // print all sides to show updated config.
    }
    // this could have probably been written to be more efficient by
    // placing for loops in the conditionals rather than so many 
    // conditionals in one for loop, but i dont feel like changing it
}

// prints either one side of the puzzle or all four sides of the puzzle
void Mastarminx::pyraprint(int SIDE) { // it aint that impressive, but im sure proud of it
    if (SIDE >=1 && SIDE <= 4) {
        std::cout << "\n";
        std::cout << "               /^\\\n";
        std::cout << "              /   \\\n";
        std::cout << "             /  "<<PYRAMINX[SIDE][0]<<"  \\\n";
        std::cout << "            /_______\\\n";
        std::cout << "           /^\\     /^\\\n";
        std::cout << "          /   \\ "<<PYRAMINX[SIDE][2]<<" /   \\\n";
        std::cout << "         /  "<<PYRAMINX[SIDE][1]<<"  \\ /  "<<PYRAMINX[SIDE][3]<<"  \\\n";
        std::cout << "        /_______V_______\\\n";
        std::cout << "       /^\\     /^\\     /^\\\n";
        std::cout << "      /   \\ "<<PYRAMINX[SIDE][5]<<" /   \\ "<<PYRAMINX[SIDE][7]<<" /   \\\n";
        std::cout << "     /  "<<PYRAMINX[SIDE][4]<<"  \\ /  "<<PYRAMINX[SIDE][6]<<"  \\ /  "<<PYRAMINX[SIDE][8]<<"  \\\n";
        std::cout << "    /_______V_______V_______\\\n";
        std::cout << "   /^\\     /^\\     /^\\     /^\\\n";
        std::cout << "  /   \\ "<<PYRAMINX[SIDE][10]<<" /   \\ "<<PYRAMINX[SIDE][12]<<" /   \\ "<<PYRAMINX[SIDE][14]<<" /   \\\n";
        std::cout << " /  "<<PYRAMINX[SIDE][9]<<"  \\ /  "<<PYRAMINX[SIDE][11]<<"  \\ /  "<<PYRAMINX[SIDE][13]<<"  \\ /  "<<PYRAMINX[SIDE][15]<<"  \\\n";
        std::cout << "/_______V_______V_______V_______\\\n";
        std::cout << "\n";
    }
    // provides same output on fewer lines
    // 1x4 triangles outputted instead of 4x1 triangles outputted
    // FAR easier to scroll through in the console
    else {

    std::cout << "\n";
    std::cout << "               /^\\                ";
    std::cout << "               /^\\                ";
    std::cout << "               /^\\                ";
    std::cout << "               /^\\                ";

    std::cout << "\n";
    std::cout << "              /   \\               ";
    std::cout << "              /   \\               ";
    std::cout << "              /   \\               ";
    std::cout << "              /   \\               ";

    std::cout << "\n";
    std::cout << "             /  "<<PYRAMINX[1][0]<<"  \\              ";
    std::cout << "             /  "<<PYRAMINX[2][0]<<"  \\              ";
    std::cout << "             /  "<<PYRAMINX[3][0]<<"  \\              ";
    std::cout << "             /  "<<PYRAMINX[4][0]<<"  \\              ";

    std::cout << "\n";
    std::cout << "            /_______\\             ";
    std::cout << "            /_______\\             ";
    std::cout << "            /_______\\             ";
    std::cout << "            /_______\\             ";

    std::cout << "\n";
    std::cout << "           /^\\     /^\\            ";
    std::cout << "           /^\\     /^\\            ";
    std::cout << "           /^\\     /^\\            ";
    std::cout << "           /^\\     /^\\            ";

    std::cout << "\n";
    std::cout << "          /   \\ "<<PYRAMINX[1][2]<<" /   \\           ";
    std::cout << "          /   \\ "<<PYRAMINX[2][2]<<" /   \\           ";
    std::cout << "          /   \\ "<<PYRAMINX[3][2]<<" /   \\           ";
    std::cout << "          /   \\ "<<PYRAMINX[4][2]<<" /   \\           ";


    std::cout << "\n";
    std::cout << "         /  "<<PYRAMINX[1][1]<<"  \\ /  "<<PYRAMINX[1][3]<<"  \\          ";
    std::cout << "         /  "<<PYRAMINX[2][1]<<"  \\ /  "<<PYRAMINX[2][3]<<"  \\          ";
    std::cout << "         /  "<<PYRAMINX[3][1]<<"  \\ /  "<<PYRAMINX[3][3]<<"  \\          ";
    std::cout << "         /  "<<PYRAMINX[4][1]<<"  \\ /  "<<PYRAMINX[4][3]<<"  \\          ";


    std::cout << "\n";
    std::cout << "        /_______V_______\\         ";
    std::cout << "        /_______V_______\\         ";
    std::cout << "        /_______V_______\\         ";
    std::cout << "        /_______V_______\\         ";

    std::cout << "\n";
    std::cout << "       /^\\     /^\\     /^\\        ";
    std::cout << "       /^\\     /^\\     /^\\        ";
    std::cout << "       /^\\     /^\\     /^\\        ";
    std::cout << "       /^\\     /^\\     /^\\        ";

    std::cout << "\n";
    std::cout << "      /   \\ "<<PYRAMINX[1][5]<<" /   \\ "<<PYRAMINX[1][7]<<" /   \\       ";
    std::cout << "      /   \\ "<<PYRAMINX[2][5]<<" /   \\ "<<PYRAMINX[2][7]<<" /   \\       ";
    std::cout << "      /   \\ "<<PYRAMINX[3][5]<<" /   \\ "<<PYRAMINX[3][7]<<" /   \\       ";
    std::cout << "      /   \\ "<<PYRAMINX[4][5]<<" /   \\ "<<PYRAMINX[4][7]<<" /   \\       ";

    std::cout << "\n";
    std::cout << "     /  "<<PYRAMINX[1][4]<<"  \\ /  "<<PYRAMINX[1][6]<<"  \\ /  "<<PYRAMINX[1][8]<<"  \\      ";
    std::cout << "     /  "<<PYRAMINX[2][4]<<"  \\ /  "<<PYRAMINX[2][6]<<"  \\ /  "<<PYRAMINX[2][8]<<"  \\      ";
    std::cout << "     /  "<<PYRAMINX[3][4]<<"  \\ /  "<<PYRAMINX[3][6]<<"  \\ /  "<<PYRAMINX[3][8]<<"  \\      ";
    std::cout << "     /  "<<PYRAMINX[4][4]<<"  \\ /  "<<PYRAMINX[4][6]<<"  \\ /  "<<PYRAMINX[4][8]<<"  \\      ";

    std::cout << "\n";
    std::cout << "    /_______V_______V_______\\     ";
    std::cout << "    /_______V_______V_______\\     ";
    std::cout << "    /_______V_______V_______\\     ";    
    std::cout << "    /_______V_______V_______\\     ";    

    std::cout << "\n";
    std::cout << "   /^\\     /^\\     /^\\     /^\\    ";
    std::cout << "   /^\\     /^\\     /^\\     /^\\    ";
    std::cout << "   /^\\     /^\\     /^\\     /^\\    ";
    std::cout << "   /^\\     /^\\     /^\\     /^\\    ";

    std::cout << "\n";
    std::cout << "  /   \\ "<<PYRAMINX[1][10]<<" /   \\ "<<PYRAMINX[1][12]<<" /   \\ "<<PYRAMINX[1][14]<<" /   \\   ";
    std::cout << "  /   \\ "<<PYRAMINX[2][10]<<" /   \\ "<<PYRAMINX[2][12]<<" /   \\ "<<PYRAMINX[2][14]<<" /   \\   ";
    std::cout << "  /   \\ "<<PYRAMINX[3][10]<<" /   \\ "<<PYRAMINX[3][12]<<" /   \\ "<<PYRAMINX[3][14]<<" /   \\   ";
    std::cout << "  /   \\ "<<PYRAMINX[4][10]<<" /   \\ "<<PYRAMINX[4][12]<<" /   \\ "<<PYRAMINX[4][14]<<" /   \\   ";

    std::cout << "\n";
    std::cout << " /  "<<PYRAMINX[1][9]<<"  \\ /  "<<PYRAMINX[1][11]<<"  \\ /  "<<PYRAMINX[1][13]<<"  \\ /  "<<PYRAMINX[1][15]<<"  \\  ";
    std::cout << " /  "<<PYRAMINX[2][9]<<"  \\ /  "<<PYRAMINX[2][11]<<"  \\ /  "<<PYRAMINX[2][13]<<"  \\ /  "<<PYRAMINX[2][15]<<"  \\  ";
    std::cout << " /  "<<PYRAMINX[3][9]<<"  \\ /  "<<PYRAMINX[3][11]<<"  \\ /  "<<PYRAMINX[3][13]<<"  \\ /  "<<PYRAMINX[3][15]<<"  \\  ";
    std::cout << " /  "<<PYRAMINX[4][9]<<"  \\ /  "<<PYRAMINX[4][11]<<"  \\ /  "<<PYRAMINX[4][13]<<"  \\ /  "<<PYRAMINX[4][15]<<"  \\  ";

    std::cout << "\n";
    std::cout << "/_______V_______V_______V_______\\ ";
    std::cout << "/_______V_______V_______V_______\\ ";
    std::cout << "/_______V_______V_______V_______\\ ";
    std::cout << "/_______V_______V_______V_______\\ ";
    std::cout << "\n";
    }
}

#endif