#include<iostream>
#include<vector>
using namespace std;

struct process{
    int pid, at, bt, pr , rem, ct, tat, wt;
};

int main(){
    int n;
    cout<<"Enter number of processes: ";
    cin>>n;

    vector<process> p(n);

    for(int i=0;i<n;i++){
        p[i].pid = i+1;
        cout<<"Enter AT, BT, Priority: ";
        cin>>p[i].at >> p[i].bt >> p[i].pr;
        p[i].rem = p[i].bt;
    }

    int time = 0, completed = 0;

    while(completed < n){
        int idx = -1;
        int best_pr = 1e9;

        // select highest priority (smallest pr value)
        for(int i=0;i<n;i++){
            if(p[i].at <= time && p[i].rem > 0){
                if(p[i].pr < best_pr || (p[i].pr == best_pr && (idx == -1 || p[i].at < p[idx].at))){
                    best_pr = p[i].pr;
                    idx = i;
                }
            }
        }

        // no process available
        if(idx == -1){
            time++;
            continue;
        }

        // execute for 1 unit
        p[idx].rem--;
        time++;

        // if finished
        if(p[idx].rem == 0){
            p[idx].ct = time;
            completed++;
        }
    }

    float avg_tat=0, avg_wt=0;

    cout<<"\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    for(int i=0;i<n;i++){
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        avg_tat += p[i].tat;
        avg_wt += p[i].wt;

        cout<<p[i].pid<<"\t"<<p[i].at<<"\t"<<p[i].bt<<"\t"
            <<p[i].pr<<"\t"<<p[i].ct<<"\t"
            <<p[i].tat<<"\t"<<p[i].wt<<"\n";
    }

    cout<<"\nAverage TAT = "<<avg_tat/n;
    cout<<"\nAverage WT = "<<avg_wt/n;
}