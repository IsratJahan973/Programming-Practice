#include<iostream>
#include<vector>
using namespace std;

void merge(int arr[],int st,int mid,int en){
vector<int>temp;
int i=st,j=mid+1;
while(i<=mid&& j<=en){
    if(arr[i]<=arr[j]){
    temp.push_back(arr[i]);
    i++;}
    else{
        temp.push_back(arr[j]);
        j++;
    }
}
while(i<=mid){
    temp.push_back(arr[i]);
    i++;
}
while(j<=en){
    temp.push_back(arr[j]);
    j++;
}
for(int idx=0;idx<temp.size();idx++){
    arr[idx+st]=temp[idx];
}
}

void mergesort(int arr[],int st,int en){
    int mid;
    if(st<en){
     mid=st+(en-st)/2;
        mergesort(arr,st,mid);
        mergesort(arr,mid+1,en);
         merge(arr,st,mid,en);
    }
}

int main(){
    int arr[]={4,9,2,3,1,10,9};
    int size=7;
    int st=0,en=size-1;
    mergesort(arr,st,en);
    for(int b:arr){
        cout<<b<<" ";
    }
}