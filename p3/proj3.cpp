
#include <limits.h>
#include <iostream>
#include <string>
using namespace std;

void printB(const char *str,int B[],int index)
{
  //base case: if index >= 0
  if(index < 0){
    return;
  }
  printB(str,B,B[index]-1);
  for(int i=index; i>=B[index];--i)
  {
    cout << str[i];
  }
  cout << endl;

}
//calculates table P,C, and B for a given string and a size
void minPartition(const char *str, int n)
{
/***** You need three tables for this problem.*****/
//C[i]=number of cuts in the best palindrome parition
//B[i]=holds the index k for the best choice of C[i]
//P[i][j]=truth table for either a palindrome or not
	int C[n];
  int B[n];
	bool P[n][n];

/********* Calculate table P   ***************/
//P[i][j]=true if i=j
	for (int i=0; i<n; i++)
	{
		P[i][i] = true;
	}

//L is the length of substring in character array
	for (int L=2; L<=n; L++)
	{
    int j;
		//set different index for substring L
		for (int i=0; i<n-L+1; i++)
		{
			j = i+L-1;//end index

			// If L = 2, we compare two characters at each end
      //Else check characters at each end and palindrome table
			if (L == 2)
				P[i][j] = (str[i] == str[j]);
			else
				P[i][j] = (str[i] == str[j]) && P[i+1][j-1];
		}
	}

/****** Calculate table C and B ******/
	for (int i=0; i<n; i++)
	{
    //Condition 1: C[i]=0 if i=0
    if(i == 0){
      C[i] = 0;
      B[i] = 0;
    }
    //Condition 2: C[i]=0 if P[0,i]=TRUE, and in this case B[i]=0
		else if (P[0][i] == true){
			C[i] = 0;
      B[i] = 0;
    }
    //Condition 3: C[i]=min(C[k] +1: p[k+1,i]=TRUE) if i>0
		else
		{
			C[i] = INT_MAX;//macro that specifies that an integer variable cannot store any value beyond this
			for(int k=0;k<i;k++)
			{
				if(P[k+1][i] == true && C[k]+1<C[i]){
					C[i]=1+C[k];
          B[i]=k + 1;
        }
			}
		}
	}
  /******  for debugging purposes, print tables  *******/
  /*cout << "printing B and C: " << endl;
  for(int c=0;c<n;c++)
  {
    cout << B[c] << " ";
  }
  cout << endl;
  for(int c=0;c<n;c++)
  {
    cout << C[c] << " ";
  }
  cout << endl;
  */
	// print the min cut value for str[0..n-1]
  printB(str,B,n-1);
	//cout << C[n-1] << endl;
}

int main()
{
   // 1) reads string from standard input
   string s;
   cin >>s;
   const char *str=s.c_str();
   int size=s.size();
   // 2) calculate table P,C, and B for backtracking
   minPartition(str,size);
   //print out minimum number of cuts
   return 0;
}
