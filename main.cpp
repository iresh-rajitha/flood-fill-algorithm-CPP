#include <iostream>
#include "Maze.h"

int main() {
    Maze maze;
    maze.initialzeCenterPath();
    maze.printMaze();
    int x=0;
    while(x<255){
        cin>>x;
        switch(x){
            case 1:maze.moveNorth();break;
            case 2:maze.moveEast();break;
            case 3:maze.moveSouth();break;
            case 4:maze.moveWest();break;
            case 5:maze.printMaze();break;
            case 6:maze.printWall(true,true,true);break;
            case 7:maze.printWall(false,true,false);break;
            case 8:maze.hasNorth();break;
            case 9:maze.searchMiniCell();break;

            default:break;
        }
    }

    return 0;
}