#include<iostream>
#include<vector>

#ifndef HEAP_H
#define HEAP_H 1

/*

// bool is_empty(){
// void swap(int x, int y){
// int lchild(int index){
// int rchild(int index){
// int parent(int index){
// void insert_at_end(dataStruct& x){
// void display()
// dataStruct remove(){
// void trickle_up(int index){
// void trickledown(int index){
// dataStruct& max(){
// void heapify()

*/

template <class dataStruct>
class MinHeap{
public:
	int size; //index of the last element
	std::vector<dataStruct> arr;
	MinHeap(){
		size = -1;
	}

	bool is_empty(){
		if (size >= 0)
			return false;
		else
			return true;
	}

	void swap(int x, int y){
		dataStruct temp = arr[x];
		arr[x] = arr[y];
		arr[y] = temp;
	}

	int lchild(int index){
		//return zero if no left child
		if (2 * index + 1 > size){
			return 0;
		}
		else
			return 2 * index + 1;
	}
	int rchild(int index){
		if (2 * index + 2 > size){
			return 0;
		}
		else
			return 2 * index + 2;
	}
	int parent(int index){
		return (index - 1) / 2;
	}

	void insert_at_end(dataStruct x){
		size += 1;
		arr.push_back(x);
	}

	void display(){
		for (int i = 0; i <= size; ++i){
			std::cout << arr[i] << ", ";
		}
		std::cout << std::endl;
	}

	dataStruct &min(){
		return arr[0];
	}
	void heapify() {
		for (int i = (size + 1) / 2; i >= 0; i--){
			trickledown(i);
		}
	}
	dataStruct remove_min() {
		dataStruct temp = arr[0];
		arr[0] = arr[size];
		size -= 1;
		arr.pop_back();
		trickledown(0);
		return temp;
	}
	void bubble_up(int index) {
		while (arr[parent(index)] > arr[index]){
			swap(index, parent(index));
		}
		return;
	}
	void trickledown(int index) {
		if (size == 0) {
			return;
		}
		if (index <= size) {
			//only enter if index is valid
			//check if it has both children
			int l = lchild(index), r = rchild(index);
			if (!l && !r) {
				//if no children
				return;
			}
			else if (!r) {
				//if no right child
				if (arr[l] < arr[index]) {
					swap(l, index);
					return;
				}
			}
			else if (l && r) {
				//if it has both children
				int min = index;
				if (arr[l] < arr[min]) {
					min = l;
				}
				if (arr[r] < arr[min]){
					min = r;
				}
				if (min != index){
					swap(min, index);
					trickledown(min);
				}
			}
		}
		else {
			//invalid index
			return;
		}
	}


};

template <class dataStruct>
class MaxHeap{
public:
	int size; //index of the last element
	std::vector<dataStruct> arr;

	MaxHeap(){
		size = -1;
	}

	bool is_empty(){
		if (size >= 0)
			return false;
		else
			return true;
	}

	void swap(int x, int y){
		dataStruct temp = arr[x];
		arr[x] = arr[y];
		arr[y] = temp;
	}

	int lchild(int index){
		//return zero if no left child
		if (2 * index + 1 > size){
			return 0;
		}
		else
			return 2 * index + 1;
	}
	int rchild(int index){
		if (2 * index + 2 > size){
			return 0;
		}
		else
			return 2 * index + 2;
	}
	int parent(int index){
		return (index - 1) / 2;
	}

	void insert_at_end(dataStruct x){
		size += 1;
		arr.push_back(x);
	}

	void display(){
		for (int i = 0; i <= size; ++i){
			std::cout << arr[i] << ", ";
		}
		std::cout << std::endl;
	}

	dataStruct remove_max(){
		dataStruct temp = arr[0];
		arr[0] = arr[size];
		size -= 1;
		arr.pop_back();
		trickledown(0);
		return temp;
	}
	void bubble_up(int index){
		while (arr[parent(index)] < arr[index]){
			swap(index, parent(index));
		}
		return;
	}
	void trickledown(int index){
		if (size == 0){
			return;
		}
		if (index <= size){
			//only enter if index is valid
			//check if it has both children
			int l = lchild(index), r = rchild(index);
			if (!l && !r){
				//if no children
				return;
			}
			else if (!r){
				//if no right child
				if (arr[l] > arr[index]){
					swap(l, index);
					return;
				}
			}
			else if (l && r){
				//if it has both children
				int max = index;
				if (arr[l] > arr[max]){
					max = l;
				}
				if (arr[r] > arr[max]){
					max = r;
				}
				if (max != index){
					swap(max, index);
					trickledown(max);
				}
			}
		}
		else{
			return;
		}
	}

	dataStruct &max(){
		return arr[0];
	}
	void heapify(){
		for (int i = (size + 1) / 2; i >= 0; i--){
			trickledown(i);
		}
	}
};

#endif