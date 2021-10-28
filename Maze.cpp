//
// Created by BumbleBee on 12/08/2019.
//
//i is y axis
//j is x axis
#include "Maze.h"


Maze::Maze() {
    //cout<<"Iresh"<<endl;

}
void Maze::initialzeCenterPath() {

    for (int i = 0; i < 14; i++) {
        //maze=Node *node;
        for (int j = 0; j < 14; j++) {
            struct Node node;
            maze[i][j]=node;
            maze[i][j].i=i;
            maze[i][j].j=j;
            //maze[i][j].northWall=true;
            //maze[i][j].eastWall=true;
            //maze[i][j].southWall=true;
            //maze[i][j].westWall=true;
        }
    }

    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 14; j++) {
            if(j<7 & i<7){
                maze[i][j].value= 12-(i+j);
            }
            if(j<7 & i>=7){
                maze[i][j].value= i-1-j;
            }
            if(j>=7 & i<7){
                maze[i][j].value=j-1-i;
            }
            if(j>=7 & i>=7){
                maze[i][j].value=(i+j)-14;
            }
        }
    }
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 14; j++) {
            if(i==0){
                maze[i][j].northWall=true;
            }
            if(i==13){
                maze[i][j].southWall=true;
            }
            if(j==0){
                maze[i][j].westWall=true;
            }
            if(j==13){
                maze[i][j].eastWall=true;
            }

        }
    }

}
void Maze::printMaze() {
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 14; j++) {
            if(j==0){
                cout << "+";
            }
            if(j==0 & maze[i][j].northWall){
                cout<<"\b";
            }
            if(j>0 & maze[i][j-1].northWall & maze[i][j].northWall){
                cout<<"\b";
            }
            if (maze[i][j].northWall) {
                cout << "+ - - - +";
            }else{
                cout<<"\t";
            }
            if (j == 13 & i==0 ) {
                cout << "\b";
            }
            if (j == 13 ) {
                cout << "+" << endl;
            }
        }
        //cout<<"+"<<endl;
        for (int j = 0; j < 14; j++) {
            if (maze[i][j].westWall) {
                cout << "|";
            }
            if (currX == j & currY == i) {
                cout << "   X";
                switch (direction) {
                    case 0:
                        cout << "^\t";
                        break;
                    case 1:
                        cout << ">\t";
                        break;
                    case 2:
                        cout << "V\t";
                        break;
                    case 3:
                        cout << "<\t";
                        break;
                }
            }else{
                cout << "   " << maze[i][j].value << "\t";
            }
            if (maze[i][j].eastWall) {
                cout << "|";
            }
            if (j == 13) {
                cout << "" << endl;
            }
        }
        //south wall
        for (int j = 0; j < 14; j++) {
            if (maze[i][j].southWall) {
                cout << "+ - - - ";
            }else{
                //cout<<"\t";
            }
            if (j == 13 & maze[i][j].southWall) {
                cout << "+" << endl;
            }
        }
    }
}
void Maze::printWall(bool left, bool front, bool right) {
    switch(direction){
        case 0:
            if(left){
                maze[currY][currX].westWall=true;//correct this
            }if(front){
                maze[currY][currX].northWall=true;
            }if(right){
                if(currX+1<14) {
                    maze[currY][currX + 1].westWall = true;
                }
            }break;
        case 1:
            if(left){
                maze[currY][currX].northWall=true;
            }if(front){
                if(currX+1<14) {
                    maze[currY][currX+1].westWall=true;
                }
            }if(right){
                if(currY+1<14){
                    maze[currY+1][currX].northWall=true;
                }
            }break;
        case 2:
            if(left){
                if(currX+1<14) {
                    maze[currY][currX+1].westWall=true;
                }
            }if(front){
                if(currY+1<14){
                    maze[currY+1][currX].northWall=true;
                }
            }if(right){
                maze[currY][currX].westWall=true;
            }break;
        case 3:
            if(left){
                if(currY+1<14){
                    maze[currY+1][currX].northWall=true;
                }
            }if(front){
                maze[currY][currX].westWall=true;
            }if(right){
                maze[currY][currX].northWall=true;
            }break;
    }
    //hasNorth();
    printMaze();
}
void Maze::searchMiniCell() {
    minDistance=maze[currY][currX].value-1;
    if(direction==0 & minDistance==searchNorthCellVal() & !(searchNorthWall())){// if North
        moveNorth();
    }else if(direction==1 & minDistance==searchEastCellVal() & !(searchEastWall())){
        moveEast();
    }else if(direction==2 & minDistance==searchSouthCellVal() & !(searchSouthWall())){
        moveSouth();
    }else if(direction==3 & minDistance==searchWestCellVal() & !(searchWestWall())){
        moveWest();
    }else{
        if(minDistance==searchNorthCellVal() & !(searchNorthWall())){
            moveNorth();
        }else if(minDistance==searchEastCellVal() & !(searchEastWall())){
            moveEast();
        }else if(minDistance==searchSouthCellVal() & !(searchSouthWall())){
            moveSouth();
        }else if(minDistance==searchWestCellVal() & !(searchWestWall())){
            moveWest();
        }else{
            updateCellsValue();
        }
    }
}
bool Maze::searchNorthWall() {
    if(maze[currY][currX].northWall){
        return true;
    }
    return false;
}
bool Maze::searchEastWall() {
    if(currX<13){
        if(maze[currY][currX].eastWall | maze[currY][currX+1].westWall){
            return true;
        }
    }else if(currX==13){
        return maze[currY][currX].eastWall;
    }else{
        return false;
    }
    return false;
}
bool Maze::searchSouthWall() {
    if(currY<13){
        if(maze[currY][currX].southWall | maze[currY+1][currX].northWall){
            return true;
        }
    }else if(currY==13){
        return maze[currY][currX].southWall;
    }else{
        return false;
    }
    return false;
}
bool Maze::searchWestWall() {
    if(maze[currY][currX].westWall){
        return true;
    }
    return false;
}
bool Maze::searchNeighbourNorthWall(Node *n) {
    if(maze[n->i][n->j].northWall){
        return true;
    }
    return false;
}
bool Maze::searchNeighbourEastWall(Node *n) {
    if(n->j<13){
        if(maze[n->i][n->j].eastWall | maze[n->i][n->j+1].westWall){
            return true;
        }
    }else if(n->j==13){
        return maze[n->i][n->j].eastWall;
    }else{
        return false;
    }
    return false;
}
bool Maze::searchNeighbourSouthWall(Node *n) {
    if(n->i<13){
        if(maze[n->i][n->j].southWall | maze[n->i+1][n->j].northWall){
            return true;
        }
    }else if(n->i==13){
        return maze[n->i][n->j].southWall;
    }else{
        return false;
    }
    return false;
}
bool Maze::searchNeighbourWestWall(Node *n) {
    if(maze[n->i][n->j].westWall){
        return true;
    }
    return false;
}
void Maze::updateCellsValue() {
    cout<<"upadate cell values"<<endl;
    //push Current Node when Flooded
    pushNode(&maze[currY][currX]);
    while(getTop()>0){
        printStack();
        Node *n=pullNode();
        short min=255;
        if(n->i>0 & !searchNeighbourNorthWall(n)){
            cout<<"\t North:("<<maze[n->i-1][n->j].j+1<<","<<maze[n->i-1][n->j].i+1<<")"<<endl;
            //pushNode(&maze[currY-1][currX]);
            if(min > maze[n->i-1][n->j].value){
                min=maze[n->i-1][n->j].value;
                cout<<"\t min North:"<<maze[n->i-1][n->j].value<<endl;

            }
        }
        if(n->i<13 & !searchNeighbourSouthWall(n)){
            cout<<"\t South:("<<maze[n->i+1][n->j].j+1<<","<<maze[n->i+1][n->j].i+1<<")"<<endl;
            //pushNode(&maze[currY+1][currX]);
            if(min > maze[n->i+1][n->j].value){
                min=maze[n->i+1][n->j].value;
                cout<<"\t min South:"<<maze[n->i+1][n->j].value<<endl;
            }
        }
        if(n->j>0 & !searchNeighbourWestWall(n)){
            cout<<"\t West:("<<maze[n->i][n->j-1].j+1<<","<<maze[n->i][n->j-1].i+1<<")"<<endl;
            //pushNode(&maze[currY][currX-1]);
            if(min > maze[n->i][n->j-1].value){
                min=maze[n->i][n->j-1].value;
                cout<<"\t min West:"<<maze[n->i][n->j-1].value<<endl;
            }
        }
        if(n->j<13 & !searchNeighbourEastWall(n)){
            cout<<"\t East:("<<maze[n->i][n->j+1].j+1<<","<<maze[n->i][n->j+1].i+1<<")"<<endl;
            //pushNode(&maze[currY][currX+1]);
            if(min > maze[n->i][n->j+1].value){
                min=maze[n->i][n->j+1].value;
                cout<<"\t min East:"<<maze[n->i][n->j+1].value<<endl;
            }
        }
        //end of min search
        if(n->value-1 != min){
            n->value=min+1;
            maze[n->i][n->j].value=n->value;
            cout<<"Update node X:"<<n->j+1<<" Y:"<<n->i+1<<" value:"<<n->value<<endl;
            pushOpenNeighbourNode(n);
            //delete(n);
        }
    }
    printMaze();
}
void Maze::pushNode(Node *node) {

    stack[top].value=node->value;
    stack[top].northWall=node->northWall;
    stack[top].eastWall=node->eastWall;
    stack[top].southWall=node->southWall;
    stack[top].westWall=node->westWall;
    stack[top].i=node->i;
    stack[top].j=node->j;
    //cout<<"top:"<<top<<"\tX:"<<stack[top].j<<"\tY:"<<stack[top].i<<endl;
    top++;
}
short Maze::getTop() {
    return top;
}
void Maze::pushOpenNeighbourNode(Node *node) {
    if(node->i>0 & !searchNorthWall()){
        pushNode(&maze[node->i-1][node->j]);
    }
    if(node->i<13 & !searchSouthWall()){
        pushNode(&maze[node->i+1][node->j]);
    }
    if(node->j>0 & !searchWestWall()){
        pushNode(&maze[node->i][node->j-1]);
    }
    if(node->j<13 & !searchEastWall()){
        pushNode(&maze[node->i][node->j+1]);
    }
}
Node* Maze::pullNode() {
    return &stack[--top];
}
void Maze::printStack() {
    cout<<"Stack top:"<<top<<"\tX:"<<stack[top-1].j+1<<"\tY:"<<stack[top-1].i+1<<endl;
}
short Maze::searchNorthCellVal() {
    if(currY-1>=0){
        return maze[currY-1][currX].value;
    }
    return maze[currY][currX].value;
}
short Maze::searchEastCellVal() {
    if(currX+1<14){
        return maze[currY][currX+1].value;
    }
    return maze[currY][currX].value;
}
short Maze::searchSouthCellVal() {
    if(currY+1<14){
        return maze[currY+1][currX].value;
    }
    return maze[currY][currX].value;
}
short Maze::searchWestCellVal() {
    if(currX-1>=0){
        return maze[currY][currX-1].value;
    }
    return maze[currY][currX].value;
}
void Maze::moveNorth() {
    //cout<<"missed me?";
    currY--;
    if(currY<0){
        currY++;
    }
    turnNorth();
    printMaze();
}
void Maze::moveEast() {
    currX++;
    if(currX>13){
        currX--;
    }
    turnEast();
    printMaze();
}
void Maze::moveSouth() {
    currY++;
    if(currY>13){
        currY--;
    }
    turnSouth();
    printMaze();
}
void Maze::moveWest() {
    currX--;
    if(currX<0){
        currX++;
    }
    turnWest();
    printMaze();
}
void Maze::turnNorth() {
    direction=0;
}
void Maze::turnEast() {
    direction=1;
}
void Maze::turnSouth() {
    direction=2;
}
void Maze::turnWest() {
    direction=3;
}
void Maze::hasNorth() {
    for (int i = 0; i < 14; ++i) {
        for (int j = 0; j <14 ; ++j) {
            if(maze[i][j].northWall){
                cout<<"north has x:"<<j<<" y:"<<i<<endl;
            }
        }
    }
}
