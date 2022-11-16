#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <array>
#include <vector>
using namespace std;

/*this function initializes the grid as a multidimensional
vector, and then returns it. The goal will be to initialize,
populate, and then compute.*/

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

void printGrid(vector<vector<int> > grid){
    for (int i = 0; i < grid.size(); i++){
        for (int j = 0; j < grid[i].size(); j++){
            cout << grid[i][j] << ", ";
        }
        cout << endl;
    }
}

void runGame(vector<vector<int> > grid){
    
}

int main(){
    vector<vector<int> > grid = gridInit(10, 10);
    printGrid(grid);
    return 0;
}