#include <vector>
#include <fstream>
#include <iostream>
#include <bits/stdc++.h>

inline bool good(std::vector<int> arr) {
    int prev = arr[0];
    int curr = arr[1];
    bool inc = (curr - prev) > 0 ? true : false;

    for(int i = 1; i<arr.size(); i++) {
        if(inc and (arr[i] - arr[i-1]) <= 0)
            return false;
        else if(not inc and (arr[i] - arr[i-1]) >= 0)
            return false;
        else if(abs(arr[i] - arr[i-1]) > 3)
            return false;
    }
    return true;
}

int main() {
    std::fstream fs("2.txt");
    std::vector<std::vector<int>> l;

    l.reserve(1000);

    if(fs.is_open()) {
        std::string temp;

        while (std::getline(fs, temp)) {
            std::istringstream buffer(temp);
            std::vector<int> line((std::istream_iterator<int>(buffer)),
                                     std::istream_iterator<int>());

            l.push_back(line);
        }
    }
    fs.close();

    int ans = 0;

    for(auto& arr: l) {
        if(good(arr)) {
            for(auto n: arr) {
                std::cout << n << " ";
            }
            std::cout << "\n";
            ans+=1;
        }
        else {
            auto arr_copy = arr;
            for(int i = 0; i<arr.size(); i++) {
                arr = arr_copy;
                arr.erase(arr.begin() + i);
                if(good(arr)) {
                    ans+=1;
                    break;
                }
            }
        }
    }
    std::cout << ans << "\n";
}
