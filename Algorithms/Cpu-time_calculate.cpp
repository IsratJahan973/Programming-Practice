#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

void insertion(int arr[],int n){
for(int i=1;i<n;i++){
    int curr=arr[i];
    int prev=i-1;
    while(prev>=0 && arr[prev]>=curr){ 
         arr[prev+1]=arr[prev];
         prev--;
    }
    arr[prev+1]=curr;
}
}
int main(){
    int k;
    cout<<"enter exponential size=";
    cin>>k;
    int size=1<<k;
    int *arr=new int[size];
    srand(time(0));
    for(int i=0;i<size;i++){
        arr[i]=rand()%100;
    }
    cout<<"Original array"<<endl;
    for(int i=0;i<size;i++){
        cout<<arr[i]<<" ";
    }
    clock_t start,end;
    start=clock();
    insertion(arr,size);
    end=clock();
    cout<<endl<<"sorted array"<<endl;
    for(int i=0;i<size;i++){
        cout<<arr[i]<<" ";
    }

}