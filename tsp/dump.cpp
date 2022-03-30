bool random_search2(void)
{
	bool hasReverted;
	bool newPair;
	do{
		hasReverted = false;
		double r_len = compute_route_len();
		unsigned short int ind1;
		unsigned short int ind2;
		do{
			// Switch 2 random cities
			ind1 = 1 + (rand() % N);
			ind2 = rand() % N;
		}while((abs(ind1 - ind2) != 1)&&(ind1>ind2));
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		for (int i = 0; i != checked.size(); ++i)
		{  	
			cout << checked[i][0] << "," << checked[i][1] << endl;
		}
		newPair = true;
		do{
			cout <<"In"<<endl;
			do{
				// Switch 2 random cities
				//ind1 = 1 + (rand() % N);
				ind2 = rand() % N;
			}while((abs(ind1 - ind2) != 1)&&(ind1>ind2));
			unsigned short int i;
			for(i = 0; i < checked_ind; i++)
			{
				cout << i << endl;
				if (( 
					(checked[i][0] == ind1) && (checked[i][1] == ind2) 
				)||( 
					(checked[i][1] == ind1) && (checked[i][0] == ind2) 
					))
				{
					newPair = false;
					break;
				}else{
					
				}
			}
			if( (i == N-1)&&(newPair == false) )
			{
				break;
			}
		}while(newPair == false);
		/*
		newPair = true;
		while((ind1 == ind2))// && (newPair == false))
		{
			cout <<"In"<<endl;
			ind2 = rand() % N;
			unsigned short int i;
			for(i = 0; i < checked_ind; i++)
			{
				cout << i << endl;
				if (( 
					(checked[i][0] == ind1) && (checked[i][1] == ind2) 
				)||( 
					(checked[i][1] == ind1) && (checked[i][0] == ind2) 
					))
				{
					newPair = false;
					break;
				}else{
					
				}
			}
			if( (i == N-1)&&(newPair == false) )
			{
				break;
			}
		}	
		/*/
		checked[checked_ind][0] = ind1;
		checked[checked_ind][1] = ind2;
		checked_ind++;

		cout << "switching " << ind1 << " with " << ind2 << endl;
		unsigned short int x_t = cities[ind1-1][0];
		unsigned short int y_t = cities[ind1-1][1];
		cities[ind1-1][0] = cities[ind2][0];
		cities[ind1-1][1] = cities[ind2][1];
		cities[ind2][0] = x_t;
		cities[ind2][1] = y_t;

		compute_distances();

		double r_len_new = compute_route_len();
		cout << "rlen: " << r_len << ", new: " << r_len_new << endl;
		if (r_len_new >= r_len)
		{
			//Revert
			hasReverted = true;
			cout << "Reverting" << endl;
			x_t = cities[ind1-1][0];
			y_t = cities[ind1-1][1];
			cities[ind1-1][0] = cities[ind2][0];
			cities[ind1-1][1] = cities[ind2][1];
			cities[ind2][0] = x_t;
			cities[ind2][1] = y_t;

			compute_distances();
		}
		cout << "A" << endl;
	}while(hasReverted == true);
	/*
	// Compute the new distances
	// Compute new columns
	for(unsigned short int i = ind1+1; i < N; i++)
	{
		dists[i][ind1] = compute_distance(cities[ind1][0], cities[ind1][1], cities[i][0], cities[i][1]);
	}

	// Compute new rows
	for(unsigned short int i = 0; i < (ind2-1); i++)
	{
		dists[i][ind2] = compute_distance(cities[ind2][0], cities[ind2][1], cities[i][0], cities[i][1]);
	}
	*/
	//dists[ind1+1][ind1] = compute_distance(cities[ind1][0], cities[ind1][1], cities[ind1][0], cities[ind1][1]);
	//dists[ind2+1][ind2] = compute_distance(cities[ind2][0], cities[ind2][1], cities[ind2][0], cities[ind2][1]);
	
	return newPair&hasReverted;
	//print(cities, dists, route);
}

void random_search(std::vector<std::vector<int>> cities_t, std::vector<std::vector<double>> dists_t)
{
	// Switch 2 random cities
	unsigned short int ind1 = rand() % N;
	unsigned short int ind2 = rand() % N;
	unsigned short int x_t = cities_t[ind1][0];
	unsigned short int y_t = cities_t[ind1][1];
	cities_t[ind1][0] = cities_t[ind2][0];
	cities_t[ind1][1] = cities_t[ind2][1];
	cities_t[ind2][0] = x_t;
	cities_t[ind2][1] = y_t;
/*
	// Compute the new distances
	// Compute new columns
	for(unsigned short int i = ind1+1; i < N; i++)
	{
		dists_t[i][ind1] = compute_distance(cities_t[ind1][0], cities_t[ind1][1], cities_t[i][0], cities_t[i][1]);
	}

	// Compute new rows
	for(unsigned short int i = 0; i < (ind2-1); i++)
	{
		dists_t[ind2][i] = compute_distance(cities_t[ind2][0], cities_t[ind2][1], cities_t[i][0], cities_t[i][1]);
	}
*/
	
	print(cities_t, dists_t, route);
}

double compute_distance(unsigned short int x1, unsigned short int y1, unsigned short int x2, unsigned short int y2)
{
	return sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
};
