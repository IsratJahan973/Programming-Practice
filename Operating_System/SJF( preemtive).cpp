#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct process{
    int pid,at,bt,ct,tat,wt,rm;
};
int main(){
    int n;
     cout<<"enter number of process= ";
    cin>>n;
    vector<process>p(n);
    for(int i=0;i<n;i++){
       p[i].pid=i+1;
       cout<<"Enter AT and BT of process "<<p[i].pid<<" = ";
       cin>>p[i].at>>p[i].bt;
       p[i].rm=p[i].bt;
    }
int completed=0,current_time=0;
while(completed<n){
    int idx=-1;
int min_rm=1e9;

for(int i=0;i<n;i++){
    if(p[i].at<=current_time && p[i].rm>0){
        if(p[i].rm < min_rm || (p[i].rm == min_rm && (idx == -1 || p[i].at < p[idx].at))){
            idx=i;
            min_rm=p[i].rm;
        }
    }
}
    if(idx==-1){
        current_time++;
        continue;
    }

    p[idx].rm--;
    current_time++;
    if(p[idx].rm==0){
        p[idx].ct=current_time;
        completed++;
    }
}
 float avg_tat=0, avg_wt=0;

    cout<<"\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    for(int i=0;i<n;i++){
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        avg_tat += p[i].tat;
        avg_wt += p[i].wt;

        cout<<p[i].pid<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"
            <<p[i].ct<<"\t"<<p[i].tat<<"\t"<<p[i].wt<<"\n";
    }

    cout<<"\nAverage TAT = "<<avg_tat/n;
    cout<<"\nAverage WT = "<<avg_wt/n;
}
