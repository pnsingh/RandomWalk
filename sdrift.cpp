#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
int main()
{
 ofstream fil;
 fil.open("slightdrift125.txt");
 double dt=0.01;int dx=1;
 int i=0;
 double f[512];
 int L[512],R[512];
 do
 {
  L[i]=i-1;
  R[i]=i+1;
  i++;
 }while(i<=511);
   L[0]=511;
   R[511]=0;
   for(int x=0;x<=511;x+=dx)
    f[x]=0;
  f[256]=1;
  for(double t=0;t<=200;t+=dt)
  {
   for(int x=0;x<=511;x+=dx)
    {
     f[x]+=(0.5*((dt/dx)*(f[x]-f[L[x]]))) + (dt/(dx*dx))*(f[R[x]]-2*f[x]+f[L[x]]);
     if((t<125.01)&&(t>124.99))fil<<t<<"   "<<x<<"  "<<f[x]<<"\n";
    }
   }
  fil.close();
return 0;
}
