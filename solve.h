#pragma once

#include "basic.h"

struct syn {
	pair<state, int> pa;
	//��ǰ״̬���ۼ��˺� 
	double pri;
	//���ȼ� 
	opes os;
	//�������� 
};
syn syncons(pair<state, int> a, double b, opes c);
bool operator<(syn a, syn b);

const double sumbasic = 1.;
const double boundbasic = 10.;
const int _need_max = 999;

extern int done, curdmg;
extern opes curos;
extern int testcnt;

string _solve(state st, int _need, int _tlim, int _collect, int _addquiz, int _print, int _exbound, int _optimize, int _pureformula, int _test);