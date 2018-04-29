#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

// 2. nlogn 해법

int n;
int C[500], S[500] = {0,};

int lis(int start) {

  int res = 0;
  for(int i=0; i<n; ++i) {
    int current = S[i];

    if(res == 0 || C[res-1] < current) {
      C[res++] = current;
    } else {
      C[binary(res, current)] = current;
    }
  }
  return res;
}

int binary(int res, int current) {
  int left = 0;
  int right = res-1;

  while(left <= right) {
    int mid = (right + left)/2;
    if(C[mid] < current) {
      left = mid+1;
    } else {
      right = mid-1;
    }
  }

  return left;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--){
    scanf("%d", &n);
    for(int i=0; i<n; scanf("%d", S[i++]));
    memset(C, 0, sizeof(C));
    printf("%d\n", lis(0));
  }
}