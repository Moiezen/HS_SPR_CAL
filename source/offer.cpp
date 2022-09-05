#include "offer.h"

bool coinopt(state a) {
	if (a.mana < manalim && a.auras[2] == 0 && a.auras[3] == 0 && a.auras[0] == 0) {
		rep(i, 0, a.H - 1) {
			if (a.hands[i].name == fakecoin && a.hands[i].cost == 0) return true;
		}
		return false;
	}
	return false;
}

opes offer(state a) {
	opes os;
	os.os.clear();

	if (coinopt(a)) {
		os.os.push_back(opecons(0, fakecoin, nul));
		return os;
	}

	rep(i, 0, a.H - 1) {
		int co = a.hands[i].cost;
		cardname na = a.hands[i].name;
		bool dup = false;
		rep(j, 0, i - 1) {
			if (a.hands[j].cost == co && a.hands[j].name == na) {
				dup = true;
				break;
			}
		}
		if (dup) continue;

		if (na == shadowstep || na == backstab || na == redsmoke || na == spectralpillager) {
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
		if (na == spectralpillager) {
			os.os.push_back(opecons(co, na, enemyhero));
		}
		if (na == backstab || na == fakecoin || na == preparation || na == illusionpotion || na == mailboxdancer || na == foxyfraud || na == cutterbutter || na == redsmoke || na == sharkspirit || na == anyminion || na == anyspell) {
			os.os.push_back(opecons(co, na, nul));
		}
		//以上提过，暂不考虑dfsc 
	}
	return os;
}