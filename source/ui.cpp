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
			yy = 0;
			xx += 200;
		}
	}
}
bool inrect(int x, int y, rect a) {
	return x >= a.x1 && x < a.x2&& y >= a.y1 && y < a.y2;
}

enum domt {
	nodomt, vnx, vx, vn, cn, c0, cx, go, ans, lk, lk1, lk2, exa
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
	setcaption(".20220907.002");
	setb(bgc);
}

rect _all = rectcons(0, 0, 1280, 640);
rect _start = rectcons(1160, 560, 1280, 640);

void drawatt() {
	textr(_all, txc, "点击开始，代表你已经阅读过https://github.com/Moiezen/HS_SPR_CAL的README.md，并且该HSSPRCAL.exe是直接获取的最新版本");

	barr(_start, bdc);
	barr(cutedge(_start, 1), bgc);
	textr(_start, txc, "开始");
}

void attention() {
	drawatt();
	refresh;

	mouse_msg e = { 0 };
	while (true) {
		while (mousemsg()) {
			e = getmouse();
		}

		if (e.is_down() && inrect(e.x, e.y, _start)) {
			return;
		}
	}
}

vector<domain> doms;
domain selected;
bool inputing;

int manadomid;
int cardsdomid[10];
int minionsdomid[7];
int ansdomid;
int tardomid;
int tlimdomid;
int lkdomid;
int sdbdomid;
int mdbdomid;
int bdbdomid;
int modedomid;
int numdomid;
int aurasdomid[4];
int exadomid;

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

string n1[15] = { "鱼灵","老千","箱舞","刀油","鬼灵","腾武","暗步","背刺","假币","伺机","幻药","随从","法术","垃圾","清除" };
int k1[15] = { 'Y','L','X','D','G','T','A','B','J','S','H',-1,-1,-1,46 };
string a1[4] = { "伺机层数","老千层数","刀一层数","刀二层数" };

string getdftlk() {
	FILE* f = freopen("dft.txt", "r", stdin);

	char s[105];
	scanf("%100s", s);

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

	adddd(860, 600, 920, 640, vx, "水晶", 0, manadomid = 1, -1, 10);
	//1
	rep(i, 0, 9) adddd(200 + i * 60, 600, 260 + i * 60, 640, vnx, "清除", 0, cardsdomid[i] = 2 + i, 200000 + 1000 * i, 10);
	//2 ... 11
	rep(i, 0, 6) adddd(200 + i * 60, 560, 260 + i * 60, 600, vn, "清除", 0, minionsdomid[i] = 101 + i, 300000 + 1000 * i, -1);
	//101 ... 107
	adddd(40, 400, 80, 440, c0, "", 0, 12, 8, -1);
	//12
	rep(i, 0, 9) adddd((i + 2) % 3 * 40, 400 + (i + 2) / 3 * 40, 40 + (i + 2) % 3 * 40, 440 + (i + 2) / 3 * 40, cx, "", i, 13 + i, 48 + i, -1);
	//13 ... 22
	rep(i, 0, 14) adddd(i % 3 * 40, 160 + i / 3 * 40, 40 + i % 3 * 40, 200 + i / 3 * 40, cn, n1[i], 0, 123 + i, k1[i], -1);
	//123 ... 137
	adddd(1220, 600, 1280, 640, go, "计算", 0, 37, 13, -1);
	//37
	adddd(880, 0, 1280, 560, ans, "", 0, ansdomid = 38, -1, -1);
	//38
	adddd(980, 600, 1040, 640, vx, "时限", 15, tlimdomid = 39, -1, 999);
	//39
	adddd(1100, 600, 1160, 640, vx, "目标", 999, tardomid = 40, -1, 999);
	//40
	string dftlk = getdftlk();
	adddd(0, 0, 400, 40, lk, dftlk, 0, lkdomid = 41, -1, -1);
	//41
	adddd(100, 60, 160, 100, lk1, "修改", 0, 42, -1, -1);
	//42
	adddd(240, 60, 300, 100, lk2, "读取", 0, 43, -1, -1);
	//43
	adddd(320, 400, 440, 440, vx, "法术加费", 0, sdbdomid = 70, -1, 10);
	//70
	adddd(440, 400, 560, 440, vx, "随从加费", 0, mdbdomid = 71, -1, 10);
	//71
	adddd(560, 400, 680, 440, vx, "战吼加费", 0, bdbdomid = 72, -1, 10);
	//72
	adddd(200, 400, 320, 440, vx, "背刺可用", 1, modedomid = 44, -1, 1);
	//44
	adddd(200, 480, 320, 520, vx, "已用牌数", 0, numdomid = 45, -1, 10);
	//45
	rep(i, 0, 3) adddd(320 + 120 * i, 480, 440 + 120 * i, 520, vx, a1[i], 0, aurasdomid[i] = 46 + i, -1, alim[i]);
	//46 ... 49
	adddd(0, 600, 120, 640, exa, "查看样例", 0, exadomid = 50, -1, -1);
	//50
}

cardname str2cn(string s) {
	if (s == "暗步") return shadowstep;
	if (s == "背刺") return backstab;
	if (s == "假币") return fakecoin;
	if (s == "伺机") return preparation;
	if (s == "幻药") return illusionpotion;
	if (s == "鱼灵") return sharkspirit;
	if (s == "老千") return foxyfraud;
	if (s == "箱舞") return mailboxdancer;
	if (s == "刀油") return cutterbutter;
	if (s == "腾武") return redsmoke;
	if (s == "鬼灵") return spectralpillager;
	if (s == "法术") return anyspell;
	if (s == "随从") return anyminion;
	if (s == "垃圾") return invalid;
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
			if (a.name == "清除") textr(r, txc, "");
			else textr(r, txc, a.name + to_string(a.x));
			break;
		}
		case vx: {
			textr(r, txc, a.name + to_string(a.x));
			break;
		}
		case vn: {
			if (a.name == "清除") textr(r, txc, "");
			else textr(r, txc, a.name);
			break;
		}
		case cn:
		case go:
		case lk1:
		case lk2:
		case exa: {
			textr(r, txc, a.name);
			break;
		}
		case c0: {
			textr(r, txc, "清");
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
	tmp.x = openmode;
	drawdom(tmp, 0);
	follow(tmp);

	rep(i, 0, st.H - 1) {
		tmp = id2dom(cardsdomid[i]);
		tmp.name = cn2str(st.hands[i].name);
		tmp.x = st.hands[i].cost;
		drawdom(tmp, 0);
		follow(tmp);
	}
	rep(i, st.H, 9) {
		tmp = id2dom(cardsdomid[i]);
		tmp.name = "清除";
		tmp.x = 0;
		drawdom(tmp, 0);
		follow(tmp);
	}

	rep(i, 0, st.F - 1) {
		tmp = id2dom(minionsdomid[i]);
		tmp.name = mn2str(st.fields[i].name);
		drawdom(tmp, 0);
		follow(tmp);
	}
	rep(i, st.F, 6) {
		tmp = id2dom(minionsdomid[i]);
		tmp.name = "清除";
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
	openmode = id2dom(modedomid).x;

	__tar = id2dom(tardomid).x;
	__tlim = id2dom(tlimdomid).x;

	state st;
	domain tmp;

	st.H = 0;
	rep(i, 0, 9) {
		tmp = id2dom(cardsdomid[i]);
		if (tmp.name != "清除") st.hands[st.H++] = cardcons(str2cn(tmp.name), tmp.x);
	}

	st.F = 0;
	rep(i, 0, 6) {
		tmp = id2dom(minionsdomid[i]);
		if (tmp.name != "清除") st.fields[st.F++] = minioncons(cn2mn(str2cn(tmp.name)));
	}

	rep(i, 0, 3) {
		st.auras[i] = min(id2dom(aurasdomid[i]).x, alim[i]);
		//过大的光环数值允许临时放置在UI上，但是转化为状态时应正常
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
	if (s == "清除") return true;
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
	openmode = 1;

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
	return a;
}

void loadauto() {
	int _tar = 999;
	state st = autoread(id2dom(lkdomid).name, _tar);
	domain tmp;

	st2doms(st);

	tmp = id2dom(tlimdomid);
	tmp.x = 15;
	drawdom(tmp, 0);
	follow(tmp);

	tmp = id2dom(tardomid);
	tmp.x = _tar;
	drawdom(tmp, 0);
	follow(tmp);
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
		case vx: {
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
			}
			break;
		}
		case c0: {
			if (selected.type == vx || selected.type == vnx) {
				inputing = true;
				
				selected.x = 0;
				drawdom(selected, 1);
				follow(selected);
			}
			break;
		}
		case cx: {
			if (selected.type == vx || selected.type == vnx) {
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
		case ans:
		case lk: {

			break;
		}
		case lk1: {
			inputing = false;

			char _lk[105];
			inputbox_getline("请输入炉石传说本地路径（回车确认）", "宇宙甜心", _lk, 100);
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