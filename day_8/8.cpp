#include <bits/stdc++.h>
using namespace std;

int main()
{
    std::fstream fs("8.txt");

    if (not fs.is_open()) {
        cout << "Error opening file\n";
        exit(1);
    }

    std::string temp;

    std::unordered_map<char, std::vector<std::tuple<int, int>>> mp;

    std::vector<std::vector<char>> grid;

    int x = 0, y = 0;
    while (std::getline(fs, temp)) {
        std::istringstream lineStream(temp);
        char value;
        std::vector<char> row;
        while (lineStream >> value) {
            if (value != '.') {
                mp[value].push_back({ y, x });
            }
            row.push_back(value);
            x++;
        }
        grid.push_back(row);
        x = 0;
        y++;
    }

    int ans = 0;

    auto check_and_inc = [&grid, &ans](tuple<int, int>& h) {
        auto& [y, x] = h;

        cout << y << " " << x << "\n";
        if(y < 0 or y >= grid.size() or x < 0 or x >= grid[0].size()) {
            return false;
        }


        if(grid[y][x]!='#') {
            grid[y][x] = '#';
            ans += 1;
        }
        return true;
    };

    for (auto& [c, v] : mp) {
        for (int i = 0; i < v.size(); i++) {
            for (int j = i + 1; j < v.size(); j++) {
                auto [yi, xi] = v[i];
                auto [yj, xj] = v[j];

                std::cout << yi << " " << xi << " " << yj << " " << xj << "\n";

                int dx = xj - xi;
                int dy = yj - yi;

                tuple<int, int> h1 = { yi - dy, xi - dx };
                while(check_and_inc(h1)) {
                    auto& [y,x] = h1;
                    y-=dy;
                    x-=dx;
                }
                tuple<int, int> h2 = { yj + dy, xj + dx };
                while(check_and_inc(h2)) {
                    auto& [y,x] = h2;
                    y+=dy;
                    x+=dx;
                }

                check_and_inc(v[i]);
                check_and_inc(v[j]);
            }
        }
    }


    std::cout << "Ans: " << ans <<"\n";
    // for(auto& row : grid) {
    //     for(auto& c: row) {
    //         std::cout << c;
    //     }
    //     std::cout << "\n";
    // }
    //
}
