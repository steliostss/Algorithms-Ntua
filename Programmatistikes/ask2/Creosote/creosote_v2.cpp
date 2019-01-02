#include <iostream>
#include <vector>

#define betaSIZE 1<<15

typedef long long int INT;
typedef std::vector<int>::iterator ITER;
typedef std::vector<int> VEC;
typedef std::vector<INT> LVEC;
typedef std::pair<VEC, VEC> VECpair;

char buffer[betaSIZE];
long bpos = 0L, bsize = 0L;

int N, a, b, c;
int pointer=0;
LVEC alpha;
LVEC beta;

int read_long();
int read_long(FILE* fp);
INT quadric_equation(INT value);
INT best_comb(VEC& sums);
VECpair read_stdin();
VECpair read_file(FILE* fp);
INT ab(int key, INT x);
INT query(INT x);
void add(INT m,INT b);
bool bad(int k1, int k2, int k3);

int main(int argc, char** argv) {

//    VECpair input = read_stdin();
    FILE* fp = fopen(argv[1], "r");
    VECpair input = read_file(fp);

    VEC x = input.first;
    VEC sums = input.second;

    INT max = best_comb(sums);

    std::cout << max << '\n';

    return 0;
}

INT best_comb(VEC& sums){
    LVEC C(N, 0);
    C[0] = quadric_equation(sums[0]);
    add(-2*a* sums[0] , C[0] + a*sums[0]*sums[0] - b*sums[0]);

    for (int i=1; i<N; ++i) {
        C[i] = quadric_equation(sums[i]);
        C[i] = std::max(C[i], C[i]+query(sums[i]));
        add(-2*a* sums[i] , C[i] + a*sums[i]*sums[i] - b*sums[i]);
    }

    return C[N-1];
}

bool bad(int k1, int k2, int k3){
    INT v1 = (beta[k3]-beta[k1])*(alpha[k1]-alpha[k2]);
    INT v2 = (beta[k2]-beta[k1])*(alpha[k1]-alpha[k3]);
    return v1 < v2;
}

void add(INT m,INT b){
    alpha.push_back(m);
    beta.push_back(b);
    int kappa = (int) alpha.size();
    while( alpha.size() >= 3 && bad(kappa-3, kappa-2, kappa-1) ){
        alpha.erase(alpha.end()-2);
        beta.erase(beta.end()-2);
        kappa = (int) alpha.size();
    }

}

INT query(INT x){
    if (pointer >= alpha.size())
        pointer = (int) alpha.size()-1;

    while ( pointer < alpha.size()-1
                    &&
        ab(pointer+1, x) > ab(pointer, x) )
    {
        pointer++;
    }
    INT val =  ab(pointer, x);
    return val;
}

INT ab(int key, INT x){
    return alpha[key]*x+beta[key];
}

INT quadric_equation(INT value){
    return (a*value*value + b*value + c);
}

VECpair read_file(FILE* fp){
    N = read_long(fp);
    a = read_long(fp);
    b = read_long(fp);
    c = read_long(fp);

    VEC x(N, 0);
    VEC sums(N, 0);

    x[0] = read_long(fp);
    sums[0] = x[0];
    for(int i = 1; i < x.size(); i++) {
        x[i] = read_long(fp);
        sums[i] = sums[i-1] + x[i];
    }
    return std::make_pair(x, sums);
}

VECpair read_stdin(){
    N = read_long();
    a = read_long();
    b = read_long();
    c = read_long();

    VEC x(N, 0);
    VEC sums(N, 0);

    x[0] = read_long();
    sums[0] = x[0];
    for(int i = 1; i < x.size(); i++) {
        x[i] = read_long();
        sums[i] = sums[i-1] + x[i];
    }

    return std::make_pair(x, sums);
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