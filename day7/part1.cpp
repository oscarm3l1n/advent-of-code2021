#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

void parse_input(std::vector<int> &v, std::string input)
{
    std::stringstream ss{input};
    std::string tmp;

    while (std::getline(ss, tmp, ','))
    {
        v.push_back(std::stoi(tmp));
    }
}

void print(std::vector<int> &v)
{
    for (auto &i : v)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

int main()
{
    std::string input;
    std::getline(std::cin, input);

    std::vector<int> v{};
    parse_input(v, input);

    // print(v);

    int max{*max_element(std::begin(v), std::end(v))};

    int shortest{std::numeric_limits<int>::max()};

    for (int i{0}; i < max; ++i)
    {
        int current_sum{0};

        for (auto &num : v)
        {
            current_sum += abs(i - num);
        }

        shortest = current_sum < shortest ? current_sum : shortest;
    }

    std::cout << shortest << std::endl;

    return 0;
}