#include "solve.h"
#include "pre.h"
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
		int p = c.find("\n");
		outtextxy(xx, yy, c.substr(0, p).c_str());
		c = c.substr(p + 1, c.size());
		yy += 20;
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
	setb(bgc);
}

rect _all = rectcons(0, 0, 1280, 640);
rect _start = rectcons(1160, 560, 1280, 640);

void drawatt() {
	textr(_all, txc, "�����ʼ���������Ѿ��Ķ���https://github.com/Moiezen/HS_SPR_CAL��README.md�����Ҹ�UI.exe��ֱ�ӻ�ȡ�����°汾");

	barr(_start, bdc);
	barr(cutedge(_start, 1), bgc);
	textr(_start, txc, "��ʼ");
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

string n1[14] = { "����","��ǧ","����","����","����","����","����","Ӳ��","�Ż�","��ҩ","���","����","����","���" };
string a1[4] = { "�Ż�����","��ǧ����","��һ����","��������" };
string defaultlk = "D:\\Hearthstone";

void getdoms() {
	doms.clear();
	addd(860, 600, 920, 640, vx, "ˮ��", 0, manadomid = 1);
	//1
	rep(i, 0, 9) addd(200 + i * 60, 600, 260 + i * 60, 640, vnx, "���", 0, cardsdomid[i] = 2 + i);
	//2 ... 11
	rep(i, 0, 6) addd(200 + i * 60, 560, 260 + i * 60, 600, vn, "���", 0, minionsdomid[i] = 101 + i);
	//101 ... 107
	rep(i, 0, 10) addd((i + 2) % 3 * 40, 400 + (i + 2) / 3 * 40, 40 + (i + 2) % 3 * 40, 440 + (i + 2) / 3 * 40, cx, "", i, 12 + i);
	//12 ... 22
	rep(i, 0, 13) addd(i % 3 * 40, 200 + i / 3 * 40, 40 + i % 3 * 40, 240 + i / 3 * 40, cn, n1[i], 0, 123 + i);
	//123 ... 136
	addd(1220, 600, 1280, 640, go, "����", 0, 37);
	//37
	addd(1000, 0, 1280, 560, ans, "", 0, ansdomid = 38);
	//38
	addd(980, 600, 1040, 640, vxa, "ʱ��", 15, tlimdomid = 39);
	//39
	addd(1100, 600, 1160, 640, vxa, "Ŀ��", 999, ehdomid = 40);
	//40
	addd(0, 0, 400, 40, lk, defaultlk, 0, lkdomid = 41);
	//41
	addd(0, 40, 60, 80, lk1, "�޸�", 0, 42);
	//42
	addd(60, 40, 120, 80, lk2, "��ȡ", 0, 43);
	//43
	addd(200, 400, 320, 440, vxb, "���̿���", 1, modedomid = 44);
	//44
	addd(360, 400, 480, 440, vx, "��������", 0, numdomid = 45);
	//45
	rep(i, 0, 3) addd(200 + 160 * i, 480, 320 + 160 * i, 520, vx, a1[i], 0, aurasdomid[i] = 46 + i);
	//46 ... 49
}

kpm str2k(string s) {
	if (s == "����") return ayb;
	if (s == "����") return bc;
	if (s == "Ӳ��") return jb;
	if (s == "�Ż�") return sjdf;
	if (s == "��ҩ") return hjys;
	if (s == "����") return syzl;
	if (s == "��ǧ") return hrlq;
	if (s == "����") return dy;
	if (s == "����") return tw;
	if (s == "����") return glfz;
	if (s == "����") return ljfs;
	if (s == "���") return ljsc;
	if (s == "����") return lj;
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
		if (tmp.name != "���") st.hands[st.H++] = cardcons(str2k(tmp.name), tmp.x);
	}

	st.F = 0;
	rep(i, 0, 6) {
		tmp = id2dom(minionsdomid[i]);
		if (tmp.name != "���") st.fields[st.F++] = minioncons(k2s(str2k(tmp.name)));
	}

	rep(i, 0, 3) {
		st.auras[i] = min(id2dom(aurasdomid[i]).x, alim[i]);
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
		tmp.name = "���";
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
		tmp.name = "���";
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
		if (a.name == "���") textr(r, txc, "");
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
		if (a.name == "���") textr(r, txc, "");
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
	setcaption("��������");
	for (auto i : doms) {
		drawdom(i, 0);
	}
	selected = nodomain;
}

bool legalcn4vn(string s) {
	if (s == "���") return true;
	if (legalk2s(str2k(s))) return true;
	return false;
}

state autoread(string s);

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
			else selected.x = min(selected.x * 10 + toselect.x, 999);
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
		inputbox_getline("������¯ʯ��˵����·�����س�ȷ�ϣ�", "��������", _lk, 100);
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

void ui_main() {
	Load();

	//ShowWindow(GetForegroundWindow(), 0);

	init();
	attention();
	cleardevice();

	getdoms();
	loaddoms();
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
				//���ⳤ�� 
				click(e.x, e.y);
				refresh;
			}
			last = 1;
		}
	}

	closegraph();
}