#include <iostream>
#include <vector>

#define bSIZE 1<<15

/*---START OF DECLARATIONS--------------------------------------------------*/
class Node;
typedef long long int INT;
typedef std::vector<Node> D1VEC; //1Dimension Vector
typedef std::vector<D1VEC> D2VEC; //2Dimension Vector
typedef std::vector<D2VEC> D3VEC; //3Dimension Vector of Nodes

char buffer[bSIZE];
long bpos = 0L, bsize = 0L;

class Node {

    private:
        INT value_;
        int valid_k_;
        int y_orig_;
        int x_orig_;
        bool end_;
        bool start_;
        int x_dest_;
        int y_dest_;

    public:
        Node() :
                value_(0),
                end_(false),
                x_orig_(-1),
                y_orig_(-1),
                valid_k_(0),
                start_(false),
                x_dest_(-1),
                y_dest_(-1)
                {};

        ~Node() = default;

        INT get_value() { return value_; }
        void set_value(INT value) { value_ = value; }

        bool get_end() { return end_; }
        void set_end(bool end) { end_ = end; }

        int get_valid_k() { return valid_k_; }
        void set_valid_k(int valid_k) { valid_k_ = valid_k; }

        bool get_start() { return start_; }
        void set_start(bool start) { start_ = start; }

        int get_x_dest() { return x_dest_; }
        void set_x_dest(int x_point) { x_dest_ = x_point; }

        int get_y_dest() { return y_dest_; }
        void set_y_dest(int y_point) { y_dest_ = y_point; }

        int get_x_orig() { return x_orig_; }
        void set_x_orig(int x_point) { x_orig_ = x_point; }

        int get_y_orig() { return y_orig_; }
        void set_y_orig(int y_point) { y_orig_ = y_point; }
};

int read_long();
int read_long(FILE* fp);
D3VEC read_stdin();
D3VEC read_file(FILE* fp);
INT number_of_paths(D3VEC& plot);
void add_right_and_down_nodes(D3VEC& plot, int i, int j);
void add_to_crossing(D3VEC& plot, int i, int j);
INT sum_all_levels(D1VEC& final_node);
void add_right(D3VEC& plot, int i, int j);
void add_below(D3VEC& plot, int i, int j);
void initialize_column(D3VEC& plot, int pos);
void initialize_row(D3VEC& plot, int pos);
void print_world(D3VEC& plot);

int globalN, globalM, globalK, globalX;
/*---END OF DECLARATIONS--------------------------------------------------*/

int main (int argc, char** argv){

//    if the two lines below are uncommented script reads from file
//    FILE* fp = fopen(argv[1], "r");
//    D3VEC plot = read_file(fp);


//    if line below is uncommented script reads from stdin
    D3VEC plot = read_stdin();

    if(globalM == 1 and globalN == 1) {
        std::cout << 1 << std::endl;
    }
    INT value =  number_of_paths(plot);
//    std::cout << "Final version\n";
//    print_world(plot);
    std::cout << value << std::endl;
    return 0;
}

/*---START OF IMPLEMENTATION OF FUNCTIONS---------------------------------*/
INT number_of_paths(D3VEC& plot) {

    plot[globalN-1][globalM-1][0].set_value(1);

    // Numbers of paths to reach any node in last column depends only from previous nodes of last column
    for (int i = globalN-2; i >= 0; --i) { //end of a crossing
        initialize_column(plot, i);
    }

    // Numbers of paths to reach any node in last row depends only from previous nodes of last row
    for (int j = globalM-2; j>=0; --j) {
        initialize_row(plot, j);
    }

    plot[0][0][0].set_start(false);

    for (int i = globalN-2; i>=0; --i) { //rows
        for (int j = globalM-2; j>=0; --j) { //columns
            add_right_and_down_nodes(plot, i, j);
            if (plot[i][j][0].get_start()) { //start of crossing
                add_to_crossing(plot, i, j);
            }
        }
//        print_world(plot);
    }

    return sum_all_levels(plot[0][0]);
}

void initialize_column(D3VEC& plot, int pos) {
    if(plot[pos+1][globalM-1][0].get_start()) {
        return;
    }
    if (plot[pos][globalM-1][0].get_start()) {
        add_below(plot, pos, globalM-1);
        add_to_crossing(plot, pos, globalM-1);
    }
    else {
        add_below(plot, pos, globalM-1);
    }
}

void initialize_row(D3VEC& plot, int pos) {
    if(plot[globalN-1][pos+1][0].get_start()) {
        return;
    }
    if(plot[globalN-1][pos][0].get_start()) {
        add_right(plot, globalN-1, pos);
        add_to_crossing(plot, globalN-1, pos);
    }
    else {
        add_right(plot, globalN-1, pos);
    }

}

void add_right_and_down_nodes(D3VEC& plot, int i, int j) {
    bool Right_start = plot[i][j+1][0].get_start();
    bool Below_start = plot[i+1][j][0].get_start();

    if (Right_start and Below_start) { //can't reach this node from neighbors
        return;
    }
    else if (Right_start) { //can reach this node only from below
        add_below(plot, i, j);
    }
    else if (Below_start) { //can reach this node only from right
        add_right(plot, i, j);
    }
    else { //can reach this from both neighbors
        add_below(plot, i, j);
        add_right(plot, i, j);
    }
}

void add_right(D3VEC& plot, int i, int j) {
    int maxk = plot[i][j+1][0].get_valid_k();
    for (int iter=0; iter<=maxk; ++iter){
        INT right = plot[i][j+1][iter].get_value();
        INT prev = plot[i][j][iter].get_value();
        prev = (right % 1000000103 + prev % 1000000103) % 1000000103;
        plot[i][j][iter].set_value(prev);
    }
    int myk = plot[i][j][0].get_valid_k();
    plot[i][j][0].set_valid_k(std::max(maxk, myk));
}

void add_below(D3VEC& plot, int i, int j){
    int maxk = plot[i+1][j][0].get_valid_k();
    for (int iter=0; iter<=maxk; ++iter){
        INT below = plot[i+1][j][iter].get_value();
        INT prev = plot[i][j][iter].get_value();
        prev = below % 1000000103 + prev % 1000000103;
        plot[i][j][iter].set_value(prev % 1000000103);
    }
    int myk = plot[i][j][0].get_valid_k();
    plot[i][j][0].set_valid_k(std::max(maxk, myk));
}

void add_to_crossing(D3VEC& plot, int i, int j) {
    int x = plot[i][j][0].get_x_dest();
    int y = plot[i][j][0].get_y_dest();

    int maxk = plot[i][j][0].get_valid_k();

    for (int iter=0; iter<=globalX; ++iter) {
        INT orig_val = plot[i][j][iter].get_value();
        INT prev_val = plot[x][y][iter+1].get_value();
        orig_val = orig_val % 1000000103 + prev_val % 1000000103;
        plot[x][y][iter+1].set_value(orig_val % 1000000103);
    }
    int prevk = plot[i][j][0].get_valid_k();
    plot[x][y][0].set_valid_k(prevk+1);
}

INT sum_all_levels(D1VEC& final_node) {

    INT sum = 0;

    for (int i=0; i<=globalX; ++i){
        sum += final_node[i].get_value() % 1000000103;
        sum = sum % 1000000103;
    }

    return sum % 1000000103;
}

//read_stdin uses read_long() to read from stdin
D3VEC read_stdin(){
    globalN = read_long();
    globalM = read_long();
    globalK = read_long();
    ++globalK;
    globalX = read_long();

    D3VEC plot(globalN, D2VEC(globalM, D1VEC(globalK)));

    for(int i = 0; i < globalK-1; ++i) {
        int st = read_long();     //ORIGIN
        int en = read_long();     //DESTINATION

        int x = st / globalM;     //ORIGIN x
        int y = st % globalM;     //ORIGIN y
        int k = en / globalM;     //DESTINATION x
        int z = en % globalM;     //DESTINATION y

        plot[x][y][0].set_start(true);
        plot[x][y][0].set_x_dest(k);
        plot[x][y][0].set_y_dest(z);
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
    globalN = read_long(fp);
    globalM = read_long(fp);
    globalK = read_long(fp);
    ++globalK;
    globalX = read_long(fp);

    D3VEC plot(globalN, D2VEC(globalM, D1VEC(globalK)));

    for(int i = 0; i < globalK-1; ++i) {
        int st = read_long(fp);     //ORIGIN
        int en = read_long(fp);     //DESTINATION

        int x = st / globalM;     //ORIGIN x
        int y = st % globalM;     //ORIGIN y
        int k = en / globalM;     //DESTINATION x
        int z = en % globalM;     //DESTINATION y

        plot[x][y][0].set_start(true);
        plot[x][y][0].set_x_dest(k);
        plot[x][y][0].set_y_dest(z);
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

void print_world(D3VEC& plot) {
    for (int zz=0; zz<globalK; ++zz) {
        std::cout << "k = " << zz << std::endl;
        for (int ii=0; ii<globalN; ++ii) {
            for (int jj=0; jj<globalM; ++jj) {
                std::cout << plot[ii][jj][zz].get_value() << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    std::cout << "----------------\n\n";
}
/*---END OF IMPLEMENTATION OF FUNCTIONS-----------------------------------*/