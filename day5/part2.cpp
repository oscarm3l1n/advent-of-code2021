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
    os << "(" << l.x1 << ", " << l.y1 << ")"
       << " to "
       << "(" << l.x2 << ", " << l.y2 << ")";
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

std::tuple<int, int> get_size(std::vector<Line> &lines)
{
    int width{std::numeric_limits<int>::min()};
    int height{std::numeric_limits<int>::min()};

    for (auto &l : lines)
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

    return std::make_tuple(width + 1, height + 1);
}

struct Grid
{
    Grid(int w, int h) : w{w}, h{h}
    {

        for (int i{0}; i < w; ++i)
        {
            grid.push_back(std::vector<int>(h, 0));
        }
    }

    void print()
    {
        for (auto &row : grid)
        {
            for (auto &col : row)
            {
                std::cout << col;
            }
            std::cout << "\n";
        }
    }

    int count_bombs()
    {
        int sum{0};
        for (auto &row : grid)
        {
            for (auto &col : row)
            {
                sum += col >= 2 ? 1 : 0;
            }
        }
        return sum;
    }

    std::vector<std::vector<int>> grid;
    int w;
    int h;
};

void visit(Grid &grid, int x, int y)
{
    grid.grid[x][y]++;
}

void walk_diag(int x1, int y1, int x2, int y2, Grid &grid)
{
    int sign_x = x1 < x2 ? 1 : -1;
    int sign_y = y1 < y2 ? 1 : -1;

    int i{0};
    while (x1 + i * sign_x != x2)
    {
        visit(grid, x1 + i * sign_x, y1 + i * sign_y);
        ++i;
    }
    visit(grid, x1 + i * sign_x, y1 + i * sign_y);
}

int walk(Line &line, Grid &grid)
{
    int x1 = line.x1;
    int x2 = line.x2;
    int y1 = line.y1;
    int y2 = line.y2;
    int max;
    int min;

    if (x1 == x2 && y1 == y2)
    {
        visit(grid, x1, y2);
        return 0;
    }

    if (abs(x1 - x2) == abs(y1 - y2))
    {
        std::cout << x1 << " " << y1 << " to " << x2 <<" " << y2 << std::endl;
        walk_diag(x1, y1, x2, y2, grid);
        return 0;
    }

    bool walk_x = false;
    if (y1 == y2)
    {
        walk_x = true;
        min = std::min(x1, x2);
        max = std::max(x1, x2);
    }
    else
    {
        walk_x = false;
        min = std::min(y1, y2);
        max = std::max(y1, y2);
    }
    for (int i{0}; i <= max - min; ++i)
    {
        if (walk_x)
        {
            visit(grid, min + i, y1);
        }
        else
        {
            visit(grid, x1, min + i);
        }
    }
}

int main()
{

    std::vector<Line> lines;

    parse_input(lines);

    int width{0};
    int height{0};

    std::tie(width, height) = get_size(lines);

    Grid grid(width, height);

    for (auto &l : lines)
    {
        walk(l, grid);
    }

    grid.print();

    std::cout << "bombs: " << grid.count_bombs() << std::endl;
    return 0;
}