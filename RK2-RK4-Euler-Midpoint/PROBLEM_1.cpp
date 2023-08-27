#include<iostream>
#include<cmath>
#include<iomanip>
#include<fstream>
using namespace std;
double fn(double x0, double y0)
{
    return ((4*pow(x0,4)) + (y0/x0));
}


double analy(int x)
{
    double table1[x][1];
    table1[x][1]= (pow(x,5)+(3*x));
    return table1[x][1];
}


float euler(double x0, double y0, double h, int x)           //euler
{
    double table1[x][1];
    table1[x][1]= y0 + h*fn(x0,y0);
    return table1[x][1];
}

float midpoint(double xn, double y0, double yn, double h, int x)          //midpoint
{
    double table1[x][2];
    if(x==1)
    {
        table1[x][2]=y0+h*fn(xn,y0);
    }
    else
    table1[x][2]=y0+(2*h*fn(xn,yn));
    return table1[x][2];
}

double RK2(double x0, double y0, double h, int x)           // RK2
{
   double table1[x][3];
   double k1, k2;
   k1=h*fn(x0,y0);
   k2=h*fn(x0+h,y0+k1);
   table1[x][3]=y0+0.5*(k1+k2);
   return table1[x][3];
}

double RK4(double x0,double y0,double h,int x)
{
  double table1[x][4];
  double k1, k2, k3, k4;
  k1= h*fn(x0,y0);
  k2=h*fn(x0+0.5*h, y0+0.5*k1);
  k3=h*fn(x0+0.5*h,y0+0.5*k2 );
  k4=h*fn(x0+h,y0+k3);
  table1[x][4]=y0 +(k1+2*k2+2*k3+k4)/6;
  return table1[x][4];
}
int main()
{
  double N;
    ofstream out("output_1.txt");
    {  
     for(int j=5;j<=20;j+=5)
       {
        
        double table1[j+1][5];

        if(j==15)
        continue;

        N=j;
        

       /*  for(int s=0;s<=10;s++)
        for(int r=0;r<5;r++)
        table1[s][r]=0;*/

        double h=5/N;
         double x0=1, y0=4;
        
         table1[0][0]=y0;
         table1[0][1]=y0;
         table1[0][2]=y0;
         table1[0][3]=y0;
         table1[0][4]=y0;
         for(int i=1; i<=N; i++)               //calculation for different methods
         {
        
             table1[i][1]= euler(x0,table1[i-1][1],h,i);

               if(i==1)
             {
                table1[i][2]= midpoint(x0,y0,table1[i-1][2],h,i);
             }
             else
             {
                table1[i][2]=midpoint(x0, table1[i-2][2],table1[i-1][2],h,i);
             }

             table1[i][3]=RK2(x0,table1[i-1][3],h,i);
             table1[i][4]=RK4(x0,table1[i-1][4],h,i); 

                 x0+=h;
                 table1[i][0]= analy(x0);

         }
        
        
        
          out<<"VALUES OF Yn FOR DIFFERENT METHODDS FOR N="<<N<<"\n\n";
          out<<" x "<<"    analytical  "<<"    euler   "<<"  midpoint  "<<"     RK2    "<<"     RK4   "<<"\n";
         for(int i=0; i<=N; i++)
         {
          out<<" "<<i+1<<" "<<"\t";
          for(int j=0;j<5;j++)          
             {
             out<<setw(10)<<setprecision(4)<<table1[i][j]<<"\t";
             }
           out<<"\n";
         } 
        out<<"\n"<<"\n";
      }

      //calculatiing errors for N2,5,10,15,20,25
        double error[6][4];
        
        int s=2;
        for(int j=0;j<=5;j++)
        {
            double table2[s+1][5];
            double eeuler=0, emidpt=0, erk2=0, erk4=0;
            N=s;
             double h=5/N;
            double x0=1, y0=4;
             table2[0][0]=y0;
             table2[0][1]=y0;
             table2[0][2]=y0;
             table2[0][3]=y0;
             table2[0][4]=y0;
             for(int i=1;i<=N;i++)
             {
              table2[i][1]= euler(x0,table2[i-1][1],h,i);
                   if(i==1)
                 {
                    table2[i][2]= midpoint(x0,y0,table2[i-1][2],h,i);
                 }
                 else
                 {
                    table2[i][2]=midpoint(x0, table2[i-2][2],table2[i-1][2],h,i);
                 }
                 table2[i][3]=RK2(x0,table2[i-1][3],h,i);
                 table2[i][4]=RK4(x0,table2[i-1][4],h,i); 
                     x0+=h;
                     table2[i][0]= analy(x0);
             }
             for(int k=0;k<=N;k++)
            {
              
                 eeuler+= pow((table2[k][1]-table2[k][0]) , 2);      // values for error 
                 emidpt+= pow((table2[k][2]-table2[k][0]) , 2); 
                 erk2+= pow((table2[k][3]-table2[k][0]) , 2); 
                 erk4+= pow((table2[k][4]-table2[k][0]) , 2);    
             }
        
           error[j][0]=sqrt(eeuler)/N;       //storing error norms for diff. N in matrix form
           error[j][1]=sqrt(emidpt)/N;
           error[j][2]=sqrt(erk2)/N;
           error[j][3]=sqrt(erk4)/N;
           s=5*(j+1);
        }

        out<<"\n\n error norms \n\n";
        out<<"N     euler        midpoint        RK2         RK4"<<"\n";
        N=2;
        for(int i=0;i<6;i++)
        {  out<<N<<"\t";
          for(int j=0;j<4;j++)
           out<<setw(7)<<setprecision(3)<<error[i][j]<<"\t";
           out<<"\n";
           N=5*(i+1);
        }
    }
    return 0;
}