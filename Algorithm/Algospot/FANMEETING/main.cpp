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