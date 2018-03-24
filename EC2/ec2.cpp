#include <iostream>
#include <limits.h>
#include <vector>

using namespace std;

//helper, recursive function that will calculate revenue table for given prices
void maxRev(vector<int> prices,vector<int> &revenue,int n)
{
  if(n>prices.size())//base case
    return;
  //wll compare to unreachable number,
  int max_val=-1;
  //loop through revenue table
  //compare current max value with revenue up to n-i-1
  //set revenue at n to whichever comparison decides is bigger
  //recurse until base case reached
  //maxRev(prices,revenue,n+1);
}

int main()
{
  int N,p;//N= size; p=price
  cin >> N;
  vector<int> prices(N);//array of prices
  vector<int> revenue(N);//array to keep track of revenue
  revenue[0]=0;
  for(int i=0;i<N;i++)//Note: i is not representative of land area
  {
    cin >>p;
    prices[i]=p;
  }
  //call maxRev here
  maxRev(prices,revenue,1);
  cout << revenue[N] << endl;
  return 0;
}
