#include "offer.h"

bool notcoinopt4demise(state a) {
	//殒命暗影对于硬币优先的附加逻辑：
	//如果有殒命暗影，且殒命暗影当前复制的不是any/coin，则硬币优先不直接成立
	//这是为了保护殒命暗影当前复制的法术，在此保护情形下，其他常规法术也不应当被打出
	//在此保护以外的情形，（该计算器）保持硬币优先，因为这一定不妨碍其复制其他之后打出的法术（反而对顺利复制有帮助）
	//也就是说，要么硬币优先，要么保护情形
	//注意：在极端情形下，这仍然是有漏洞的！这有可能妨碍了殒命暗影复制硬币
	//抛开费用限制不谈，如果殒命暗影需要复制硬币，总是可以随着硬币一起打出的，并不妨碍
	//但是：例如在费用为9的情况下，手牌中有殒命暗影，硬币，帷幕。有可能需要先打帷幕，再打硬币，然后让殒命暗影复制硬币
	//如果先打硬币，此时已经费用为10，殒命暗影可能难以合适地复制到硬币
	//这个漏洞可能在之后会被防止
	if (a.todemise == anyspell || a.todemise==anycombospell || a.todemise == fakecoin) {
		return false;
	}
	rep(i, 0, a.H - 1) {
		if (a.hands[i].name == demise) {
			return true;
		}
	}
	return false;
}

bool coinopt(state a, oxy& b) {
	//硬币优先逻辑：有0费硬币，不受加减费光环影响，当前费用小于上限，不需要破冰
	if (iceblockif == 1) return false;
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

	bool protectdemise = false;
	if (coinopt(a, o)) {
		os.os.push_back(o);
		if (notcoinopt4demise(a)) {
			protectdemise = true;
		}
		else {
			return os;
		}
	}

	if (a.hatk > 0) {
		os.os.push_back(oxycons(-1, -2));
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

		if (na == demise) {
			na = a.todemise;
		}

		if (protectdemise) {
			if (normalspell(na) && na != a.todemise) {
				//被保护情形下，不同于当前复制的法术不应当被打出
				//当前复制的法术已经确定不是any/coin，所以any/coin不需要额外排除
				continue;
			}
		}

		if (na == shadowstep || na == backstab || na == extortion || na == bonespike 
			|| na == redsmoke || na == shadowcaster || na == zolag || na == spectralpillager) {
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
		if (na == backstab || na == extortion || na == bonespike
			|| na == fakecoin || na == preparation || na == illusionpotion || na == shroud || na == swindle || na == madnessplague
			|| na == redsmoke || na == shadowcaster || na == zolag
			|| na == mailboxdancer || na == foxyfraud || na == cutterbutter || na == elvensinger || na == sharkspirit || na == illucia || na == brann
			|| na == anyminion || na == anyspell || na == anyweapon || na == anycombospell) {
			os.os.push_back(oxycons(i, -1));
		}
	}

	return os;
}