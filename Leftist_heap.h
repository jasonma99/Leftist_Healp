/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  x237ma@uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Fall 2018
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/
#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Leftist_node.h"

template <typename Type>
class Leftist_heap {
	private:
		Leftist_node<Type> *root_node; //a pointer to the root node
		int heap_size; //number of elements in the heap

	public:
		Leftist_heap();
		~Leftist_heap();

		void swap( Leftist_heap &heap );
		
		//accessors
		bool empty() const; //return true if the heap is empty O(1)
		int size() const; //return the number of nodes in the heap O(1)
		int null_path_length() const; //return the null_path_length of the root node O(1)
		Type top() const; //Returns the element at the top of the heap. If the tree is empty, this function throws an underflow exception. (O(1))
		int count( Type const &obj ) const; //Return the number of instances of the argument in the heap. (O(n))

		//mutators
		void push( Type const &obj ); //(known as insert in ADT definition) Insert the new element into the heap by creating a new leftist node and calling push on the root node using root_node as a second argument. Increment the heap size. (O(ln(n))).
		Type pop(); //(known as extract-min in ADT definition) Pop the least element in the heap and delete its node (extracts min from the heap). If the tree is empty, this function throws an underflow exception. Otherwise, the left sub-tree of the root node is made the root node and the right-sub tree of the original root node is pushed into the new root node. Return the element in the popped node and decrement the heap size. (O(ln(n)))
		void clear();//Call clear on the root node and reset the root node and heap size. (O(n))

	// Friends
	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Leftist_heap<T> const & );
};

template <typename Type>
Leftist_heap<Type>::Leftist_heap(): //constructor
root_node( nullptr ),
heap_size( 0 ) {
	// empty constructor
}

template <typename Type> //destructor
Leftist_heap<Type>::~Leftist_heap() {
	clear();  // might as well use it...
}

template <typename Type>
void Leftist_heap<Type>::swap( Leftist_heap<Type> &heap ) {
	std::swap( root_node, heap.root_node );
	std::swap( heap_size, heap.heap_size );
}

// STRONG HINT:  Write a default definition of each function, even if it only returns the default value (false, 0, or Type()).
// Once you have done this, you can proceed and implement the member functions one at a time.  If you do not, and just start implementing the member functions so that you can't compile and test your function, good luck. :-)
template <typename Type>
bool Leftist_heap<Type>::empty() const{
	return (heap_size==0);
}

template <typename Type>
int Leftist_heap<Type>::size() const{
	return heap_size;
}

template <typename Type>
int Leftist_heap<Type>::null_path_length() const{
	return root_node->null_path_length();
}

template <typename Type>
Type Leftist_heap<Type>::top() const{
	if (empty())
		throw underflow();
	return root_node->retrieve();
}

template <typename Type> //O(n)
int Leftist_heap<Type>::count( Type const &obj ) const{
	return root_node->count(obj);
}

template <typename Type>
void Leftist_heap<Type>::push( Type const &obj ){
	Leftist_node<Type> *GG = new Leftist_node<Type>(obj);
	root_node->push(GG, root_node);
	heap_size++;
}

template <typename Type>
Type Leftist_heap<Type>::pop(){
	if (this->empty())
		throw underflow();
	Type value = root_node->retrieve();
	Leftist_node<Type> *temp = root_node;
	root_node = root_node->left();
	root_node->push(temp->right(),root_node);
	delete temp;
	heap_size--;
	return value;
}

template <typename Type>
void Leftist_heap<Type>::clear(){
	root_node->clear();
	root_node = nullptr;
	heap_size = 0;
}

// You can modify this function however you want:  it will not be tested
template <typename T>
std::ostream &operator<<( std::ostream &out, Leftist_heap<T> const &heap ) {
	return out;
}
// Is an error showing up in ece250.h or elsewhere? Did you forget a closing '}' ?
#endif