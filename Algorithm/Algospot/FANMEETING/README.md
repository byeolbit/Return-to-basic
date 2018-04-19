### 문제

가장 멤버가 많은 아이돌 그룹으로 기네스 북에 올라 있는 혼성 팝 그룹 하이퍼시니어가 데뷔 10주년 기념 팬 미팅을 개최했습니다. 팬 미팅의 한 순서로, 멤버들과 참가한 팬들이 포옹을 하는 행사를 갖기로 했습니다. 하이퍼시니어의 멤버들은 우선 무대에 일렬로 섭니다. 팬 미팅에 참가한 M명의 팬들은 줄을 서서 맨 오른쪽 멤버에서부터 시작해 한 명씩 왼쪽으로 움직이며 멤버들과 하나씩 포옹을 합니다. 모든 팬들은 동시에 한 명씩 움직입니다. 아래 그림은 행사 과정의 일부를 보여줍니다. a~d는 네 명의 하이퍼시니어 멤버들이고, 0~5는 여섯 명의 팬들입니다.

![image](http://algospot.com/media/judge-attachments/bcbb33d48baf27a4347cf09608aece35/Screenshot%20from%202013-01-14%2022%3A31%3A18.png)

하지만 하이퍼시니어의 남성 멤버들이 남성 팬과 포옹하기가 민망하다고 여겨서, 남성 팬과는 포옹 대신 악수를 하기로 했습니다. 줄을 선 멤버들과 팬들의 성별이 각각 주어질 때 팬 미팅이 진행되는 과정에서 하이퍼시니어의 모든 멤버가 동시에 포옹을 하는 일이 몇 번이나 있는지 계산하는 프로그램을 작성하세요.

#### 입력

첫 줄에 테스트 케이스의 개수 C (C≤20)가 주어집니다. 각 테스트 케이스는 멤버들의 성별과 팬들의 성별을 각각 나타내는 두 줄의 문자열로 구성되어 있습니다. 각 문자열은 왼쪽부터 오른쪽 순서대로 각 사람들의 성별을 나타냅니다.

M은 해당하는 사람이 남자, F는 해당하는 사람이 여자임을 나타냅니다. 멤버의 수와 팬의 수는 모두 1 이상 200,000 이하의 정수이며, 멤버의 수는 항상 팬의 수 이하입니다.

#### 출력

각 테스트 케이스마다 한 줄에 모든 멤버들이 포옹을 하는 일이 몇 번이나 있는지 출력합니다.

예제 입력
```
4
FFFMMM
MMMFFF
FFFFF
FFFFFFFFFF
FFFFM
FFFFFMMMMF
MFMFMFFFMMMFMF
MMFFFFFMFFFMFFFFFFMFFFMFFFFMFMMFFFFFFF
```
예제 출력
```
1
6
2
2
```

### 접근 방법

문제를 시간제한내에 풀기 위해서는 사전지식이 필요함.
절대로 나이브한 방법으로는 시간제한내에 해결할 수 없다.

멤보와 팬의 정보를 2진수로 보고 각 곱셈에 대한 결과라고 생각한다면 0이 나오는 갯수를 셀 때 동시에 포옹하는 횟수를 구할 수 있게 된다.

하지만 단순 곱셈을 한다고 하더라도, 20만이나 되는 길이의 수의 곱의 수행은 가능하지 않다. 무식하게 곱셈을 하면 최대 20만의 제곱에 해당하는 시간복잡도가 걸리게 된다.

즉 이문제는 곱셈을 빠르게 풀어낼 수 있느냐가 관건인데, 책에서는 카라츠바 알고리즘을 통한 구현을 제안하고 있다.

다음은 위키백과 에서 설명하고 있는 카라츠바 알고리즘의 원리다.

카라추바 알고리즘의 기본 단계는 큰 두 수 x와 y의 곱을 자릿수가 x, y의 절반인 수들의 곱 3번과 덧셈과 시프트 연산을 이용해 계산하는 것이다.

x와 y를 B진법의 n자리수라고 하자. n보다 작은 양수 m에 대해 다음과 같이 x, y를 쪼갤 수 있다.
```
x = x1Bm + x0
y = y1Bm + y0(단, x0과 y0는 Bm보다 작다.)

z2 = x1y1
z1 = x1y0 + x0y1
z0 = x0y0

라고 할 때, x와 y의 곱은

xy = (x1Bm + x0)(y1Bm + y0)
= z2 B2m + z1 Bm + z0

이 식은 4번의 곱셈을 해야한다. 카라추바는 덧셈을 몇 번 함으로써, xy를 3번의 곱셈을 통해 구할 수 있다는 걸 알았다.

z2 = x1y1 라 하자.
z0 = x0y0 라 하자.
z1 = (x1y1 + x1y0 + x0y1 + x0y0) - x1y1 - x0y0 = x1y0 + x0y1
이므로

z1 = (x1 + x0)(y1 + y0) − z2 − z0 라 할 수 있다.
```

카라츠바 알고리즘을 통해서 곱셈의 시간복잡도를 O(n^lg3)으로 줄일 수 있다.

이 문제에서는 노말라이즈 과정이 필요없다. 0과 1의 계산만 이루어지기 때문. 
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> multiply(const vector<int> &a, const vector<int> &b) {
  vector<int> c(a.size() + b.size() + 1, 0);
  for(int i=0; i<a.size(); ++i){
    for(int j=0; j<b.size(); ++j){
      c[i+j] += a[i] * b[j];
    }
  }
  return c;
}

void addTo(vector<int> &a, const vector<int> &b, int k){
  int length = b.size();
	a.resize(max(a.size(), b.size()+k));  
	for (int i=0; i<length; ++i){
		a[i+k] += b[i];
	}
}

void subFrom(vector<int> &a, const vector<int> &b) {
  int length = b.size();
	a.resize(max(a.size(), b.size())+1);
	for(int i=0; i<length; ++i){
		a[i] -= b[i]; 
	}
}

vector<int> karatsuba(vector<int>& a, vector<int>& b){
	int an = a.size(), bn = b.size(); 
	// a가 b보다 짧을경우, 둘을 바꾼다. 
	if (an < bn)
	  return karatsuba(b,a);
  // 기저사례: a나 b가 비어있을 때
	if (an == 0 || bn == 0)
	  return vector<int>(); 
	// 기저사례: a가 비교적 짧을 때는 일반 곱셈으로 변경 
	if (an <= 50)
	  return multiply(a,b);  
	int half = an/2; 
	// a와 b를 밑에서 half자리와 나머지로 분리한다.
	vector<int> a0(a.begin(),a.begin()+half); 
	vector<int> a1(a.begin()+half, a.end()); 
	vector<int> b0(b.begin(),b.begin()+min<int>(b.size(), half));  
	vector<int> b1(b.begin()+min<int>(b.size(), half),b. end());  
	// z2 = a1*b1 
	vector<int> z2 = karatsuba(a1,b1); 
	// z0 = a0*b0 
	vector<int> z0 = karatsuba(a0,b0); 
	// a0 = a0 + a1, b0 = b0 + b1 update 
	addTo(a0,a1,0); 
	addTo(b0,b1,0); 
	// z1 = (a0*b0)-z0-z1 
	vector<int> z1 = karatsuba(a0,b0); 
	subFrom(z1,z0); 
	subFrom(z1,z2); 
	// ret = z0 + z1*10^half + z2*10^(half*2) 
	vector<int> ret; 
	addTo(ret,z0,0); 
	addTo(ret,z1,half); 
	addTo(ret,z2,half+half); 
	
	return ret; 
}

int meeting(string &mem, string &fan) {
  int m_size = mem.size(), f_size = fan.size();
  vector<int> m(m_size), f(f_size);
  
  for(int i=-1; ++i<m_size; (m[i]=(mem[i]=='M')));
  for(int i=-1; ++i<f_size; (f[f_size-i-1]=(fan[i]=='M')));
  
  vector<int> r = karatsuba(m, f);
  int sum=0;
  for(int i=m_size-1; i<f_size; ++i) {
    if(r[i]==0) {
      ++sum;
    }
  }
  return sum;
  
}

int main() {
  int T;
  scanf("%d\n", &T);
  while(T--) {
    string m;
    string f;
    getline(cin, m);
    getline(cin, f);
    cout << meeting(m, f) << "\n";
  }
}
```