#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>

#define STRING std::string
#define VECTOR std::vector

#define INF std::numeric_limits<int>::max();

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
    VECTOR<int> low_points{};
    for (int row{1}; row < grid.size() - 1; ++row)
    {
        for (int col{1}; col < grid[0].size() - 1; ++col)
        {
            int current = grid[row][col];
            if (current < grid[row - 1][col] &&
                current < grid[row + 1][col] &&
                current < grid[row][col + 1] &&
                current < grid[row][col - 1])
                {
                    low_points.push_back(current);
                }
        }
    }

    int res{0};
    for (auto& i : low_points)
    {
        res += (i + 1);
    }
    
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