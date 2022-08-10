#include "output.h"

string o2s(ope o) {
	string s = "";
	s = s + k2str(o.name);
	s = s + "(";
	s = s + to_string(o.cost);
	s = s + ")";
	if (o.target != nul) {
		s = s + "->" + s2str(o.target);
	}
	s = s + "\n";
	return s;
}

string output(opes o, int d, int u, ll t) {
	string s = "";
	if (u == 0) s += "(Çî¾¡Æþ¶Ï)\n";
	if (u == 1) s += "(´ï±êÆþ¶Ï)\n";
	if (u == 2) s += "(Ê±ÏÞÆþ¶Ï)\n";
	s = s + to_string(d) + "\n";
	for (auto i : o.os) {
		s = s + o2s(i);
	}
	s = s + "(" + to_string(t) + ")\n";
	return s;
}