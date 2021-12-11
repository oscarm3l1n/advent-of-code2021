#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define STRING std::string
#define npos std::string::npos

//   0:      1:      2:      3:      4:
//  aaaa    ....    aaaa    aaaa    ....
// b    c  .    c  .    c  .    c  b    c
// b    c  .    c  .    c  .    c  b    c
//  ....    ....    dddd    dddd    dddd
// e    f  .    f  e    .  .    f  .    f
// e    f  .    f  e    .  .    f  .    f
//  gggg    ....    gggg    gggg    ....

//   5:      6:      7:      8:      9:
//  aaaa    aaaa    aaaa    aaaa    aaaa
// b    .  b    .  .    c  b    c  b    c
// b    .  b    .  .    c  b    c  b    c
//  dddd    dddd    ....    dddd    dddd
// .    f  e    f  .    f  e    f  .    f
// .    f  e    f  .    f  e    f  .    f
//  gggg    gggg    ....    gggg    gggg

// 1: cf (2)
// 7: acf (3)
// 4: bcdf (4)
// 2: acdeg (5)
// 3: acdfg (5)
// 5: abdfg (5)
// 6: abdefg (6)
// 0: abcefg (6)
// 9: abcdfg (6)
// 8: abcdefg (7)

void print(std::vector<STRING> &v)
{
    for (auto &i : v)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void my_sort(std::vector<STRING> &v)
{
    for (auto &str : v)
    {
        std::sort(str.begin(), str.end());
    }
}

std::vector<STRING> get_string_from_vec(std::vector<STRING> &v, int &&len)
{
    std::vector<STRING> res;

    for (auto &i : v)
    {
        if (i.length() == len)
        {
            res.push_back(i);
        }
    }
    return res;
}

int solve(std::vector<STRING> &signals, std::vector<STRING> &digits)
{
    std::unordered_map<char, char> decode{};

    std::unordered_map<STRING, STRING> true_combination{
        {"abcefg", "0"},
        {"cf", "1"},
        {"acdeg", "2"},
        {"acdfg", "3"},
        {"bcdf", "4"},
        {"abdfg", "5"},
        {"abdefg", "6"},
        {"acf", "7"},
        {"abcdefg", "8"},
        {"abcdfg", "9"}};

    // from digit 1 we get the identity of cf
    // but dont know which order

    // in this case we can just take the
    // 1st element since we know '1' is the only
    // digit with length=2
    print(signals);
    STRING cf = get_string_from_vec(signals, 2)[0];

    // We can find the identity by looking
    // for digits with length=6 which are
    // 0,6,9, and look which of these share
    // only one common with the 'cf' string
    // to find the identity of 'f'
    std::vector<STRING> targets = get_string_from_vec(signals, 6);
    for (auto &i : targets)
    {
        if (i.find(cf[0]) != npos && i.find(cf[1]) == npos)
        {
            decode[cf[0]] = 'f';
            decode[cf[1]] = 'c';
            break;
        }
        else if (i.find(cf[0]) == npos && i.find(cf[1]) != npos)
        {
            decode[cf[0]] = 'c';
            decode[cf[1]] = 'f';
            break;
        }
    }

    // At this point, we know the true identity of 'c' and 'f'
    // now we can check digit 7 with length=3 in order to get
    // identity of 'a'
    STRING acf = get_string_from_vec(signals, 3)[0];

    // The 'a' is the one that is not in cf
    for (auto &ch : acf)
    {
        if (!(cf.find(ch) != npos))
        {
            decode[ch] = 'a';
        }
    }

    // At this point we have decoded letters
    // 'a' 'c' and 'f'. 4 to go, we can get
    // 'bd' from the digit 4 with length=4
    STRING wrong_bd = get_string_from_vec(signals, 4)[0];

    // Need to trim down bd since it contains 
    // 4 chars at first, we do this by removing
    // 'c' and 'f'
    STRING bd{""};
    for (auto& i : wrong_bd)
    {
        if (!(cf.find(i) != npos))
        {
            bd += i;
        }
    }

    // But we don't know the order of bd
    // so we can check digits 2,5,3
    // which both have length=5 but only the
    // digit 2 and 3 shares the 'd' with our 4
    targets = get_string_from_vec(signals, 5);
    for (auto &i : targets)
    {
        if (i.find(bd[0]) != npos && i.find(bd[1]) == npos)
        {
            decode[bd[0]] = 'd';
            decode[bd[1]] = 'b';
            break;
        }
        else if (i.find(bd[0]) == npos && i.find(bd[1]) != npos)
        {
            decode[bd[1]] = 'd';
            decode[bd[0]] = 'b';
            break;
        }
    }

  

    // Now only 2 letters are missing 'eg'
    // i guess we can look at the digit 8
    // with unique length=7 and take the
    // values that we have not already discoverd
    // and these will be our 'eg'

    STRING digit_eight = get_string_from_vec(signals, 7)[0];
    STRING eg{""};

    // get all our decoded letters
    // and take the ones from
    // digit_eigth that don't exist
    // among these
    STRING known{};
    for (auto &i : decode)
    {
        known += i.first;
    }
    for (auto &i : digit_eight)
    {
        if (known.find(i) == npos)
        {
            eg += i;
        }
    }

    // Final step is to get the 
    // digits 0,6,9 with length=6
    // and find the true identity
    // of 'g' which is the only
    // one in 9
    targets = get_string_from_vec(signals, 6);
    for (auto& i : targets)
    {
        if (i.find(eg[0]) != npos && !(i.find(eg[1]) != npos))
        {
            decode[eg[0]] = 'g';
            decode[eg[1]] = 'e';
        }
        else if (!(i.find(eg[0]) != npos) && i.find(eg[1]) != npos)
        {
            decode[eg[1]] = 'g';
            decode[eg[0]] = 'e';
        }
    }

    for (auto &i : decode)
    {
        std::cout << i.first << " -> " << i.second << std::endl;
    }

    // first decode the digits
    std::vector<STRING> decoded_digits{};
    for (auto &i : digits)
    {
        STRING tmp{""};
        for (auto &j : i)
        {
            tmp += decode[j];
        }
        decoded_digits.push_back(tmp);
    }
    print(decoded_digits);
    my_sort(decoded_digits);

    STRING res{""};
    for (auto& i : decoded_digits)
    {
        res += true_combination[i];
    }
    
    return std::stoi(res);
}

int main()
{
    STRING input;
    std::vector<STRING> unique_signals(10, "");
    std::vector<STRING> actual_digits(4, "");

    int idx{0};
    int ctr{0};
    while (std::cin >> input)
    {
        if (input == "|")
        {
            for (int i{0}; i < 4; ++i)
            {
                STRING digit;
                std::cin >> digit;
                actual_digits[i] = digit;
            }

            ctr += solve(unique_signals, actual_digits);
            idx = 0;
        }
        else
        {
            unique_signals[idx++] = input;
        }
    }
    std::cout << ctr << std::endl;
    return 0;
}