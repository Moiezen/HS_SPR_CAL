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
			return "���";
			break;
		}
		case ayb:{
			return "����";
			break;
		}
		case bc:{
			return "����";
			break;
		}
		case jb:{
			return "Ӳ��";
			break;
		}
		case sjdf:{
			return "�Ż�"; 
			break;
		}
		case hjys:{
			return "��ҩ";
			break;
		}
		case ljfs:{
			return "����";
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

int openmode;

pair<state,int> trans(state st,ope op){
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
			//��������ʱ��Ŀ��ͳһ����null�������ֵз���Ӻ�Ѫ��>2���ѷ����
			//����ģʽ�춨��openmode=1ʱ��Ϊ���ез���ӿ���ѡ��ֱ��ͨ��
			//openmode=0ʱ��Ϊû�ез���ӿ���ѡ�񣬽�����ѡ������֮�飬���ͺ͹������������Ϊ�����ܿ���ѡ�����ܲ���ȥ�� 
			//����ȥ��ʱ��������ѡ�������ǧ�ͳ������� 
			flag=rmv2(st.hands,op.name,op.cost);
			if(!flag) return badpair;
			if(op.target==nul){
				if(openmode==0){
					flag=false;
					vector<minion>::iterator i=st.fields.begin();
					while(i!=st.fields.end()){
						if((*i).name==msyzl||(*i).name==mdy||(*i).name==mglfz){
							flag=true;
							break;
						}
						i++;
					}
					if(!flag) return badpair;
				}
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

string solve(state st,int _eh=999,int _tlim=999999){
	eh=_eh;
	done=curdmg=0;
	curos=emptyos;
	
	tlim=_tlim;
	tbegin=time(0);
	
	solve_(syncons(make_pair(st,0),0,emptyos));
	
	return output(curos,curdmg,done);
}

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
	nodomt,vnx,vx,cn,cx,go,ans,vxa,lk,lk1,lk2,vxb
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
	textr(_all,txc,"�����ʼ���������Ѿ��Ķ���https://github.com/Moiezen/HS_SPR_CAL��README.md�����Ҹ�UI.exe��ֱ�ӻ�ȡ�����°汾");
	
	barr(_start,bdc);
	barr(cutedge(_start,1),bgc);
	textr(_start,txc,"��ʼ");
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

string n1[14]={"����","��ǧ","����","����","����","����","����","Ӳ��","�Ż�","��ҩ","���","����","����","���"};
string customlk="D:\\Hearthstone";

void getdoms(){
	doms.clear();
	addd(860,600,920,640,vx,"ˮ��",0,manadomid=1);
	//1
	rep(i,0,9) addd(200+i*60,600,260+i*60,640,vnx,"���",0,cardsdomid[i]=2+i);
	//2 ... 11
	rep(i,0,10) addd((i+2)%3*40,400+(i+2)/3*40,40+(i+2)%3*40,440+(i+2)/3*40,cx,"",i,12+i);
	//12 ... 22
	rep(i,0,13) addd(i%3*40,200+i/3*40,40+i%3*40,240+i/3*40,cn,n1[i],0,23+i);
	//23 ... 36
	addd(1220,600,1280,640,go,"����",0,37);
	//37
	addd(1000,0,1280,560,ans,"",0,ansdomid=38);
	//38
	addd(980,600,1040,640,vxa,"ʱ��",15,tlimdomid=39);
	//39
	addd(1100,600,1160,640,vxa,"Ŀ��",999,ehdomid=40);
	//40
	addd(0,0,400,40,lk,customlk,0,lkdomid=41);
	//41
	addd(0,40,60,80,lk1,"�޸�",0,42);
	//42
	addd(60,40,120,80,lk2,"��ȡ",0,43);
	//43
	addd(0,80,120,120,vxb,"���̿���",1,modedomid=44);
	//44
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
kpm k2str(string s){
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

int __eh=999;
int __tlim=999999;

state doms2st(vector<domain> a){
	openmode=id2dom(modedomid).x;
	
	__eh=id2dom(ehdomid).x;
	__tlim=id2dom(tlimdomid).x;
	
	state st;
	st.hands.clear();
	rep(i,0,9){
		domain _card=id2dom(cardsdomid[i]);
		if(_card.name!="���") st.hands.push_back(cardcons(str2k(_card.name),_card.x));
	}
	st.fields.clear();
	st.auras=emptyau;
	st.mana=id2dom(manadomid).x;
	st.num=0;
	return st;
}

void st2doms(state st){
	int p=0;
	vector<card>::iterator i=st.hands.begin();
	while(i!=st.hands.end()){
		domain _card=id2dom(cardsdomid[p]);
		_card.name=k2str((*i).name);
		_card.x=(*i).cost;
		follow(_card);
		i++;
		p++;
	}
	rep(i,p,9){
		domain _card=id2dom(cardsdomid[i]);
		_card.name="���";
		follow(_card);
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
		case vnx:
		case vx:
		case vxa:
		case vxb:{
			if(a.name=="���") textr(r,txc,""); 
			else textr(r,txc,a.name+to_string(a.x));
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
	setcaption("��������");
	vector<domain>::iterator i=doms.begin();
	while(i!=doms.end()){
		drawdom(*i,0);
		i++;
	}
	selected=nodomain;
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
			if(selected.type==vxa){
				if(toselect.x==0) selected.x=0;
				else selected.x+=toselect.x;
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
			ans.name=solve(st,__eh,__tlim);
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
        	inputbox_getline("������¯ʯ��˵����·�����س�ȷ�ϣ�","��������",_lk,100);
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
		//���ڿ��ܶ�ε��ã���Ҫÿ����� 
		
		//���½ṹ�� 
		//id->cid,cost,zone
		//resource(mana)
		//op->id,err
		//�˴�Ϊ��㣬ֱ����op.id->err 
		
		cin.clear();
		//��������������ֹ�޷���ȡ 
		
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
				//s0�������ⲿ��ȴ�Ѿ��������ˣ�Ӧ��ֱ����Ϊ��һ�ε�s 
				//�����s�������������²��֣������ʹ��while 
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
				//�˴��п��ܴ���error=���Ϊ�գ��������� 
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
				//ż�����ƻᱣ����ʾzone=DECK 
				//��Ȼ����ֵ���work 
				autost.hands.push_back(cardcons(cid2kpm(s2),atoi(s3.c_str())));
			}
			s6=id2err[s1];
			if(cid2kpm(s2)==bc&&s6!=""){
				openmode=0;
				//ģʽ�춨�����޷�ֱ��ͨ��bc->nul 
			}
			else openmode=1;
			
			id2zone[s1]="";
			//��ֹ���ɽ����ƣ���ͳ������ 
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
