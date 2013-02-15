//
//  Graph.h
//  MazeGenerator
//
//  Created by Vishal Patel on 8/04/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef MazeGenerator_Graph_h
#define MazeGenerator_Graph_h

#include <vector>

using namespace std;

enum _Direction {
    Top      = 1,
    Right    = 4,
    Bottom   = 2,
    Left     = 8,
};
typedef enum _Direction Direction;

struct GraphNode {
    
    GraphNode* right;
    GraphNode* left;
    GraphNode* top;
    GraphNode* bottom;
    
    bool visited;
    unsigned int directionNext;
    
public:
    
    GraphNode() {
        right = NULL;
        left  = NULL;
        top   = NULL;
        bottom = NULL;
        visited = false;
        directionNext = 0;
    }
    
    inline bool Visited() { return visited ; }
    inline void MarkVisited(bool visited) {
        this->visited = visited;
    }
};

typedef GraphNode Node;

class MazeGraph {
    
    vector<Node*> nodeStack;
    
public:
    
    MazeGraph();
    Node* CreateGridGraph( int numRow, int numCol );
    void printNode(Node* rootNode);
    void Traversal(Node* rootNode);
    int Randomize();
    bool AllNodesAreVisited(Node* rootNode);
    ~MazeGraph();
};

#endif
