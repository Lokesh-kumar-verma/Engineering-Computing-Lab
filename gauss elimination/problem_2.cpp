
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<iomanip>                  
#include<cmath>
using namespace std;
int main()
{
int i,j,k,r=3,c=4,l;
double I[10][10],x[10];
    double d;
    double f;
ifstream file("input_2.txt");                    
        for(i=1;i<=3;i++)                                   
        for(j=1;j<=4;j++)
         file>>I[i][j];  

for (i=1;i<=r;i++)
{
   for(j=i+1;j<=c;j++)
   {
    if (I[i][i]==0)
     {
      for(l=j;l<=r;l++)
      {
      if (I[l][i]!=0)
       {
        for(k=1;k<=c;k++)
         {
            d=I[i][k];
            I[i][k]=I[j][k];
            I[j][k]=d;
         }
         break;
       }
        else if(l<r)
         {
            continue;
         }
          else if(l==r)
           {
             cout<<"Matrix is singular";
             break;
           }
          j=l+1;
      }
     }
  
    f=I[j][i]/I[i][i];
     for (k=1;k<=c;k++){
     I[j][k]=I[j][k]-(f*I[i][k]);
     }
   }
}
 ofstream out("output_2.txt");
      {  
        for(i=1;i<=3;i++)
      {
        for(j=1;j<=4;j++)
        out<<setprecision(3)<<I[i][j]<<"\t";
        out<<"\n"; 
       }
        if (I[r][r]==0 && I[r][c]!=0)
             {
                 out<<"There is no solution";
             }
        else if(I[r][r]!=0)
             { 
              out<<"\n unique solution \n";
                 x[r] = I[r][c]/I[r][r];
                out<<x[r]<<" , ";
                         for(i=(r-1);i>=1;i--)
                 {
                   double sum = 0;
                   for(j=(i+1);j<=c;j++)
                   {
                       sum = sum + I[i][j]*x[j];
                   }
                   x[i] = (I[i][c]-sum)/I[i][i];
                    out<<x[i]<<" , ";
                 }
             }
          else
          {
              out<<"There is multiple solution";
          }
       }
  return 0;
}