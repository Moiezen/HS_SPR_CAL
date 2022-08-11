#pragma once

#include <bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
enum kpm {
	ayb, bc, jb, sjdf, hjys, syzl, hrlq, yxwz, dy, tw, glfz, ljsc, ljfs, lj
};
enum scm {
	msyzl, mhrlq, myxwz, mdy, mtw, mglfz, mljsc, dfyx, dfsc, nul
	//敌方英雄-可以是鬼灵匪贼的目标
	//敌方随从-可以是背刺的目标
	//空目标
	//以上虚目标均归入随从名以简化操作目标
};
string s2str(scm a);
string k2str(kpm a);
kpm s2k(scm a);
scm k2s(kpm a);
bool legalk2s(kpm a);
int bcost(scm a);

struct card {
	kpm name;
	int cost;
	//int health;
};
card cardcons(kpm a, int b);

struct minion {
	scm name;
	//int health;
	//已假设 背刺只用于去除老千和腾武 而鬼灵匪贼总能去除 因此略去health 
};
minion minioncons(scm a);

struct state {
	card hands[10]; int H;
	minion fields[7]; int F;
	int auras[4];
	int mana;
	int num;
};
state emptystcons();
extern state emptyst;

const int hlim = 10;
const int mlim = 7;
const int manalim = 10;
const int alim[4] = { 1,3,2,2 };

struct ope {
	int cost;
	kpm name;
	scm target;
	//由于随从暂时不区分血量，因此操作目标仅需要随从名（且已可以包括敌方英雄，敌方随从，空目标） 
};
ope opecons(int a, kpm b, scm c);

struct opes {
	vector<ope> os;
	~opes() {
		os.clear();
	}
};
opes emptyoscons();
extern opes emptyos;

extern int openmode;

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