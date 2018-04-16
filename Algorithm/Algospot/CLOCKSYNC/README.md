## 문제

그림과 같이 4 x 4 개의 격자 형태로 배치된 16개의 시계가 있다. 이 시계들은 모두 12시, 3시, 6시, 혹은 9시를 가리키고 있다. 이 시계들이 모두 12시를 가리키도록 바꾸고 싶다.

시계의 시간을 조작하는 유일한 방법은 모두 10개 있는 스위치들을 조작하는 것으로, 각 스위치들은 모두 적게는 3개에서 많게는 5개의 시계에 연결되어 있다. 한 스위치를 누를 때마다, 해당 스위치와 연결된 시계들의 시간은 3시간씩 앞으로 움직인다. 스위치들과 그들이 연결된 시계들의 목록은 다음과 같다.
|스위치| 시계 |
|--|--|
0|	0, 1, 2
1|	3, 7, 9, 11
2|	4, 10, 14, 15
3|	0, 4, 5, 6, 7
4|	6, 7, 8, 10, 12
5|	0, 2, 14, 15
6|	3, 14, 15
7|	4, 5, 7, 14, 15
8|	1, 2, 3, 4, 5
9|	3, 4, 5, 9, 13
시계들은 맨 윗줄부터, 왼쪽에서 오른쪽으로 순서대로 번호가 매겨졌다고 가정하자. 시계들이 현재 가리키는 시간들이 주어졌을 때, 모든 시계를 12시로 돌리기 위해 최소한 눌러야 할 스위치의 수를 계산하는 프로그램을 작성하시오.

### 입력

첫 줄에 테스트 케이스의 개수 C (<= 30) 가 주어진다. 
각 테스트 케이스는 한 줄에 16개의 정수로 주어지며, 각 정수는 0번부터 15번까지 각 시계가 가리키고 있는 시간을 12, 3, 6, 9 중 하나로 표현한다.

### 출력

각 테스트 케이스당 한 줄을 출력한다. 시계들을 모두 12시로 돌려놓기 위해 눌러야 할 스위치의 최소 수를 출력한다. 만약 이것이 불가능할 경우 -1 을 출력한다.

### 예제 입력
```
2
12 6 6 6 6 6 12 12 12 12 12 12 12 12 12 12 
12 9 3 12 6 6 9 3 12 9 12 9 12 12 6 6
```

### 예제 출력
```
2
9
```

## 문제 접근

1. 0번부터 9번까지, 스위치를 순차적으로 순회한다.
2. 기저탐색은 다음과 같이 이루어진다.
    1. 스위치를 1~3번까지 누른다.
    2. 각 누르는 횟수에 대해 다음 스위치를 파라미터로 재귀호출을 한다.
    3. 만약 호출되었을 때 남아있는 시계가 없다면 0을 리턴,
    4. 9번스위치까지 다 눌렀는데 3이 성립하지 않는다면 무한대 리턴.
    5. 다시 재귀적으로 얻어진 각 결과중에서 가장 작은 값을 리턴한다.
3. 기저탐색이 끝나면 결과를 리턴한다.


```cpp
#include <cstdio>
#include <array>
using namespace std;

int T;
const int INF = 99999999;

const int s[10][6] = {
    {0,1,2,-1},
    {3,7,9,11,-1},
    {4,10,14,15,-1},
    {0,4,5,6,7,-1},
    {6,7,8,10,12,-1},
    {0,2,14,15,-1},
    {3,14,15,-1},
    {4,5,7,14,15,-1}, 
    {1,2,3,4,5,-1},
    {3,4,5,9,13,-1}
};

void push(array<int, 16> &c, int n) {
  for(int i=0; s[n][i]+1; ++i) {
    c[s[n][i]]-3 ? c[s[n][i]]++ : c[s[n][i]]=0;
  }
}

int check(array<int, 16> &c) {
  int r=0;
  for(int i=-1; i<15 && r-1; (r+=c[++i]));
  return !r;
}

int min(int a, int b) {
  return a>b?b:a;
}

int find(array<int, 16> &c, int p) {
  
  if(check(c)) return 0;
  if(p==10) return INF;
  int r = INF;
  for(int i=0; i<4; i++) {
    r = min(r, i + find(c, p+1));
    push(c, p);
  }
  return r;
}

int main() {
  scanf("%d", &T);
  while(T--){
    array<int, 16> t;
    for(int i=0; i<16; i++) {
      int a=0;
      scanf("%d", &a);
      t[i] = a/3;
      if(t[i]==4) t[i]=0;
    }
    int r = find(t, 0);
    printf("%d\n",r==INF?-1:r);
  }
  return 0;
}
```
문제의 의도가 완전 탐색이라면, 어마어마하게 시간이 걸리지만, 시계의 특성을 이용하면 훨씬 빠르게 풀어낼 수 있다. 스위치와 시계의 관계를 다시 뜯어보면, 페어를 확인할수 있다.

`8-12` 라던가, `9-13`, `14-15`처럼 처음부터 둘이 같지 않으면 절대 문제를 풀 수 없는 조건들이 존재한다.
해당 스위치를 눌러서 가능한 스위치를 제거해 나가면 스위치의 목록을 한 번 순회하는 것으로 문제를 풀 수 있게된다.

```cpp
#include <cstdio>
#include <array>
using namespace std;

int T;

const int COUNT[4] = {0,3,2,1};
const int s[10][6] = {
  {0,1,2,-1},
  {3,7,9,11,-1},
  {4,10,14,15,-1},
  {0,4,5,6,7,-1},
  {6,7,8,10,12,-1},
  {0,2,14,15,-1},
  {3,14,15,-1},
  {4,5,7,14,15,-1}, 
  {1,2,3,4,5,-1},
  {3,4,5,9,13,-1}
};
const int SWITCH[10] = {1,11,10,6,8,0,3,7,4,9};
const int CLOCK[10] = {1,4,9,2,3,7,8,6,0,5};

int _push(array<int, 16> &c, int n) {
  int m = SWITCH[n];
  int loop = COUNT[c[m]];
  int r = loop;
  while(loop--){
    for(int i=0; s[n][i]+1; ++i) {
      c[s[n][i]]-3 ? c[s[n][i]]++ : c[s[n][i]]=0;
    }
  }
  return r;
}

int _find(array<int, 16> &t) {
  int p = 0;
  for (int i=0; i<10; i++) {
    switch (SWITCH[CLOCK[i]]) {
      case 0:
        if (t[0]!=t[2] || t[2]!=t[14] || t[14]!=t[15] || t[0]!=t[15]) {
          return -1;
        }
        break;
      case 4:
        if(t[4] != t[5]) {
          return -1;
        }
        break;
      case 8:
        if (t[8] != t[12] || t[14] != t[15]) {
          return -1;
        }
        break;
      case 9:
        if (t[9] != t[13]) {
          return -1;
        }
        break;
      default:
        break;
    }
    p += _push(t, CLOCK[i]);
  }
  return p;
}

int main() {
  scanf("%d", &T);
  while(T--){
    array<int, 16> t;
    for(int i=0; i<16; i++) {
      int a=0;
      scanf("%d", &a);
      t[i] = a/3;
      if(t[i]==4) t[i]=0;
    }
    printf("%d\n",_find(t));
  }
  return 0;
}

```