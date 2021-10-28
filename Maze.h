//
// Created by BumbleBee on 12/08/2019.
//

#ifndef UNTITLED7_MAZE_H
#define UNTITLED7_MAZE_H

#include <iostream>
using namespace std;

struct Node{
    short i=0,j=0,value;
    bool northWall= false,eastWall=false,southWall=false,westWall= false,visited=false;
};



class Maze {
public:
    Node maze[14][14];
    short direction=0;
    short minDistance;
    short currX=0,currY=13;

    Node stack[50];
    short top=0;

    Maze();
    void initialzeCenterPath();
    void printMaze();
    void printWall(bool left,bool front,bool right);
    void moveNorth();
    void moveEast();
    void moveSouth();
    void moveWest();
    void turnNorth();
    void turnEast();
    void turnSouth();
    void turnWest();
    void hasNorth();
    void searchMiniCell();
    void updateCellsValue();
    short searchNorthCellVal();
    short searchEastCellVal();
    short searchSouthCellVal();
    short searchWestCellVal();
    bool searchNorthWall();
    bool searchEastWall();
    bool searchSouthWall();
    bool searchWestWall();
    void pushNode(Node *node);
    Node* pullNode();
    void pushOpenNeighbourNode(Node *node);
    short getTop();
    void printStack();
    bool searchNeighbourNorthWall(Node *n);
    bool searchNeighbourEastWall(Node *n);
    bool searchNeighbourSouthWall(Node *n);
    bool searchNeighbourWestWall(Node *n);

};


#endif //UNTITLED7_MAZE_H
