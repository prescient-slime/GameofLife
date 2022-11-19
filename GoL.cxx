#include <iostream>
#include <random>
#include <time.h>
#include <GL/freeglut.h>
#include <GLUT/glut.h>


#define WIDTH 1366
#define HEIGHT 768
#define WAIT 15000

bool initialized = false;
bool board [HEIGHT][WIDTH] = {false};

void initGame(bool(&grid)[HEIGHT][WIDTH]){
    if (!initialized){
        srand( time(NULL) ); //Randomize seed initialization
        for (int i = 0; i < HEIGHT; i++){
            for (int j = 0; j < WIDTH; j++){
                int randNum = rand() & 1; // Generate a random number between 0 and 1
                grid[i][j] = (bool)randNum;
            }
        }
        initialized = true;
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

int getNeighbors(bool(grid)[HEIGHT][WIDTH], int j, int i){
    int n = 0;
    
    if (grid[(i - 1) % HEIGHT][(j - 1) % WIDTH]) n++;
    if (grid[(i - 1) % HEIGHT][(j)]) n++;
    if (grid[(i - 1) % HEIGHT][(j + 1) % WIDTH]) n++;
    if (grid[(i)][(j - 1) % WIDTH]) n++;
    if (grid[(i)][(j + 1) % WIDTH]) n++;
    if (grid[(i + 1) % HEIGHT][(j - 1) % WIDTH]) n++;
    if (grid[(i + 1) % HEIGHT][(j)]) n++;
    if (grid[(i + 1) % HEIGHT][(j + 1) % WIDTH]) n++;

    return n;
    
}


void stepGame(bool(&grid)[HEIGHT][WIDTH]){
    int neighbors = 0;
    int dead = 0;
    bool swap [HEIGHT][WIDTH] = {false};
    for (int i = 0; i < HEIGHT; i++){
        for (int j = 0; j < WIDTH; j++){
            neighbors = getNeighbors(grid, j, i);
            if (grid[i][j] == true){
                if (neighbors > 3 || neighbors < 2){
                    swap[i][j] = false;
                }
                else{
                    swap[i][j] = grid[i][j];
                }
                dead++;
            }
            else if (grid[i][j] == false){
                if (neighbors == 3){
                    swap[i][j] = true;
                }
            }
            
        }
    }
    
    if (dead <= 0){
        initialized = false;
        initGame(swap);
    }
    std::swap(swap, grid);
    
}

void display(){
    //printGame(board);
    glClear(GL_COLOR_BUFFER_BIT);
    drawGame(board);
    stepGame(board);
    
    glutSwapBuffers();
}

void init(){
    
    gluOrtho2D(0, WIDTH, HEIGHT, 0);
    initGame(board);
}


int main(int argc, char* argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Conway's Game of Life");
    init();

    glutDisplayFunc(display);

    glutMainLoop();
    initGame(board);

    return 0;
}