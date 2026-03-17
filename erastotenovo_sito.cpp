#include <iostream>
#include <vector>
using namespace std;

void s(int n){
    vector<bool> p(n+1,1);
    p[0]=p[1]=0;
    for(int i=2;i*i<=n;i++)
        if(p[i])
            for(int j=i*i;j<=n;j+=i)
                p[j]=0;
    for(int i=2;i<=n;i++)
        if(p[i]) cout<<i<<" ";
}

int main(){
    int n; cin>>n;
    s(n);
}