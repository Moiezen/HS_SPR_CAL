#include "gen.h"

int getrand(int count, ...) {
	va_list v;
	int valuet;
	vector<int> value;
	int sum = 0;

	va_start(v, count);

	while (count--) {
		valuet = va_arg(v, int);
		value.push_back(valuet);
		sum += valuet;
	}

	va_end(v);

	int r = rand() % sum;
	int n = 0;
	for (auto i : value) {
		r -= i;
		if (r < 0) return n;
		n++;
	}
	assert(0);
	return 0;
}

card ctmp[99];
int cT;
void madd(int n, card c) {
	while (n--) ctmp[cT++] = c;
}

state gen() {
	state st;

	cT = 0;
	madd(getrand(2, 1, 5), cardcons(syzl, 4));
	madd(getrand(3, 7, 2, 1), cardcons(hrlq, 2));
	madd(getrand(3, 3, 1, 0), cardcons(yxwz, 2));
	madd(getrand(2, 1, 5), cardcons(dy, 4));
	madd(getrand(3, 0, 1, 1), cardcons(glfz, 6));
	madd(getrand(2, 1, 3), cardcons(tw, 2));
	madd(getrand(3, 1, 4, 3), cardcons(ayb, 0));
	madd(getrand(3, 4, 5, 1), cardcons(hjys, 4));
	madd(getrand(3, 3, 2, 1), cardcons(jb, 0));
	madd(getrand(3, 3, 4, 1), cardcons(bc, 0));
	madd(getrand(3, 3, 2, 1), cardcons(sjdf, 0));
	madd(getrand(2, 1, 1), cardcons(ljfs, 1));

	random_shuffle(ctmp, ctmp + cT);
	st.H = min(cT, hlim);
	rep(i, 0, st.H - 1) {
		st.hands[i] = ctmp[i];
	}

	st.F = 0;
	rep(i, 0, 3) st.auras[i] = 0;
	st.mana = getrand(10, 0, 0, 0, 0, 1, 2, 4, 4, 2, 1);
	st.num = 0;
	return st;
}