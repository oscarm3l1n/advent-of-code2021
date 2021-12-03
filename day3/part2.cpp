#include <iostream>
#include <vector>
#include <string.h>
#include <bitset>

void remove_with_char(std::vector<std::string> &v, char target, int start)
{
    for (int k{(int)v.size() - 1}; k >= 0; --k)
    {
        if (v.size() == 1)
        {
            break;
        }

        if (v[k][start] == target)
        {
            v.erase(v.begin() + k);
        }
    }
}

void get_ones_zeros(std::vector<int> &ones, std::vector<int> &zeros, std::vector<std::string> &v)
{
    
    std::vector<int> zero_vector(v[0].length(), 0);

    ones = zero_vector;
    zeros = zero_vector;

    for (int i{0}; i < v[0].length(); ++i)
    {
        for (int k{0}; k < v.size(); ++k)
        {
            if (v[k][i] == '0')
            {
                zeros[i]++;
            }
            else
            {
                ones[i]++;
            }
        }
    }
}

void update_counters(std::vector<int> &ones, std::vector<int> &zeros, std::vector<std::string> new_v)
{
    get_ones_zeros(ones, zeros, new_v);
}

int main()
{
    std::string input{};
    std::vector<std::string> v;

    while (std::cin >> input)
    {
        v.push_back(input);
    }

    std::vector<int> ones(v[0].length(), 0);
    std::vector<int> zeros(v[0].length(), 0);

    get_ones_zeros(ones, zeros, v);

    std::vector<std::string> new_v{v};

    // specifically for oxygen generator rating
    int start{0};
    for (int i{0}; i < new_v[0].length(); ++i)
    {
        if (new_v.size() == 1)
            break;

        if (ones[i] > zeros[i])
        {
            remove_with_char(new_v, '0', start++);
        }
        else if (ones[i] < zeros[i])
        {
            remove_with_char(new_v, '1', start++);
        }
        else
        {
            remove_with_char(new_v, '0', start++);
        }

        update_counters(ones, zeros, new_v);
    }

    unsigned long long oxygen_generator_rating{std::bitset<64>(new_v[0]).to_ullong()};
    std::cout << "oxygen: " << oxygen_generator_rating << std::endl;

    // reset vec
    new_v = v;

    // specifically for co2 scrubber rating generator rating
    start = 0;
    for (int i{0}; i < new_v[0].length(); ++i)
    {
        if (new_v.size() == 1)
            break;

        if (ones[i] > zeros[i])
        {
            remove_with_char(new_v, '1', start++);
        }
        else if (ones[i] < zeros[i])
        {
            remove_with_char(new_v, '0', start++);
        }
        else
        {
            remove_with_char(new_v, '1', start++);
        }

        update_counters(ones, zeros, new_v);
    }

    unsigned long long co2_scrubber_rating{std::bitset<64>(new_v[0]).to_ullong()};
    
    std::cout << "res: " << co2_scrubber_rating * oxygen_generator_rating << std::endl;

    return 0;
}