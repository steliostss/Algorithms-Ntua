#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <cfloat>

typedef long double LD;
typedef long L;

#define BSIZE 1<<15
char buffer[BSIZE];
L bpos = 0L, bsize = 0L;

L read_long(FILE* fp);
L read_long();

class Particle {
    private:
        L velocity;
        L time_launched;
        int index;

    public:
        L get_velocity() { return velocity; }
        L get_time_launched() { return time_launched; }
        L get_index() { return index; }

        void set_time_launched(L time) { time_launched = time;}
        void set_velocity(L vel) { velocity = vel; }
        void set_index(int ind) { index = ind; }

        explicit Particle(int ind);
        explicit Particle(FILE* fp, int ind);
        ~Particle();
};

Particle::Particle(int ind) {
    time_launched = read_long();
    velocity = read_long();
    index = ind;
}

Particle::Particle(FILE *fp, int ind) {
    time_launched = read_long(fp);
    velocity = read_long(fp);
    index = ind;
}

Particle::~Particle() = default;

typedef std::vector<Particle>::iterator ITER;
typedef std::vector<Particle> VEC;
typedef std::pair<LD, ITER> f_PAIR; //fundamental pair
typedef std::pair<f_PAIR, f_PAIR> PAIR;


void read_file(FILE* fp, L& particles, L& length, L& max_collisions, VEC& canon_A, VEC& canon_B);
void read_stdin(L& particles, L& length, L& max_collisions, VEC& canon_A, VEC& canon_B);
void fix_B_pair(PAIR& elements, L& length);
LD redefine_upper_bound(VEC& canon_A, VEC& canon_B, L& length, LD& time);

LD calculate_first_K_collisions(LD upper_bound, LD lower_bound, L& length, L& max_collisions, VEC& canon_A, VEC& canon_B);
PAIR get_first_two_particles (VEC& canon, L& length, LD& time);

/*---------ΜΑΙΝ---------*/
int main(int argc, char* argv[]) {

    try { //catch exceptions
        L particles;
        L length, max_collisions;
        VEC canon_A, canon_B;
//        FILE *fp = fopen(argv[1], "r");
//        read_file(fp, particles, length, max_collisions, canon_A, canon_B);
        read_stdin(particles, length, max_collisions, canon_A, canon_B);

        //set proper upper bound
        auto itA = canon_A.begin();
        auto itB = canon_B.begin();

        LD v1 = itA->get_velocity();
        LD t1 = itA->get_time_launched();
        LD v2 = itB->get_velocity();
        LD t2 = itB->get_time_launched();

        LD upper_bound = LD(t1*v1+v2*t2 + length) / (v1 + v2);
        LD lower_bound = 0;

        while (max_collisions > 0) {
            LD time = calculate_first_K_collisions(upper_bound, lower_bound, length, max_collisions, canon_A, canon_B);
            lower_bound = time;
            upper_bound = redefine_upper_bound(canon_A, canon_B, length, lower_bound);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what();
    }

    return 0;

}

void read_file(FILE* fp, L& particles, L& length, L& max_collisions, VEC& canon_A, VEC& canon_B){
    /*-------FROM FILE---------*/
    particles = read_long(fp);
    length = read_long(fp);
    max_collisions = read_long(fp);

    /*-------READING-----------*/
    for (int i = 0; i < particles; ++i) {
        canon_A.push_back(Particle(fp, i+1));
    }

    for (int i = 0; i < particles; ++i) {
        canon_B.push_back(Particle(fp, i+1));
    }
}

void read_stdin(L& particles, L& length, L& max_collisions, VEC& canon_A, VEC& canon_B){
    /*-------FROM STDIN--------*/
    particles = read_long();
    length = read_long();
    max_collisions = read_long();

    /*-------READING-----------*/
    for (int i = 0; i < particles; ++i) {
        canon_A.push_back(Particle(i+1));
    }

    for (int i = 0; i < particles; ++i) {
        canon_B.push_back(Particle(i+1));
    }
}

L read_long() {
    L d = 0L, x = 0L;
    char c;

    while (1)  {
        if (bpos >= bsize) {
            bpos = 0;
            if (feof(stdin))
                return x;
            bsize = (L) fread(buffer, 1, BSIZE, stdin);
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

L read_long(FILE* fp) {
    L d = 0L, x = 0L;
    char c;

    while (1)  {
        if (bpos >= bsize) {
            bpos = 0;
            if (feof(fp))
                return x;
            bsize = (L) fread(buffer, 1, BSIZE, fp);
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

LD calculate_first_K_collisions(LD upper_bound, LD lower_bound, L& length, L& max_collisions, VEC& canon_A, VEC& canon_B) {
    //exit case
    if (max_collisions == 0)
        return -2;
    LD time = LD(upper_bound + lower_bound) / 2;

    if (upper_bound >= lower_bound) {
        PAIR A_elements = get_first_two_particles(canon_A, length, time);
        PAIR B_elements = get_first_two_particles(canon_B, length, time);
        //B_elements position is from x=0 to x=L
        //make it from x=L to x=0
        //multiply with (-1) and add L
        fix_B_pair(B_elements, length);

        LD first_a, sec_a;
        ITER ita1;
        //a1 position & iterator
        first_a = A_elements.first.first;
        ita1 = A_elements.first.second;
        //a2 position & iterator
        sec_a = A_elements.second.first;


        LD first_b, sec_b;
        ITER itb1;
        //a1 position & iterator
        first_b = B_elements.first.first;
        itb1 = B_elements.first.second;
        //a2 position & iterator
        sec_b = B_elements.second.first;

        PAIR Compare_elementsA = get_first_two_particles(canon_A, length, upper_bound);
        PAIR Compare_elementsB = get_first_two_particles(canon_B, length, upper_bound);
        fix_B_pair(Compare_elementsB, length);


        //hypothetically first elements
        //check if worst case: collision @ upper bound

        ITER hypoth_first_a_it;
        //a1 position & iterator
        hypoth_first_a_it = Compare_elementsA.first.second;

        ITER hypoth_first_b_it;
        //b1 position & iterator
        hypoth_first_b_it = Compare_elementsB.first.second;


        //calculate velocities and times_launched
        LD t1 = hypoth_first_a_it->get_time_launched();
        LD v1 = hypoth_first_a_it->get_velocity();
        LD t2 = hypoth_first_b_it->get_time_launched();
        LD v2 = hypoth_first_b_it->get_velocity();

        LD compare_w_upper = LD(t1*v1+v2*t2 + length) / (v1 + v2);

        if (upper_bound == compare_w_upper){
            std::cout << hypoth_first_a_it->get_index() << ' ' << hypoth_first_b_it->get_index() << '\n';
            --max_collisions;
            hypoth_first_a_it->set_velocity(0);
            hypoth_first_b_it->set_velocity(0);
            return upper_bound;
        }

        /*  then retry in the "future"*/
        if (first_a < first_b) {
            lower_bound = time;
            return calculate_first_K_collisions(upper_bound, lower_bound, length, max_collisions, canon_A, canon_B);
        }
        /*  retry in the "past"*/
        else if ( first_a > sec_b || first_b < sec_a) {
            upper_bound = time;
            return calculate_first_K_collisions(upper_bound, lower_bound, length, max_collisions, canon_A, canon_B);
        }
        /* found exactly one collision */
        else {
            std::cout << ita1->get_index() << ' ' << itb1->get_index() << '\n';
            --max_collisions;
            ita1->set_velocity(0);
            itb1->set_velocity(0);
            return time;
        }
    }
    else {
        return -1;
    }
}

void fix_B_pair(PAIR& elements, L& length){
    elements.first.first -= length;
    elements.first.first *= -1;

    elements.second.first -= length;
    elements.second.first *= -1;
}

PAIR get_first_two_particles (VEC& canon, L& length, LD& time){
    //for all elements in canon, return the first two
    LD first_position = -1;
    ITER first_index;
    LD second_position = -1;
    ITER second_index;
    for (auto it = canon.begin(); it != canon.end(); ++it) {

        if(it->get_time_launched() <= time) {
            LD position = it->get_velocity() * (time - it->get_time_launched());

            if (position > first_position) {
                second_position = first_position;
                first_position = position;
                second_index = first_index;
                first_index = it;
            } else if (position < first_position && position > second_position) {
                second_position = position;
            }
        }
        else
            break;
    }

    f_PAIR temp1 = std::make_pair(first_position, first_index);
    f_PAIR temp2 = std::make_pair(second_position, second_index);

    return std::make_pair(temp1, temp2);

}

LD redefine_upper_bound(VEC& canon_A, VEC& canon_B, L& length, LD& time){
    ITER itA;
    ITER itB;
    for (auto it = canon_A.begin(); it != canon_A.end(); ++it) {
        if(it->get_velocity() > 0) {
            itA = it;
            break;
        }
    }
    for (auto it = canon_B.begin(); it != canon_B.end(); ++it) {
        if (it->get_velocity() > 0) {
            itB = it;
            break;
        }
    }

    LD v1 = itA->get_velocity();
    LD t1 = itA->get_time_launched();
    LD v2 = itB->get_velocity();
    LD t2 = itB->get_time_launched();

    LD upper_bound = LD(t1*v1+v2*t2 + length) / (v1 + v2);

    return upper_bound;
}