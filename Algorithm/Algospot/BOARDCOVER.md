## 문제

![image](http://algospot.com/media/judge-attachments/2b7bfee35cbec2f4e799bb011ac18f69/03.png)

H*W 크기의 게임판이 있습니다. 게임판은 검은 칸과 흰 칸으로 구성된 격자 모양을 하고 있는데 이 중 모든 흰 칸을 3칸짜리 L자 모양의 블록으로 덮고 싶습니다. 이 때 블록들은 자유롭게 회전해서 놓을 수 있지만, 서로 겹치거나, 검은 칸을 덮거나, 게임판 밖으로 나가서는 안 됩니다. 위 그림은 한 게임판과 이를 덮는 방법을 보여줍니다.

게임판이 주어질 때 이를 덮는 방법의 수를 계산하는 프로그램을 작성하세요.

### 입력

력의 첫 줄에는 테스트 케이스의 수 C (C <= 30) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 2개의 정수 H, W (1 <= H,W <= 20) 가 주어집니다. 다음 H 줄에 각 W 글자로 게임판의 모양이 주어집니다. # 은 검은 칸, . 는 흰 칸을 나타냅니다. 입력에 주어지는 게임판에 있는 흰 칸의 수는 50 을 넘지 않습니다.

### 출력

한 줄에 하나씩 흰 칸을 모두 덮는 방법의 수를 출력합니다.

## 접근 방법

1. 흰 칸의 갯수가 3의 배수가 아니면 무조건 채울 수 없다. (블록은 무조건 3칸 단위로 채워지기 때문에)
2. 보드의 첫 칸부터 순회를 시작한다. 1은 채운칸, 0은 채우지 않은칸. 0을 만나면 매치를 해본다.
3. 기준 칸에 대한 매치는 다음의 네 종류로 생각해볼 수 있다.

```
xoo
xox 

xox
xoo

xoo
xxo
  
xox
oox
```
4. 각 매치에 대해서 일치하면 다시 자기 자신을 불러내어 해당 매치에 대해 찾아, 제일 첫 빈칸부터 다시또 매칭을 해나간다. 이 과정을 반복함으로써 모든 경우에 대한 탐색이 가능해진다.
5. 위 로직에서 제일 마지막에 다다른 경우는 모든 배열을 탐색하고도 0으로 남아있는 칸이 없을때 이다. 이때 1을 반환한다. 그렇지 않은 경우에 대해서는 0을 반환.

## 코드 
```cpp
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
```


