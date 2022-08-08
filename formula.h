#pragma once

#include "basic.h"

int o2i(ope a);

const int flim = 4;
const double rho = 0.5;

typedef unsigned long long ull;
ull ishash(int l, int r, int* s);
extern map<ull, double> value;