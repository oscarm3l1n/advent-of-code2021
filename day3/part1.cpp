#include <iostream>
#include <vector>
#include <string>
#include <bitset>

int main()
{
	std::string input{};
	std::vector<std::string> v;

	while (std::cin >> input)
	{
		v.push_back(input);
	}

	int ones[v[0].length()] = {0};
	int zeros[v[0].length()] = {0};

	for (int i{0}; i < v[0].length(); ++i)
	{
		for (int k{0}; k < v.size(); ++k)
		{
			if (v[k][i] == '0')
			{
				zeros[i]++;
			}
			else
			{
				ones[i]++;
			}
		}
	}

	std::string gamma{""};
	std::string epsilon{""};
	for (int i{0}; i < v[0].length(); ++i)
	{
		gamma += ones[i] > zeros[i] ? '1' : '0';
		epsilon += ones[i] < zeros[i] ? '1' : '0';
	}

	unsigned long long a{std::bitset<64>(gamma).to_ullong()};
	unsigned long long b{std::bitset<64>(epsilon).to_ullong()};

	std::cout << "gamma: " << gamma << "\t" << a <<  std::endl;
	std::cout << "epsilon: " << epsilon << "\t" << b << std::endl;

	std::cout << a * b << std::endl;

  	return 0;
}