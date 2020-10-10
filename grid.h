# include <iostream>
using namespace std;

class grid{
    public:
        grid(); // default constructor
        grid(int rows, int column); // overloaded constructor
        ~grid(); // destructor

        // functions needed
        void setGrid(double d);
        void setFileGrid(ifstream& x);
        void getGrid();
        void getFileGrid(ofstream& x);
        void changeStat();
        void getNextGen();
        void getFileNextGen(ofstream& x);
        void resetNextGen();
        void changeMode(int m);
        int checkNclassic();
        int checkNdonut();
        int checkNmirror();
        bool isStable();
        bool isEmpty();

        // member variables
        char **currGrid, **nextGrid;
        int row, column, currRow, currCol;
        int trueCounter, generation, mode;
};
