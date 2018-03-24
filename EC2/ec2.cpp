#include <iostream>
#include <vector>

using namespace std;

//helper function that will return Maximum Revenue for given prices
int maxRev(vector<int> prices,int size)
{
  for(int i=0;i<size;i++)
  {
    cout << "Test" << endl;
  }

}

int main()
{
  int N,p;//N= size; p=price
  cin >> N;
  vector<int> prices(N);
  for(int i=0;i<N;i++)//Note: i is not representative of land area
  {
    cin >>p;
    prices[i]=p;
  }
  //call maxRev here
  maxRev(prices,N);
  return 0;
}
