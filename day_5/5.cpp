// #include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
//
// class Graph {
//     std::vector<std::vector<int>> adj;
//     std::vector<std::vector<int>> radj;
//     std::vector<int> in_deg;
//     std::vector<int> component_no;
//
//     int total_components;
//     int n;
//
//     void _topo_sort(std::vector<bool>& visited, std::vector<int>& topo, int u)
//     {
//         visited[u] = true;
//         for (auto ad : adj[u]) {
//             if (not visited[ad])
//                 _topo_sort(visited, topo, ad);
//         }
//         topo.push_back(u);
//     }
//
//     void _dfs(std::vector<bool>& visited, int u, int component)
//     {
//         visited[u] = true;
//         component_no[u] = component;
//         for (auto v : adj[u]) {
//             if (not visited[v])
//                 _dfs(visited, v, component);
//         }
//         for (auto v : radj[u]) {
//             if (not visited[v])
//                 _dfs(visited, v, component);
//         }
//     }
//
// public:
//     Graph(int n)
//         : n(n)
//         , component_no(n, -1)
//         , adj(n)
//         , radj(n)
//         , in_deg(n)
//     {
//     }
//
//     void add_edge(int u, int v)
//     {
//         adj[u].push_back(v);
//         radj[v].push_back(u);
//         in_deg[v]++;
//     };
//
//     void set_component_no()
//     {
//         std::vector<bool> visited(n, false);
//         int component_no = 0;
//
//         for (int i = 0; i < n; i++) {
//             if (not visited[i] and (adj[i].size() != 0 or radj[i].size() != 0)) {
//                 _dfs(visited, i, component_no);
//                 component_no += 1;
//             }
//         }
//
//         total_components = component_no;
//     }
//
//     inline int get_component_no(int u)
//     {
//         return component_no[u];
//     }
//
//     std::vector<std::vector<int>> topo_sort()
//     {
//         using t2i = std::array<int, 2>;
//         std::vector<int> q;
//
//         for (int i = 0; i < n; i++) {
//             if (adj[i].size() > 0 and in_deg[i] == 0) {
//                 q.push_back(i);
//             }
//         }
//
//         std::vector<bool> visited(n);
//         std::vector<std::vector<int>> topo(total_components);
//
//         for (auto i : q) {
//             _topo_sort(visited, topo[get_component_no(i)], i);
//         }
//         // while(not pq.empty()) {
//         //     auto [order, i] = pq.top();
//         //     pq.pop();
//         // }
//
//         for (auto& t : topo) {
//             std::reverse(t.begin(), t.end());
//             std::cout << "\n";
//         }
//         return topo;
//     }
// };
//
int main()
{
    std::fstream fs("5_order.txt");

    if (not fs.is_open()) {
        std::cerr << "error opening order";
    }
    std::string temp;
    std::vector<std::array<int, 2>> rules;

    // Graph g(100);

    while (std::getline(fs, temp)) {
        std::istringstream buffer(temp);
        char c;
        int u, v;
        buffer >> u;
        buffer >> c;
        buffer >> v;

        rules.push_back({ u, v });

        // g.add_edge(u, v);
    }
    fs.close();

    fs.open("5_updates.txt");
    if (not fs.is_open()) {
        std::cerr << "error opening order";
    }

    std::vector<std::vector<int>> updates;
    while (std::getline(fs, temp)) {
        std::istringstream buffer(temp);
        std::string value;
        std::vector<int> line;
        while (std::getline(buffer, value, ',')) {
            line.push_back(std::stoi(value));
        }
        updates.push_back(line);
    }
    fs.close();

    auto sort_update = [&rules](std::vector<int>& update) {
        std::vector<std::array<int, 2>> rules_in_update;

        std::unordered_map<int, int> in_deg;

        for (auto& [a, b] : rules) {
            if (std::find(update.begin(), update.end(), a) == update.end() or std::find(update.begin(), update.end(), b) == update.end())
                continue;

            rules_in_update.push_back(std::array<int, 2> { a, b });
        }

        for(auto& [a, b]: rules_in_update) {
            in_deg[b]+=1;
        }

        std::vector<int> ans;

        while (ans.size() < update.size()) {
            for (auto& x : update) {
                if (std::find(ans.begin(), ans.end(), x) != ans.end())
                    continue;

                if (in_deg[x] <= 0) {
                    ans.push_back(x);
                    for (auto& [a, b] : rules_in_update) {
                        if (a == x)
                            in_deg[b] -= 1;
                    }
                }
            }
        }

        return ans;
    };

    auto print_vector = [](std::vector<int>& v) {
        for (auto i : v) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    };

    long long ans = 0;
    for (auto& update : updates) {
        std::unordered_map<int, int> idx;
        bool good_order = true;
        for (int i = 0; i < update.size(); i++) {
            int u = update[i];
            idx[u] = i;

            for (auto& [a, b] : rules) {
                if (idx.find(a) != idx.end() and idx.find(b) != idx.end() and not(idx[a] < idx[b])) {
                    good_order = false;
                    break;
                }
            }
            if (not good_order)
                break;
        }

        if (not good_order) {
            print_vector(update);
            std::vector<int> a = sort_update(update);
            print_vector(update);
            ans += a[a.size() / 2];
        }
    }
    std::cout << "Ans: " << ans << "\n";
}
