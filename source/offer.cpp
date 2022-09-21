#include "offer.h"

bool coinopt(state a, oxy& b) {
	if (a.mana < manalim && a.auras[2] == 0 && a.auras[3] == 0 && a.auras[0] == 0 && spelldebuff == 0) {
		rep(i, 0, a.H - 1) {
			if (a.hands[i].name == fakecoin && a.hands[i].cost == 0) {
				b.x = i;
				b.y = -1;
				return true;
			}
		}
		return false;
	}
	return false;
}

oxys offer(state a) {
	oxys os = emptyoxyscons();
	oxy o;

	if (coinopt(a, o)) {
		os.os.push_back(o);
		return os;
	}

	rep(i, 0, a.H - 1) {
		int co = a.hands[i].cost;
		cardname na = a.hands[i].name;
		bool dup = false;
		rep(j, 0, i - 1) {
			if (a.hands[j].cost == co && a.hands[j].name == na && a.hands[j].health == a.hands[i].health) {
				dup = true;
				break;
			}
		}
		if (dup) continue;

		if (na == shadowstep || na == backstab || na == redsmoke || na == spectralpillager || na == bonespike) {
			rep(j, 0, a.F - 1) {
				bool dup2 = false;
				rep(k, 0, j - 1) {
					if (a.fields[k].name == a.fields[j].name && a.fields[k].health == a.fields[j].health && a.fields[k].curhealth == a.fields[j].curhealth) {
						dup2 = true;
						break;
					}
				}
				if (dup2) continue;
				os.os.push_back(oxycons(i, j));
			}
		}
		if (na == spectralpillager) {
			os.os.push_back(oxycons(i, -2));
		}
		if (na == backstab || na == fakecoin || na == preparation || na == illusionpotion
		 || na == mailboxdancer || na == foxyfraud || na == cutterbutter || na == redsmoke
		 || na == sharkspirit || na == anyminion || na == anyspell || na == anyweapon || na == anycombospell || na == bonespike) {
			os.os.push_back(oxycons(i, -1));
		}
		//not include enemyminion yet
	}
	return os;
}