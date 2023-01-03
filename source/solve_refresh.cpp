#include "offer.h"
#include "trans.h"
#include "output.h"
#include "formula.h"
#include "solve.h"
#include "ui.h"

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

double optf(double x, double y) {
	return log(x / y);
}

ll tlim, tbegin;
int tar;
int collect, addquiz, print;
int exbound, optimize, pureformula;
double bound;
int bounded;
int test;

int done, curdmg;
opes curos;
int testcnt;

int tick;

ull statehb = 77232917;
ull p1 = 1000000123;
ull p2 = 1000000181;
ull statehash(state a, int b) {
	ull d1 = 1;
	bool ifdemise = false;
	rep(i, 0, a.H - 1) {
		d1 = d1 * (a.hands[i].name * 100 + a.hands[i].cost + p1);
		ifdemise = ifdemise || (a.hands[i].name == demise);
	}
	ull d2 = 1;
	rep(i, 0, a.F - 1) d2 = d2 * (a.fields[i].name + p2);
	//暂时当作无序
	//事实上在offer.cpp中已经一定程度上当作无序处理

	ull h = d1 * statehb + d2;
	rep(i, 0, 3) h = h * statehb + a.auras[i];
	h = h * statehb + a.num;
	h = h * statehb + a.mana;
	h = h * statehb + a.drawmn;
	h = h * statehb + a.hatk;

	if (ifdemise) {
		h = h * statehb + a.todemise;
	}
	else {
		h = h * statehb;
	}
	//手牌中还有殒命暗影存在时，要将.todemise加入哈希，否则补位

	if (iceblockif == 1) {
		h = h * statehb + b;
	}
	else {
		h = h * statehb;
	}
	//破冰需求下，因为不对当前伤害做偏序优化，所以要当前伤害也加入哈希，否则补位

	return h;
}
int hashon = 1;

map<ull, int> st2hidmg;
int st2hidmgcountlim = (1 << 21);
int st2hidmgcount = 0;

map<ull, int> st2hinum;

int allcount = 0;

int accum(int x, int y) {
	int t = 1;
	if (y < 0) {
		y = -y;
		t = 2;
	}

	if (iceblockif == 0) {
		return x + t * y;
	}

	while (t--) {
		if (x >= _tar_ice2) {
			x = x;
		}
		else if (x + y < tar) {
			x = x + y;
		}
		else if (x + y >= tar) {
			x = _tar_ice1 - (tar - x);
		}
		else {
			assert(0);
		}
	}
	return x;
}

void solve(syn q) {
	if (hashon) {
		allcount++;

		ull hq = statehash(q.pa.first, q.pa.second);
		if (q.pa.second <= st2hidmg[hq] - 1) {
			return;
		}
		else {
			if (st2hidmg[hq] == 0) {
				if (st2hidmgcount < st2hidmgcountlim) {
					st2hidmgcount++;
					st2hidmg[hq] = q.pa.second + 1;
				}
			}
			else {
				st2hidmg[hq] = q.pa.second + 1;
			}
		}
	}

	if (q.pa.second >= curdmg) {
		if (collect == 1 && q.pa.second >= dmgbd) {
			if (q.pa.second > curdmg) cls.clear();
			cls.push_back(q.os);
		}
		if (q.pa.second > curdmg) {
			curos = q.os;
			curdmg = q.pa.second;
			if (curdmg >= dmgbd) {
				refreshans(output(curos, curdmg, -1, time(0) - tbegin));
			}
		}
	}
	if (iceblockif == 0 && q.pa.second >= tar) {
		done = 1;
		return;
	}
	if (iceblockif == 1 && q.pa.second == _tar_ice1 - 1) {
		done = 1;
		return;
		//1血破冰已是最优，相当于达标
	}
	if ((tick++ & 8) == 0 && time(0) >= tbegin + tlim) {
		done = 2;
		return;
	}
	if (exbound == 1 && q.pri < bound) {
		bounded = 1;
		return;
	}
	if (q.pa.second >= _tar_ice2) {
		return;
		//已经打出破冰则也已不必继续操作
	}

	if (optimize == 1) {
		isn = 0;
		for (auto i : q.os.os) {
			iseq[isn++] = o2i(i);
		}
	}

	oxys o0 = offer(q.pa.first);

	vector<double> sums;
	double sum, allsum, lost;

	if (optimize == 1) {
		sums.clear();
		allsum = 0;

		for (auto i : o0.os) {
			iseq[isn++] = o2i(exact4f(q.pa.first, i));

			sum = sumbasic;
			rep(i, (isn - 1) - flimr + 1, (isn - 1) - fliml + 1) {
				sum += value[ishash(i, isn - 1, iseq)];
			}
			sums.push_back(sum);
			allsum += sum;
			isn--;
		}
	}

	int j = 0;
	int alreadyvalids = 0;
	for (auto i : o0.os) {
		opes os = q.os;
		os.os.push_back(exact(q.pa.first, i));

		if (optimize == 1) {
			sum = sums[j++];
			lost = optf(sum, allsum);
		}
		else {
			lost = -1.;
		}

		if (optimize == 1 && pureformula == 1 && sum - sumbasic < 1e-6) {
			//cerr<<sums[j-1]<<" "<<allsum<<endl;
			//cerr<<lost<<endl;
		}
		else {
			pair<state, int> p = trans(q.pa.first, i);
			if (test == 1) {
				testcnt++;
			}
			if (p.second == badpair_min) {
				continue;
			}
			//if (iceblockif == 0 && i.x == -1 && alreadyvalids > 0) {
				//continue;
				//如果不需要破冰，那么英雄攻击一定可以留到最后进行
				//因此，只要可以进行任何其他选择(alreadyvalids > 0)，就可以暂时忽视英雄攻击这一选择（i.x == -1）
				//这一优化应当归为offer，但在offer中不容易实现，因此在此处实现
			//}

			alreadyvalids++;
			solve(syncons(make_pair(p.first, accum(q.pa.second, p.second)), q.pri + lost, os));
			if (done > 0) return;
		}

	}
}

string _solve(state st, int _tar, int _tlim, int _collect, int _addquiz, int _print, int _exbound, int _optimize, int _pureformula, int _test) {
	if (_tar < _tar_max && _collect == 1) assert(0);
	//同时开启需求截断和收集会污染数据 

	tar = _tar;
	done = curdmg = 0;
	curos = emptyopes;

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

	tick = 0;

	st2hidmg.clear();
	st2hidmgcount = 0;
	allcount = 0;

	if (exbound == 0) {
		bound = 1e9;
		solve(syncons(make_pair(st, 0), 0, emptyopes));
	}
	if (exbound == 1) {
		bound = -boundbasic;
		bounded = 0;
		solve(syncons(make_pair(st, 0), 0, emptyopes));

		while (done == 0 && bounded == 1) {
			st2hidmg.clear();
			st2hidmgcount = 0;
			allcount = 0;

			bound -= boundbasic;
			bounded = 0;

			solve(syncons(make_pair(st, 0), 0, emptyopes));
		}
	}

	st2hidmg.clear();

	if (collect == 1 && done == 0) {
		if (curdmg >= dmgbd) {
			allcls.insert(allcls.end(), cls.begin(), cls.end());
		}
	}
	if (addquiz == 1 && done == 0) {
		if (curdmg >= dmgbd) {
			quiz q = emptyqcons();
			q.qnd = curdmg;
			q.qst = st;
			quizs.push_back(q);
		}
	}

	return output(curos, curdmg, done, time(0) - tbegin);
}