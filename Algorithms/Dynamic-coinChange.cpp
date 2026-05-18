#include<iostream>
#include<vector>
#include<climits>
using namespace std;
int main(){
vector<int>coins={1,3,4};
int coin=coins.size();
int amount=6;
vector<vector<int>>dp(coin+1,vector<int>(amount+1,INT_MAX));
for(int i=0;i<=coin;i++){
    dp[i][0]=0;
}
for(int i=1;i<=coin;i++){
    for(int j=1;j<=amount;j++){
        if(j>=coins[i-1])
        dp[i][j]=min(dp[i-1][j],dp[i][j-coins[i-1]]+1);
        else
        dp[i][j]=dp[i-1][j];
    }
}
cout<<"minimum coins taken= "<<dp[coin][amount]<<endl;
int i=coin;
int j=amount;
vector<int> take;
 while(i>0 && j>0){
        if(dp[i][j]==dp[i-1][j]){
            i--; // not taken
        }
        else{
            take.push_back(coins[i-1]);
            j = j - coins[i-1]; // stay in same row
        }
    }
cout<<"coins taken= ";
for(int b:take){
    cout<<b<<" ";
}
}