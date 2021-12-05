#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
#include <tuple>

struct Line
{
    Line(int x1, int y1, int x2, int y2) : x1{x1}, y1{y1}, x2{x2}, y2{y2} {};
    int x1;
    int x2;
    int y1;
    int y2;
};

std::ostream &operator<<(std::ostream &os, Line l)
{
    os << "(" << l.x1 << ", " << l.y1 << ")" << " to " << "(" << l.x2 << ", " << l.y2 << ")";
    return os;
}

void parse_input(std::vector<Line> &vec)
{
    std::string line{};

    while (std::getline(std::cin, line))
    {
        std::stringstream ss{line};
        std::string tmp{};
        int input_index{0};
        int x1{}, x2{}, y1{}, y2{};

        while (ss >> tmp)
        {
            if (tmp.length() != 2)
            {
                // skip the arrow
                std::stringstream ss2{tmp};

                if (input_index++ % 2 == 0)
                {
                    ss2 >> x1;
                    ss2.ignore(1);
                    ss2 >> y1;
                }
                else
                {
                    ss2 >> x2;
                    ss2.ignore(1);
                    ss2 >> y2;

                    vec.push_back(Line(x1, y1, x2, y2));
                }
            }
        }
    }
}

std::tuple<int, int> get_size(std::vector<Line>& lines)
{
    int width{std::numeric_limits<int>::min()};
    int height{std::numeric_limits<int>::min()};

    for (auto& l: lines)
    {
        if (width < l.x1 || width < l.x2)
        {
            width = std::max(l.x1, l.x2);
        }
        if (height < l.y1 || height < l.y2)
        {
            height = std::max(l.y1, l.y2);
        }
    }

    return std::make_tuple(width, height);
}

int main()
{
    std::vector<std::vector<int>> grid;
    std::vector<Line> lines;

    parse_input(lines);

    int width{0};
    int height{0};

    std::tie(width, height) = get_size(lines);

    for (auto &l : lines)
    {
        std::cout << l << std::endl;
    }

    std::cout << "w h"<< std::endl;
    std::cout << width << " " << height << std::endl;

    return 0;
}