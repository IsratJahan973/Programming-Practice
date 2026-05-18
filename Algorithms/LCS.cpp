#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
    string x="providence";
    string y="president";
    int m=x.size();
    int n=y.size();
    vector<vector<int>>dp(m+1,vector<int>(n+1,0));
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(x[i-1]==y[j-1]){
                dp[i][j]=dp[i-1][j-1]+1;
            }
            else
               dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
        }
    }
    int max_l=dp[m][n];
    cout<<"Largest common subsequence= "<<max_l<<endl;

    int i=m;   
    int j=n;
    vector<char>taken;
    while(i>0 && j>0){
        if(x[i-1]==y[j-1]){
           taken.push_back(x[i-1]);
           j--;
           i--;
        }
        else if(dp[i-1][j]>dp[i][j-1])
        i--;
        else
        j--;
    }
    reverse(taken.begin(), taken.end());

    cout<<"LCS = ";

    for(char c : taken)
        cout<<c;
}