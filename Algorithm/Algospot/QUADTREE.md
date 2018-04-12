## 문제

![image](http://algospot.com/media/judge-attachments/0cafdb9ffa8ace4fb8315949d25d2fb3/quadtree.png)

대량의 좌표 데이터를 메모리 안에 압축해 저장하기 위해 사용하는 여러 기법 중 쿼드 트리(quad tree)란 것이 있습니다. 주어진 공간을 항상 4개로 분할해 재귀적으로 표현하기 때문에 쿼드 트리라는 이름이 붙었는데, 이의 유명한 사용처 중 하나는 검은 색과 흰 색밖에 없는 흑백 그림을 압축해 표현하는 것입니다. 쿼드 트리는 2N × 2N 크기의 흑백 그림을 다음과 같은 과정을 거쳐 문자열로 압축합니다.

- 이 그림의 모든 픽셀이 검은 색일 경우 이 그림의 쿼드 트리 압축 결과는 그림의 크기에 관계없이 b가 됩니다.
- 이 그림의 모든 픽셀이 흰 색일 경우 이 그림의 쿼드 트리 압축 결과는 그림의 크기에 관계없이 w가 됩니다.
- 모든 픽셀이 같은 색이 아니라면, 쿼드 트리는 이 그림을 가로 세로로 각각 2등분해 4개의 조각으로 쪼갠 뒤 각각을 쿼드 트리 압축합니다. 이때 전체 그림의 압축 결과는 x(왼쪽 위 부분의 압축 결과)(오른쪽 위 부분의 압축 결과)(왼쪽 아래 부분의 압축 결과)(오른쪽 아래 부분의 압축 결과)가 됩니다. 예를 들어 그림 (a)의 왼쪽 위 4분면은 xwwwb로 압축됩니다.


그림 (a)와 그림 (b)는 16×16 크기의 예제 그림을 쿼드 트리가 어떻게 분할해 압축하는지를 보여줍니다. 이때 전체 그림의 압축 결과는 xxwww bxwxw bbbww xxxww bbbww wwbb가 됩니다.

쿼드 트리로 압축된 흑백 그림이 주어졌을 때, 이 그림을 상하로 뒤집은 그림 을 쿼드 트리 압축해서 출력하는 프로그램을 작성하세요.

### 입력

첫 줄에 테스트 케이스의 개수 C (C≤50)가 주어집니다. 그 후 C줄에 하나씩 쿼드 트리로 압축한 그림이 주어집니다. 모든 문자열의 길이는 1,000 이하이며, 원본 그림의 크기는 220 × 220 을 넘지 않습니다.

### 출력

각 테스트 케이스당 한 줄에 주어진 그림을 상하로 뒤집은 결과를 쿼드 트리 압축해서 출력합니다.

#### 예제 입력
```
4
w
xbwwb
xbwxwbbwb
xxwwwbxwxwbbbwwxxxwwbbbwwwwbb
```
#### 예제 출력
```
w
xwbbw
xxbwwbbbw
xxwbxwwxbbwwbwbxwbwwxwwwxbbwb
```

## 문제접근

### 나이브한 생각
1. 받아들인 문자열의 압축을 푼다.
2. 압축을 푼 좌표계의 위치를 뒤집는다.
3. 다시 압축한다.

### 의도를 생각해보면

압축을 완전히 다푸는것은 메모리를 너무 많이 차지하고, 시간이 너무 오래걸린다. 문제의 의도를 생각해본다면 압축을 전부 풀지않고도 뒤집힌 좌표계를 표현할 수 있을것.

조금 더 작은 그림의 예제를 생각해보자.

```
xbwxwbbwb
```
위를 그림으로 나타내면..

![tree.png](/files/2191690098208600118)
 
 뒤집으면..
![tree2.png](/files/2191691554899462046)

압축된 문자열은...
```
xxbwwbbbw
```

즉 이문제는 다음의 두 로직의 재귀로 종결될 수 있음을 생각해볼 수 있다.

1. 각 네 좌표의 칸 내부를 뒤집는다.
2. 뒤집은 네 좌표의 상하를 바꾼 값을 돌려준다.

두 로직을 가진 함수를 만들어 재귀호출 시키면 문제 해결!

```cpp
#include <iostream>
#include <string>
using namespace std;

string reverse(string::iterator &it) {
  char h = *it;
  ++it;
  if(h=='b' || h=='w') {
    return string(1, h);
  }
  string a = reverse(it);
  string b = reverse(it);
  string c = reverse(it);
  string d = reverse(it);
  
  return string("x")+c+d+a+b;
}

int main() {
  int T;
  cin >> T;
  string q;
  while(T--) {
    cin >> q;
    string::iterator it = q.begin();
    cout << reverse(it) << endl;
  }
}
```


