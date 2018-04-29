#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

// 2. 메모이제이션 사용하기 

int n;
int cache[501], S[500] = {0,};

int lis(int start) {
  int &ret = &cache[start+1];
  if (ret != -1) return ret;

  ret = 1;
  for (int next = start+1; next < n; ++next) {
    if(start == -1 || S[start] < S[next]) {
      ret = max(ret, 1 + lis(next));
    }
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--){
    scanf("%d", &n);
    for(int i=-1; i<n; scanf("%d", S[++i]));
    memset(cache, -1, sizeof(cache));
    printf("%d\n", lis(-1)-1);
  }
}