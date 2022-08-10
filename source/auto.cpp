#include "auto.h"

map<string, string> id2cid;
map<string, string> id2cost;
map<string, string> id2zone;
map<string, string> id2err;

void getafter(string s, string a, string& t) {
	if (t != "") return;
	auto p = s.find(a);
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
	if (s.find("SW_070") != -1) return yxwz;
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
	//现在可能多次调用，需要每次清空 

	//更新结构： 
	//id->cid,cost,zone
	//resource(mana)
	//op->id,err
	//此处为简便，直接令op.id->err 

	cin.clear();
	//重置输入流，防止无法读取 

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
			//s0不属于这部分却已经被读入了，应当直接视为下一次的s 
			//且这个s可能立即属于新部分，故外层使用while 
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
			//此处有可能存在error=项但项为空，不必区分 
		}
	}

	secrets = 0;
	for (auto s1 : hand) {
		s2 = id2cid[s1];
		s3 = id2cost[s1];
		if (s3 == "") s3 = "0";
		s4 = id2zone[s1];
		if (s4 == "HAND" || s4 == "DECK") {
			//偶尔手牌会保持显示zone=DECK 
			//虽然很奇怪但能work 
			autost.hands[autost.H++] = cardcons(cid2kpm(s2), atoi(s3.c_str()));
		}
		s6 = id2err[s1];
		if (cid2kpm(s2) == bc && s6 != "") {
			openmode = 0;
			//模式检定，将无法直接通过bc->nul 
		}
		else openmode = 1;

		id2zone[s1] = "";
		//防止（可交易牌）被统计两次 
	}

	autost.mana = atoi(resources.c_str());

	fclose(stdin);

	return autost;
}