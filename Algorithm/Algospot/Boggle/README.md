# 보글

![image](http://algospot.com/media/judge-attachments/09ee7a6e752f07b0d99b82a010938ab4/boggle.png)

## 문제

보글(Boggle) 게임은 그림 (a)와 같은 5x5 크기의 알파벳 격자인 
게임판의 한 글자에서 시작해서 펜을 움직이면서 만나는 글자를 그 순서대로 나열하여 만들어지는 영어 단어를 찾아내는 게임입니다. 펜은 상하좌우, 혹은 대각선으로 인접한 칸으로 이동할 수 있으며 글자를 건너뛸 수는 없습니다. 지나간 글자를 다시 지나가는 것은 가능하지만, 펜을 이동하지않고 같은 글자를 여러번 쓸 수는 없습니다.

예를 들어 그림의 (b), (c), (d)는 각각 (a)의 격자에서 PRETTY, GIRL, REPEAT을 찾아낸 결과를 보여줍니다.

보글 게임판과 알고 있는 단어들의 목록이 주어질 때, 보글 게임판에서 각 단어를 찾을 수 있는지 여부를 출력하는 프로그램을 작성하세요.

### 입력

입력의 첫 줄에는 테스트 케이스의 수 C(C <= 50)가 주어집니다. 각 테스트 케이스의 첫 줄에는 각 5줄에 5글자로 보글 게임판이 주어집니다. 게임판의 모든 칸은 알파벳 대문자입니다.
그 다음 줄에는 우리가 알고 있는 단어의 수 N(1 <= N <= 10)이 주어집니다. 그 후 N줄에는 한 줄에 하나씩 우리가 알고 있는 단어들이 주어집니다. 각 단어는 알파벳 대문자 1글자 이상 10글자 이하로 구성됩니다.

### 출력

각 테스트 케이스마다 N줄을 출력합니다. 각 줄에는 알고 있는 단어를 입력에 주어진 순서대로 출력하고, 해당 단어를 찾을 수 있을 경우 YES, 아닐 경우 NO를 출력합니다.

## 문제 접근

이 문제는 어떻게 나눌 수 있을까?
1. 글자판에 현재 찾고자 하는 단어의 글자가 있는가?
2. 있다면 다음에 이어지는 글자가 있는가?
의 두가지 문제로 나눌 수 있다.

선형적으로 앞으로 나이브하게 풀어나가면 다음과 같은 문제가 발생한다.

같은 글자밖에 없는 판에서 없는글자가 제일 마지막에 나왔을때! 시간복잡도가 어마무지하게 올라간다.

보자마자 나이브 하게 풀었다가 시간초과 만났다.. OTL..

### 이렇게 접근

단어가 만약 PRETTY로 주어진다고 하면,

P, R, E, T, T, Y 총 여섯번, `각 글자가 이전글자와 다음 글자를 찾을 수 있는지` 체크를 돌린다.

즉 P는 다음에 R이 포함되는 칸이 있는지 확인해야 하고
R은 주변에 P와 E를 포함하고 있는지 봐야 한다.

단어중 글자를 순차적으로 찾아가며 만약 한 글자라도 조건을 만족하지 못한다면 false!

그런 부분이 없다면, 서로 겹치는 부분끼리 연결하여 꼬리를 물도록 엮는다. 모두가 겹치도록 할 수 있는 조합을 찾을 수 없다면 false!

i가 0이라면 prev = null
i+1이 outof bound라면 next = null

다음 예제에서 
데이터는 다음과 같을 것이다.
```
1
URLPM
XPRET
GIAET
XTNZY
XOQRS
1
PRETTY

P : {
    3: { prev: null, next: [7] },
    6: { prev: null, next: [7] }
},
R : {
    7: { prev: [3,6], next: [8,13] },
    23: { prev: [], next: [] } // 탈락!
},
E : {
    8: {prev: [7], next: [9, 14]},
    13: {prev: [7]. next: [9, 13]}
},
T : {
    9: {prev: [8, 13]. next: [14]},
    14: {prev: [8, 13], next: [9]}.
    16: {prev: [], next: []} // 탈락!
},
T : {
    9: {prev: [14], next: []},
    14: {prev: [9], next: [19]},
    16: {prev: [], next: []} // 탈락!
},
Y : {
    19: {prev: [14], next: null}
}   
```

탈락인 항목들을 제거해도 모든 단어에 선택지가 남아있다.

단어의 완성을 따지므로, 제일 마지막단어부터 역순으로 추적해 올라간다.

1. 이전 글자의 목록에 현재 prev와 일치하는것이 있는가?
2. 1을 충족한다면, 그 글자가 현재 글자가 된다.
3. 1을 충족하지 못하면 목록중 다른 글자로 찾아가서 1을 한다.
4. 목록을 모두 돌아도 적절한 것을 찾을 수 없었다면 단어 찾기 실패
5. 끝까지 찾아가서 prev가 null인 글자를 찾으면 단어 찾기 성공!

..은 fail

시간초과가 나와버렸다.

이 방법에는 지대한 문제가 있는데, 이미 한 일을 두 번 한다는 것이다... 굳이 역순으로 추적해 올라갈 필요가 없다.

애초에 글자를 찾을때 앞뒤가 연결되는 단어인지를 찾으면서 행동하면 시간을 줄일 수 있을것이라 생각했고 생각대로 시간제한을 이겨내는데 성공했다.

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
int w_t[50];
char c[50][25];
string words[50][10];

bool find_word(int tc, string w);

int main() {
    int TC;
    cin >> TC;
    for (int t = 0; t<TC; t++) {
        for (int i = 0; i<25; i++) {
            cin >> c[t][i];
        }
        
        cin >> w_t[t];
        getline(cin, words[t][0]);
        for (int i=0; i<w_t[t]; i++) {
            getline(cin, words[t][i]);
            if (find_word(t, words[t][i])) {
                cout << words[t][i] << " YES\n";
            } else {
                cout << words[t][i] << " NO\n";
            }
        }
    }
}

bool move_up(int i) {
    return i-5 >= 0;
}

bool move_left(int i) {
    return (i-1)%5 != 4;
}

bool move_right(int i) {
    return (i+1)%5 != 0;
}

bool move_down(int i) {
    return (i+5) < 25;
}

bool find_word(int tc, string w) {
    vector<vector<int>> pos;
    vector<vector<vector<int>>> P, N;
    char temp_c;
    char temp_p;
    char temp_n;
    
    for (int a=0; a<w.length(); a++) {
        vector<vector<int>> prev, next;
        temp_c = w.at(a);
        temp_p = a==0 ? '_' : w.at(a-1);
        temp_n = a==w.length()-1 ? '_' : w.at(a+1);
        vector<int> _pos;
        for (int i=0; i<25; i++) {
            if (c[tc][i] == temp_c) {
                if(a>0) {
                    bool _c = true;
                    for (int _i=0; _i<N[a-1].size(); _i++) {
                        if (find(N[a-1][_i].begin(), N[a-1][_i].end(), i) != N[a-1][_i].end()) {
                            _c = false;
                            break;
                        }
                    }
                    if (_c == true) {
                        continue;
                    }
                }
                vector<int> _prev;
                vector<int> _next;
                if (move_up(i)) {
                    if (temp_p == c[tc][i-5]) {
                        _prev.push_back(i-5);
                    }
                    if (temp_n == c[tc][i-5]) {
                        _next.push_back(i-5);
                    }
                    if (move_left(i-5)) {
                        if (temp_p == c[tc][i-6]) {
                            _prev.push_back(i-6);
                        }
                        if (temp_n == c[tc][i-6]) {
                            _next.push_back(i-6);
                        }
                    }
                    if (move_right(i-5)) {
                        if (temp_p == c[tc][i-4]) {
                            _prev.push_back(i-4);
                        }
                        if (temp_n == c[tc][i-4]) {
                            _next.push_back(i-4);
                        }
                    }
                }
                if (move_right(i)) {
                    if (temp_p == c[tc][i+1]) {
                        _prev.push_back(i+1);
                    }
                    if (temp_n == c[tc][i+1]) {
                        _next.push_back(i+1);
                    }
                }
                if (move_down(i)) {
                    if (temp_p == c[tc][i+5]) {
                        _prev.push_back(i+5);
                    }
                    if (temp_n == c[tc][i+5]) {
                        _next.push_back(i+5);
                    }
                    if (move_right(i+5)) {
                        if (temp_p == c[tc][i+6]) {
                            _prev.push_back(i+6);
                        }
                        if (temp_n == c[tc][i+6]) {
                            _next.push_back(i+6);
                        }
                    }
                    if (move_left(i+5)) {
                        if (temp_p == c[tc][i+4]) {
                            _prev.push_back(i+4);
                        }
                        if (temp_n == c[tc][i+4]) {
                            _next.push_back(i+4);
                        }
                    }
                }
                if (move_left(i)) {
                    if (temp_p == c[tc][i-1]) {
                        _prev.push_back(i-1);
                    }
                    if (temp_n == c[tc][i-1]) {
                        _next.push_back(i-1);
                    }
                }
                if (_prev.size() > 0 && _next.size() > 0) {
                    _pos.push_back(i);
                    prev.push_back(_prev);
                    next.push_back(_next);
                } else if (temp_p == '_' && _next.size() > 0) {
                    _pos.push_back(i);
                    next.push_back(_next);
                } else if (temp_n == '_' && _prev.size() > 0) {
                    _pos.push_back(i);
                    prev.push_back(_prev);
                } else if (w.length() == 1) {
                    return true;
                }
            }
        }
        if (_pos.size() > 0) {
            pos.push_back(_pos);
            P.push_back(prev);
            N.push_back(next);
        } else {
            return false;
        }
    }
    return true;
}
```

### 풀기는 풀었는데.. 이건 좀...

너무나 필요 이상으로 복잡하고 무식하게 푸는것 같다.. 조금더 심플하게 생각 할 수 있을 것 같았다.

다시 심플하게 처음으로 돌아가서 생각해보자. 내가 처음 생각했던 문제의 풀이는
```
1. 글자판에 현재 찾고자 하는 단어의 글자가 있는가?
2. 있다면 다음에 이어지는 글자가 있는가?
```
두 단계의 문제이다.

왜인지 그대로 풀려고 하지 않고 너무 복잡하게 문제를 구조화 해버렸다.

저대로만 푼다고 생각해봤을 때
```
1. 현재 찾은 글자가 바로 이전에 다음 글자로 나온 글자인가?
2. 그렇다면 다음에 이어지는 글자가 있는가?
```
정말 심플하다..

잘 생각해보면... 처음에 글자를 찾아 갈 때, 애초에 바로 전 글자에서 찾은 next와 겹치지 않을때는 제외해 버리면 prev를 사용할 필요가 없다.

이중 벡터를 쓰는 대신에 오로지 필요한 것은 next뿐이므로, 이를 찾은 결과를 저장할 2차원 배열을 쓰면 벡터나 알고리즘 라이브러리도 전혀 필요가 없어진다.

불필요한 부분들을 쳐내고 다듬었다.

```cpp
#include <iostream>
#include <string>

using namespace std;
char c[25];
string words[10];

bool find_word(string w);

int main() {
    int w_t;
    int TC;
    cin >> TC;
    for (int t = 0; t<TC; t++) {
        for (int i = 0; i<25; i++) {
            cin >> c[i];
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

int move_up(int i) {
    return i-5 >= 0;
}

int move_left(int i) {
    return (i-1)%5 != 4;
}

int move_right(int i) {
    return (i+1)%5 != 0;
}

int move_down(int i) {
    return (i+5) < 25;
}

bool find_word(string w) {
    int _pos;
    int cache[10][25] = {0,};
    
    for (int a=0; a<w.length(); a++) {
        _pos = 0;
        char temp_c = w.at(a);
        char temp_n = a==w.length()-1 ? '_' : w.at(a+1);
        for (int i=0; i<25; i++) {
            if (c[i] == temp_c) {
                if (w.length() == 1) {
                    return true;
                }
                if (a>0) {
                    if (cache[a-1][i] == 0) {
                        continue;
                    } else {
                        _pos++;
                    }
                }
                if (move_up(i)) {
                    cache[a][i-4] = temp_n == c[i-4] && move_right(i-5);
                    cache[a][i-5] = temp_n == c[i-5];
                    cache[a][i-6] = temp_n == c[i-6] && move_left(i-5);
                }
                if (move_right(i)) {
                    cache[a][i+1] = temp_n == c[i+1];
                }
                if (move_down(i)) {
                    cache[a][i+4] = temp_n == c[i+4] && move_left(i+5);;
                    cache[a][i+5] = temp_n == c[i+5];
                    cache[a][i+6] = temp_n == c[i+6] && move_right(i+5);;
                }
                if (move_left(i)) {
                    cache[a][i-1] = temp_n == c[i-1];
                }
            }
        }
        if (a>0 && _pos == 0) {
            return false;
        }
    }
    return true;
}
```

첫 풀이에 비해서 7배 가까이 단축할 수 있었다.

### + 2차원 배열 사용ver

```cpp
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

```

### 책에서는 이렇게

6장에서는 완전 탐색 방법으로 문제를 해결할 수 있다고 소개하고 있다.
하지만 내가 문제를 보자마자 바로 풀어낸 방법이 완전 탐색 방법이었고, 이는 시간초과로 이어졌다.
알고스팟 문제를 보면 8장의 동적 계획법을 참고하라고 되어있다.
메모이제이션을 활용해서 푼다고 하면 된다고 한다.

아직 동적계획법과 메모이제이션이 무엇인지 잘 모르겠어서 해당 부분을 읽어보고 풀어봐야 할듯.
