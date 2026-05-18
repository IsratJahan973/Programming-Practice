#include<iostream>
using namespace std;

void Bubblesort(int arr[],int n){   //Pushing biggest elements to the last
int temp;
for(int i=0;i<n-1;i++){
    bool isswap=false;
    for(int j=0;j<n-1-i;j++){
        if(arr[j]>arr[j+1]){
            temp=arr[j];
            arr[j]=arr[j+1];
            arr[j+1]=temp;
            isswap=true;
        }  
        }
         if(!isswap){// array is allready sorted;
            return;
    }
}
}
void selectionsort(int arr[],int n){  //pushing the smallest elements to the first
    int temp;
    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++){
            if(arr[j]<arr[min]){
                min=j;
            }
        }
        temp=arr[i];
        arr[i]=arr[min];
        arr[min]=temp;
    }
}

void insertionsort(int arr[],int n){   //card suffle
    for(int i=1;i<n;i++){
        int curr=arr[i];
        int prev=i-1;
        while(prev>=0&& arr[prev]>curr){
            arr[prev+1]=arr[prev];
            prev--;
        }
        arr[prev+1]=curr;
    }
}
int main(){
    int arr[]={8,4,6,9,2,3,1};
    int n=7;
    //Bubblesort(arr,n);
    //selectionsort(arr,n);
    insertionsort(arr,n);
    for(int b:arr){
        cout<<b<<" ";
    }

}