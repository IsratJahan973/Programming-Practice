#include<iostream>
using namespace std;
int main(){
    int arr[]={9,7,6,15,16,5,10,11};
    int n=sizeof(arr)/sizeof(arr[0]);
    int temp,i;
    for(int j=1;j<n;j++){        // n
        i=j-1;                   //n-1
        temp=arr[j];                //n-1
        while(i>=0 && temp<arr[i]){   //
            arr[i+1]=arr[i];
            i--;
        }
        arr[i+1]=temp;
    }
    for(int b:arr){
        cout<<b<<" ";
    }
}