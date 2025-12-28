#include <bits/stdc++.h>
using namespace std;

class GS {
    char* t;
    int s;
    char* p;

public:
    GS() {
        s = 0;
        t = nullptr;
        p = nullptr;
    }

    GS(const char* a) {
        if (!a) {
            s = 0;
            t = nullptr;
            p = nullptr;
            return;
        }

        s = strlen(a);
        t = new char[s + 1];
        for (int i = 0; i < s; i++) t[i] = a[i];
        t[s] = '\0';

        if (s <= 12) {
            p = new char[5];
            for (int i = 0; i < min(4, s); i++) p[i] = a[i];
            p[min(4, s)] = '\0';
        } else {
            p = nullptr;
        }
    }

    GS(const GS& o) {
        s = o.s;
        if (s == 0) {
            t = nullptr;
            p = nullptr;
            return;
        }

        t = new char[s + 1];
        for (int i = 0; i < s; i++) t[i] = o.t[i];
        t[s] = '\0';

        if (s <= 12) {
            p = new char[5];
            for (int i = 0; i < min(4, s); i++) p[i] = o.p[i];
            p[min(4, s)] = '\0';
        } else {
            p = nullptr;
        }
    }

    GS& operator=(const GS& o) {
        if (this == &o) return *this;

        delete[] t;
        delete[] p;

        s = o.s;
        if (s == 0) {
            t = nullptr;
            p = nullptr;
            return *this;
        }

        t = new char[s + 1];
        for (int i = 0; i < s; i++) t[i] = o.t[i];
        t[s] = '\0';

        if (s <= 12) {
            p = new char[5];
            for (int i = 0; i < min(4, s); i++) p[i] = o.p[i];
            p[min(4, s)] = '\0';
        } else {
            p = nullptr;
        }

        return *this;
    }

    ~GS() {
        delete[] t;
        delete[] p;
    }

    int sz() const {
        return s;
    }

    void pr() const {
        for (int i = 0; i < s; i++) cout << t[i];
        cout << '\n';
    }

    void cl() {
        delete[] t;
        delete[] p;
        t = nullptr;
        p = nullptr;
        s = 0;
    }

    const char& operator[](int i) const {
        return t[i];
    }

    char& operator[](int i) {
        return t[i];
    }

    int fd(char c) const {
        for (int i = 0; i < s; i++)
            if (t[i] == c) return i;
        return -1;
    }
};

GS operator+(const GS& a, const GS& b) {
    int sa = a.sz();
    int sb = b.sz();
    char* n = new char[sa + sb + 1];

    for (int i = 0; i < sa; i++) n[i] = a[i];
    for (int i = 0; i < sb; i++) n[sa + i] = b[i];

    n[sa + sb] = '\0';
    GS r(n);
    delete[] n;
    return r;
}

int main() {
    GS a("Boban");
    GS b("Joksimovski");

    cout << a.sz() << '\n';
    a.pr();

    cout << a[2] << '\n';
    a[2] = 'p';
    cout << a[2] << '\n';

    cout << a.fd('a') << '\n';

    GS c = a + b;
    c.pr();

    return 0;
}
