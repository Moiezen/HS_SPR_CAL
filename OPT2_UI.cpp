#include <windows.h>
#include <bits/stdc++.h>
#include <graphics.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define setb setbkcolor
#define setc setcolor
#define setf setfillcolor
#define sett settextjustify
#define refresh delay_ms(0)
#define addd(a,b,c,d,e,f,g,h) doms.push_back(domaincons(rectcons(a,b,c,d),e,f,g,h));
using namespace std;
enum kpm{
	ayb,bc,jb,sjdf,hjys,syzl,hrlq,dy,tw,glfz,ljsc,ljfs,lj
};
enum scm{
	msyzl,mhrlq,mdy,mtw,mglfz,mljsc,dfyx,dfsc,nul
};
string s2str(scm a){
	switch(a){
		case msyzl:{
			return "鱼灵";
			break;
		}
		case mhrlq:{
			return "老千";
			break;
		}
		case mdy:{
			return "刀油";
			break;
		}
		case mtw:{
			return "腾武";
			break;
		}
		case mglfz:{
			return "鬼灵";
			break;
		}
		case mljsc:{
			return "垃圾";
			break;
		}
		case dfyx:{
			return "对手";
			break;
		}
		case dfsc:{
			assert(0);
			break;
		}
		case nul:{
			return "";
			break;
		}
		default:{
			assert(0);
			break;
		}
	}
}
string k2str(kpm a){
	switch(a){
		case syzl:{
			return "鱼灵";
			break;
		}
		case hrlq:{
			return "老千";
			break;
		}
		case dy:{
			return "刀油";
			break;
		}
		case tw:{
			return "腾武";
			break;
		}
		case glfz:{
			return "鬼灵";
			break;
		}
		case ljsc:{
			return "随从";
			break;
		}
		case ayb:{
			return "暗步";
			break;
		}
		case bc:{
			return "背刺";
			break;
		}
		case jb:{
			return "硬币";
			break;
		}
		case sjdf:{
			return "伺机"; 
			break;
		}
		case hjys:{
			return "幻药";
			break;
		}
		case ljfs:{
			return "法术";
			break;
		}
		case lj:{
			return "垃圾";
			break;
		}
		default:{
			assert(0);
			break;
		} 
	}
}
kpm s2k(scm a){
	switch(a){
		case msyzl:{
			return syzl;
			break;
		}
		case mhrlq:{
			return hrlq;
			break;
		}
		case mdy:{
			return dy;
			break;
		}
		case mtw:{
			return tw;
			break;
		}
		case mglfz:{
			return glfz;
			break;
		}
		case mljsc:{
			return ljsc;
			break;
		}
		default:{
			assert(0);
			break;
		}
	}
}
scm k2s(kpm a){
	switch(a){
		case syzl:{
			return msyzl;
			break;
		}
		case hrlq:{
			return mhrlq;
			break;
		}
		case dy:{
			return mdy;
			break;
		}
		case tw:{
			return mtw;
			break;
		}
		case glfz:{
			return mglfz; 
			break;
		}
		case ljsc:{
			return mljsc;
			break;
		}
		default:{
			assert(0);
			break;
		}
	}
}
bool legalk2s(kpm a){
	switch(a){
		case syzl:
		case hrlq:
		case dy:
		case tw:
		case glfz:
		case ljsc:{
			return true;
			break;
		}
		default:{
			return false;
			break;
		}
	}
}
//敌方英雄-可以是鬼灵匪贼的目标
//敌方随从-可以是背刺的目标
//空目标
//以上虚目标均归入随从名以简化操作目标
int bcost(scm a){
	switch(a){
		case msyzl:{
			return 4;
			break;
		}
		case mhrlq:{
			return 2;
			break;
		}
		case mdy:{
			return 4;
			break;
		}
		case mtw:{
			return 2;
			break;
		}
		case mglfz:{
			return 6;
			break;
		}
		case mljsc:{
			return 20;
			break;
		}
		case dfyx:{
			assert(0);
			break;
		}
		case dfsc:{
			assert(0);
			break;
		}
		default:{
			assert(0);
			break;
		}
	}
}
struct card{
	kpm name;
	int cost;
	//int health;
};
card cardcons(kpm a,int b){
	card c;
	c.name=a;
	c.cost=b;
	return c;
}
struct minion{
	scm name;
	//int health;
};
minion minioncons(scm a){
	minion b;
	b.name=a;
	return b;
}
//已假设 背刺只用于去除老千和腾武 而鬼灵匪贼总能去除
struct aura{
	int asjdf;
	int ahrlq;
	int ady1;
	int ady2;
};
aura auracons(int a,int b,int c,int d){
	aura e;
	e.asjdf=a;
	e.ahrlq=b;
	e.ady1=c;
	e.ady2=d;
	return e;
}
aura emptyau=auracons(0,0,0,0);
struct state{
	card hands[10];int H;
	minion fields[7];int F;
	aura auras;
	int mana;
	int num;
};
state emptystcons(){
	state a;
	a.H=0;
	a.F=0;
	a.auras=emptyau;
	a.mana=0;
	a.num=0;
	return a;
}
state emptyst=emptystcons();
struct ope{
	int cost;
	kpm name;
	scm target;
};
//由于随从暂时不区分血量，操作目标仅需要随从名，且已可以包括敌方英雄，敌方随从，空目标 
ope opecons(int a,kpm b,scm c){
	ope d;
	d.cost=a;
	d.name=b;
	d.target=c;
	return d;
}
bool rmv1(minion*a,int&n,scm b){
	rep(i,0,n-1){
		if(a[i].name==b){
			rep(j,i+1,n-1) a[j-1]=a[j];
			n--;
			return true;
		}
	}
	return false;
}
bool rmv2(card*a,int&n,kpm b,int c){
	rep(i,0,n-1){
		if(a[i].name==b&&a[i].cost==c){
			rep(j,i+1,n-1) a[j-1]=a[j];
			n--;
			return true;
		}
	}
	return false;
}

pair<state,int> badpair=make_pair(emptyst,-999999);

const int hlim=10;
const int mlim=7;
const int manalim=10;

const int sjdflim=1;
const int hrlqlim=3;
const int dy1lim=2;
const int dy2lim=2;

int twice(state st){
	rep(i,0,st.F-1)
		if(st.fields[i].name==msyzl){
			return 2;
		}
	return 1;
}

int openmode;

pair<state,int> trans(state st,ope op){
	int dmg=0;
	bool flag=true;
	switch(op.name){
		case ayb:{
			flag=rmv2(st.hands,st.H,op.name,op.cost);
			if(!flag) return badpair;
			flag=rmv1(st.fields,st.F,op.target);
			if(!flag) return badpair;
			st.mana-=max(op.cost-st.auras.asjdf*2-st.auras.ady1*3,0);
			if(st.mana<0) return badpair;
			
			st.hands[st.H++]=cardcons(s2k(op.target),bcost(op.target)-2);
			st.auras.asjdf=0;
			st.auras.ady1=st.auras.ady2;
			st.auras.ady2=0;
			st.num++;
			break;
		}
		case bc:{
			//暂时未考虑区分背刺敌方随从和背刺血量>2的友方随从，统一记作null，且认为总能这么做 
			//用作去除时，仅考虑去除狐人老千和赤烟腾武 
			flag=rmv2(st.hands,st.H,op.name,op.cost);
			if(!flag) return badpair;
			if(op.target==nul){
				if(openmode==0){
					flag=false;
					rep(i,0,st.F-1){
						if(st.fields[i].name==msyzl||st.fields[i].name==mdy||st.fields[i].name==mglfz){
							flag=true;
							break;
						}
					}
					if(!flag) return badpair;
				}
			}
			else{
				flag=(op.target==mhrlq)||(op.target==mtw);
				if(!flag) return badpair;
				flag=rmv1(st.fields,st.F,op.target);
				if(!flag) return badpair;
			} 
			st.mana-=max(op.cost-st.auras.asjdf*2-st.auras.ady1*3,0);
			if(st.mana<0) return badpair;
			
			st.auras.asjdf=0;
			st.auras.ady1=st.auras.ady2;
			st.auras.ady2=0;
			st.num++;
			break;
		}
		case jb:{
			flag=rmv2(st.hands,st.H,op.name,op.cost)&&(op.target==nul);
			if(!flag) return badpair;
			st.mana-=max(op.cost-st.auras.asjdf*2-st.auras.ady1*3,0);
			if(st.mana<0) return badpair;
			
			st.mana=min(st.mana+1,manalim);
			st.auras.asjdf=0;
			st.auras.ady1=st.auras.ady2;
			st.auras.ady2=0;
			st.num++;
			break;
		}
		case sjdf:{
			flag=rmv2(st.hands,st.H,op.name,op.cost)&&(op.target==nul);
			if(!flag) return badpair;
			st.mana-=max(op.cost-st.auras.asjdf*2-st.auras.ady1*3,0);
			if(st.mana<0) return badpair;
			
			st.auras.asjdf=1;
			st.auras.ady1=st.auras.ady2;
			st.auras.ady2=0;
			st.num++;
			break;
		}
		case hjys:{
			flag=rmv2(st.hands,st.H,op.name,op.cost)&&(op.target==nul);
			if(!flag) return badpair;
			st.mana-=max(op.cost-st.auras.asjdf*2-st.auras.ady1*3,0);
			if(st.mana<0) return badpair;
			
			rep(i,0,st.F-1){
				if(st.H>=hlim) break; 
				st.hands[st.H++]=cardcons(s2k(st.fields[i].name),1);
			}
			st.auras.asjdf=0;
			st.auras.ady1=st.auras.ady2;
			st.auras.ady2=0;
			st.num++;
			break;
		}
		case syzl:{
			flag=rmv2(st.hands,st.H,op.name,op.cost)&&(op.target==nul);
			if(!flag) return badpair;
			if(st.F>=mlim) flag=false;
			else st.fields[st.F++]=minioncons(k2s(op.name));
			if(!flag) return badpair;
			st.mana-=max(op.cost-st.auras.ady1*3,0);
			if(st.mana<0) return badpair;
			
			st.auras.ady1=st.auras.ady2;
			st.auras.ady2=0;
			st.num++;
			break;
		}
		case hrlq:{
			int twi=twice(st);
			flag=rmv2(st.hands,st.H,op.name,op.cost)&&(op.target==nul);
			if(!flag) return badpair;
			if(st.F>=mlim) flag=false;
			else st.fields[st.F++]=minioncons(k2s(op.name));
			if(!flag) return badpair;
			st.mana-=max(op.cost-st.auras.ady1*3,0);
			if(st.mana<0) return badpair;
			
			st.auras.ahrlq=min(st.auras.ahrlq+twi,hrlqlim);
			st.auras.ady1=st.auras.ady2;
			st.auras.ady2=0;
			st.num++;
			break;
		}
		case dy:{
			int twi=twice(st);
			flag=rmv2(st.hands,st.H,op.name,op.cost)&&(op.target==nul);
			if(!flag) return badpair;
			if(st.F>=mlim) flag=false;
			else st.fields[st.F++]=minioncons(k2s(op.name));
			if(!flag) return badpair;
			st.mana-=max(op.cost-st.auras.ahrlq*2-st.auras.ady1*3,0);
			if(st.mana<0) return badpair;
			
			st.auras.ahrlq=0;
			if(st.num){
				st.auras.ady1=min(st.auras.ady2+twi,dy1lim);
				st.auras.ady2=twi;
			}
			else{
				st.auras.ady1=st.auras.ady2;
				st.auras.ady2=0;
			}
			st.num++;
			break;
		}
		case tw:{
			flag=rmv2(st.hands,st.H,op.name,op.cost);
			if(!flag) return badpair;
			if(st.F>=mlim) flag=false;
			else st.fields[st.F++]=minioncons(k2s(op.name));
			if(!flag) return badpair;
			if(op.target==nul&&st.F==1){
				//空场，腾武可空交 
			}
			else{
				flag=rmv1(st.fields,st.F,op.target);
				if(!flag) return badpair;
				st.hands[st.H++]=cardcons(s2k(op.target),1);
			}
			st.mana-=max(op.cost-st.auras.ady1*3,0);
			if(st.mana<0) return badpair;
			
			st.auras.ady1=st.auras.ady2;
			st.auras.ady2=0;
			st.num++;
			break;
		}
		case glfz:{
			int twi=twice(st);
			flag=rmv2(st.hands,st.H,op.name,op.cost);
			if(!flag) return badpair;
			if(st.F>=mlim) flag=false;
			else st.fields[st.F++]=minioncons(k2s(op.name));
			if(!flag) return badpair;
			if(op.target==dfyx){
				dmg=st.num*twi;
			}
			else{
				//应用总能去除的假定 
				bool flag=rmv1(st.fields,st.F,op.target);
				if(!flag) return badpair;
			}
			st.mana-=max(op.cost-st.auras.ahrlq*2-st.auras.ady1*3,0);
			if(st.mana<0) return badpair;
			
			st.auras.ahrlq=0;
			st.auras.ady1=st.auras.ady2;
			st.auras.ady2=0;
			st.num++;
			break;
		}
		case ljsc:{
			//假设为无词条随从，不适用于吉尔尼斯 
			bool flag=rmv2(st.hands,st.H,op.name,op.cost)&&(op.target==nul);
			if(!flag) return badpair;
			if(st.F>=mlim) flag=false;
			else st.fields[st.F++]=minioncons(k2s(op.name));
			if(!flag) return badpair;
			st.mana-=max(op.cost-st.auras.ady1*3,0);
			if(st.mana<0) return badpair;
			
			st.auras.ady1=st.auras.ady2;
			st.auras.ady2=0;
			st.num++;
			break;
		}
		case ljfs:{
			bool flag=rmv2(st.hands,st.H,op.name,op.cost)&&(op.target==nul);
			if(!flag) return badpair;
			st.mana-=max(op.cost-st.auras.asjdf*2-st.auras.ady1*3,0);
			if(st.mana<0) return badpair;
			
			st.auras.asjdf=0;
			st.auras.ady1=st.auras.ady2;
			st.auras.ady2=0;
			st.num++;
			break;
		}
		case lj:{
			return badpair;
			break;
		}
	}
	return make_pair(st,dmg);
}

bool coinopt(state a){
	if(a.mana<manalim&&a.auras.ady1==0&&a.auras.ady2==0&&a.auras.asjdf==0){
		rep(i,0,a.H-1){
			if(a.hands[i].name==jb&&a.hands[i].cost==0) return true;
		}
		return false;
	}
	return false;
}

struct opes{
	vector<ope> opes;
	~opes(){
		opes.clear();
	}
};
opes emptyoscons(){
	opes a;
	a.opes.clear();
	return a;
}
opes emptyos=emptyoscons();

opes offer(state a){
	opes os;
	os.opes.clear();
	
	if(coinopt(a)){
		os.opes.push_back(opecons(0,jb,nul));
		return os;
	}
	
	rep(i,0,a.H-1){
		int co=a.hands[i].cost;
		kpm na=a.hands[i].name;
		bool dup=false;
		rep(j,0,i-1){
			if(a.hands[j].cost==co&&a.hands[j].name==na){
				dup=true;
				break;
			}
		}
		if(dup) continue;
		
		if(na==ayb||na==bc||na==tw||na==glfz){
			rep(j,0,a.F-1){
				bool dup2=false; 
				rep(k,0,j-1){
					if(a.fields[j].name==a.fields[k].name){
						dup2=true;
						break;
					}
				}
				if(dup2) continue;
				os.opes.push_back(opecons(co,na,a.fields[j].name));
			}
		}
		if(na==glfz){
			os.opes.push_back(opecons(co,na,dfyx));
		}
		if(na==bc||na==jb||na==sjdf||na==hjys||na==hrlq||na==dy||na==tw||na==syzl||na==ljsc||na==ljfs){
			os.opes.push_back(opecons(co,na,nul));
		}
		//以上提过，暂不考虑dfsc 
	}
	return os;
}

string o2s(ope o){
	string s="";
	s=s+k2str(o.name);
	s=s+"(";
	s=s+to_string(o.cost);
	s=s+")";
	if(o.target!=nul){
		s=s+"->"+s2str(o.target);
	}
	s=s+"\n";
	return s;
}

string output(opes o,int d,int u){
	string s="";
	if(u==1) s+="(达标掐断)\n";
	if(u==2) s+="(时限掐断)\n";
	for(auto i:o.opes){
		s=s+o2s(i);
	}
	s=s+to_string(d)+"\n";
	return s;
}

struct syn{
	pair<state,int> pa;
	//当前状态与累计伤害 
	double pri;
	//优先级 
	opes os;
	//操作序列 
};
syn syncons(pair<state,int> a,double b,opes c){
	syn d;
	d.pa=a;
	d.pri=b;
	d.os=c;
	return d;
}
bool operator<(syn a,syn b){
	return a.pri<b.pri;
}

int o2i(ope a){
	return a.cost+a.name*100+a.target*10000+93589;
}
int iseq[999],isn;
const int flim=4;

const double rho=0.5;

typedef unsigned long long ull;
ull ishash(int l,int r,int*s){
	ull t=0;
	rep(i,l,r){
		if(i<0) t=t*19260817+910570131/(-i);
		else t=t*19260817+s[i];
	}
	return t;
}
map<ull,double> value;

struct quiz{
	state qst;
	int qnd;
};
quiz emptyqcons(){
	quiz q;
	q.qst=emptystcons();
	q.qnd=0;
	return q;
}

namespace config{
	int need,tlim;
	
	int collect,addquiz,print;
	
	int exbound,optimize,pureformula;
	
	double bound;
	
	int test,testcnt;
}
using namespace config;

int done,curdmg;
opes curos;
int tbegin;

double optf(double x,double y){
	return log(x/y);
}

const double sumbasic=1.;

vector<opes> cls;
vector<opes> allcls;
int clsbd=10;

vector<quiz> quizs;

void solve(syn q){
	if(q.pa.second>=curdmg){
		if(collect==1&&q.pa.second>=clsbd){
			if(q.pa.second>curdmg) cls.clear();
			cls.push_back(q.os);
		}
		curos=q.os;
		curdmg=q.pa.second;
	}
	if(q.pa.second>=need){
		done=1;
		return;
	}
	if(time(0)>tbegin+tlim){
		done=2;
		return;
	}
	if(exbound==1&&q.pri<bound){
		return;
	}
	
	if(optimize==1){
		isn=0;
		for(auto i:q.os.opes){
			iseq[isn++]=o2i(i);
		}
	}
	
	opes of=offer(q.pa.first);
	
	vector<double> sums;
	double sum,allsum,lost;
	
	if(optimize==1){
		sums.clear();
		allsum=0;
		
		for(auto i:of.opes){
			iseq[isn++]=o2i(i);
			
			sum=sumbasic;
			rep(i,(isn-1)-flim+1,isn-1){
				sum+=value[ishash(i,isn-1,iseq)];
			}
			sums.push_back(sum);
			allsum+=sum;
			isn--;
		}
	}
	
	int j=0;
	for(auto i:of.opes){
		opes os=q.os;
		os.opes.push_back(i);
		
		if(optimize==1){
			lost=optf(sums[j++],allsum);
		}
		if(optimize==0){
			lost=-1.;
		}
		
		if(pureformula==1&&sums[j-1]-sumbasic<1e-6){
			//cerr<<sums[j-1]<<" "<<allsum<<endl;
			//cerr<<lost<<endl;
		}
		else{
			pair<state,int> p=trans(q.pa.first,i);if(test==1) testcnt++;
			solve(syncons(make_pair(p.first,q.pa.second+p.second),q.pri+lost,os));
			if(done>0) return;
			
		}
		
	}
}

const double boundbasic=10.;

const int _need_max=999;

string _solve(state st,int _need,int _tlim,int _collect,int _addquiz,int _print,int _exbound,int _optimize,int _pureformula,int _test){
	if(_need<_need_max&&_collect==1) assert(0);
	//同时开启需求截断和收集会污染数据 
	
	need=_need;
	done=curdmg=0;
	curos=emptyos;
	
	tlim=_tlim;
	tbegin=time(0);
	
	collect=_collect;
	addquiz=_addquiz;
	print=_print;
	
	exbound=_exbound;
	optimize=_optimize;
	pureformula=_pureformula;
	test=_test;
	//复制参数 
	
	if(collect==1) cls.clear();
	if(test==1) testcnt=0;
	
	if(exbound==0){
		bound=1e9;
		solve(syncons(make_pair(st,0),0,emptyos));
	}
	if(exbound==1){
		bound=-boundbasic;
		solve(syncons(make_pair(st,0),0,emptyos));
		while(done==0){
			bound-=boundbasic;
			solve(syncons(make_pair(st,0),0,emptyos));
		}
	}
	
	//if(print==1) show(curos,curdmg);
	if(collect==1&&done==0){
		if(curdmg>=clsbd){
			allcls.insert(allcls.end(),cls.begin(),cls.end());
		}
	}
	if(addquiz==1&&done==0){
		if(curdmg>=clsbd){
			quiz q=emptyqcons();
			q.qnd=curdmg;
			q.qst=st;
			quizs.push_back(q);
		}
	}
	
	return output(curos,curdmg,done);
}

void Load(){
	FILE* f=freopen("fml.txt","r",stdin);
	
	value.clear();
	
	ull p,r;
	double q;
	while(scanf("%llu%llu",&p,&r)==2){
		q=*(double*)(&r);
		value[p]=q;
	}
	
	fclose(stdin);
}

//////////////////////////////////////////////

//////////////////////////////////////////////

int H=640;
int W=1280;

struct rect{
	int x1,y1,x2,y2;
};
rect rectcons(int a,int b,int c,int d){
	rect r;
	r.x1=a;r.y1=b;r.x2=c;r.y2=d;
	return r;
}
rect norect=rectcons(-1,-1,-1,-1);
rect cutedge(rect a,int b){
	return rectcons(a.x1+b,a.y1+b,a.x2-b,a.y2-b);
}
void barr(rect a,color_t b){
	setf(b);
	bar(a.x1,a.y1,a.x2,a.y2);
}
void textr(rect a,color_t b,string c){
	setc(b);
	sett(CENTER_TEXT,CENTER_TEXT);
	outtextxy((a.x1+a.x2)/2,(a.y1+a.y2)/2,c.c_str());
}
void textra(rect a,color_t b,string c){
	setc(b);
	sett(LEFT_TEXT,TOP_TEXT);
	int xx=a.x1+5,yy=a.y1+5;
	while(c!=""){
		int p=c.find("\n");
		outtextxy(xx,yy,c.substr(0,p).c_str());
		c=c.substr(p+1,c.size());
		yy+=20;
	}
	
}
bool inrect(int x,int y,rect a){
	return x>=a.x1&&x<a.x2&&y>=a.y1&&y<a.y2;
}

enum domt{
	nodomt,vnx,vx,vn,cn,cx,go,ans,vxa,lk,lk1,lk2,vxb
};
struct domain{
	rect r;
	domt type;
	string name;
	int x;
	int id;
};
domain domaincons(rect a,domt b,string c,int d,int e){
	domain dom;
	dom.r=a;dom.type=b;dom.name=c;dom.x=d;dom.id=e;
	return dom;
}
domain nodomain=domaincons(norect,nodomt,"",-1,-1);
bool indom(int x,int y,domain a){
	return inrect(x,y,a.r);
}

color_t bgc=EGERGB(255,255,255);
color_t bdc=EGERGB(0,0,0);
color_t slc=EGERGB(0,255,0);
color_t txc=EGERGB(0,0,255);

void init(){
	initgraph(W,H);
	setb(bgc);
}

rect _all=rectcons(0,0,1280,640);
rect _start=rectcons(1160,560,1280,640);

void drawatt(){
	textr(_all,txc,"点击开始，代表你已经阅读过https://github.com/Moiezen/HS_SPR_CAL的README.md，并且该UI.exe是直接获取的最新版本");
	
	barr(_start,bdc);
	barr(cutedge(_start,1),bgc);
	textr(_start,txc,"开始");
}

void attention(){
	drawatt();
	refresh;
	
	mouse_msg e={0};
	while(true){
		while(mousemsg()){
            e=getmouse();
        }
        
        if(e.is_down()&&inrect(e.x,e.y,_start)){
        	return;
		}
	}
}

vector<domain> doms;
domain selected;
int manadomid;
int cardsdomid[10];
int minionsdomid[7];
int ansdomid;
int ehdomid;
int tlimdomid;
int lkdomid;
int modedomid;

domain id2dom(int id){
	vector<domain>::iterator i=doms.begin();
	while(i!=doms.end()){
		if(id==(*i).id){
			return (*i);
			break;
		}
		i++;
	}
	return nodomain;
}

void follow(domain a){
	vector<domain>::iterator i=doms.begin();
	while(i!=doms.end()){
		if(a.id==(*i).id){
			(*i)=a;
			break;
		}
		i++;
	}
}

string n1[14]={"鱼灵","老千","刀油","鬼灵","腾武","暗步","背刺","硬币","伺机","幻药","随从","法术","垃圾","清除"};
string defaultlk="D:\\Hearthstone";

void getdoms(){
	doms.clear();
	addd(860,600,920,640,vx,"水晶",0,manadomid=1);
	//1
	rep(i,0,9) addd(200+i*60,600,260+i*60,640,vnx,"清除",0,cardsdomid[i]=2+i);
	//2 ... 11
	rep(i,0,6) addd(200+i*60,560,260+i*60,600,vn,"清除",0,minionsdomid[i]=101+i);
	//101 ... 107
	rep(i,0,10) addd((i+2)%3*40,400+(i+2)/3*40,40+(i+2)%3*40,440+(i+2)/3*40,cx,"",i,12+i);
	//12 ... 22
	rep(i,0,13) addd(i%3*40,200+i/3*40,40+i%3*40,240+i/3*40,cn,n1[i],0,123+i);
	//123 ... 136
	addd(1220,600,1280,640,go,"计算",0,37);
	//37
	addd(1000,0,1280,560,ans,"",0,ansdomid=38);
	//38
	addd(980,600,1040,640,vxa,"时限",15,tlimdomid=39);
	//39
	addd(1100,600,1160,640,vxa,"目标",999,ehdomid=40);
	//40
	addd(0,0,400,40,lk,defaultlk,0,lkdomid=41);
	//41
	addd(0,40,60,80,lk1,"修改",0,42);
	//42
	addd(60,40,120,80,lk2,"读取",0,43);
	//43
	addd(0,80,120,120,vxb,"背刺可用",1,modedomid=44);
	//44
}

kpm str2k(string s){
	if(s=="暗步") return ayb;
	if(s=="背刺") return bc;
	if(s=="硬币") return jb;
	if(s=="伺机") return sjdf;
	if(s=="幻药") return hjys;
	if(s=="鱼灵") return syzl;
	if(s=="老千") return hrlq;
	if(s=="刀油") return dy;
	if(s=="腾武") return tw;
	if(s=="鬼灵") return glfz;
	if(s=="法术") return ljfs;
	if(s=="随从") return ljsc;
	if(s=="垃圾") return lj;
	return lj;
}

int __eh=999;
int __tlim=999999;

state doms2st(vector<domain> a){
	openmode=id2dom(modedomid).x;
	
	__eh=id2dom(ehdomid).x;
	__tlim=id2dom(tlimdomid).x;
	
	state st;
	domain tmp;
	
	st.H=0;
	rep(i,0,9){
		tmp=id2dom(cardsdomid[i]);
		if(tmp.name!="清除") st.hands[st.H++]=cardcons(str2k(tmp.name),tmp.x);
	}
	
	st.F=0;
	rep(i,0,6){
		tmp=id2dom(minionsdomid[i]);
		if(tmp.name!="清除") st.fields[st.F++]=minioncons(k2s(str2k(tmp.name))); 
	}
	
	st.auras=emptyau;
	st.mana=id2dom(manadomid).x;
	st.num=0;
	return st;
}

void st2doms(state st){
	domain tmp;
	rep(i,0,st.H-1){
		tmp=id2dom(cardsdomid[i]);
		tmp.name=k2str(st.hands[i].name);
		tmp.x=st.hands[i].cost;
		follow(tmp);
	}
	rep(i,st.H,9){
		tmp=id2dom(cardsdomid[i]);
		tmp.name="清除";
		tmp.x=0;
		follow(tmp);
	}
	
	rep(i,0,st.F-1){
		tmp=id2dom(minionsdomid[i]);
		tmp.name=s2str(st.fields[i].name);
		follow(tmp);
	}
	rep(i,st.F,6){
		tmp=id2dom(minionsdomid[i]);
		tmp.name="清除";
		follow(tmp);
	}
	
	domain _mana=id2dom(manadomid);
	_mana.x=st.mana;
	follow(_mana);
}

void drawdom(domain a,bool sl){
	rect r=a.r;
	
	barr(r,bdc);
	if(sl){
		barr(cutedge(r,1),slc);
		barr(cutedge(r,5),bgc);
	}
	else{
		barr(cutedge(r,1),bgc);
	}
	
	switch(a.type){
		case nodomt:{
			
			break;
		}
		case vnx:{
			if(a.name=="清除") textr(r,txc,"");
			else textr(r,txc,a.name+to_string(a.x));
			break;
		}
		case vx:
		case vxa:
		case vxb:{
			textr(r,txc,a.name+to_string(a.x));
			break;
		}
		case vn:{
			if(a.name=="清除") textr(r,txc,"");
			else textr(r,txc,a.name);
			break;
		}
		case cn:
		case go:
		case lk1:
		case lk2:{
			textr(r,txc,a.name);
			break;
		}
		case cx:{
			textr(r,txc,to_string(a.x));
			break;
		}
		case ans:{
			textra(r,txc,a.name);
			break;
		}
		case lk:{
			textr(r,txc,a.name+"\\Logs\\power.log");
			break;
		} 
	}
}

void loaddoms(){
	setcaption("暗歌是猪");
	vector<domain>::iterator i=doms.begin();
	while(i!=doms.end()){
		drawdom(*i,0);
		i++;
	}
	selected=nodomain;
}

bool legalcn4vn(string s){
	if(s=="清除") return true;
	if(legalk2s(str2k(s))) return true;
	return false;
}

state autoread(string s);

void click(int x,int y){
	domain toselect=nodomain;
	vector<domain>::iterator i=doms.begin();
	while(i!=doms.end()){
		if(indom(x,y,*i)){
			toselect=*i;
			break;
		}
		i++;
	}
	switch(toselect.type){
		case nodomt:{
			
			break;
		}
		case vnx:
		case vn:
		case vx:
		case vxa:
		case vxb:{
			if(selected.id==toselect.id){
				drawdom(selected,0);
				selected=nodomain;
			}
			else{
				drawdom(selected,0);
				drawdom(toselect,1);
				selected=toselect;
			}
			break;
		}
		case cn:{
			if(selected.type==vnx||(selected.type==vn&&legalcn4vn(toselect.name))){
				selected.name=toselect.name;
				drawdom(selected,1);
				follow(selected);
			}
			break;
		}
		case cx:{
			if(selected.type==vx||selected.type==vnx){
				selected.x=toselect.x;
				drawdom(selected,1);
				follow(selected);
			}
			if(selected.type==vxa){
				if(toselect.x==0) selected.x=0;
				else selected.x=min(selected.x*10+toselect.x,999);
				drawdom(selected,1);
				follow(selected);
			}
			if(selected.type==vxb){
				selected.x=(bool)toselect.x;
				drawdom(selected,1);
				follow(selected);
			}
			break;
		}
		case go:{
			state st=doms2st(doms);
			domain ans=id2dom(ansdomid);
			ans.name=_solve(st,__eh,__tlim,0,0,0,1,1,0,0);
			drawdom(ans,0);
			follow(ans);
			break;
		}
		case ans:
		case lk:{
			
			break;
		}
		case lk1:{
			char _lk[100];
        	inputbox_getline("请输入炉石传说本地路径（回车确认）","宇宙甜心",_lk,100);
        	domain lk=id2dom(lkdomid);
        	lk.name=(string)_lk;
        	drawdom(lk,0);
        	follow(lk);
			break;
		}
		case lk2:{
			state st=autoread(id2dom(lkdomid).name);
			st2doms(st);
			rep(i,0,9) drawdom(id2dom(cardsdomid[i]),0);
			drawdom(id2dom(manadomid),0);
			break;
		}
	}
}

namespace autor{
	map<string,string> id2cid;
	map<string,string> id2cost;
	map<string,string> id2zone;
	map<string,string> id2err;
	
	void getafter(string s,string a,string&t){
		if(t!="") return;
		int p=s.find(a);
		if(p==-1) return;
		p=p+a.size();
		while(s[p]!=' '&&s[p]!='\0'){
			t=t+s[p];p++;
		}
	}
	void getid(string s,string&t){
		getafter(s,"tag=ENTITY_ID value=",t);
		getafter(s," id=",t);
	}
	void getcid(string s,string&t){
		getafter(s,"CardID=",t);
		getafter(s,"cardId=",t);
	}
	void getcost(string s,string&t){
		getafter(s,"tag=COST value=",t);
	}
	void getzone(string s,string&t){
		getafter(s,"tag=ZONE value=",t);
		getafter(s,"zone=",t);
	}
	
	int secrets;
	
	kpm cid2kpm(string s){
		if(s.find("EX1_144")!=-1) return ayb;
		if(s.find("CS2_072")!=-1) return bc;
		if(s.find("CFM_630")!=-1) return jb;
		if(s.find("COIN")!=-1) return jb;
		if(s.find("GAME_005")!=-1) return jb;
		if(s.find("EX1_145")!=-1) return sjdf;
		if(s.find("SCH_352")!=-1) return hjys;
		if(s.find("TRL_092")!=-1) return syzl;
		if(s.find("DMF_511")!=-1) return hrlq;
		if(s.find("BAR_552")!=-1) return dy;
		if(s.find("DMF_071")!=-1) return tw;
		if(s.find("ICC_910")!=-1) return glfz;
		if(s.find("DMF_512")!=-1) return ljfs;
		if(s.find("LOOT_214")!=-1&&secrets==0){
			secrets=1;
			return ljfs;
		}
		return lj;
	}
	
	vector<string> hand;
	state autost;
	void autore(string _s){
		autost=emptyst;
		//现在可能多次调用，需要每次清空 
		
		//更新结构： 
		//id->cid,cost,zone
		//resource(mana)
		//op->id,err
		//此处为简便，直接令op.id->err 
		
		cin.clear();
		//重置输入流，防止无法读取 
		
		freopen((_s+"\\Logs\\power.log").c_str(),"r",stdin);
		
		id2cid.clear();
		id2cost.clear();
		id2zone.clear();
		id2err.clear();
		hand.clear();
		
		string s,s0;
		string s1,s2,s3,s4;
		string s5,resources;
		string s6;
		
		int lines=0;
		
		while(getline(cin,s)){
			lines++;
			if(s.find("- CREATE_GAME")!=-1){
				id2cid.clear();
				id2cost.clear();
				id2zone.clear();
				id2err.clear(); 
				hand.clear();
			}
			
			while(s.find("-     SHOW_ENTITY")!=-1){
				getline(cin,s0);
				while(s0.find("-         tag=")!=-1){
					s=s+" "+s0;
					getline(cin,s0);
				}
				s1=s2=s3=s4="";
				getid(s,s1);
				getcid(s,s2);
				getcost(s,s3);
				getzone(s,s4);
				if(s1!=""){
					if(s2!="") id2cid[s1]=s2;
					if(s3!="") id2cost[s1]=s3;
					if(s4!="") id2zone[s1]=s4;
				}
				
				s=s0;
				//s0不属于这部分却已经被读入了，应当直接视为下一次的s 
				//且这个s可能立即属于新部分，故外层使用while 
			}
			
			if(s.find("TAG_CHANGE")!=-1){
				s1=s2=s3=s4=s5="";
				getid(s,s1);
				getcid(s,s2);
				getcost(s,s3);
				getzone(s,s4);
				getafter(s,"tag=RESOURCES value=",s5);
				if(s1!=""){
					if(s2!="") id2cid[s1]=s2;
					if(s3!="") id2cost[s1]=s3;
					if(s4!="") id2zone[s1]=s4;
				}
				if(s5!="") resources=s5;
				continue;
			}
			
			if(s.find("Options() - id=")!=-1) hand.clear();
			if(s.find("Options()")!=-1&&s.find("option")!=-1){
				s1=s6="";
				getid(s,s1);
				getafter(s,"error=",s6);
				if(s1!="") hand.push_back(s1);
				if(s1!=""&&s6!="") id2err[s1]=s6;
				//此处有可能存在error=项但项为空，不必区分 
			}
		}
		
		secrets=0;
		vector<string>::iterator i=hand.begin();
		while(i!=hand.end()){
			s1=*i;
			s2=id2cid[s1];
			s3=id2cost[s1];
			if(s3=="") s3="0";
			s4=id2zone[s1];
			if(s4=="HAND"||s4=="DECK"){
				//偶尔手牌会保持显示zone=DECK 
				//虽然很奇怪但能work 
				autost.hands[autost.H++]=cardcons(cid2kpm(s2),atoi(s3.c_str()));
			}
			s6=id2err[s1];
			if(cid2kpm(s2)==bc&&s6!=""){
				openmode=0;
				//模式检定，将无法直接通过bc->nul 
			}
			else openmode=1;
			
			id2zone[s1]="";
			//防止（可交易牌）被统计两次 
			i++;
		}
		
		autost.mana=atoi(resources.c_str());
		
		fclose(stdin);
	}
}
using namespace autor;
state autoread(string s){
	autore(s);
	return autost;
}

int main(){
	Load(); 
	
	ShowWindow(GetForegroundWindow(),0);
	
	init();
	attention();
	cleardevice();
	
	getdoms();
	loaddoms();
	refresh;

	mouse_msg e={0};
	int last=0;
	while(true){
		while(mousemsg()){
            e=getmouse();
        }
        
        if(!e.is_down()) last=0;
        else{
			if(last==0){
				//避免长点 
				click(e.x,e.y);
				refresh;
			}
        	last=1;
		}
	}

	closegraph();
	return 0;
}

