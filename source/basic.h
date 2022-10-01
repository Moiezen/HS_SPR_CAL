#pragma once

#include <bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
enum cardname {
	shadowstep, backstab, fakecoin, preparation, illusionpotion, sharkspirit, foxyfraud, mailboxdancer, cutterbutter, redsmoke, spectralpillager,
	anyminion, anyspell, invalid, anyweapon, anycombospell, bonespike, elvensinger, shroud, extortion, swindle, shadowcaster, illucia, bronze
};
enum minionname {
	sharkspirit_m, foxyfraud_m, mailboxdancer_m, cutterbutter_m, redsmoke_m, spectralpillager_m,
	anyminion_m, enemyhero, enemyminion, nul, elvensinger_m, shadowcaster_m, illucia_m, bronze_m
	//敌方英雄-可以是鬼灵匪贼的目标
	//敌方随从-可以是背刺的目标
	//空目标
	//以上虚目标均归入随从名以简化操作目标
};
enum lang {
	CN, EN
};
extern lang _lang;
string shak_s();
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
string clr_s();
string mana_s();
string calc_s();
string randc_s();
string time_s();
string targ_s();
string chng_s();
string read_s();
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

string mn2str(minionname a);
string cn2str(cardname a);
cardname mn2cn(minionname a);
minionname cn2mn(cardname a);
bool legalcn2mn(cardname a);
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
};
state emptystcons();
extern state emptyst;

const int hlim = 10;
const int mlim = 7;
const int manalim = 10;
const int alim[4] = { 1,6,12,6 };

struct oxy {
	int x, y;
	//x 手牌序号
	//y 目标序号
	//y=-1 nul
	//y=-2 enemyhero
};
oxy oxycons(int x, int y);

struct ope {
	int cost;
	cardname name;
	minionname target;
};
ope opecons(int a, cardname b, minionname c);

ope exact(state a, oxy b);

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
extern minionname deckm[10];

extern int oppoH;
extern card oppohands[10];

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