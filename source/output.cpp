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
	if (u == -1) s += "(正在计算)\n";
	if (u == 0) s += "(穷尽掐断)\n";
	if (u == 1) s += "(达标掐断)\n";
	if (u == 2) s += "(时限掐断)\n";
	s = s + to_string(d) + "\n";
	for (auto i : o.os) {
		s = s + o2s(i);
	}
	s = s + "(" + to_string(t) + ")\n";
	return s;
}