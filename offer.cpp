#include "offer.h"

bool coinopt(state a) {
	if (a.mana < manalim && a.auras[2] == 0 && a.auras[3] == 0 && a.auras[0] == 0) {
		rep(i, 0, a.H - 1) {
			if (a.hands[i].name == jb && a.hands[i].cost == 0) return true;
		}
		return false;
	}
	return false;
}

opes offer(state a) {
	opes os;
	os.os.clear();

	if (coinopt(a)) {
		os.os.push_back(opecons(0, jb, nul));
		return os;
	}

	rep(i, 0, a.H - 1) {
		int co = a.hands[i].cost;
		kpm na = a.hands[i].name;
		bool dup = false;
		rep(j, 0, i - 1) {
			if (a.hands[j].cost == co && a.hands[j].name == na) {
				dup = true;
				break;
			}
		}
		if (dup) continue;

		if (na == ayb || na == bc || na == tw || na == glfz) {
			rep(j, 0, a.F - 1) {
				bool dup2 = false;
				rep(k, 0, j - 1) {
					if (a.fields[j].name == a.fields[k].name) {
						dup2 = true;
						break;
					}
				}
				if (dup2) continue;
				os.os.push_back(opecons(co, na, a.fields[j].name));
			}
		}
		if (na == glfz) {
			os.os.push_back(opecons(co, na, dfyx));
		}
		if (na == bc || na == jb || na == sjdf || na == hjys || na == hrlq || na == dy || na == tw || na == syzl || na == ljsc || na == ljfs) {
			os.os.push_back(opecons(co, na, nul));
		}
		//以上提过，暂不考虑dfsc 
	}
	return os;
}