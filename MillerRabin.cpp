#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using u128 = __uint128_t;

ull mulmod(ull a, ull b, ull m){ return (u128)a*b % m; }

ull powmod(ull a, ull d, ull m){
    ull r=1;
    while(d){
        if(d&1) r=mulmod(r,a,m);
        a=mulmod(a,a,m);
        d>>=1;
    }
    return r;
}

bool check(ull n, ull a, ull d, int s){
    ull x=powmod(a,d,n);
    if(x==1||x==n-1) return 1;
    for(int i=1;i<s;i++){
        x=mulmod(x,x,n);
        if(x==n-1) return 1;
    }
    return 0;
}

bool isPrime(ull n){
    if(n<2) return 0;
    for(ull p:{2,3,5,7,11,13,17,19,23,29}) if(n%p==0) return n==p;
    ull d=n-1; int s=0;
    while((d&1)==0){ d>>=1; s++; }
    for(ull a:{2,325,9375,28178,450775,9780504,1795265022}){
        if(a%n==0) continue;
        if(!check(n,a,d,s)) return 0;
    }
    return 1;
}

int main(){
    ull n; cin>>n;
    cout<<(isPrime(n)?"YES":"NO");
}