#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

int cache[101][101];
string W, S;

int match(int w, int s) {
	int &ret = cache[w][s];
  // 캐시에 값이 존재하면 값을 리턴
	if (ret != -1) {
		return ret;
	}

  // 주어진 문자가 와일드카드의 문자와 일치한다면 다음 글자에 대해 호출
	while (s < S.size() && w < W.size() && (W[w] == '?' || W[w] == S[s])) {
		return ret = match(w + 1, s + 1);
	}

  // 끝까지 다 돌았을 때, 두 반복자가 각각의 문자열의 끝과 일치해야함
	if (w == W.size() && s == S.size()) {
		return 1;
	}

  // 별에 대응하는것을 완전탐색한다.
  // 별에 대응하는 경우는 와일드카드의 다음 글자가 현재 글자와 일치할 때
  // 그리고, 와일드 카드의 문자는 별이면서, 두 문자의 반복자가 끝까지 도달했을 때이다. 
	if (W[w] == '*') {
		if (match(w + 1, s) || (s < S.size() && match(w, s + 1)))
			return ret = 1;
	}

  // 나머지는 모두 충족시키지 못하는 경우
	return ret = 0;
}

int main() {
	int C;
	cin >> C;
	while (C--) {
    cin >> W;
		int n;
		cin >> n;
		vector<string> matched;
		for (int i=0; i < n; ++i) {
			memset(cache, -1, sizeof(cache));
      cin >> S;
			if (match(0, 0))
			  matched.push_back(S);
		}
    // 정렬후 출력
		sort(matched.begin(), matched.end());
		for(int i=0; i<matched.size(); i++) {
		  cout << matched[i] << endl;
		}
	}
}