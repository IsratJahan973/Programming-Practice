#include<iostream>
#include<set>
#include<vector>
using namespace std;
int main(){
    set<int,greater<int>>coins={2,7,1,10,12};
    int amount=50;
    auto it=coins.begin();
    int notes=0;
    vector<int>ans;
    while(amount>0 && it!=coins.end()){
          int count=0;
          count=amount/(*it);
          amount=amount-(count*(*it));
          for(int i=0;i<count;i++){
            ans.push_back(*it);
          }
          notes=notes+count;
          it++;
    }
    cout<<"Total coins needed= "<<notes<<endl<<"Coins are = ";
    for(int b:ans){
        cout<<b<<" ";
    }
}