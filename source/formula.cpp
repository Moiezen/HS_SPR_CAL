#include "formula.h"

int o2i(ope a) {
	return a.cost + a.name * 100 + a.target * 10000 + 93589;
}

ull ishash(int l, int r, int* s) {
	ull t = 0;
	rep(i, l, r) {
		if (i < 0) t = t * 19260817 + 910570131 / (-i);
		else t = t * 19260817 + s[i];
	}
	return t;
}
map<ull, double> value;