/* karatsuba 알고리즘
 * 프로그래밍 대회에서 배우는 알고리즘 문제 해결 전략
 * 7장 분할정복에서 발췌
 */

#include <vector>
#include <algorithm>

// num의 자릿수 올림을 처리하는 함수
void normalize(vector<int> &num) {
  num.push_back(0);
  
  for(int i=0; i<num.size(); ++i) {
    if(num[i]<0) {
      int borrow = (abs(num[i])+9)/10;
      num[i+1] -= borrow;
      num[i] += borrow*10;
    } else {
      num[i+1] += num[i]/10;
      num[i] %= 10;
    }
  }
  while(num.size()>1 && num.back()==0) num.pop_back();
}

vector<int> multiply(const vector<int> &a, const vector<int> &b) {
  vector<int> c(a.size() + b.size() + 1, 0);
  int a_len = a.size();
  int b_len = b.size();
  for(int i=0; i<a_len; ++i){
    for(int j=0; j<b_len; ++j){
      c[i+j] += a[i] * b[j];
    }
  }
  normalize(c);
  return c;
}

void addTo(vector<int> &a, const vector<int> &b, int k){
  int length = b.size();
	a.resize(max(a.size(), b.size()+k));  
	for (int i=0; i<length; ++i){
		a[i+k] += b[i];
	}
  normalize(a);
}

void subFrom(vector<int> &a, const vector<int> &b) {
  int length = b.size();
	a.resize(max(a.size(), b.size())+1);
	for(int i=0; i<length; ++i){
		a[i] -= b[i]; 
	}
  normalize(a);
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
	vector<int> a0(a.begin(), a.begin()+half); 
	vector<int> a1(a.begin()+half, a.end()); 
	vector<int> b0(b.begin(), b.begin() + min<int>(b.size(), half));  
	vector<int> b1(b.begin() + min<int>(b.size(), half),b. end());

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