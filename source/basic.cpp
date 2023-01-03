#include "basic.h"

lang _lang = CN;

string shak_s() {
	return _lang == CN ? "����" : "Shak";
}
string shxk_s() {
	return _lang == CN ? "����" : "Shxk";
}
string foxy_s() {
	return _lang == CN ? "��ǧ" : "Foxy";
}
string mail_s() {
	return _lang == CN ? "����" : "Mail";
}
string scab_s() {
	return _lang == CN ? "����" : "Scab";
}
string tenw_s() {
	return _lang == CN ? "����" : "Tenw";
}
string cast_s() {
	return _lang == CN ? "��ʩ" : "Cast";
}
string pill_s() {
	return _lang == CN ? "����" : "Pill";
}
string elvn_s() {
	return _lang == CN ? "ӽ��" : "Elvn";
}
string anym_s() {
	return _lang == CN ? "���" : "AnyM";
}
string face_s() {
	return _lang == CN ? "����" : "Face";
}
string step_s() {
	return _lang == CN ? "����" : "Step";
}
string stab_s() {
	return _lang == CN ? "����" : "Stab";
}
string si7_s() {
	return _lang == CN ? "ҪЮ" : "SI7.";
}
string coin_s() {
	return _lang == CN ? "�ٱ�" : "Coin";
}
string prep_s() {
	return _lang == CN ? "�Ż�" : "Prep";
}
string pshn_s() {
	return _lang == CN ? "��ҩ" : "Pshn";
}
string anys_s() {
	return _lang == CN ? "����" : "Anys";
}
string trsh_s() {
	return _lang == CN ? "����" : "Trsh";
}
string anyw_s() {
	return _lang == CN ? "����" : "AnyW";
}
string cmbs_s() {
	return _lang == CN ? "����" : "CmbS";
}
string bone_s() {
	return _lang == CN ? "�ݴ�" : "Bone";
}
string shrd_s() {
	return _lang == CN ? "�Ļ" : "Shrd";
}
string swin_s() {
	return _lang == CN ? "��ƭ" : "Swin";
}
string iuca_s() {
	return _lang == CN ? "����" : "Iuca";
}
string bran_s() {
	return _lang == CN ? "ͭ��" : "Bran";
}
string zola_s() {
	return _lang == CN ? "����" : "Zola";
}
string plag_s() {
	return _lang == CN ? "����" : "Plag";
}
string clr_s() {
	return _lang == CN ? "���" : "Clr.";
}
string mana_s() {
	return _lang == CN ? "ˮ��" : "Mana";
}
string calc_s() {
	return _lang == CN ? "����" : "Calc";
}
string randc_s() {
	return _lang == CN ? "����" : "R&C.";
}
string time_s() {
	return _lang == CN ? "ʱ��" : "Time";
}
string targ_s() {
	return _lang == CN ? "Ŀ��" : "Targ";
}
string adpt_s() {
	return _lang == CN ? "��Ӧ" : "Adpt";
}
string chng_s() {
	return _lang == CN ? "�޸�" : "Chng";
}
string read_s() {
	return _lang == CN ? "��ȡ" : "Read";
}
string back_s() {
	return _lang == CN ? "����" : "Back";
}
string stax_s() {
	return _lang == CN ? "�����ӷ�" : "AnySTax.";
}
string mtax_s() {
	return _lang == CN ? "��Ӽӷ�" : "AnyMTax,";
}
string btax_s() {
	return _lang == CN ? "ս��ӷ�" : "BcryTax.";
}
string able_s() {
	return _lang == CN ? "���̿���" : "StabAble";
}
string able2_s() {
	return _lang == CN ? "�ݴ̿���" : "BoneAble";
}
string plyd_s() {
	return _lang == CN ? "��������" : "CrdsPlyd";
}
string samp_s() {
	return _lang == CN ? "�鿴����" : "ViewSamp";
}
string cl_s() {
	return _lang == CN ? "��" : "Cl";
}
string a0_s() {
	return _lang == CN ? "�Ż�����" : "PrepDisc";
}
string a1_s() {
	return _lang == CN ? "��ǧ����" : "FoxyDisc";
}
string a2_s() {
	return _lang == CN ? "��һ����" : "Nxt1Disc";
}
string a3_s() {
	return _lang == CN ? "�¶�����" : "Nxt2Disc";
}
string hint_s() {
	return _lang == CN ? "������¯ʯ��˵����·�����س�ȷ�ϣ�" : "Please enter the local path of HS:";
}
string calcing_s() {
	return _lang == CN ? "(���ڼ���)" : "(Calcing.)";
}
string exhaust_s() {
	return _lang == CN ? "(�����)" : "(Exhaust.)";
}
string targrch_s() {
	return _lang == CN ? "(�������)" : "(TargRch.)";
}
string timerch_s() {
	return _lang == CN ? "(ʱ������)" : "(TimeRch.)";
}
string iceblock_s() {
	return _lang == CN ? "�Ʊ���Ҫ" : "IceBlock";
}
string heroattk_s() {
	return _lang == CN ? "Ӣ�۹���" : "HeroAttk";
}
string demi_s() {
	return _lang == CN ? "����" : "Demi";
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

oxy oxycons(int a, int b){//oxy:x-y����
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
ope exact(state a, oxy b) {//��x-y��������Ϊ��������ľ������
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

ope exact4f(state a, oxy b) {//�����������ƣ������빫ʽ
	ope o = exact(a, b);
	if (o.name == extortion) o.name = backstab;//ҪЮ���ձ������빫ʽ
	//ĳЩ����������ӣ���Ҳ���԰�����һ�����빫ʽ���ݲ�����
	if (o.name == demise) o.name = a.todemise;//������Ӱ����ʵ�ʸ��Ƶķ������빫ʽ
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