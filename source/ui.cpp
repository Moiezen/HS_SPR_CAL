#include "solve.h"
#include "pre.h"
#include "auto.h"
#include "ui.h"

#include <graphics.h>
#define setb setbkcolor
#define setc setcolor
#define setf setfillcolor
#define sett settextjustify
#define refresh delay_ms(0)
#define adddd(a,b,c,d,e,f,g,h,i,j) doms.push_back(domaincons(rectcons(a,b,c,d),e,f,g,h,i,j));

int H = 640;
int W = 1280;

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
	nodomt, vnx, vx, vn, cn, c0, cx, go, ans, lk, lk1, lk2, exa, vx0, gogo
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

void init() {
	initgraph(W, H);
	setcaption(".20221002.001");
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

void follow(domain a) {
	for (auto& i : doms) {
		if (a.id == i.id) {
			i = a;
			break;
		}
	}
}

const int countn = 25;
const int splitn = 14;
int k1[countn] = { 'Y','L','X','D','G','E','T','A','B','C','J','S','H','W',-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,46};

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

void getdoms() {
	doms.clear();

	string n1[countn] = {
		shak_s(), foxy_s(), mail_s(), scab_s(), pill_s(), elvn_s(), tenw_s(),
		step_s(), stab_s(), bone_s(), coin_s(), prep_s(), pshn_s(), shrd_s(),
		anym_s(), anys_s(), trsh_s(), anyw_s(), cmbs_s(), si7_s(), swin_s(), cast_s(), iuca_s(), bran_s(), clr_s()
	};

	string a1[4] = { a0_s(), a1_s(), a2_s(), a3_s() };

	adddd(860, 600, 920, 640, vx, mana_s(), 0, manadomid = 1, -1, 10);
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
	adddd(40, 400, 80, 440, c0, "", 0, 12, 8, -1);
	//12
	rep(i, 0, 9) adddd((i + 2) % 3 * 40, 400 + (i + 2) / 3 * 40, 40 + (i + 2) % 3 * 40, 440 + (i + 2) / 3 * 40, cx, "", i, 13 + i, 48 + i, -1);
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
	adddd(980, 600, 1040, 640, vx, time_s(), 15, tlimdomid = 39, -1, 999);
	//39
	adddd(1100, 600, 1160, 640, vx, targ_s(), 30, tardomid = 40, -1, 999);
	//40
	string dftlk = getdftlk();
	adddd(0, 0, 400, 40, lk, dftlk, 0, lkdomid = 41, -1, -1);
	//41
	adddd(400, 0, 440, 40, lk1, chng_s(), 0, 42, -1, -1);
	//42
	adddd(440, 0, 480, 40, lk2, read_s(), 0, 43, 32, -1);
	//43
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
	if (s == bran_s()) return bronze;
	if (s == anys_s()) return anyspell;
	if (s == anym_s()) return anyminion;
	if (s == anyw_s()) return anyweapon;
	if (s == cmbs_s()) return anycombospell;
	if (s == trsh_s()) return invalid;
	return invalid;
}

int __tar = 999;
int __tlim = 999999;

void drawdom(domain a, bool sl) {
	rect r = a.r;

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
		case lk1:
		case lk2:
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

void st2doms(state st) {
	domain tmp;

	tmp = id2dom(sdbdomid);
	tmp.x = spelldebuff;
	drawdom(tmp, 0);
	follow(tmp);

	tmp = id2dom(mdbdomid);
	tmp.x = miniondebuff;
	drawdom(tmp, 0);
	follow(tmp);

	tmp = id2dom(bdbdomid);
	tmp.x = battlecrydebuff;
	drawdom(tmp, 0);
	follow(tmp);

	tmp = id2dom(modedomid);
	tmp.x = stabable;
	drawdom(tmp, 0);
	follow(tmp);

	tmp = id2dom(mode2domid);
	tmp.x = boneable;
	drawdom(tmp, 0);
	follow(tmp);

	rep(i, 0, deckmn - 1) {
		tmp = id2dom(deckmdomid[i]);
		tmp.name = mn2str(deckm[i]);
		drawdom(tmp, 0);
		follow(tmp);
	}

	rep(i, deckmn, 9) {
		tmp = id2dom(deckmdomid[i]);
		tmp.name = clr_s();
		drawdom(tmp, 0);
		follow(tmp);
	}

	rep(i, 0, st.H - 1) {
		tmp = id2dom(handsdomid[i]);
		tmp.name = cn2str(st.hands[i].name);
		tmp.x = st.hands[i].cost;
		drawdom(tmp, 0);
		follow(tmp);

		tmp = id2dom(chdomid[i]);
		tmp.x = st.hands[i].health;
		drawdom(tmp, 0);
		follow(tmp);
	}
	rep(i, st.H, 9) {
		tmp = id2dom(handsdomid[i]);
		tmp.name = clr_s();
		tmp.x = 0;
		drawdom(tmp, 0);
		follow(tmp);

		tmp = id2dom(chdomid[i]);
		tmp.x = 0;
		drawdom(tmp, 0);
		follow(tmp);
	}

	rep(i, 0, st.F - 1) {
		tmp = id2dom(fieldsdomid[i]);
		tmp.name = mn2str(st.fields[i].name);
		drawdom(tmp, 0);
		follow(tmp);

		tmp = id2dom(fmhdomid[i]);
		tmp.x = st.fields[i].health;
		drawdom(tmp, 0);
		follow(tmp);

		tmp = id2dom(fmchdomid[i]);
		tmp.x = st.fields[i].curhealth;
		drawdom(tmp, 0);
		follow(tmp);
	}
	rep(i, st.F, 6) {
		tmp = id2dom(fieldsdomid[i]);
		tmp.name = clr_s();
		drawdom(tmp, 0);
		follow(tmp);

		tmp = id2dom(fmhdomid[i]);
		tmp.x = 0;
		drawdom(tmp, 0);
		follow(tmp);

		tmp = id2dom(fmchdomid[i]);
		tmp.x = 0;
		drawdom(tmp, 0);
		follow(tmp);
	}

	rep(i, 0, 3) {
		tmp = id2dom(aurasdomid[i]);
		tmp.x = st.auras[i];
		drawdom(tmp, 0);
		follow(tmp);
	}

	tmp = id2dom(manadomid);
	tmp.x = st.mana;
	drawdom(tmp, 0);
	follow(tmp);

	tmp = id2dom(numdomid);
	tmp.x = st.num;
	drawdom(tmp, 0);
	follow(tmp);
}

state doms2st(vector<domain> a) {
	spelldebuff = id2dom(sdbdomid).x;
	miniondebuff = id2dom(mdbdomid).x;
	battlecrydebuff = id2dom(bdbdomid).x;
	stabable = id2dom(modedomid).x;
	boneable = id2dom(mode2domid).x;

	__tar = id2dom(tardomid).x;
	__tlim = id2dom(tlimdomid).x;

	state st;
	domain tmp, tmp2, tmp3;

	deckmn = 0;
	rep(i, 0, 9) {
		tmp = id2dom(deckmdomid[i]);
		if (tmp.name != clr_s()) deckm[deckmn++] = cn2mn(str2cn(tmp.name));
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
		if (tmp.name != clr_s()) st.fields[st.F++] = minioncons(cn2mn(str2cn(tmp.name)), tmp2.x, tmp3.x);
	}

	rep(i, 0, 3) {
		st.auras[i] = min(id2dom(aurasdomid[i]).x, alim[i]);
	}

	st.mana = id2dom(manadomid).x;
	st.num = id2dom(numdomid).x;
	return st;
}

void loaddoms() {
	for (auto i : doms) {
		drawdom(i, 0);
	}
	selected = nodomain;
	inputing = false;
}

bool legalcn4vn(string s) {
	if (s == clr_s()) return true;
	if (legalcn2mn(str2cn(s))) return true;
	return false;
}

void refreshans(string _s) {
	domain ans = id2dom(ansdomid);
	ans.name = _s;
	drawdom(ans, 0);
	follow(ans);
	refresh;
}

state initstcons() {
	spelldebuff = 0;
	miniondebuff = 0;
	battlecrydebuff = 0;
	stabable = 1;
	boneable = 1;

	state a;
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
	return a;
}

void loadauto() {
	int _tar = 999;
	state st = autoread(id2dom(lkdomid).name, _tar);
	domain tmp;

	st2doms(st);

	//tmp = id2dom(tlimdomid);
	//tmp.x = 15;
	//drawdom(tmp, 0);
	//follow(tmp);

	tmp = id2dom(tardomid);
	if (tmp.x != 999) {
		tmp.x = _tar;
		drawdom(tmp, 0);
		follow(tmp);
	}
}

void loadsample() {
	state initst = initstcons();
	domain tmp;

	st2doms(initst);
	
	tmp = id2dom(tlimdomid);
	tmp.x = 999;
	drawdom(tmp, 0);
	follow(tmp);

	tmp = id2dom(tardomid);
	tmp.x = 60;
	drawdom(tmp, 0);
	follow(tmp);
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
			if (selected.type == vnx || (selected.type == vn && legalcn4vn(toselect.name))) {
				//非随从在UI上就不允许被放置在随从位
				inputing = false;

				selected.name = toselect.name;
				drawdom(selected, 1);
				follow(selected);

				if (selected.id >= handsdomid[0] && selected.id <= handsdomid[9]) {
					domain tmp;
					int z = selected.id - handsdomid[0];
					//then handsdomid[z] = selected.id

					selected.x = originalcost_c(str2cn(selected.name));
					drawdom(selected, 1);
					follow(selected);

					tmp = id2dom(chdomid[z]);
					tmp.x = originalhealth_c(str2cn(selected.name));
					drawdom(tmp, 0);
					follow(tmp);
				}
				if (selected.id >= fieldsdomid[0] && selected.id <= fieldsdomid[6]) {
					domain tmp;
					int z = selected.id - fieldsdomid[0];
					//then handsdomid[z] = selected.id

					tmp = id2dom(fmhdomid[z]);
					tmp.x = originalhealth_c(str2cn(selected.name));
					drawdom(tmp, 0);
					follow(tmp);

					tmp = id2dom(fmchdomid[z]);
					tmp.x = originalhealth_c(str2cn(selected.name));
					drawdom(tmp, 0);
					follow(tmp);
				}
			}
			break;
		}
		case c0: {
			if (selected.type == vx || selected.type == vnx || selected.type == vx0) {
				inputing = true;
				
				selected.x = 0;
				drawdom(selected, 1);
				follow(selected);
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
				drawdom(selected, 1);
				follow(selected);
			}
			break;
		}
		case go: {
			inputing = false;

			state st = doms2st(doms);
			domain ans = id2dom(ansdomid);
			ans.name = _solve(st, __tar, __tlim, 0, 0, 0, 1, 1, 0, 0);
			drawdom(ans, 0);
			follow(ans);
			break;
		}
		case gogo: {
			inputing = false;

			loadauto();
			selected = nodomain;

			domain tmp = id2dom(ansdomid);
			tmp.name = "";
			drawdom(tmp, 0);
			follow(tmp);

			state st = doms2st(doms);
			domain ans = id2dom(ansdomid);
			ans.name = _solve(st, __tar, __tlim, 0, 0, 0, 1, 1, 0, 0);
			drawdom(ans, 0);
			follow(ans);
			break;
		}
		case ans:
		case lk: {

			break;
		}
		case lk1: {
			inputing = false;

			char _lk[105];
			inputbox_getline(hint_s().c_str(), "宇宙甜心", _lk, 100);
			domain lk = id2dom(lkdomid);
			lk.name = (string)_lk;
			savedftlk(lk.name);
			drawdom(lk, 0);
			follow(lk);
			break;
		}
		case lk2: {
			inputing = false;

			loadauto();
			selected = nodomain;

			domain tmp = id2dom(ansdomid);
			tmp.name = "";
			drawdom(tmp, 0);
			follow(tmp);
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