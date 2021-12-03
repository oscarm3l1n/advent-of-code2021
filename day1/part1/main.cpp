#include <iostream>
#include <limits.h>

int main()
{
    int n{0};
    int increased{0};
    int old{INT_MIN};

    while (std::cin >> n)
    {
        if (n > old){
            increased++;
        }
        old = n;
    }

    std::cout << "Increased: " << increased - 1 << std::endl;
}