#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <set>
#include <deque>

#define STRING std::string
#define VECTOR std::vector

#define INF std::numeric_limits<int>::max();

struct Point
{
    int x;
    int y;
};

void print_grid(VECTOR<VECTOR<int>> &grid)
{
    for (auto &row : grid)
    {
        for (auto &col : row)
        {
            std::cout << col << " ";
        }
        std::cout << "\n";
    }
}

int solve(VECTOR<VECTOR<int>> &grid)
{
    VECTOR<int> basins{};
    VECTOR<int> row_dir{-1, 1, 0, 0};
    VECTOR<int> col_dir{0, 0, -1, 1};
    std::set<STRING> visited{};

    for (int row{1}; row < grid.size() - 1; ++row)
    {
        for (int col{1}; col < grid[0].size() - 1; ++col)
        {
            STRING xy{std::to_string(row) + std::to_string(col)};

            if (!(visited.find(xy) != visited.end()) &&
                grid[row][col] != 9)
            {
                int ctr{0};
                std::deque<Point> Q;
                Q.push_back(Point{row, col});

                while (!Q.empty())
                {
                    Point tmp = Q.back();
                    Q.pop_back();

                    int x = tmp.x;
                    int y = tmp.y;

                    STRING coord{std::to_string(x) + std::to_string(y)};

                    if (visited.find(coord) != visited.end())
                    {
                        continue;
                    }
                    visited.insert(coord);

                    ++ctr;
                    for (int i{0}; i < 4; ++i)
                    {
                        int r = x + row_dir[i];
                        int c = y + col_dir[i];

                        if (r >= 1 &&
                            c >= 1 &&
                            r < grid.size() - 1 &&
                            c < grid[0].size() - 1 &&
                            grid[r][c] != 9)
                        {
                            Q.push_back(Point{r, c});
                        }
                    }
                }
                basins.push_back(ctr);
            }
        }
    }

    std::sort(basins.begin(), basins.end());
    int res{basins[basins.size() - 1] * basins[basins.size() - 2] * basins[basins.size() - 3]};

    return res;
}

int main()
{
    STRING input;
    VECTOR<STRING> inputs{};
    while (std::cin >> input)
    {
        inputs.push_back(input);
    }

    long unsigned int w{inputs[0].length()};
    long unsigned int h{inputs.size()};

    // Create a border around the
    // map with inf
    VECTOR<VECTOR<int>> grid{h + 2, VECTOR<int>(w + 2)};

    // horizontal fill
    for (int i{0}; i < grid[0].size(); ++i)
    {
        grid[0][i] = INF;
        grid[grid.size() - 1][i] = INF;
    }
    // vertical fill
    for (int i{0}; i < grid.size(); ++i)
    {
        grid[i][0] = INF;
        grid[i][grid[0].size() - 1] = INF;
    }

    // fill grid from input
    for (int row{1}; row < grid.size() - 1; ++row)
    {
        for (int col{1}; col < grid[0].size() - 1; ++col)
        {
            grid[row][col] = inputs[row - 1][col - 1] - '0';
        }
    }

    std::cout << solve(grid) << std::endl;

    // print_grid(grid);

    return 0;
}