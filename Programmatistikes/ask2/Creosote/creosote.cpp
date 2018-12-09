#include <iostream>
#include <vector>
#include <climits>

#define BSIZE 1<<15

typedef long long int INT;
typedef std::vector<int>::iterator ITER;
typedef std::vector<int> VEC;

char buffer[BSIZE];
long bpos = 0L, bsize = 0L;

int read_long();
INT quadric_equation(INT value, long a, long b, long c);
int read_long(FILE* fp);


int main(int argc, char** argv)
{
//    FILE* fp = fopen(argv[1], "r");
    long N = read_long(), a = read_long(), b = read_long(), c = read_long();
    //std::cout <<"N is " << N <<" a is " << a << " b is " << b << " c is " << c <<"\n";
    auto x = new int[N];
    for(long i = 0; i < N; i++) {
        x[i] = read_long();
    }

    //Calculating
    auto plates_sums = new long long[N+1];
    plates_sums[N-1] = quadric_equation(x[N-1], a, b, c);

    INT sum=0, temp, max_dish;
    //plates_sums[i] show the max total MIAM if
    //there where only delights i,i+1,...,N-1
    // => the answer is plates_sums[0]
    for(long i=N-2; i>=0; --i){
        plates_sums[i] = LLONG_MIN;
        long long sum_x = 0;
        for (long j=i+1; j<=N; ++j) {
            //search for the best index
            //to complete the first plate
            //starting with delight i
            sum_x += x[j - 1];
            temp = quadric_equation(sum_x, a, b, c) + plates_sums[j];
            if (temp > plates_sums[i])
                plates_sums[i] = temp;
        }
    }

    std::cout << plates_sums[0] << std::endl;
}

int read_long()
{
    long d = 0L, x = 0L;
    char c;
    bool b = false;
    while (1)  {
        if (bpos >= bsize) {
            bpos = 0;
            if (feof(stdin)) return x;
            bsize = fread(buffer, 1, BSIZE, stdin);
        }
        c = buffer[bpos++];
        if (c == '-') b = true;
        if (c >= '0' && c <= '9') { x = x*10 + (c -'0'); d = 1; }
        else if (d == 1) return b ? (-1*x) : x;
    }
    return -1;
}

int read_long(FILE* fp)
{
    int d = 0L, x = 0L;
    char c;

    while (1)  {
        if (bpos >= bsize) {
            bpos = 0;
            if (feof(fp))
                return x;
            bsize = (long long) fread(buffer, 1, BSIZE, fp);
        }
        c = buffer[bpos++];
        if (c >= '0' && c <= '9') {
            x = x*10 + (c-'0');
            d = 1;
        }
        else if (d == 1)
            return x;
    }
//    return -1;
}

INT quadric_equation(INT value, long a, long b, long c){
    return (a*value*value + b*value + c);
}
