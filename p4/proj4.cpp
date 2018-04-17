#include <iostream>
#include <fstream>//ifstream
#include <sstream>//stringstream
using namespace std;

int main()
{
  /*******  read in input file using cin  *******/
  string filename;
  ifstream file;
  cout << "please specify input file: ";
  cin >> filename;
  cout << endl;
  file.open(filename.c_str());

  string T;
  if(file.is_open())
  {
    stringstream ss;
    string line;
    while( getline( file, line) )
    {
      ss << line;
    }
    T=ss.str();
  }
  cout << T << endl;







  file.close();
  return 0;
}
