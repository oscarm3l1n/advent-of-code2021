#include <iostream>

int main()
{

    int n{};
    std::string str{};

    int horizontal{0};
    int depth{0};
    int aim{0};

    while (std::cin >> str >> n)
    {
        if (str == "forward")
        {
            if (aim > 0)
            {
                std::cout << "increasing depth" << std::endl;
                std::cout << "n: " << n << " aim: " << aim << std::endl;
                depth += n * aim;
            }
            horizontal += n;
        }
        else if (str == "up")
        {
            // depth -= n;
            aim -= n;
        }
        else if (str == "down")
        {
            // depth += n;
            aim += n;
        }
    }

    std::cout << "horiz: " << horizontal << std::endl;
    std::cout << "depth: " << depth << std::endl;

    std::cout << "mult: " << horizontal * depth << std::endl;

    return 0;
}