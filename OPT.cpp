#include <bits/stdc++.h>
#include <windows.h>
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
	vector<card> hands;
	vector<minion> fields;
	aura auras;
	int mana;
	int num;
};
state emptystcons(){
	state a;
	a.hands.clear();
	a.fields.clear();
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
struct opes{
	vector<ope> opes;
};
opes emptyoscons(){
	opes a;
	a.opes.clear();
	return a;
}
opes emptyos=emptyoscons();
bool rmv1(vector<minion>&a,scm b){
	vector<minion>::iterator i=a.begin();
	while(i!=a.end()){
		if((*i).name==b){
			a.erase(i);
			return true;
		}
		i++;
	}
	return false;
}
bool rmv2(vector<card>&a,kpm b,int c){
	vector<card>::iterator i=a.begin();
	while(i!=a.end()){
		if((*i).name==b&&(*i).cost==c){
			a.erase(i);
			return true;
		}
		i++;
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
	vector<minion>::iterator i=st.fields.begin();
	while(i!=st.fields.end()){
		if((*i).name==msyzl){
			return 2;
		}
		i++;
	}
	return 1;
}

int tc=0;

pair<state,int> trans(state st,ope op){
	tc++;
	
	int dmg=0;
	bool flag=true;
	switch(op.name){
		case ayb:{
			flag=rmv2(st.hands,op.name,op.cost);
			if(!flag) return badpair;
			flag=rmv1(st.fields,op.target);
			if(!flag) return badpair;
			st.mana-=max(op.cost-st.auras.asjdf*2-st.auras.ady1*3,0);
			if(st.mana<0) return badpair;
			
			st.hands.push_back(cardcons(s2k(op.target),bcost(op.target)-2));
			st.auras.asjdf=0;
			st.auras.ady1=st.auras.ady2;
			st.auras.ady2=0;
			st.num++;
			break;
		}
		case bc:{
			//暂时未考虑区分背刺敌方随从和背刺血量>2的友方随从，统一记作null，且认为总能这么做 
			//用作去除时，仅考虑去除狐人老千和赤烟腾武 
			flag=rmv2(st.hands,op.name,op.cost);
			if(!flag) return badpair;
			if(op.target==nul){
				
			}
			else{
				flag=(op.target==mhrlq)||(op.target==mtw);
				if(!flag) return badpair;
				flag=rmv1(st.fields,op.target);
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
			flag=rmv2(st.hands,op.name,op.cost)&&(op.target==nul);
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
			flag=rmv2(st.hands,op.name,op.cost)&&(op.target==nul);
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
			flag=rmv2(st.hands,op.name,op.cost)&&(op.target==nul);
			if(!flag) return badpair;
			st.mana-=max(op.cost-st.auras.asjdf*2-st.auras.ady1*3,0);
			if(st.mana<0) return badpair;
			
			vector<minion>::iterator i=st.fields.begin();
			while(i!=st.fields.end()){
				if(st.hands.size()>=hlim) break; 
				st.hands.push_back(cardcons(s2k((*i).name),1));
				i++;
			}
			st.auras.asjdf=0;
			st.auras.ady1=st.auras.ady2;
			st.auras.ady2=0;
			st.num++;
			break;
		}
		case syzl:{
			flag=rmv2(st.hands,op.name,op.cost)&&(op.target==nul);
			if(!flag) return badpair;
			if(st.fields.size()>=mlim) flag=false;
			else st.fields.push_back(minioncons(k2s(op.name)));
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
			flag=rmv2(st.hands,op.name,op.cost)&&(op.target==nul);
			if(!flag) return badpair;
			if(st.fields.size()>=mlim) flag=false;
			else st.fields.push_back(minioncons(k2s(op.name)));
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
			flag=rmv2(st.hands,op.name,op.cost)&&(op.target==nul);
			if(!flag) return badpair;
			if(st.fields.size()>=mlim) flag=false;
			else st.fields.push_back(minioncons(k2s(op.name)));
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
			flag=rmv2(st.hands,op.name,op.cost);
			if(!flag) return badpair;
			if(st.fields.size()>=mlim) flag=false;
			else st.fields.push_back(minioncons(k2s(op.name)));
			if(op.target==nul&&st.fields.size()==0){
				//空场，腾武可空交 
			}
			else{
				bool flag=rmv1(st.fields,op.target);
				if(!flag) return badpair;
			}
			if(!flag) return badpair;
			st.mana-=max(op.cost-st.auras.ady1*3,0);
			if(st.mana<0) return badpair;
			
			st.hands.push_back(cardcons(s2k(op.target),1));
			st.auras.ady1=st.auras.ady2;
			st.auras.ady2=0;
			st.num++;
			break;
		}
		case glfz:{
			int twi=twice(st);
			flag=rmv2(st.hands,op.name,op.cost);
			if(!flag) return badpair;
			if(st.fields.size()>=mlim) flag=false;
			else st.fields.push_back(minioncons(k2s(op.name)));
			if(!flag) return badpair;
			if(op.target==dfyx){
				dmg=st.num*twi;
			}
			else{
				//应用总能去除的假定 
				bool flag=rmv1(st.fields,op.target);
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
			bool flag=rmv2(st.hands,op.name,op.cost)&&(op.target==nul);
			if(!flag) return badpair;
			if(st.fields.size()>=mlim) flag=false;
			else st.fields.push_back(minioncons(k2s(op.name)));
			if(!flag) return badpair;
			st.mana-=max(op.cost-st.auras.ady1*3,0);
			if(st.mana<0) return badpair;
			
			st.auras.ady1=st.auras.ady2;
			st.auras.ady2=0;
			st.num++;
			break;
		}
		case ljfs:{
			bool flag=rmv2(st.hands,op.name,op.cost)&&(op.target==nul);
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

void output(opes o,int d){
	string s="";
	vector<ope>::iterator i=o.opes.begin();
	while(i!=o.opes.end()){
		s=s+o2s(*i);
		i++;
	}
	s=s+to_string(d);
	s=s+"\n";
	MessageBox(NULL,s.c_str(),"暗歌是猪",MB_OK);
}
void outputfail(){
	string s="爷不会";
	MessageBox(NULL,s.c_str(),"暗歌是猪",MB_OK);
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

int tlim=15;

namespace OPT{
	state sample1cons(){
		state st;
		st.hands.clear();
		st.hands.push_back(cardcons(syzl,4));
		st.hands.push_back(cardcons(hrlq,2));
		st.hands.push_back(cardcons(dy,4));
		st.hands.push_back(cardcons(glfz,6));
		st.hands.push_back(cardcons(glfz,6));
		st.fields.clear();
		st.auras=emptyau;
		st.mana=6;
		st.num=0;
		return st;
	}
	state sample1=sample1cons();
	state sample2cons(){
		state st;
		st.hands.clear();
		st.hands.push_back(cardcons(jb,0));
		st.hands.push_back(cardcons(syzl,4));
		st.hands.push_back(cardcons(tw,2));
		st.hands.push_back(cardcons(dy,4));
		st.hands.push_back(cardcons(glfz,6));
		st.hands.push_back(cardcons(glfz,6));
		st.fields.clear();
		st.auras=emptyau;
		st.mana=5;
		st.num=0;
		return st;
	}
	state sample2=sample2cons();
	state sample3cons(){
		state st;
		st.hands.clear();
		st.hands.push_back(cardcons(ayb,0));
		st.hands.push_back(cardcons(hrlq,2));
		st.hands.push_back(cardcons(syzl,4));
		st.hands.push_back(cardcons(tw,2));
		st.hands.push_back(cardcons(dy,4));
		st.hands.push_back(cardcons(glfz,6));
		st.hands.push_back(cardcons(glfz,6));
		st.fields.clear();
		st.auras=emptyau;
		st.mana=4;
		st.num=0;
		return st;
	}
	state sample3=sample3cons();
	state sample4cons(){
		state st;
		st.hands.clear();
		st.hands.push_back(cardcons(jb,0));
		st.hands.push_back(cardcons(ayb,0));
		st.hands.push_back(cardcons(hrlq,2));
		st.hands.push_back(cardcons(syzl,4));
		st.hands.push_back(cardcons(tw,2));
		st.hands.push_back(cardcons(dy,4));
		st.hands.push_back(cardcons(glfz,6));
		st.fields.clear();
		st.auras=emptyau;
		st.mana=5;
		st.num=0;
		return st;
	}
	state sample4=sample4cons();
	state sample5cons(){
		state st;
		st.hands.clear();
		st.hands.push_back(cardcons(sjdf,0));
		st.hands.push_back(cardcons(hjys,4));
		st.hands.push_back(cardcons(syzl,4));
		st.hands.push_back(cardcons(dy,4));
		st.hands.push_back(cardcons(glfz,6));
		st.hands.push_back(cardcons(glfz,6));
		st.fields.clear();
		st.auras=emptyau;
		st.mana=6;
		st.num=0;
		return st;
	}
	state sample5=sample5cons();
	state sample6cons(){
		state st;
		st.hands.clear();
		st.hands.push_back(cardcons(jb,0));
		st.hands.push_back(cardcons(jb,0));
		st.hands.push_back(cardcons(ayb,0));
		st.hands.push_back(cardcons(hrlq,2));
		st.hands.push_back(cardcons(syzl,4));
		st.hands.push_back(cardcons(dy,4));
		st.hands.push_back(cardcons(glfz,6));
		st.fields.clear();
		st.auras=emptyau;
		st.mana=6;
		st.num=2;
		return st;
	}
	state sample6=sample6cons();
	state sample7cons(){
		state st;
		st.hands.clear();
		st.hands.push_back(cardcons(jb,0));
		st.hands.push_back(cardcons(sjdf,0));
		st.hands.push_back(cardcons(hjys,4));
		st.hands.push_back(cardcons(dy,4));
		st.hands.push_back(cardcons(tw,2));
		st.hands.push_back(cardcons(glfz,6));
		st.hands.push_back(cardcons(glfz,6));
		st.fields.clear();
		st.auras=emptyau;
		st.mana=10;
		st.num=0;
		return st;
	}
	state sample7=sample7cons();
	state sample8cons(){
		state st;
		st.hands.clear();
		st.hands.push_back(cardcons(jb,0));
		st.hands.push_back(cardcons(jb,0));
		st.hands.push_back(cardcons(sjdf,0));
		st.hands.push_back(cardcons(hjys,4));
		st.hands.push_back(cardcons(dy,4));
		st.hands.push_back(cardcons(tw,2));
		st.hands.push_back(cardcons(glfz,6));
		st.hands.push_back(cardcons(glfz,6));
		st.fields.clear();
		st.auras=emptyau;
		st.mana=10;
		st.num=0;
		return st;
	}
	state sample8=sample8cons();
	state sample9cons(){
		state st;
		st.hands.clear();
		st.hands.push_back(cardcons(jb,0));
		st.hands.push_back(cardcons(sjdf,0));
		st.hands.push_back(cardcons(hjys,4));
		st.hands.push_back(cardcons(syzl,4));
		st.hands.push_back(cardcons(hrlq,2));
		st.hands.push_back(cardcons(dy,4));
		st.hands.push_back(cardcons(tw,2));
		st.hands.push_back(cardcons(glfz,6));
		st.hands.push_back(cardcons(glfz,6));
		st.hands.push_back(cardcons(ljsc,4));
		st.fields.clear();
		st.auras=emptyau;
		st.mana=7;
		st.num=0;
		return st;
	}
	state sample9=sample9cons();
	state sample10cons(){
		state st;
		st.hands.clear();
		st.hands.push_back(cardcons(ayb,0));
		st.hands.push_back(cardcons(ayb,0));
		st.hands.push_back(cardcons(hjys,4));
		st.hands.push_back(cardcons(syzl,4));
		st.hands.push_back(cardcons(hrlq,2));
		st.hands.push_back(cardcons(dy,4));
		st.hands.push_back(cardcons(glfz,6));
		st.fields.clear();
		st.auras=emptyau;
		st.mana=6;
		st.num=0;
		return st;
	}
	state sample10=sample10cons();
	state sample11cons(){
		state st;
		st.hands.clear();
		st.hands.push_back(cardcons(ayb,0));
		st.hands.push_back(cardcons(ayb,0));
		st.hands.push_back(cardcons(hjys,4));
		st.hands.push_back(cardcons(hjys,4));
		st.hands.push_back(cardcons(syzl,4));
		st.hands.push_back(cardcons(hrlq,2));
		st.hands.push_back(cardcons(dy,4));
		st.hands.push_back(cardcons(glfz,6));
		st.fields.clear();
		st.auras=emptyau;
		st.mana=5;
		st.num=0;
		return st;
	}
	state sample11=sample11cons();
	state sample12cons(){
		state st;
		st.hands.clear();
		st.hands.push_back(cardcons(glfz,6));
		st.hands.push_back(cardcons(glfz,6));
		st.hands.push_back(cardcons(ayb,0));
		st.hands.push_back(cardcons(ayb,0));
		st.hands.push_back(cardcons(hrlq,2));
		st.hands.push_back(cardcons(tw,2));
		st.hands.push_back(cardcons(dy,4));
		//st.hands.push_back(cardcons(jb,0));
		//st.hands.push_back(cardcons(jb,0));
		//st.hands.push_back(cardcons(sjdf,0));
		
		st.fields.clear();
		st.auras=emptyau;
		st.mana=7;
		st.num=3;
		return st;
	}
	state sample12=sample12cons();
	
	vector<opes> cls;
	
	priority_queue<syn> Q;
	
	void collect(state st,int eh){
		opes curos=emptyos;
		int curdmg=0;
		
		int tbegin=time(0);
		
		while(!Q.empty()) Q.pop();
		Q.push(syncons(make_pair(st,0),0,emptyos));
		while(time(0)<=tbegin+tlim&&!Q.empty()){
			syn q=Q.top();Q.pop();
			if(q.pa.second>=eh){
				//output(q.os,q.pa.second);
				//cls++;
				cls.push_back(q.os);
			}
			
			vector<card> C=q.pa.first.hands;
			vector<minion> T=q.pa.first.fields;
			T.push_back(minioncons(dfyx));
			//T.push_back(minioncons(dfsc));
			//还没加背刺，此略 
			T.push_back(minioncons(nul));
			
			vector<card>::iterator i=C.begin();
			while(i!=C.end()){
				vector<minion>::iterator j=T.begin();
				while(j!=T.end()){
					ope o=opecons((*i).cost,(*i).name,(*j).name);
					pair<state,int> p=trans(q.pa.first,o);
					opes os=q.os;os.opes.push_back(o);
					Q.push(syncons(make_pair(p.first,q.pa.second+p.second),q.pri-1.0,os));
					j++;
				}
				i++;
			}
		}
	}
	void Collect(){
		cls.clear();
		
		collect(sample1,12);
		collect(sample2,20);
		collect(sample3,28);
		collect(sample4,28);
		collect(sample5,20);
		collect(sample6,28);
		collect(sample7,28);
		collect(sample8,32);
		collect(sample9,54);
		collect(sample10,44);
		collect(sample11,42);
		collect(sample12,30);
		
		freopen("cls.txt","w",stdout);
		
		vector<opes>::iterator i=cls.begin();
		while(i!=cls.end()){
			vector<ope> a=(*i).opes;
			vector<ope>::iterator j=a.begin();
			while(j!=a.end()){
				ope b=(*j);
				printf("%d %d %d ",b.cost,b.name,b.target);
				j++;
			}
			printf("-1 -1 -1\n");
			i++;
		}
		
		fclose(stdout);
	}
	int mix(int a,int b,int c){
		return a+b*100+c*10000+93589;
	}
	int mi[70],m;
	
	typedef unsigned long long ull;
	ull hash(int l,int r,int*mi){
		ull t=0;
		for(int i=l;i<=r;i++){
			if(i<1) t=t*19260817+910570131/(1-i);
			else t=t*19260817+mi[i];
		}
		return t;
	}
	map<ull,double> value;
	const int flim=4;
	double rho=0.5;
	double tot; 
	void maintain(){
		for(int i=1;i<=m;i++) for(int j=i-flim+1;j<i;j++){
			tot+=exp(rho*(i-j));
			value[hash(j,i,mi)]+=exp(rho*(i-j));
		}
	}
	void Load(){
		freopen("cls.txt","r",stdin);
		
		tot=0;
		
		int a,b,c;
		m=0;
		while(scanf("%d%d%d",&a,&b,&c)==3){
			if(a==-1&&b==-1&&c==-1){
				maintain();
				m=0;
				continue;
			}
			mi[++m]=mix(a,b,c);
		}
		
		fclose(stdin);
	}
}
using namespace OPT;

priority_queue<syn> Q2;

double optf(double s,double t){
	return log(s/t);
}

int testcnt;

int opttlim=60; 

void optsolve(state st,int eh=999999){
	opes curos=emptyos;
	int curdmg=0;
	
	int tbegin=time(0);
	
	while(!Q2.empty()) Q2.pop();
	Q2.push(syncons(make_pair(st,0),0,emptyos));
	while(time(0)<=tbegin+opttlim&&!Q2.empty()){
		syn q=Q2.top();Q2.pop();
		if(q.pa.second>=eh){
			output(q.os,q.pa.second);
			return;
		}
		if(q.pa.second>=curdmg){
			curos=q.os;
			curdmg=q.pa.second;
		}
		
		vector<card> C=q.pa.first.hands;
		vector<minion> T=q.pa.first.fields;
		T.push_back(minioncons(dfyx));
		//T.push_back(minioncons(dfsc));
		//还没加背刺，此略 
		T.push_back(minioncons(nul));
		
		int mi[70],m;
		m=0;
		vector<ope>::iterator i0=q.os.opes.begin();
		while(i0!=q.os.opes.end()){
			ope o=*i0;
			mi[++m]=mix(o.cost,o.name,o.target);
			i0++;
		}
		
		vector<card>::iterator i=C.begin();
		while(i!=C.end()){
			vector<minion>::iterator j=T.begin();
			while(j!=T.end()){
				ope o=opecons((*i).cost,(*i).name,(*j).name);
				pair<state,int> p=trans(q.pa.first,o);testcnt++;
				opes os=q.os;os.opes.push_back(o);
				mi[m+1]=mix(o.cost,o.name,o.target);
				
				double sum=0;
				for(int i=(m+1)-flim+1;i<m+1;i++){
					sum+=value[OPT::hash(i,m+1,mi)];
				}
				
				Q2.push(syncons(make_pair(p.first,q.pa.second+p.second),q.pri+optf(sum,tot),os));
				j++;
			}
			i++;
		}
	}
	//printf("??%d\n",curdmg);
	//assert(0); 
	output(curos,curdmg);
}

state sampleAcons(){
	state st;
	st.hands.clear();
	st.hands.push_back(cardcons(glfz,6));
	st.hands.push_back(cardcons(glfz,6));
	st.hands.push_back(cardcons(ayb,0));
	st.hands.push_back(cardcons(dy,4));
	st.hands.push_back(cardcons(sjdf,0));
	st.hands.push_back(cardcons(hjys,4));
	st.hands.push_back(cardcons(hjys,4));
	st.hands.push_back(cardcons(jb,0));
	//st.hands.push_back(cardcons(ljfs,1));
	st.fields.clear();
	st.auras=emptyau;
	st.mana=7;
	st.num=0;
	return st;
}
state sampleA=sampleAcons();

void Test(){
	testcnt=0;
	optsolve(sampleA);
	printf("%d\n",testcnt);
}

int main(){
	srand(time(0));
	
	//Collect();
	
	Load(); 
	
	Test();
}
