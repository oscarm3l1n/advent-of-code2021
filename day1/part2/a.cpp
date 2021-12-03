#include <iostream>
#include <vector>
#include <limits.h>

int main()
{
    std::vector<int> v;
    std::vector<int> results;

    int n{};
    while (std::cin >> n)
    {
        v.push_back(n);
    }

    

    int index{0};

    for (int i{0}; i < v.size(); ++i)
    {
        int sum{0};
        for (int j{0}; j < 3; ++j)
        {
            sum += v[i + j];
        }
        results.push_back(sum);
    }

    int old{INT_MIN};
    int incr{0};
    for (auto& i : results) {
        if (old < i){
            incr++;
        }
        old = i;
    }
    std::cout << "Incremented: " << incr - 1 << std::endl;
}