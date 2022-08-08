#include "auto.h"

map<string, string> id2cid;
map<string, string> id2cost;
map<string, string> id2zone;
map<string, string> id2err;

void getafter(string s, string a, string& t) {
	if (t != "") return;
	int p = s.find(a);
	if (p == -1) return;
	p = p + a.size();
	while (s[p] != ' ' && s[p] != '\0') {
		t = t + s[p]; p++;
	}
}
void getid(string s, string& t) {
	getafter(s, "tag=ENTITY_ID value=", t);
	getafter(s, " id=", t);
}
void getcid(string s, string& t) {
	getafter(s, "CardID=", t);
	getafter(s, "cardId=", t);
}
void getcost(string s, string& t) {
	getafter(s, "tag=COST value=", t);
}
void getzone(string s, string& t) {
	getafter(s, "tag=ZONE value=", t);
	getafter(s, "zone=", t);
}

int secrets;

kpm cid2kpm(string s) {
	if (s.find("EX1_144") != -1) return ayb;
	if (s.find("CS2_072") != -1) return bc;
	if (s.find("CFM_630") != -1) return jb;
	if (s.find("COIN") != -1) return jb;
	if (s.find("GAME_005") != -1) return jb;
	if (s.find("EX1_145") != -1) return sjdf;
	if (s.find("SCH_352") != -1) return hjys;
	if (s.find("TRL_092") != -1) return syzl;
	if (s.find("DMF_511") != -1) return hrlq;
	if (s.find("BAR_552") != -1) return dy;
	if (s.find("DMF_071") != -1) return tw;
	if (s.find("ICC_910") != -1) return glfz;
	if (s.find("DMF_512") != -1) return ljfs;
	if (s.find("LOOT_214") != -1 && secrets == 0) {
		secrets = 1;
		return ljfs;
	}
	return lj;
}

vector<string> hand;
state autoread(string _s) {
	state autost = emptyst;
	//���ڿ��ܶ�ε��ã���Ҫÿ����� 

	//���½ṹ�� 
	//id->cid,cost,zone
	//resource(mana)
	//op->id,err
	//�˴�Ϊ��㣬ֱ����op.id->err 

	cin.clear();
	//��������������ֹ�޷���ȡ 

	FILE* f = freopen((_s + "\\Logs\\power.log").c_str(), "r", stdin);

	id2cid.clear();
	id2cost.clear();
	id2zone.clear();
	id2err.clear();
	hand.clear();

	string s, s0;
	string s1, s2, s3, s4;
	string s5, resources;
	string s6;

	int lines = 0;

	while (getline(cin, s)) {
		lines++;
		if (s.find("- CREATE_GAME") != -1) {
			id2cid.clear();
			id2cost.clear();
			id2zone.clear();
			id2err.clear();
			hand.clear();
		}

		while (s.find("-     SHOW_ENTITY") != -1) {
			getline(cin, s0);
			while (s0.find("-         tag=") != -1) {
				s = s + " " + s0;
				getline(cin, s0);
			}
			s1 = s2 = s3 = s4 = "";
			getid(s, s1);
			getcid(s, s2);
			getcost(s, s3);
			getzone(s, s4);
			if (s1 != "") {
				if (s2 != "") id2cid[s1] = s2;
				if (s3 != "") id2cost[s1] = s3;
				if (s4 != "") id2zone[s1] = s4;
			}

			s = s0;
			//s0�������ⲿ��ȴ�Ѿ��������ˣ�Ӧ��ֱ����Ϊ��һ�ε�s 
			//�����s�������������²��֣������ʹ��while 
		}

		if (s.find("TAG_CHANGE") != -1) {
			s1 = s2 = s3 = s4 = s5 = "";
			getid(s, s1);
			getcid(s, s2);
			getcost(s, s3);
			getzone(s, s4);
			getafter(s, "tag=RESOURCES value=", s5);
			if (s1 != "") {
				if (s2 != "") id2cid[s1] = s2;
				if (s3 != "") id2cost[s1] = s3;
				if (s4 != "") id2zone[s1] = s4;
			}
			if (s5 != "") resources = s5;
			continue;
		}

		if (s.find("Options() - id=") != -1) hand.clear();
		if (s.find("Options()") != -1 && s.find("option") != -1) {
			s1 = s6 = "";
			getid(s, s1);
			getafter(s, "error=", s6);
			if (s1 != "") hand.push_back(s1);
			if (s1 != "" && s6 != "") id2err[s1] = s6;
			//�˴��п��ܴ���error=���Ϊ�գ��������� 
		}
	}

	secrets = 0;
	for (auto s1 : hand) {
		s2 = id2cid[s1];
		s3 = id2cost[s1];
		if (s3 == "") s3 = "0";
		s4 = id2zone[s1];
		if (s4 == "HAND" || s4 == "DECK") {
			//ż�����ƻᱣ����ʾzone=DECK 
			//��Ȼ����ֵ���work 
			autost.hands[autost.H++] = cardcons(cid2kpm(s2), atoi(s3.c_str()));
		}
		s6 = id2err[s1];
		if (cid2kpm(s2) == bc && s6 != "") {
			openmode = 0;
			//ģʽ�춨�����޷�ֱ��ͨ��bc->nul 
		}
		else openmode = 1;

		id2zone[s1] = "";
		//��ֹ���ɽ����ƣ���ͳ������ 
	}

	autost.mana = atoi(resources.c_str());

	fclose(stdin);

	return autost;
}