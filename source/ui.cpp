#include "solve.h"
#include "pre.h"
#include "auto.h"
#include "adapt.h"
#include "ui.h"

#include <graphics.h>
#define setb setbkcolor
#define setc setcolor
#define setf setfillcolor
#define sett settextjustify
#define refresh delay_ms(0)
#define adddd(a,b,c,d,e,f,g,h,i,j) doms.push_back(domaincons(rectcons(a,b,c,d),e,f,g,h,i,j));

struct rect {
	int x1, y1, x2, y2;
};
rect rectcons(int a, int b, int c, int d) {
	rect r;
	r.x1 = a; r.y1 = b; r.x2 = c; r.y2 = d;
	return r;
}
rect norect = rectcons(-1, -1, -1, -1);
rect cutedge(rect a, int b) {
	return rectcons(a.x1 + b, a.y1 + b, a.x2 - b, a.y2 - b);
}
rect movedxdy(rect a, int dx, int dy) {
	return rectcons(a.x1 + dx, a.y1 + dy, a.x2 +dx, a.y2 - dy);
}
void barr(rect a, color_t b) {
	setf(b);
	bar(a.x1, a.y1, a.x2, a.y2);
}
void rectr(rect a, color_t b) {
	setc(b);
	rectangle(a.x1, a.y1, a.x2, a.y2);
}
void textr(rect a, color_t b, string c) {
	setc(b);
	sett(CENTER_TEXT, CENTER_TEXT);
	outtextxy((a.x1 + a.x2) / 2, (a.y1 + a.y2) / 2, c.c_str());
}
void textra(rect a, color_t b, string c) {
	setc(b);
	sett(LEFT_TEXT, TOP_TEXT);
	int xx = a.x1 + 5, yy = a.y1 + 5;
	while (c != "") {
		auto p = c.find("\n");
		outtextxy(xx, yy, c.substr(0, p).c_str());
		c = c.substr(p + 1, c.size());
		yy += 20;
		if (yy >= 560) {
			yy = 5;
			xx += 200;
		}	
	}
}
bool inrect(int x, int y, rect a) {
	return x >= a.x1 && x < a.x2&& y >= a.y1 && y < a.y2;
}

enum domt {
	nodomt, vnx, vx, vn, cn, c0, cx, go, ans, lk, lk1, lk2, exa, vx0, gogo, lk2_1, lk0, adj
};
struct domain {
	rect r;
	domt type;
	string name;
	int x;
	int id;
	int key;
	int lim;
};
domain domaincons(rect a, domt b, string c, int d, int e, int f, int g) {
	domain dom;
	dom.r = a; dom.type = b; dom.name = c; dom.x = d; dom.id = e; dom.key = f; dom.lim = g;
	return dom;
}
domain nodomain = domaincons(norect, nodomt, "", -1, -1, -1, -1);
bool indom(int x, int y, domain a) {
	return inrect(x, y, a.r);
}

color_t bgc = EGERGB(255, 255, 255);
color_t bdc = EGERGB(0, 0, 0);
color_t slc = EGERGB(0, 255, 0);
color_t txc = EGERGB(0, 0, 255);

int H = 640;
int W = 1280;

string caption_s = "帆帆小甜心.20230104";

void init() {
	initgraph(W, H);
	setcaption(caption_s.c_str());
	setb(bgc);
}

rect _all = rectcons(0, 0, 1280, 640);
rect _start_cn = rectcons(1040, 560, 1160, 640);
rect _start_en = rectcons(1160, 560, 1280, 640);

void drawatt() {
	textr(_all, txc, "你已经阅读过https://github.com/Moiezen/HS_SPR_CAL/README.md，并且该HSSPRCAL.exe是直接获取的最新版本");

	barr(_start_cn, bdc);
	barr(cutedge(_start_cn, 1), bgc);
	textr(_start_cn, txc, "中文");

	barr(_start_en, bdc);
	barr(cutedge(_start_en, 1), bgc);
	textr(_start_en, txc, "EN");
}

void attention() {
	drawatt();
	refresh;

	mouse_msg e = { 0 };
	while (true) {
		while (mousemsg()) {
			e = getmouse();
		}

		if (e.is_down() && inrect(e.x, e.y, _start_cn)) {
			return;
		}
		if (e.is_down() && inrect(e.x, e.y, _start_en)) {
			_lang = EN;
			return;
		}
	}
}

vector<domain> doms;
domain selected;
bool inputing;

int manadomid;
int handsdomid[10];
int fieldsdomid[7];
int ansdomid;
int tardomid;
int tlimdomid;
int lkdomid;
int sdbdomid;
int mdbdomid;
int bdbdomid;
int modedomid;
int mode2domid;
int numdomid;
int aurasdomid[4];
int exadomid;
int icebdomid;
int hatkdomid;
int todemisedomid;
int adjustdomid;

int chdomid[10];
int fmhdomid[7];
int fmchdomid[7];
int deckmdomid[10];

domain id2dom(int id) {
	for (auto i : doms) {
		if (id == i.id) {
			return i;
			break;
		}
	}
	return nodomain;
}

string getdftlk() {
	cin.clear();
	//重置输入流，防止无法读取 

	FILE* f = freopen("dft.txt", "r", stdin);

	string s;
	getline(cin, s);

	fclose(stdin);

	return s;
}

void savedftlk(string s) {
	FILE* f = freopen("dft.txt", "w", stdout);

	printf("%s\n", s.c_str());

	fclose(stdout);
}

int k1[countn] = { 'Y','L','X','D','G','E','T','A','B','C','J','S','H','W',-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,46 };

void getdoms() {
	doms.clear();

	string n1[countn] = {
		shak_s(), foxy_s(), mail_s(), scab_s(), pill_s(), elvn_s(), tenw_s(),
		step_s(), stab_s(), bone_s(), coin_s(), prep_s(), pshn_s(), shrd_s(),
		anym_s(), anys_s(), trsh_s(), anyw_s(), cmbs_s(), si7_s(), swin_s(),
		shxk_s(), cast_s(), iuca_s(), bran_s(), zola_s(), plag_s(), demi_s(), clr_s()
	};

	string a1[4] = { a0_s(), a1_s(), a2_s(), a3_s() };

	adddd(920, 600, 980, 640, vx, mana_s(), 0, manadomid = 1, -1, 10);
	//1
	rep(i, 0, 9) adddd(200 + i * 60, 560, 260 + i * 60, 600, vnx, clr_s(), 0, handsdomid[i] = 2 + i, 1200000 + 1000 * i, 10);
	//2 ... 11
	rep(i, 0, 9) adddd(200 + i * 60, 600, 260 + i * 60, 640, vx0, "", 0, chdomid[i] = 201 + i, 1100000, 5);
	//201 ... 210
	rep(i, 0, 6) adddd(200 + i * 60, 520, 260 + i * 60, 560, vn, clr_s(), 0, fieldsdomid[i] = 101 + i, 1300000 + 1000 * i, -1);
	//101 ... 107
	rep(i, 0, 6) adddd(200 + i * 60, 480, 260 + i * 60, 520, vx0, "", 0, fmhdomid[i] = 301 + i, 1400000, 5);
	//301 ... 307
	rep(i, 0, 6) adddd(200 + i * 60, 440, 260 + i * 60, 480, vx0, "", 0, fmchdomid[i] = 401 + i, 1500000, 5);
	//401 ... 407
	rep(i, 0, 9) adddd(200 + i * 60, 360, 260 + i * 60, 400, vn, clr_s(), 0, deckmdomid[i] = 1001 + i, 9300000 + 1000 * i, -1);
	//1001 ... 1010
	adddd(40, 420, 80, 460, c0, "", 0, 12, 8, -1);
	//12
	rep(i, 0, 9) adddd((i + 2) % 3 * 40, 420 + (i + 2) / 3 * 40, 40 + (i + 2) % 3 * 40, 460 + (i + 2) / 3 * 40, cx, "", i, 13 + i, 48 + i, -1);
	//13 ... 22
	rep(i, 0, countn - 1) adddd(i % 4 * 40, 60 + i / 4 * 40 + (i >= splitn) * 40, 40 + i % 4 * 40, 100 + i / 4 * 40 + (i >= splitn) * 40, 
								cn, n1[i], 0, 123 + i, k1[i], -1);
	//123 ... 139
	adddd(1220, 600, 1280, 640, go, calc_s(), 0, 37, 13, -1);
	//37
	adddd(1220, 560, 1280, 600, gogo, randc_s(), 0, 737, 187, -1);
	//737
	adddd(880, 0, 1280, 560, ans, "", 0, ansdomid = 38, -1, -1);
	//38
	adddd(1020, 600, 1080, 640, vx, time_s(), 15, tlimdomid = 39, -1, 999);
	//39
	adddd(1120, 600, 1180, 640, vx, targ_s(), 30, tardomid = 40, -1, 999);
	//40
	string dftlk = getdftlk();
	adddd(0, 0, 400, 40, lk, dftlk, 0, lkdomid = 41, -1, -1);
	//41
	adddd(400, 0, 440, 40, lk0, adpt_s(), 0, 42, -1, -1);
	//51
	adddd(440, 0, 480, 40, lk1, chng_s(), 0, 42, -1, -1);
	//42
	adddd(480, 0, 520, 40, lk2, read_s(), 0, 43, 32, -1);
	//43
	adddd(520, 0, 560, 40, lk2_1, back_s(), 0, 91, 'Z', -1);
	//91
	adddd(440, 200, 560, 240, vx, stax_s(), 0, sdbdomid = 70, -1, 10);
	//70
	adddd(560, 200, 680, 240, vx, mtax_s(), 0, mdbdomid = 71, -1, 10);
	//71
	adddd(680, 200, 800, 240, vx, btax_s(), 0, bdbdomid = 72, -1, 10);
	//72
	adddd(200, 200, 320, 240, vx, able_s(), 1, modedomid = 44, -1, 1);
	//44
	adddd(320, 200, 440, 240, vx, able2_s(), 1, mode2domid = 73, -1, 1);
	//73
	adddd(200, 280, 320, 320, vx, plyd_s(), 0, numdomid = 45, -1, 10);
	//45
	rep(i, 0, 3) adddd(320 + 120 * i, 280, 440 + 120 * i, 320, vx, a1[i], 0, aurasdomid[i] = 46 + i, -1, alim[i]);
	//46 ... 49
	adddd(0, 600, 120, 640, exa, samp_s(), 0, exadomid = 50, -1, -1);
	//50
	adddd(200, 120, 320, 160, vx, iceblock_s(), 0, icebdomid = 80, -1, 1);
	//80
	adddd(320, 120, 440, 160, vx, heroattk_s(), 0, hatkdomid = 81, -1, 10);
	//81
	adddd(820, 560, 860, 600, vn, clr_s(), 0, todemisedomid = 82, -1, -1);
	//82
	adddd(880, 600, 900, 640, adj, smal_s(), 0, adjustdomid = 83, 189, -1);
	//83
}

cardname str2cn(string s) {
	if (s == step_s()) return shadowstep;
	if (s == stab_s()) return backstab;
	if (s == si7_s()) return extortion;
	if (s == bone_s()) return bonespike;
	if (s == coin_s()) return fakecoin;
	if (s == prep_s()) return preparation;
	if (s == pshn_s()) return illusionpotion;
	if (s == shrd_s()) return shroud;
	if (s == swin_s()) return swindle;
	if (s == shak_s()) return sharkspirit;
	if (s == foxy_s()) return foxyfraud;
	if (s == mail_s()) return mailboxdancer;
	if (s == scab_s()) return cutterbutter;
	if (s == tenw_s()) return redsmoke;
	if (s == pill_s()) return spectralpillager;
	if (s == cast_s()) return shadowcaster;
	if (s == elvn_s()) return elvensinger;
	if (s == iuca_s()) return illucia;
	if (s == bran_s()) return brann;
	if (s == zola_s()) return zolag;
	if (s == plag_s()) return madnessplague;
	if (s == anys_s()) return anyspell;
	if (s == anym_s()) return anyminion;
	if (s == anyw_s()) return anyweapon;
	if (s == cmbs_s()) return anycombospell;
	if (s == trsh_s()) return invalid;
	if (s == demi_s()) return demise;
 	return invalid;
}

minionname str2mn(string s) {
	if (s == shxk_s()) {
		return sharkspirit_mx;
	}
	else {
		return cn2mn(str2cn(s));
	}
}

int W_small = 400;
int if_small = 0;
//=0 when large
//=1 when small

void drawdom(domain a, bool sl) {
	rect r = a.r;
	if (if_small == 1) {
		r = movedxdy(r, -(W - W_small), 0);
	}

	barr(r, bdc);
	if (sl) {
		barr(cutedge(r, 1), slc);
		barr(cutedge(r, 5), bgc);
	}
	else {
		barr(cutedge(r, 1), bgc);
	}

	switch (a.type) {
		case nodomt: {

			break;
		}
		case vnx: {
			if (a.name == clr_s()) textr(r, txc, "");
			else textr(r, txc, a.name + to_string(a.x));
			break;
		}
		case vx: {
			textr(r, txc, a.name + to_string(a.x));
			break;
		}
		case vx0: {
			if (a.x == 0) textr(r, txc, "");
			else textr(r, txc, a.name + to_string(a.x));
			break;
		}
		case vn: {
			if (a.name == clr_s()) textr(r, txc, "");
			else textr(r, txc, a.name);
			break;
		}
		case cn:
		case go:
		case gogo:
		case lk0:
		case lk1:
		case lk2:
		case lk2_1:
		case adj:
		case exa: {
			textr(r, txc, a.name);
			break;
		}
		case c0: {
			textr(r, txc, cl_s());
			break;
		}
		case cx: {
			textr(r, txc, to_string(a.x));
			break;
		}
		case ans: {
			textra(r, txc, a.name);
			break;
		}
		case lk: {
			textr(r, txc, a.name + "\\Logs\\power.log");
			break;
		}
	}
}

void drawfixdom(domain a, int x = 0) {
	drawdom(a, x);
	for (auto& i : doms) {
		if (a.id == i.id) {
			i = a;
			break;
		}
	}
}

void loaddoms() {
	for (auto i : doms) {
		drawdom(i, 0);
	}
	selected = nodomain;
	inputing = false;
}

void adjust_size_small() {
	initgraph(W_small, H);
	setcaption(caption_s.c_str());
	setb(bgc);
	cleardevice();
	loaddoms();

	domain tmp = id2dom(adjustdomid);
	tmp.name = larg_s();
	drawfixdom(tmp);
}

void adjust_size_large() {
	initgraph(W, H);
	setcaption(caption_s.c_str());
	setb(bgc);
	cleardevice();
	loaddoms();

	domain tmp = id2dom(adjustdomid);
	tmp.name = smal_s();
	drawfixdom(tmp);
}

void adjust_size() {
	if (if_small == 0) {
		if_small = 1;
		adjust_size_small();
	}
	else {
		if_small = 0;
		adjust_size_large();
	}
}

int __tar;
int __tlim;

state doms2st() {
	spelldebuff = id2dom(sdbdomid).x;
	miniondebuff = id2dom(mdbdomid).x;
	battlecrydebuff = id2dom(bdbdomid).x;
	stabable = id2dom(modedomid).x;
	boneable = id2dom(mode2domid).x;
	iceblockif = id2dom(icebdomid).x;

	__tar = id2dom(tardomid).x;
	__tlim = id2dom(tlimdomid).x;

	state st = emptyst;
	domain tmp, tmp2, tmp3;

	deckmn = 0;
	rep(i, 0, 9) {
		tmp = id2dom(deckmdomid[i]);
		if (tmp.name != clr_s()) deckm[deckmn++] = str2mn(tmp.name);
	}

	st.H = 0;
	rep(i, 0, 9) {
		tmp = id2dom(handsdomid[i]);
		tmp2 = id2dom(chdomid[i]);
		if (tmp.name != clr_s()) st.hands[st.H++] = cardcons(str2cn(tmp.name), tmp.x, tmp2.x);
	}

	oppoH = st.H;
	rep(i, 0, st.H - 1) {
		oppohands[i] = st.hands[i];
	}

	st.F = 0;
	rep(i, 0, 6) {
		tmp = id2dom(fieldsdomid[i]);
		tmp2 = id2dom(fmhdomid[i]);
		tmp3 = id2dom(fmchdomid[i]);
		if (tmp.name != clr_s()) st.fields[st.F++] = minioncons(str2mn(tmp.name), tmp2.x, tmp3.x);
	}

	rep(i, 0, 3) {
		st.auras[i] = min(id2dom(aurasdomid[i]).x, alim[i]);
	}

	st.mana = id2dom(manadomid).x;
	st.num = id2dom(numdomid).x;
	st.drawmn = 0;
	st.hatk = id2dom(hatkdomid).x;
	st.todemise = str2cn(id2dom(todemisedomid).name);
	return st;
}

void st2doms(state st) {
	domain tmp;

	tmp = id2dom(sdbdomid);
	tmp.x = spelldebuff;
	drawfixdom(tmp);

	tmp = id2dom(mdbdomid);
	tmp.x = miniondebuff;
	drawfixdom(tmp);

	tmp = id2dom(bdbdomid);
	tmp.x = battlecrydebuff;
	drawfixdom(tmp);

	tmp = id2dom(modedomid);
	tmp.x = stabable;
	drawfixdom(tmp);

	tmp = id2dom(mode2domid);
	tmp.x = boneable;
	drawfixdom(tmp);

	tmp = id2dom(icebdomid);
	tmp.x = iceblockif;
	drawfixdom(tmp);

	if (deckmn >= 10) {
		deckmn = 10;
	}
	//autoread得到的牌库随从实际上可能超过10
	//在UI部分以及之后的计算部分，暂仅考虑不超过10个牌库随从

	rep(i, 0, deckmn - 1) {
		tmp = id2dom(deckmdomid[i]);
		tmp.name = mn2str(deckm[i]);
		drawfixdom(tmp);
	}

	rep(i, deckmn, 9) {
		tmp = id2dom(deckmdomid[i]);
		tmp.name = clr_s();
		drawfixdom(tmp);
	}

	rep(i, 0, st.H - 1) {
		tmp = id2dom(handsdomid[i]);
		tmp.name = cn2str(st.hands[i].name);
		tmp.x = st.hands[i].cost;
		drawfixdom(tmp);

		tmp = id2dom(chdomid[i]);
		tmp.x = st.hands[i].health;
		drawfixdom(tmp);
	}
	rep(i, st.H, 9) {
		tmp = id2dom(handsdomid[i]);
		tmp.name = clr_s();
		tmp.x = 0;
		drawfixdom(tmp);

		tmp = id2dom(chdomid[i]);
		tmp.x = 0;
		drawfixdom(tmp);
	}

	rep(i, 0, st.F - 1) {
		tmp = id2dom(fieldsdomid[i]);
		tmp.name = mn2str(st.fields[i].name);
		drawfixdom(tmp);

		tmp = id2dom(fmhdomid[i]);
		tmp.x = st.fields[i].health;
		drawfixdom(tmp);

		tmp = id2dom(fmchdomid[i]);
		tmp.x = st.fields[i].curhealth;
		drawfixdom(tmp);
	}
	rep(i, st.F, 6) {
		tmp = id2dom(fieldsdomid[i]);
		tmp.name = clr_s();
		drawfixdom(tmp);

		tmp = id2dom(fmhdomid[i]);
		tmp.x = 0;
		drawfixdom(tmp);

		tmp = id2dom(fmchdomid[i]);
		tmp.x = 0;
		drawfixdom(tmp);
	}

	rep(i, 0, 3) {
		tmp = id2dom(aurasdomid[i]);
		tmp.x = st.auras[i];
		drawfixdom(tmp);
	}

	tmp = id2dom(manadomid);
	tmp.x = st.mana;
	drawfixdom(tmp);

	tmp = id2dom(numdomid);
	tmp.x = st.num;
	drawfixdom(tmp);

	tmp = id2dom(hatkdomid);
	tmp.x = st.hatk;
	drawfixdom(tmp);

	tmp = id2dom(todemisedomid);
	tmp.name = cn2str(st.todemise);
	drawfixdom(tmp);
}

bool legalstr2cn4vn(string s) {
	if (s == clr_s()) return true;
	if (s == shxk_s()) return true;
	if (normalminion(str2cn(s))) return true;
	return false;
}

bool legalstr2cn4vnx(string s) {
	return not (s == shxk_s());
}

bool legalstr2cn4vn_demi(string s) {
	if (s == clr_s()) return true;
	if (normalspell(str2cn(s))) return true;
	return false;
}

void refreshans(string _s) {
	domain tmp = id2dom(ansdomid);
	tmp.name = _s;
	drawfixdom(tmp);
	refresh;
}

state initst() {
	spelldebuff = 0;
	miniondebuff = 0;
	battlecrydebuff = 0;
	stabable = 1;
	boneable = 1;

	state a = emptyst;
	a.H = 10;
	a.hands[0] = cardcons(fakecoin, 0);
	a.hands[1] = cardcons(fakecoin, 0);
	a.hands[2] = cardcons(fakecoin, 0);
	a.hands[3] = cardcons(shadowstep, 0);
	a.hands[4] = cardcons(preparation, 0);
	a.hands[5] = cardcons(foxyfraud, 2);
	a.hands[6] = cardcons(cutterbutter, 4);
	a.hands[7] = cardcons(redsmoke, 2);
	a.hands[8] = cardcons(spectralpillager, 6);
	a.hands[9] = cardcons(illusionpotion, 4);
	srand(time(0));
	//random_shuffle(a.hands, a.hands + 10);
	a.F = 0;
	rep(i, 0, 3) a.auras[i] = 0;
	a.mana = 10;
	a.num = 0;
	a.drawmn = 0;
	a.hatk = 0;
	a.todemise = anyspell;
	return a;
}

int countslimitsaved = 0;

void loadauto(int normalwhen0 = 0) {
	int _tar = 999;
	int _countslimit = normalwhen0 == 0 ? 1 << 30 : countslimitsaved - 1;
	state st = autoread(id2dom(lkdomid).name, _tar, _countslimit);
	domain tmp;

	countslimitsaved = _countslimit;

	st2doms(st);

	tmp = id2dom(tardomid);
	if (tmp.x != 999) {
		tmp.x = _tar;
		drawfixdom(tmp);
	}
}

void loadsample() {
	state st = initst();
	domain tmp;

	st2doms(st);
	
	tmp = id2dom(tlimdomid);
	tmp.x = 999;
	drawfixdom(tmp);

	tmp = id2dom(tardomid);
	tmp.x = 60;
	drawfixdom(tmp);
}

void touch(domain toselect) {
	rect r = toselect.r;
	rectr(cutedge(r, 3), slc);
	delay_ms(100);
	rectr(cutedge(r, 3), bgc);

	switch (toselect.type) {
		case nodomt: {

			break;
		}
		case vnx:
		case vn:
		case vx:
		case vx0: {
			if (selected.id == toselect.id) {
				inputing = false;

				drawdom(selected, 0);
				selected = nodomain;
			}
			else {
				inputing = false;

				drawdom(selected, 0);
				drawdom(toselect, 1);
				selected = toselect;
			}
			break;
		}
		case cn: {
			if (
				(
					selected.type == vnx && legalstr2cn4vnx(toselect.name)
				)
				||
				(
					selected.type == vn &&
					(
						(
							selected.id != todemisedomid && legalstr2cn4vn(toselect.name)
						)
						||
						(
							selected.id == todemisedomid && legalstr2cn4vn_demi(toselect.name)
						)
					)
				)
			   ) {
				//在UI上已经：
				//沉默的鲨鱼之灵不允许被放置在手牌位
				//非随从不允许被放置在随从位
				inputing = false;
				
				selected.name = toselect.name;
				drawfixdom(selected, 1);

				if (selected.id >= handsdomid[0] && selected.id <= handsdomid[9]) {
					domain tmp;
					int z = selected.id - handsdomid[0];
					//then handsdomid[z] = selected.id

					selected.x = originalcost_c(str2cn(selected.name));
					drawfixdom(selected, 1);

					tmp = id2dom(chdomid[z]);
					tmp.x = originalhealth_c(str2cn(selected.name));
					drawfixdom(tmp);
				}
				if (selected.id >= fieldsdomid[0] && selected.id <= fieldsdomid[6]) {
					domain tmp;
					int z = selected.id - fieldsdomid[0];
					//then handsdomid[z] = selected.id

					tmp = id2dom(fmhdomid[z]);
					tmp.x = originalhealth_c(str2cn(selected.name));
					drawfixdom(tmp);

					tmp = id2dom(fmchdomid[z]);
					tmp.x = originalhealth_c(str2cn(selected.name));
					drawfixdom(tmp);
				}
			}
			break;
		}
		case c0: {
			if (selected.type == vx || selected.type == vnx || selected.type == vx0) {
				inputing = true;
				
				selected.x = 0;
				drawfixdom(selected, 1);
			}
			break;
		}
		case cx: {
			if (selected.type == vx || selected.type == vnx || selected.type == vx0) {
				if (!inputing) {
					selected.x = 0;
				}
				inputing = true;

				selected.x = min(selected.x * 10 + toselect.x, selected.lim);
				drawfixdom(selected, 1);
			}
			break;
		}
		case go: {
			inputing = false;

			state st = doms2st();
			domain tmp = id2dom(ansdomid);
			tmp.name = _solve(st, __tar, __tlim, 0, 0, 0, 1, 1, 0, 0);
			drawfixdom(tmp);
			break;
		}
		case gogo: {
			inputing = false;

			loadauto();
			selected = nodomain;

			domain tmp = id2dom(ansdomid);
			tmp.name = "";
			drawfixdom(tmp);

			state st = doms2st();
			tmp = id2dom(ansdomid);
			tmp.name = _solve(st, __tar, __tlim, 0, 0, 0, 1, 1, 0, 0);
			drawfixdom(tmp);
			break;
		}
		case ans:
		case lk: {

			break;
		}
		case lk0: {
			inputing = false;

			string _lk = adaptlk();
			domain tmp = id2dom(lkdomid);
			if (_lk.length() == 0) break;
			tmp.name = _lk;
			savedftlk(tmp.name);
			drawfixdom(tmp);
			break;
		}
		case lk1: {
			inputing = false;

			char _lk[105] = {};
			inputbox_getline(hint_s().c_str(), "帆帆甜甜", _lk, 100);
			domain tmp = id2dom(lkdomid);
			tmp.name = _lk;
			savedftlk(tmp.name);
			drawfixdom(tmp);
			break;
		}
		case lk2: {
			inputing = false;

			loadauto();
			selected = nodomain;

			domain tmp = id2dom(ansdomid);
			tmp.name = "";
			drawfixdom(tmp);
			break;
		}
		case lk2_1: {
			inputing = false;

			loadauto(1);
			selected = nodomain;

			domain tmp = id2dom(ansdomid);
			tmp.name = "";
			drawfixdom(tmp);
			break;
		}
		case adj: {
			inputing = false;

			adjust_size();
			selected = nodomain;
			break;
		}
		case exa: {
			inputing = false;

			loadsample();
			selected = nodomain;
			break;
		}
	}
}

void click(int x, int y) {
	if (if_small == 1) {
		x = x + (W - W_small);
	}

	domain t = nodomain;
	for (auto i : doms) {
		if (indom(x, y, i)) {
			t = i;
			break;
		}
	}
	touch(t);
}

void press(int k) {
	//rect a = rectcons(610, 0, 670, 40);
	//textr(a, txc, to_string(k));

	if (k == 37) {
		k = selected.key - 1000;
	}
	if (k == 38) {
		k = selected.key + 100000;
	}
	if (k == 39) {
		k = selected.key + 1000;
	}
	if (k == 40) {
		k = selected.key - 100000;
	}

	//上下左右特例

	if (k >= 96 && k <= 105) {
		k = k - 48;
	}

	//小键盘数字键特例

	domain t = nodomain;
	for (auto i : doms) {
		if (i.key == k) {
			t = i;
			break;
		}
	}
	touch(t);
}

void ui_main() {
	Load();

	//ShowWindow(GetForegroundWindow(), 0);

	init();
	attention();
	cleardevice();

	getdoms();
	loaddoms();

	refresh;

	key_msg k = { 0 };
	mouse_msg e = { 0 };
	int last = 0;
	while (true) {
		if (kbmsg()) {
			k = getkey();
			/*
			while (kbmsg()) {
				k = getkey();
			}
			*/
			//按键消息不需要使用while控制至最后
			if (k.msg == key_msg_down) {
				press(k.key);
				refresh;
			}
		}
		if (mousemsg()) {
			e = getmouse();
			while (mousemsg()) {
				e = getmouse();
			}
			if (e.is_down()) {
				click(e.x, e.y);
				refresh;
			}
		}
	}

	closegraph();
}