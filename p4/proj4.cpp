#include <iostream>
#include <fstream>//ifstream
#include <sstream>//stringstream
#include <vector>
using namespace std;

void readFile(string filename,stringstream &ss);
vector<int> convertToInts(stringstream &T, int &alphabetSize);
void printVector(vector<int> v)
{
  cout << v[0];
  for(int i=1;i<v.size();i++)
    cout << " " << v[i];
  cout << endl;
};
void tableA(vector<int> &A, vector<int> &T)
{
  for(int i=0;i<T.size();i++)
  {
    A[T[i]]=A[T[i]]+1;
  }

}
void tableC(vector<int> &C, vector<int> &A)
{
  for(int i=1;i<A.size();i++)
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

void SAIS(vector<int> &T, vector<int> &SA, int alphabetSize)
{
  vector<int> A(alphabetSize,0);
  vector<int> B(alphabetSize,0);
  vector<int> C(alphabetSize,0);
  int Tsize=T.size();

  tableA(A,T);
  cout << "A: ";
  printVector(A);

  tableC(C,A);
  cout << "C: ";
  printVector(C);

  tableB(B,A,Tsize);
  cout << "B: ";
  printVector(B);

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
  cout << "t: ";
  for(int i=0;i<t.size();i++)
  {
    cout << t[i] << " ";
  }

  cout << endl;
  cout << "SA: ";
  printVector(SA);
/********Step 1, sort all LMS-substrings of T in O(n) time *******/
  for(int i=0; i<B.size();i++)
  {
    B[i]=C[i];
  }
  cout << "(step1) B: ";
  printVector(B);
  int i=0;
  int Ssize=SA.size();
  int p;
  cout << "size of SA: " << SA.size() << endl;
  cout << "size of B: " << B.size() << endl;
  cout << "size of T: " << T.size() << endl;
/*
  for(vector<int>::iterator it=SA.begin();it != SA.end(); ++it)
  {
    p=*it;
    if(p > -1){
      p=p-1;
      int j=T[p];
      j=B[T[p]];
      if(t[p]==0)
      {
        SA[j]=p;
        cout << "p: " << p <<  ", j: " << j << "--->";
        j=T[p];
        cout << j << endl;
        //B[j]=B[j]+1;
      }
    }
    printVector(SA);
    cout << endl;
  }
*/

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

  cout << endl;
  cout << "(step1) SA: ";
  printVector(SA);

};

int main()
{
/********  read in input file using cin  *******/
  string filename;
  stringstream T;
  cout << "please specify input file: ";
  cin >> filename;
  cout << endl;

  readFile(filename,T);

/******** convert the input string T into an array of ints ******/
  int alphabetSize=0;
  vector<int> S=convertToInts(T,alphabetSize);

/******* Output content of Suffix Array ********/
  vector<int> SA(S.size(),-1);//initialize SA to -1
  SAIS(S,SA,alphabetSize);

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
    ss << '$';
  }
  file.close();
  //return ss;
}

vector<int> convertToInts(stringstream &T, int &alphabetSize)
{
  vector<int>index(256,0);//will help find indexes for T
  vector<int>S;//holds indexes for string T

  //scan T for each char c
  char c;
  int name=1;
  while(T.get(c))
  {
    if(c != '$')
    {
     index[c]=name;
     S.push_back(c);//holds ASCII value to be used later
    }
  }
  S.push_back(0);//index value for $

  //scan index from L-to-R
  for(int i=0; i < index.size();i++)
  {
    if(index[i]>0)
    {
      index[i]=name++;
    }
  }
  //scan array of int S
  for(int i=0; i < S.size();i++)
  {
    S[i]=index[S[i]];
  }
  cout << "T: ";
  printVector(S);//ERROR CHECKING
  alphabetSize=name;
  return S;
}
