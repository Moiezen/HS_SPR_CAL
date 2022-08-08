#pragma once

#include <bits/stdc++.h>
#define rep(i,l,r) for(int i=l;i<=r;i++)
using namespace std;
enum kpm {
	ayb, bc, jb, sjdf, hjys, syzl, hrlq, dy, tw, glfz, ljsc, ljfs, lj
};
enum scm {
	msyzl, mhrlq, mdy, mtw, mglfz, mljsc, dfyx, dfsc, nul
	//�з�Ӣ��-�����ǹ��������Ŀ��
	//�з����-�����Ǳ��̵�Ŀ��
	//��Ŀ��
	//������Ŀ�������������Լ򻯲���Ŀ��
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
	//�Ѽ��� ����ֻ����ȥ����ǧ������ �������������ȥ�� �����ȥhealth 
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
	//���������ʱ������Ѫ������˲���Ŀ�����Ҫ����������ѿ��԰����з�Ӣ�ۣ��з���ӣ���Ŀ�꣩ 
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
extern vector<quiz> quizs;

const int clsbd = 10;
extern vector<opes> cls;
extern vector<opes> allcls;