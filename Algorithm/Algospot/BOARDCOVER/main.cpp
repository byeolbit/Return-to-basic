#include <cstdio>
#include <array>
using namespace std;

int T;
int h,w;

// 놓는 방법에 대한 커버 프리셋
// 이를 이용해 보드판에 상대 경로로 겹쳐서 놓을 수 있는지 표시한다.
const int cover[4][3][2] = {
  {{0,0}, {1,0}, {0,1}},
  // xoo
  // xox  
  {{0,0}, {1,0}, {1,1}},
  // xox
  // xoo
  {{0,0}, {0,1}, {1,1}},
  // xoo
  // xxo
  {{0,0}, {1,0}, {1,-1}}
  // xox
  // oox
};

bool match(array<array <int, 20>, 20> &F, int x, int y, int t, int d) {
  bool r = true;
  for (int i = 0; i < 3; i++) {
    const int yy = y + cover[t][i][0];
    const int xx = x + cover[t][i][1];
    if (xx < 0 || xx >= w || yy < 0 || yy >= h) {
      r = false;
    } else if ((F[yy][xx] += d) > 1) {
      r = false;
    }
  }
  return r;
}

int find(array<array <int, 20>, 20> &F) {
  int r = 0;
  int x = -1, y = -1;
  for(int i=0; i<h; i++) {
    for(int j=0; j<w; j++) {
      if(F[i][j]==0) {
        x = j;
        y = i;
        break;
      }
    }
    if (y+1) break;
  }
  
  if(y==-1) {
    return 1;
     // 모든 경우의 수를 채웠으므로 1 반환
  }
  
  for(int t=0; t<4; t++) {
    if(match(F, x, y, t, 1)) {
      r += find(F);
    }
    match(F, x, y, t, -1);
    // 방금 놓은 조각을 무르는 것은, 다른 방법으로 조각을 두기 위함.
  }
  return r;
}

int main() {
  scanf("%d", &T);
  while(T--){
    int W = 0;
    array<array <int, 20>, 20> F;// board flag
    scanf("%d %d", &h, &w);
    for(int i=0; i<h; i++) {
      for(int j=0; j<w; j++) {
        char a;
        int b;
        scanf(" %c", &a);
        if (a=='#') {
          b=1;
        }
        else{
          W++;
          b=0;
        }
        F[i][j] = b;
        printf("%d",F[i][j]);
      }
      printf("\n");
    }
    if (W%3) {
      printf("0\n");
    } else {
      printf("%d\n", find(F));
    }
  }
}