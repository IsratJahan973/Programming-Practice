#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
    int n;
    cin>>n;
    int m;
    cin>>m;
    vector<int>vec(n);
    int count=0;
    for(int i=0;i<n;i++){
        cin>>vec[i];
    }
    for(int b:vec){
        if(b>0 && b>=vec[m-1])
        count++;
    }
    cout<<count;

}