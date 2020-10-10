# include <iostream>
# include <cmath>
# include <fstream>
# include "grid.h"


// default constructor
grid::grid(){
    currGrid = new char *[5];
    nextGrid = new char *[5];
    for (int i = 0; i < 5; ++i){
        currGrid[i] = new char[5];
        nextGrid[i] = new char[5];
    }

    for (int m = 0; m < 5; ++m){
        for (int n = 0; n < 5; ++n){
            currGrid[m][n] = '-';
            nextGrid[m][n] = '-';
        }
    }
    row = 5;
    column = 5;
    currRow = 0;
    currCol = 0;
    trueCounter = 0;
    generation = 1;
    mode = 0;
}

// overloaded constructor
grid::grid(int num1, int num2){
    row = num1;
    column = num2;
    currGrid = new char *[row];
    nextGrid = new char *[row];
    for (int i = 0; i < row; ++i){
        currGrid[i] = new char[column];
        nextGrid[i] = new char[column];
    }

    for (int m = 0; m < row; ++m){
        for (int n = 0; n < column; ++n){
            currGrid[m][n] = '-';
            nextGrid[m][n] = '-';
        }
    }
    currRow = 0;
    currCol = 0;
    trueCounter = 0;
    generation = 1;
    mode = 0;
}

// destructor
grid::~grid(){
    delete currGrid;
    delete nextGrid;
}

// set grid with argument of population density of 0-1
void grid::setGrid(double d){
    int Xcounter = 0;
    double arraySize = (double)row * column;
    double Xdecimal = arraySize * d;

    // if else statement to round up or down acordingly
    if (remainder(Xdecimal, 1) >= 0.5){
        Xdecimal += (1 - remainder(Xdecimal, 1));
    }
    else {
        Xdecimal -= remainder(Xdecimal, 1);
    }

    Xcounter = (int)Xdecimal;

    // while loop to set grid with appropriate size and population density
    while (Xcounter != 0){
        for (int i = 0; i < row; ++i){
            if (Xcounter == 0){
                break;
            }
            for (int j = 0; j < column; ++j){
                if (Xcounter == 0){
                    break;
                }
                double random = ((double)rand()/RAND_MAX);
                if (random < d){
                    if (currGrid[i][j] == '-'){
                        currGrid[i][j] = 'X';
                        --Xcounter;
                    }
                }
            }
        }
    }
}

// set grid with information given in a text file
void grid::setFileGrid(ifstream& x){
    string line = "";
    x >> line;

    // for loop to recreate the grid in the file
    for (int i = 0; i < row; ++i){
        for (int j = 0; j < column; ++j){
            if (line.at(j) == '-'){
                currGrid[i][j] = '-';
            }
            else if (line.at(j) == 'X'){
                currGrid[i][j] = 'X';
            }
        }
        x >> line;
    }
}

// print grid to consel
void grid::getGrid(){
    cout << "Current generation: " << endl;
    for (int i = 0; i < row; ++i){
        currRow = i;
        for (int j = 0; j < column; ++j){
            currCol = j;
            cout << currGrid[i][j];
        }
        cout << endl;
    }
}

// print grid to file
void grid::getFileGrid(ofstream& x){

    x << "Current generation: " << endl;
    for (int i = 0; i < row; ++i){
        currRow = i;
        for (int j = 0; j < column; ++j){
            currCol = j;
            x << currGrid[i][j];
        }
        x << endl;
    }
}

// function that changes the alive status state according to numbers of neighbor cells
void grid::changeStat(){
    int Ntotal = 0;

    // classic mode
    if (mode == 1){
        Ntotal = checkNclassic();
    }
    // donut mode
    else if (mode == 2){
        Ntotal = checkNdonut();
    }
    // mirror mode
    else if (mode == 3){
        Ntotal = checkNmirror();
    }

    // if else if else statement to change state according to the rule
    if (Ntotal <= 1){
        nextGrid[currRow][currCol] = '-';
    }
    else if (Ntotal == 2){
        if (currGrid[currRow][currCol] == 'X'){
            nextGrid[currRow][currCol] = 'X';
        }
        else {
            nextGrid[currRow][currCol] = '-';
        }
    }
    else if (Ntotal == 3){
        nextGrid[currRow][currCol] = 'X';
    }
    else{
        nextGrid[currRow][currCol] = '-';
    }
}

// print next generation to consel
void grid::getNextGen(){

    // for loop that calls on changeStat function and print updated grid
    for (int i = 0; i < row; ++i){
        currRow = i;
        for (int j = 0; j < column; ++j){
            currCol = j;
            changeStat();
            cout << nextGrid[i][j];
        }
        cout << endl;
    }
}

// print next gen to file
void grid::getFileNextGen(ofstream& x){
    x << "Generation: " << generation++ << endl;

    // for loop that calls on changeStat function and print updated grid
    for (int i = 0; i < row; ++i){
        currRow = i;
        for (int j = 0; j < column; ++j){
            currCol = j;
            changeStat();
            x << nextGrid[i][j];
        }
        x << endl;
    }
}

// store next generation as current Generation
// clear out newGrid for future generation
void grid::resetNextGen(){
    currGrid = nextGrid;
    nextGrid = new char *[row];
    for (int i = 0; i < row; ++i){
        nextGrid[i] = new char[column];
    }

    for (int m = 0; m < row; ++m){
        for (int n = 0; n < column; ++n){
            nextGrid[m][n] = '-';
        }
    }
}

// to check number of neighbors for classic mode
int grid::checkNclassic(){
    int Ntotal = 0;

    if (currRow == 0 || currRow == (row - 1)){
        // if we are on the top row
        if (currRow == 0){
            // if we are on first column
            if (currCol == 0){
                if (currGrid[currRow][currCol + 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][currCol + 1] == 'X'){
                    ++Ntotal;
                }
            }
            // if we are on last column
            else if (currCol == (column - 1)){
                if (currGrid[currRow][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][currCol] == 'X'){
                    ++Ntotal;
                }
            }
            // if we are on the top row in between two corners
            else {
                if (currGrid[currRow][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow][currCol + 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][currCol + 1] == 'X'){
                    ++Ntotal;
                }
            }
        }

        // if we are on bottom row
        else if (currRow == (row - 1)){
            // if we are first column
            if (currCol == 0){
                if (currGrid[currRow][currCol + 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][currCol + 1] == 'X'){
                    ++Ntotal;
                }
            }
            // if we are on last column
            else if (currCol == (column - 1)){
                if (currGrid[currRow][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][currCol] == 'X'){
                    ++Ntotal;
                }
            }
            // if we are in between of the two bottom corner
            else {
                if (currGrid[currRow][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow][currCol + 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][currCol + 1] == 'X'){
                    ++Ntotal;
                }
            }
        }

    }

    else if (currCol == 0 || currCol == (column - 1)){
        // if we are on the first column
        if (currCol == 0){
            if (currGrid[currRow][currCol + 1] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow - 1][currCol] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow - 1][currCol + 1] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow + 1][currCol] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow + 1][currCol + 1] == 'X'){
                ++Ntotal;
            }
        }
        // if we are on last column
        else if (currCol == (column - 1)){
            if (currGrid[currRow - 1][currCol] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow - 1][currCol - 1] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow][currCol - 1] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow + 1][currCol - 1] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow + 1][currCol] == 'X'){
                ++Ntotal;
            }
        }
    }

    // if we are not on the border
    else {
        if (currGrid[currRow][currCol - 1] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow][currCol + 1] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow - 1][currCol - 1] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow - 1][currCol] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow - 1][currCol + 1] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow + 1][currCol - 1] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow + 1][currCol] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow + 1][currCol + 1] == 'X'){
            ++Ntotal;
        }
    }
    return Ntotal;
}

// to check number of neighbors for donut mode
int grid::checkNdonut(){
    int Ntotal = 0;

    if (currRow == 0 || currRow == (row - 1)){
        if (currRow == 0){
            if (currCol == 0){
                if (currGrid[row - 1][column - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[row - 1][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[row - 1][currCol + 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow][currCol + 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][currCol + 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][column - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow][column - 1] == 'X'){
                    ++Ntotal;
                }
            }
            else if (currCol == (column - 1)){
                if (currGrid[currRow][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][column - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow][0] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][0] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[row - 1][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[row - 1][0] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[row - 1][currCol - 1] == 'X'){
                    ++Ntotal;
                }
            }
            else {
                if (currGrid[row - 1][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[row - 1][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[row - 1][currCol + 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow][currCol + 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][currCol + 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow][currCol - 1] == 'X'){
                    ++Ntotal;
                }
            }
        }

        else if (currRow == (row - 1)){
            if (currCol == 0){
                if (currGrid[currRow - 1][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][currCol + 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow][currCol + 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[0][currCol + 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[0][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[0][column - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow][column - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][column - 1] == 'X'){
                    ++Ntotal;
                }
            }
            else if (currCol == (column - 1)){
                if (currGrid[currRow][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][0] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow][0] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[0][0] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[0][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[0][currCol - 1] == 'X'){
                    ++Ntotal;
                }
            }
            else {
                if (currGrid[currRow][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][currCol + 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow][currCol + 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[0][currCol + 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[0][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[0][currCol - 1] == 'X'){
                    ++Ntotal;
                }
            }
        }

    }

    else if (currCol == 0 || currCol == (column - 1)){
        if (currCol == 0){
            if (currGrid[currRow - 1][currCol] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow - 1][currCol + 1] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow][currCol + 1] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow + 1][currCol + 1] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow + 1][currCol] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow + 1][column - 1] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow][column - 1] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow - 1][currCol - 1] == 'X'){
                ++Ntotal;
            }
        }

        else if (currCol == (column - 1)){
            if (currGrid[currRow][currCol - 1] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow - 1][currCol - 1] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow - 1][currCol] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow - 1][0] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow][0] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow + 1][0] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow + 1][currCol] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow + 1][currCol - 1] == 'X'){
                ++Ntotal;
            }
        }
    }

    else {
        if (currGrid[currRow][currCol - 1] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow][currCol + 1] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow - 1][currCol - 1] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow - 1][currCol] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow - 1][currCol + 1] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow + 1][currCol - 1] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow + 1][currCol] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow + 1][currCol + 1] == 'X'){
            ++Ntotal;
        }
    }
    return Ntotal;
}

// to check number of neighbors for mirror mode
int grid::checkNmirror(){
    int Ntotal = 0;

    if (currRow == 0 || currRow == (row - 1)){
        if (currRow == 0){
            if (currCol == 0){
                if (currGrid[currRow][currCol] == 'X'){
                    Ntotal += 3;
                }
                if (currGrid[currRow][currCol + 1] == 'X'){
                    Ntotal += 2;
                }
                if (currGrid[currRow + 1][currCol] == 'X'){
                    Ntotal += 2;
                }
                if (currGrid[currRow + 1][currCol + 1] == 'X'){
                    ++Ntotal;
                }
            }
            else if (currCol == (column - 1)){
                if (currGrid[currRow][currCol] == 'X'){
                    Ntotal += 3;
                }
                if (currGrid[currRow][currCol - 1] == 'X'){
                    Ntotal += 2;
                }
                if (currGrid[currRow + 1][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][currCol] == 'X'){
                    Ntotal += 2;
                }
            }
            else {
                if (currGrid[currRow][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow][currCol - 1] == 'X'){
                    Ntotal += 2;
                }
                if (currGrid[currRow][currCol + 1] == 'X'){
                    Ntotal += 2;
                }
                if (currGrid[currRow + 1][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow + 1][currCol + 1] == 'X'){
                    ++Ntotal;
                }
            }
        }

        else if (currRow == (row - 1)){
            if (currCol == 0){
                if (currGrid[currRow][currCol] == 'X'){
                    Ntotal += 3;
                }
                if (currGrid[currRow][currCol + 1] == 'X'){
                    Ntotal += 2;
                }
                if (currGrid[currRow - 1][currCol + 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][currCol] == 'X'){
                    Ntotal += 2;
                }
            }
            else if (currCol == (column - 1)){
                if (currGrid[currRow][currCol] == 'X'){
                    Ntotal += 3;
                }
                if (currGrid[currRow][currCol - 1] == 'X'){
                    Ntotal += 2;
                }
                if (currGrid[currRow - 1][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][currCol] == 'X'){
                    Ntotal += 2;
                }
            }
            else {
                if (currGrid[currRow][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow][currCol - 1] == 'X'){
                    Ntotal += 2;
                }
                if (currGrid[currRow][currCol + 1] == 'X'){
                    Ntotal += 2;
                }
                if (currGrid[currRow - 1][currCol - 1] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][currCol] == 'X'){
                    ++Ntotal;
                }
                if (currGrid[currRow - 1][currCol + 1] == 'X'){
                    ++Ntotal;
                }
            }
        }

    }

    else if (currCol == 0 || currCol == (column - 1)){
        if (currCol == 0){
            if (currGrid[currRow][currCol] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow - 1][currCol] == 'X'){
                Ntotal += 2;
            }
            if (currGrid[currRow - 1][currCol + 1] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow][currCol + 1] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow + 1][currCol + 1] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow + 1][currCol] == 'X'){
                Ntotal += 2;
            }
        }

        else if (currCol == (column - 1)){
            if (currGrid[currRow][currCol] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow - 1][currCol] == 'X'){
                Ntotal += 2;
            }
            if (currGrid[currRow - 1][currCol - 1] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow][currCol - 1] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow + 1][currCol - 1] == 'X'){
                ++Ntotal;
            }
            if (currGrid[currRow + 1][currCol] == 'X'){
                Ntotal += 2;
            }
        }
    }

    else {
        if (currGrid[currRow][currCol - 1] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow][currCol + 1] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow - 1][currCol - 1] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow - 1][currCol] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow - 1][currCol + 1] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow + 1][currCol - 1] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow + 1][currCol] == 'X'){
            ++Ntotal;
        }
        if (currGrid[currRow + 1][currCol + 1] == 'X'){
            ++Ntotal;
        }
    }
    return Ntotal;
}

// to check if generations are stable state
bool grid::isStable(){
    // nested for loop to check if next gen is the same as current gen
    for (int m = 0; m < row; ++m){
        for (int n = 0; n < column; ++n){
            // if it is not the same, exit
            if (nextGrid[m][n] != currGrid[m][n]){
                return false;
            }
        }
    }

    // if it is the same then incriment counter
    ++trueCounter;

    // if counter reaches 3, resets counter and reuturn is stable
    if (trueCounter == 3){
        trueCounter = 0;

        return true;
    }
    return false;
}

// to check if grid is empty
bool grid::isEmpty(){
    for (int m = 0; m < row; ++m){
        for (int n = 0; n < column; ++n){
            if (nextGrid[m][n] == 'X'){
                return false;
            }
        }
    }

    return true;
}

// to change game mode
void grid::changeMode(int m){

    mode = m;
}
