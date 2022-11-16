#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <array>
#include <vector>
#include <GL/freeglut.h>
#include <GLUT/glut.h>
using namespace std;

/*this function initializes the grid as a multidimensional
vector, and then returns it. The goal will be to initialize,
populate, and then compute.*/

int WIDTH = 800;
int HEIGHT = 600;


vector<vector<int> > gridInit(int nrow, int mcol){
    vector<vector<int> > grid(nrow, vector<int>(mcol, 0));
    for (int i = 0; i < nrow; i++){
        for (int j = 0; j < mcol; j++){
            int n = rand() & 1;
            grid[i][j] = n;
        }
        
    }
    return grid;
}

int getNeighbors(vector<vector<int> > grid, int row, int col){
    int topn [3]= {grid[row - 1][col - 1], grid[row - 1][col], grid[row - 1][col + 1]};
    int lr [2] = {grid[row][col - 1], grid[row][col + 1]};
    int botn [3] = {grid[row + 1][col - 1], grid[row + 1][col], grid[row + 1][col + 1]};
    int neighbors = 0;
    for (int i = 0; i < 3; i++){
        if (topn[i] == 1){
            neighbors++;
        }
        if (botn[i] == 1){
            neighbors++;
        }
    }
    for (int i = 0; i < 2; i++){
        if (lr[i] == 1){
            neighbors++;
        }
    }
    return neighbors;
}

void printGrid(vector<vector<int> > grid){
    for (int i = 0; i < grid.size(); i++){
        for (int j = 0; j < grid[i].size(); j++){
            cout << grid[i][j] << ", ";
        }
        cout << endl;
    }
}

vector<vector<int> > game = gridInit(HEIGHT, WIDTH);

void init(){
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

void stepGame(vector<vector<int> > &grid){
    int* n = new int(0);
    for (int i = 0; i < grid.size(); i++){
        for (int j = 0; j < grid[i].size(); j++){
            //live cell rules
            if (grid[i][j] == 1){
                if (getNeighbors(grid, i, j) < 2 || getNeighbors(grid, i, j) > 3){
                    grid[i][j] = 0;
                }
            }
            // dead cell rules
            if (grid[i][j] == 0){
                if (getNeighbors(grid, i, j) > 3){
                    grid[i][j] = 1;
                }
            }
        }
    }
}

void readGrid(vector<vector<int> > grid){

}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    stepGame(game);
    readGrid(game);
    glFlush();
    glFinish();
}


int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Conway's Game of Life");
    init();
    glutDisplayFunc(display);
    //printGrid(grid);
    return 0;
}