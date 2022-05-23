#include <bits/stdc++.h>
using namespace std;
enum kpm{
	ayb,bc,jb,sjdf,hjys,syzl,hrlq,dy,tw,glfz,ljsc,ljfs,lj
};
enum scm{
	msyzl,mhrlq,mdy,mtw,mglfz,mljsc,dfyx,dfsc,nul
};
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
			if(!flag) return badpair;
			bool flag=rmv1(st.fields,op.target);
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

int maxdmg(state st){
	int res=0;
	vector<card>::iterator i=st.hands.begin();
	while(i!=st.hands.end()){
		pair<state,int> pa; 
		vector<minion>::iterator j=st.fields.begin();
		while(j!=st.fields.end()){
			pa=trans(st,opecons((*i).cost,(*i).name,(*j).name));
			res=max(res,pa.second+maxdmg(pa.first));
			if(pa.second<0) tc--;
			j++;
		}
		pa=trans(st,opecons((*i).cost,(*i).name,dfyx));
		res=max(res,pa.second+maxdmg(pa.first));
		if(pa.second<0) tc--;
		//pa=trans(st,opecons((*i).cost,(*i).name,dfsc));
		//还没加背刺，此略 
		//res=max(res,pa.second+maxdmg(pa.first));
		pa=trans(st,opecons((*i).cost,(*i).name,nul));
		res=max(res,pa.second+maxdmg(pa.first));
		if(pa.second<0) tc--;
		
		i++;
	}
	return res;
}
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
	st.hands.push_back(cardcons(jb,0));
	st.hands.push_back(cardcons(jb,0));
	st.hands.push_back(cardcons(ayb,0));
	st.hands.push_back(cardcons(syzl,4));
	st.hands.push_back(cardcons(hrlq,2));
	st.hands.push_back(cardcons(tw,2));
	st.hands.push_back(cardcons(glfz,6));
	st.fields.clear();
	st.auras=emptyau;
	st.mana=7;
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
state sample11=sample11cons();
int main(){
	/*printf("%d\n",maxdmg(sample1));
	printf("%d\n",maxdmg(sample2));
	printf("%d\n",maxdmg(sample3));
	printf("%d\n",maxdmg(sample4));
	printf("%d\n",maxdmg(sample5));
	printf("%d\n",maxdmg(sample6));
	printf("%d\n",maxdmg(sample7));
	printf("%d\n",maxdmg(sample8));
	printf("%d\n",maxdmg(sample9));
	printf("%d\n",maxdmg(sample10));*/
	
	printf("%d\n",maxdmg(sample11));
}
