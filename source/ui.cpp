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
#define addd(a,b,c,d,e,f,g,h) doms.push_back(domaincons(rectcons(a,b,c,d),e,f,g,h));

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
	nodomt, vnx, vx, vn, cn, cx, go, ans, vxa, lk, lk1, lk2, vxb
};
struct domain {
	rect r;
	domt type;
	string name;
	int x;
	int id;
};
domain domaincons(rect a, domt b, string c, int d, int e) {
	domain dom;
	dom.r = a; dom.type = b; dom.name = c; dom.x = d; dom.id = e;
	return dom;
}
domain nodomain = domaincons(norect, nodomt, "", -1, -1);
bool indom(int x, int y, domain a) {
	return inrect(x, y, a.r);
}

color_t bgc = EGERGB(255, 255, 255);
color_t bdc = EGERGB(0, 0, 0);
color_t slc = EGERGB(0, 255, 0);
color_t txc = EGERGB(0, 0, 255);

void init() {
	initgraph(W, H);
	setcaption("暗歌是猪");
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
int manadomid;
int cardsdomid[10];
int minionsdomid[7];
int ansdomid;
int ehdomid;
int tlimdomid;
int lkdomid;
int modedomid;
int numdomid;
int aurasdomid[4];

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

string n1[15] = { "鱼灵","老千","邮箱","刀油","鬼灵","腾武","暗步","背刺","硬币","伺机","幻药","随从","法术","垃圾","清除" };
string a1[4] = { "伺机层数","老千层数","刀一层数","刀二层数" };
string defaultlk = "D:\\Hearthstone";

void getdoms() {
	doms.clear();
	addd(860, 600, 920, 640, vx, "水晶", 0, manadomid = 1);
	//1
	rep(i, 0, 9) addd(200 + i * 60, 600, 260 + i * 60, 640, vnx, "清除", 0, cardsdomid[i] = 2 + i);
	//2 ... 11
	rep(i, 0, 6) addd(200 + i * 60, 560, 260 + i * 60, 600, vn, "清除", 0, minionsdomid[i] = 101 + i);
	//101 ... 107
	rep(i, 0, 10) addd((i + 2) % 3 * 40, 400 + (i + 2) / 3 * 40, 40 + (i + 2) % 3 * 40, 440 + (i + 2) / 3 * 40, cx, "", i, 12 + i);
	//12 ... 22
	rep(i, 0, 14) addd(i % 3 * 40, 160 + i / 3 * 40, 40 + i % 3 * 40, 200 + i / 3 * 40, cn, n1[i], 0, 123 + i);
	//123 ... 137
	addd(1220, 600, 1280, 640, go, "计算", 0, 37);
	//37
	addd(880, 0, 1280, 560, ans, "", 0, ansdomid = 38);
	//38
	addd(980, 600, 1040, 640, vxa, "时限", 15, tlimdomid = 39);
	//39
	addd(1100, 600, 1160, 640, vxa, "目标", 999, ehdomid = 40);
	//40
	addd(0, 0, 400, 40, lk, defaultlk, 0, lkdomid = 41);
	//41
	addd(0, 40, 60, 80, lk1, "修改", 0, 42);
	//42
	addd(60, 40, 120, 80, lk2, "读取", 0, 43);
	//43
	addd(200, 400, 320, 440, vxb, "背刺可用", 1, modedomid = 44);
	//44
	addd(360, 400, 480, 440, vx, "已用牌数", 0, numdomid = 45);
	//45
	rep(i, 0, 3) addd(200 + 160 * i, 480, 320 + 160 * i, 520, vx, a1[i], 0, aurasdomid[i] = 46 + i);
	//46 ... 49
}

kpm str2k(string s) {
	if (s == "暗步") return ayb;
	if (s == "背刺") return bc;
	if (s == "硬币") return jb;
	if (s == "伺机") return sjdf;
	if (s == "幻药") return hjys;
	if (s == "鱼灵") return syzl;
	if (s == "老千") return hrlq;
	if (s == "邮箱") return yxwz;
	if (s == "刀油") return dy;
	if (s == "腾武") return tw;
	if (s == "鬼灵") return glfz;
	if (s == "法术") return ljfs;
	if (s == "随从") return ljsc;
	if (s == "垃圾") return lj;
	return lj;
}

int __eh = 999;
int __tlim = 999999;

state doms2st(vector<domain> a) {
	openmode = id2dom(modedomid).x;

	__eh = id2dom(ehdomid).x;
	__tlim = id2dom(tlimdomid).x;

	state st;
	domain tmp;

	st.H = 0;
	rep(i, 0, 9) {
		tmp = id2dom(cardsdomid[i]);
		if (tmp.name != "清除") st.hands[st.H++] = cardcons(str2k(tmp.name), tmp.x);
	}

	st.F = 0;
	rep(i, 0, 6) {
		tmp = id2dom(minionsdomid[i]);
		if (tmp.name != "清除") st.fields[st.F++] = minioncons(k2s(str2k(tmp.name)));
	}

	rep(i, 0, 3) {
		st.auras[i] = min(id2dom(aurasdomid[i]).x, alim[i]);
		//过大的光环数值允许临时放置在UI上，但是转化为状态时应正常
	}

	st.mana = id2dom(manadomid).x;
	st.num = id2dom(numdomid).x;
	return st;
}

void st2doms(state st) {
	domain tmp;

	rep(i, 0, st.H - 1) {
		tmp = id2dom(cardsdomid[i]);
		tmp.name = k2str(st.hands[i].name);
		tmp.x = st.hands[i].cost;
		follow(tmp);
	}
	rep(i, st.H, 9) {
		tmp = id2dom(cardsdomid[i]);
		tmp.name = "清除";
		tmp.x = 0;
		follow(tmp);
	}

	rep(i, 0, st.F - 1) {
		tmp = id2dom(minionsdomid[i]);
		tmp.name = s2str(st.fields[i].name);
		follow(tmp);
	}
	rep(i, st.F, 6) {
		tmp = id2dom(minionsdomid[i]);
		tmp.name = "清除";
		follow(tmp);
	}

	rep(i, 0, 3) {
		tmp = id2dom(aurasdomid[i]);
		tmp.x = st.auras[i];
		follow(tmp);
	}

	tmp = id2dom(manadomid);
	tmp.x = st.mana;
	follow(tmp);
	tmp = id2dom(numdomid);
	tmp.x = st.num;
	follow(tmp);
}

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
	case vx:
	case vxa:
	case vxb: {
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
	case lk2: {
		textr(r, txc, a.name);
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

void loaddoms() {
	for (auto i : doms) {
		drawdom(i, 0);
	}
	selected = nodomain;
}

bool legalcn4vn(string s) {
	if (s == "清除") return true;
	if (legalk2s(str2k(s))) return true;
	return false;
}

void refreshans(string _s) {
	domain ans = id2dom(ansdomid);
	ans.name = _s;
	drawdom(ans, 0);
	follow(ans);
	refresh;
}

void click(int x, int y) {
	domain toselect = nodomain;
	for (auto i : doms) {
		if (indom(x, y, i)) {
			toselect = i;
			break;
		}
	}
	switch (toselect.type) {
	case nodomt: {

		break;
	}
	case vnx:
	case vn:
	case vx:
	case vxa:
	case vxb: {
		if (selected.id == toselect.id) {
			drawdom(selected, 0);
			selected = nodomain;
		}
		else {
			drawdom(selected, 0);
			drawdom(toselect, 1);
			selected = toselect;
		}
		break;
	}
	case cn: {
		if (selected.type == vnx || (selected.type == vn && legalcn4vn(toselect.name))) {
			//非随从在UI上就不允许被放置在随从位
			selected.name = toselect.name;
			drawdom(selected, 1);
			follow(selected);
		}
		break;
	}
	case cx: {
		if (selected.type == vx || selected.type == vnx) {
			selected.x = toselect.x;
			drawdom(selected, 1);
			follow(selected);
		}
		if (selected.type == vxa) {
			if (toselect.x == 0) selected.x = 0;
			else selected.x = min(selected.x * 10 + (toselect.x % 10), 999);
			drawdom(selected, 1);
			follow(selected);
		}
		if (selected.type == vxb) {
			selected.x = (bool)toselect.x;
			drawdom(selected, 1);
			follow(selected);
		}
		break;
	}
	case go: {
		state st = doms2st(doms);
		domain ans = id2dom(ansdomid);
		ans.name = _solve(st, __eh, __tlim, 0, 0, 0, 1, 1, 0, 0);
		drawdom(ans, 0);
		follow(ans);
		break;
	}
	case ans:
	case lk: {

		break;
	}
	case lk1: {
		char _lk[100];
		inputbox_getline("请输入炉石传说本地路径（回车确认）", "宇宙甜心", _lk, 100);
		domain lk = id2dom(lkdomid);
		lk.name = (string)_lk;
		drawdom(lk, 0);
		follow(lk);
		break;
	}
	case lk2: {
		state st = autoread(id2dom(lkdomid).name);
		st2doms(st);
		rep(i, 0, 9) drawdom(id2dom(cardsdomid[i]), 0);
		drawdom(id2dom(manadomid), 0);
		break;
	}
	}
}

state initstcons() {
	state a;
	a.H = 10;
	a.hands[0] = cardcons(jb, 0);
	a.hands[1] = cardcons(jb, 0);
	a.hands[2] = cardcons(jb, 0);
	a.hands[3] = cardcons(ayb, 0);
	a.hands[4] = cardcons(sjdf, 0);
	a.hands[5] = cardcons(hrlq, 2);
	a.hands[6] = cardcons(dy, 4);
	a.hands[7] = cardcons(tw, 2);
	a.hands[8] = cardcons(glfz, 6);
	a.hands[9] = cardcons(hjys, 4);
	srand(time(0));
	random_shuffle(a.hands, a.hands + 10);
	a.F = 0;
	rep(i, 0, 3) a.auras[i] = 0;
	a.mana = 10;
	a.num = 0;
	return a;
}
state initst = initstcons();

void loadsample() {
	st2doms(initst);
	rep(i, 0, 9) drawdom(id2dom(cardsdomid[i]), 0);
	drawdom(id2dom(manadomid), 0);
	domain a;
	a = id2dom(tlimdomid);
	a.x = 999;
	follow(a);
	drawdom(a, 0);
	a = id2dom(ehdomid);
	a.x = 60;
	follow(a);
	drawdom(a, 0);
}

void ui_main() {
	Load();

	//ShowWindow(GetForegroundWindow(), 0);

	init();
	attention();
	cleardevice();

	getdoms();
	loaddoms();

	loadsample();

	refresh;

	mouse_msg e = { 0 };
	int last = 0;
	while (true) {
		while (mousemsg()) {
			e = getmouse();
		}

		if (!e.is_down()) last = 0;
		else {
			if (last == 0) {
				//避免长点 
				click(e.x, e.y);
				refresh;
			}
			last = 1;
		}
	}

	closegraph();
}