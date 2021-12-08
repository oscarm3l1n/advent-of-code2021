#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void print(std::vector<std::string> &v)
{
    for (auto &i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int solve(std::vector<std::string> &digits)
{
    int counter{0};

    for (auto &j : digits)
    {
        if (j.length() == 4 ||
            j.length() == 2 ||
            j.length() == 3 ||
            j.length() == 7)
            {
                ++counter;
            }
    }

    return counter;
}

int main()
{
    std::string input;
    std::vector<std::string> actual_digits(4, "");

    int idx{0};
    int ctr{0};
    while (std::cin >> input)
    {
        if (input == "|")
        {
            for (int i{0}; i < 4; ++i)
            {
                std::string digit;
                std::cin >> digit;
                actual_digits[i] = digit;
            }

            ctr += solve(actual_digits);
            idx = 0;
        }
    }
    std::cout << ctr << std::endl;
    return 0;
}