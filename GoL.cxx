#include <iostream>
#include <random>
#include <time.h>
#include <GL/freeglut.h>
#include <GLUT/glut.h>


#define WIDTH 800
#define HEIGHT 600

using namespace std;

bool board [HEIGHT][WIDTH] = {false};

void printGame(bool(grid)[HEIGHT][WIDTH]){
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            cout << grid[i][j];
        }
        cout << endl;
    }
}

void initGame(bool(&grid)[HEIGHT][WIDTH]){
    srand( time(NULL) ); //Randomize seed initialization
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            int randNum = rand() % 2; // Generate a random number between 0 and 1
            grid[i][j] = (bool)randNum;
        }
    }
}



void draw_point(int x, int y, int size){
    glColor3f(1, 1, 1);
    glPointSize(size);
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();
}

void drawGame(bool(grid)[HEIGHT][WIDTH]){
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            if (grid[i][j]){
                //draw_point(j, i, 1);
                glColor3f(1, 1, 1);
                glBegin(GL_POINTS);
                    glVertex2i(j, i);
                glEnd();
            }
        }
    }
    glutPostRedisplay();
}


void stepGame(bool(&grid)[HEIGHT][WIDTH]){
    int neighbors = 0;
    int dead = 0;
    bool swap [HEIGHT][WIDTH] = {false};
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            neighbors = int(
                        grid[(i - 1) % HEIGHT][(j - 1) % WIDTH] +
                        grid[(i - 1) % HEIGHT][(j)] +
                        grid[(i - 1) % HEIGHT][(j + 1) % WIDTH] +
                        grid[(i)][(j - 1) % WIDTH] +
                        grid[(i)][(j + 1) % WIDTH] +
                        grid[(i + 1) % HEIGHT][(j - 1) % WIDTH] +
                        grid[(i + 1) % HEIGHT][(j)] + 
                        grid[(i + 1) % HEIGHT][(j + 1) % WIDTH]
            );
            if (grid[i][j]){
                if (neighbors > 3 || neighbors < 2){
                    swap[i][j] = false;
                }
                dead++;
            }
            if (!grid[i][j]){
                if (neighbors == 3){
                    swap[i][j] = true;
                }
            }
        }
    }
    /*for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            grid[i][j] = swap[i][j];
        }
    }*/
    std::swap(swap, grid);
    if (dead > 0){
        initGame(grid);
    }
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    drawGame(board);
    stepGame(board);
    
    glFlush();
    //glFinish();
}

void init(){
    gluOrtho2D(0, WIDTH, 0, HEIGHT);
}

int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Conway's Game of Life");
    init();

    glutDisplayFunc(display);



    glutMainLoop();
    
    
    return 0;
}