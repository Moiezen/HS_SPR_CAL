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
			return "����";
			break;
		}
		case mhrlq:{
			return "��ǧ";
			break;
		}
		case mdy:{
			return "����";
			break;
		}
		case mtw:{
			return "����";
			break;
		}
		case mglfz:{
			return "����";
			break;
		}
		case mljsc:{
			return "����";
			break;
		}
		case dfyx:{
			return "������";
			break;
		}
		case dfsc:{
			return "�����";
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
			return "����";
			break;
		}
		case hrlq:{
			return "��ǧ";
			break;
		}
		case dy:{
			return "����";
			break;
		}
		case tw:{
			return "����";
			break;
		}
		case glfz:{
			return "����";
			break;
		}
		case ljsc:{
			return "�������"; 
			break;
		}
		case ayb:{
			return "��Ӱ��";
			break;
		}
		case bc:{
			return "����";
			break;
		}
		case jb:{
			return "��";
			break;
		}
		case sjdf:{
			return "�Ż�����"; 
			break;
		}
		case hjys:{
			return "�þ�ҩˮ";
			break;
		}
		case ljfs:{
			return "��������"; 
			break;
		}
		case lj:{
			return "����";
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
//�з�Ӣ��-�����ǹ��������Ŀ��
//�з����-�����Ǳ��̵�Ŀ��
//��Ŀ��
//������Ŀ�������������Լ򻯲���Ŀ��
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
//�Ѽ��� ����ֻ����ȥ����ǧ������ �������������ȥ��
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
//���������ʱ������Ѫ��������Ŀ�����Ҫ����������ѿ��԰����з�Ӣ�ۣ��з���ӣ���Ŀ�� 
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
			//��ʱδ�������ֱ��̵з���Ӻͱ���Ѫ��>2���ѷ���ӣ�ͳһ����null������Ϊ������ô�� 
			//����ȥ��ʱ��������ȥ��������ǧ�ͳ������� 
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
			if(!flag) return badpair;
			if(op.target==nul&&st.fields.size()<=1){
				//�ճ�������ɿս� 
			}
			else{
				flag=rmv1(st.fields,op.target);
				if(!flag) return badpair;
			}
			st.mana-=max(op.cost-st.auras.ady1*3,0);
			if(st.mana<0) return badpair;
			
			if(op.target!=nul) st.hands.push_back(cardcons(s2k(op.target),1));
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
				//Ӧ������ȥ���ļٶ� 
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
			//����Ϊ�޴�����ӣ��������ڼ�����˹ 
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
	MessageBox(NULL,s.c_str(),"��������",MB_OK);
}
void outputfail(){
	string s="ү����";
	MessageBox(NULL,s.c_str(),"��������",MB_OK);
}

struct syn{
	pair<state,int> pa;
	//��ǰ״̬���ۼ��˺� 
	double pri;
	//���ȼ� 
	opes os;
	//�������� 
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

int tlim=999999;

priority_queue<syn> Q;

void solve(state st,int eh=999999){
	opes curos=emptyos;
	int curdmg=0;
	
	int tbegin=time(0);
	
	while(!Q.empty()) Q.pop();
	Q.push(syncons(make_pair(st,0),0,emptyos));
	while(time(0)<=tbegin+tlim&&!Q.empty()){
		syn q=Q.top();Q.pop();
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
		//������������ֱ��̵з���Ӻͱ���Ѫ��>2���ѷ���ӣ����� 
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
	output(curos,curdmg);
}
state sample1cons(){
	state st;
	st.hands.clear();
	st.hands.push_back(cardcons(tw,2));
	st.hands.push_back(cardcons(glfz,6));
	st.fields.clear();
	st.auras=emptyau;
	st.mana=8;
	st.num=0;
	return st;
}
//state sample1=sample1cons();
kpm str2k(string s){
	if(s=="ayb") return ayb;
	if(s=="bc") return bc;
	if(s=="jb") return jb;
	if(s=="sjdf") return sjdf;
	if(s=="hjys") return hjys;
	if(s=="syzl") return syzl;
	if(s=="hrlq") return hrlq;
	if(s=="dy") return dy;
	if(s=="tw") return tw;
	if(s=="glfz") return glfz;
	if(s=="ljfs") return ljfs;
	if(s=="ljsc") return ljsc;
	if(s=="lj") return lj;
	return lj;
}
int _eh=999999; 
state sampleread(){
	cout<<"����y�������Ѿ��Ķ���https://github.com/Moiezen/HS_SPR_CAL�ϵ�˵�������Ҹ�.exe��ֱ�ӴӴ˴���ȡ��"<<endl;
	string Y;
	cin>>Y;
	if(Y!="y") exit(0);
	
	//�򵥵Ĵӱ�׼�������
	cin>>_eh;
	state st;
	st.hands.clear();
	int n,a;
	string s;
	cin>>n;
	while(n--){
		cin>>s>>a;
		st.hands.push_back(cardcons(str2k(s),a));
	}
	cin>>n;
	st.fields.clear();
	while(n--){
		cin>>s;
		st.fields.push_back(minioncons(k2s(str2k(s))));
		//����дstr2s�� 
	}
	st.auras=emptyau;
	cin>>st.auras.asjdf;
	cin>>st.auras.ahrlq;
	cin>>st.auras.ady1;
	cin>>st.auras.ady2;
	st.mana=0;
	cin>>st.mana;
	st.num=0;
	cin>>st.num;
	return st;
}
state sample1=sampleread();
int main(){
	srand(time(0));
	
	solve(sample1,_eh);
}
