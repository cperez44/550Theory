/*
* file: hw1.cpp
* author: Carlos Perez
* class: CSCI 550
*
*/

#include <iostream>
#include <vector>

using namespace std;

class Graph{
  public:
  Graph(int size)
  {
  m_size=size;adjacencyList.resize(size);parent.resize(size);distance.resize(size);}
  void addEdge(int u,int v);
  void reset();
  void BFS(int s);
  void BFSAll();
  void maxDistance();
  int core();
  void printPath(int i);
  
  private:
  vector<vector<int> > adjacencyList;
  vector<int> parent;
  vector<int> distance;
  vector<int> longestD;
  int m_size;
  int u;
};
void Graph::addEdge(int u,int v){
  adjacencyList[u].push_back(v);
  adjacencyList[v].push_back(u);
}

void Graph::reset(){
  distance.clear();
  parent.clear();
  distance.resize(m_size);
  parent.resize(m_size);
}
void Graph::BFS(int s){
  for(int i=0; i< distance.size(); i++){
    distance[i]=1000;
    parent[i]=i;
  }
  distance[s]=0;
  vector<int> q;
  q.push_back(s);
  while(q.size() != 0){
    vector<int>::iterator it=q.begin();
    int u=*it;
    q.erase(q.begin());
    for(int i=0;i<adjacencyList[u].size();i++){
      int v=adjacencyList[u][i];
      if(distance[v]==1000){
        distance[v]=distance[u]+1;
        parent[v]=u;
        q.push_back(v);
      }
    }
  }
}
void Graph::maxDistance(){
  int max=0;
  for(int i=0;i<distance.size();i++){
    if(distance[i]>max){
      max=distance[i];
    }
  }
  longestD.push_back(max);
}
int Graph::core(){
  int u;
  int min=longestD[0];
  for(int i=0;i<longestD.size();i++){
    if(longestD[i]<min){
      min=longestD[i];
      u=i;
    }
  }
  return u;
}
void Graph::BFSAll()
{
  
  for(int i=0;i<adjacencyList.size();i++){
    BFS(i);
    maxDistance();
    reset();
  }
  
  u=core();
  BFS(u);
  for(int i=0;i<adjacencyList.size();i++){
    if(i != u){
      printPath(i);
      cout << endl;
    }
  }
}
void Graph::printPath(int i)
{
  if(parent[i]==u)
    cout << u;
  else
    printPath(parent[i]);
    cout << " " << i;
}
int main()
{
  int N;
  int u,v;
  
  cin >> N;
  if(N <= 0){
    cerr << "Error: graph is empty." << endl; 
  }
  Graph g(N);
  
  int i=0;
  while(i < (N-1) && i>=0){
    cin >> u;
    cin >> v;
    g.addEdge(u,v);
    i++;
  }
  g.BFSAll();
  return 0;
}
