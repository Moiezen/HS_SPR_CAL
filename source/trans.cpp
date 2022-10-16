#include "trans.h"

void rmvh(card* a, int& n, int x) {
	rep(i, x, n - 1) {
		a[i] = a[i + 1];
	}
	n--;
}
void rmvf(minion* a, int& n, int x) {
	rep(i, x, n - 1) {
		a[i] = a[i + 1];
	}
	n--;
}

pair<state, int> badpair = make_pair(emptyst, badpair_min);

int twice(state st) {
	rep(i, 0, st.F - 1)
		if (st.fields[i].name == sharkspirit_m) {
			return 2;
		}
	return 1;
}
int twice2(state st) {
	rep(i, 0, st.F - 1)
		if (st.fields[i].name == sharkspirit_m || st.fields[i].name == bronze_m) {
			return 2;
		}
	return 1;
}

pair<state, int> trans(state st, oxy ox) {
	if (ox.x >= st.H || ox.x < -1 || ox.y >= st.F || ox.y < -2) {
		return badpair;
	}
	ope op = exact(st, ox);

	int dmg = 0;
	switch (op.name) {
		case shadowstep: {
			rmvh(st.hands, st.H, ox.x);
			if (ox.y < 0) return badpair;
			rmvf(st.fields, st.F, ox.y);

			st.hands[st.H++] = cardcons(mn2cn(op.target), originalcost(op.target) - 2);

			st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] + spelldebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[0] = 0;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case backstab: {
			rmvh(st.hands, st.H, ox.x);
			if (ox.y == -1) {
				if (stabable == 0) {
					return badpair;
				}
			}
			else if (ox.y >= 0) {
				if (st.fields[ox.y].curhealth != st.fields[ox.y].health) {
					return badpair;
				}
				st.fields[ox.y].curhealth -= 2;
				if (st.fields[ox.y].curhealth <= 0) {
					rmvf(st.fields, st.F, ox.y);
				}
			}

			st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] + spelldebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[0] = 0;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case extortion: {
			rmvh(st.hands, st.H, ox.x);
			if (ox.y == -1) {
				if (stabable == 0) {
					return badpair;
				}
			}
			else if (ox.y >= 0) {
				if (st.fields[ox.y].curhealth != st.fields[ox.y].health) {
					return badpair;
				}
				st.fields[ox.y].curhealth -= 3;
				if (st.fields[ox.y].curhealth <= 0) {
					rmvf(st.fields, st.F, ox.y);
				}
			}

			st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] + spelldebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[0] = 0;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case bonespike: {
			rmvh(st.hands, st.H, ox.x);
			int kill = 0;
			if (ox.y == -1) {
				if (boneable == 0) {
					return badpair;
				}
				kill = 1;
			}
			else if (ox.y >= 0) {
				st.fields[ox.y].curhealth -= 3;
				if (st.fields[ox.y].curhealth <= 0) {
					rmvf(st.fields, st.F, ox.y);
					kill = 1;
				}
			}

			st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] + spelldebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[0] = 0;
			st.auras[2] = st.auras[3] + kill * 2;
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case fakecoin: {
			rmvh(st.hands, st.H, ox.x);
			if (ox.y != -1) return badpair;

			st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] + spelldebuff, 0);
			if (st.mana < 0) return badpair;

			st.mana = min(st.mana + 1, manalim);
			st.auras[0] = 0;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case preparation: {
			rmvh(st.hands, st.H, ox.x);
			if (ox.y != -1) return badpair;

			st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] + spelldebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[0] = 1;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case illusionpotion: {
			rmvh(st.hands, st.H, ox.x);
			if (ox.y != -1) return badpair;

			rep(i, 0, st.F - 1) {
				if (st.H >= hlim) break;
				st.hands[st.H++] = cardcons(mn2cn(st.fields[i].name), 1, 1);
			}

			st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] + spelldebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[0] = 0;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case shroud: {
			rmvh(st.hands, st.H, ox.x);
			if (ox.y != -1) return badpair;

			if (st.drawmn < deckmn && st.drawmn + 2 >= deckmn) {
				rep(i, 0, deckmn - 1) {
					if (st.H >= hlim) break;
					st.hands[st.H++] = cardcons(mn2cn(deckm[i]), originalcost(deckm[i]));
				}
			}
			st.drawmn += 2;

			st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] + spelldebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[0] = 0;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case swindle: {
			rmvh(st.hands, st.H, ox.x);
			if (ox.y != -1) return badpair;

			if (st.num) {
				if (st.drawmn < deckmn && st.drawmn + 1 >= deckmn) {
					rep(i, 0, deckmn - 1) {
						if (st.H >= hlim) break;
						st.hands[st.H++] = cardcons(mn2cn(deckm[i]), originalcost(deckm[i]));
					}
				}
				st.drawmn += 1;
			}

			st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[1] * 2 - st.auras[2] + spelldebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[0] = 0;
			st.auras[1] = 0;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case sharkspirit: {
			int h = st.hands[ox.x].health;
			rmvh(st.hands, st.H, ox.x);
			if (ox.y != -1) return badpair;
			if (st.F >= mlim) {
				return badpair;
			}
			if (h > 0) {
				st.fields[st.F++] = minioncons(cn2mn(op.name), h, h);
			}

			st.mana -= max(op.cost - st.auras[2] + miniondebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case bronze: {
			int h = st.hands[ox.x].health;
			rmvh(st.hands, st.H, ox.x);
			if (ox.y != -1) return badpair;
			if (st.F >= mlim) {
				return badpair;
			}
			if (h > 0) {
				st.fields[st.F++] = minioncons(cn2mn(op.name), h, h);
			}

			st.mana -= max(op.cost - st.auras[2] + miniondebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case foxyfraud: {
			int twi = twice2(st);
			int h = st.hands[ox.x].health;
			rmvh(st.hands, st.H, ox.x);
			if (ox.y != -1) return badpair;
			if (st.F >= mlim) {
				return badpair;
			}
			st.fields[st.F++] = minioncons(cn2mn(op.name), h, h);

			st.mana -= max(op.cost - st.auras[2] + miniondebuff + battlecrydebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[1] = min(st.auras[1] + twi, alim[1]);
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case mailboxdancer: {
			int twi = twice2(st);
			int h = st.hands[ox.x].health;
			rmvh(st.hands, st.H, ox.x);
			if (ox.y != -1) return badpair;
			if (st.F >= mlim) {
				return badpair;
			}
			st.fields[st.F++] = minioncons(cn2mn(op.name), h, h);

			while (twi--) {
				if (st.H >= hlim) break;
				st.hands[st.H++] = cardcons(fakecoin, 0);
			}

			st.mana -= max(op.cost - st.auras[2] + miniondebuff + battlecrydebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case illucia: {
			int twi = twice2(st);
			int h = st.hands[ox.x].health;
			rmvh(st.hands, st.H, ox.x);
			if (ox.y != -1) return badpair;
			if (st.F >= mlim) {
				return badpair;
			}
			st.fields[st.F++] = minioncons(cn2mn(op.name), h, h);

			st.H = oppoH;
			rep(i, 0, oppoH - 1) {
				st.hands[i] = oppohands[i];
			}

			st.mana -= max(op.cost - st.auras[2] + miniondebuff + battlecrydebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case cutterbutter: {
			int twi = twice(st);
			int h = st.hands[ox.x].health;
			rmvh(st.hands, st.H, ox.x);
			if (ox.y != -1) return badpair;
			if (st.F >= mlim) {
				return badpair;
			}
			st.fields[st.F++] = minioncons(cn2mn(op.name), h, h);

			st.mana -= max(op.cost - st.auras[1] * 2 - st.auras[2] + miniondebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[1] = 0;
			if (st.num) {
				st.auras[2] = min(st.auras[3] + twi * 3, alim[2]);
				st.auras[3] = twi * 3;
			}
			else {
				st.auras[2] = st.auras[3];
				st.auras[3] = 0;
			}
			st.num++;
			break;
		}
		case elvensinger: {
			int twi = twice(st);
			int h = st.hands[ox.x].health;
			rmvh(st.hands, st.H, ox.x);
			if (ox.y != -1) return badpair;
			if (st.F >= mlim) {
				return badpair;
			}
			st.fields[st.F++] = minioncons(cn2mn(op.name), h, h);

			if (st.num) {
				if (st.drawmn < deckmn && st.drawmn + twi * 2 >= deckmn) {
					rep(i, 0, deckmn - 1) {
						if (st.H >= hlim) break;
						st.hands[st.H++] = cardcons(mn2cn(deckm[i]), originalcost(deckm[i]));
					}
				}
				st.drawmn += twi * 2;
			}
			
			st.mana -= max(op.cost - st.auras[1] * 2 - st.auras[2] + miniondebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[1] = 0;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case redsmoke: {
			int twi = twice2(st);
			int h = st.hands[ox.x].health;
			rmvh(st.hands, st.H, ox.x);
			if (st.F >= mlim) {
				return badpair;
			}
			st.fields[st.F++] = minioncons(cn2mn(op.name), h, h);

			if (ox.y == -1 && st.F == 1) {
				//腾武可空交（空场限定）
			}
			else if (ox.y >= 0) {
				rmvf(st.fields, st.F, ox.y);
				st.hands[st.H++] = cardcons(mn2cn(op.target), 1);
			}
			else {
				return badpair;
			}

			st.mana -= max(op.cost - st.auras[2] + miniondebuff + battlecrydebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case shadowcaster: {
			int twi = twice2(st);
			int h = st.hands[ox.x].health;
			rmvh(st.hands, st.H, ox.x);
			if (st.F >= mlim) {
				return badpair;
			}
			st.fields[st.F++] = minioncons(cn2mn(op.name), h, h);

			if (ox.y == -1 && st.F == 1) {
				//暗施可空交（空场限定）
			}
			else if (ox.y >= 0) {
				while (twi--) {
					if (st.H >= hlim) break;
					st.hands[st.H++] = cardcons(mn2cn(op.target), 1, 1);
				}
			}
			else {
				return badpair;
			}

			st.mana -= max(op.cost - st.auras[2] + miniondebuff + battlecrydebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case spectralpillager: {
			int twi = twice(st);
			int h = st.hands[ox.x].health;
			rmvh(st.hands, st.H, ox.x);
			if (st.F >= mlim) {
				return badpair;
			}
			st.fields[st.F++] = minioncons(cn2mn(op.name), h, h);

			if (ox.y == -2) {
				dmg = st.num;
				if (twi == 2) dmg = -dmg;
				//以此标记双倍
			}
			else if (ox.y >= 0) {
				st.fields[ox.y].curhealth -= st.num * twi;
				if (st.fields[ox.y].curhealth <= 0) {
					rmvf(st.fields, st.F, ox.y);
				}
			}
			else {
				return badpair;
			}

			st.mana -= max(op.cost - st.auras[1] * 2 - st.auras[2] + miniondebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[1] = 0;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case anyminion: {
			//假设为无词条随从，不适用于吉尔尼斯 
			int h = st.hands[ox.x].health;
			rmvh(st.hands, st.H, ox.x);
			if (st.F >= mlim) {
				return badpair;
			}
			st.fields[st.F++] = minioncons(cn2mn(op.name), h, h);

			st.mana -= max(op.cost - st.auras[2] + miniondebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case anyspell: {
			rmvh(st.hands, st.H, ox.x);
			if (ox.y != -1) return badpair;

			st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] + spelldebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[0] = 0;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case anyweapon: {
			rmvh(st.hands, st.H, ox.x);
			if (ox.y != -1) return badpair;

			if (st.hatk >= 0) st.hatk = 2;

			st.mana -= max(op.cost - st.auras[2], 0);
			if (st.mana < 0) return badpair;

			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case anycombospell: {
			rmvh(st.hands, st.H, ox.x);
			if (ox.y != -1) return badpair;

			st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[1] * 2 - st.auras[2] + spelldebuff, 0);
			if (st.mana < 0) return badpair;

			st.auras[0] = 0;
			st.auras[1] = 0;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case madnessplague: {
			rmvh(st.hands, st.H, ox.x);
			if (ox.y != -1) return badpair;

			if (st.hatk >= 0) st.hatk = 2;

			st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] + spelldebuff, 0);
			if (st.mana < 0) return badpair;
			
			st.auras[0] = 0;
			st.auras[2] = st.auras[3];
			st.auras[3] = 0;
			st.num++;
			break;
		}
		case heroattack: {
			if (ox.y != -2) return badpair;
			if (st.hatk <= 0) return badpair;

			dmg = st.hatk;
			st.hatk = -1;

			if (iceblockif == 0) {
				st.mana = -999;
				//如果不需要破冰，那么英雄攻击一定可以留到最后进行
				//因此，可以认为在英雄攻击后不会再进行任何操作，即直接将mana设置为-999
				//这一优化在solve中曾有另一种不完全相同但实际效果相同的解决方式
			}
			break;
		}
		case invalid: {
			return badpair;
			break;
		}
	}
	return make_pair(st, dmg);
}