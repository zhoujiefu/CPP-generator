#ifndef GENERATOR_H
#define GENERATOR_H
#include<bits/stdc++.h>
#define ll long long
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define per(i,a,b) for(int i=a;i>=b;--i)
#define debug(x) cout<<#x<<"="<<x<<'\n'
using namespace std;
namespace gen{
    inline void file(string s){
        s+=".in";
        freopen(s.data(),"w",stdout);
    }
    mt19937_64 rng(time(0));
    template<typename T>
    inline T rnd(T l,T r){
        uniform_int_distribution<T>rd(l,r);
        return rd(rng);
    }
    inline double rnd(double l,double r){
        uniform_real_distribution<double>rd(l,r);
        return rd(rng);
    }
    inline bool rnd(double p=0.5){
        bernoulli_distribution rd(p);
        return rd(rng);
    }
    template <typename T>
    typename T::value_type choice(const T& c){//从给定容器中随机选取一个元素 
        if(c.empty()) throw runtime_error("Cannot choose from an empty container.");
        auto it=begin(c);
        advance(it,rnd(0,c.size()));
        return *it;
    }
    template<typename T>
    inline vector<T> rnd_array(int n,T l,T r){//随机长为 n,a_i 在 [l,r] 的序列 
        vector<T> a(n);
        rep(i,0,n-1) a[i]=rnd(l,r);
        return a;
    }
    template<typename T>
    inline vector<T> rnd_arr_with_all_val(int n,T vl,T vr,T l,T r){//随机一个长为 n,vl<=a_i<=vr,且包含 [l,r] 全部元素 
        vector<T> a;a.reserve(n);
        if(n<(r-l+1)) throw runtime_error("n must be at least r-l+1.");
        rep(i,l,r) a.push_back(i);
        int cnt=n-(r-l+1);
        rep(i,1,cnt) a.push_back(rnd<T>(vl,vr));
        shuffle(a.begin(),a.end(),rng);
        return a;
    }
    inline vector<int> rnd_permu(int n){//随机[1,n]的排列 
        vector<int> a(n);
        rep(i,0,n-1) a[i]=i+1;
        shuffle(a.begin(),a.end(),rng);
        return a;
    }
    inline string rnd_str(int n,string c="abcdefghijklmnopqrstuvwxyz"){
    	string s;s.reserve(n);
        rep(i,1,n) s.push_back(choice(c));
        return s;
	} 
    inline string rnd_str(int n,int upper=0){//随机一个字符串 
        string c="abcdefghijklmnopqrstuvwxyz";
        if(upper) for(char &x:c) x=toupper(x);
        string s;s.reserve(n);
        rep(i,1,n) s.push_back(choice(c));
        return s;
    }
    struct Graph{
        struct edge{
            int u,v;ll w;
            inline void print(bool val){
                if(val) cout<<u<<' '<<v<<' '<<w<<'\n';
                else cout<<u<<' '<<v<<'\n';
            }
        };
        int n,m;
        bool val;
        vector<edge>g;
        Graph(int nn,int mm,bool v){n=nn,m=mm,val=v;g.clear();}
        inline void adde(int u,int v,ll w){
            g.push_back({u,v,w});
        }
        inline void print(){
            for(edge i:g) i.print(val);
        }
    };
    inline Graph rnd_tree(int n,int h,int rt,ll vl,ll vr){
        Graph g(n,n-1,vl>0);
        vector<int>a=rnd_arr_with_all_val(n-1,2,h,2,h);
        a.insert(a.begin()+rt-1,1);
        vector<vector<int>>v(h+1);
        for(int i=0;i<(int)a.size();++i) v[a[i]].push_back(i+1);
        rep(i,2,h){
            ll w=rnd(vl,vr);
            for(int u:v[i]) g.adde(u,choice(v[i-1]),w);
        }
        return g;
    }
};using namespace gen;
#endif
