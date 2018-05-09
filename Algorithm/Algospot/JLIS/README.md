### 문제

어떤 수열에서 0개 이상의 숫자를 지운 결과를 원 수열의 부분 수열이라고 부릅니다. 예를 들어 '4 7 6'은 '4 3 7 6 9'의 부분 수열입니다. 중복된 숫자가 없고 오름 차순으로 정렬되어 있는 부분 수열들을 가리켜 증가 부분 수열이라고 부르지요. 예를 들어 '3 6 9'는 앞의 수열의 증가 부분 수열입니다.

두 개의 정수 수열 A 와 B 에서 각각 증가 부분 수열을 얻은 뒤 이들을 크기 순서대로 합친 것을 합친 증가 부분 수열이라고 부르기로 합시다. 이 중 가장 긴 수열을 합친 LIS(JLIS, Joined Longest Increasing Subsequence)이라고 부릅시다. 예를 들어 '1 3 4 7 9' 은 '1 9 4' 와 '3 4 7' 의 JLIS입니다. '1 9' 와 '3 4 7' 을 합쳐 '1 3 4 7 9'를 얻을 수 있기 때문이지요.

A 와 B 가 주어질 때, JLIS의 길이를 계산하는 프로그램을 작성하세요.

### 입력

입력의 첫 줄에는 테스트 케이스의 수 c ( 1 <= c <= 50 ) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 A 와 B 의 길이 n 과 m 이 주어집니다 (1 <= n,m <= 100). 다음 줄에는 n 개의 정수로 A 의 원소들이, 그 다음 줄에는 m 개의 정수로 B 의 원소들이 주어집니다. 모든 원소들은 32비트 부호 있는 정수에 저장할 수 있습니다.

### 출력

각 테스트 케이스마다 한 줄에, JLIS 의 길이를 출력합니다.

### 예제 입력
```
3
3 3
1 2 4
3 4 7
3 3
1 2 3
4 5 6
5 3
10 20 30 1 2
10 20 30
```
### 예제 출력
```
5
6
5
```


### 코드
```cpp
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
```

LIS를 두 줄에 대해 구한다. 코드는 이전에 작성했던 lis코드와 비슷하다