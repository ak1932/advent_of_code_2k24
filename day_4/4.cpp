#include <vector>
#include <fstream>
#include <bits/stdc++.h>

std::array<std::array<int, 2>, 8>  dirs = {
    std::array<int, 2>{0, 1},
    std::array<int, 2>{0, -1},
    std::array<int, 2>{1, 0},
    std::array<int, 2>{-1, 0},
    std::array<int, 2>{1, 1},
    std::array<int, 2>{-1, -1},
    std::array<int, 2>{-1, 1},
    std::array<int, 2>{1, -1},
};

bool check(int x, int y, int i, const std::array<int, 2>& dir, std::vector<std::vector<char>>& grid, const std::string s) {
    if(i >= s.size())
        return true;

    if(x < 0 or x >= grid.size() or y < 0 or y >= grid[0].size())
        return false;

    if(grid[x][y] == s[i]) {
        return check(x + dir[0], y + dir[1], i+1, dir, grid, s);
    }
    return false;
}

int main() {
    std::fstream fs("4.txt");
    std::vector<std::vector<char>> grid;

    if(fs.is_open()) {
        std::string temp;

        while (std::getline(fs, temp)) {
            std::istringstream buffer(temp);
            std::vector<char> line((std::istream_iterator<char>(buffer)),
                                     std::istream_iterator<char>());

            grid.push_back(line);
        }
        fs.close();
    }

    long long ans = 0;
    for(int x = 0; x<grid.size(); x++) {
        for(int y = 0; y<grid[0].size(); y++) {
            for(auto dir: dirs) {
                ans += check(x, y, 0, dir, grid, "XMAS");
            }
        }
    }

    std::cout << "Ans: " << ans << "\n";

    ans = 0;
    for(int x = 0; x<grid.size(); x++) {
        for(int y = 0; y<grid[0].size(); y++) {
            bool check_in_tl = check(x, y, 0, {1, 1}, grid, "MAS");
            bool check_in_br = check(x, y, 0, {-1, -1}, grid, "MAS");

            ans += check_in_tl and check(x + 2, y, 0, {-1, 1}, grid, "MAS");
            ans += check_in_tl and check(x, y + 2, 0, {1, -1}, grid, "MAS");

            ans += check_in_br and check(x - 2, y, 0, {1, -1}, grid, "MAS");
            ans += check_in_br and check(x, y - 2, 0, {-1, 1}, grid, "MAS");
        }
    }

    std::cout << "Ans: " << ans << "\n";
}
