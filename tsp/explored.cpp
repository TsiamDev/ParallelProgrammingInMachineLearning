#include <iostream>
#include <iterator>

using namespace std;

int main(void)
{
	int N = 4;
	int eplored_ind = 0;
	int explored[N] = {1,-1,-1,-1,-1};

	int route_ind = 0;
	double route_dist = 0.0;
	int xs[N+1] = {-1};
	int ys[N+1] = {-1};
	//int j = 0;
	for (int j = 0; j < N-1; j++)
	{
		//minimum value
		double min_dist = dists[j+1][j];
		int temp_min_x = j+1;
		int temp_min_y = j;
		//double min_dist = dists[i][0];
		//int temp_min_x = ;
		//int temp_min_y = j;

		//second minimum value
		double min_dist2 = dists[j+2][j];
		int temp_x = j+2;
		int temp_y = j;
	
		//compare the two first values and swap them accordingly
		if (min_dist < min_dist2)
		{
			double temp = min_dist;
			min_dist = min_dist2;
			min_dist2 = temp;

			temp_x = j+1;
			temp_min_x = j+2;
		}		
	
		cout << min_dist << "---" <<  min_dist2 << endl;
		for (int i = 3; i < N+1; i++)
		{
			bool found = false;
			for (int t = 0; t < explored_ind; t++)
			{
				if (i == explored[t])
				{	
					found = true;
					break;
				}
			}
			if ( ( i > j ) and (found == false) )
			{
				if (min_dist > dists[i][j])
				{
					min_dist2 = min_dist;
					min_dist = dists[i][j];
					temp_x = temp_min_x;
					temp_y = temp_min_y;
					temp_min_x = i;
					temp_min_y = j;
					explored[explored_ind] = i;
					explored_ind++;
				}else if( min_dist2 > dists[i][j])
				{
					min_dist2 = dists[i][j];
					temp_x = i;
					temp_y = j;
					explored[explored_ind] = i;
					explored_ind++;
				}
			}
		}
		//route[route_ind] = temp_ind;
		route_dist += min_dist2;
		cout << route_dist << endl;
		xs[route_ind] = cities[temp_y][0];
		ys[route_ind] = cities[temp_y][1];
		cout << xs[route_ind] << "," << ys[route_ind] << endl;

		route_ind++;
	}
	
	//the two last steps are unrolled
	//Second to last step
	if ( dists[N-1][N-2] > dists[N][N-2] )
	{
		route_dist += dists[N-1][N-2];
		xs[route_ind] = cities[N-1][0];
		ys[route_ind] = cities[N-1][1];
	}else{
		route_dist += dists[N][N-2];
		xs[route_ind] = cities[N][0];
		ys[route_ind] = cities[N][1];
	}
	cout << route_dist << endl;
	cout << xs[route_ind] << "," << ys[route_ind] << endl;
	route_ind++;

	//Last step
	route_dist += dists[N][N-1];
	xs[route_ind] = cities[N][0];
	ys[route_ind] = cities[N][1];
	cout << xs[route_ind] << "," << ys[route_ind] << endl;
	route_ind++;
	cout << "-------------------------------" << endl;

	return 0;
}
