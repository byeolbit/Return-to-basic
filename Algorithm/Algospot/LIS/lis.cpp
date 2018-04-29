#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

// 1. 완전 탐색 알고리즘
int lis(vector<int> &S) {
  if (!S.size()) return 0;
  int ret = 0;
  for(int i=0; i<S.size(); ++i) {
    vector<int> sub;
    for(int j=i+1; j<S.size(); ++j) {
      if(S[i] < S[j]) {
        sub.push_back(S[j]);
      }
    }
    ret = max(ret,  1+lis(sub));
  }
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--){
    int n;
    scanf("%d", &n);
    vector<int> S;
    while(n--) {
      int t;
      scanf("%d", &t);
      S.push_back(t);
    }
    printf("%d\n", lis(S));
  }
}

