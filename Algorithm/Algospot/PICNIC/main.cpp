#include <cstdio>
#include <string.h>
using namespace std;

int P[10][10] = {0,};
int n, p;

int matching(int m[10]) {
    int a = -1;
    int r = 0;
    for (int i=0; i<n; i++) {
        if(!m[i]) {
            a = i;
            break;
        }
    }
    if (a == -1) return 1;
    for (int i=a+1; i<n; i++) {
        if(!m[i] && P[a][i]) {
            m[a] = m[i] = 1;
            r += matching(m);
            m[a] = m[i] = 0;
        }
    }
    return r;
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        for(int i=0; i<10; i++) {
            memset(P[i], 0, sizeof(int)*10);
        }
        scanf("%d %d", &n, &p);
        int temp_a=0, temp_b=0;
        for (int i=0; i<p; i++) {
            scanf("%d %d", &temp_a, &temp_b);
            P[temp_a][temp_b] = 1;
            P[temp_b][temp_a] = 1;
        }
        int M[10] = {0,};
        printf("%d\n", matching(M));
    }
}