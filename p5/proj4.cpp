#include <iostream>
#include <fstream>//ifstream
#include <sstream>//stringstream
#include <vector>
using namespace std;

void readFile(string filename,stringstream &ss);
vector<int> convertToInts(stringstream &S, int &alphabetSize);
void printVector(vector<int> v)
{
  for(unsigned int i=0;i<v.size();i++)
    cout << v[i] << " ";
  cout << endl;
  /*
  for(unsigned int i=0;i<v.size(); i++)
    cout << "i=" << i << ": " << v[i] << endl;
  */
}
void tableA(vector<int> &A, vector<int> &T);
void tableC(vector<int> &C, vector<int> &A);
void tableB(vector<int> &B, vector<int> &A, int Tsize);

void SAIS(vector<int> &T, vector<int> &SA, int alphabetSize)
{
  vector<int> A(alphabetSize,0);
  vector<int> B(alphabetSize,0);
  vector<int> C(alphabetSize,0);
  int Tsize=T.size();

  tableA(A,T);

  tableC(C,A);

  tableB(B,A,Tsize);

/********* Step 0, assign type of each suffix in T *******/
  vector<bool> t(T.size());//L-type=0;S-type=1;
  t[T.size()-1]=1;//initialize $ to S-type=1;
  for(int i=T.size()-2;i > -1;i--)//Scan T from Right-To-Left
  {
    if(T[i] > T[i+1])//if left > right, L-type
    {
      t[i]=0;
      if(t[i+1]==1){
        SA[ B[ T[i+1] ] ]=i+1;
        B[ T[i+1] ] = B[ T[i+1] ] - 1;
      }
    }
    else if(T[i]<T[i+1])//if left < right, S-type
      t[i]=1;
    else //if left==right, same-types
      t[i]=t[i+1];
  }

/********Step 1, sort all LMS-substrings of T in O(n) time *******/
  for(unsigned int i=0; i<B.size();i++)
  {
    B[i]=C[i];
  }

  for(unsigned int i=0;i<SA.size();i++)
  {
    int p=SA[i];
    if(p > 0 || i==0)
    {
      p=p-1;
      int j=T[p];
      j=B[T[p]];
      if(t[p]==0)
      {
        SA[j]=p;
        j=T[p];
        B[j]=B[j]+1;
      }
    }
  }


  /**** Reset the vlues of B to point to the End of c-buckets ****/
  B[B.size()-1]=SA.size()-1;
  for(int i=B.size()-2;i>0;i--)
  {
    B[i]=B[i+1]-A[i+1];
  }

  /**** Induce the order of S-type suffixes from ordered L-type suffixes ****/
  vector<int> L(SA.size());
  for(int i=SA.size()-1;i>-1;i--)
  {
    int p=SA[i];
    if(p>-1)
    {
      if(p==0){
        if(t[T.size()-1]==1)
        {
          SA[B[T[T.size()-1]]]=T.size()-1;
          B[T[T.size()-1]]=B[T[T.size()-1]]-1;

          if(t[T.size()-2]==0)
          {
            L[B[T[p]]]=1;
          }

        }
      }
      else if(p==1)
      {
        if(t[p-1]==1)
        {
          SA[B[T[p-1]]]=p-1;
          B[T[p-1]]=B[T[p-1]]-1;


          if(t[T.size()-1]==0)
          {
            L[B[T[p-1]]]=1;
          }

        }

      }
      else
      {
        if(t[p-1]==1)
        {
          SA[B[T[p-1]]]=p-1;
          B[T[p-1]]=B[T[p-1]]-1;

          if(t[p-2]==0)
          {
            L[B[T[p-1]]]=1;
          }
        }
      }
    }
  }
  printVector(SA);
  //printVector(L);
}

int main()
{
/********  read in input file using cin  *******/
  //string filename;
  stringstream ss;
  //cout << "please specify input file: ";
  //cin >> filename;
  //cout << endl;

  //readFile(filename,ss);

  string line;
  while(getline(cin,line))
  {
    ss<<line;
  }
  //ss<<'$';

/******** convert the input string T into an array of ints ******/
  int alphabetSize=0;
  vector<int> T=convertToInts(ss,alphabetSize);

/******* Output content of Suffix Array ********/
  vector<int> SA(T.size(),-1);//initialize SA to -1
  SAIS(T,SA,alphabetSize);

  return 0;
}






/********************** HELPER FXNS **********************/
void readFile(string filename,stringstream &ss)
{
  //stringstream ss;
  ifstream file(filename.c_str());
  if(file.is_open())
  {
    string line;
    while( getline( file,line))
    {
      ss << line;
    }
    //ss << '$';
  }
  file.close();

  //return ss;
}

vector<int> convertToInts(stringstream &S, int &alphabetSize)
{
  vector<int>index(256,0);//will help find indexes for T
  vector<int>T;//holds indexes for string T

  //scan T for each char c
  char c;
  int name=1;
  while(S.get(c))
  {
     index[c]=name;
     T.push_back(c);//holds ASCII value to be used later
  }
  //scan index from L-to-R
  for(unsigned int i=0; i < index.size();i++)
  {
    if(index[i]>0)
    {
      index[i]=name++;
    }
  }
  //scan array of int T
  for(unsigned int i=0; i < T.size();i++)
  {
    T[i]=index[T[i]];
  }

  T.push_back(0);
  alphabetSize=name;
  return T;
}
void tableA(vector<int> &A, vector<int> &T)
{
  for(unsigned int i=0;i<T.size();i++)
  {
    A[T[i]]=A[T[i]]+1;
  }

}
void tableC(vector<int> &C, vector<int> &A)
{
  for(unsigned int i=1;i<A.size();i++)
  {
    C[i]=C[i-1]+A[i-1];
  }
}
void tableB(vector<int> &B, vector<int> &A, int Tsize)
{
  B[A.size()-1]=Tsize-1;
  for(int i=A.size()-2;i>0;i--)
  {
    B[i]=B[i+1]-A[i+1];
  }
}
