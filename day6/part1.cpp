#include <iostream>
#include <vector>
#include <sstream>

struct Fish
{
    Fish(int a = 8) : timer{a} {}
    bool create_new()
    {
        return timer == 0;
    }
    void decrement()
    {
        --timer;
        timer = timer == -1 ? 6 : timer;
    }
    int timer;
};

std::ostream& operator<<(std::ostream& os, std::vector<Fish>& fishes)
{
    for (auto& f : fishes)
    {
        os << f.timer << " ";
    }
    os << std::endl;
    return os;
}

int main()
{

    std::string line;
    std::getline(std::cin, line);

    std::stringstream input{line};
    std::string tmp;

    std::vector<Fish> fishes;

    while (std::getline(input, tmp, ','))
    {
        fishes.push_back(Fish(std::stoi(tmp)));
    }

    for (int i{0}; i < 80; ++i)
    {
        std::cout << "After " << i + 1 << " days: ";
        std::cout << fishes << std::endl;

        int add_fishes{};
        for (auto &f : fishes)
        {
            // std::cout << f.timer << std::endl;
            if (f.create_new())
            {
                ++add_fishes;
            }
            f.decrement();
        }

        for (int k{0}; k < add_fishes; ++k)
        {
            fishes.push_back(Fish());
        }
    }

    std::cout << "n fishes: " << fishes.size() << std::endl;
    return 0;
}