#include <windows.h>
#include <graphics.h>
#include <bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
#define setb setbkcolor
#define setc setcolor
#define setf setfillcolor
#define sett settextjustify
#define refresh delay_ms(0)
#define addd(a,b,c,d,e,f,g,h) doms.push_back(domaincons(rectcons(a,b,c,d),e,f,g,h));
using namespace std;

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

string output(opes o,int d,int u){
	string s="";
	if(u==2) s+="(ʱ������)\n";
	vector<ope>::iterator i=o.opes.begin();
	while(i!=o.opes.end()){
		s=s+o2s(*i);
		i++;
	}
	s=s+to_string(d)+"\n";
	return s;
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

int tlim,tbegin;

int eh,done,curdmg;
opes curos;
string _output;

void solve_(syn q){
	if(q.pa.second>=curdmg){
		curos=q.os;
		curdmg=q.pa.second;
	}
	if(q.pa.second>=eh){
		done=1;
		return;
	}
	if(time(0)>tbegin+tlim){
		done=2;
		return;
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
			solve_(syncons(make_pair(p.first,q.pa.second+p.second),q.pri-1.0,os));
			if(done>0) return;
			j++;
		}
		i++;
	}
}

string solve(state st,int _eh=999999,int _tlim=999999){
	eh=_eh;
	done=curdmg=0;
	curos=emptyos;
	
	tlim=_tlim;
	tbegin=time(0);
	
	solve_(syncons(make_pair(st,0),0,emptyos));
	
	return output(curos,curdmg,done);
}

int __eh=999999;
int __tlim=999999;

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
	nodomt,vnx,vx,cn,cx,go,ans
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
rect _start=rectcons(1060,560,1180,640);

void drawatt(){
	textr(_all,txc,"�����ʼʹ�ã��������Ѿ��Ķ���https://github.com/Moiezen/HS_SPR_CAL��README.md�����Ҹ�UI.exe��ֱ�ӻ�ȡ�����°汾");
	
	barr(_start,bdc);
	barr(cutedge(_start,1),bgc);
	textr(_start,txc,"��ʼʹ��");
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
		case vnx:
		case vx:{
			textr(r,txc,a.name+to_string(a.x));
			break;
		}
		case cn:
		case go:{
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
	}
}

vector<domain> doms;
domain selected;
int manaid;
int cardsdomid[10];
int ansdomid;

string n1[14]={"����","��ǧ","����","����","����","����","����","Ӳ��","�Ż�","��ҩ","���","����","����",""};

void getdoms(){
	doms.clear();
	addd(900,600,960,640,vx,"ˮ��",0,manaid=1);
	//1
	rep(i,0,9) addd(200+i*60,600,260+i*60,640,vnx,"",0,cardsdomid[i]=2+i);
	//2 ... 11
	rep(i,0,10) addd((i+2)%3*40,400+(i+2)/3*40,40+(i+2)%3*40,440+(i+2)/3*40,cx,"",i,12+i);
	//12 ... 22
	rep(i,0,13) addd(i%3*40,200+i/3*40,40+i%3*40,240+i/3*40,cn,n1[i],0,23+i);
	//23 ... 36
	addd(1060,560,1180,640,go,"��ʼ����",0,37);
	//37
	addd(1000,0,1280,560,ans,"",0,ansdomid=38);
	//38
}

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

kpm str2k(string s){
	if(s=="����") return ayb;
	if(s=="����") return bc;
	if(s=="Ӳ��") return jb;
	if(s=="�Ż�") return sjdf;
	if(s=="��ҩ") return hjys;
	if(s=="����") return syzl;
	if(s=="��ǧ") return hrlq;
	if(s=="����") return dy;
	if(s=="����") return tw;
	if(s=="����") return glfz;
	if(s=="����") return ljfs;
	if(s=="���") return ljsc;
	if(s=="����") return lj;
	return lj;
}

state doms2st(vector<domain> a){
	state st;
	st.hands.clear();
	rep(i,0,9){
		domain _card=id2dom(cardsdomid[i]);
		if(_card.name!="") st.hands.push_back(cardcons(str2k(_card.name),_card.x));
	}
	st.fields.clear();
	st.auras=emptyau;
	st.mana=id2dom(manaid).x;
	st.num=0;
	return st;
}

void loaddoms(){
	setcaption("��������");
	vector<domain>::iterator i=doms.begin();
	while(i!=doms.end()){
		drawdom(*i,0);
		i++;
	}
	selected=nodomain;
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
		case vx:{
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
			if(selected.type==vnx){
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
			break;
		}
		case go:{
			state st=doms2st(doms);
			domain ans=id2dom(ansdomid);
			ans.name=solve(st);
			drawdom(ans,0);
			follow(ans);
			break;
		}
	}
}

int main(){
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
				//���ⳤ�� 
				click(e.x,e.y);
				refresh;
			}
        	last=1;
		}
	}

	closegraph();
	return 0;
}
