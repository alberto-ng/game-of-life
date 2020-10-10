# include <iostream>
using namespace std;

class header{
    public:
        // functions
        void setDoor();
        void setMode();
        void setOut();
        void setRow();
        void setCol();
        void setDen();
        string getOut();
        string getMode();
        string getDoor();
        string getFileName();
        int getRow();
        int getCol();
        double getDen();


        // member variables
        string door, mode, out, fileName;
        int row, col;
        double den;
};
