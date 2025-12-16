#include "Validation.h"

bool isValidRoll(const string& r) {
    if (r.length() != 13) return false;
    if (r.substr(0, 3) != "01-") return false;
    if (r[9] != '-') return false;
    for (int i = 3; i <= 8; i++) if (!isdigit(r[i])) return false;
    for (int i = 10; i <= 12; i++) if (!isdigit(r[i])) return false;
    return true;
}

bool isValidGmail(const string& g) {
    const string s = "@gmail.com";
    return g.length() > s.length() &&
        g.substr(g.length() - s.length()) == s;
}

bool isStrongPassword(const string& p) {
    if (p.length() < 6) return false;
    for (char c : p) if (isdigit(c)) return true;
    return false;
}
