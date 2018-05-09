#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

// 입력이 32비트 부호 정수의 모든 값을 가질 수 있으므로 64비트가 필요함
const long long NEGINF = numeric_limits<long long>::min();
int n, m;
int cache[101][101];
int A[100], B[100];

int jlis(int indexA, int indexB) {
  int &ret = cache[indexA+1][indexB+1];
  if(ret != -1) return ret;
  
  ret = 0;
  long long a = (indexA == -1 ? NEGINF : A[indexA]);
  long long b = (indexB == -1 ? NEGINF : B[indexB]);
  long long maxElement = max(a, b);
  
  for (int nextA = indexA + 1; nextA < n; ++nextA) {
      if (maxElement < A[nextA]) {
          ret = max(ret, jlis(nextA, indexB)+1);
      }
  }
  for (int nextB = indexB + 1; nextB < m; ++nextB) {
      if (maxElement < B[nextB]) {
          ret = max(ret, jlis(indexA, nextB)+1);
      }
  }
  
  return ret;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--){
      scanf("%d %d", &n, &m);
      for(int i=0; i<n; scanf("%d", &A[i++]));
      for(int i=0; i<m; scanf("%d", &B[i++]));
      memset(cache, -1, sizeof(cache));
      printf("%d\n", jlis(-1, -1));
  }
}
