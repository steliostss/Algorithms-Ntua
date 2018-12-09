#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>


#define BSIZE 1<<15

typedef long long int INT;
typedef std::vector<INT>::iterator ITER;
typedef std::vector<INT> VEC;

char buffer[BSIZE];
INT bpos = 0L, bsize = 0L;

//DECLARATIONS-------------------------------------------------------------------------------------------------------
INT read_long(FILE* fp);

ITER find_max_check_incr_decr(const VEC& my_city, INT* max, ITER start, ITER end, bool* incr, bool* decr);

INT calculate_best_sum(const VEC& my_city, ITER start, ITER end);
//-------------------------------------------------------------------------------------------------------------------


int main(int argc, char* argv[]) {
    clock_t start = clock();
    try { //catch exceptions
//        FILE* fp = fopen(argv[1], "r");

//        -------FROM FILE---------
//        INT N = read_long(fp);                                                                 //read size of city
//        VEC my_city;
//
//        for(INT i=0; i<N; ++i) {
//            my_city.push_back(read_long(fp));         //read heights of buildings in city
//        }


        //-------FROM STDIN--------
        INT N;
        VEC my_city;
        std::scanf("%lld", &N);
        INT i,temp;
        for(i=0; i<N; ++i){
            std::scanf("%lld", &temp);
            my_city.push_back(temp);
        }

        ITER itmax = std::max_element(my_city.begin(), my_city.end());
        if(itmax != my_city.end()) {
            INT min = calculate_best_sum(my_city, my_city.begin(), my_city.end());
            std::cout << min << std::endl;
        }
    }
    catch (std::exception& e){
        std::cerr << e.what();
    }

    return 0;
}


//returns index of max
//checks if decr or incr
//returns max by reference
ITER find_max_check_incr_decr(const VEC& my_city, ITER first, ITER end, bool& sorted) {

    bool incr = true;
    bool decr = true;

    ITER sec = first;
    if(first != end) ++sec;
    ITER maxposition = first;

    for (; sec != end; ++sec){
        if (*sec > *maxposition){
            maxposition = sec;
        }
        if (*sec > *first) {       //Find max element
            decr = false;
        }
        else if (*sec < *first) {
            incr = false;           //Check if sorted in decreasing order
        }
        ++first;
    }

    sorted = decr || incr;
    return maxposition;
}

INT calculate_best_sum(const VEC& my_city, ITER start, ITER end){

    //If we have only one element, return itself
    if(start == end){
        return *start;
    }

    bool sorted = false;

    ITER maxIndex = find_max_check_incr_decr(my_city, start, end, sorted);
//    std::cout << *maxIndex <<std::endl;
    if (sorted) {
        INT tax = std::accumulate(start, end, 0LL);
        return tax;
    }

    //If max element is at the begging, recursive call to right partition
    if(maxIndex == start) {
        INT left_partition_sum = *maxIndex;
        INT right = calculate_best_sum(my_city, start+1, end) + left_partition_sum;
        return (right);
    }
    //If max element is at the end, recursive call to left partition
    else if (maxIndex == end-1){
        INT right_partition_sum = *maxIndex;
        INT left = calculate_best_sum(my_city, start, end-1) + right_partition_sum;
        return (left);
    }
    //If max element is at the middle, recursive call to both
    //left and right partition and find min
    else {
        //If we choose an element at the right partition then add left partition sum
        INT left_partition_sum = (std::distance(start, maxIndex)+1)*(*maxIndex);
        //If we choose an element at the left partition then add right partition sum
        INT right_partition_sum = std::distance(maxIndex, end)*(*maxIndex);


        INT left = calculate_best_sum(my_city, start, maxIndex) + right_partition_sum;
        INT right = calculate_best_sum(my_city, maxIndex+1, end) + left_partition_sum;

        if(right <= left){
            return right;
        }
        else{
            return left;
        }
    }
}

INT read_long(FILE* fp)
{
    INT d = 0L, x = 0L;
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
    return -1;
}
