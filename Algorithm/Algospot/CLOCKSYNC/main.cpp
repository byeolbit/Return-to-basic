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
