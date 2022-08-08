#include "basic.h"

string s2str(scm a) {
	switch (a) {
		case msyzl: {
			return "����";
			break;
		}
		case mhrlq: {
			return "��ǧ";
			break;
		}
		case mdy: {
			return "����";
			break;
		}
		case mtw: {
			return "����";
			break;
		}
		case mglfz: {
			return "����";
			break;
		}
		case mljsc: {
			return "����";
			break;
		}
		case dfyx: {
			return "����";
			break;
		}
		case dfsc: {
			assert(0);
			break;
		}
		case nul: {
			return "";
			break;
		}
		default: {
			assert(0);
			break;
		}
	}
}
string k2str(kpm a) {
	switch (a) {
		case syzl: {
			return "����";
			break;
		}
		case hrlq: {
			return "��ǧ";
			break;
		}
		case dy: {
			return "����";
			break;
		}
		case tw: {
			return "����";
			break;
		}
		case glfz: {
			return "����";
			break;
		}
		case ljsc: {
			return "���";
			break;
		}
		case ayb: {
			return "����";
			break;
		}
		case bc: {
			return "����";
			break;
		}
		case jb: {
			return "Ӳ��";
			break;
		}
		case sjdf: {
			return "�Ż�";
			break;
		}
		case hjys: {
			return "��ҩ";
			break;
		}
		case ljfs: {
			return "����";
			break;
		}
		case lj: {
			return "����";
			break;
		}
		default: {
			assert(0);
			break;
		}
	}
}
kpm s2k(scm a) {
	switch (a) {
		case msyzl: {
			return syzl;
			break;
		}
		case mhrlq: {
			return hrlq;
			break;
		}
		case mdy: {
			return dy;
			break;
		}
		case mtw: {
			return tw;
			break;
		}
		case mglfz: {
			return glfz;
			break;
		}
		case mljsc: {
			return ljsc;
			break;
		}
		default: {
			assert(0);
			break;
		}
	}
}
scm k2s(kpm a) {
	switch (a) {
		case syzl: {
			return msyzl;
			break;
		}
		case hrlq: {
			return mhrlq;
			break;
		}
		case dy: {
			return mdy;
			break;
		}
		case tw: {
			return mtw;
			break;
		}
		case glfz: {
			return mglfz;
			break;
		}
		case ljsc: {
			return mljsc;
			break;
		}
		default: {
			assert(0);
			break;
		}
	}
}
bool legalk2s(kpm a) {
	switch (a) {
		case syzl:
		case hrlq:
		case dy:
		case tw:
		case glfz:
		case ljsc: {
			return true;
			break;
		}
		default: {
			return false;
			break;
		}
	}
}
int bcost(scm a) {
	switch (a) {
		case msyzl: {
			return 4;
			break;
		}
		case mhrlq: {
			return 2;
			break;
		}
		case mdy: {
			return 4;
			break;
		}
		case mtw: {
			return 2;
			break;
		}
		case mglfz: {
			return 6;
			break;
		}
		case mljsc: {
			return 20;
			break;
		}
		case dfyx: {
			assert(0);
			break;
		}
		case dfsc: {
			assert(0);
			break;
		}
		default: {
			assert(0);
			break;
		}
	}
}

card cardcons(kpm a, int b) {
	card c;
	c.name = a;
	c.cost = b;
	return c;
}
minion minioncons(scm a) {
	minion b;
	b.name = a;
	return b;
}
state emptystcons() {
	state a;
	a.H = 0;
	a.F = 0;
	rep(i, 0, 3) a.auras[i] = 0;
	a.mana = 0;
	a.num = 0;
	return a;
}
state emptyst = emptystcons();
ope opecons(int a, kpm b, scm c) {
	ope d;
	d.cost = a;
	d.name = b;
	d.target = c;
	return d;
}

opes emptyoscons() {
	opes a;
	a.os.clear();
	return a;
}
opes emptyos = emptyoscons();

int openmode;

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