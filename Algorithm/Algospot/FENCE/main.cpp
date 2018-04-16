#include <cstdio>
using namespace std;

int T;
int N;

int arr[20000] = {0,};

int max(int a, int b) {
  return a>b?a:b;
}

int min(int a, int b) {
  return a<b?a:b;
}

int getSize(int l, int r) {
  // 더이상 진행할 곳이없을때
  if (l==r) return arr[l];
  
  // 가운데 선정
  int m = (l+r)/2;
  
  // 반으로 나누어 진행
  int c = m;
  int n = m+1;
  int res = max(getSize(l, m), getSize(n, r));
  
  // 높이는 양쪽중 작은쪽으로
  int h = min(arr[c], arr[n]);
  
  // 기본값은 작은쪽 높이의 너비2의 곱
  res = max(res, 2*h);
  
  // 왼쪽과 오른쪽 칸을 비교해서 높이가 더 높은 쪽으로만 움직인다. 
  while(l < c || n < r) {
    if (n < r && (c == l || arr[c-1] < arr[n+1])) {
      h = min(h, arr[++n]);
    } else {
      h = min(h, arr[--c]);
    }
    // 넓이는 기본값과 움직였을때의 값을 비교해서 더 큰쪽이 결과가 된다.
    res = max(res, h*(n-c+1));
  }
  
  return res;
}

int main() {
  scanf("%d",&T);
  while(T--){
    scanf("%d",&N);
    for(int i=0; i<N; scanf("%d", &arr[i++]));
    printf("%d\n",getSize(0, N-1));
  }
}