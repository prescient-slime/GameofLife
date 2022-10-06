#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <array>
using namespace std;

int* gridInit(int nrow, int mcol){
    int grid[nrow][mcol];
    memset(grid, 0, sizeof(grid));
    for (int i = 0; i < nrow; i++){
        for (int j = 0; j < mcol; j++){
            cout << grid[i][j] << ", ";
        }
        cout << endl;
    }
    return 0;
}

int main(){
    gridInit(10, 10);
    return 0;
}