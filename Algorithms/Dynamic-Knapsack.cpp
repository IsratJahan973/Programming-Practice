#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int>w={3,2,5,4};
    vector<int>v={4,3,6,5};
    int item=w.size();
    int max_w=7;
    vector<vector<int>>dp(item+1,vector<int>(max_w+1,0));
    for(int j=1;j<=max_w;j++){
        for(int i=1;i<=item;i++){
           if(j>=w[i-1])
           dp[i][j]=max(dp[i-1][j],dp[i-1][j-w[i-1]]+v[i-1]);
           else
           dp[i][j]=dp[i-1][j];
        }
    }
    int max_profit=dp[item][max_w];
    cout<<"Max profit= "<<max_profit<<endl;
    vector<int>take;
    int i=item;
    int j=max_w;
    while(i>0 &&j>0){
        if(dp[i][j]!=dp[i-1][j]){
            take.push_back(i);
            j=j-w[i-1];
        }
        i--;
    }
    cout<<"items taken= ";
    for(int b:take){
       cout<<b<<" ";
    }
}