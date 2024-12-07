#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <cmath>

using namespace std;
using namespace boost::multiprecision;

bool check(long long& target, vector<long long>& nums, int i, cpp_int cur)
{
    if (i == nums.size())
        return (cur == target);

    if (cur > target)
        return false;

    return (check(target, nums, i + 1, cur + nums[i]) or check(target, nums, i + 1, cur * nums[i]) or check(target, nums, i + 1, (cur * (int) pow(10, (((int)log10(nums[i])) + 1))) + nums[i]));
}

int main()
{
    std::fstream fs("7.txt");

    if (not fs.is_open()) {
        cout << "Error opening file\n";
        exit(1);
    }

    std::vector<long long> targets;
    std::vector<std::vector<long long>> nums;

    std::string temp;

    while (std::getline(fs, temp)) {
        std::istringstream lineStream(temp);
        long long key;
        char colon;
        lineStream >> key >> colon;

        targets.push_back(key);

        std::vector<long long> row;
        long long value;
        while (lineStream >> value) {
            row.push_back(value);
        }
        nums.push_back(row);
    }

    cpp_int ans = 0;

    for (int i = 0; i < targets.size(); i++) {
        if (check(targets[i], nums[i], 1, nums[i][0])) {
            ans += targets[i];
        }
    }

    cout << "Ans: " << ans << "\n";
}
