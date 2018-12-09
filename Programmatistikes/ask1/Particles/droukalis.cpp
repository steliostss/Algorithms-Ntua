#include <iostream>
#include <tuple>
#include <vector>

#define BSIZE 1<<15

using namespace std;

char buffer[BSIZE];
long bpos = 0L, bsize = 0L;

typedef long double LD;

long read_long();
long read_long(FILE* fp);

class Particle {
    public:
        long velocity;
        long time;
        int cnt;

        explicit Particle(int ind);
        explicit Particle(FILE* fp, int ind);
        ~Particle();
};

Particle::Particle(int ind) {
    time = read_long();
    velocity = read_long();
    cnt = ind;
}

Particle::Particle(FILE *fp, int ind) {
    time = read_long(fp);
    velocity = read_long(fp);
    cnt = ind;
}

typedef std::vector<Particle> p_VEC;
typedef std::vector<Particle>::iterator p_ITER;
typedef std::pair<p_ITER, p_ITER> PAIR;

Particle::~Particle() = default;

PAIR find_collision_2(p_VEC& A, p_VEC& B, LD t_lower, LD t_upper, long L);
PAIR two_furthest_advanced_particles(p_VEC& A, LD time);
p_ITER furthest_advanced_particle(p_VEC& A, LD time);
void read_stdin(long& particles, long& length, long& max_collisions, p_VEC& canon_A, p_VEC& canon_B);
void read_file(FILE* fp, long& particles, long& length, long& max_collisions, p_VEC& canon_A, p_VEC& canon_B);

int main (int argc, char* argv[]) {

    long N, L, K;
//    N = read_long();
//    L = read_long();
//    K = read_long();
    p_VEC A, B;

//    FILE *fp = fopen(argv[1], "r");
//    read_file(fp, N, L, K, A, B);
    read_stdin(N, L, K, A, B);

    //Τέλος οι αναγνώσεις, ώρα να παίξουμε
    LD time_first;           //χρονική στιγμή προηγούμενης σύγκρουσης
    LD time_second;          //χρονική στιγμή επόμενης περίπτωσης στη χειρότερη περίπτωση
    time_first = 0;          //αρχικά προφανώς δεν υπάρχει προηγούμενη σύγκρουση, οπότε θεωρούμε την αρχή του πολέμου
    PAIR collision;          //για να μας επιστρέφει η συνάρτηση τους αριθμούς και του α και του β σωματιδίου που συγκρούστηκαν

    auto old_iterA = A.begin();
    auto old_iterB = B.begin();
    //προφανώς στην αρχή τα πιο παλιά σωματίδια που έχουν ξεκινήσει,
    //αλλά δεν έχουν συγκρουστεί ακόμα είναι τα πρώτα από κάθε πλευρά
    for (int j = 0; j < K; ++j) {
        LD t1 = old_iterA->time;
        LD v1 = old_iterA->velocity;
        LD t2 = old_iterB->time;
        LD v2 = old_iterB->velocity;

        time_second = LD(t1*v1+v2*t2 + L) / (v1 + v2);


        collision = find_collision_2(A, B, time_first, time_second, L);

        auto a_collided = collision.first;
        auto b_collided = collision.second;

        LD timeA = a_collided->time;
        LD timeB = b_collided->time;

        LD velA = a_collided->velocity;
        LD velB = b_collided->velocity;

        time_first = LD(L + timeA * velA + timeB * velB ) / (velA + velB);   //ο χρόνος της τελευταίας κρούσης γίνεται ο χρόνος της κρούσης που μόλις βρήκαμε για να βρούμε την επόμενη
        cout << a_collided->cnt << " " << b_collided->cnt << endl;    //Η έξοδός μας
        //cout << "WOW I HAVE SOMETHING" <<endl;
        //Αυτά που συγκρούστηκαν δεν θέλουμε να τα λάβουμε υπ'όψιν, οπότε τα "διαγράφουμε"
        a_collided->velocity = -1;   //αρνητικό για να το αγνοούμε
        b_collided->velocity = -1;   //αρνητικό για να το αγνοούμε
        for(auto it = A.begin(); it != A.end(); ++it){
            if (it->velocity > 0) {
                old_iterA = it;
                break;
            }
        }
        for (auto it = B.begin(); it != B.end(); ++it){
            if (it->velocity > 0) {
                old_iterB = it;
                break;
            }
        }
    }
    return 0;
}

p_ITER furthest_advanced_particle(p_VEC& A, LD time){

    auto start = A.begin();

    LD position = (time-start->time)*start->velocity;

    auto max_position = start;

    for (auto it = start; it != A.end(); ++it) {
        if (it->time <= time) {
            LD temp = (time - it->time) * it->velocity;

            if (temp > position) {
                position = temp;
                max_position = it;
            }
        }
    }

    return max_position;
}

PAIR two_furthest_advanced_particles(p_VEC& A, LD time){

    auto start = A.begin();

    LD position = (time-start->time)*start->velocity;
    LD sec_pos = (time-start->time)*start->velocity;

    auto max_pos = start, second_max_pos = start;

    for (auto it = start; it != A.end(); ++it) {
        if (it->time <= time) {
            LD temp = (time - it->time) * it->velocity;

            if (temp > position) {
                second_max_pos = max_pos;
                sec_pos = position;
                position = temp;
                max_pos = it;
            } else if (temp > sec_pos) {
                second_max_pos = it;
                sec_pos = temp;
            }
        }
    }

    return make_pair(max_pos,second_max_pos);
}

PAIR find_collision_2(p_VEC& A, p_VEC& B, LD t_lower, LD t_upper, long L) {
    //cout << "Searching for collision in " << t_lower << "-" << t_upper << endl;

    p_ITER upper_furthest_advanced_a_first;
    upper_furthest_advanced_a_first = furthest_advanced_particle(A, t_upper);

    p_ITER upper_furthest_advanced_b_first;
    upper_furthest_advanced_b_first = furthest_advanced_particle(B, t_upper);

    LD tA = upper_furthest_advanced_a_first->time;
    LD vA = upper_furthest_advanced_a_first->velocity;
    LD tB = upper_furthest_advanced_b_first->time;
    LD vB = upper_furthest_advanced_b_first->velocity;

    if ( t_upper == (LD)(L +  tA * vA + tB * vB) / ( vA + vB) ) {
        //cout << "Τα πρώτα 2 συγκρούστηκαν" << endl;
        return make_pair(upper_furthest_advanced_a_first, upper_furthest_advanced_b_first);
    }

    LD  t_middle = (t_lower+t_upper)/2;    //χωρίζουμε το χρόνο στα 2, θα δούμε αν η κρούση έγινε τότε, πριν ή μετά
    p_ITER a_furthest, a_second_furthest;     //βρίσκουμε το πιο προχωρημένο Α σωματίδιο εκείνη τη στιγμή
    p_ITER b_furthest, b_second_furthest;     //αντίστοιχα για τα Β σωματίδια

    PAIR furthest_a_particles, furthest_b_particles;
    furthest_a_particles = two_furthest_advanced_particles(A, t_middle);
    furthest_b_particles = two_furthest_advanced_particles(B, t_middle);

    a_furthest = furthest_a_particles.first;
    a_second_furthest = furthest_a_particles.second;

    b_furthest = furthest_b_particles.first;
    b_second_furthest = furthest_b_particles.second;

    //cout << "Δεν συγκρούστηκαν τα πρώτα 2" << endl;
    //cout << "First a: " << a_furthest << " Second a: " << a_second_furthest << " First b: " << b_furthest << " Second b: " << b_second_furthest << endl;
    auto a1 = (t_middle-a_furthest->time)*a_furthest->velocity;

    auto a2 = (t_middle-a_second_furthest->time)*a_second_furthest->velocity;

    auto b1 = L-(t_middle-b_furthest->time)*b_furthest->velocity;

    auto b2 = L-(t_middle-b_second_furthest->time)*b_second_furthest->velocity;

    if ( a1 < b1 ) {
        //cout << "Δεν έχει γίνει ακόμα σύγκρουση" << endl;
        return find_collision_2(A, B, t_middle, t_upper, L);  //δεν έχει γίνει ακόμα σύγκρουση
    }
    else if ( (a2 > b1) || (a1 > b2) ) {
        //cout << "Δεν ξέρω ποιο από τα δύο έχει συγκρουστεί" << endl;
        return find_collision_2(A, B, t_lower, t_middle, L);
    }
    else {
        return make_pair(a_furthest, b_furthest);
    }
}

void read_file(FILE* fp, long& particles, long& length, long& max_collisions, p_VEC& canon_A, p_VEC& canon_B){
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

void read_stdin(long& particles, long& length, long& max_collisions, p_VEC& canon_A, p_VEC& canon_B){
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

long read_long() {
    long d = 0L, x = 0L;
    char c;

    while (1)  {
        if (bpos >= bsize) {
            bpos = 0;
            if (feof(stdin))
                return x;
            bsize = (long) fread(buffer, 1, BSIZE, stdin);
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

long read_long(FILE* fp) {
    long d = 0L, x = 0L;
    char c;

    while (1)  {
        if (bpos >= bsize) {
            bpos = 0;
            if (feof(fp))
                return x;
            bsize = (long) fread(buffer, 1, BSIZE, fp);
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