#include "matplotlibcpp.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <chrono>

using namespace std;

namespace plt = matplotlibcpp;

using namespace std::chrono;

//Number of point vectors
#define N 100000//000
//Number of point dimensions
#define Nv 1000
//Number of clusters
#define Nc 100//0
//Tolerance
#define THR_KMEANS 0.000001


//Point Vectors
std::vector<std::vector<double>> V( N , vector<double> (Nv, -1));
//std::vector<int> V[N][Nv];

//Cluster Centers
std::vector<std::vector<double>> centroids( Nc , vector<double> (Nv, 0));
//std::vector<int> centroids[Nc][Nv];

//Classes
std::vector<int> classes(N, -1);

//http://www.cplusplus.com/forum/general/209784/
inline double vectors_distance(std::vector<double> a, std::vector<double> b)
{
	std::vector<double>	auxiliary;

	std::transform (a.begin(), a.end(), b.begin(), std::back_inserter(auxiliary),
	[](double element1, double element2) {return (element1-element2)*(element1-element2);});//pow((element1-element2),2);});

	return  sqrt(std::accumulate(auxiliary.begin(), auxiliary.end(), 0.0));
};

//*
void compute_new_center(int * vec, int j)
{
		int k;
		double temp [Nv] = {0.0};
//		register double tempy = 0.0;
		for (k = 0; k < N; k++)
		{
			//cout << vec2[k] << endl;
			if (vec[k] == -1)
			{
				break;
			}
			else
			{
				for(int o = 0; o < Nv; o++)
				{
					temp[o] += V[vec[k]][o];
				}
			}
		}	
		for (int o = 0; o < Nv; o++)
		{
			centroids[j][o] = temp[o] / k;
		}
}
//*/

//inlining propably is useless here
inline void find_indexes(std::vector<int> vec)
{
	static int vec2[N];
	register int ind;
	for (int j = 0; j < Nc; j++)
	{
		ind = 0;
		for (int i = 0; i < N; i++)
		{
			vec2[i] = -1;
			//cout << vec[i] << "," << j << endl;
			if (vec[i] == j)
			{
				vec2[ind] = i;
				ind++;
			}
		}	

		/*
		for (int i = 0; i < N; i++)
			std::cout << vec2[i] << ' ';
		cout << endl;
		*/
		compute_new_center(vec2, j);

	}
}

// main function that doesn't receive any parameter and
// returns integer.
int main(void)
{

	cout << "Initializing..." << endl;


	//Seed rand()
	//srand (time(NULL));
	srand(1645283643);
	//cout << time(NULL) << endl;
	//Generate random point vectors
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < Nv; j++)
		{
			V[i][j] = rand() % 30;
		}
		//cout << V[i][0] << "," << V[i][1] << endl;
	}
	//cout << "---------------------------" << endl;
	
	//Pick Nc random centers-----------------------------------------
	std::vector<int> xs(Nc, -1);
	int ind = 0;

	int x;

	for (int i = 0; i < Nc; i++)
	{
		do{
			x = rand() % N;
			//cout << x << endl;
			auto res = std::find(begin(xs), end(xs), x);
			/*
			for (std::vector<int>::const_iterator i = xs.begin(); i != xs.end(); i++)
				std::cout << *i << ' ';
			//*/
			if (res != std::end(xs)) 
			{
				//cout << "in xs" << endl;
				continue;	
			}else{
				//cout << "not in xs" << endl; 
				break;
			}
		}while(true);
		//cout << "-----------------------" << endl;
		xs.at(ind) = x;
		ind++;
	
		//Pick new centroid
		for (int j = 0; j < Nv; j++)
		{
			centroids[i][j] = V[x][j];
			//cout << centroids[i][j] << ' ';
		}
		//cout << endl;
		//cout << centroids[i][0] << "," << centroids[i][1] << endl;
		//*/
		


	}
	//---------------------------Pick Nc random centers-------------------------
	
	cout << "Begin Clustering..." << endl;

//	double last_dist = 1000;
	//int it_cnt = 0;
	double cumulative_dist;
	double last_c_dist = 0.0;
	double tol;
	do
	{
		//high_resolution_clock::time_point t1 = high_resolution_clock::now();

		cumulative_dist = 0.0;
		register double temp;
		register double min_dist;
		//---------------------------Cluster Points---------------------------------
		//Calculate Euclidian distances of each point to every cluster centroid
		for (int i = 0; i < N; i++)
		{
			min_dist = 1000.0;

			for (int j = 0; j < Nc; j++)
			{
				//Calculate the Euclidian Distances of each point to every centroid
				temp = 0.0;
				for(int u = 0; u < Nv; u++)
				{
					temp += (V[i][u] - centroids[j][u]) * (V[i][u] - centroids[j][u]);
				}
				temp = sqrt(temp);
				//temp = vectors_distance(V[i], centroids[j]);
				//cout << temp;
				//cout << cumulative_dist << endl;

				//Store the minimum ED in a register, and
				//update the cluster index
				if (temp < min_dist)
				{
					//cout << temp << "--" << min_dist << "  ";
					min_dist = temp;
					classes[i] = j;
				}
			}
			cumulative_dist += min_dist;
			//cout << endl;
		}
		/*
		for (std::vector<int>::const_iterator i = classes.begin(); i != classes.end(); i++)
			std::cout << *i << ' ';
		cout << endl;
		*/

		//high_resolution_clock::time_point t2 = high_resolution_clock::now();
		//duration<double, std::milli> time_span = t2 - t1;
 
  		//std::cout << "It took me " << time_span.count() << " milliseconds." << endl;

		/*
		//Plot centroids
		std::vector<double> xss(Nc), yss(Nc);
		for(int i = 0; i < Nc; i++)
		{
			xss.at(i) = centroids[i][0];
			yss.at(i) = centroids[i][1];
		}

		//Plot Points
		std::vector<double> pxs(N), pys(N);
		for(int i = 0; i < N; i++)
		{
			pxs[i] = V[i][0];
			pys[i] = V[i][1];
		}

		//plt::scatter(xss, yss, "b+");//plt::plot(xss);//, yss, "r--");
		plt::plot(pxs, pys, "bo", xss, yss, "r*");
		plt::show();
		//*/
		//for (int j = 0; j < Nc; j++)
		//{
			//find points assigned to this cluster
		//high_resolution_clock::time_point t3 = high_resolution_clock::now();
		find_indexes(classes);
		//high_resolution_clock::time_point t4 = high_resolution_clock::now();
		//duration<double, std::milli> time_span2 = t4 - t3;
 
  		//std::cout << "It took me " << time_span2.count() << " milliseconds." << endl;
			//Compute new cluster centroid
			//compute_new_center(vec, j);
			//compute_new_center(vec);
			/*
			//Compute new cluster centroid
			int k;
			double tempx = 0.0;
			double tempy = 0.0;
			for (k = 0; k < N; k++)
			{
				//cout << vec[k] << endl;
				if (vec[k] == -1)
				{
					break;
				}
				else
				{
					tempx = tempx + V[vec[k]][0];
					tempy = tempy + V[vec[k]][1];
				}
			}	
			tempx = tempx / k;
			tempy = tempy / k;
			//cout << tempx << "," << tempy << endl;
			centroids[j][0] = tempx;
			centroids[j][1] = tempy;
			//*/
		//}


		//it_cnt++;
		tol = fabs(cumulative_dist - last_c_dist);
		
		//cout << "c_dist: " << cumulative_dist << endl;
		//cout << "last_c_dist: " << last_c_dist << endl;
		cout << "tol: " << tol << endl;
		last_c_dist = cumulative_dist;
	}while( tol > THR_KMEANS);

	cout << "Done!" << endl;
    return 0;
};
