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
    int neighbors = 0;
    if (row < HEIGHT && col < WIDTH && row > 0 && col > 0){
        neighbors += grid.at(row - 1).at(col - 1);
        neighbors += grid.at(row - 1).at(col);
        neighbors += grid.at(row - 1).at(col + 1);
        neighbors += grid.at(row).at(col - 1);
        neighbors += grid.at(row).at(col + 1);
        neighbors += grid.at(row + 1).at(col - 1);
        neighbors += grid.at(row + 1).at(col);
        neighbors += grid.at(row + 1).at(col + 1);
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
                try{
                    if (getNeighbors(grid, i, j) < 2 || getNeighbors(grid, i, j) > 3){
                    grid[i][j] = 0;
                    }
                }
                catch(const std::out_of_range & ex){
                    cout << "out of range exception caught" << ex.what();
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
    cout << "initial state: " << endl;
    printGrid(game);
    cout << "stepping game: " << endl;
    stepGame(game);
    cout << "game stepped: " << endl;
    printGrid(game);
    return 0;
}