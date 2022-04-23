#include "param.h"
#include "proc.h"



struct proc *H[NPROC];
int size = -1;

//return the location of the parent
int parent(int i)
{
	return (i - 1) / 2;
}

//return the location of the left child
int leftChild(int i)
{
	return ((2 * i) + 1);
}

//return the location of the right child
int rightChild(int i)
{
	return ((2 * i) + 2);
}

void swap(struct proc *old, struct proc *new)
{
	struct proc *temp;
	temp=old;
	old=new;
	new=temp;
	
}


// Function to shift up the node in order
// to maintain the heap property
void shiftUp(int size)
{
	while (size > 0 && H[parent(size)]->mean_ticks > H[size]->mean_ticks) {

		// Swap parent and current node
		swap(H[parent(size)], H[size]);

		// Update i to parent of i
		size = parent(size);
	}
}

// Function to shift down the node in
// order to maintain the heap property
void shiftDown(int size)
{
	int minIndex = size;

	// Left Child
	int l = leftChild(size);

	if (l <= size && H[l]->mean_ticks < H[minIndex]->mean_ticks) {
		minIndex = l;
	}

	// Right Child
	int r = rightChild(size);

	if (r <= size && H[r]->mean_ticks < H[minIndex]->mean_ticks) {
		minIndex = r;
	}

	// If i not same as minIndex
	if (size != minIndex) {
		swap(H[size], H[minIndex]);
		shiftDown(minIndex);
	}
}

// Function to insert a new element
// in the Binary Heap
void insert(struct proc *new_p)
{
	size = size + 1;
	H[size] = new_p;

	// Shift Up to maintain heap property
	shiftUp(size);
}

// Function to extract the element with
// minimum priority
struct proc* extractmin()
{
	struct proc *result = H[0];

	// Replace the value at the root
	// with the last leaf
	H[0] = H[size];
	size = size - 1;

	// Shift down the replaced element
	// to maintain the heap property
	shiftDown(0);
	return result;
}

// Function to change the priority
// of an element
void changePriority(int i, struct proc *p)
{
	struct proc *oldp = H[i];
	H[i] = p;

	if (p->mean_ticks > oldp->mean_ticks) {
		shiftUp(i);
	}
	else {
		shiftDown(i);
	}
}

// Function to get value of the current
// minimum element
struct proc * getmin()
{

	return H[0];
}

// Function to remove the element
// located at given index
void remove(int i)
{
	H[i] = getmin() + 1;

	// Shift the node to the root
	// of the heap
	shiftUp(i);

	// Extract the node
	extractmin();
}



