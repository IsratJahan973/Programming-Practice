
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

void shortestRoute(){
    int n,e;
    cout<<"Enter number of locations: ";
    cin>>n;
    vector<vector<pair<int,int>>> graph(n);
    cout<<"Enter number of roads: ";
    cin>>e;

    for(int i=0;i<e;i++){
        int u,v,w;
        cout<<"Enter road (from to distance): ";
        cin>>u>>v>>w;
        graph[u].push_back({v,w});
        graph[v].push_back({u,w});
    }
    int source=0;
    vector<int> dist(n,INT_MAX);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

    dist[source]=0;
    pq.push({0,source});

    while(!pq.empty()){
        int node=pq.top().second;
        pq.pop();

        for(auto edge:graph[node]){
            int next=edge.first;
            int weight=edge.second;

            if(dist[node]+weight<dist[next]){
                dist[next]=dist[node]+weight;
                pq.push({dist[next],next});
            }
        }
    }
    cout<<"Shortest Distance:"<<endl;

    for(int i=0;i<n;i++){
        cout<<"Location "<<i<<" = "<<dist[i]<<endl;
    }
}

void supplySelection(){
    int n,capacity;
    cout<<"Enter number of supplies: ";
    cin>>n;
    vector<int> weight(n+1),value(n+1);

    for(int i=1;i<=n;i++){
        cout<<"Enter weight and importance of supply "<<i<<": ";
        cin>>weight[i]>>value[i];
    }
    cout<<"Enter truck capacity: ";
    cin>>capacity;
    vector<vector<int>> dp(n+1,vector<int>(capacity+1,0));

    for(int i=1;i<=n;i++){
        for(int j=0;j<=capacity;j++){
            if(weight[i]<=j)
                dp[i][j]=max(dp[i-1][j],value[i]+dp[i-1][j-weight[i]]);
            else
                dp[i][j]=dp[i-1][j];
        }
    }
    cout<<"Maximum Importance = "<<dp[n][capacity]<<endl;
}

struct Edge{
    int u,v,w;
};
bool compare(Edge a,Edge b){
    return a.w<b.w;
}
int parent[100];
int find(int x){
    if(parent[x]==x)
        return x;

    return parent[x]=find(parent[x]);
}

void connectCamps(){
    int n,e;
    cout<<"Enter number of camps: ";
    cin>>n;
    cout<<"Enter number of roads: ";
    cin>>e;
    vector<Edge> edges(e);

    for(int i=0;i<e;i++){
        cout<<"Enter camp1 camp2 cost: ";
        cin>>edges[i].u>>edges[i].v>>edges[i].w;
    }

    sort(edges.begin(),edges.end(),compare);

    for(int i=0;i<n;i++)
        parent[i]=i;

    int total=0;
    cout<<"Selected Roads:"<<endl;

    for(auto edge:edges){
        int pu=find(edge.u);
        int pv=find(edge.v);

        if(pu!=pv){
            parent[pu]=pv;
            cout<<edge.u<<" - "<<edge.v<<" Cost = "<<edge.w<<endl;
            total+=edge.w;
        }
    }
    cout<<"Total Cost = "<<total<<endl;
}

void maxAidFlow(){
    int n,e;
    cout<<"Enter number of cities: ";
    cin>>n;
    vector<vector<int>> capacity(n,vector<int>(n,0));
    cout<<"Enter number of routes: ";
    cin>>e;

    for(int i=0;i<e;i++){
        int u,v,cap;
        cout<<"Enter from to capacity: ";
        cin>>u>>v>>cap;
        capacity[u][v]=cap;
    }
    int source,sink;
    cout<<"Enter source and destination: ";
    cin>>source>>sink;
    int totalFlow=0;

    while(true){
        vector<int> parent(n,-1);
        queue<int> q;
        q.push(source);
        parent[source]=source;

        while(!q.empty()){
            int current=q.front();
            q.pop();

            for(int next=0;next<n;next++){
                if(parent[next]==-1 && capacity[current][next]>0){
                    parent[next]=current;
                    q.push(next);
                }
            }
        }
        if(parent[sink]==-1)
            break;

        int flow=INT_MAX;
        int current=sink;

        while(current!=source){
            int prev=parent[current];
            flow=min(flow,capacity[prev][current]);
            current=prev;
        }
        current=sink;

        while(current!=source){
            int prev=parent[current];
            capacity[prev][current]-=flow;
            capacity[current][prev]+=flow;
            current=prev;
        }
        totalFlow+=flow;
    }
    cout<<"Maximum Aid Flow = "<<totalFlow<<endl;
}

int main(){
    int choice;
    while(true){
        cout<<"===== Disaster Relief Project ====="<<endl;
        cout<<"1. Shortest Rescue Route"<<endl;
        cout<<"2. Supply Selection"<<endl;
        cout<<"3. Connect Camps"<<endl;
        cout<<"4. Maximum Aid Flow"<<endl;
        cout<<"5. Exit"<<endl;
        cout<<"Enter choice: ";
        cin>>choice;

        if(choice==1)
            shortestRoute();
        else if(choice==2)
            supplySelection();
        else if(choice==3)
            connectCamps();
        else if(choice==4)
            maxAidFlow();
        else if(choice==5)
            break;
        else
            cout<<"Invalid Choice"<<endl;
    }
    return 0;
}

