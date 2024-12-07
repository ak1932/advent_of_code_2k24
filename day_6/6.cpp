#include <array>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

enum Dir {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
    UNVISITED = 4,
};

int distinct_pos(std::vector<std::vector<char>> grid, int x, int y, Dir dir)
{
    std::vector<std::vector<Dir>> dir_of_visited { grid.size(), { grid[0].size(), UNVISITED } };

    grid[y][x] = '.';
    int ans = 0;

    auto move = [&x, &y, &dir_of_visited](Dir dir, bool forward = false) {
        std::array<int, 2> v;
        switch (dir) {
        case UP:
            v = { 0, -1 };
            break;
        case DOWN:
            v = { 0, 1 };
            break;
        case LEFT:
            v = { -1, 0 };
            break;
        case RIGHT:
            v = { 1, 0 };
            break;
        }

        x += (forward) ? v[0] : -v[0];
        y += (forward) ? v[1] : -v[1];
    };

    while (x >= 0 and x < grid.size() and y < grid.size() and y >= 0) {
        char& c = grid[y][x];

        switch (c) {
        case '.': {
            ans += 1;
            c = 'X';
            dir_of_visited[y][x] = dir;
            move(dir, true);
            break;
        }
        case '#': {
            move(dir, false);

            dir = static_cast<Dir>((dir + 1) % 4);

            move(dir, true);
            break;
        }
        case 'X': {
            if (dir_of_visited[y][x] == dir) {
                return INT_MAX;
            }
            move(dir, true);
            break;
        }
        }
    }

    return ans;
}

bool detect_cycles(std::vector<std::vector<char>> grid, int x, int y, Dir dir, int ox, int oy)
{
    if (grid[oy][ox] != '.') {
        return false;
    }

    grid[oy][ox] = '#';

    return (distinct_pos(grid, x, y, dir) == INT_MAX);
}

int main()
{
    std::fstream fs("6.txt");
    std::vector<std::vector<char>> grid;

    if (fs.is_open()) {
        std::string temp;

        while (std::getline(fs, temp)) {
            std::istringstream buffer(temp);
            std::vector<char> line((std::istream_iterator<char>(buffer)),
                std::istream_iterator<char>());

            grid.push_back(line);
        }
        fs.close();
    }

    bool found_guard = false;
    Dir dir;

    int x, y;

    for (int i = 0; not found_guard and i < grid.size(); i++) {
        for (int j = 0; not found_guard and j < grid.size(); j++) {
            char c = grid[i][j];
            if (c == '.' or c == '#')
                continue;

            found_guard = true;

            y = i;
            x = j;

            switch (c) {
            case '^':
                dir = UP;
                break;
            case '>':
                dir = RIGHT;
                break;
            case 'v':
                dir = DOWN;
                break;
            case '<':
                dir = LEFT;
                break;
            }

            break;
        }
    }

    std::cout << "Ans1: " << distinct_pos(grid, x, y, dir) << "\n";

    int ans = 0;
    for (int oy = 0; oy < grid.size(); oy++) {
        for (int ox = 0; ox < grid[0].size(); ox++) {
            ans += detect_cycles(grid, x, y, dir, ox, oy);
        }
    }
    std::cout << "Ans2: " << ans << "\n";
}
