#include <bits/stdc++.h>

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
template<typename T, size_t S> void TRACEV(array<T,S> t){TRACEV("[");TRACEV(t[0]);FOR1(i,S){TRACEV(", ");TRACEV(t[i]);}TRACEV("]");}
template<typename T,typename... Args>void TRACEUT_(T t){TRACEV(t);}
template<typename T,typename... Args>void TRACEUT_(T t, Args... args){TRACEV(t); TRACED(", "); TRACEUT_(args...);}
template<typename T,typename... Args>void TRACEUT(T t, Args... args){TRACED('('); TRACEUT_(t,args...); TRACED(")");}
template<typename Tuple, size_t... Is>void TRACET_(Tuple t, index_sequence<Is...>){TRACEUT(get<Is>(t)...);}
template<typename Tuple>void TRACET(Tuple t){TRACET_(t,make_index_sequence<tuple_size<Tuple>::value>{});}
#define TRACEP(p_) TRACED("("); TRACEV(p_.first);TRACED(", ");TRACEV(p_.second);TRACED(")");
template<typename... Args> void TRACEV(tuple<Args...> t){TRACET(t);}
template<typename l, typename r> void TRACEV(pair<l,r> t){TRACEP(t);}
template<template<typename...> class T, typename... K> void TRACEV(T<K...> t){if(t.empty()){TRACEV("[]");return;}auto it = t.begin();
TRACED("[");TRACEV(*it);for(++it;it!=t.end();++it){TRACED(", ");TRACEV(*it);}TRACED("]");}
template<typename T> void TRACE(T t){TRACEV(t);_N;}
template<typename T,typename... Ts> void TRACE(T t,Ts... args){TRACEV(t); _T; TRACE(args...);}

#define ll long long int
#define ull unsigned long long int
#define pii pair<int,int>

vector<vector<bool>> board;
int N,M;
vector<vector<int>> tiles;
vector<vector<int>> tilesC;
vector<int> tis;
vector<int> tcs;
int bestR = -1;

bool check_column(int c, int r, int& ti, int& tc){
	if(board[r][c]) ++tc;
	else{
		if(tc > 0){
			if(tilesC[c].empty() || tc != tilesC[c][ti]) return false;
			else{
				tc = 0;
				++ti;
			}
		}
	}
	if(r == N - 1){
		if(tc > 0){
			if(tilesC[c].empty() || tc != tilesC[c][ti]) return false;
			else{
				tc = 0;
				++ti;
			}
		}
	}
	return true;
}

bool check_row(int r){
	FOR(i,M){
		if(!check_column(i,r,tis[i],tcs[i]))return false;
	}
	if(r == N-1){
		FOR(i,N){
			FOR(j,M){
				cout<<board[i][j];
			}
			cout<<'\n';
		}
		exit(0);
	}
	return true;
}

void fill_row(int r, int cs, int ti){
	if(r > bestR){
		bestR = r;
		TRACE(r,"Row Reached");
	}
	if(r==N) return;
	if(ti == tiles[r].size()){
		if(cs <= M+1){
			vector<int> tisc = tis, tcsc = tcs;
			if(check_row(r)){
				fill_row(r+1,0,0);
				tis = tisc; tcs = tcsc;
			}
			else{
				tis = tisc; tcs = tcsc;
				return;
			}
		}
		else return;
	}
	else{
		if(cs < M){
			FOR(j,M-tiles[r][ti]-cs+1){
				FOR(i,tiles[r][ti]){
					board[r][cs+i+j] = true;
				}
				fill_row(r,cs+tiles[r][ti]+1+j,ti+1);
				FOR(i,tiles[r][ti]){
					board[r][cs+i+j] = false;
				}
			}
		}
	}
}

int main(){
	cin.tie(0);
	ios::sync_with_stdio(false);
	cin>>N>>M;
	board.resize(N,vector<bool>(M,false));
	tiles.resize(N);
	tilesC.resize(M);
	int S;
	FOR(i,N){
		cin>>S;
		tiles[i].resize(S);
		FOR(j,S){
			cin>>tiles[i][j];
		}
	}
	FOR(i,M){
		cin>>S;
		tilesC[i].resize(S);
		FOR(j,S){
			cin>>tilesC[i][j];
		}
	}
	tis.resize(M,0);
	tcs.resize(M,0);
	TRACE("DATA IN");
	fill_row(0,0,0);
	return 0;
}