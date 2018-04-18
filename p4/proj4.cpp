#include <iostream>
#include <fstream>//ifstream
#include <sstream>//stringstream
#include <vector>
using namespace std;

void SAIS();

void readFile(string filename,stringstream &ss);
void convertToInts(stringstream &T);


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
  convertToInts(T);

/******* Output content of Suffix Array ********/

  return 0;
}

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

void convertToInts(stringstream &T)
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

  for(int i=0; i < S.size();i++)
  {
    cout << S[i] << " ";
  }

  //scan index from L-to-R
  for(int i=0; i < index.size();i++)
  {
    if(index[i]>0)
    {
      index[i]=name++;
    }
    cout << index[i] << " ";
  }
  cout << endl;
  //scan array of int S
  for(int i=0; i < S.size();i++)
  {
    S[i]=index[S[i]];
    cout << S[i] << " ";
  }

  cout << endl;
}
