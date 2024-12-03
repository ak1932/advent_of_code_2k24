#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

int main() {
    std::fstream fs("1.txt");
    std::vector<long long> ll;
    std::vector<long long> rl;

    ll.reserve(1000);
    rl.reserve(1000);

    if(fs.is_open()) {
        long long l, r;
        while(fs >> l >> r) {
            ll.push_back(l);
            rl.push_back(r);
        }
    }

    std::sort(ll.begin(), ll.end());
    std::sort(rl.begin(), rl.end());

    long long diff = 0;
    for(int i = 0; i<1000; i++) {
        diff += llabs(ll[i]-rl[i]);
    }
    std::cout << diff << "\n";

    int i = 0, j = 0;

    long long ans = 0;
    while(i < 1000 or j < 1000) {
        long long num = ll[i];
        int n = 0;
        while(num > rl[j]) {
            j++;
        }

        while(num == rl[j]) {
            j++;
            n++;
        }

        int m = 1;
        while(num == ll[++i]) {
            m++;
        }

        ans += (num * n * m);
    }
    std::cout << ans << "\n";
}
