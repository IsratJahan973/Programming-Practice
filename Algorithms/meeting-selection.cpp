#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

bool comp(pair<int,int>a,pair<int,int>b){
    return a.second<b.second;
}
int main(){
   vector<pair<int,int>>meeting={{1,2},{3,4},{0,6},{5,7},{8,9},{5,9}};
   sort(meeting.begin(),meeting.end(),comp);
   int count=1;
   vector<pair<int,int>>taken;
   taken.push_back(meeting[0]);
   int last=meeting[0].second;
   for(int i=1;i<meeting.size();i++){
      if(meeting[i].first>=last){
        taken.push_back(meeting[i]);
        count++;
        last=meeting[i].second;
      }
   }
   for(auto b:taken){
   cout<<"taken {"<<b.first<<","<<b.second<<"}"<<endl;
   }
   cout<<"Total meeting= "<<count<<endl;
   
}