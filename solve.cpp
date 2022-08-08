#include "offer.h"
#include "trans.h"
#include "output.h"
#include "formula.h"
#include "solve.h"

syn syncons(pair<state, int> a, double b, opes c) {
	syn d;
	d.pa = a;
	d.pri = b;
	d.os = c;
	return d;
}
bool operator<(syn a, syn b) {
	return a.pri < b.pri;
}

int need, tlim, tbegin;
int collect, addquiz, print;
int exbound, optimize, pureformula;
double bound;
int test;

int done, curdmg;
opes curos;
int testcnt;

double optf(double x, double y) {
	return log(x / y);
}

void solve(syn q) {
	if (q.pa.second >= curdmg) {
		if (collect == 1 && q.pa.second >= clsbd) {
			if (q.pa.second > curdmg) cls.clear();
			cls.push_back(q.os);
		}
		curos = q.os;
		curdmg = q.pa.second;
	}
	if (q.pa.second >= need) {
		done = 1;
		return;
	}
	if (time(0) > tbegin + tlim) {
		done = 2;
		return;
	}
	if (exbound == 1 && q.pri < bound) {
		return;
	}

	if (optimize == 1) {
		isn = 0;
		for (auto i : q.os.os) {
			iseq[isn++] = o2i(i);
		}
	}

	opes of = offer(q.pa.first);

	vector<double> sums;
	double sum, allsum, lost;

	if (optimize == 1) {
		sums.clear();
		allsum = 0;

		for (auto i : of.os) {
			iseq[isn++] = o2i(i);

			sum = sumbasic;
			rep(i, (isn - 1) - flim + 1, isn - 1) {
				sum += value[ishash(i, isn - 1, iseq)];
			}
			sums.push_back(sum);
			allsum += sum;
			isn--;
		}
	}

	int j = 0;
	for (auto i : of.os) {
		opes os = q.os;
		os.os.push_back(i);

		if (optimize == 1) {
			lost = optf(sums[j++], allsum);
		}
		if (optimize == 0) {
			lost = -1.;
		}

		if (pureformula == 1 && sums[j - 1] - sumbasic < 1e-6) {
			//cerr<<sums[j-1]<<" "<<allsum<<endl;
			//cerr<<lost<<endl;
		}
		else {
			pair<state, int> p = trans(q.pa.first, i); if (test == 1) testcnt++;
			solve(syncons(make_pair(p.first, q.pa.second + p.second), q.pri + lost, os));
			if (done > 0) return;

		}

	}
}

string _solve(state st, int _need, int _tlim, int _collect, int _addquiz, int _print, int _exbound, int _optimize, int _pureformula, int _test) {
	if (_need < _need_max && _collect == 1) assert(0);
	//同时开启需求截断和收集会污染数据 

	need = _need;
	done = curdmg = 0;
	curos = emptyos;

	tlim = _tlim;
	tbegin = time(0);

	collect = _collect;
	addquiz = _addquiz;
	print = _print;

	exbound = _exbound;
	optimize = _optimize;
	pureformula = _pureformula;
	test = _test;
	//复制参数 

	if (collect == 1) cls.clear();
	if (test == 1) testcnt = 0;

	if (exbound == 0) {
		bound = 1e9;
		solve(syncons(make_pair(st, 0), 0, emptyos));
	}
	if (exbound == 1) {
		bound = -boundbasic;
		solve(syncons(make_pair(st, 0), 0, emptyos));
		while (done == 0) {
			bound -= boundbasic;
			solve(syncons(make_pair(st, 0), 0, emptyos));
		}
	}

	//if(print==1) show(curos,curdmg);
	if (collect == 1 && done == 0) {
		if (curdmg >= clsbd) {
			allcls.insert(allcls.end(), cls.begin(), cls.end());
		}
	}
	if (addquiz == 1 && done == 0) {
		if (curdmg >= clsbd) {
			quiz q = emptyqcons();
			q.qnd = curdmg;
			q.qst = st;
			quizs.push_back(q);
		}
	}

	return output(curos, curdmg, done);
}