#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <stack>
#include <tuple>
#define BSIZE 1<<15

typedef long long int INT;
typedef std::vector<INT>::iterator ITER;
typedef std::vector<INT> VEC;
typedef std::pair<INT, INT> INTpair;
typedef std::stack<INTpair> STACKPair;


//INT read_long();
//INT read_long(FILE* fp);
void make_sum(ITER it, STACKPair& next_greater_element, unsigned int& position, VEC& sums, VEC& my_city);
INT find_min(VEC& right_to_left_sum, VEC& left_to_right_sum, VEC& my_city);

int main(int argc, char* argv[]) {
    try {
//        INT N = read_long();
//        VEC my_city;
//        INT i;
//        for (i = 0; i < N; ++i) {
//            my_city.push_back(read_long());
//        }

//        FILE* fp = fopen(argv[1], "r");
//
//        //-------FROM FILE---------
//        INT N = read_long(fp);                                                                 //read size of city
//        VEC my_city;
//
//        for(INT i=0; i<N; ++i) {
//            my_city.push_back(read_long(fp));         //read heights of buildings in city
//        }

        INT N;
        VEC my_city;
        std::scanf("%lld", &N);
        INT i,value;
        for(i=0; i<N; ++i){
            std::scanf("%lld", &value);
            my_city.push_back(value);
        }

        unsigned int position = 1L;
        auto start = my_city.begin();
        auto end = my_city.end();
        STACKPair next_greater_element;
        next_greater_element.push(std::make_pair(*my_city.begin(), position));

        VEC left_to_right_sum;
        VEC right_to_left_sum;
        left_to_right_sum.push_back(*start); //first sum

        start++;
        for (auto it = start; it != end; ++it) {
            ++position;
            make_sum(it, next_greater_element, position, left_to_right_sum, my_city);
        }
        while(!next_greater_element.empty())
            next_greater_element.pop();

        position = 1LL;
        auto temp = std::next(my_city.begin(), N-1);
        right_to_left_sum.push_back(*temp);

        next_greater_element.push(std::make_pair(*temp, position));

        VEC my_city_reversed = my_city;
        std::reverse(my_city_reversed.begin(), my_city_reversed.end());
        start = my_city_reversed.begin();
        start++;
        end = my_city_reversed.end();
        for (auto it = start; it != end; ++it) {
            ++position;
            make_sum(it, next_greater_element, position, right_to_left_sum, my_city_reversed);
        }
        INT result = find_min(right_to_left_sum, left_to_right_sum, my_city);

        std::cout << result << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what();
    }

    return 0;

}


void make_sum(ITER it, STACKPair& next_greater_element, unsigned int& position, VEC& sums, VEC& my_city) {
    if (*it < next_greater_element.top().first) {
        next_greater_element.push(std::make_pair(*it, position));

        //find the previous position and add with the previous sum;
        auto temp = std::next(sums.begin(), position-2);
        INT prev_sum = *temp;
        sums.push_back(prev_sum + *it);
    }
    else {
        while ( ! next_greater_element.empty() && next_greater_element.top().first < *it) {
            next_greater_element.pop();
        }
        if ( next_greater_element.empty() ) {
            next_greater_element.push(std::make_pair(*it, position));
            auto result = *it * position;
            sums.push_back(result);
        }
        else {
            auto prev = next_greater_element.top();
            INT temp = prev.second;

            auto tempIT = std::next(sums.begin(), temp-1);

            auto result = *it * (position - temp) + *tempIT;
            sums.push_back(result);
            next_greater_element.push(std::make_pair(*it, position));
        }
    }
}

INT find_min(VEC& right_to_left_sum, VEC& left_to_right_sum, VEC& my_city) {

    auto Rit = right_to_left_sum.end()-1;
    auto Lit = left_to_right_sum.begin();
    auto Cit = my_city.begin();

    INT position = 0LL;
    INT min = *Rit;

    for (; Lit != left_to_right_sum.end(); ++Lit ) {
        INT res = *Lit+*Rit-*Cit;
        if(res < min){
            min = res;
        }
        ++Cit;
        --Rit;
    }
    return min;
}

//INT read_long()
//{
//    INT d = 0L, x = 0L;
//    char c;
//
//    while (1)  {
//        if (bpos >= bsize) {
//            bpos = 0;
//            if (stdin)
//                return x;
//            bsize = (long long) fread(buffer, 1, BSIZE, stdin);
//        }
//        c = buffer[bpos++];
//        if (c >= '0' && c <= '9') {
//            x = x*10 + (c-'0');
//            d = 1;
//        }
//        else if (d == 1)
//            return x;
//    }
//    return -1;
//}

//INT read_long(FILE* fp)
//{
//    INT d = 0L, x = 0L;
//    char c;
//
//    while (1)  {
//        if (bpos >= bsize) {
//            bpos = 0;
//            if (feof(fp))
//                return x;
//            bsize = (long long) fread(buffer, 1, BSIZE, fp);
//        }
//        c = buffer[bpos++];
//        if (c >= '0' && c <= '9') {
//            x = x*10 + (c-'0');
//            d = 1;
//        }
//        else if (d == 1)
//            return x;
//    }
//    return -1;
//}
