#include <iostream>
#include <cctype>
#include <fstream>
#include <string>

bool check_if_present(const std::string& s, const std::string& t, int i) {
    int j = 0;
    while(j < t.size() and s[i] == t[j]) { i++; j++; }
    return (j == t.size());
}

int main()
{
    std::fstream fs("3.txt");
    if (not fs.is_open())
        exit(1);

    std::string s(std::istreambuf_iterator<char> { fs }, {});
    fs.close();

    long long ans = 0;
    int do_count = 0;
    int dont_count = 0;
    int mul_count = 0;

    bool add = true;

    const std::string do_string = "do()";
    const std::string dont_string = "don't()";
    const std::string mul_string = "mul(";
    const std::string comma = ",";
    const std::string r_bracket = ")";

    int i = 0;

    // s.size() - 8 as minimum target mul is mul(x,x) 8 characters
    // this helps in removing the check for out of bounds while string match
    //
    while(i < s.size() - 8) {
        if(check_if_present(s, do_string, i)) {
            do_count++;
            add = true;
            i+=do_string.size();
        }
        else if(check_if_present(s, dont_string, i)) {
            dont_count++;
            add = false;
            i+=dont_string.size();
        }
        else if(add) {
            int found = i;

            if(not check_if_present(s, mul_string, i))
                continue;

            i+=mul_string.size();

            int temp = i;
            while(isdigit(s[temp])) {temp++;}

            if((temp - i) < 1 or (temp - i) > 3) {
                continue;
            }

            int a = std::stoi(s.substr(i, temp-i));
            i=temp;

            if(not check_if_present(s, comma, i)) {
                i--;
                continue;
            }

            i++;
            temp = i;
            while(isdigit(s[temp])) {temp++;}

            if((temp - i) < 1 or (temp - i) > 3)
                continue;

            int b = std::stoi(s.substr(i, temp-i));
            i=temp;

            if(not check_if_present(s, r_bracket, i)) {
                i--;
                continue;
            }

            mul_count++;

            ans += add ? a * b : 0;
        }
    }

    std::cout << "Ans: " << ans << "\n";
    std::cout << "dos: " << do_count << "\n";
    std::cout << "donts: " << dont_count << "\n";
    std::cout << "muls: " << mul_count << "\n";
}
