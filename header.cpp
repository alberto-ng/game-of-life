# include <iostream>
# include "header.h"


// set which way user want to start
void header::setDoor(){

    cout << "Enter 1 for file input, enter 2 for random assignment: " << endl;
    cin >> door;

    // error checking
    while (door != "1" && door != "2"){
        cout << "Invalid input.\n Enter 1 for file input, enter 2 for random assignment: " << endl;
        cin >> door;
    }
}

// get which way user want to start
string header::getDoor(){
    return door;
}

// set which mode user want to play
void header::setMode(){
    cout << "Enter 1 for classic mode, 2 for donut mode, 3 for mirror mode: " << endl;
    cin >> mode;

    // error checking
    while (mode != "1" && mode != "2" && mode != "3"){
        cout << "Invalid input.\n Enter 1 for classic mode, 2 for donut mode, 3 for mirror mode: " << endl;
        cin >> mode;
    }
}

// get which mode user want to play
string header::getMode(){
    return mode;
}

// set which way user want to output
void header::setOut(){
    cout << "Enter 1 for brief pause before next generation." << endl;
    cout << "Enter 2 for enter to next generation." << endl;
    cout << "Enter 3 for output to file. " << endl;
    cin >> out;

    // error checking
    while (out != "1" && out != "2" && out != "3"){
        cout << "Invalid input." << endl;
        cout << " Enter 1 for brief pause before next generation." << endl;
        cout << " Enter 2 for enter to next generation." << endl;
        cout << " Enter 3 for output to file. " << endl;
        cin >> out;
    }
}

// get which way user want to output
string header::getOut(){
    return out;
}

// set roll length
void header::setRow(){
    cout << "Enter an integer for length of row: " << endl;
    cin >> row;
}

// get roll length
int header::getRow(){
    return row;
}

// set column length
void header::setCol(){
    cout << "Enter an integer for length of column: " << endl;
    cin >> col;
}

// get column length
int header::getCol(){
    return col;
}

// set population density
void header::setDen(){
    cout << "Enter an decimal from 0-1 for density: " << endl;
    cin >> den;
}

// get population density
double header::getDen(){
    return den;
}

// get file name to input for the game
string header::getFileName(){
    cout << "Enter a file: " << endl;
    cin >> fileName;
    return fileName;
}
