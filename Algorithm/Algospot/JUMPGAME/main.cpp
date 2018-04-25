#include <cstdio>
#include <cstring>
using namespace std;

int n, board[100][100];
int cache[100][100];

int jump(int y, int x) {
    // 기저 사례1 : 게임판 밖을 벗어난 경우
    if( y>= n || x >= n ) return 0;
    // 기저 사레2 : 게임판 마지막 칸에 도착한 경우
    if (y == n-1 && x==n-1) return 1;
    
    // 메모이제이션
    int &ret = cache[y][x];
    if(ret != -1) return ret;
  
    // 그 외에는 오른쪽과 아래로 재귀적으로 탐색
    int jumpSize = board[y][x];
    return ret = (jump(y + jumpSize, x) || jump(y, x + jumpSize));
}

int main() {
  int T;
  scanf("%d\n", &T);
  while(T--){
    memset(cache, -1, sizeof(cache));
    scanf("%d\n", &n);
    for(int i=0; i<n; i++) {
      for(int j=0; j<n; j++) {
        scanf("%d", &board[i][j]);
      }
    }
    printf("%s\n", jump(0, 0)?"YES":"NO");
  }
}

