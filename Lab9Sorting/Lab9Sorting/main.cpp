#include "pch.h"
#include <iostream>
#include "time.h"
#include <algorithm>

using namespace std;

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000;

int Partition_medianOfThree(int numbers[], int i, int k) {
	int leftMost = 0;
	int midpoint = 0;
	int rightMost = 0;
	int j = 0;
	int pivot = 0;
	int low = 0;
	int high = 0;
	int temp = 0;
	bool done = false;

	leftMost = numbers[i];
	midpoint = numbers[i + (k - i) / 2];
	rightMost = numbers[k];

	//Need to find pivot using medianOfThree method
	j = min(leftMost, rightMost);
	j = max(j, midpoint);

	pivot = j;
	low = i;
	high = k;

	while (!done) {
		while (numbers[low] < pivot) {
			++low;
		}

		while (numbers[high] > pivot) {
			--high;
		}

		if (low >= high) {
			done = true;
		}
		else {
			temp = numbers[low];
			numbers[low] = numbers[high];
			numbers[high] = temp;

			++low;
			--high;
		}
	}
	return high;
}

int Partition_midpoint(int numbers[], int i, int k) {
	int midpoint = 0;
	int pivot = 0;
	int low = 0;
	int high = 0;
	int temp = 0;
	bool done = false;

	midpoint = i + (k - i) / 2;
	pivot = numbers[midpoint];

	low = i;
	high = k;

	while (!done) {
		while (numbers[low] < pivot) {
			++low;
		}

		while (numbers[high] > pivot) {
			--high;
		}

		if (low >= high) {
			done = true;
		}
		else {
			temp = numbers[low];
			numbers[low] = numbers[high];
			numbers[high] = temp;

			++low;
			--high;
		}
	}
	return high;
}
void Quicksort_midpoint(int numbers[], int i, int k) {
	int j = 0;

	if (i >= k) {
		return;
	}

	j = Partition_midpoint(numbers, i, k);
	Quicksort_midpoint(numbers, i, j);
	Quicksort_midpoint(numbers, j + 1, k);
}

void Quicksort_medianOfThree(int numbers[], int i, int k) {
	int j = 0;

	if (i >= k) {
		return;
	}

	j = Partition_medianOfThree(numbers, i, k);
	Quicksort_medianOfThree(numbers, i, j);
	Quicksort_medianOfThree(numbers, j + 1, k);
}

void InsertionSort(int numbers[], int numbersSize) {
	int i = 0;
	int j = 0;
	int temp = 0;

	for (i = 1; i < numbersSize; i++) {
		j = i;

		while (j > 0 && numbers[j] < numbers[j - 1]) {
			temp = numbers[j];
			numbers[j] = numbers[j - 1];
			numbers[j - 1] = temp;

			--j;
		}
	}
}

int genRandInt(int low, int high) {
	return low + rand() % (high - low + 1);
}
void fillArrays(int arr1[], int arr2[], int arr3[]) {
	for (int i = 0; i < NUMBERS_SIZE; ++i) {
		arr1[i] = genRandInt(0, NUMBERS_SIZE);
		arr2[i] = arr1[i];
		arr3[i] = arr1[i];
	}
}

int main(){
	int quickMidArray[NUMBERS_SIZE];
	int quickMedArray[NUMBERS_SIZE];
	int insertArray[NUMBERS_SIZE];

	fillArrays(quickMidArray, quickMedArray, insertArray);
	
	clock_t Start = clock();
	Quicksort_midpoint(quickMidArray, 0, NUMBERS_SIZE - 1);
	clock_t End = clock();
	int elapsedTime = (End - Start) / CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
	cout << "The elapsed time for Quicksort_midpoint() was " << elapsedTime << "ms" << endl;
	
	Start = clock();
	Quicksort_medianOfThree(quickMedArray, 0, NUMBERS_SIZE - 1);
	End = clock();
	int elapsedTime2 = (End - Start) / CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
	cout << "The elapsed time for Quicksort_medianOfThree() was " << elapsedTime2 << "ms" << endl;
	
	Start = clock();
	InsertionSort(insertArray, NUMBERS_SIZE - 1);
	End = clock();
	int elapsedTime3 = (End - Start) / CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
	cout << "The elapsed time for InsertionSort() was " << elapsedTime3 << "ms" << endl;
	
}

