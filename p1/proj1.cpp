/*
* File: proj1.cpp
* Author: Carlos A Perez, Elena Harris(select, mbst)
* Class: CSCI 550
* Term: Spring 2018
*/
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <math.h>
//#include <string>

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
void MBST( vector<list<edge> > &adjA,
                vector<list<edge> > &adjD);
int select(vector<int> &v, int start, int fin, int k);
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
  //we have to collect weights into array A

  //we have to find median m of A->use select
  //collects edges with w<=m
  //Run BFS. is H connected? Yes, call camerini on H
  //No, collapse G into G' and recursively call camerini on G'
  //^^^^all this in MBST File


  return 0;
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
                adjD[u].push_front(*it);//add edge(u,v)

                int v=it->getV();
                it=adjA[v].begin();
                adjD[v].push_front(*it);//add edge(v,u)
                break;
              }
            }

        /***********   Collect weights of edges **********/
        vector<int> weights(m, 0);
        //You need to write this function:
        collect_weights(adjA, weights);



        /*******   Find the median of weights *********/
        int k = m >> 1;//divide by 2
        if(m % 2 == 0)
                k--;
        int median_weight = select(weights, 0, m-1,k);
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


        /******* Find connected components in adjB
                in linear time
         ***************************************/
        vector<short int> cc(adjB.size());
        int total_cc = connected(adjB, cc);//number of comp



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

                Rename edges according to the names
                of new supervertices (0, 1,.., total_cc-1)
                call recursively MBST on adjC:

				MBST(adjC, adjD);

                When call returns,
                Add edges of adjB (use original names)
                into adjD
            *****************************************/

                return;
        }//else not connected
}//MBST recursive


/***********************************************************/

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
