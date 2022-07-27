#include <bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
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
			return "对面脸";
			break;
		}
		case dfsc:{
			return "对面怪";
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
			return "垃圾随从"; 
			break;
		}
		case ayb:{
			return "暗影步";
			break;
		}
		case bc:{
			return "背刺";
			break;
		}
		case jb:{
			return "币";
			break;
		}
		case sjdf:{
			return "伺机待发"; 
			break;
		}
		case hjys:{
			return "幻觉药水";
			break;
		}
		case ljfs:{
			return "垃圾法术"; 
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
			return 99;
			break;
		}
		case dfsc:{
			return 88;
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
			if(op.target==nul&&st.F==0){
				//空场，腾武可空交 
			}
			else{
				bool flag=rmv1(st.fields,st.F,op.target);
				if(!flag) return badpair;
			}
			if(!flag) return badpair;
			st.mana-=max(op.cost-st.auras.ady1*3,0);
			if(st.mana<0) return badpair;
			
			st.hands[st.H++]=cardcons(s2k(op.target),1);
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

int getrand(int count,...){
	va_list v;
	int valuet;
	vector<int> value;
	int sum=0;
	
	va_start(v,count);
	
	while(count--){
		valuet=va_arg(v,int);
		value.push_back(valuet);
		sum+=valuet;
	}
	
	va_end(v);
	
	int r=rand()%sum;
	int n=0;
	for(auto i:value){
		r-=i;
		if(r<0) return n;
		n++;
	}
	assert(0);
}

card ctmp[99];
int cT;
void madd(int n,card c){
	while(n--) ctmp[cT++]=c;
}

state gen(){
	state st;
	
	cT=0;
	madd(getrand(2,1,5),cardcons(syzl,4));
	madd(getrand(3,4,3,1),cardcons(hrlq,2));
	madd(getrand(2,1,5),cardcons(dy,4));
	madd(getrand(3,0,1,1),cardcons(glfz,6));
	madd(getrand(2,1,3),cardcons(tw,2));
	madd(getrand(3,1,4,3),cardcons(ayb,0));
	madd(getrand(3,4,5,1),cardcons(hjys,4));
	madd(getrand(3,3,2,1),cardcons(jb,0));
	madd(getrand(3,3,4,1),cardcons(bc,0));
	madd(getrand(3,3,2,1),cardcons(sjdf,0));
	madd(getrand(2,1,1),cardcons(ljfs,1));
	
	random_shuffle(ctmp,ctmp+cT);
	st.H=min(cT,hlim);
	rep(i,0,st.H-1){
		st.hands[i]=ctmp[i];
	}
	
	st.F=0;
	st.auras=emptyau;
	st.mana=getrand(10,0,0,0,0,1,2,4,4,2,1);
	st.num=0;
	return st;
}

void Coll(){
	srand(1);
	
	allcls.clear();
	
	int N=1000,T=0,S=0;
	rep(i,1,N){
		state st=gen();
		_solve(st,_need_max,15,1,0,0,0,0,0,1);
		if(done==0) S++;T++;
		cerr<<"now "<<S<<" of "<<T<<endl;
	}
	
	value.clear();
	
	for(auto i:allcls){
		vector<ope> a=i.opes;
		
		isn=0;
		for(auto j:a){
			iseq[isn++]=o2i(j);
		}
		
		rep(i,0,isn-1) rep(j,i-flim+1,i-1){
			value[ishash(j,i,iseq)]+=exp(rho*(i-j));
		}
	}
	
	FILE* f=freopen("fml.txt","w",stdout);
	
	ull p,r;
	double q;
	for(auto i:value){
		p=i.first;q=i.second;
		r=*(ull*)(&q);
		printf("%llu %llu\n",p,r);
	}
	
	fclose(stdout);
}

void quizwrite(quiz q){
	printf("%d\n",q.qnd);
	
	printf("%d\n",(int)q.qst.H);
	rep(i,0,q.qst.H-1){
		printf("%d %d\n",q.qst.hands[i].name,q.qst.hands[i].cost);
	}
	printf("%d\n",(int)q.qst.F);
	rep(i,0,q.qst.F-1){
		printf("%d\n",q.qst.fields[i].name);
	}
	printf("%d ",q.qst.auras.asjdf);
	printf("%d ",q.qst.auras.ahrlq);
	printf("%d ",q.qst.auras.ady1);
	printf("%d\n",q.qst.auras.ady2);
	printf("%d ",q.qst.mana);
	printf("%d\n",q.qst.num);
}

void Genq(){
	srand(2);
	
	quizs.clear();
	
	int N=1000,T=0,S=0;
	rep(i,1,N){
		state st=gen();
		_solve(st,_need_max,15,0,1,0,0,0,0,1);
		if(done==0) S++;T++;
		cerr<<"now "<<S<<" of "<<T<<endl;
	}
	
	FILE* f=freopen("qiz.txt","w",stdout);
	
	for(auto i:quizs){
		quizwrite(i);
	}
	
	fclose(stdout);
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

quiz quizread(){
	quiz q=emptyqcons();
	int sc=scanf("%d",&q.qnd);
	if(sc!=1){
		q.qnd=-1;
		return q;
	}
	
	int n,s,a;
	sc=scanf("%d",&n);
	q.qst.H=0;
	while(n--){
		sc=scanf("%d %d",&s,&a);
		q.qst.hands[q.qst.H++]=cardcons((kpm)s,a);
	}
	sc=scanf("%d",&n);
	q.qst.F=0;
	while(n--){
		sc=scanf("%d%d",&s,&a);
		q.qst.fields[q.qst.F++]=minioncons((scm)s);
	}
	sc=scanf("%d",&q.qst.auras.asjdf);
	sc=scanf("%d",&q.qst.auras.ahrlq);
	sc=scanf("%d",&q.qst.auras.ady1);
	sc=scanf("%d",&q.qst.auras.ady2);
	sc=scanf("%d",&q.qst.mana);
	sc=scanf("%d",&q.qst.num);
	return q;
}

void Getq(){
	FILE* f=freopen("qiz.txt","r",stdin);
	
	quizs.clear();
	while(1){
		quiz q=quizread();
		if(q.qnd==-1) break;
		//if(quizs.size()>=1) break;
		quizs.push_back(q);
	}
	
	fclose(stdin);
}

void Test(int term){
	//term:
	//1 - nothing
	//2 - only exbound
	//3 - optimize with exbound
	//4 - optimize with pureformula
	//5 - optimize with exbound and pureformula
	int alltestcnt=0;
	int solvecnt=0;
	for(auto q:quizs){
		switch(term){
			case 1:{
				_solve(q.qst,q.qnd,15,0,0,0,0,0,0,1);
				break;
			}
			case 2:{
				_solve(q.qst,q.qnd,15,0,0,0,1,0,0,1);
				break;
			}
			case 3:{
				_solve(q.qst,q.qnd,15,0,0,0,1,1,0,1);
				break;
			}
			case 4:{
				_solve(q.qst,q.qnd,15,0,0,0,0,1,1,1);
				break;
			}
			case 5:{
				_solve(q.qst,q.qnd,15,0,0,0,1,1,1,1);
				break;
			}
		}
		alltestcnt+=testcnt;
		solvecnt+=(done==1);
	}
	cerr<<";;;"<<solvecnt<<";;;"<<alltestcnt<<endl;
}

state sample1cons(){
	state st;
	st.H=0;
	st.hands[st.H++]=cardcons(syzl,4);
	st.hands[st.H++]=cardcons(hrlq,2);
	st.hands[st.H++]=cardcons(dy,4);
	st.hands[st.H++]=cardcons(glfz,6);
	st.hands[st.H++]=cardcons(glfz,6);
	st.F=0;
	st.auras=emptyau;
	st.mana=6;
	st.num=0;
	return st;
}
state sample1=sample1cons();

int main(int argc,char* argv[]){
	//Coll();
	//Genq();
	
	Load();cerr<<"load complete"<<endl;
	Getq();cerr<<"getq complete"<<endl;
	
	Test(atoi(argv[1]));
	
	//Test(1);cerr<<"test1 complete"<<endl;
	//Test(2);cerr<<"test2 complete"<<endl;
	//Test(3);cerr<<"test3 complete"<<endl;
	//Test(4);cerr<<"test4 complete"<<endl;
	//Test(5);cerr<<"test5 complete"<<endl;
	
	//cout<<_solve(sample1,14,15,0,0,0,1,1,0,1)<<endl;
}
