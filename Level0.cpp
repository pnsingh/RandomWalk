 #include<MersenneTwister.h>
 #include<iostream>
 #include<fstream>
 #include<time.h>
 using namespace std;
 int s=0;
 MTRand M2(s);
 int main()
 {
  s=(int)time(0);
  M2.seed(s);
  ofstream fil;
  int x=0;
  unsigned long long nr=0,nl=0;
  double q=0,q1=0,mean=0,ms=0;
  long double B[20000];
  for(int a=0;a<20000;a++)
   B[a]=0.0;
  fil.open("RWN6.TXT");
  for(unsigned long long i=0;i<1000000;i++)
   {
     nr=0;nl=0;
     for (int j=0;j<10000;j++)
      {
       x=M2.randInt(1);
       if(x==1)
        nr++;
       else
        nl++;
      }
     B[(nr-nl+9999)]++;
   }
  for (int l=0;l<20000;l++)
  {
    q+=(l-9999)*B[l];
    q1+=((l-9999)*(l-9999))*B[l];
  }
   mean=q/1000000;
   ms=q1/1000000;
   cout<<mean<<"        "<<ms;;
   for(int l=0;l<20000;l++)
   fil<<l-10000<<"   "<<(B[l]/1000000)<<"\n";
   return 0;
}
