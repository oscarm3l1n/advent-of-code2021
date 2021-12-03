#include <iostream>

int main()
{

    int n{};
    std::string str{};

    int horizontal{0};
    int depth{0};

    while (std::cin >> str >> n)
    {
        if (str == "forward")
        {
            horizontal += n;
        }
        else if (str == "up")
        {
            depth -= n;
        }
        else if (str == "down")
        {
            depth += n;
        }
    }

    std::cout << "horiz: " << horizontal << std::endl;
    std::cout << "depth: " << depth << std::endl;

    std::cout << "mult: " << horizontal * depth << std::endl;

    return 0;
}