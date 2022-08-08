#include "trans.h"

bool rmv1(minion* a, int& n, scm b) {
	rep(i, 0, n - 1) {
		if (a[i].name == b) {
			rep(j, i + 1, n - 1) a[j - 1] = a[j];
			n--;
			return true;
		}
	}
	return false;
}
bool rmv2(card* a, int& n, kpm b, int c) {
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
		if (st.fields[i].name == msyzl) {
			return 2;
		}
	return 1;
}

pair<state, int> trans(state st, ope op) {
	int dmg = 0;
	bool flag = true;
	switch (op.name) {
	case ayb: {
		flag = rmv2(st.hands, st.H, op.name, op.cost);
		if (!flag) return badpair;
		flag = rmv1(st.fields, st.F, op.target);
		if (!flag) return badpair;
		st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] * 3, 0);
		if (st.mana < 0) return badpair;

		st.hands[st.H++] = cardcons(s2k(op.target), bcost(op.target) - 2);
		st.auras[0] = 0;
		st.auras[2] = st.auras[3];
		st.auras[3] = 0;
		st.num++;
		break;
	}
	case bc: {
		//��ʱδ�������ֱ��̵з���Ӻͱ���Ѫ��>2���ѷ���ӣ�ͳһ����null������Ϊ������ô�� 
		//����ȥ��ʱ��������ȥ��������ǧ�ͳ������� 
		flag = rmv2(st.hands, st.H, op.name, op.cost);
		if (!flag) return badpair;
		if (op.target == nul) {
			if (openmode == 0) {
				flag = false;
				rep(i, 0, st.F - 1) {
					if (st.fields[i].name == msyzl || st.fields[i].name == mdy || st.fields[i].name == mglfz) {
						flag = true;
						break;
					}
				}
				if (!flag) return badpair;
			}
		}
		else {
			flag = (op.target == mhrlq) || (op.target == mtw);
			if (!flag) return badpair;
			flag = rmv1(st.fields, st.F, op.target);
			if (!flag) return badpair;
		}
		st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] * 3, 0);
		if (st.mana < 0) return badpair;

		st.auras[0] = 0;
		st.auras[2] = st.auras[3];
		st.auras[3] = 0;
		st.num++;
		break;
	}
	case jb: {
		flag = rmv2(st.hands, st.H, op.name, op.cost) && (op.target == nul);
		if (!flag) return badpair;
		st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] * 3, 0);
		if (st.mana < 0) return badpair;

		st.mana = min(st.mana + 1, manalim);
		st.auras[0] = 0;
		st.auras[2] = st.auras[3];
		st.auras[3] = 0;
		st.num++;
		break;
	}
	case sjdf: {
		flag = rmv2(st.hands, st.H, op.name, op.cost) && (op.target == nul);
		if (!flag) return badpair;
		st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] * 3, 0);
		if (st.mana < 0) return badpair;

		st.auras[0] = 1;
		st.auras[2] = st.auras[3];
		st.auras[3] = 0;
		st.num++;
		break;
	}
	case hjys: {
		flag = rmv2(st.hands, st.H, op.name, op.cost) && (op.target == nul);
		if (!flag) return badpair;
		st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] * 3, 0);
		if (st.mana < 0) return badpair;

		rep(i, 0, st.F - 1) {
			if (st.H >= hlim) break;
			st.hands[st.H++] = cardcons(s2k(st.fields[i].name), 1);
		}
		st.auras[0] = 0;
		st.auras[2] = st.auras[3];
		st.auras[3] = 0;
		st.num++;
		break;
	}
	case syzl: {
		flag = rmv2(st.hands, st.H, op.name, op.cost) && (op.target == nul);
		if (!flag) return badpair;
		if (st.F >= mlim) flag = false;
		else st.fields[st.F++] = minioncons(k2s(op.name));
		if (!flag) return badpair;
		st.mana -= max(op.cost - st.auras[2] * 3, 0);
		if (st.mana < 0) return badpair;

		st.auras[2] = st.auras[3];
		st.auras[3] = 0;
		st.num++;
		break;
	}
	case hrlq: {
		int twi = twice(st);
		flag = rmv2(st.hands, st.H, op.name, op.cost) && (op.target == nul);
		if (!flag) return badpair;
		if (st.F >= mlim) flag = false;
		else st.fields[st.F++] = minioncons(k2s(op.name));
		if (!flag) return badpair;
		st.mana -= max(op.cost - st.auras[2] * 3, 0);
		if (st.mana < 0) return badpair;

		st.auras[1] = min(st.auras[1] + twi, alim[1]);
		st.auras[2] = st.auras[3];
		st.auras[3] = 0;
		st.num++;
		break;
	}
	case dy: {
		int twi = twice(st);
		flag = rmv2(st.hands, st.H, op.name, op.cost) && (op.target == nul);
		if (!flag) return badpair;
		if (st.F >= mlim) flag = false;
		else st.fields[st.F++] = minioncons(k2s(op.name));
		if (!flag) return badpair;
		st.mana -= max(op.cost - st.auras[1] * 2 - st.auras[2] * 3, 0);
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
	case tw: {
		flag = rmv2(st.hands, st.H, op.name, op.cost);
		if (!flag) return badpair;
		if (st.F >= mlim) flag = false;
		else st.fields[st.F++] = minioncons(k2s(op.name));
		if (!flag) return badpair;
		if (op.target == nul && st.F == 1) {
			//�ճ�������ɿս� 
		}
		else {
			flag = rmv1(st.fields, st.F, op.target);
			if (!flag) return badpair;
			st.hands[st.H++] = cardcons(s2k(op.target), 1);
		}
		st.mana -= max(op.cost - st.auras[2] * 3, 0);
		if (st.mana < 0) return badpair;

		st.auras[2] = st.auras[3];
		st.auras[3] = 0;
		st.num++;
		break;
	}
	case glfz: {
		int twi = twice(st);
		flag = rmv2(st.hands, st.H, op.name, op.cost);
		if (!flag) return badpair;
		if (st.F >= mlim) flag = false;
		else st.fields[st.F++] = minioncons(k2s(op.name));
		if (!flag) return badpair;
		if (op.target == dfyx) {
			dmg = st.num * twi;
		}
		else {
			//Ӧ������ȥ���ļٶ� 
			bool flag = rmv1(st.fields, st.F, op.target);
			if (!flag) return badpair;
		}
		st.mana -= max(op.cost - st.auras[1] * 2 - st.auras[2] * 3, 0);
		if (st.mana < 0) return badpair;

		st.auras[1] = 0;
		st.auras[2] = st.auras[3];
		st.auras[3] = 0;
		st.num++;
		break;
	}
	case ljsc: {
		//����Ϊ�޴�����ӣ��������ڼ�����˹ 
		bool flag = rmv2(st.hands, st.H, op.name, op.cost) && (op.target == nul);
		if (!flag) return badpair;
		if (st.F >= mlim) flag = false;
		else st.fields[st.F++] = minioncons(k2s(op.name));
		if (!flag) return badpair;
		st.mana -= max(op.cost - st.auras[2] * 3, 0);
		if (st.mana < 0) return badpair;

		st.auras[2] = st.auras[3];
		st.auras[3] = 0;
		st.num++;
		break;
	}
	case ljfs: {
		bool flag = rmv2(st.hands, st.H, op.name, op.cost) && (op.target == nul);
		if (!flag) return badpair;
		st.mana -= max(op.cost - st.auras[0] * 2 - st.auras[2] * 3, 0);
		if (st.mana < 0) return badpair;

		st.auras[0] = 0;
		st.auras[2] = st.auras[3];
		st.auras[3] = 0;
		st.num++;
		break;
	}
	case lj: {
		return badpair;
		break;
	}
	}
	return make_pair(st, dmg);
}