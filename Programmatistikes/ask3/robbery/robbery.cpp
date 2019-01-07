#include <iostream>
#include <vector>

#define bSIZE 1<<15

/*---START OF DECLARATIONS--------------------------------------------------*/


char buffer[bSIZE];
long bpos = 0L, bsize = 0L;

typedef long int INT;

int read_long();
int read_long(FILE* fp);
long read_stdin();
long read_file(FILE* fp);

/*---END OF DECLARATIONS--------------------------------------------------*/

int main (int argc, char** argv) {

//    if the two lines below are uncommented script reads from file

//    if line below is uncommented script reads from stdin

    try {

    }
    catch (std::exception& e) {
        std::cerr << "Exception catched : " << e.what() << std::endl;
    }

    return 0;
}

//read_stdin uses read_long() to read from stdin
long read_stdin(){

    //call read_long() as many times as needed

    return -1;
}
int read_long() {
    int d = 0L, x = 0L;
    char c;
    bool b = false;
    while (1)  {
        if (bpos >= bsize) {
            bpos = 0;
            if (feof(stdin))
                return x;
            bsize = (long long) fread(buffer, 1, bSIZE, stdin);
        }
        c = buffer[bpos++];
        if (c == '-') b = true;
        if (c >= '0' && c <= '9') { x = x*10 + (c -'0'); d = 1; }
        else if (d == 1) return b ? (-1*x) : x;
    }
    return -1;
}

//read_file uses read_long(FILE* fp) to read from file
long read_file(FILE* fp){

    //call read_long() as many times as needed

    return -1;
}
int read_long(FILE* fp) {
    int d = 0L, x = 0L;
    char c;
    bool b = false;
    while (1)  {
        if (bpos >= bsize) {
            bpos = 0;
            if (feof(fp))
                return x;
            bsize = (long long) fread(buffer, 1, bSIZE, fp);
        }
        c = buffer[bpos++];
        if (c == '-') b = true;
        if (c >= '0' && c <= '9') { x = x*10 + (c -'0'); d = 1; }
        else if (d == 1) return b ? (-1*x) : x;
    }
    return -1;
}