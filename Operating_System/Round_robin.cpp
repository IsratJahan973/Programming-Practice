#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct process{
    int pid,at,bt,ct,tat,wt,rem;
};
int main(){
int n;
cout<<"enter number of processes=";
cin>>n;
vector<process>p(n);
for(int i=0;i<n;i++){
    p[i].pid=i+1;
    cout<<"enter process "<<p[i].pid<<" at and bt= ";
    cin>>p[i].at>>p[i].bt;
    p[i].rem=p[i].bt;
}
int tq=2;
queue<int>q;
vector<bool>inqueue(n,false);

int time=0,completed=0;
while(completed<n){
    for(int i=0;i<n;i++){
        if(p[i].at<=time && !inqueue[i] && p[i].rem>0){
           q.push(i);
           inqueue[i]=true;
        }
    }
    if(q.empty()){
        time++;
        continue;
    }
    
    int i=q.front();
    q.pop();
    int exec= min(tq,p[i].rem);
    p[i].rem-=exec;
    time+=exec;

    for(int j=0;j<n;j++){
        if(p[j].at<=time && !inqueue[j] && p[j].rem>0){
            q.push(j);
            inqueue[j]=true;
        }
    }
    if(p[i].rem>0){
        q.push(i);
    }
    else{
        p[i].ct=time;
        completed++;
    }
    for(int i=0;i<n;i++){
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt= p[i].tat-p[i].bt;
    }
}
cout<<"\nprocess\tAT\tBT\tCT\tTAT\tWT\n";

float avg_tat=0,avg_wt=0;
for(auto &b:p){
    cout<<b.pid<<"\t"<<b.at<<"\t"<<b.bt<<"\t"<<b.ct<<"\t"<<b.tat<<"\t"<<b.wt<<"\n";
    avg_tat+=b.tat;
    avg_wt+=b.wt;
   }
   cout<<"\nAverage TAT= "<<avg_tat/n<<"\nAverage WT= "<<avg_wt/n<<endl;

}

