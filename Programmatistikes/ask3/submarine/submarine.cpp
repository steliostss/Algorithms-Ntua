#include <iostream>
#include <vector>

#define bSIZE 1<<15

class Node;
typedef long long int INT;
typedef std::vector<Node> D1VEC; //1Dimension Vector
typedef std::vector<D1VEC> D2VEC; //2Dimension Vector
typedef std::vector<D2VEC> D3VEC; //3Dimension Vector of Nodes

class Node {

    private:
        INT value_;
        int y_orig_;
        int valid_k_;
        int x_orig_;
        bool end_;
        bool start_;
//        int x_dest_;  //Dest in not needed. Could be used though.
//        int y_dest_;

    public:
        Node() :
                value_(0),
                end_(false),
                x_orig_(-1),
                y_orig_(-1),
                valid_k_(0)
//                start_(false),
//                x_dest_(-1),
//                y_dest_(-1),
                {}
        ~Node() = default;

        INT get_value() { return value_; }
        void set_value(INT value) { value_ = value; }

        bool get_end() { return end_; }
        void set_end(bool end) { end_ = end; }

        int get_x_orig() { return x_orig_; }
        void set_x_orig(int x_point) { x_orig_ = x_point; }

        int get_y_orig() { return y_orig_; }
        void set_y_orig(int y_point) { y_orig_ = y_point; }

        int get_valid_k() { return valid_k_; }
        void set_valid_k(int valid_k) { valid_k_ = valid_k; }

        bool get_start() { return start_; }
        void set_start(bool start) { start_ = start; }

//        int get_x_dest() { return x_dest_; }
//        void set_x_dest(int x_point) { x_dest_ = x_point; }
//
//        int get_y_dest() { return y_dest_; }
//        void set_y_dest(int y_point) { y_dest_ = y_point; }

};

int N, M, K, X;

char buffer[bSIZE];
long bpos = 0L, bsize = 0L;

int read_long();
int read_long(FILE* fp);
D3VEC read_stdin();
D3VEC read_file(FILE* fp);
INT number_of_paths(D3VEC& plot);
void initialize_node(D3VEC& plot, bool column, int pos);
void add_right_and_down_nodes(D3VEC& plot, int i, int j);
void add_crossing(D3VEC& plot, int i, int j);
INT sum_all_levels(D3VEC& plot);

int main (int argc, char** argv){

//    if line below is uncommented script reads from file
    FILE* fp = fopen(argv[1], "r");
    D3VEC plot = read_file(fp);
//    if line below is uncommented script reads from stdin
//    D2VEC plot = read_stdin();

    std::cout << number_of_paths(plot) << std::endl;
    return 0;
}

INT number_of_paths(D3VEC& plot) {

    plot[N-1][M-1][0].set_valid_k(0);
    plot[N-1][M-1][0].set_value(1);

    // Numbers of paths to reach any node in last column depends only from previous nodes of last column
    for (int i = N-2; i >= 0; --i) { //end of a crossing
        initialize_node(plot, true, i);
    }

    // Numbers of paths to reach any node in last row depends only from previous nodes of last row
    for (int j = M-2; j>=0; --j) {
        initialize_node(plot, false, j);
    }

    for (int i = N-2; i>=0; --i) { //rows
        for (int j = M-2; j>=0; --j) { //columns
            add_right_and_down_nodes(plot, i, j);
            if (plot[i][j][0].get_end()) { //end of crossing
                add_crossing(plot, i, j);
            }
        }
    }
    return sum_all_levels(plot);
}

void initialize_node(D3VEC& plot, bool column, int pos) {
    if (column) {
        if (plot[pos][M-1][0].get_start()) //previous node is start of crossing
            return;
        if (plot[pos][M-1][0].get_end()) { //end of crossing
            int valid_k = plot[pos+1][M-1][0].get_valid_k();
            if (valid_k < X) {
                int start_y = plot[pos+1][M-1][0].get_y_orig();
                INT prev = plot[start_y][M-1][valid_k].get_value();
                plot[pos][M-1][valid_k+1].set_valid_k(valid_k+1);
                plot[pos][M-1][valid_k+1].set_value(prev);
            }
        }
        else { //not an end of a crossing
            int valid_k = plot[pos+1][M-1][0].get_valid_k();
            INT prev = plot[pos+1][M-1][valid_k].get_value();
            plot[pos][M-1][0].set_value(prev);
            plot[N-1][pos][0].set_valid_k(valid_k);
        }
    }
    else {
        if (plot[N-1][pos][0].get_start()) //previous node is start of crossing
            return;
        if (plot[N-1][pos][0].get_end()) { //end of crossing
            int valid_k = plot[N-1][pos+1][0].get_valid_k();
            if (valid_k < X) {
                int start_x = plot[N-1][pos+1][0].get_y_orig();
                INT prev = plot[N-1][start_x][valid_k].get_value();
                plot[N-1][pos][0].set_valid_k(valid_k+1);
                plot[N-1][pos][valid_k+1].set_value(prev);
            }
        }
        else { //not an end of a crossing
            int valid_k = plot[N-1][pos+1][0].get_valid_k();
            INT prev = plot[N-1][pos+1][valid_k].get_value();
            plot[N-1][pos][valid_k].set_value(prev);
            plot[N-1][pos][0].set_valid_k(valid_k);
        }
    }
}

void add_right_and_down_nodes(D3VEC& plot, int i, int j) {
    bool R = plot[i][j+1][0].get_start();
    bool B = plot[i+1][j][0].get_start();
    if (R & B) { //both neighbors are start of crossings, can't reach this node this way
        return;
    }
    else if (R) { //right neighbor is a start of a crossing, can reach this node only from below
        int maxk = plot[i+1][j][0].get_valid_k();
        if (maxk <= X) {
            for (int z=0; z <= maxk; ++z) {
                INT below = plot[i+1][j][z].get_value() % 1000000103;
                plot[i][j][z].set_value(below % 1000000103);
            }
        }
    }
    else if (B) { //below neighbor is a start of a crossing, can reach this node only from right
        int maxk = plot[i][j+1][0].get_valid_k();
        if (maxk <= X) {
            for (int z=0; z <= maxk; ++z) {
                INT right = plot[i][j+1][z].get_value() % 1000000103;
                plot[i][j][z].set_value(right % 1000000103);
            }
        }
    }
    else { //can reach this node from both neighbors
        int maxk = std::max(plot[i][j+1][0].get_valid_k(), plot[i+1][j][0].get_valid_k());
        plot[i][j][0].set_valid_k(maxk);
        for (int z = 0; z <= maxk; ++z) {
            INT below = plot[i+1][j][z].get_value() % 1000000103;
            INT right = plot[i][j+1][z].get_value() % 1000000103;
            plot[i][j][z].set_value((below + right) % 1000000103);
        }
    }
}

void add_crossing(D3VEC& plot, int i, int j) {
    int x = plot[i][j][0].get_x_orig();
    int y = plot[i][j][0].get_y_orig();
    int maxk = plot[x][y][0].get_valid_k();

    if (maxk <= X) {
        for(int z=0; z<maxk; ++z) {
            INT prev = plot[x][y][z].get_value();
            INT temp = plot[i][j][z].get_value();
            plot[i][j][0].set_valid_k(z+1);
            plot[i][j][z+1].set_value(prev+temp);
        }
    }

}

INT sum_all_levels(D3VEC& plot) {
    int valid_k = plot[0][0][0].get_valid_k();
    INT part_sum = 0;
    for (int i=0; i<=valid_k; ++i) {
        part_sum += plot[0][0][i].get_value() % 1000000103;
    }
    part_sum = part_sum % 1000000103;
}

//read_stdin uses read_long() to read from stdin
D3VEC read_stdin(){
    N = read_long();
    M = read_long();
    K = read_long();
    X = read_long();

    D3VEC plot(N, D2VEC(M, D1VEC(K)));

    for(int i = 0; i < K; ++i) {
        int st = read_long();     //ORIGIN
        int en = read_long();     //DESTINATION

        int x = st / M;     //ORIGIN x
        int y = st % M;     //ORIGIN y
        int k = en / M;     //DESTINATION x
        int z = en % M;     //DESTINATION y

//        plot[x][y][0].set_start(true);
//        plot[x][y][0].set_x_dest(k);
//        plot[x][y][0].set_y_dest(z);
        plot[k][z][0].set_end(true);
        plot[k][z][0].set_x_orig(x);
        plot[k][z][0].set_y_orig(y);
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
D3VEC read_file(FILE* fp){
    N = read_long(fp);
    M = read_long(fp);
    K = read_long(fp);
    X = read_long(fp);

    D3VEC plot(N, D2VEC(M, D1VEC(K)));


    for(int i = 0; i < K; ++i) {
        int st = read_long(fp);     //ORIGIN
        int en = read_long(fp);     //DESTINATION

        int x = st / M;     //ORIGIN x
        int y = st % M;     //ORIGIN y
        int k = en / M;     //DESTINATION x
        int z = en % M;     //DESTINATION y

        plot[x][y][0].set_start(true);
//        plot[x][y][0].set_x_dest(k);
//        plot[x][y][0].set_y_dest(z);
        plot[k][z][0].set_end(true);
        plot[k][z][0].set_x_orig(x);
        plot[k][z][0].set_y_orig(y);
    }

    return plot;
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
