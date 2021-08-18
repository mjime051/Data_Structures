#pragma once
#ifndef STACK_H
#define STACK_H

#include "pch.h"
#include <iostream>
#include <string>
#include <stdexcept>

const int MAX_SIZE = 20;

template<typename T>
class stack {
private:
	T data[MAX_SIZE];
	int size;
	

public:
	stack() {
		size = 0;
	}

	void push(T val) {
			if (size == MAX_SIZE) {
				throw std::overflow_error("Called push on full stack.");
			}
			else {
				data[size] = val;
				size++;
			}
	}

	void pop() {
			if (this->empty()) {
				throw std::out_of_range("Called pop on empty stack.");
			}
			else {
				size--;
			}
	}

	T top() {
			if (this->empty()) {
				throw std::underflow_error("Called top on empty stack.");
			}
			else {
				return data[size-1];
			}
	}

	bool empty() {
		if (size == 0) {
			return true;
		}
		else {
			return false;
		}
	}
};
#endif // !STACK_H
