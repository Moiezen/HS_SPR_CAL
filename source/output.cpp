#include "output.h"

string o2s(ope o) {
	string s = "";
	s = s + cn2str(o.name);
	s = s + "(";
	s = s + to_string(o.cost);
	s = s + ")";
	if (o.target != nul) {
		s = s + "->" + mn2str(o.target);
	}
	s = s + "\n";
	return s;
}

string output(opes o, int d, int u, ll t) {
	string s = "";
	if (u == -1) s += calcing_s();
	if (u == 0) s += exhaust_s();
	if (u == 1) s += targrch_s();
	if (u == 2) s += timerch_s();
	s = s + "\n";
	s = s + to_string(d) + "\n";
	//int count = 0;
	for (auto i : o.os) {
		s = s + o2s(i);
		//count++;
		//if (count % 4 == 0) s = s + "\n";
	}
	s = s + "(" + to_string(t) + ")\n";
	return s;
}