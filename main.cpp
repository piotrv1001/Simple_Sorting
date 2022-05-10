#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <algorithm>

using namespace std;

void generateRandomIntArray(int arr[], int N) {
	for (int i = 0; i < N; i++) {
		arr[i] = i;
	}
	random_shuffle(&arr[0], &arr[N]);
}

void generateRandomStringArray(string arr[], istream& stream, int N) {
	int counter = 0;
	string line;
	while (getline(stream, line) && counter < N) {
		arr[counter] = line;
		counter++;
	}
	random_shuffle(&arr[0], &arr[N]);
}

template<typename T>
bool check_if_sorted(T arr[], int N) {
	int i = 1;
	bool is_sorted = true;
	while ((i < N) && is_sorted) {
		if (arr[i - 1] > arr[i])
		{
			is_sorted = false;
			break;
		}	
		i++;
	}
	return is_sorted;
}

template<typename T>
void printArray(T arr[], int N) {
	for (int i = 0; i < N; i++) {
		cout << " " << arr[i];
	}
	cout << endl;
}

template <typename T>
void bubbleSort(T arr[], int N) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N - i - 1; ++j) {
			if (arr[j] > arr[j + 1]) {
				//swap elements
				T temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

template<typename T>
void selectionSort(T arr[], int N) {
	for (int i = 0; i < N - 1; i++) {
		int min = i;
		for (int j = i + 1; j < N; j++) {
			if (arr[j] < arr[min])
				min = j;
		}
		//swap elements
		T temp = arr[i];
		arr[i] = arr[min];
		arr[min] = temp;
	}
}

template<typename T>
void insertionSort(T arr[], int N) {
	for (int i = 1; i < N; i++) {
		T key = arr[i];
		int j = i - 1;
		while (key < arr[j] && j >= 0) {
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = key;
	}
}

template<typename T>
void bubbleSortImproved(T arr[], int N) {
	for (int i = 0; i < N; ++i) {
		bool swapped = false;
		for (int j = 0; j < N - i - 1; ++j) {
			if (arr[j] > arr[j + 1]) {
				//swap elements
				T temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;

				swapped = true;
			}
		}
		if (!swapped)
			break;
	}
}

template<typename T>
int binarySearch(T arr[], T item, int low, int high) {
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if (arr[mid] == item)
			return mid;
		else if (arr[mid] < item)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return -1;
}

template<typename T>
void binaryInsertionSort(T arr[], int N) {
	for (int i = 1; i < N; i++) {
		T key = arr[i];
		int pos = binarySearch(arr, key, 0, i - 1);
		int j = i - 1;
		while (key < arr[j] && j >= pos) {
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = key;
	}
}

int main() {

	// generate sample data
	const int dataSize = 32000;
	int* data1 = new int[dataSize];
	string* data2 = new string[dataSize];
	generateRandomIntArray(data1, dataSize);

	ifstream file("english.txt"); // English Dictionary
	if (file) {
		generateRandomStringArray(data2, file, dataSize);
	}
	file.close();

	// measure execution time
	chrono::time_point<chrono::system_clock> start, end;
	start = chrono::system_clock::now();

	if(!check_if_sorted<string>(data2,dataSize))
		bubbleSort<string>(data2, dataSize);

	end = chrono::system_clock::now();
	chrono::duration<double> executionTime = end - start;
	cout << "Execution time: " << executionTime.count()<< "s" << endl;
	if (check_if_sorted<string>(data2, dataSize))
		cout << "Sorted succesfully!" << endl;

	delete[] data1;
	delete[] data2;

	return 0;
}