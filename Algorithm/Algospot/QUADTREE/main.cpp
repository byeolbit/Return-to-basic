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