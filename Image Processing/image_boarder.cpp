#include <bits/stdc++.h>

using namespace std;

#define FOR(i_,a_) for(int i_=0;i_<a_;++i_)
#define FORS(s_,i_,a_) for(int i_=s_;i_<a_;++i_)
#define FORR(i_,a_) for(int i_=a_-1;i_>=0;--i_)
#define FORI(i_,a_) for(int i_=1;i_<=a_;++i_)
#define FORA(i_,a_) for(auto i_:a_)
#define FOR1(i_,a_) for(int i_=1;i_<a_;++i_)
#define FORIT(it_,c_) for(auto it_ = c_.begin(); it_!=c_.end();++it_)

#define pii pair<int,int>

int W,H,E;
#define coorToIndex(x,y) y*W + x
#define coorInBound(x,y) 0<=x && x < W && 0<=y && y < H
#define iTCX(ind) ind%W
#define iTCY(ind) ind/W
#define withinError(a,b) (a-b)*(a-b) <= E
#define swap(x,y) x^=y^=x^=y
vector<int> image;
vector<int> groups;
vector<int> groupSize;
vector<pii> boarders;
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
	boarders[aP].first = coorToIndex(min(iTCX(boarders[aP].first),iTCX(boarders[bP].first)),min(iTCY(boarders[aP].first),iTCY(boarders[bP].first)));
	boarders[aP].second = coorToIndex(max(iTCX(boarders[aP].second),iTCX(boarders[bP].second)),max(iTCY(boarders[aP].second),iTCY(boarders[bP].second)));
}

int main(){
	// cin.tie(0);
	// ios::sync_with_stdio(false);
	cin>>W>>H>>E;
	image.resize(W*H);
	boarders.resize(W*H);
	
	FOR(y,H){
		FOR(x,W){
			cin>>image[coorToIndex(x,y)];
			roots.insert(roots.end(),coorToIndex(x,y));
			boarders[coorToIndex(x,y)] = {coorToIndex(x,y),coorToIndex(x,y)};
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
	cout<<roots.size()<<'\n';
	FORA(ele,roots){
		cout<<iTCX(boarders[ele].first)<<' '<<iTCY(boarders[ele].first)<<' '<<iTCX(boarders[ele].second)<<' '<<iTCY(boarders[ele].second)<<'\n';
	}
	return 0;
}