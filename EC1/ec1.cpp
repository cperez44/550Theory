#include <iostream>
#include <vector>
#include <list>
using namespace std;

class path
{
  public:
  path(){};
  path(int U,int V,int W)
  {u=U;v=V;w=W;}
  int getV(){return v;}
  int getW(){return w;}
  private:
  int u;
  int v;
  int w;//maintance fee per year
};
void printList(vector<list<path> > &adjList, int N);
int annualCost(vector<list<path> > &R, vector<list<path> > &S, int N, int w, int cost);
int main()
{
  int N,M;//Size of each network
  int a,b;//ID of stations
  int w;//Path weight or maintanence fee per year
  vector<list<path> > Red;
  vector<list<path> > Star;
  cout << "Enter total number of stations in RedNova's network:" << endl;
  cin >> N;//the totaul number of stations in RedNova's wormhole
  Red.resize(N);
  Star.resize(N);
  for(int i=0;i<(N-1);i++)
  {
    cin >> a;
    cin >> b;
    cin >> w;
    path p1(a,b,w);
    path p3(b,a,w);
    Red[a].push_front(p1);
    Red[b].push_front(p3);
  }
  cout << "Enter total number of stations in StarTrace's network:" << endl;
  cin >> M;
  for(int i=0;i<(M-1);i++)
  {
    cin >> a;
    cin >> b;
    cin >> w;
    path p2(a,b,w);
    path p4(b,a,w);
    Star[a].push_front(p2);
    Star[b].push_front(p4);
  }

  cout << "/////// REDNOVA NETWORK //////" << endl;
  printList(Red,N);
  cout << "/////// STARTRACE NETWORK /////" << endl;
  printList(Star,N);

  int A,B,C,D,w1,c1,w2,c2;
  cout << "Wormhole 1" << endl;
  cin >> A;
  cin >> C;
  cin >> w1;
  cin >> c1;
  cout << "Sum" << A << "&" << C << ": " << annualCost(Red,Star,N,w1,c1) << endl;

  cout << "Wormhole 2" << endl;
  cin >> B;
  cin >> D;
  cin >> w2;
  cin >> c2;
  cout << "Sum" << B << "&" << D << ": " << annualCost(Star,Red,N,w2,c2) << endl;
  return 0;
}
/*
path sum3(vector<list<path> > &R, vector<list<path> > &S, int N, int w, int cost)
{
  path p;
  for(list<path>::iterator it =R[i].begin(); it !=R[i].end();it++)
  {
    if(i<(*it).getV())
      sum=sum+(*it).getW();
  }

}
*/
int annualCost(vector<list<path> > &R, vector<list<path> > &S, int N, int w, int cost)
{
  int sum=0;
  for(int i=0;i<N;i++)
  {
    for(list<path>::iterator it =R[i].begin(); it !=R[i].end();it++)
    {
      if(i<(*it).getV())
        sum=sum+(*it).getW();
    }
    for(list<path>::iterator it =S[i].begin(); it !=S[i].end();it++)
    {
      if(i<(*it).getV())
        sum=sum+(*it).getW();
    }
  }
  sum=sum+w;
  sum = (10*sum) + cost;
}
void printList(vector<list<path> > &adjList, int N)
{
  for(int i=0;i<N;i++)
  {
    cout << i << ": ";
    for(list<path>::iterator it =adjList[i].begin(); it !=adjList[i].end();it++)
    {
      cout << "(" << i << "," << (*it).getV() << ","<<(*it).getW() << "), ";
    }
    cout << endl;
  }
}
