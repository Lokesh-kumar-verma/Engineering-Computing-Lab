#include<iostream>
#include <math.h>
#include<iomanip>
#include<fstream>
using namespace std;
double fn(double x, double y, double z)
{
    return (2*y)/x - x*z;
}
double gn(double x, double y, double z)
{
    return (z+y)/x ;
}
double Yx(double x)
{
    return x*x*cos(x) ;
}
double Zx(double x)
{
    return x*sin(x) ;
}

double Rk4(double x0, double y0,double z0,double xn, int N,double Y[],double Z[])
{
    double h,eY=0,eZ=0,k1,l1,k2,l2,k3,l3,k4,l4;
    
    h = (xn-x0)/N;

    Y[0] = y0;
    Z[0] = z0;
    
    int i;
    for(i=0;i<N;i++)
    {
      k1 = h*fn(x0,Y[i],Z[i]);
      l1 = h*gn(x0,Y[i],Z[i]);
      k2 = h*fn(x0+0.5*h,Y[i]+0.5*k1,Z[i]+0.5*l1);
      l2 = h*gn(x0+0.5*h,Y[i]+0.5*k1,Z[i]+0.5*l1);
      k3 = h*fn(x0+0.5*h,Y[i]+0.5*k2,Z[i]+0.5*l2);
      l3 = h*gn(x0+0.5*h,Y[i]+0.5*k2,Z[i]+0.5*l2);
      k4 = h*fn(x0+h,Y[i]+k3,Z[i]+l3);
      l4 = h*gn(x0+h,Y[i]+k3,Z[i]+l3);
    
      Y[i+1] = Y[i] + (k1 + 2*k2 + 2*k3 + k4)/6;
      Z[i+1] = Z[i] + (l1 + 2*l2 + 2*l3 + l4)/6;
      
      eY+= pow((Y[i+1] - Yx(x0+h)),2);
      eZ+= pow((Z[i+1] - Zx(x0+h)),2); 
      
      x0 = x0 + h;
    } 
    Y[N+1] = sqrt(eY)/N;
    Z[N+1] = sqrt(eZ)/N;
}
int main()
{ 
  
  double x0=(M_PI/2),y0=0,z0=(M_PI/2),h;
  double xn=M_PI;
  ofstream out("output_2.txt");
  {
  for(int N=5;N<=20;N+=5)
  {
      if(N==15)
      continue;
      else
       {  
        out<<"the values for N="<<N<<"\n"<<"\n";
        out<<"x                 y(x)          y(RK4)          z(x)           z(RK4)"<<"\n";
          
          h=(xn-x0)/N;
          double Y[N+2],Z[N+2];
          Rk4(x0,y0,z0,xn,N,Y,Z);
  
          for(int i=0;i<=N;i++)
          {
              out<<x0+i*h<<"     "<<setw(14)<<setprecision(5)<<Yx(x0+i*h)<<"   "<<setw(14)<<setprecision(5)<<Y[i]<<"   "<<setw(14)<<setprecision(5)<<Zx(x0+i*h)<<"   "<<setw(14)<<setprecision(5)<<Z[i]<<"\n";
          }
          out<<"\n"<<"\n";
       }
  }
   

   out<<"\n"<<"\n";
   out<<" N             eLy                 eLz\n";
   int N=2;
   for(int m=1;m<=6;m++)
   {
           double Y[N+2],Z[N+2];
           Rk4(x0,y0,z0,xn,N,Y,Z);
           out<<N<<"      "<<setw(15)<<setprecision(5)<<Y[N+1]<<"     "<<setw(15)<<setprecision(4)<<Z[N+1]<<"\n";
       N=5*m;
   }
  }
 return 0;
}