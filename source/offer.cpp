#include "offer.h"

bool notcoinopt4demise(state a) {
	//������Ӱ����Ӳ�����ȵĸ����߼���
	//�����������Ӱ����������Ӱ��ǰ���ƵĲ���any/coin����Ӳ�����Ȳ�ֱ�ӳ���
	//����Ϊ�˱���������Ӱ��ǰ���Ƶķ������ڴ˱��������£��������淨��Ҳ��Ӧ�������
	//�ڴ˱�����������Σ����ü�����������Ӳ�����ȣ���Ϊ��һ���������临������֮�����ķ�����������˳�������а�����
	//Ҳ����˵��ҪôӲ�����ȣ�Ҫô��������
	//ע�⣺�ڼ��������£�����Ȼ����©���ģ����п��ܷ�����������Ӱ����Ӳ��
	//�׿��������Ʋ�̸�����������Ӱ��Ҫ����Ӳ�ң����ǿ�������Ӳ��һ�����ģ���������
	//���ǣ������ڷ���Ϊ9������£���������������Ӱ��Ӳ�ң��Ļ���п�����Ҫ�ȴ��Ļ���ٴ�Ӳ�ң�Ȼ����������Ӱ����Ӳ��
	//����ȴ�Ӳ�ң���ʱ�Ѿ�����Ϊ10��������Ӱ�������Ժ��ʵظ��Ƶ�Ӳ��
	//���©��������֮��ᱻ��ֹ
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
	//Ӳ�������߼�����0��Ӳ�ң����ܼӼ��ѹ⻷Ӱ�죬��ǰ����С�����ޣ�����Ҫ�Ʊ�
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
				//�����������£���ͬ�ڵ�ǰ���Ƶķ�����Ӧ�������
				//��ǰ���Ƶķ����Ѿ�ȷ������any/coin������any/coin����Ҫ�����ų�
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