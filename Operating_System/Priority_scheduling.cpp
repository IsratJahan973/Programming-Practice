#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct process{
    int pid,at,bt,ct,tat,wt,pr;
    bool done = false;
};
int main(){
    int n;
    cout<<"Enter number of process= ";
    cin>>n;
    vector<process>p(n);
    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        cout<<"process "<<p[i].pid<<" AT and BT and priority: ";
        cin >>p[i].at>>p[i].bt>>p[i].pr;
    }
    int completed=0, current_time=0;
    while(completed<n){
        int idx=-1;
        int highest_pr=1e9;
        for(int i=0;i<n;i++){
            if(p[i].at<=current_time && !p[i].done){
                if(p[i].pr<highest_pr){
                    idx=i;
                    highest_pr=p[i].pr;
                }
            }
        }
        if(idx== -1){
            current_time++;
            continue;
        }

        p[idx].ct=current_time + p[idx].bt;
        p[idx].tat= p[idx].ct - p[idx].at;
        p[idx].wt=p[idx].tat - p[idx].bt;
        current_time=p[idx].ct;
        p[idx].done=true;
        completed++;
    }
    
    cout<<"\nprocess\tat\tbt\tpr\tct\ttat\twt\n";
    float avg_tat=0,avg_wt=0;
    for(auto b:p){
        cout<<b.pid<<"\t"<<b.at<<"\t"<<b.bt<<"\t"<<b.pr<<"\t"<<b.ct<<"\t"<<b.tat<<"\t"<<b.wt<<endl;
        avg_tat+=b.tat;
        avg_wt+=b.wt;
    }
    cout<<"\nAverage TAT= "<<avg_tat/n<<"\nAverage WT= "<<avg_wt/n<<endl;
    return 0;
}