#include "pch.h"
#include "Heap.h"

using namespace std;

Heap::Heap() {
	numItems = 0;
}

PrintJob* Heap::highest() {
	if (numItems > 0) {
		return arr[0];
	}
	return nullptr;
}

void Heap::enqueue(PrintJob* newPrint) {
	if (numItems != MAX_HEAP_SIZE) {
		//cout << "Im in here" << endl;
		if (numItems == 0) {
			arr[numItems] = newPrint;
			++numItems;
		}
		else {
			int x = numItems;
			while (x > 0 && arr[(x - 1) / 2]->getPriority() < newPrint->getPriority()) {
				arr[x] = arr[(x - 1) / 2];
				x = (x - 1) / 2;
			}
			arr[x] = newPrint;
			++numItems;
		}
	}
}

void Heap::dequeue() {
	if (numItems > 0) {
		//cout << "I made it in" << endl;
		PrintJob* temp = arr[0];
		arr[0] = arr[numItems - 1];
		//cout << "my new root is " << arr[0]->getPriority() << endl;
		arr[numItems - 1] = temp;
		//cout << "numItems before is " << numItems << endl;
		numItems--;
		//cout << "numItems now is " << numItems << endl;
		//cout << "I am before the loop to trickle down" << endl;
		
		trickleDown(0);
	}
}

void Heap::trickleDown(int curr) {
	int i = curr;
	//cout << "I am in trickle" << endl;
	while ((i * 2) + 1 < numItems) {
		//cout << "I have a left child at least" << endl;
		if ((i * 2) + 2 < numItems) {
			//cout << "I have a right child to take into consideration" << endl;
			int leftChild = (i * 2) + 1;
			//cout << "my left child is " << arr[leftChild]->getPriority() << endl;
			int rightChild = (i * 2) + 2;
			//cout << "my right child is " << arr[rightChild]->getPriority() << endl;
			if (arr[i]->getPriority() < arr[leftChild]->getPriority() && arr[i]->getPriority() < arr[rightChild]->getPriority()) {
				//cout << "I am less than both children" << endl;
				if (arr[leftChild]->getPriority() > arr[rightChild]->getPriority()) {
					//cout << "Switching with left child" << endl;
					PrintJob* temp = arr[i];
					arr[i] = arr[leftChild];
					arr[leftChild] = temp;
					i = (i * 2) + 1;
				}
				else {
					//cout << "Switching with right child" << endl;
					PrintJob* temp = arr[i];
					arr[i] = arr[rightChild];
					arr[rightChild] = temp;
					i = (i * 2) + 2;
				}
			}
			else if (arr[i]->getPriority() < arr[leftChild]->getPriority() && arr[i]->getPriority() > arr[rightChild]->getPriority()) {
				//cout << "I am only less than left child" << endl;
				PrintJob* temp = arr[i];
				arr[i] = arr[leftChild];
				arr[leftChild] = temp;
				i = (i * 2) + 1;
			}
			else if (arr[i]->getPriority() > arr[leftChild]->getPriority() && arr[i]->getPriority() < arr[rightChild]->getPriority()) {
				//cout << "I am only less than right child" << endl;
				PrintJob* temp = arr[i];
				arr[i] = arr[rightChild];
				arr[rightChild] = temp;
				i = (i * 2) + 2;
			}
			else {
				break;
			}
			
		}
		else {
			if (arr[curr]->getPriority() < arr[(i * 2) + 1]->getPriority()) {
				PrintJob* temp = arr[curr];
				arr[curr] = arr[(i * 2) + 1];
				arr[(i * 2) + 1] = temp;
				i = (i * 2) + 1;
			}
			else {
				break;
			}
		}
	}
}

void Heap::print() {
	if (numItems > 0) {
		//for (int i = 0; i < numItems; i++) {
		PrintJob* temp = arr[0];
		cout << "Priority: " << temp->getPriority() << ", Job Number: " << temp->getJobNumber() << ", Number of Pages: " << temp->getPages() << endl;
		//}
	}
}