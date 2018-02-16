/*
* File: proj1.cpp
* Author: Carlos A Perez
* Class: CSCI 550
* Term: Spring 2018
*/
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class edge
{
  public:
  edge(){};
  edge(int V,int W, int uOrigin, int vOrigin)
  {v=V;w=W;u_original=uOrigin;v_original=vOrigin;}
  int getV(){return v;}
  int getW(){return w;}
  int getU_origin(){return u_original;}
  int getV_origin(){return v_original;}

  private:
  int v;
  int w;
  int u_original;
  int v_original;

};

int main()
{
  int N,M;
  int x,y,w;
  vector<list<edge> > adjList;
  cin >> N;
  cin >> M;
  adjList.resize(N);
  for(int i=0;i<M;i++)
  {
    cin >> x;
    cin >> y;
    cin >> w;
    if(x<N && y<N){
      edge e(y,w,x,y);
      adjList[x].push_front(e);
      edge e2(x,w,y,x);
      adjList[y].push_front(e2);
    }
    else
      cout << "Not a valid edge" << endl;
  }


  return 0;
}
