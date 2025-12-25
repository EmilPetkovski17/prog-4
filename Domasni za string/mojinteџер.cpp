#include <bits/stdc++.h>
using namespace std;

struct MojInt {
    string broj;
    friend bool operator>=(string prv, string vtor);
    friend MojInt operator+(MojInt& prv, MojInt& vtor);
    friend MojInt operator-(MojInt& prv, MojInt& vtor);
};

string trgninuli(string tekst) {
    int indeks = 0;
    while (indeks + 1 < tekst.size() && tekst[indeks] == '0') {
        indeks++;
    }
    return tekst.substr(indeks);
}

bool operator>=(string prv, string vtor) {
    prv = trgninuli(prv);
    vtor = trgninuli(vtor);

    if (prv.size() != vtor.size())
        return prv.size() > vtor.size();
    return prv >= vtor;
}

MojInt operator+(MojInt& prv, MojInt& vtor) {
    string x = prv.broj, y = vtor.broj;
    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());

    string rezultat = "";
    int ostatok = 0;

    for (int i = 0; i < max(x.size(), y.size()); i++) {
        int cifra1 = (i < x.size()) ? x[i] - '0' : 0;
        int cifra2 = (i < y.size()) ? y[i] - '0' : 0;
        int zbir = cifra1 + cifra2 + ostatok;
        rezultat.push_back(zbir % 10 + '0');
        ostatok = zbir / 10;
    }

    if (ostatok) rezultat.push_back(ostatok + '0');

    reverse(rezultat.begin(), rezultat.end());
    return { trgninuli(rezultat) };
}

MojInt operator-(MojInt& prv, MojInt& vtor) {
    string x = prv.broj, y = vtor.broj;
    if (!(x >= y)) swap(x, y);

    reverse(x.begin(), x.end());
    reverse(y.begin(), y.end());

    string rezultat = "";
    int pozajmica = 0;

    for (int i = 0; i < x.size(); i++) {
        int cifra1 = x[i] - '0' - pozajmica;
        int cifra2 = (i < y.size()) ? y[i] - '0' : 0;

        if (cifra1 < cifra2) {
            cifra1 += 10;
            pozajmica = 1;
        } else {
            pozajmica = 0;
        }

        rezultat.push_back(cifra1 - cifra2 + '0');
    }

    reverse(rezultat.begin(), rezultat.end());
    return { trgninuli(rezultat) };
}

int main() {
    MojInt prvBroj{"12345"};
    MojInt vtorBroj{"567890"};

    MojInt zbir = prvBroj + vtorBroj;
    MojInt razlika = prvBroj - vtorBroj;

    cout << zbir.broj << "\n";
    cout << razlika.broj << "\n";

    return 0;
}
