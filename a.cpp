#include<bits/stdc++.h>
using namespace std;
long long gcd(long long a, long long b){
    if (b ==0) return a;
    return gcd(b,a%b);
}
int n,m;
int main(){
    scanf("%d%d",&n,&m);
    int len = 1e7;
    int k = 0;
    long long ans = 1ll*n*m/(gcd(n,m)),tmp;
    for (int i = 1; i <= len; ++i){
        tmp = 1ll*(n+i)*(m+i)/gcd(n+i,m+i);
        if (tmp < ans) ans = tmp, k = i;
    }
    printf("%d\n",k);

    return 0;
}