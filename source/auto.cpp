#include "auto.h"

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
	if (s.find("LOOT_214") != -1) return ljfs;
	return lj;
}

string idhandle[4] = {
	" id=",
	" ID=",
	" Entity=",
	" EntityID="
};

string pidhandle = " PlayerID=";
string namehandle = " PlayerName=";

int mycid = -1;
int myid = -1;
int mypid = -1;
string myname;
int myhid = -1;

int yourcid = -1;
int yourid = -1;
int yourpid = -1;
string yourname;
int yourhid = -1;

const int Gid = 1;
const string Gname = "GameEntity";

map<int, map<string, pair<int, string>  > > id2tag2stampandvalue;
int stampcnt;

void updid(int x) {
	if (x == 0) {
		return;
	}

	if (mycid == -1 && id2tag2stampandvalue[x]["ZONE"].second == "HAND" && id2tag2stampandvalue[x]["CardID"].second.length() > 0) {
		mycid = id2tag2stampandvalue[x]["CONTROLLER"].second[0] - 48;

		rep(i, 2, 3) {
			if (mycid == id2tag2stampandvalue[i]["CONTROLLER"].second[0] - 48) {
				myid = i;
				mypid = id2tag2stampandvalue[i]["PlayerID"].second[0] - 48;
			}
		}

		assert(mycid == 1 || mycid == 2);
		assert(mycid + 1 == myid);
		assert(mycid == mypid);

		yourcid = 3 - mycid;
		yourid = yourcid + 1;
		yourpid = yourcid;
	}

	if (id2tag2stampandvalue[x]["CARDTYPE"].second == "HERO") {
		if (mycid != -1 && mycid == id2tag2stampandvalue[x]["CONTROLLER"].second[0] - 48) {
			myhid = x;
		}
		if (yourcid != -1 && yourcid == id2tag2stampandvalue[x]["CONTROLLER"].second[0] - 48) {
			yourhid = x;
		}
	}
}

void updname(string s) {
	auto p = s.find(namehandle);
	if (p != -1) {
		p = p + namehandle.length();
		string t = s.substr(p);
		p = t.find(" ");
		if (p != -1) {
			t = t.substr(0, p - 1);
		}

		p = s.find(pidhandle);
		p = p + pidhandle.length();
		if (mypid == s[p] - 48) {
			myname = t;
		}
		if (yourpid == s[p] - 48) {
			yourname = t;
		}
	}
}

int updcurid(string s, int x) {
	rep(i, 0, 3) {
		if (s.find(idhandle[i] + Gname) != -1) {
			return Gid;
		}
		if (myname.length() > 0 && s.find(idhandle[i] + myname) != -1) {
			return myid;
		}
		if (yourname.length() > 0 && s.find(idhandle[i] + yourname) != -1) {
			return yourid;
		}

		auto p = s.find(idhandle[i]);
		if (p != -1) {
			x = 0;
			p = p + idhandle[i].length();
			while (p < s.length() && s[p] >= '0' && s[p] <= '9') {
				x = x * 10 + s[p] - '0';
				p = p + 1;
			}
			if (x == 0) cout << s << endl << myname << endl;
			return x;
		}
	}
	return x;
}

state autoread(string _s, int& _tar) {
	cin.clear();
	//重置输入流，防止无法读取 

	FILE* f = freopen((_s + "\\Logs\\power.log").c_str(), "r", stdin);

	string s;
	int lines = 0;

	int curid = 0;
	string t, u, v, lu, lv;

	while (getline(cin, s)) {
		lines++;
		if (s.find("- CREATE_GAME") != -1) {
			mycid = -1;
			myid = -1;
			mypid = -1;
			myname = "";
			myhid = -1;

			yourcid = -1;
			yourid = -1;
			yourpid = -1;
			yourname = "";
			yourhid = -1;

			id2tag2stampandvalue.clear();
			stampcnt = 0;

			curid = 0;
		}

		updid(curid);

		updname(s);

		curid = updcurid(s, curid);

		while (s.length() > 0) {
			auto p = min(min(s.find("["), s.find("]")), s.find(" "));
			if (p != -1) {
				t = s.substr(0, p);
				s = s.substr(p + 1);
			}
			else {
				t = s;
				s = "";
			}
			p = t.find("=");
			if (p != -1) {
				u = t.substr(0, p);
				v = t.substr(p + 1);

				if (lu == "tag" && u == "value") {
					u = lv;
					lu = "";
					lv = "";
				}

				id2tag2stampandvalue[curid][u] = make_pair(stampcnt++, v);

				lu = u;
				lv = v;
			}
		}
	}

	fclose(stdin);

	//读取完毕，开始转化

	state autost = emptyst;

	for (auto i : id2tag2stampandvalue) {
		auto j = i.second;

		if (j["ZONE"].second == "HAND" && j["player"].second == to_string(mypid)) {
			kpm a = cid2kpm(j["CardID"].second);
			int b = atoi(j["COST"].second.c_str());

			autost.hands[autost.H++] = cardcons(a, b);

			if (a == bc) {
				if (j["error"].second == "NONE") {
					openmode = 1;
				}
				else {
					openmode = 0;
				}
			}
		}

		if (j["ZONE"].second == "PLAY" && j["CARDTYPE"].second == "MINION" && j["player"].second == to_string(mypid)) {
			scm a = k2s(cid2kpm(j["CardID"].second));

			autost.fields[autost.F++] = minioncons(a);
		}
	}

	autost.mana = atoi(id2tag2stampandvalue[myid]["RESOURCES"].second.c_str())
		- atoi(id2tag2stampandvalue[myid]["RESOURCES_USED"].second.c_str())
		+ atoi(id2tag2stampandvalue[myid]["TEMP_RESOURCES"].second.c_str());

	autost.num = atoi(id2tag2stampandvalue[myid]["NUM_CARDS_PLAYED_THIS_TURN"].second.c_str());

	_tar = atoi(id2tag2stampandvalue[yourhid]["HEALTH"].second.c_str())
		- atoi(id2tag2stampandvalue[yourhid]["DAMAGE"].second.c_str())
		+ atoi(id2tag2stampandvalue[yourhid]["ARMOR"].second.c_str());

	return autost;
}