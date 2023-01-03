#include "basic.h"

lang _lang = CN;

string shak_s() {
	return _lang == CN ? "鱼灵" : "Shak";
}
string shxk_s() {
	return _lang == CN ? "沉鱼" : "Shxk";
}
string foxy_s() {
	return _lang == CN ? "老千" : "Foxy";
}
string mail_s() {
	return _lang == CN ? "箱舞" : "Mail";
}
string scab_s() {
	return _lang == CN ? "刀油" : "Scab";
}
string tenw_s() {
	return _lang == CN ? "腾武" : "Tenw";
}
string cast_s() {
	return _lang == CN ? "暗施" : "Cast";
}
string pill_s() {
	return _lang == CN ? "鬼灵" : "Pill";
}
string elvn_s() {
	return _lang == CN ? "咏唱" : "Elvn";
}
string anym_s() {
	return _lang == CN ? "随从" : "AnyM";
}
string face_s() {
	return _lang == CN ? "对面" : "Face";
}
string step_s() {
	return _lang == CN ? "暗步" : "Step";
}
string stab_s() {
	return _lang == CN ? "背刺" : "Stab";
}
string si7_s() {
	return _lang == CN ? "要挟" : "SI7.";
}
string coin_s() {
	return _lang == CN ? "假币" : "Coin";
}
string prep_s() {
	return _lang == CN ? "伺机" : "Prep";
}
string pshn_s() {
	return _lang == CN ? "幻药" : "Pshn";
}
string anys_s() {
	return _lang == CN ? "法术" : "Anys";
}
string trsh_s() {
	return _lang == CN ? "垃圾" : "Trsh";
}
string anyw_s() {
	return _lang == CN ? "武器" : "AnyW";
}
string cmbs_s() {
	return _lang == CN ? "连法" : "CmbS";
}
string bone_s() {
	return _lang == CN ? "齿刺" : "Bone";
}
string shrd_s() {
	return _lang == CN ? "帷幕" : "Shrd";
}
string swin_s() {
	return _lang == CN ? "行骗" : "Swin";
}
string iuca_s() {
	return _lang == CN ? "裂心" : "Iuca";
}
string bran_s() {
	return _lang == CN ? "铜须" : "Bran";
}
string zola_s() {
	return _lang == CN ? "佐拉" : "Zola";
}
string plag_s() {
	return _lang == CN ? "毒刀" : "Plag";
}
string clr_s() {
	return _lang == CN ? "清除" : "Clr.";
}
string mana_s() {
	return _lang == CN ? "水晶" : "Mana";
}
string calc_s() {
	return _lang == CN ? "计算" : "Calc";
}
string randc_s() {
	return _lang == CN ? "读算" : "R&C.";
}
string time_s() {
	return _lang == CN ? "时限" : "Time";
}
string targ_s() {
	return _lang == CN ? "目标" : "Targ";
}
string adpt_s() {
	return _lang == CN ? "适应" : "Adpt";
}
string chng_s() {
	return _lang == CN ? "修改" : "Chng";
}
string read_s() {
	return _lang == CN ? "读取" : "Read";
}
string back_s() {
	return _lang == CN ? "回退" : "Back";
}
string stax_s() {
	return _lang == CN ? "法术加费" : "AnySTax.";
}
string mtax_s() {
	return _lang == CN ? "随从加费" : "AnyMTax,";
}
string btax_s() {
	return _lang == CN ? "战吼加费" : "BcryTax.";
}
string able_s() {
	return _lang == CN ? "背刺可用" : "StabAble";
}
string able2_s() {
	return _lang == CN ? "齿刺可用" : "BoneAble";
}
string plyd_s() {
	return _lang == CN ? "已用牌数" : "CrdsPlyd";
}
string samp_s() {
	return _lang == CN ? "查看样例" : "ViewSamp";
}
string cl_s() {
	return _lang == CN ? "清" : "Cl";
}
string a0_s() {
	return _lang == CN ? "伺机层数" : "PrepDisc";
}
string a1_s() {
	return _lang == CN ? "老千层数" : "FoxyDisc";
}
string a2_s() {
	return _lang == CN ? "下一减费" : "Nxt1Disc";
}
string a3_s() {
	return _lang == CN ? "下二减费" : "Nxt2Disc";
}
string hint_s() {
	return _lang == CN ? "请输入炉石传说本地路径（回车确认）" : "Please enter the local path of HS:";
}
string calcing_s() {
	return _lang == CN ? "(正在计算)" : "(Calcing.)";
}
string exhaust_s() {
	return _lang == CN ? "(穷尽掐断)" : "(Exhaust.)";
}
string targrch_s() {
	return _lang == CN ? "(达标掐断)" : "(TargRch.)";
}
string timerch_s() {
	return _lang == CN ? "(时限掐断)" : "(TimeRch.)";
}
string iceblock_s() {
	return _lang == CN ? "破冰需要" : "IceBlock";
}
string heroattk_s() {
	return _lang == CN ? "英雄攻击" : "HeroAttk";
}
string demi_s() {
	return _lang == CN ? "殒命" : "Demi";
}
string smal_s() {
	return "><";
}
string larg_s() {
	return "<>";
}

string mn2str(minionname a) {
	switch (a) {
		case sharkspirit_m: {
			return shak_s();
			break;
		}
		case sharkspirit_mx: {
			return shxk_s();
		}
		case foxyfraud_m: {
			return foxy_s();
			break;
		}
		case mailboxdancer_m: {
			return mail_s();
			break;
		}
		case cutterbutter_m: {
			return scab_s();
			break;
		}
		case redsmoke_m: {
			return tenw_s();
			break;
		}
		case shadowcaster_m: {
			return cast_s();
		}
		case spectralpillager_m: {
			return pill_s();
			break;
		}
		case elvensinger_m: {
			return elvn_s();
		}
		case illucia_m: {
			return iuca_s();
			break;
		}
		case brann_m: {
			return bran_s();
			break;
		}
		case zolag_m: {
			return zola_s();
			break;
		}
		case anyminion_m: {
			return anym_s();
			break;
		}
		case enemyhero: {
			return face_s();
			break;
		}
		case enemyminion: {
			assert(0);
			return "";
			break;
		}
		case nul: {
			return "";
			break;
		}
		default: {
			assert(0);
			return "";
			break;
		}
	}
}
string cn2str(cardname a) {
	switch (a) {
		case sharkspirit: {
			return shak_s();
			break;
		}
		case foxyfraud: {
			return foxy_s();
			break;
		}
		case mailboxdancer: {
			return mail_s();
			break;
		}
		case cutterbutter: {
			return scab_s();
			break;
		}
		case redsmoke: {
			return tenw_s();
			break;
		}
		case shadowcaster: {
			return cast_s();
		}
		case spectralpillager: {
			return pill_s();
			break;
		}
		case elvensinger: {
			return elvn_s();
			break;
		}
		case illucia: {
			return iuca_s();
			break;
		}
		case brann: {
			return bran_s();
			break;
		}
		case zolag: {
			return zola_s();
			break;
		}
		case anyminion: {
			return anym_s();
			break;
		}
		case shadowstep: {
			return step_s();
			break;
		}
		case backstab: {
			return stab_s();
			break;
		}
		case extortion: {
			return si7_s();
			break;
		}
		case fakecoin: {
			return coin_s();
			break;
		}
		case preparation: {
			return prep_s();
			break;
		}
		case illusionpotion: {
			return pshn_s();
			break;
		}
		case anyspell: {
			return anys_s();
			break;
		}
		case anyweapon: {
			return anyw_s();
			break;
		}
		case anycombospell: {
			return cmbs_s();
			break;
		}
		case bonespike: {
			return bone_s();
			break;
		}
		case shroud: {
			return shrd_s();
		}
		case swindle: {
			return swin_s();
		}
		case madnessplague: {
			return plag_s();
		}
		case demise: {
			return demi_s();
		}
		case invalid: {
			return trsh_s();
			break;
		}
		default: {
			assert(0);
			return "";
			break;
		}
	}
}
cardname mn2cn(minionname a) {
	switch (a) {
		case sharkspirit_m: {
			return sharkspirit;
			break;
		}
		case sharkspirit_mx: {
			return sharkspirit;
			break;
		}
		case foxyfraud_m: {
			return foxyfraud;
			break;
		}
		case mailboxdancer_m: {
			return mailboxdancer;
			break;
		}
		case cutterbutter_m: {
			return cutterbutter;
			break;
		}
		case redsmoke_m: {
			return redsmoke;
			break;
		}
		case shadowcaster_m: {
			return shadowcaster;
			break;
		}
		case spectralpillager_m: {
			return spectralpillager;
			break;
		}
		case elvensinger_m: {
			return elvensinger;
			break;
		}
		case illucia_m: {
			return illucia;
			break;
		}
		case brann_m: {
			return brann;
			break;
		}
		case zolag_m: {
			return zolag;
			break;
		}
		case anyminion_m: {
			return anyminion;
			break;
		}
		default: {
			assert(0);
			return anyminion;
			break;
		}
	}
}
minionname cn2mn(cardname a) {
	switch (a) {
		case sharkspirit: {
			return sharkspirit_m;
			break;
		}
		case foxyfraud: {
			return foxyfraud_m;
			break;
		}
		case mailboxdancer: {
			return mailboxdancer_m;
			break;
		}
		case cutterbutter: {
			return cutterbutter_m;
			break;
		}
		case redsmoke: {
			return redsmoke_m;
			break;
		}
		case shadowcaster: {
			return shadowcaster_m;
			break;
		}
		case spectralpillager: {
			return spectralpillager_m;
			break;
		}
		case elvensinger: {
			return elvensinger_m;
			break;
		}
		case illucia: {
			return illucia_m;
			break;
		}
		case zolag: {
			return zolag_m;
			break;
		}
		case anyminion: {
			return anyminion_m;
			break;
		}
		default: {
			assert(0);
			return anyminion_m;
			break;
		}
	}
}
bool normalminion(cardname a) {
	switch (a) {
		case sharkspirit:
		case foxyfraud:
		case mailboxdancer:
		case cutterbutter:
		case redsmoke:
		case shadowcaster:
		case spectralpillager:
		case elvensinger:
		case illucia:
		case brann:
		case zolag:
		case anyminion: {
			return true;
			break;
		}
		default: {
			return false;
			break;
		}
	}
}
bool normalspell(cardname a) {
	switch (a) {
		case shadowstep:
		case backstab:
		case fakecoin:
		case preparation:
		case illusionpotion:
		case bonespike:
		case shroud:
		case extortion:
		case swindle:
		case madnessplague:
		case anyspell:
		case anycombospell: {
			return true;
			break;
		}
		default: {
			return false;
			break;
		}
	}
}
int originalcost(minionname a) {
	switch (a) {
		case sharkspirit_m: {
			return 4;
			break;
		}
		case sharkspirit_mx: {
			return 4;
			break;
		}
		case foxyfraud_m: {
			return 2;
			break;
		}
		case mailboxdancer_m: {
			return 2;
			break;
		}
		case cutterbutter_m: {
			return 4;
			break;
		}
		case redsmoke_m: {
			return 2;
			break;
		}
		case shadowcaster_m: {
			return 5;
			break;
		}
		case spectralpillager_m: {
			return 6;
			break;
		}
		case elvensinger_m: {
			return 4;
		}
		case illucia_m: {
			return 3;
		}
		case brann_m: {
			return 3;
		}
		case zolag_m: {
			return 3;
		}
		case anyminion_m: {
			return 99;
			break;
		}
		case enemyhero: {
			assert(0);
			return 0;
			break;
		}
		case enemyminion: {
			assert(0);
			return 0;
			break;
		}
		default: {
			assert(0);
			return 0;
			break;
		}
	}
}
int originalcost_c(cardname a) {
	if (normalminion(a)) {
		return originalcost(cn2mn(a));
	}
	else switch(a) {
		case shadowstep: {
			return 0;
			break;
		}
		case backstab: {
			return 0;
			break;
		}
		case extortion: {
			return 1;
		}
		case fakecoin: {
			return 0;
			break;
		}
		case preparation: {
			return 0;
			break;
		}
		case illusionpotion: {
			return 4;
			break;
		}
		case bonespike: {
			return 2;
			break;
		}
		case shroud: {
			return 3;
			break;
		}
		case swindle: {
			return 2;
		}
		case madnessplague: {
			return 1;
		}
		case anyweapon: {
			return 1;
			break;
		}
		default: {
			return 0;
			break;
		}
	}
}
int originalhealth(minionname a) {
	switch (a) {
		case sharkspirit_m: {
			return 3;
			break;
		}
		case sharkspirit_mx: {
			return 3;
			break;
		}
		case foxyfraud_m: {
			return 2;
			break;
		}
		case mailboxdancer_m: {
			return 2;
			break;
		}
		case cutterbutter_m: {
			return 3;
			break;
		}
		case redsmoke_m: {
			return 2;
			break;
		}
		case shadowcaster_m: {
			return 4;
			break;
		}
		case spectralpillager_m: {
			return 5;
			break;
		}
		case elvensinger_m: {
			return 2;
		}
		case illucia_m: {
			return 3;
		}
		case brann_m: {
			return 4;
		}
		case zolag_m: {
			return 2;
		}
		case anyminion_m: {
			return 99;
			break;
		}
		case enemyhero: {
			assert(0);
			return 0;
			break;
		}
		case enemyminion: {
			assert(0);
			return 0;
			break;
		}
		default: {
			assert(0);
			return 0;
			break;
		}
	}
}
int originalhealth_c(cardname a) {
	if (normalminion(a)) {
		return originalhealth(cn2mn(a));
	}
	else {
		return 0;
	}
}

card cardcons(cardname a, int b) {
	card c;
	c.name = a;
	c.cost = b;
	c.health = originalhealth_c(a);
	return c;
}
card cardcons(cardname a, int b, int c) {
	card d;
	d.name = a;
	d.cost = b;
	d.health = c;
	return d;
}

minion minioncons(minionname a) {
	minion b;
	b.name = a;
	b.health = originalhealth(a);
	b.curhealth = b.health;
	return b;
}
minion minioncons(minionname a, int b, int c) {
	minion d;
	d.name = a;
	d.health = b;
	d.curhealth = c;
	return d;
}

state emptystcons() {
	state a;
	a.H = 0;
	a.F = 0;
	rep(i, 0, 3) a.auras[i] = 0;
	a.mana = 0;
	a.num = 0;
	a.drawmn = 0;
	a.hatk = 0;
	a.todemise = anyspell;
	return a;
}
state emptyst = emptystcons();

oxy oxycons(int a, int b){//oxy:x-y操作
	oxy c;
	c.x = a;
	c.y = b;
	return c;
}
ope opecons(int a, cardname b, minionname c) {//
	ope d;
	d.cost = a;
	d.name = b;
	d.target = c;
	return d;
}
ope exact(state a, oxy b) {//将x-y操作具体为用于输出的具体操作
	minionname z = nul;
	if (b.y >= 0) {
		z = a.fields[b.y].name;
		if (a.hands[b.x].name == backstab && a.fields[b.y].curhealth > 2) {
			z = nul;
		}
		if (a.hands[b.x].name == extortion && a.fields[b.y].curhealth > 3) {
			z = nul;
		}
	}
	else if (b.y == -1) {
		z = nul;
	}
	else if (b.y == -2) {
		z = enemyhero;
	}
	else {
		assert(0);
	}

	if (b.x >= 0) {
		return opecons(a.hands[b.x].cost, a.hands[b.x].name, z);
	}
	else if (b.x == -1) {
		return opecons(0, heroattack, z);
	}
	else {
		assert(0);
		return opecons(0, invalid, nul);
	}
}

ope exact4f(state a, oxy b) {//与具体操作类似，且融入公式
	ope o = exact(a, b);
	if (o.name == extortion) o.name = backstab;//要挟按照背刺融入公式
	//某些不常见（随从）牌也可以按照另一张融入公式，暂不考虑
	if (o.name == demise) o.name = a.todemise;//殒命暗影按照实际复制的法术融入公式
	return o;
}

oxys emptyoxyscons() {
	oxys a;
	a.os.clear();
	return a;
}
oxys emptyoxys = emptyoxyscons();

opes emptyopescons() {
	opes a;
	a.os.clear();
	return a;
}
opes emptyopes = emptyopescons();

int stabable;
int boneable;
int spelldebuff;
int miniondebuff;
int battlecrydebuff;

int deckmn;
minionname deckm[99];

int oppoH;
card oppohands[10];

int iceblockif;

int iseq[999], isn;

quiz emptyqcons() {
	quiz q;
	q.qst = emptystcons();
	q.qnd = 0;
	return q;
}
vector<quiz> quizs;

vector<opes> cls;
vector<opes> allcls;