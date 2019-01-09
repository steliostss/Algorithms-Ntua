#include <iostream>
#include <vector>

#define bSIZE 1<<15

/*---START OF DECLARATIONS--------------------------------------------------*/
class Node;
typedef long int INT;

int globalN, globalM;

char buffer[bSIZE];
long bpos = 0L, bsize = 0L;

int read_long();
int read_long(FILE* fp);
int read_stdin();
int read_file(FILE* fp);

/*---END OF DECLARATIONS--------------------------------------------------*/

int main (int argc, char** argv) {

    try {
//        if the two lines below are uncommented script reads from file
//        FILE* fp = fopen(argv[1], "r");
//        int k = read_file(fp);
//
//        if line below is uncommented script reads from stdin
//        int k = read_stdin();

    }
    catch (std::exception& e) {
        std::cerr << "Exception catched : " << e.what() << std::endl;
    }

    return 0;
}

//read_stdin uses read_long() to read from stdin
int read_stdin(){

    globalN = read_long();
    globalM = read_long();

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
            bsize = fread(buffer, 1, bSIZE, stdin);
        }
        c = buffer[bpos++];
        if (c == '-') b = true;
        if (c >= '0' && c <= '9') { x = x*10 + (c -'0'); d = 1; }
        else if (d == 1) return b ? (-1*x) : x;
    }
    return -1;
}

//read_file uses read_long(FILE* fp) to read from file
int read_file(FILE* fp){

    globalN = read_long(fp);
    globalM = read_long(fp);

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
            bsize = fread(buffer, 1, bSIZE, fp);
        }
        c = buffer[bpos++];
        if (c == '-') b = true;
        if (c >= '0' && c <= '9') { x = x*10 + (c -'0'); d = 1; }
        else if (d == 1) return b ? (-1*x) : x;
    }
    return -1;
}