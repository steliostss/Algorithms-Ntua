#include <iostream>
#include <vector>

#define betaSIZE 1<<15

class Node;
typedef long long int INT;
typedef std::vector<INT>::iterator ITER;
typedef std::vector<Node> VEC;
typedef std::vector<VEC> D2VEC;

class Node {
    private:
        int value_;
        int start_;
        bool end_;
    public:
        Node(int value) : value_(value), start_(-1), end_(false) {}
        ~Node() = default;

        int get_value() { return value_; }
        void set_value(int value) { value_ = value; }
        int get_start() { return start_; }
        void set_start(int start) { start_ = start; }
        bool get_end() { return end_; }
        void set_end(bool end) { end_ = end; }
};

int N, M, K, X;

char buffer[betaSIZE];
long bpos = 0L, bsize = 0L;


int read_long();
int read_long(FILE* fp);
D2VEC read_stdin();
D2VEC read_file(FILE* fp);

int main (int argc, char** argv){

    FILE* fp = fopen(argv[1], "r");
    D2VEC plot = read_file(fp);
//    D2VEC plot = read_stdin();

    return 0;
}

D2VEC read_stdin(){
    N = read_long();
    M = read_long();
    K = read_long();
    X = read_long();

    D2VEC plot(N, VEC(M, 0));

    for(int i = 0; i < K; i++) {
        int st = read_long();
        int en = read_long();
        int x = st / M;
        int y = st % M;
        plot[x][y].set_start(x);
        x = en / M;
        y = en % M;
        plot[x][y].set_end(true);
    }

    return plot;
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
            bsize = (long long) fread(buffer, 1, betaSIZE, stdin);
        }
        c = buffer[bpos++];
        if (c == '-') b = true;
        if (c >= '0' && c <= '9') { x = x*10 + (c -'0'); d = 1; }
        else if (d == 1) return b ? (-1*x) : x;
    }
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
            bsize = (long long) fread(buffer, 1, betaSIZE, fp);
        }
        c = buffer[bpos++];
        if (c == '-') b = true;
        if (c >= '0' && c <= '9') { x = x*10 + (c -'0'); d = 1; }
        else if (d == 1) return b ? (-1*x) : x;
    }
    return -1;
}

D2VEC read_file(FILE* fp){
    N = read_long(fp);
    M = read_long(fp);
    K = read_long(fp);
    X = read_long(fp);

    D2VEC plot(N, VEC(M, 0));

    for(int i = 0; i < K; ++i) {
        int st = read_long(fp);
        int en = read_long(fp);
        int x = st / M;
        int y = st % M;
        plot[x][y].set_start(x);
        x = en / M;
        y = en % M;
        plot[x][y].set_end(true);
    }

    return plot;
}
