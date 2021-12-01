#pragma once
#include<iostream>
using namespace std;
template <typename T>
class node {

public:
	T data;
	node<T>* next;
	
	node() : next(nullptr) {}
	node(const T& item, node<T>* ptr = nullptr) :data(item), next(ptr) {}
};


template <typename T>
class myLST {
private:
	node<T>* head;
	node<T>* tail;
public:
	myLST() {
		try {
			head = tail = new node<T>();
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		}
	myLST(const myLST<T>& other) ;
	myLST(myLST<T>&& other) = delete;
	void push_Back(T& data);
	void push_Front(T& data);
	void pop_Front();
	void clear();
	void init();
	bool empty();
	int size();
	T& front()const;

	
	~myLST() {
		while (head->next != nullptr) {
			node<T>* temp = head;
			head = head->next;
			delete temp;
		}
		delete head;
	}

	myLST<T>& operator=(const myLST<T>& other);
	myLST<T>& operator=(myLST<T>&& other) = delete;

	
	class iterator {
		friend class myLST;
	private:
		node<T>* nodePtr;

		iterator(node<T>* newPtr) : nodePtr(newPtr) {}
	public:
		
		iterator() : nodePtr(nullptr) {}

		
		bool operator!=(const iterator& itr) {
			return nodePtr != itr.nodePtr;
		}

		
		T& operator*(){
			return nodePtr->next->data;
		}
		T* operator->() {
			return &(nodePtr->next->data);
		}

		iterator operator++(int) {
			iterator temp = *this;
			nodePtr = nodePtr->next;
			return temp;
		}
	}; 
	class const_iterator {
		friend class myLST;
	private:
		node<T>* nodePtr;
		const_iterator(node<T>* newPtr) : nodePtr(newPtr) {}
	public:
		const_iterator() : nodePtr(nullptr) {}
		bool operator!=(const const_iterator& itr) const {
			return nodePtr != itr.nodePtr;
		}

		
		T& operator*() const {
			return nodePtr->next->data;
		}
	};




	const_iterator c_begin() const{
		return const_iterator(head);
	}

	const_iterator c_end() const{
		return const_iterator(tail);
	}
	iterator begin()  {
		return iterator(head);
	}

	iterator end()  {
		return iterator(tail);
	}

	iterator insert(iterator position, const T& value) {
		node<T>* newNode = nullptr;
		try {
			newNode = new node<T>(value, position.nodePtr->next);
		}
		catch (bad_alloc & ex)
		{
			cout << ex.what();
			exit(1);
		}
		if (position.nodePtr == tail) tail = newNode;
		position.nodePtr->next = newNode;
		return position;
	}

	iterator erase(iterator position) {
		node<T>* toDelete = position.nodePtr->next;
		position.nodePtr->next = position.nodePtr->next->next;
		if (toDelete == tail) tail = position.nodePtr;
		delete toDelete;
		return position;
	}

};



template<typename T>
inline myLST<T>::myLST(const myLST<T>& other){
	node<T> *cpCurrent = other.head;
	node<T>* lsCurrent = nullptr;


		if (cpCurrent) {
			try {
				head = new node<T>(cpCurrent->data);
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			lsCurrent = head;
			cpCurrent = cpCurrent->next;
		}
		while (cpCurrent) {
			node<T>* newNode = nullptr;
			try {
				 newNode = new  node<T>(cpCurrent->data);
			}
			catch (bad_alloc & ex)
			{
				cout << ex.what();
				exit(1);
			}
			lsCurrent->next = newNode;
			lsCurrent = lsCurrent->next;
			cpCurrent = cpCurrent->next;
		}
}

template<typename T>
inline void myLST<T>::push_Back(T& data)
{
	node<T>* newNode = nullptr;
	try {
		newNode = new node<T>(data);
	}
	catch (bad_alloc & ex)
	{
		cout << ex.what();
		exit(1);
	}
	if (tail) {

		tail->next = newNode;

		tail = newNode;
	}
	else {
		
		 head->next=tail= newNode;
	}
}

template<typename T>
inline void myLST<T>::push_Front(T& data){
	node<T>* newNode = nullptr;
	try {
	 newNode = new node<T>(data);
	}
	catch (bad_alloc & ex)
	{
		cout << ex.what();
		exit(1);
	}
	if (head->next) {
		newNode->next = head->next;
		head->next = newNode;
	}
	else {
		head->next = tail = newNode;
	}
}

template<typename T>
inline void myLST<T>::pop_Front(){
	if (head->next) {
		node<T>* temp = head->next;
		head->next = temp->next;
		delete temp;
	}
}

template<typename T>
inline void myLST<T>::clear()
{
	node<T>* curr;
	while (head->next != nullptr)
	{
		curr = head->next;
		head->next = head->next->next;
		delete curr;
	}
	tail = nullptr;
}

template<typename T>
inline void myLST<T>::init()
{
	tail = nullptr;
}

template<typename T>
inline bool myLST<T>::empty(){
	int s = size();
	return s;
}

template<typename T>
inline int myLST<T>::size(){
	int size = 0;
	node<T>* curr = head->next;
	while (curr){
		curr = curr->next;
		size++;
	}
	return size;
}

template<typename T>
inline T& myLST<T>::front()const{
	if (head->next)
		return head->next->data;
	else
		break;

}

template<typename T>
inline myLST<T>& myLST<T>::operator=(const myLST<T>& other){
	myLST<T> temp(other);
	std::swap(temp.head, head);
	return *this;
}

