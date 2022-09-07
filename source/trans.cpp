#include "trans.h"

bool rmv1(minion* a, int& n, minionname b) {
	rep(i, 0, n - 1) {
		if (a[i].name == b) {
			rep(j, i + 1, n - 1) a[j - 1] = a[j];
			n--;
			return true;
		}
	}
	return false;
}
bool rmv2(card* a, int& n, cardname b, int c) {
	rep(i, 0, n - 1) {
		if (a[i].name == b && a[i].cost == c) {
			rep(j, i + 1, n - 1) a[j - 1] = a[j];
			n--;
			return true;
		}
	}
	return false;
}

pair<state, int> badpair = make_pair(emptyst, -999999);

int twice(state st) {
	rep(i, 0, st.F - 1)
		if (st.fields[i].name == sharkspirit_m) {
			return 2;
		}
	return 1;
}

pair<state, int> trans(state st, ope op) {
	int dmg = 0;
	bool flag = true;
	switch (op.name) {
		case shadowstep: {
			flag = rmv2(st.hands, st.H, op.name, op.cost);
			if (!flag) return badpair;
			flag = rmv1(st.fields, st.F, op.target);
			if (!flag) return badpair;
			st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] * 3 + spelldebuff, 0);
			if (st.mana < 0) return badpair;

			st.hands[st.H++] = cardcons(mn2cn(op.target), originalcost(op.target) - 2);
			st.auras[0] = 0;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case backstab: {
			//暂时未考虑区分背刺敌方随从和背刺血量>2的友方随从，统一记作null，且认为总能这么做 
			//用作去除时，仅考虑去除狐人老千和赤烟腾武 
			flag = rmv2(st.hands, st.H, op.name, op.cost);
			if (!flag) return badpair;
			if (op.target == nul) {
				if (openmode == 0) {
					flag = false;
					rep(i, 0, st.F - 1) {
						if (st.fields[i].name == sharkspirit_m || st.fields[i].name == cutterbutter_m || st.fields[i].name == spectralpillager_m) {
							flag = true;
							break;
						}
					}
					if (!flag) return badpair;
				}
			}
			else {
				flag = (op.target == foxyfraud_m) || (op.target == mailboxdancer_m) || (op.target == redsmoke_m);
				if (!flag) return badpair;
				flag = rmv1(st.fields, st.F, op.target);
				if (!flag) return badpair;
			}
			st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] * 3 + spelldebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[0] = 0;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case fakecoin: {
			flag = rmv2(st.hands, st.H, op.name, op.cost) && (op.target == nul);
			if (!flag) return badpair;
			st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] * 3 + spelldebuff, 0);
			if (st.mana < 0) return badpair;

			st.mana = min(st.mana + 1, manalim);
			st.auras[0] = 0;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case preparation: {
			flag = rmv2(st.hands, st.H, op.name, op.cost) && (op.target == nul);
			if (!flag) return badpair;
			st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] * 3 + spelldebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[0] = 1;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case illusionpotion: {
			flag = rmv2(st.hands, st.H, op.name, op.cost) && (op.target == nul);
			if (!flag) return badpair;
			st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] * 3 + spelldebuff, 0);
			if (st.mana < 0) return badpair;

			rep(i, 0, st.F - 1) {
				if (st.H >= hlim) break;
				st.hands[st.H++] = cardcons(mn2cn(st.fields[i].name), 1);
			}
			st.auras[0] = 0;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case sharkspirit: {
			flag = rmv2(st.hands, st.H, op.name, op.cost) && (op.target == nul);
			if (!flag) return badpair;
			if (st.F >= mlim) flag = false;
			else st.fields[st.F++] = minioncons(cn2mn(op.name));
			if (!flag) return badpair;
			st.mana -= max(op.cost - st.auras[2] * 3 + miniondebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case foxyfraud: {
			int twi = twice(st);
			flag = rmv2(st.hands, st.H, op.name, op.cost) && (op.target == nul);
			if (!flag) return badpair;
			if (st.F >= mlim) flag = false;
			else st.fields[st.F++] = minioncons(cn2mn(op.name));
			if (!flag) return badpair;
			st.mana -= max(op.cost - st.auras[2] * 3 + miniondebuff + battlecrydebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[1] = min(st.auras[1] + twi, alim[1]);
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case mailboxdancer: {
			int twi = twice(st);
			flag = rmv2(st.hands, st.H, op.name, op.cost) && (op.target == nul);
			if (!flag) return badpair;
			if (st.F >= mlim) flag = false;
			else st.fields[st.F++] = minioncons(cn2mn(op.name));
			if (!flag) return badpair;
			st.mana -= max(op.cost - st.auras[2] * 3 + miniondebuff + battlecrydebuff, 0);
			if (st.mana < 0) return badpair;

			while (twi--) {
				if (st.H >= hlim) break;
				st.hands[st.H++] = cardcons(fakecoin, 0);
			}
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case cutterbutter: {
			int twi = twice(st);
			flag = rmv2(st.hands, st.H, op.name, op.cost) && (op.target == nul);
			if (!flag) return badpair;
			if (st.F >= mlim) flag = false;
			else st.fields[st.F++] = minioncons(cn2mn(op.name));
			if (!flag) return badpair;
			st.mana -= max(op.cost - st.auras[1] * 2 - st.auras[2] * 3 + miniondebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[1] = 0;
			if (st.num) {
				st.auras[2] = min(st.auras[3] + twi, alim[2]);
				st.auras[3] = twi;
			}
			else {
				st.auras[2] = st.auras[3];
				st.auras[3] = 0;
			}
			st.num++;
			break;
		}
		case redsmoke: {
			flag = rmv2(st.hands, st.H, op.name, op.cost);
			if (!flag) return badpair;
			if (st.F >= mlim) flag = false;
			else st.fields[st.F++] = minioncons(cn2mn(op.name));
			if (!flag) return badpair;
			if (op.target == nul && st.F == 1) {
				//空场，腾武可空交 
			}
			else {
				flag = rmv1(st.fields, st.F, op.target);
				if (!flag) return badpair;
				st.hands[st.H++] = cardcons(mn2cn(op.target), 1);
			}
			st.mana -= max(op.cost - st.auras[2] * 3 + miniondebuff + battlecrydebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case spectralpillager: {
			int twi = twice(st);
			flag = rmv2(st.hands, st.H, op.name, op.cost);
			if (!flag) return badpair;
			if (st.F >= mlim) flag = false;
			else st.fields[st.F++] = minioncons(cn2mn(op.name));
			if (!flag) return badpair;
			if (op.target == enemyhero) {
				dmg = st.num * twi;
			}
			else {
				//应用总能去除的假定 
				bool flag = rmv1(st.fields, st.F, op.target);
				if (!flag) return badpair;
			}
			st.mana -= max(op.cost - st.auras[1] * 2 - st.auras[2] * 3 + miniondebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[1] = 0;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case anyminion: {
			//假设为无词条随从，不适用于吉尔尼斯 
			bool flag = rmv2(st.hands, st.H, op.name, op.cost) && (op.target == nul);
			if (!flag) return badpair;
			if (st.F >= mlim) flag = false;
			else st.fields[st.F++] = minioncons(cn2mn(op.name));
			if (!flag) return badpair;
			st.mana -= max(op.cost - st.auras[2] * 3 + miniondebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case anyspell: {
			bool flag = rmv2(st.hands, st.H, op.name, op.cost) && (op.target == nul);
			if (!flag) return badpair;
			st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] * 3 + spelldebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[0] = 0;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case invalid: {
			return badpair;
			break;
		}
	}
	return make_pair(st, dmg);
}