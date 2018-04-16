#include <iostream>
#include <string>

using namespace std;
char c[5][5];
string words[10];

bool find_word(string w) {
    int _p;
    int cache[10][5][5] = {0,};
    
    for (int a=0; a<w.length(); a++) {
        _p = 0;
        char t_c = w.at(a);
        char t_n = a==w.length()-1 ? '_' : w.at(a+1);
        for (int i=0; i<5; i++) {
            for (int j=0; j<5; j++) {
                if (c[i][j] == t_c) {
                    if (w.length() == 1) return true;
                    if (a>0) {
                        if (!cache[a-1][i][j]) continue;
                        else _p++;
                    }
                    for (int k=-1; k<2; k++) {
                        for (int l=-1; l<2; l++) {
                            if (i+k<0 || i+k>4 || j+l<0 || j+l>4 || (l==0 && k==0)) continue;
                            cache[a][i+k][j+l] = t_n == c[i+k][j+l];
                        }
                    }
                }
            }
        }
        if (a>0 && _p == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int w_t;
    int TC;
    cin >> TC;
    for (int t = 0; t<TC; t++) {
        for (int i = 0; i<5; i++) {
            for (int j=0; j<5; j++) {
                cin >>c[i][j];
            }
        }
        cin >> w_t;
        getline(cin, words[0]);
        for (int i=0; i<w_t; i++) {
            getline(cin, words[i]);
            if (find_word(words[i])) {
                cout << words[i] << " YES\n";
            } else {
                cout << words[i] << " NO\n";
            }
        }
    }
    return 0;
}
