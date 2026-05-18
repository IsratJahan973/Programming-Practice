#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int>coins={3,5,2,1};
    int amount=10;
    int coin=coins.size();
    vector<vector<int>>dp(coin+1,vector<int>(amount+1,0));
    for(int i=0;i<=coin;i++){
        dp[i][0]=1;
    }
    for(int i=1;i<=coin;i++){
        for(int j=1;j<=amount;j++){
            if(coins[i-1]<=j){
               dp[i][j]=dp[i-1][j]+dp[i][j-coins[i-1]];
            }
            else
            dp[i][j]=dp[i-1][j];
        }
    }
    cout<<"number of ways="<<dp[coin][amount]<<endl;
}
