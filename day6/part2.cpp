#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>

int main()
{

    std::string line;
    std::getline(std::cin, line);

    std::stringstream input{line};
    std::string tmp;

    std::unordered_map<int, unsigned long long int> map;

    while (std::getline(input, tmp, ','))
    {
        map[std::stoi(tmp)] += 1;
    }

    for (int i{0}; i < 256; ++i)
    {
        std::cout << i << " " << map.size() << std::endl;

        std::unordered_map<int, unsigned long long int> tmp_map;

        for (auto &i : map)
        {
            if (i.first == 0)
            {
                tmp_map[6] += i.second;
                tmp_map[8] += i.second;
            }
            else
            {
                tmp_map[i.first - 1] += i.second;
            }
        }
        map = tmp_map;
    }

    unsigned long long int sum{0};
    for (auto& i : map)
    {
        sum += i.second;
    }
    std::cout << sum << std::endl;

    return 0;
}

