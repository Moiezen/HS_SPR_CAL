#include "auto.h"
#include "deck.h"

int char2u6(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    }
    if (c >= 'a' && c <= 'z') {
        return c - 'a' + 26;
    }
    if (c >= '0' && c <= '9') {
        return c - '0' + 52;
    }
    if (c == '+') {
        return 62;
    }
    if (c == '/') {
        return 63;
    }
    return 0;
}

string plainu6(int x) {
    string s = "";
    rep(i, 0, 5) {
        s = char(x % 2 + 48) + s;
        x /= 2;
    }
    return s;
}

string dbfid2cid(int x) {
    if (x == 63517) return "BAR_552";
    if (x == 40437) return "CFM_630";
    if (x == 69521) return "CORE_CS2_072";
    if (x == 69622) return "CORE_EX1_144";
    if (x == 69623) return "CORE_EX1_145";
    if (x == 180) return "CS2_072";
    if (x == 65597) return "DED_004";
    if (x == 61635) return "DMF_071";
    if (x == 61151) return "DMF_511";
    if (x == 61154) return "DMF_512";
    if (x == 61159) return "DMF_515";
    if (x == 365) return "EX1_144";
    if (x == 1158) return "EX1_145";
    if (x == 45975) return "ICC_910";
    if (x == 45520) return "LOOT_204";
    if (x == 45531) return "LOOT_211";
    if (x == 45535) return "LOOT_214";
    if (x == 77148) return "REV_825";
    if (x == 77556) return "REV_938";
    if (x == 77557) return "REV_939";
    if (x == 59621) return "SCH_352";
    if (x == 64718) return "SW_070";
    if (x == 64033) return "SW_412";
    if (x == 49972) return "TRL_092";
    if (x == 72119) return "TSC_916";
    if (x == 54426) return "ULD_715";
    if (x == 68348) return "VAN_CS2_072";
    if (x == 69863) return "VAN_EX1_144";
    if (x == 69864) return "VAN_EX1_145";
    if (x == 63358) return "WC_016";
    return "";
}

int nums[99], nn;

vector<string> deckcode2cids(string s) {
    int l = s.length();
    string t = "";
    rep(i, 0, l - 1) t = t + plainu6(char2u6(s[i]));

    int l2 = t.length();
    int cur = 0;
    int base = 1;
    nn = 0;
    rep(i, 0, l2 / 8 - 1) {
        int bit = 0;
        rep(j, 1, 7) bit = bit * 2 + (t[8 * i + j] - 48);
        cur = cur + base * bit;
        base = base * 128;
        if (t[8 * i] == 48) {
            nums[nn++] = cur;
            cur = 0;
            base = 1;
        }
    }

    vector<string> cids;
    cids.clear();

    int m = nums[5];
    rep(i, 0, m - 1) cids.push_back(dbfid2cid(nums[6 + i]));
    int k = nums[6 + m];
    rep(i, 0, k - 1) rep(j, 0, 1) cids.push_back(dbfid2cid(nums[7 + m + i]));

    return cids;
}

void parsedeck(string _s) {
    cin.clear();
    //重置输入流，防止无法读取 

    FILE* f = freopen((_s + "\\Logs\\decks.log").c_str(), "r", stdin);

    string line;
    string code;

    while (getline(cin, line)) {
        code = line;
    }

    fclose(stdin);

    auto p = code.find("A");
    code = code.substr(p);

    vector<string> cids = deckcode2cids(code);
    deckmn = 0;
    for (auto cid : cids) {
        cardname c = cid2cn(cid);
        if (legalcn2mn(c)) {
            deckm[deckmn++] = cn2mn(c);
        }
    }
}