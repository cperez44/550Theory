#include <iostream>

using namespace std;

/*
class path
{
  public:
  path(){};
  path(int V,int W, int uOrigin, int vOrigin)
  {v=V;w=W;u_original=uOrigin;v_original=vOrigin;}
  int getV(){return v;}
  int getW(){return w;}
  void setV(int s){v=s;}
  int getU_origin(){return u_original;}
  int getV_origin(){return v_original;}
  private:
  int v;
  int w;//maintance fee per year
  int u_original;
  int v_original;

};
*/

int main()
{
  int N,M;//Size of each network
  int a,b;//ID of stations
  int w;//Path weight or maintanence fee per year

  cout << "Enter total number of stations in RedNova's network:" << endl;
  cin >> N;//the total number of stations in RedNova's wormhole
  for(int i=0;i<N;i++)
  {
    cin >> a;
    cin >> b;
    cin >> w;
  }
  cout << "Enter total number of stations in StarTrace's network:" << endl;
  cin >> M;
  for(int i=0;i<M;i++)
  {
    cin >> a;
    cin >> b;
    cin >> w;
  }

  return 0;
}
