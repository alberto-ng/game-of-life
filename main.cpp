# include <iostream>
# include <fstream>
# include <unistd.h>
# include "grid.h"
# include "header.h"


using namespace std;

// tried to shorten main for the last couple of days but it broke and i had to restore it from git hub with the earlier version
int main (int argc, char **argv) {

    // initiating/assigning
    int generation = 1;
    int first = 0;
    string door, mode, out, fileName;
    int row, column;
    float d;

    header h;

    // set user's actions
    h.setDoor();
    h.setMode();
    h.setOut();

    // get user's actions
    door = h.getDoor();
    mode = h.getMode();
    out = h.getOut();

    // file input
    if (door == "1") {
        ifstream inFile;

        // open file
        inFile.open(h.getFileName());
        if (inFile.fail()) {
            // while fail, kept prompting unil user quits or enter a valid file
            while (inFile.fail()) {
                cout << "Failed. Enter a valid file." << endl;
                inFile.open(h.getFileName());
            }
        }

        // first two lines are row and column
        inFile >> row;
        inFile >> column;

        // create a grid with size promted by file
        grid *grid1 = new grid(row, column);
        // recreate a grid like the grid in the file
        grid1 -> setFileGrid(inFile);

        // classic
        if (mode == "1") {
            // so program knows what checkN to use
            grid1 -> changeMode(1);

            // if user want a brief pause in between gen
            if (out == "1") {
                // print current grid
                grid1 -> getGrid();
                // delay 1 sec
                sleep(1);

                // keep printing next gen unless is empty or stable
                while (true) {
                    cout << "Generation: " << generation++ << endl;
                    grid1 -> getNextGen();

                    if (grid1 -> isStable() || grid1 -> isEmpty()) {
                        if (grid1 -> isEmpty()){
                            cout << "Empty." << endl;
                            if (cin.get() == '\n'){
                                break;
                            }
                        }
                        else {
                            cout << "Stable." << endl;
                            if (cin.get() == '\n'){
                                break;
                            }
                        }
                    }

                    grid1 -> resetNextGen();

                    // delay 1 second
                    sleep(1);

                }

            }

            // press enter for next gen
            else if (out == "2") {
                grid1 -> getGrid();
                cout << "Press enter for next generation." << endl;

                if (cin.get() == '\n'){
                    ++first;
                }

                if (first == 1) {
                    // while loop if user type enter print next gen
                    while (cin.get() == '\n') {
                        cout << "Generation: " << generation++ << endl;
                        grid1 -> getNextGen();

                        if (grid1 -> isStable() || grid1 -> isEmpty()){
                            if (grid1 -> isEmpty()){
                                cout << "Empty." << endl;
                                if (cin.get() == '\n'){
                                    break;
                                }
                            }
                            else {
                                cout << "Stable." << endl;
                                if (cin.get() == '\n'){
                                    break;
                                }
                            }
                        }

                        grid1 -> resetNextGen();

                        cout << "Press enter for next generation.";
                    }
                }
            }

            // output to file
            else{
                ofstream outFile;

                // open/create albertoNg.out
                outFile.open("albertoNg.out");

                // print to file
                grid1 -> getFileGrid(outFile);

                // keep printing next gen unless is empty or stable
                while (true) {

                    grid1 -> getFileNextGen(outFile);

                    if (grid1 -> isStable() || grid1 -> isEmpty()) {
                        break;
                    }

                    grid1 -> resetNextGen();

                }
                // close the out file
                outFile.close();
            }
        }
        // donut
        else if (mode == "2") {
            grid1 -> changeMode(2);

            // brief pause between generation
            if (out == "1") {
                grid1 -> getGrid();
                sleep(1);

                while (true) {
                    cout << "Generation: " << generation++ << endl;
                    grid1 -> getNextGen();

                    if (grid1 -> isStable() || grid1 -> isEmpty()) {
                        if (grid1 -> isEmpty()){
                            cout << "Empty." << endl;
                            if (cin.get() == '\n'){
                                break;
                            }
                        }
                        else {
                            cout << "Stable." << endl;
                            if (cin.get() == '\n'){
                                break;
                            }
                        }
                    }

                    grid1 -> resetNextGen();
                    sleep(1);

                }

            }

            // enter for next generation
            else if (out == "2") {
                grid1 -> getGrid();
                cout << "Press enter for next generation." << endl;
                if (cin.get() == '\n'){
                    ++first;
                }

                if (first == 1) {
                while (cin.get() == '\n') {
                        cout << "Generation: " << generation++ << endl;
                        grid1 -> getNextGen();

                        if (grid1 -> isStable() || grid1 -> isEmpty()){
                            if (grid1 -> isEmpty()){
                                cout << "Empty." << endl;
                                if (cin.get() == '\n'){
                                    break;
                                }
                            }
                            else {
                                cout << "Stable." << endl;
                                if (cin.get() == '\n'){
                                    break;
                                }
                            }
                        }

                        grid1 -> resetNextGen();

                        cout << "Press enter for next generation.";
                    }
                }
            }

            // print next gen to file
            else{
                ofstream outFile;
                outFile.open("albertoNg.out");

                grid1 -> getFileGrid(outFile);

                while (true) {

                    grid1 -> getFileNextGen(outFile);

                    if (grid1 -> isStable() || grid1 -> isEmpty()) {
                        break;
                    }

                    grid1 -> resetNextGen();

                }
                outFile.close();
            }
        }
        // mirror
        else {
            grid1 -> changeMode(3);
            // brief pause between gen
            if (out == "1") {
                grid1 -> getGrid();
                sleep(1);

                while (true) {
                    cout << "Generation: " << generation++ << endl;
                    grid1 -> getNextGen();

                    if (grid1 -> isStable() || grid1 -> isEmpty()) {
                        if (grid1 -> isEmpty()){
                            cout << "Empty." << endl;
                            if (cin.get() == '\n'){
                                break;
                            }
                        }
                        else {
                            cout << "Stable." << endl;
                            if (cin.get() == '\n'){
                                break;
                            }
                        }
                    }

                    grid1 -> resetNextGen();
                    sleep(1);

                }

            }
            // enter for next generation
            else if (out == "2") {
                grid1 -> getGrid();
                cout << "Press enter for next generation." << endl;
                if (cin.get() == '\n'){
                    ++first;
                }

                if (first == 1) {
                while (cin.get() == '\n') {
                        cout << "Generation: " << generation++ << endl;
                        grid1 -> getNextGen();

                        if (grid1 -> isStable() || grid1 -> isEmpty()){
                            if (grid1 -> isEmpty()){
                                cout << "Empty." << endl;
                                if (cin.get() == '\n'){
                                    break;
                                }
                            }
                            else {
                                cout << "Stable." << endl;
                                if (cin.get() == '\n'){
                                    break;
                                }
                            }
                        }

                        grid1 -> resetNextGen();

                        cout << "Press enter for next generation.";
                    }
                }
            }
            // output to file
            else{
                ofstream outFile;
                outFile.open("albertoNg.out");

                grid1 -> getFileGrid(outFile);

                while (true) {

                    grid1 -> getFileNextGen(outFile);

                    if (grid1 -> isStable() || grid1 -> isEmpty()) {
                        break;
                    }

                    grid1 -> resetNextGen();

                }
                outFile.close();
            }
        }

        // close the in file
        inFile.close();
        // delete the grid to clear garbage
        delete grid1;
    }

    // random assignment
    else {
        h.setRow();
        h.setCol();
        h.setDen();
        row = h.getRow();
        column = h.getCol();
        d = h.getDen();

        grid *grid1 = new grid(row, column);

        grid1 -> setGrid(d);
        // classic
        if (mode == "1") {
            grid1 -> changeMode(1);

            // brief pause between n=gen
            if (out == "1") {
                grid1 -> getGrid();
                sleep(1);

                while (true) {
                    cout << "Generation: " << generation++ << endl;
                    grid1 -> getNextGen();

                    if (grid1 -> isStable() || grid1 -> isEmpty()) {
                        if (grid1 -> isEmpty()){
                            cout << "Empty." << endl;
                            if (cin.get() == '\n'){
                                break;
                            }
                        }
                        else {
                            cout << "Stable." << endl;
                            if (cin.get() == '\n'){
                                break;
                            }
                        }
                    }

                    grid1 -> resetNextGen();
                    sleep(1);

                }
            }
            // enter for next gen
            else if (out == "2") {
                grid1 -> getGrid();

                cout << "Press enter for next generation." << endl;
                if (cin.get() == '\n') {
                    ++first;
                }


                if (first == 1) {
                    while (cin.get() == '\n') {
                        cout << "Generation: " << generation++ << endl;
                        grid1 -> getNextGen();

                        if (grid1 -> isStable() || grid1 -> isEmpty()) {
                            if (grid1 -> isEmpty()){
                                cout << "Empty." << endl;
                                if (cin.get() == '\n'){
                                    break;
                                }
                            }
                            else {
                                cout << "Stable." << endl;
                                if (cin.get() == '\n'){
                                    break;
                                }
                            }
                        }

                        grid1 -> resetNextGen();

                        cout << "Press enter for next generation.";
                    }
                }
            }
            // output to file
            else {
                ofstream outFile;
                outFile.open("albertoNg.out");

                grid1 -> getFileGrid(outFile);
                while (true) {
                    grid1 -> getFileNextGen(outFile);

                    if (grid1 -> isStable() || grid1 -> isEmpty()) {
                        break;
                    }

                    grid1 -> resetNextGen();

                }
                outFile.close();
            }
        }
        // donut
        else if (mode == "2") {
            grid1 -> changeMode(2);

            // brief pause between gen
            if (out == "1") {
                grid1 -> getGrid();
                sleep(1);

                while (true) {
                    cout << "Generation: " << generation++ << endl;
                    grid1 -> getNextGen();

                    if (grid1 -> isStable() || grid1 -> isEmpty()) {
                        if (grid1 -> isEmpty()){
                            cout << "Empty." << endl;
                            if (cin.get() == '\n'){
                                break;
                            }
                        }
                        else {
                            cout << "Stable." << endl;
                            if (cin.get() == '\n'){
                                break;
                            }
                        }
                    }

                    grid1 -> resetNextGen();
                    sleep(1);

                }

            }
            // enter for next gen
            else if (out == "2") {
                grid1 -> getGrid();
                cout << "Press enter for next generation." << endl;
                if (cin.get() == '\n'){
                    ++first;
                }

                if (first == 1) {
                while (cin.get() == '\n') {
                        cout << "Generation: " << generation++ << endl;
                        grid1 -> getNextGen();

                        if (grid1 -> isStable() || grid1 -> isEmpty()){
                            if (grid1 -> isEmpty()){
                                cout << "Empty." << endl;
                                if (cin.get() == '\n'){
                                    break;
                                }
                            }
                            else {
                                cout << "Stable." << endl;
                                if (cin.get() == '\n'){
                                    break;
                                }
                            }
                        }

                        grid1 -> resetNextGen();

                        cout << "Press enter for next generation.";
                    }
                }
            }
            // output to file
            else{
                ofstream outFile;
                outFile.open("albertoNg.out");

                grid1 -> getFileGrid(outFile);

                while (true) {

                    grid1 -> getFileNextGen(outFile);

                    if (grid1 -> isStable() || grid1 -> isEmpty()) {
                        if (grid1 -> isEmpty()){
                            cout << "Empty." << endl;
                            if (cin.get() == '\n'){
                                break;
                            }
                        }
                        else {
                            cout << "Stable." << endl;
                            if (cin.get() == '\n'){
                                break;
                            }
                        }
                    }

                    grid1 -> resetNextGen();

                }
                outFile.close();
            }
        }
        // mirror
        else {
            grid1 -> changeMode(3);
            // brief pause between generations
            if (out == "1") {
                grid1 -> getGrid();
                sleep(1);

                while (true) {
                    cout << "Generation: " << generation++ << endl;
                    grid1 -> getNextGen();

                    if (grid1 -> isStable() || grid1 -> isEmpty()) {
                        if (grid1 -> isEmpty()){
                            cout << "Empty." << endl;
                            if (cin.get() == '\n'){
                                break;
                            }
                        }
                        else {
                            cout << "Stable." << endl;
                            if (cin.get() == '\n'){
                                break;
                            }
                        }
                    }

                    grid1 -> resetNextGen();
                    sleep(1);

                }

            }
            // enter to print next generation
            else if (out == "2") {
                grid1 -> getGrid();
                cout << "Press enter for next generation." << endl;
                if (cin.get() == '\n'){
                    ++first;
                }

                if (first == 1) {
                while (cin.get() == '\n') {
                        cout << "Generation: " << generation++ << endl;
                        grid1 -> getNextGen();

                        if (grid1 -> isStable() || grid1 -> isEmpty()){
                            if (grid1 -> isEmpty()){
                                cout << "Empty." << endl;
                                if (cin.get() == '\n'){
                                    break;
                                }
                            }
                            else {
                                cout << "Stable." << endl;
                                if (cin.get() == '\n'){
                                    break;
                                }
                            }
                        }

                        grid1 -> resetNextGen();

                        cout << "Press enter for next generation.";
                    }
                }
            }
            // print generations to file
            else{
                ofstream outFile;
                outFile.open("albertoNg.out");

                grid1 -> getFileGrid(outFile);

                while (true) {

                    grid1 -> getFileNextGen(outFile);

                    if (grid1 -> isStable() || grid1 -> isEmpty()) {
                        if (grid1 -> isEmpty()){
                            cout << "Empty." << endl;
                            if (cin.get() == '\n'){
                                break;
                            }
                        }
                        else {
                            cout << "Stable." << endl;
                            if (cin.get() == '\n'){
                                break;
                            }
                        }
                    }

                    grid1 -> resetNextGen();

                }
                outFile.close();
            }
        }
        // delete the grid to clear garbage
        delete grid1;
    }

    return 0;
}
