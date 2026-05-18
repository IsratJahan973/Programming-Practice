#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int>arr = {9,2,4,3,1,10,13,6,11};
    int n = arr.size();
    vector<int>dp(n,1); 
    for(int i=0;i<n;i++) {
        for(int j=0;j<i;j++) {
            if(arr[j]<arr[i])
                dp[i]=max(dp[i],dp[j]+1);
        }
    }
    int length=0;
    for(int i=0;i<n;i++){
        length=max(length,dp[i]);
    }
    cout<<"Length of LIS: "<<length<<endl;
}