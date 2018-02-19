#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <math.h>
using namespace std;

class edge
{
  public:
  edge(){};
  edge(int V,int W, int uOrigin, int vOrigin)
  /*: v(V),w(W),u_original(uOrigin),v_original(vOrigin)*/
  {v=V;w=W;u_original=uOrigin;v_original=vOrigin;}
  /*edge(edge e)
  {v=e.getV();w=e.getW();u_original=e.getU_origin();v_orginal=e.getV_origin();}*/
  int getV(){return v;}
  int getW(){return w;}
  void setV(int s){v=s;}
  int getU_origin(){return u_original;}
  int getV_origin(){return v_original;}

  private:
  int v;
  int w;
  int u_original;
  int v_original;

};
void printWeights(vector<int> &weights)
{
  cout << "Weights: ";
  for(int i=0;i<weights.size(); i++)
  {
    cout << weights[i] << ", ";
  }
  cout << endl;
}
void BFS(vector<list<edge> > &adjB, int source,
            short int component,vector<short int> &cc);
int connected(vector<list<edge> > &adjB, vector<short int> &cc);
void select_smallest(vector<list<edge> > &adjA,
                vector<list<edge> > &adjB, int median_weight);
void collect_weights(vector<list<edge> > &adjA, vector<int> &weights);
void MBST( vector<list<edge> > &adjA,
                vector<list<edge> > &adjD);
int select(vector<int> &v, int start, int fin, int k);
void printList(vector<list<edge> > &adjList, int N);

int main()
{
  int N,M;
  int x,y,w;
  vector<list<edge> > adjList;

  vector<list<edge> > tempA;
  vector<list<edge> > tempD;

  cin >> N;
  cin >> M;
  adjList.resize(N);

  tempA.resize(N);
  tempD.resize(N);
  for(int i=0;i<M;i++)
  {
    cin >> x;
    cin >> y;
    cin >> w;
    if(x<N && y<N){
      edge e(y,w,x,y);
      adjList[x].push_front(e);
      tempA[x].push_front(e);

      edge e2(x,w,y,x);
      adjList[y].push_front(e2);
      tempA[y].push_front(e2);
    }
    else
      cout << "Not valid edge" << endl;
  }

  MBST(tempA,tempD);
  //printList(tempD,N);
  return 0;
}

int connected(vector<list<edge> > &adjB, vector<short int> &cc)
{
  //will call BFS on indexes from vector cc
  short int component=0;
  int flag=1;//flag will be used to stop loop of BFS
  for(int i=0;i<cc.size();i++)
  {
    cc[i]=-1;//sentinel value
  }

  for(int i=0;i<cc.size();i++)
  {
    if(cc[i]==-1)
    {
      BFS(adjB,i,component,cc);
      component++;
    }
  }
  return component;
  //a connected component (cc) will be array 1 and 0
  //0=component; 1=no component;
  //BFS will return 0 if component for node is connected
  //BFS will return 1 if not connected
  //we will scan array and count how many 1's there are
  //count will be total_cc
}

void BFS(vector<list<edge> > &adjB, int source,
            short int component,vector<short int> &cc)
{

  list<int> q;
  cc[source]=component;
  q.push_back(source);
  while(q.empty() != true)
  {
    source=q.front();
    q.pop_front();

    for(list<edge>::iterator it=adjB[source].begin();it != adjB[source].end();++it)
    {
      int v=it->getV_origin();
      if(cc[v]==-1)
      {
        cc[v]=component;
        q.push_back(v);
      }
    }

  }

}

/*************************************************************/
void MBST( vector<list<edge> > &adjA,
                vector<list<edge> > &adjD){

        //Count the number of edges in adjA
        int m = 0;
        int size = adjA.size();

        for(int i = 0; i < size; i++){
                m += adjA[i].size();
        }
        m = m >> 1;//divide by 2, each edge occurs twice in Adj
        //BASE case, if number of edges is 1, return
        //after adding the first edge to adjD
        if(m == 1){
            for(int u=0; u<size;u++)
            {
              if(adjA[u].size() != 0 )
              {
                list<edge>::iterator it=adjA[u].begin();
                it->setV(it->getV_origin());
                adjD[u].push_front(*it);//add edge(u,v)

                int v=it->getV();
                it=adjA[v].begin();
                adjD[v].push_front(*it);//add edge(v,u)
                break;
              }
            }
            //Here you need to add edge to adjD
            //from adjA (add original name of the edge)

          //.................................

            return;
        }

        /***********   Collect weights of edges **********/
        vector<int> weights(m, 0);
        //You need to write this function:
        collect_weights(adjA, weights);
        printWeights(weights);


        /*******   Find the median of weights *********/
        int k = m >> 1;//divide by 2
        if(m % 2 == 0)
                k--;
        int median_weight = select(weights, 0, m-1,k);
        cout << "Median weight: " << median_weight << endl;
        //Function "select" is provided


        /*****  Collect edges with weights <= median_weight
                from adjA into adjB
                Erase an edge from adjA:
                it takes O(1) to erase (use erase) from
                a list
        *************************************************/
        vector< list<edge> > adjB(adjA.size());//smallest edges

        //You need to write this function:
        select_smallest(adjA, adjB, median_weight);
        cout << "adjA ---------------------------" << endl;
        printList(adjA,adjA.size());
        cout << "adjB ---------------------------" << endl;
        printList(adjB,adjB.size());

        /******* Find connected components in adjB
                in linear time
         ***************************************/
        vector<short int> cc(adjB.size());
        int total_cc = connected(adjB, cc);//number of comp
        cout << "connected components: " << cc[0];
        for(int i=1;i<cc.size();i++)
        {
          cout << ", "<< cc[i];
        }
        cout << endl;
        cout << "total_cc: " << total_cc << endl;

        /**********     If connected (only one component)
                we don't need edges of A anymore
                just call recursively MBST and return
                after the recursive call returns
                i.e. do nothing after recursive call returns
        ****************************************/

        if(total_cc == 1){
                MBST(adjB, adjD);
                return;
        }else{

            /******     If not connected,
                contract connected components
                construct adjC from adjA and
                super vertices (each represents a
                connected component)
                */
            vector< list<edge> > adjC(adjA.size());
            for(int i=0;i<adjA.size();i++)
            {
              for(list<edge>::iterator it=adjA[i].begin();it != adjA[i].end();
                    ++it)
              {
                int u=getU_origin();
                int v=getV_origin();
                adjC[i]
              }
            }

                /*

                Rename edges according to the names
                of new supervertices (0, 1,.., total_cc-1)
                call recursively MBST on adjC:
                */

				//MBST(adjC, adjD);
                /*
                When call returns,
                Add edges of adjB (use original names)
                into adjD

                for(int u=0; u<size;u++)
                {
                  for(list<edge>::iterator it=adjB[u].begin();
                    it != adjB[u].end();++it)
                  {
                    it->setV();//sets v to original name
                    it->setV=it->getV_origin;
                  }


                }
                */


                return;
        }//else not connected


}//MBST recursive

/***********************************************************/

void select_smallest(vector<list<edge> > &adjA,
                vector<list<edge> > &adjB, int median_weight)
{
  int size=adjA.size();
  for(int u=0;u<size;u++)
  {
    list<edge>::iterator i=adjA[u].begin();
    while(i != adjA[u].end())
    {
      if(i->getW() <= median_weight)
      {
        adjB[u].push_front((*i));//copy edge from A to B
        i=adjA[u].erase(i);//erase edge from A, return iterator at new edge
      }
      else
        i++;
    }
  }
}


void collect_weights(vector<list<edge> > &adjA, vector<int> &weights)
{
  int size=adjA.size();
  int index=0;
  for(int u=0;u<size;u++)
  {
    for(list<edge>::iterator i=adjA[u].begin(); i != adjA[u].end();i++)
    {
      if(u > i->getV_origin())
      {
        weights[index]=i->getW();
        index++;
      }
    }
  }
}

int select(vector<int> &v, int start, int fin, int k){

    int vsize = fin - start + 1;

    if(start == fin)
        return v[start];
    else if(start > fin)
        return -1;

	if(vsize <= 5){
		sort(v.begin() + start, v.begin() + fin + 1);

		return v[k];
	}

	int msize = ceil((double)vsize/5);

    vector<int> medians(msize, 0);
    int med_ind = 0;
    for(int i = start; i <= fin; i = i + 5){
        vector<int> temp(5, 0);
        int j = 0;
        for(; j < 5 && (i + j)<= fin; j++){
            temp[j] = v[i+j];
        }//for j
        if(j < 5)
            temp.resize(j);
        sort(temp.begin(), temp.end());
        if(j == 5)
            medians[med_ind++] = temp[2];
        else{
            int jmid = j >> 1;//divide by 2
            if(j % 2 == 0)
                jmid--;
            medians[med_ind++] = temp[jmid];

            }
    }//for i
    //so far we selected medians of n/5 groups of 5 elem
    int mid = msize >> 1; //divide by 2
    if((msize % 2) == 0)
        mid--;
    int x = select(medians, 0, msize - 1, mid);
    //partition v's elements around x
    //find x
    int indx = -1;
    for(int i = start; i <= fin; i++){
        if(v[i] == x){
            indx = i;
            break;
            }
    }//for i
    if(indx == -1)
        return -2;
    int t = v[start];
    v[start] = x;
    v[indx] = t;
    int i = start + 1, j = fin;
    while(i < j){
        if(v[i] > x && v[j] <= x){
            t = v[j];
            v[j] = v[i];
            v[i] = t;
            i++;
            j--;
        }//if
        else if(v[i] <= x){
            i++;
            if(i > fin){
                i--;
                break;
            }
            }
        else{
            j--;
            if(j == 0){
                j++;
                break;
            }
            }
    }//while partition
    int last = i;
    if(v[i] > x)
        last--;//last index that has less than or equal elemenents than x
//count how many elements are equal to x
    int count_equal = 0;
    for(int u = start; u <= last; u++){
        if(v[u] == x)
            count_equal++;
    }//for u

    if(k > (last - count_equal) && k <= last)
        return x;
    else if(last < k)
        return select(v, last + 1, fin, k);
    else
        return select(v, start, last, k);
}//select


//////  functions ///////////////
void printList(vector<list<edge> > &adjList, int N)
{
    for(int i=0;i<N;i++)
    {
      cout << i << ": ";
      for(list<edge>::iterator it =adjList[i].begin(); it !=adjList[i].end();it++)
      {
        cout <<(*it).getW() <<"(" << (*it).getU_origin()<< ","<<(*it).getV() << "), ";
      }
      cout << endl;
    }
}
