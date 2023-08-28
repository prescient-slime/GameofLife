#include <random>
#include <GL/freeglut.h>
#include <GLUT/glut.h>

#define WIDTH 800
#define HEIGHT 600
#define SIZE 480000
#define WAIT 15000

bool initialized = false;
std::array<bool, SIZE> board;
void initGame(std::array<bool, SIZE> &grid){
  if (!initialized){
    auto gen = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine());
    for (int i = 0; i < SIZE; i++){
      grid[i] = gen();
    }
    initialized = true;
  } 
}

void restart(int key, int a, int b){
  if (key == 'r'){
    initialized = false;
    initGame(board);
  }
  if (key == 'q'){
    int win = glutGetWindow();
    glutDestroyWindow(win);
    exit(0);
  }
}


void draw_point(int x, int y){
    glColor3ub(61, 236, 242);
    glPointSize(1);
    glBegin(GL_POINTS);
        glVertex2f(x, y);
    glEnd();
}

void drawGame(std::array<bool, SIZE>& board){
    for (int i = 0; i < SIZE; i++){
        if (board[i]) {
            int x = i % static_cast<int>(WIDTH);
            int y = i / static_cast<int>(WIDTH);
            draw_point(x, y);
        }
    } 
    glutPostRedisplay();
}

int getNeighbors(std::array<bool, SIZE>& grid, int position){
    int n = 0;
    
    if (grid[(position - WIDTH) % static_cast<int>(grid.size())]) n++; // up
    if (grid[(position - (WIDTH - 1)) % static_cast<int>(grid.size())]) n++; // up right
    if (grid[(position + 1) % static_cast<int>(grid.size())]) n++; // right
    if (grid[(position + (WIDTH + 1)) % static_cast<int>(grid.size())]) n++; // down right
    if (grid[(position + WIDTH) % static_cast<int>(grid.size())]) n++; // down
    if (grid[(position + (WIDTH - 1)) % static_cast<int>(grid.size())]) n++; // down left
    if (grid[(position - 1) % static_cast<int>(grid.size())]) n++; // left
    if (grid[(position - (WIDTH + 1)) % static_cast<int>(grid.size())]) n++; // up left

    return n;
    
}


void stepGame(std::array<bool, SIZE>& grid){
    int neighbors = 0;
    int dead = 0;
    for (int i = 0; i < SIZE; i++){
        neighbors = getNeighbors(grid, i);
            if (grid[i] && (neighbors > 3 || neighbors < 2)){
                grid[i] = !grid[i];
            }
            else if (!grid[i] && neighbors == 3){
                grid[i] = !grid[i];
            }
        }
    }

void display(){
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
    glutSpecialFunc(restart);
    glutMainLoop();
    initGame(board);

    return 0;
}
