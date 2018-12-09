#include <iostream>
#include <vector>
#include <algorithm>

typedef std::vector<int> VEC;
typedef std::vector<int>::iterator ITER;

#define BSIZE 1<<15
char buffer[BSIZE];
long bpos = 0L, bsize = 0L;

int read_long();
int read_long(FILE* fp);
int CeilIndex(VEC& v, int l, int r, int key);
int LongestSubsequenceLength(VEC& v, VEC& subseq);


int main(int argc, char** argv) {

    VEC people;

    int N;
    std::scanf("%d", &N);
    int i,value;
    for(i=0; i<N; ++i){
        std::scanf("%d", &value);
        people.push_back(value);
    }
//    //-------FROM STDIN--------
//    int N = read_long();
//    for (int i = 0; i < N; ++i) {
//        people.push_back(read_long());
//    }
//
//    //-------FROM FILE---------
//    FILE *fp = fopen(argv[1], "r");
//    int N = read_long(fp);
//
//    for (int i = 0; i < N; ++i) {
//        people.push_back(read_long(fp));
//    }

    VEC incr_sub;
    LongestSubsequenceLength(people, incr_sub);

    VEC decr_sub;
    std::reverse(people.begin(), people.end());
    for (int &it : people) { it *= -1; }
    LongestSubsequenceLength(people, decr_sub);

    std::reverse(decr_sub.begin(), decr_sub.end());

    auto subit = decr_sub.begin();
    int max = 0;
    for (int &incrit : incr_sub) {
        int temp = incrit + *subit;
        if(temp > max)
            max = temp;

        try {
            subit++;
        }
        catch (std::exception &e){
            std::cerr << e.what() << '\n';
        }
    }

    std::cout << max << '\n';


    return 0;
}


// Binary search (note boundaries in the caller)
int CeilIndex(VEC& v, int l, int r, int key)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (v[m] >= key)
            r = m;
        else
            l = m;
    }

    return r;
}

int LongestSubsequenceLength(VEC& v, VEC& subseq)
{
    if (v.empty())
        return 0;

    VEC tail(v.size(), 0);
    int length = 1; // always points empty slot in tail
    subseq.push_back(length);
    tail[0] = v[0];
    for (size_t i = 1; i < v.size(); i++) {

        // new smallest value
        if (v[i] < tail[0]) {
            tail[0] = v[i];
            subseq.push_back(length);
        }

            // v[i] extends largest subsequence
        else if (v[i] > tail[length - 1]) {
            tail[length++] = v[i];
            subseq.push_back(length);
        }

            // v[i] will become end candidate of an existing
            // subsequence or Throw away larger elements in all
            // LIS, to make room for upcoming grater elements
            // than v[i] (and also, v[i] would have already
            // appeared in one of LIS, identify the location
            // and replace it)
        else {
            tail[CeilIndex(tail, -1, length - 1, v[i])] = v[i];
            subseq.push_back(length);
        }
    }

    return length;
}

int read_long()
{
    int d = 0L, x = 0L;
    char c;
    bool b = false;
    while (1)  {
        if (bpos >= bsize) {
            bpos = 0;
            if (stdin)
                return x;
            bsize = (long long) fread(buffer, 1, BSIZE, stdin);
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
    bool b = false;
    while (1)  {
        if (bpos >= bsize) {
            bpos = 0;
            if (feof(fp))
                return x;
            bsize = (long long) fread(buffer, 1, BSIZE, fp);
        }
        c = buffer[bpos++];
        if (c == '-') b = true;
        if (c >= '0' && c <= '9') { x = x*10 + (c -'0'); d = 1; }
        else if (d == 1) return b ? (-1*x) : x;
    }
    return -1;
}