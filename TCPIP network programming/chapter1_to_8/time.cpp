#include<iostream>
#include<stdio.h>
using namespace std;

class Time
{
      double hour;
      double minute;
      double seconds;

   public:
      Time(){}
      Time(double h,double m,double s);
      void show() const;
      void reset(double h);
     ~Time(){};

};

Time::Time(double h,double m,double s)
{

 hour=h;
   minute=m;
   seconds=s;
}
void Time::show() const
{
  cout<<"Hour : "<<hour<<endl;
  cout<<"minute : "<<minute<<endl;
  cout<<"second : "<<seconds<<endl;
}
void Time::reset(double h)
{
   hour=h;  
}       

int main(int argc,char *argv[])
{
  Time t1(12,45,41);
  cout<<"time is : \n";
  t1.show();
  t1.reset(20);
  cout<<"time after change:\n";
  t1.show();
  return 0;
}

