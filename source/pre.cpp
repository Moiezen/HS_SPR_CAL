#include "formula.h"
#include "solve.h"
#include "gen.h"

void Coll() {
	srand(1);

	allcls.clear();

	int N = 5000, T = 0, S = 0;
	rep(i, 1, N) {
		state st = gen(i);
		_solve(st, _tar_max, 15, 1, 0, 0, 0, 0, 0, 1);
		if (done == 0) S++; T++;
		cerr << "now " << S << " of " << T << endl;
	}

	value.clear();

	for (auto i : allcls) {
		vector<ope> a = i.os;

		isn = 0;
		for (auto j : a) {
			iseq[isn++] = o2i(j);
		}

		rep(i, 0, isn - 1) rep(j, i - flimr + 1, i - 1) {
			value[ishash(j, i, iseq)] += exp(rho * (i - j));
		}
	}

	FILE* f = freopen("fml.txt", "w", stdout);

	ull p, r;
	double q;
	for (auto i : value) {
		p = i.first; q = i.second;
		r = *(ull*)(&q);
		printf("%llu %llu\n", p, r);
	}

	fclose(stdout);
}

void quizwrite(quiz q) {
	printf("%d\n", q.qnd);

	printf("%d\n", (int)q.qst.H);
	rep(i, 0, q.qst.H - 1) {
		printf("%d %d\n", q.qst.hands[i].name, q.qst.hands[i].cost);
	}
	printf("%d\n", (int)q.qst.F);
	rep(i, 0, q.qst.F - 1) {
		printf("%d\n", q.qst.fields[i].name);
	}
	rep(i, 0, 3) {
		printf(i < 3 ? "%d " : "%d\n", q.qst.auras[i]);
	}
	printf("%d %d\n", q.qst.mana, q.qst.num);
}

void Genq() {
	srand(2);

	quizs.clear();

	int N = 1000, T = 0, S = 0;
	rep(i, 1, N) {
		state st = gen(i);
		_solve(st, _tar_max, 15, 0, 1, 0, 0, 0, 0, 1);
		if (done == 0) S++; T++;
		cerr << "now " << S << " of " << T << endl;
	}

	FILE* f = freopen("qiz.txt", "w", stdout);

	for (auto i : quizs) {
		quizwrite(i);
	}

	fclose(stdout);
}

void Load() {
	FILE* f = freopen("fml.txt", "r", stdin);

	value.clear();

	ull p, r;
	double q;
	while (scanf("%llu%llu", &p, &r) == 2) {
		q = *(double*)(&r);
		value[p] = q;
	}

	fclose(stdin);
}

quiz quizread() {
	quiz q = emptyqcons();
	int sc = scanf("%d", &q.qnd);
	if (sc != 1) {
		q.qnd = -1;
		return q;
	}

	int n, s, a;
	sc = scanf("%d", &n);
	q.qst.H = 0;
	while (n--) {
		sc = scanf("%d %d", &s, &a);
		q.qst.hands[q.qst.H++] = cardcons((cardname)s, a);
	}
	sc = scanf("%d", &n);
	q.qst.F = 0;
	while (n--) {
		sc = scanf("%d%d", &s, &a);
		q.qst.fields[q.qst.F++] = minioncons((minionname)s);
	}
	rep(i, 0, 3) {
		sc = scanf("%d", &q.qst.auras[i]);
	}
	sc = scanf("%d%d", &q.qst.mana, &q.qst.num);
	return q;
}

void Getq() {
	FILE* f = freopen("qiz.txt", "r", stdin);

	quizs.clear();
	while (1) {
		quiz q = quizread();
		if (q.qnd == -1) break;
		//if(quizs.size()>=1) break;
		quizs.push_back(q);
	}

	fclose(stdin);
}

void Test(int term) {
	//term:
	//1 - nothing
	//2 - only exbound
	//3 - optimize with exbound
	//4 - optimize with pureformula
	//5 - optimize with exbound and pureformula
	int alltestcnt = 0;
	int solvecnt = 0;
	for (auto q : quizs) {
		switch (term) {
		case 1: {
			_solve(q.qst, q.qnd, 15, 0, 0, 0, 0, 0, 0, 1);
			break;
		}
		case 2: {
			_solve(q.qst, q.qnd, 15, 0, 0, 0, 1, 0, 0, 1);
			break;
		}
		case 3: {
			_solve(q.qst, q.qnd, 15, 0, 0, 0, 1, 1, 0, 1);
			break;
		}
		case 4: {
			_solve(q.qst, q.qnd, 15, 0, 0, 0, 0, 1, 1, 1);
			break;
		}
		case 5: {
			_solve(q.qst, q.qnd, 15, 0, 0, 0, 1, 1, 1, 1);
			break;
		}
		}
		alltestcnt += testcnt;
		solvecnt += (done == 1);
	}
	cerr << ";;;" << solvecnt << ";;;" << alltestcnt << endl;
}

void pre_main() {
	Coll();
	Genq();

	//Load(); cerr << "load complete" << endl;
	//Getq(); cerr << "getq complete" << endl;
}	