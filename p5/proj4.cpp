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
void resetB(vector<int> &B, vector<int> &A, vector<int> &SA);
bool identical(vector<int> &T, vector<bool> t,int current, int previous);

void SAIS(vector<int> &T, vector<int> &SA, int alphabetSize, int iteration)
{
  //BASE CASE
  cout << "Iteration " << iteration << endl;
  cout << "T at iteration " << iteration << endl;
  printVector(T);
  bool different=false;
  int max=0;
  //if(T.size() != 1)
  //{
    for(unsigned int i=0;i<T.size();i++)
    {
      if(T[i]>max)//if all are 1, then all are same characters excluding $
        max=T[i];
    }
  //}
  //cout << "asize: " << alphabetSize << " ;;;; " << "max: "<< max << endl;
  if( alphabetSize==(max+1) && T.size()==(max+1) ){//true if ALL characters different, no reps
    for(unsigned int i=0;i<T.size();i++)
    {
      SA[ T[i] ] = i;
    }
    cout << endl;
    return;
  }
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
  resetB(B,A,SA);

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

          if(t[T.size()-2]==0)
          {
            L[B[T[T.size()-1]]]=1;
          }
          B[T[T.size()-1]]=B[T[T.size()-1]]-1;
        }
      }
      else if(p==1)
      {
        if(t[p-1]==1)
        {
          SA[B[T[p-1]]]=p-1;

          if(t[T.size()-1]==0)
          {
            L[B[T[p-1]]]=1;
          }
          B[T[p-1]]=B[T[p-1]]-1;
        }

      }
      else
      {
        if(t[p-1]==1)
        {
          SA[B[T[p-1]]]=p-1;

          if(t[p-2]==0)
          {
            L[B[T[p-1]]]=1;
          }
          B[T[p-1]]=B[T[p-1]]-1;
        }
      }
    }
  }
  cout << "LMS prefixes are sorted." << endl;
  cout << "SA at iteration " << iteration << endl;
  printVector(SA);

/** Step 2: Give each LMS-substring of T a name and construct shortened str T1 **/
  vector<int> T1;
  vector<int> N(T.size(),-1);//initialize N[0...n]=-1
  //a)
  N[T.size()-1]=0;//initialize N[n]=0, m=0 for $
  int m=0;
  int previous=SA[0];//initially, previous is set to SA[0]
  for(unsigned int i= 1; i<SA.size();i++)
  {
    if(L[i]==1)
    {
      int p=SA[i];
      if(identical(T,t,p,previous)==true){
        N[p]=m;
        previous=SA[i];
      }
      else
      {
        m++;
        N[p]=m;
        previous=SA[i];
      }
    }
  }
  //c) Fill in T1
  //cout << "N: ";
  //printVector(N);
  for(unsigned int i=0;i<N.size();i++)
  {
    if(N[i] != -1)
      T1.push_back(N[i]);
  }
  cout << "T1 at iteration " << iteration << endl;
  printVector(T1);
/****** Step 3: Call recursively SA-IS on T1 to calculate the SA1 for T1 *****/
  vector<int> SA1(T1.size());
  cout << "Iteration " << iteration << ". Recursive call on T1." << endl;
  cout << "********************************************" << endl;
  SAIS(T1,SA1,m+1,iteration+1);

/*************** Step 4: Induce SA from SA1 in O(n) time. ********************/
  //resetB(B,A,SA);//a) reset B to point to END of buckets
  /*
  for(unsigned int i=0;i<SA.size();i++)//b) reset SA all to -1
    SA[i]=-1;
    */
  cout << "********************************************" << endl;
  cout << "After recursive call inside iteration " << iteration << endl;
  cout << "SA1 at iteration " << iteration << " (after recursive call) is:" << endl;
  printVector(SA1);
  cout << "SA at the end of SAIS function just before the return at iteration " << iteration << endl;
  printVector(SA);
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
  SAIS(T,SA,alphabetSize,1);

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
void resetB(vector<int> &B, vector<int> &A, vector<int> &SA)
{
  B[B.size()-1]=SA.size()-1;
  for(int i=B.size()-2;i>0;i--)
  {
    B[i]=B[i+1]-A[i+1];
  }
}
bool identical(vector<int> &T, vector<bool> t,int current, int previous)
{
  bool ident=true;
  if(T[current] != T[previous] || t[current] != t[previous])//this will prevent comparing with $(the end one, not the one in the string)
  {
    ident=false;//fails if first characters not the same in char and type
  }
  else if(T[current+1] != T[previous +1] || t[current+1] != t[previous+1]){
    ident=false;
  }
  else
  {
    current++;
    previous++;
    while(t[current]<=t[current-1] && t[previous]<=t[previous-1])
    {
        if(T[current] != T[previous])
        {
          ident=false;//will execute if the characters are not the same
        }
        current++;
        previous++;
    }
    if(T[current] != T[previous] || t[current] != t[previous])
    {
      ident=false;//final check if loop made it to the end
    }
  }
  return ident;
}
