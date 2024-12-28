#ifndef STARPOWER_H
#define STARPOWER_H

 // works closely with Mastarminx in performing rotations
 // to create new instances/configurations of the puzzle
#include "mastarminx.h"
#include <vector> // more convenient than arrays at times
#include <unordered_set> // for size tracking w/o dupe vals
/*
<list> used as container to hold all generated nodes.
--  lists are used specifically for the purpose of keeping
    placed container elements where they are as the size
    of the container increases.
--  this property is crucial as there will be an immense
    number of pointers to these nodes, and not a single
    node can be moved lest an error/segfault/etc. occurs
*/
#include <list>


class PyrAStar {
    public:
        PyrAStar(std::map<int, std::array<char, 16> > START);
        std::vector<std::array<int, 3> > asolve();
        int expandednodes;
    private:
        struct Pnode {
            std::map<int, std::array<char, 16>> config;
            std::array<int, 3> lastmove;
            Pnode* parent;
            // 16 possible rotations = 16 children
            std::array<Pnode*, 16> children = {nullptr};
            // h := heuristic value
            int h;
            // g := distance from root
            int g;
            // f := g + h
            int f;
            Pnode() {}
            Pnode(std::map<int, std::array<char, 16> > arg1, std::array<int, 3> arg2);
            void update();
            void addchild(Pnode* arg1);
            int heur();
            int fval();
        };
        // min heap priority queue: priority = minimum f value
        // modified version of my code used to complete PA3 in CS*315
        struct PQ {
            std::vector<Pnode*> HEAP;
            int HEAPSIZE;
            PQ() {}
            PQ(std::array<Pnode*, 16> &CHILDREN);
            void minheapify(int i);
            void buildminheap();
            Pnode* extractmin();
            bool empty();
        };

        void offspring(Pnode* parent);
        void asearch(Pnode* currNode, int threshold, std::unordered_set<int>& pruned_values);
        void makestats();
        
        /*
        all generated children of the
        root pyraminx node are stored here
        for easier memory management
        */
        Pnode* ROOT;
        std::list<Pnode> PYRACHEST;

        Pnode* GOAL;
        bool GOALFOUND;
        std::vector<std::array<int, 3> > GOALPATH;
};

/*________________PRIVATE PNODE STRUCT CONTENTS________________*/
// each Pnode struct holds a config of the puzzle, the last move
// made to reach that config, a ptr to its parent, and then its
// g-value (dist. from ROOT), h-value (heuristic), and f-value (g+h)
PyrAStar::Pnode::Pnode(std::map<int, std::array<char, 16> > arg1, std::array<int, 3> arg2) {
    config = arg1;
    lastmove = arg2;
    parent = nullptr;
    g = 0; // node is a root iff it has no parent
    h = heur();
    f = fval();
}
// used by addchild() to update g-value
// and f-value of a node when changes occur.
void PyrAStar::Pnode::update() {
    if (parent != nullptr) {
        g=(parent->g)+1;
    }
    f = fval();
}
// update both parent and child node with
// corresponding ptrs, and then update 
// child's g-value and f-value.
void PyrAStar::Pnode::addchild(Pnode* arg1) {
    arg1->parent = this;
    arg1->update();
    for (int i = 0; i < children.size(); i++) {
        if (children[i] == nullptr) {
            children[i] = arg1;
            return;
        }
    }
    arg1->update();
}
/*
the heuristic function!!
--  h = (maximum of the # colors found on each face) - 1
--  max value of 3, min of 0 (0 == solved)
--  not the best heuristic but it works.
--  as far as my testing goes, this heuristic + my program
    implementation allows for scrambling of up to 8 moves.
--  unless a solution takes < k scrambled moves, a k=9+
    scramble leads to excessive RAM usage and the program
    is killed by my OS. :(
*/
int PyrAStar::Pnode::heur() {
    int heur = 0; 
    // unordered because i only care about preventing duplicate vals
    std::unordered_set<char> foundcolors;
    std::unordered_set<int> faceheurs;
    for (int face = 1; face <= 4; face++) {
        for (int sticker = 0; sticker < 16; sticker++) {
            foundcolors.insert((this->config)[face][sticker]);
        }
        faceheurs.insert(foundcolors.size()-1);
        foundcolors.clear();
    }
    for (auto it = faceheurs.begin(); it != faceheurs.end(); it++) {
        if (*it > heur) {
            heur = *it;
        }
    }
    return heur;
}
// calculates f = g + h
int PyrAStar::Pnode::fval() {
    return (this->g + this->h);
}

/*________________PRIVATE PRIORITY QUEUE STRUCT CONTENTS________________*/
// adds the children pointers of a parent to a vectors
// after adding all children, build a min heap to order nodes by f-value
PyrAStar::PQ::PQ(std::array<Pnode*, 16> &CHILDREN) {
    for (int i = 0; i < CHILDREN.size() && CHILDREN[i] != nullptr; i++) {
        HEAP.push_back(CHILDREN[i]);
    }
    HEAPSIZE = HEAP.size();
    buildminheap();
}
// used to build the minheap
void PyrAStar::PQ::minheapify(int i) {
    int l = (i*2)+1;
    int r = (i*2)+2;
    int smallest;
    if (l < HEAPSIZE && HEAP[l]->f < HEAP[i]->f) {
        smallest = l;
    } 
    else {
        smallest = i;
    }
    if (r < HEAPSIZE && HEAP[r]->f < HEAP[smallest]->f) {
        smallest = r;
    } 
    if (smallest != i) {
        Pnode *middleman = HEAP[i];
        HEAP[i] = HEAP[smallest];
        HEAP[smallest] = middleman;
        minheapify(smallest);
    } 
}
// sorts the nodes in order of lowest to greatest f-values
void PyrAStar::PQ::buildminheap() {
    for (int i = (HEAPSIZE / 2) -1; i >= 0; i--) {
        minheapify(i);
    }
}
// removes the first element, aka the node w/ lowest f-value
// rebuilds the minheap after extracting the node
PyrAStar::Pnode* PyrAStar::PQ::extractmin() {
    if (HEAPSIZE < 1) {
        std::cout << "\nPQ ERROR: HEAP UNDERFLOW\n";
        return NULL;
    }
    Pnode *min = HEAP[0];
    HEAP[0] = HEAP[HEAPSIZE-1];
    HEAPSIZE = HEAPSIZE - 1;
    HEAP.pop_back();
    minheapify(0);
    return min;
}
// checks if queue is empty, returns T/F
bool PyrAStar::PQ::empty() {
    return !HEAP.size();
}


/*________________CLASS FUNCTIONS________________*/
// creates ROOT node of the tree using the START puzzle config
// adds ROOT to the node container.
// assigns the ROOT pointer to the location of ROOT node in list
PyrAStar::PyrAStar(std::map<int, std::array<char, 16> > START) {
    std::array<int, 3> nomoves = {0, 0, 0};
    PYRACHEST.push_back(Pnode(START, nomoves));
    ROOT = &PYRACHEST.front();
}

/*
starts off the IDA* search algorithm and sustains it.

--  produces offspring of ROOT, aka the scambled config

--  creates an f-value threshold from the pruned-values
    list that asearch() returns. this threshold prevents
    the exploration of nodes with either bad heuristic 
    values or takes more moves to reach (bad g-value)

--  tracks the results of the exploration/search of the
    tree showing every possible move that can be 
    performed on the 4x4x4 pyraminx

--  when asearch finds the goal, asearch updates the
    GOALFOUND flag and returns, and asolve() adds to 
    GOALPATH the trail leading from ROOT to GOAL
*/
std::vector<std::array<int, 3> > PyrAStar::asolve() {
    GOALFOUND = false;
    if (ROOT->h == 0) {
        GOALFOUND = true;
        GOAL = ROOT;
        expandednodes = 0;
        return GOALPATH;
    }
    offspring(ROOT);
    int threshold;
    std::unordered_set<int> pruned_values = {ROOT->f};
    while (!GOALFOUND) {
        auto it = pruned_values.begin();
        threshold = *it;
        it++;
        for (; it != pruned_values.end(); it++) {
            if (*it < threshold) {
                threshold = *it;
            }
        }
        pruned_values.clear();
        expandednodes = 1;
        asearch(ROOT, threshold, pruned_values);
    }

    // add path to reach goal to GOALPATH
    Pnode* currNode = GOAL;
    for (; currNode->parent != nullptr; currNode = currNode->parent) {
        GOALPATH.insert(GOALPATH.begin(), currNode->lastmove);
    }
    return GOALPATH;
}

// given that the child (currNode) is not GOAL:
// if a child f-val is <= threshold, offspring() it and search its children
// otherwise add f-val to pruned_values and return.
// if the child == GOAL, GOAL == child, GOALFOUND == true,
// and return all recursive instances of the function
void PyrAStar::asearch(Pnode* currNode, int threshold, std::unordered_set<int>& pruned_values) {
    if (GOALFOUND) {
        return;
    }
    // minheap/priority queue
    PQ kidheap = PQ(currNode->children);
    while (!kidheap.empty()) {
        Pnode* child = kidheap.extractmin();
        if (child->h == 0) {
            GOAL = child;
            GOALFOUND = true;
            return;
        }
        if (child->f <= threshold) {
            // expand the node
            expandednodes += 1;
            offspring(child);
            asearch(child, threshold, pruned_values);
        }
        else {
            pruned_values.insert(child->f);
            return;
        }
    }
}

/*
quick summary:
offspring() takes a node and gives it 16 children.
each child represents a possible rotation that can be
performed on the 4x4x4 pyraminx. with 16 children, 
every possible rotation is available to explore.
*/
void PyrAStar::offspring(Pnode* parent) {
    Mastarminx rotater = Mastarminx(parent->config);
    // this gives each parent 16 children, EEK!
    // could run into MAJOR memory problems... :(
    for (int face = 1; face <= 4; face++) {
        for (int level = 1; level <= 4; level++) {
            /* 
            a painful seg fault problem was fixed here...
            
            the node struct needs to be defined, placed into the list,
            and THEN parent->children pointers should be assigned.

            if you attempt to nest functions + constructors, such as
            "
            addToList(new Node(config, parent))
            "
            and the Node(config, parent) constructor assigns a pointer to
            itself within the parent->children container BEFORE it's placed
            in the list, the pointer to itself does not point to its
            location in the list but rather to its location before it got 
            moved into the list. this was a painful seg fault to figure out...

            ...rant is now over, please carry onward...
            */
            rotater.setconfig(parent->config);
            rotater.rotate(face, level, CC);
            std::array<int, 3> move = {face, level, (int) CC};
            PYRACHEST.push_back(Pnode(rotater.getconfig(), move));
            parent->addchild(&PYRACHEST.back());
        }
    }
}

#endif
