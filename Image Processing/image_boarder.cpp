#include "vector"
#include "iostream"
#include "set"

using namespace std;

#define FOR(i_,a_) for(int i_=0;i_<a_;++i_)
#define FORS(s_,i_,a_) for(int i_=s_;i_<a_;++i_)
#define FORR(i_,a_) for(int i_=a_-1;i_>=0;--i_)
#define FORI(i_,a_) for(int i_=1;i_<=a_;++i_)
#define FORA(i_,a_) for(auto i_:a_)
#define FOR1(i_,a_) for(int i_=1;i_<a_;++i_)
#define FORIT(it_,c_) for(auto it_ = c_.begin(); it_!=c_.end();++it_)

#define _ cerr<<' ';
#define _N cerr<<'\n';
#define _T cerr<<'\t';
#define TRACED(_v) cerr<<_v;
void TRACEV(string a){TRACED(a);}
template<typename... Args> void TRACEV(tuple<Args...> t);
template<typename l, typename r> void TRACEV(pair<l,r> t);
template<typename T> void TRACEV(T t){TRACED(t);}
template<template<typename...> class T, typename... K> void TRACEV(T<K...> t);
template<typename T,typename... Args>void TRACEUT_(T t){TRACEV(t);}
template<typename T,typename... Args>void TRACEUT_(T t, Args... args){TRACEV(t); TRACED(", "); TRACEUT_(args...);}
template<typename T,typename... Args>void TRACEUT(T t, Args... args){TRACED('('); TRACEUT_(t,args...); TRACED(")");}
template<typename Tuple, size_t... Is>void TRACET_(Tuple t, index_sequence<Is...>){TRACEUT(get<Is>(t)...);}
template<typename Tuple>void TRACET(Tuple t){TRACET_(t,make_index_sequence<tuple_size<Tuple>::value>{});}
#define TRACEP(p_) TRACED("("); TRACEV(p_.first);TRACED(", ");TRACEV(p_.second);TRACED(")");
template<typename... Args> void TRACEV(tuple<Args...> t){TRACET(t);}
template<typename l, typename r> void TRACEV(pair<l,r> t){TRACEP(t);}
template<template<typename...> class T, typename... K> void TRACEV(T<K...> t){auto it = t.begin();
TRACED("[");TRACEV(*it);for(++it;it!=t.end();++it){TRACED(", ");TRACEV(*it);}TRACED("]");}
template<typename T> void TRACE(T t){TRACEV(t);_N;}
template<typename T,typename... Ts> void TRACE(T t,Ts... args){TRACEV(t); _T; TRACE(args...);}

#define ll long long int
#define ull unsigned long long int
#define pii pair<int,int>

int W,H,E;
#define coorToIndex(x,y) y*W + x
#define coorInBound(x,y) 0<=x && x < W && 0<=y && y < H
#define withinError(a,b) (a-b)*(a-b) <= E
#define swap(x,y) x^=y^=x^=y;
vector<int> image;
vector<int> groups;
vector<int> groupSize;
set<int> roots;

inline int uFind(int a){
	int current = a;
	while(groups[current] != -1) current = groups[current];
	if(current != a) groups[a] = current;
	return current;
}

inline void uMerge(int a, int b){
	int aP = uFind(a), bP = uFind(b);
	if(aP == bP) return;
	if(groupSize[bP] > groupSize[aP]) swap(bP,aP);
	groups[bP] = aP;
	groupSize[aP] += groupSize[bP];
	roots.erase(roots.find(bP));
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	cin>>W>>H>>E;
	image.resize(W*H);
	FOR(x,W){
		FOR(y,H){
			cin>>image[coorToIndex(x,y)];
			roots.insert(roots.end(),coorToIndex(x,y));
		}
	}
	groupSize.resize(W*H,1);
	groups.resize(W*H,-1);
	FOR(x,W){
		FOR(y,H){
			if(coorToIndex(x,y+1) && withinError(image[coorToIndex(x,y)],image[coorToIndex(x,y+1)]))
				 uMerge(coorToIndex(x,y),coorToIndex(x,y+1));
			if(coorToIndex(x+1,y) && withinError(image[coorToIndex(x,y)],image[coorToIndex(x+1,y)]))
				 uMerge(coorToIndex(x,y),coorToIndex(x+1,y));
		}
	}

	return 0;
}