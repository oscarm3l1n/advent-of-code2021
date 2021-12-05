#include <iostream>
#include <vector>
#include <string>
#include <sstream>

struct Number
{
    Number(int n)
    {
        value = n;
        marked = false;
    }
    int value;
    bool marked;
};

struct Board
{
    Board()
    {
        for (int i{0}; i < 5; ++i)
        {
            board.push_back(std::vector<Number>{0, 0, 0, 0, 0});
        }
    };
    void print()
    {
        for (int i{0}; i < 5; ++i)
        {
            for (int j{0}; j < 5; ++j)
            {
                std::cout << board[i][j].value << " ";
            }
            std::cout << "\n";
        }
    };

    int mark_number(int &n)
    {
        for (int i{0}; i < 5; ++i)
        {
            for (int j{0}; j < 5; ++j)
            {
                if (board[i][j].value == n)
                {
                    board[i][j].marked = true;
                    return 0;
                }
            }
        }

        return 0;
    };

    bool has_won()
    {
        int n_marked{0};

        // row by row
        for (int i{0}; i < 5; ++i)
        {
            for (int j{0}; j < 5; ++j)
            {
                if (board[i][j].marked)
                    ++n_marked;
                else
                    break;
            }
            if (n_marked == 5)
                return true;
            n_marked = 0;
        }
        // col by col
        n_marked = 0;
        for (int i{0}; i < 5; ++i)
        {
            for (int j{0}; j < 5; ++j)
            {
                if (board[j][i].marked)
                    ++n_marked;
                else
                    break;
            }
            if (n_marked == 5)
                return true;
            n_marked = 0;
        }

        return false;
    };

    int unmarked_sum()
    {
        int sum{0};
        for (int i{0}; i < 5; ++i)
        {
            for (int j{0}; j < 5; ++j)
            {
                if (!board[i][j].marked)
                {
                    sum += board[i][j].value;
                }
            }
        }
        return sum;
    }

    std::vector<std::vector<Number>> board;
};

void parse_drawn_numbers(std::vector<int> &vec)
{
    std::string line{};

    // Read drawn numbers
    std::getline(std::cin, line);

    std::stringstream input{line};

    std::string tmp{};

    while (std::getline(input, tmp, ','))
    {
        vec.push_back(std::stoi(tmp));
    }
}

void init_boards(std::vector<Board> &boards)
{
    std::string line{};

    int board_index{0};
    int row{0};
    int col{0};

    while (std::getline(std::cin, line))
    {
        std::stringstream ss{line};
        std::string tmp{};

        col = 0;

        if (line.length() == 0)
        {
            boards.push_back(Board());
            board_index++;

            row = 0;
        }

        while (std::getline(ss, tmp, ' '))
        {
            if (tmp.length() > 0)
            {
                boards[board_index - 1].board[row - 1][col] = std::stoi(tmp);
                ++col;
            }
        }
        ++row;
    }
}

void mark_number(int &n, std::vector<Board> &vec)
{
    for (auto &board : vec)
    {
        board.mark_number(n);
    }
}

int find_loser(std::vector<Board> &vec, std::vector<int> &drawn_numbers)
{
    unsigned long n_boards{vec.size()};

    for (auto &b : vec)
    {
        if (b.has_won())
            --n_boards;

        if (n_boards == 1)
        {
            std::cout << "lets find our loser" << std::endl;
            for (auto &bb : vec)
            {
                if (!bb.has_won())
                {
                    std::cout << "here he is!" << std::endl;
                    bb.print();

                    // Make sure to mark numbers until it has won,
                    // and then we can see the result
                    for (int &n : drawn_numbers)
                    {
                        bb.mark_number(n);
                        if (bb.has_won())
                        {
                            std::cout << "solution: " << bb.unmarked_sum() * n << std::endl;
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int main()
{
    std::vector<int> drawn_numbers;

    parse_drawn_numbers(drawn_numbers);

    std::vector<Board> boards;

    init_boards(boards);

    long unsigned n_boards{boards.size()};
    std::cout << "n boards: " << n_boards << std::endl;

    for (int &number : drawn_numbers)
    {
        mark_number(number, boards);
        if (find_loser(boards, drawn_numbers))
            return 0;
    }

    return 0;
}