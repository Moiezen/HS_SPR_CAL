#pragma once

#include <bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
enum cardname {
	shadowstep, backstab, fakecoin, preparation, illusionpotion, sharkspirit, foxyfraud, mailboxdancer, cutterbutter, redsmoke, spectralpillager,
	anyminion, anyspell, invalid, anyweapon, anycombospell, bonespike, elvensinger, shroud, extortion, swindle, shadowcaster, illucia, brann, zolag,
	madnessplague, heroattack, demise
	//heroattack��������
};
enum minionname {
	sharkspirit_m, foxyfraud_m, mailboxdancer_m, cutterbutter_m, redsmoke_m, spectralpillager_m,
	anyminion_m, enemyhero, enemyminion, nul, elvensinger_m, shadowcaster_m, illucia_m, brann_m, zolag_m, sharkspirit_mx
	//�з�Ӣ��-�����ǹ��������Ŀ��
	//�з����-�����Ǳ��̵�Ŀ�꣨����Ŀǰ����/�Ǵ̵з���ӻ��Ϊ��Ŀ�꣩
	//��Ŀ��
	//������Ŀ�������������Լ򻯲���Ŀ��
};

//ÿ���¼�һ������
//1. �޸�basic.h��basic.cpp�еĶ�����Ϣ������������Ϣ����Ӣ��������Ϣ
//	�������ӻ���Ҫ�޸����-����ת����Ϣ(cn2mn,normalminion)������Ѫ����Ϣ
//  ����Ƿ���Ҳ��Ҫָ����һ�ų��淨��(normalspell)
//2. �޸�offer.cpp��trans.cpp�еĲ��������ж��Լ�������ɵ�״̬�仯
//3. �޸�ui.cpp�е�UI��ں�auto.cpp�е��Զ����
//��4. ���ھ����Զ���ڣ�����Ҫ�ӳ�ʼ������ʶ��ģ��޸�deck.cpp�е�ʶ��

enum lang {
	CN, EN
};
extern lang _lang;
string shak_s();
string shxk_s();
string foxy_s();
string mail_s();
string scab_s();
string tenw_s();
string cast_s();
string pill_s();
string elvn_s();
string anym_s();
string face_s();
string step_s();
string stab_s();
string si7_s();
string coin_s();
string prep_s();
string pshn_s();
string anys_s();
string trsh_s();
string anyw_s();
string cmbs_s();
string bone_s();
string shrd_s();
string swin_s();
string iuca_s();
string bran_s();
string zola_s();
string plag_s();
string clr_s();
string mana_s();
string calc_s();
string randc_s();
string time_s();
string targ_s();
string adpt_s();
string chng_s();
string read_s();
string back_s();
string stax_s();
string mtax_s();
string btax_s();
string able_s();
string able2_s();
string plyd_s();
string samp_s();
string cl_s();
string a0_s();
string a1_s();
string a2_s();
string a3_s();
string hint_s();
string calcing_s();
string exhaust_s();
string targrch_s();
string timerch_s();
string iceblock_s();
string heroattk_s();
string demi_s();
string smal_s();
string larg_s();

string mn2str(minionname a);
string cn2str(cardname a);
cardname mn2cn(minionname a);
minionname cn2mn(cardname a);
bool normalminion(cardname a);
bool normalspell(cardname a);
int originalcost(minionname a);
int originalcost_c(cardname a);
int originalhealth(minionname a);
int originalhealth_c(cardname a);

struct card {
	cardname name;
	int cost;
	int health;
};
card cardcons(cardname a, int b);
card cardcons(cardname a, int b, int c);

struct minion {
	minionname name;
	int health;
	int curhealth;
};
minion minioncons(minionname a);
minion minioncons(minionname a, int b, int c);

struct state {
	card hands[10]; int H;
	minion fields[7]; int F;
	int auras[4];
	int mana;
	int num;
	int drawmn;
	int hatk;
	cardname todemise;
};
state emptystcons();
extern state emptyst;

const int hlim = 10;
const int mlim = 7;
const int manalim = 10;
const int alim[4] = { 1,6,12,6 };

const int _tar_max = 999;
const int _tar_ice1 = 990;
const int _tar_ice2 = 900;
//����xѪ������_tar_ice1-x���Ҹ�ֵ������_tar_ice2

struct oxy {
	int x, y;
	//x �������
	//y Ŀ�����
	//y=-1 nul
	//y=-2 enemyhero
	//y=-3 heroattack to enemyhero
};
oxy oxycons(int x, int y);

struct ope {
	int cost;
	cardname name;
	minionname target;
};
ope opecons(int a, cardname b, minionname c);

ope exact(state a, oxy b);

ope exact4f(state a, oxy b);

struct oxys {
	vector<oxy> os;
	~oxys() {
		os.clear();
	}
};
oxys emptyoxyscons();
extern oxys emptyoxys;

struct opes {
	vector<ope> os;
	~opes() {
		os.clear();
	}
};
opes emptyopescons();
extern opes emptyopes;

extern int stabable;
extern int boneable;
extern int spelldebuff;
extern int miniondebuff;
extern int battlecrydebuff;

extern int deckmn;
extern minionname deckm[99];

extern int oppoH;
extern card oppohands[10];

extern int iceblockif;

extern int iseq[999], isn;

struct quiz {
	state qst;
	int qnd;
};
quiz emptyqcons();

const int dmgbd = 10;
extern vector<quiz> quizs;
extern vector<opes> cls;
extern vector<opes> allcls;