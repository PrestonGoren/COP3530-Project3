#include <iostream>
#include <vector>
#include <chrono>

using namespace std;


void merge(vector<int>& toSort, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;
	vector<int> x(n1);
	vector<int> y(n2);
	for (int i = 0; i < n1; i++)
		x[i] = toSort[left + i];
	for (int j = 0; j < n2; j++)
		y[j] = toSort[mid + j + 1];

	int k = left;
	int i = 0;
	int j = 0;
	while (i < n1 && j < n2) {
		if (x[i] <= y[j]) {
			toSort[k] = x[i];
			i += 1;
		}
		else {
			toSort[k] = y[j];
			j += 1;
		}
		k += 1;
	}
	while (i < n1) {
		toSort[k] = x[i];
		i += 1;
		k += 1;
	}
	while (j < n2) {
		toSort[k] = y[j];
		j += 1;
		k += 1;
	}


}

void mergeSort(vector<int>& toSort, int left, int right) {
	int mid;
	if (left < right) {
		mid = left + (right - left) / 2;
		mergeSort(toSort, left, mid);
		mergeSort(toSort, mid + 1, right);
		merge(toSort, left, mid, right);

	}

}

int partition(vector<int>& toSort, int low, int high) {
	int pivot = toSort[low];
	int up = low;
	int down = high;

	while (up < down) {
		for (int j = up; j < high; j++) {
			if (toSort[up] > pivot)
				break;
			up += 1;
		}
		for (int j = high; j > low; j--) {
			if (toSort[down] < pivot)
				break;
			down -= 1;
		}
		if (up < down) {
			int temp = toSort[up];
			toSort[up] = toSort[down];
			toSort[down] = temp;
		}
	}
	int temp = toSort[low];
	toSort[low] = toSort[down];
	toSort[down] = temp;
	return down;

}

void quickSort(vector<int>& toSort, int low, int high) {
	if (low < high) {
		int pivot = partition(toSort, low, high);
		quickSort(toSort, low, pivot - 1);
		quickSort(toSort, pivot + 1, high);
	}

}
vector<int> countSort(vector<int>& toSort, int minVal, int maxVal) {

	//calculate range of vals and index offset
	int range = maxVal - minVal + 1;
	int offset = 0 - minVal;

	//initialize count list and results list
	vector<int> counts(range);
	vector<int> result(toSort.size());

	//fill countlist with each number's corresponding frequency
	for (int i = 0; i < toSort.size(); i++) {
		counts[toSort[i] + offset] += 1;
	}
	/*for (int i = 0; i < counts.size(); i++) {
		cout << i - offset << ": " << counts[i] << endl;
	}*/ //debug code to print count list

	//update each index of count list to be sum of previous indices
	for (int i = 0; i < counts.size(); i++) {
		if (i != 0)
			counts[i] = counts[i] + counts[i - 1];
	}

	/*for (int i = 0; i < counts.size(); i++) {
		cout << i - offset << ": " << counts[i] << endl;
	}*/ //debug code to print count list

	//fill result list with items of toSort in proper order
	for (int i = 0; i < toSort.size(); i++) {

		//the proper index is found by taking the value in counts at the index of the value in toSort
		//... an offset of -1 is required to avoid an out of bounds exception
		//... the count list is accordingly updated after the value is inserted
		//... to make sure subsequent insertions are in the proper location
		result[counts[toSort[i] + offset] - 1] = toSort[i];
		counts[toSort[i] + offset] -= 1;
	}
	//return sorted list
	return result;

}

void partition3(vector<int>& toSort, int low, int high, int& i, int& j) {
	//partition into 3 parts rather than the traditional 2
	//our vector from low -> i is the first partition (elements smaller than pivot)
	//our vector from i+1->j+1 contains all values equivalent to our pivot
	//our vector from j->high contains all values larger than pivot

	//initialize necessary components
	i = low - 1;
	j = high;
	int p = low - 1;
	int v = toSort[high];
	int q = high;
	bool breakLoop = false;

	while (true) {
		// From left, find the first element greater than
		// or equal to v. This loop will definitely
		// terminate as v is last element
		//this loop will iterate (left->right) until i is an index with a value
		//greater than or equal to v (our pivot)
		while (true) {
			if (toSort[++i] >= v) {
				break;
			}
		}

	
		//this loop will iterate (right->left) until j is an index with a value
		//less than or equal to v (our pivot)
		while (true) {
			if (toSort[--j] <= v)
				break;
			if (j == low)
				break;
		}

		//this is the base case, if i crosses to the right of j
		//or j crosses to the left of i (or if they are equal)
		//we are done in the loop
		if (i >= j)
			break;

		//swap i and j to place the value smaller than the pivot
		//on the left and the value larger on the right
		int temp = toSort[i];
		toSort[i] = toSort[j];
		toSort[j] = temp;

		//swap any occurences of pivot value in left partition to start of array
		if (toSort[i] == v) {
			p += 1;
			int temp = toSort[i];
			toSort[i] = toSort[p];
			toSort[p] = temp;
		}
		//swap any occurences of pivot value in right partition to end of array
		if (toSort[j] == v) {
			q -= 1;
			int temp = toSort[j];
			toSort[j] = toSort[q];
			toSort[q] = temp;
		}
	}

	//place pivot into proper index
	int temp = toSort[i];
		toSort[i] = toSort[high];
		toSort[high] = temp;

	// Move all occurences of pivot from beginning of array
	// to pivot location
	//we use p which we incremented when swapping to left earlier to keep track of
	//number of ocurrences

	j = i - 1;
	for (int y = low; y < p; y++) {
		int temp = toSort[y];
		toSort[y] = toSort[j];
		toSort[j] = temp;
		j -= 1;

	}
	

	//perform same process as above loop except for pivot occurences
	//at end of array
	i += 1;
	for (int y = high - 1; y > q; y--) {
		int temp = toSort[i];
		toSort[i] = toSort[y];
		toSort[y] = temp;
		i += 1;

	}
	
}
void quickSort3(vector<int>& toSort, int low, int high) {


	if (high > low) {
		int i = 0;
		int j = 0;

		partition3(toSort, low, high, i, j);
		quickSort3(toSort, low, j);
		quickSort3(toSort, i, high);

	}

}

//helper function to check if a vector is sorted in ascending order
bool checkSorted(vector<int>& toCheck) {
	for (int i = 0; i < toCheck.size(); i++) {
		if (i != 0) {
			if (toCheck[i] < toCheck[i - 1])
				return false;
		}
	}
	return true;
}
vector<int> genList(int listChoice) {
	vector<int> resultList;
	if (listChoice == 1) {
		for (int i = 0; i < 100000; i++) {
			//list with values from -30 to 30
			int randNumber = (rand() % 101) - 50;
			resultList.push_back(randNumber);
		}
	}
	else if (listChoice == 2) {
		for (int i = 0; i < 100000; i++) {
			//list with values from -75000 to 75000
			int randNumber = (rand() % 150001) - 75000;
			resultList.push_back(randNumber);
		}
	}
	else if (listChoice == 3) {
		for (int i = 0; i < 250000; i++) {
			//list with values from -30 to 30
			int randNumber = (rand() % 101) - 50;
			resultList.push_back(randNumber);
		}
	}
	else if (listChoice == 4) {
		for (int i = 0; i < 250000; i++) {
			//list with values from -75000 to 75000
			int randNumber = (rand() % 150001) - 75000;
			resultList.push_back(randNumber);
		}
	}
	return resultList;
}


int main() {

	//compare: countsort, mergesort, quicksort, quicksort3
	//with different lists: length/range can be modified
	vector<int> toSort;
	int randNumber;
	chrono::steady_clock::time_point begin;
	chrono::steady_clock::time_point end;
	
	while (true) {
		cout << "Enter: " << endl;
		cout << "1 to time the sorting speed of a specific algorithm" << endl;
		cout << "2 to compare times of all implemented sorting algorithms on a specific list" << endl;
		cout << "3 to compare... EVERYTHING" << endl;
		cout << "5 to exit" << endl;
		int input;
		cin >> input;
		if (input < 1 || input>5) {
			cout << "Invalid input... try again!" << endl;
		}
		
		if (input == 1) {
			int listChoice;
			cout << "Choose a list to sort: " << endl;
			cout << "1, 100,000 integers between -50 and 50" << endl;
			cout << "2, 100,000 integers between -75000 and 75000" << endl;
			cout << "3, 250,000 integers between -50 and 50" << endl;
			cout << "4, 250,000 integers between -75000 and 75000" << endl;
			cin >> listChoice;
			vector<int> listToSort = genList(listChoice);
			
			cout  << "Enter: " << endl;
			cout << "1 to time the sorting speed of Count Sort" << endl;
			cout << "2 to time the sorting speed of Merge Sort" << endl;
			cout << "3 to time the sorting speed of Quick Sort" << endl;
			cout << "4 to time the sorting speed of Quick Sort (3 partition variant)" << endl;
			cin >> input;
			cout << endl;
			if (input == 1) {
				if (listChoice == 1 || listChoice == 3) {
					begin = chrono::steady_clock::now();
					listToSort = countSort(listToSort, -50, 50);
					end = chrono::steady_clock::now();
				}
				else {
					begin = chrono::steady_clock::now();
					listToSort = countSort(listToSort, -75000, 75000);
					end = chrono::steady_clock::now();
				}
				cout << "Count Sort took: " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "(sec)" << endl;

			}else if (input == 2) {
				
				begin = chrono::steady_clock::now();
				mergeSort(listToSort, 0, listToSort.size()-1);
				end = chrono::steady_clock::now();

				cout << "Merge Sort took: " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "(sec)" << endl;

			}
			else if (input == 3) {

				begin = chrono::steady_clock::now();
				quickSort(listToSort, 0, listToSort.size()-1);
				end = chrono::steady_clock::now();

				cout << "Quick Sort took: " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "(sec)" << endl;

			}
			else if (input == 4) {

				begin = chrono::steady_clock::now();
				quickSort3(listToSort, 0, listToSort.size()-1);
				end = chrono::steady_clock::now();

				cout << "Quick Sort (3 partition variant) took: " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "(sec)" << endl;

			}
			cout << endl;

		}
		else if (input == 2) {
			int listChoice;
			cout << "Choose a list to sort: " << endl;
			cout << "1, 100,000 integers between -50 and 50" << endl;
			cout << "2, 100,000 integers between -75000 and 75000" << endl;
			cout << "3, 250,000 integers between -50 and 50" << endl;
			cout << "4, 250,000 integers between -75000 and 75000" << endl;
			
			cin >> listChoice;
			
			vector<int> listToSort = genList(listChoice);
			vector<int> listCopy = listToSort;

			if (listChoice == 1 || listChoice == 3) {
				begin = chrono::steady_clock::now();
				listToSort = countSort(listToSort, -50, 50);
				end = chrono::steady_clock::now();
			}
			else {
				begin = chrono::steady_clock::now();
				listToSort = countSort(listToSort, -75000, 75000);
				end = chrono::steady_clock::now();
			}
			cout << endl;
			cout << "Count Sort took: " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "(sec)" << endl;
			listToSort = listCopy;

			begin = chrono::steady_clock::now();
			mergeSort(listToSort, 0, listToSort.size() - 1);
			end = chrono::steady_clock::now();
			cout << "Merge Sort took: " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "(sec)" << endl;
			listToSort = listCopy;

			begin = chrono::steady_clock::now();
			quickSort(listToSort, 0, listToSort.size() - 1);
			end = chrono::steady_clock::now();
			cout << "Quick Sort took: " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "(sec)" << endl;
			listToSort = listCopy;

			begin = chrono::steady_clock::now();
			quickSort3(listToSort, 0, listToSort.size() - 1);
			end = chrono::steady_clock::now();
			cout << "Quick Sort (3 partition variation) took: " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "(sec)" << endl;

			cout << endl;


		}
		else if (input == 3) {
		cout << endl;
			for (int listChoice = 1; listChoice < 5; listChoice++) {
				if (listChoice == 1) {
					cout << "Performances with 100,000 integers between -50 and 50" << endl;
				}
				else if (listChoice == 2) {
					cout << "Performances with 100,000 integers between -75000 and 75000" << endl;
				}
				else if (listChoice == 3) {
					cout << "Performances with 250,000 integers between -50 and 50" << endl;
				}
				else if (listChoice == 4) {
					cout << "Performances with 250,000 integers between -75000 and 75000" << endl;
				}
				vector<int> listToSort = genList(listChoice);
				vector<int> listCopy = listToSort;

				if (listChoice == 1 || listChoice == 3) {
					begin = chrono::steady_clock::now();
					listToSort = countSort(listToSort, -50, 50);
					end = chrono::steady_clock::now();
				}
				else {
					begin = chrono::steady_clock::now();
					listToSort = countSort(listToSort, -75000, 75000);
					end = chrono::steady_clock::now();
				}
				cout << endl;
				cout << "Count Sort took: " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "(sec)" << endl;
				listToSort = listCopy;

				begin = chrono::steady_clock::now();
				mergeSort(listToSort, 0, listToSort.size() - 1);
				end = chrono::steady_clock::now();
				cout << "Merge Sort took: " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "(sec)" << endl;
				listToSort = listCopy;

				begin = chrono::steady_clock::now();
				quickSort(listToSort, 0, listToSort.size() - 1);
				end = chrono::steady_clock::now();
				cout << "Quick Sort took: " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "(sec)" << endl;
				listToSort = listCopy;

				begin = chrono::steady_clock::now();
				quickSort3(listToSort, 0, listToSort.size() - 1);
				end = chrono::steady_clock::now();
				cout << "Quick Sort (3 partition variation) took: " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << "(sec)" << endl;

				cout << endl;
			}
		}

		if (input == 5) {
			break;
		}
	}

		


	//generate list to be sorted

	//lengths: 25,000 ; 100,000 ; 500,000
	//
/*
	for (int i = 0; i < 100000; i++) {
		
		randNumber = (rand() % 61) - 30;
		toSort.push_back(randNumber);
	}
	vector<int> toSortCopy = toSort;
	
	//toSort = countSort(toSort, -10, 10);
	begin = chrono::steady_clock::now();
	quickSort(toSort, 0, toSort.size() - 1);
	end = chrono::steady_clock::now();
	std::cout << "Time to sort (sec) = " << (chrono::duration_cast<chrono::microseconds>(end - begin).count()) / 1000000.0 << endl;

	cout << checkSorted(toSort) << endl;
	cout << checkSorted(toSortCopy) << endl;
	*/



}

