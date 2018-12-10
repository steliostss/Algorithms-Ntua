#include <iostream> 
#include <vector> 
#include <algorithm>
using namespace std;

typedef vector<long long> VEC ;
long long int a,b,c,N;
long long niknik=0;

VEC ilia,leya;

bool bad(long long l1,long long l2,long long l3)
{
        return (ilia[l1]-ilia[l2])*(leya[l3]-leya[l1])<(ilia[l1]-ilia[l3])*(leya[l2]-leya[l1]);
}
void add(long long int m,long long int b)
{
        ilia.push_back(m);
        leya.push_back(b);
        while (ilia.size()>=3&&bad(ilia.size()-3,ilia.size()-2,ilia.size()-1))
        {
                ilia.erase(ilia.end()-2);
                leya.erase(leya.end()-2);
        }
}


long long int solution (VEC& s){
	VEC vi(N,0);
	vi[0] = a*(s[0]*s[0]) +  b*(s[0]) +c;
	add(-2*a*s[0], vi[0]+ a*(s[0]*s[0]) - b*s[0]);

	for ( long long int i=1; i<N; ++i){
		vi[i]= a*(s[i]*s[i]) +  b*(s[i]) +c;

		if (niknik >=ilia.size())
			niknik = (long long ) ilia.size()-1;

		//int next=ilia[niknik+1]*s[i] + leya[s[i]];

		//int cur=ilia[niknik]*s[i] + leya[s[i]];


		while ( niknik < ilia.size()-1 &&
                (ilia[niknik+1]*s[i]+leya[niknik+1] > ilia[niknik]*s[i]+leya[niknik])){
			niknik++;
		}
		long long val =  ilia[niknik]*s[i]+leya[niknik];
		// exei vrethei i megaliteri eutheia 
		vi[i]= max( vi[i],vi[i]+val);
		add(-2*a*s[i], vi[i]+ a*(s[i]*s[i]) - b*s[i]);
	}
	return vi[N-1];
}




int main(int argc, char** argv)
{
//    FILE* file;
    FILE* file = fopen (argv[1], "r");
    long long int i;
//  file = fopen("input1.txt", "r");
  //scanf("%lld",&N);

  fscanf (file, "%lld\n", &N);
  if (N==0) return 0;
/*scanf("%lld",&a);
scanf("%lld",&b);
scanf("%lld",&c);*/

  fscanf(file, "%lld ", &a);

  fscanf(file, "%lld ", &b);

  fscanf(file, "%lld", &c);
  VEC x(N, 0);
  VEC s(N,0);
   fscanf(file,"%lld ", &x[0]);
//scanf("%lld",&x[0]);
  s[0]=x[0];
 
  for (i=1; i<N; i++)
    {
	fscanf(file,"%lld ", &x[i]);
	//scanf("%lld",&x[i]);
	s[i]=s[i-1]+x[i];
	}

	long long int max = solution(s);
	printf("%lld\n", max);
	return 0;

}

