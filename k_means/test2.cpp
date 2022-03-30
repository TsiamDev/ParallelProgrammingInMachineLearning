#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <vector>
#include <functional>
#include <cmath>
#include <numeric>

using namespace std;

//http://www.cplusplus.com/forum/general/209784/
double	vectors_distance(const std::vector<double>& a, const std::vector<double>& b)
{
	std::vector<double>	auxiliary;

	std::transform (a.begin(), a.end(), b.begin(), std::back_inserter(auxiliary),
	[](double element1, double element2) {return pow((element1-element2),2);});

	return  sqrt(std::accumulate(auxiliary.begin(), auxiliary.end(), 0.0));
} // end template vectors_distance

int main()
{
std::vector<double> v1 = {0.1,0.3,0.4};
//std::vector<double> v2 = {0.1,0.3,0.4};
std::vector<double> v2 = {-0.1,-0.3,-0.4};

std::cout << vectors_distance(v1,v2) << "\n";
}
