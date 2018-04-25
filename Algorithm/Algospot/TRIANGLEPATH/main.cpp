#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

int h;
int T[100][100];
int cache[100][100];

int path(int y, int x) {
  if (y == h-1) {
    return T[y][x];
  }
  int &ret = cache[y][x];
  if(ret != -1) {
    return ret;
  }
  return ret = max(path(y+1, x), path(y+1, x+1)) + T[y][x];
}

int main() {
  int TC;
  scanf("%d", &TC);
  while(TC--) {
    scanf("%d", &h);
    memset(cache, -1, sizeof(cache));
    for(int i=0; i<h; ++i) {
      for(int j=0; j<=i; ++j) {
        scanf("%d", &T[i][j]);
      }
    }
    printf("%d\n", path(0,0));
  }
}