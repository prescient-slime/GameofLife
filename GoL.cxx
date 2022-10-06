#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <array>
#include <vector>
using namespace std;

vector<vector<int> > gridInit(int nrow, int mcol){
    vector<vector<int> > grid(nrow, vector<int>(mcol, 0));
    //fill(grid.begin(), grid.end(), 0);
    for (int i = 0; i < nrow; i++){
        for (int j = 0; j < mcol; j++){
            cout << grid[i][j] << ", ";
        }
        cout << endl;
    }
    return grid;
}

int main(){
    gridInit(10, 10);
    return 0;
}