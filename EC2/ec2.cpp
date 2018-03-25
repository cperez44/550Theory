#include <iostream>
#include <vector>

using namespace std;

//helper, recursive function that will calculate revenue table for given prices
void maxRev(vector<int> prices,vector<int> &revenue,int n)
{
  if(n>prices.size())//base case
    return;
  //will compare to unreachable number, prices not negative
  int max_val=-1;
  //loop through revenue table
  for(int i=0;i<n;i++)
  {
    //compare current max value with revenue up to n-i-1
    int p=prices[i] + revenue[n-i-1];
    if(max_val> p)
      max_val=max_val;
    else
      max_val=p;
  }
  //set revenue at n to whichever comparison decides is bigger
  revenue[n]=max_val;
  //recurse until base case reached
  maxRev(prices,revenue,n+1);
}

int main()
{
  int N,p;//N= size; p=price
  cin >> N;
  vector<int> prices(N);//array of prices
  vector<int> revenue(N+1);//array to keep track of revenue
  revenue[0]=0;
  for(int i=0;i<N;i++)//Note: i is not representative of land area
  {
    cin >>p;
    prices[i]=p;
  }
  //call maxRev here
  maxRev(prices,revenue,1);
  //print revenue at last element for max Revenue
  cout << revenue[N] << endl;
  return 0;
}
