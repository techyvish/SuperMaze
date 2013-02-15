//
//  Graph.cpp
//  MazeGenerator
//
//  Created by Vishal Patel on 8/04/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Graph.h"

using namespace std;

template <typename T>
T **AllocateMemory(int numRows,int numCols) {
    T **dynamicArray;
    dynamicArray = new T *[numCols];
    for ( int i = 0 ; i < numRows ; i++ ) {
        dynamicArray[i] = new T [numCols];
    }
    return dynamicArray;
}

MazeGraph::MazeGraph() {
    srand((unsigned int)time((time_t *)NULL));
    Node* rootNode =  CreateGridGraph(3, 3);
    printNode(rootNode);
    Traversal(rootNode);
}

Node* MazeGraph::CreateGridGraph( int numRow, int numCol ) {
    Node* **nodes = AllocateMemory<Node*>(numRow, numCol);
    for ( int i = 0 ; i < numRow ; i ++ ) {
        for (int j = 0 ; j < numCol ; j++ ) {
            Node *newNode = new Node();
            nodes[i][j] = newNode;
            if ( j >= 1 ) {
                Node* tempNode  = nodes[i][j - 1 ];
                newNode->left = tempNode;
                tempNode->right = newNode;
            }
            if ( i >= 1 ) {
                Node* tempNode = nodes[i-1][j];
                newNode->top = tempNode;
                tempNode->bottom = newNode;
            }
        }
    }
    return nodes[0][0];
}

void MazeGraph::printNode(Node* rootNode ){
    while (rootNode != NULL ) {
        while (rootNode->right != NULL) {
            rootNode = rootNode->right;
        }
        
        while ( rootNode-> left != NULL ) {
            rootNode = rootNode->left;
        }
        printf("\n");
        rootNode = rootNode->bottom;
    }
}

int MazeGraph::Randomize(){
    return   (rand() % 4) ;    
}

bool MazeGraph::AllNodesAreVisited(Node* rootNode) {
    bool allVisited = true;
    if ( rootNode->left != NULL )
        allVisited &= rootNode->left->Visited();
    if ( rootNode->right != NULL )
        allVisited &= rootNode->right->Visited();
    if ( rootNode->top != NULL )
        allVisited &= rootNode->top->Visited();
    if ( rootNode->bottom != NULL )
        allVisited &= rootNode->bottom->Visited();
    return allVisited;
}

void MazeGraph::Traversal(Node* rootNode) {

    if ( rootNode == NULL)
        return;
    nodeStack.push_back(rootNode);
    rootNode->MarkVisited(true);
    switch ( Randomize() ) {
        case 0 : {
            if ( rootNode->left != NULL && !rootNode->left->Visited() ) {
                rootNode->directionNext |= Left;
                rootNode->left->directionNext |= Right;
                printf(" %d \n", rootNode->directionNext );
                Traversal(rootNode->left);
            }
        }break;
            
        case 1:{
            if ( rootNode->right != NULL && !rootNode->right->Visited() ) {
                rootNode->directionNext |= Right;
                rootNode->right->directionNext |= Left;
                printf(" %d \n", rootNode->directionNext );
                Traversal(rootNode->right);
            }
        }break;
            
        case 2:{
            if ( rootNode->top != NULL && !rootNode->top->Visited() ) {
                rootNode->directionNext |= Top;
                rootNode->top->directionNext |= Bottom;
                printf(" %d \n", rootNode->directionNext );
                Traversal(rootNode->top);
            }
        }break;
            
        case 3: {
            if ( rootNode->bottom != NULL && !rootNode->bottom->Visited() ) {
                rootNode->directionNext |= Bottom;
                rootNode->bottom->directionNext |= Top;
                printf(" %d \n", rootNode->directionNext );
                Traversal(rootNode->bottom);
            }
        }break;
    }
    
    vector<Node*>::iterator it =  nodeStack.end() - 1;
    rootNode = *it;
    nodeStack.pop_back();
    
    if ( !AllNodesAreVisited(rootNode) )
        Traversal(rootNode);
    
}

MazeGraph::~MazeGraph() {
    
}