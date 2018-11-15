
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

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
		Leftist_node *left_tree; //A pointer to the left subtree
		Leftist_node *right_tree; //A pointer to the right subtree
		int heap_null_path_length; //The null-path length of a tree is defined as the shortest path to a node that has an empty sub-tree. This can be calculated as follows: i) an empty node has a null-path length of -1, otherwise, ii) the null-path length of a node is one plus the minimum of the null-path lengths of the two children. Note that a consequence of the second point is that a node with no children (a leaf node) or a node with exactly one child has a null-path length of 0.

	public:
		Leftist_node( Type const & );

		Type retrieve() const; //Returns the element stored in this node. (O(1))
		bool empty() const;
		Leftist_node *left() const; //Returns the address of the left sub-tree. (O(1))
		Leftist_node *right() const; //Returns the address of the right sub-tree. (O(1))	
		int count( Type const &obj ) const; //Returns the number of instances of the argument in this sub-tree. (O(n))
		int null_path_length() const; //Returns the member variable null-path length unless this is the null pointer, in which case, return -1. (O(1))

		void push( Leftist_node *new_heap, Leftist_node *&ptr_to_this);
		void clear(); //If this is nullptr, return; otherwise, call clear on the left sub-tree, then on the right, and finally delete this. (O(n))
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

template <typename Type>
Type Leftist_node<Type>::retrieve() const{
	return element;
}

template <typename Type>
bool Leftist_node<Type>::empty() const {
	return ( this == nullptr );
}

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::left() const{
	return left_tree;
} 

template <typename Type>
Leftist_node<Type> *Leftist_node<Type>::right() const{
	return right_tree;
}

template <typename Type>  //O(n)
int Leftist_node<Type>::count( Type const &obj) const{
	int ret = 0;
	if (this->left()!=nullptr)
		ret += left_tree->count(obj);
	if (this->right()!=nullptr)
		ret += right_tree->count(obj);
	if (this->retrieve()==obj)
		ret += 1;
	return ret;
}

template <typename Type>
int Leftist_node<Type>::null_path_length() const{
	if (this==nullptr){
		return -1;
	}
	return heap_null_path_length;
}

template <typename Type>
void Leftist_node<Type>::push( Leftist_node *new_heap, Leftist_node *&ptr_to_this ){
	if (new_heap==nullptr)
		return;
	else{
		if (ptr_to_this==nullptr){
			ptr_to_this = new_heap;
			return;
		}
		else{
			if (ptr_to_this->element<=new_heap->retrieve()){
				push(new_heap,ptr_to_this->right_tree);
			}
			else {
				Leftist_node *temp = ptr_to_this;
				ptr_to_this = new_heap;
				push(temp, ptr_to_this->right_tree);
			}	
		}
	}
	ptr_to_this->heap_null_path_length = 1+std::min(ptr_to_this->left_tree->null_path_length(),ptr_to_this->right_tree->null_path_length());
		if (ptr_to_this->left_tree->null_path_length()<ptr_to_this->right_tree->null_path_length())
			std::swap(ptr_to_this->left_tree, ptr_to_this->right_tree);
		//std::cout<<ptr_to_this->heap_null_path_length;
}
template <typename Type>
void Leftist_node<Type>::clear(){
	if (this==nullptr)
		return;
	left_tree->clear();
	right_tree->clear();
	delete this;
}
#endif
