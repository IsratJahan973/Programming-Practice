#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct process{
    int pid,at,bt,ct,tat,wt;
};
bool comp(process a,process b){
    return a.at<b.at;
}
int main(){
int n;
cout<<"enter number of processes=";
cin>>n;
vector<process>p(n);
for(int i=0;i<n;i++){
    p[i].pid=i+1;
    cout<<"enter process "<<p[i].pid<<" at and bt= ";
    cin>>p[i].at>>p[i].bt;
}
sort(p.begin(),p.end(),comp);
int current_time=0;
float avg_tat=0,avg_wt=0;
for(int i=0;i<n;i++){
   if(current_time<p[i].at){
    current_time=p[i].at;
   }
   p[i].ct= current_time + p[i].bt;
   p[i].tat=p[i].ct-p[i].at;
   p[i].wt=p[i].tat- p[i].bt;
   current_time=p[i].ct;

   avg_tat+=p[i].tat;
   avg_wt+=p[i].wt;
}
cout<<"\nprocess\tAT\tBT\tCT\tTAT\tWT\n";
 
   for(auto &b:p){
    cout<<b.pid<<"\t"<<b.at<<"\t"<<b.bt<<"\t"<<b.ct<<"\t"<<b.tat<<"\t"<<b.wt<<"\n";
   }
   cout<<"\nAverage TAT= "<<avg_tat/n<<"\nAverage WT= "<<avg_wt/n<<endl;

}