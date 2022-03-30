#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
	std::vector<int> v{1, 2, 3, 4};
	int n1 = 0;

	auto result1 = std::find(begin(v), end(v), n1);

	(result1 != std::end(v))
	? std::cout << "v contains " << n1 << '\n'
	: std::cout << "v does not contain " << n1 << '\n';
}
