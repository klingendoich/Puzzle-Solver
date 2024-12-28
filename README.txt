==============================================================
============================ ___ =============================
=========================== /   \ ============================
========================== /     \ ===========================
========================= /  THE  \ ==========================
======================== /         \ =========================
======================= /   MASTER  \ ========================
====================== /             \ =======================
===================== /    PYRAMINX   \ ======================
==================== /_________________\ =====================
==============================================================


_____________________ | Requirements | _______________________

<> A computer running Linux or macOS
<> C++11 or later with its standard libraries
<> G++ or Clang++ compiler
<> A terminal to run the program and read program output from
______________________________________________________________
v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^


_____________________ | Instructions | _______________________

[1] In your terminal, change your current directory to the
 unzipped folder containing both header files and the
 "ProjStar.cpp" file.
==============================================================
[2] Run the below command to compile the program:

 (with g++ compiler)
 g++ -std=c++11 ProjStar.cpp -o ProjectStar

 (with clang++ compiler)
 clang++ -std=c++11 ProjStar.cpp -o ProjectStar
==============================================================
[3] Now, run the following command to run the program:
 ./ProjectStar
==============================================================
[4] Provide an integer value as the number of moves to
 scramble the master pyraminx puzzle in, and watch it work!
______________________________________________________________
v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^ 


______________ | The Data Structures Involved | ______________

There are 2 primary data structures involved in masterminx.h:
<> A private map of the master pyraminx's four faces, each
 represented by an array of 16 chars, labeled “PYRAMINX”
<> A custom "Corner" struct that contains 27 pointers to
 specific positions on the master pyraminx.
While the map of four arrays is fairly simple, the Corner
struct is a bit more complicated. when making this program,
I wanted to find a way to minimize the number of rotation
functions necessary to move every part of the puzzle. In
order to accomplish this, I created this struct and made
four instances of it in the program. This struct allows me to
view the pyraminx from the perspective of four separate axes,
each of which include both stickers/pieces unique to each
axis and stickers/pieces shared among multiple axes. Each
struct represents a top-down view of three horizontal
layers/slices of the master pyraminx, with the top level,
level 1, being a corner piece itself. Given that these
layers can only turn clockwise or counter-clockwise, one can
say that they are rotating about an imaginary fixed axis that
pierces through a corner piece and the center of the corner
piece's opposite-side face (if I explained that poorly,
imagine just sitting the puzzle on a desk and then poking a
needle straight through the top and center of the it).
This structure includes a single rotation function that
handles which level to rotate on the axis and which direction
to rotate it, clockwise or counter-clockwise.
==============================================================

There are 2 primary data structures involved in starpower.h:

<> A custom “Pnode” struct that contains essential information
 That allows it to be usable in a tree and by IDA*
<> A custom “PQ” struct that represents a priority queue that
 uses a min-heap that sorts Pnodes by order of its f-values.

Both of these structures are essential to the program for many
reasons. Let’s start by breaking down the Pnode struct (in its
full name, “Pyraminx Node"). This structure contains many
different variables:

<> A configuration of the puzzle
<> The last rotation that created its configuration 
<> A pointer to the Pnode’s parent
<> An array of pointers to the Pnode’s children
<> The h-value, supplemented by a built-in heuristic function
<> The g-value, which is the Pnode’s distance from the root
<> The f-value, which is the sum of the h-value and g-value.

As can be seen above, a Pnode is equipped for the sole purpose
of being placed in a tree and used by the A* algorithm. Now,
let’s break down the PQ struct’s contents:

<> A std::vector that contains Pnode children pointers (HEAP)
<> An integer storing the size of the heap (HEAPSIZE).

For the sake of priority queues and min-heaps, these variables
are fairly straightforward in what their purposes are. The
additional functions that are included in this struct are used
to build the heap/queue into a min-heap, ordering the Pnodes
by their corresponding f-values, the Pnodes with the lowest 
fvalues having greatest priority.
______________________________________________________________
v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^


___________________ | The Heuristic Used | ___________________

Going back to the built-in heuristic function implemented in
the Pnode struct, the heuristic I chose to use may not be the
best, but it does work: max(# colors found on each face) - 1.
In other terms, this heuristic function looks at each face of
the pyraminx and sees how many colors it finds on it. After
counting this total for each face, it picks the maximum total
found among the puzzle’s faces and subtracts 1 from it. At the
very least, this shows how many colors are not on the side
they need to be and thus the LEAST number of rotations that
will be used to solve it (for example, rotating one level of
the pyraminx puzzle will leave three sides with two colors.
2-1=1, which we obviously know is the number of moves to fully
solve the puzzle.). Additionally, a heuristic of 0 tells us
that the puzzle has no stickers out of place and therefore is
in a solved state.
______________________________________________________________
v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^v^ 
