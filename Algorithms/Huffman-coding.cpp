#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

struct node {
    char ch;
    int freq;
    node* left;
    node* right;
    node(char c,int f){
        ch=c;
        freq=f;
        left=right=nullptr;}
};
struct compare{
    bool operator()(node* a,node* b){
        return a->freq>b->freq;}
};
void getcode(node* root,string code,unordered_map<char,string>& huffmancode) {
    if(!root) 
    return;
    if(!root->left && !root->right) {
        huffmancode[root->ch]=code;
    }
    getcode(root->left,code+"0",huffmancode);
    getcode(root->right,code+"1",huffmancode);
}
string decodeString(node* root,const string& encoded) {
    string decoded="";
    node* curr=root;
    for (int i=0;i<encoded.length();i++) {
        if(encoded[i]=='0'){
            curr= curr->left;}
        else{
            curr=curr->right;
        }
        if (curr->left==nullptr && curr->right==nullptr) {
            decoded=decoded+curr->ch;
            curr= root;
        }
    }
    return decoded;
}

int main() {
    string text="this is a test string for huffman coding";
    unordered_map<char,int>freq;
    for (char c:text){
        freq[c]++;}
    priority_queue<node*, vector<node*>, compare> pq;
    for (auto p : freq) {
        pq.push(new node(p.first,p.second));}
        
    while (pq.size() > 1) { // build huffman tree
        node*left=pq.top();
        pq.pop();
        node*right=pq.top();
        pq.pop();
        node*sum=new node('$',left->freq+right->freq);
        sum->left=left;
        sum->right=right;
        pq.push(sum);
    }
    node* root=pq.top();//

    unordered_map<char,string>huffmancode;
    getcode(root,"",huffmancode);
    cout<<"Huffman Codes:\n";
    for (auto p:huffmancode) {
        if (p.first==' ')
            cout<<"space: "<<p.second<<endl;
        else
            cout<<p.first<<": "<<p.second<<endl;
    }
    string encoded="";
    for (char c:text){
        encoded+=huffmancode[c];}

    cout<<"Original String:\n"<<text<<endl;
    cout<<"Encoded Data:\n"<<encoded<<endl;
    string decoded=decodeString(root,encoded);
    cout<<"Decoded Data:\n"<<decoded<<endl;
    return 0;
}