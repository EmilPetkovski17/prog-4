#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>

using namespace std;

const string MAKEDONSKA_AZBUKA = "абвгдѓежзѕијклљмнњопрстуфхцчџш";

map<char,int> napraviMapa() {
    map<char,int> m;
    for (int i=0; i<MAKEDONSKA_AZBUKA.size(); i++)
        m[MAKEDONSKA_AZBUKA[i]] = i;
    return m;
}

struct Trie {
    Trie* deca[31] = {nullptr};
    bool krajNaZbor = false;
    string oznaka = "";
};

void dodadiVoTrie(Trie* koren, const string& zbor, map<char,int>& m) {
    Trie* tekoven = koren;
    for (char bukva : zbor) {
        bukva = tolower(bukva);
        if (!m.count(bukva)) continue;

        int indeks = m[bukva];
        if (!tekoven->deca[indeks])
            tekoven->deca[indeks] = new Trie();

        tekoven = tekoven->deca[indeks];
    }
    tekoven->krajNaZbor = true;
}

void konvertirajPatricia(Trie* jazol) {
    if (!jazol) return;
    for (int i=0; i<31; i++)
        if (jazol->deca[i]) konvertirajPatricia(jazol->deca[i]);

    int brojDeca = 0, indeks = -1;
    for (int i=0; i<31; i++)
        if (jazol->deca[i]) { brojDeca++; indeks=i; }

    if (brojDeca != 1) return;

    Trie* dete = jazol->deca[indeks];
    jazol->oznaka.push_back(MAKEDONSKA_AZBUKA[indeks]);
    jazol->oznaka += dete->oznaka;

    for (int i=0; i<31; i++)
        jazol->deca[i] = dete->deca[i];

    jazol->krajNaZbor = dete->krajNaZbor;
    delete dete;
}

void pecatiTrie(Trie* jazol, string& tekoven) {
    if (!jazol) return;
    if (jazol->krajNaZbor) cout << tekoven << "\n";

    for (int i=0; i<31; i++) {
        if (jazol->deca[i]) {
            tekoven.push_back(MAKEDONSKA_AZBUKA[i]);
            pecatiTrie(jazol->deca[i], tekoven);
            tekoven.pop_back();
        }
    }
}

void pecatiPatricia(Trie* jazol, string& tekoven) {
    if (!jazol) return;
    tekoven += jazol->oznaka;
    if (jazol->krajNaZbor) cout << tekoven << "\n";

    for (int i=0; i<31; i++)
        if (jazol->deca[i])
            pecatiPatricia(jazol->deca[i], tekoven);

    tekoven.erase(tekoven.size() - jazol->oznaka.size());
}

bool prebarajTrie(Trie* koren, const string& zbor, map<char,int>& m) {
    Trie* tekoven = koren;
    for (char bukva : zbor) {
        bukva = tolower(bukva);
        if (!m.count(bukva)) return false;

        int indeks = m[bukva];
        if (!tekoven->deca[indeks]) return false;

        tekoven = tekoven->deca[indeks];
    }
    return tekoven->krajNaZbor;
}

bool prebarajPatricia(Trie* jazol, const string& zbor, map<char,int>& m, int pozicija=0) {
    if (!jazol) return false;
    int dolzinaOznaka = jazol->oznaka.size();
    if (zbor.size() - pozicija < dolzinaOznaka) return false;

    for (int i=0; i<dolzinaOznaka; i++)
        if (tolower(zbor[pozicija+i]) != jazol->oznaka[i]) return false;

    pozicija += dolzinaOznaka;
    if (pozicija == zbor.size()) return jazol->krajNaZbor;

    char sledna = tolower(zbor[pozicija]);
    if (!m.count(sledna)) return false;

    int indeks = m[sledna];
    return prebarajPatricia(jazol->deca[indeks], zbor, m, pozicija);
}

int main() {
    Trie* koren = new Trie();
    map<char,int> mapaBukvi = napraviMapa();

    string pateka = "MKRECNIK";
    ifstream datoteka(pateka);

    vector<string> zborovi;
    string linija;
    while (getline(datoteka, linija)) {
        if (linija.empty()) continue;
        if (linija[0] == '#') continue;
        zborovi.push_back(linija);
    }

    for (const auto& z : zborovi)
        dodadiVoTrie(koren, z, mapaBukvi);

    string temp;
    pecatiTrie(koren, temp);
    konvertirajPatricia(koren);
    pecatiPatricia(koren, temp);

    return 0;
}

