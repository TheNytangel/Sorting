/*
	Sorting
	Christopher Peterson
	7/15/17
*/

#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <queue>

using namespace std;


void makeHeap(int tempArray[], int heapSize, int node);
clock_t heapSort(queue<int> numbers);
clock_t bubbleSort(queue<int> numbers);

int main()
{
	// Read values from files
	queue<int> numbers;

	for (int i = 10; i <= 1000000; i *= 10)
	{
		///////////////////////////////

		// Open file
		ifstream numberFile;
		numberFile.open("num" + to_string(i) + ".dat");

		if (numberFile.is_open())
		{
			string fileLine;

			// Loop through and get each number
			while (getline(numberFile, fileLine))
			{
				try
				{
					// Try to convert the line to an integer and add it to the queue
					numbers.push(stoi(fileLine));
				}
				catch(...) {}
			}

			// Close the file
			numberFile.close();
		}

		///////////////////////////////

		cout << "Bubble sort time on " << i << " items: " << (float)bubbleSort(numbers) / CLOCKS_PER_SEC << " seconds\n";
		cout << "Heap sort time on " << i << " items: " << (float)heapSort(numbers) / CLOCKS_PER_SEC << " seconds\n";

		///////////////////////////////

		// Clear the queue for the next round of numbers
		int temp = numbers.size();
		for (int i = 0; i < temp; ++i)
		{
			numbers.pop();
		}

		///////////////////////////////
	}

	cout << endl;

	system("pause");
	return 0;
}

clock_t heapSort(queue<int> numbers)
{
	int arraySize = numbers.size();

	// Make a copy of the numbers
	int * tempArray = new int[arraySize];

	for (int i = 0; i < arraySize; ++i)
	{
		tempArray[i] = numbers.front();
		numbers.pop();
	}
	////////////

	///
	/// Start timing
	///

	clock_t t = clock();

	// Rearrange array
	for (int i = (arraySize / 2) - 1; i >= 0; --i)
	{
		makeHeap(tempArray, arraySize, i);
	}

	for (int i = arraySize - 1; i >= 0; --i)
	{
		// Swap the current value with the end
		int temp = tempArray[i];

		tempArray[i] = tempArray[0];
		tempArray[0] = temp;

		// Make a new heap
		makeHeap(tempArray, i, 0);
	}

	t = clock() - t;

	///
	/// Stop timing
	///

	delete[] tempArray;

	return t;
}

void makeHeap(int tempArray[], int heapSize, int node)
{
	// Largest number (index) (default to node size)
	int largest = node;
	// Left number (index)
	int leftChild = 2 * node + 1;
	// Right number (index)
	int rightChild = 2 * node + 2;

	// Check if the child on the left is the largest now (while still within the heap)
	if (leftChild < heapSize && tempArray[leftChild] > tempArray[largest])
	{
		largest = leftChild;
	}

	// Check if the child on the right is the largest now (while still within the heap)
	if (rightChild < heapSize && tempArray[rightChild] > tempArray[largest])
	{
		largest = rightChild;
	}

	if (largest != node)
	{
		// Swap the values
		int temp = tempArray[node];

		tempArray[node] = tempArray[largest];
		tempArray[largest] = temp;

		// Recursively make a new heap
		makeHeap(tempArray, heapSize, largest);
	}
}

clock_t bubbleSort(queue<int> numbers)
{
	int arraySize = numbers.size();

	// Make a copy of the numbers
	int * tempArray = new int[arraySize];

	for (int i = 0; i < arraySize; ++i)
	{
		tempArray[i] = numbers.front();
		numbers.pop();
	}
	////////////

	bool swap = true;

	///
	/// Start timing
	///

	clock_t t = clock();

	for (int i = 0; i < arraySize && swap; ++i)
	{
		swap = false;

		for (int j = 0; j < arraySize - 1 - i; ++j)
		{
			if (tempArray[j] > tempArray[j + 1])
			{
				swap = true;

				int temp = tempArray[j];

				tempArray[j] = tempArray[j + 1];
				tempArray[j + 1] = temp;
			}
		}
	}

	t = clock() - t;

	///
	/// Stop timing
	///

	delete[] tempArray;

	return t;
}
