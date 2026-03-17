#include <bits/stdc++.h>
using namespace std;

struct mojint{
    static const int B=1000000000;
    vector<int> a;

    mojint(long long v=0){ *this=v; }
    mojint& operator=(long long v){
        a.clear();
        if(v==0) return *this;
        while(v){ a.push_back(v%B); v/=B; }
        return *this;
    }

    mojint(const string& s){ read(s); }
    mojint& read(const string& s){
        a.clear();
        for(int i=s.size(); i>0; i-=9){
            int x=0;
            for(int j=max(0,i-9); j<i; j++) x=x*10+(s[j]-'0');
            a.push_back(x);
        }
        trim();
        return *this;
    }

    string str() const{
        if(a.empty()) return "0";
        string s=to_string(a.back());
        for(int i=(int)a.size()-2;i>=0;i--){
            string t=to_string(a[i]);
            s+=string(9-t.size(),'0')+t;
        }
        return s;
    }

    friend ostream& operator<<(ostream& os,const mojint& v){ return os<<v.str(); }
    friend istream& operator>>(istream& is,mojint& v){ string s; is>>s; v.read(s); return is; }

    bool operator<(const mojint& o) const{
        if(a.size()!=o.a.size()) return a.size()<o.a.size();
        for(int i=a.size()-1;i>=0;i--) if(a[i]!=o.a[i]) return a[i]<o.a[i];
        return 0;
    }
    bool operator==(const mojint& o) const{ return a==o.a; }

    void trim(){ while(!a.empty() && a.back()==0) a.pop_back(); }

    friend mojint operator+(mojint x,const mojint& y){
        int c=0;
        for(size_t i=0;i<max(x.a.size(),y.a.size())||c;i++){
            if(i==x.a.size()) x.a.push_back(0);
            x.a[i]+=c+(i<y.a.size()?y.a[i]:0);
            c=x.a[i]>=B;
            if(c) x.a[i]-=B;
        }
        return x;
    }

    friend mojint operator-(mojint x,const mojint& y){
        int c=0;
        for(size_t i=0;i<y.a.size()||c;i++){
            x.a[i]-=c+(i<y.a.size()?y.a[i]:0);
            c=x.a[i]<0;
            if(c) x.a[i]+=B;
        }
        x.trim();
        return x;
    }

    friend mojint operator*(const mojint& x,const mojint& y){
        mojint r;
        r.a.assign(x.a.size()+y.a.size(),0);
        for(size_t i=0;i<x.a.size();i++){
            long long c=0;
            for(size_t j=0;j<y.a.size()||c;j++){
                long long cur=r.a[i+j]+c+(long long)x.a[i]*(j<y.a.size()?y.a[j]:0);
                r.a[i+j]=int(cur%B);
                c=cur/B;
            }
        }
        r.trim();
        return r;
    }
};

int main(){
    mojint a,b; cin>>a>>b;
    cout<<a+b<<"\n";
    cout<<a-b<<"\n";
    cout<<a*b<<"\n";
}
