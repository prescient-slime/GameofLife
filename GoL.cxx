#include <array>
#include <iostream>
//#include <GLUT/glut.h>
#include <GL/freeglut.h>
#include <random>

using namespace std;

const size_t HEIGHT = 600;
const size_t WIDTH = 800;
const float CELL_COLOR[3] = {1.0, 1.0, 1.0};

void init(){
    gluOrtho2D(0, WIDTH, HEIGHT, 0);
}

array<array<bool, HEIGHT>, WIDTH > boardInit(array<array<bool, HEIGHT>, WIDTH > &grid){
    for (auto &row : grid){
        generate(row.begin(), row.end(), []() { return rand() % 10 == 0 ? 1: 0; });
    }
}

int countNeighbors(array<array<bool, HEIGHT>, WIDTH> grid, int x, int y){
    int neighbors = 0;
    neighbors += (int)(
        grid[(y - 1)%HEIGHT][(x - 1)%WIDTH] +
        grid[(y - 1)%HEIGHT][(x)%WIDTH] +
        grid[(y - 1)%HEIGHT][(x + 1)%WIDTH] +
        grid[(y)][(x - 1)] +
        grid[(y)][(x + 1)] +
        grid[(y + 1)%HEIGHT][(x - 1)%WIDTH] +
        grid[(y + 1)%HEIGHT][(x)%WIDTH] +
        grid[(y + 1)%HEIGHT][(x + 1)%WIDTH]
    );
    return neighbors;
}
void stepGame(array<array<bool, HEIGHT>, WIDTH> &grid){
    int neighbors = 0;
    array<array<bool, HEIGHT>, WIDTH> swapGrid = {false};
    for (int y = 0; y < HEIGHT; y++){
        for (int x = 0; x < WIDTH; x++){
            neighbors = countNeighbors(grid, x, y);
            if (grid[y][x]){
                if (neighbors > 3 || neighbors < 2){
                    swapGrid[y][x] = false;
                }
            }
            else if (!grid[y][x]){
                if (neighbors == 3){
                    swapGrid[y][x] = true;
                }
            }
        }
    }
    swap(grid, swapGrid);
}

void drawGame(array<array<bool, HEIGHT>,WIDTH> grid, const float color[3]){
    glPointSize(1);
    glColor3fv(color);
    glBegin(GL_POINTS);
        for (int y = 0; y < HEIGHT; y++){
            for (int x = 0; x < WIDTH; x++){
                if (grid[y][x]){
                    glVertex2d(y, x);
                }
            }
        }
    glEnd();
    glutPostRedisplay();
}

array<array<bool, HEIGHT>,WIDTH> game = boardInit(game);

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    stepGame(game);
    drawGame(game, CELL_COLOR);
    glFlush();
    
    glFinish();
}

int main(int argc, char* argv []){
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Conway's Game of Life");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}