#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void quickSort(int v[], int start, int end);
int partition(int v[], int start, int end);
int pivot(int v[], int start, int end);
void swap(int *a, int *b);

int main(int argc, char const *argv[])
{
	//size of the array to be ordered
	int array[90000];
	int n;
	cin >> n;

	//Creates the vector with the desired size.
	//vector<int> array;
	//array.resize(n);

	//Fill the array with random numbers from 0 to n.
	for(int i = 0; i < n; ++i)
		array[i] = (rand()%n);

	for(int i = 0; i < n; ++i)
		cout << " " << array[i] << ","; //print our array

	quickSort(array, 0, n-1); //sort it from start to end.

	cout << endl << endl;

	for(int i = 0; i < n; ++i)
		cout << " " << array[i] << ","; //print our ordered array.

	cout << endl << endl;

	return 0;
}

void quickSort(int v[],int start, int end)
{
	int p=0;

	//since it's recursive, this is our stop condition.
	if(start >= end)
		return;

	//this will create our partition and return our pivot element position
	//respecting the same interval of course.
	p = partition(v, start, end);

	//now we call it recursively for our first half(left of pivot)
	quickSort(v, start, p-1); 
	//and then for our second half (right of pivot)
	quickSort(v, p+1, end);

	//note: it's p-1 and p+1 because we are SURE that the pivot is in his RIGHT POSITION.
}

int partition(int v[], int start, int end)
{
	//now the magic happens

	//this is used to choose our pivot element. Aka the element that will be reference for the others.
	int p = pivot(v, start, end);

	//XOR SWAP CAUSE IT'S COOL
	//put the pivot at the leftmost position.
	swap(&v[start], &v[p]);

    //these will be our "navigators" through the array.
    int i = start;
    int j = end;

    //while the cursors haven't 'crossed eachother'
    while(i < j)
    {
    	//if our start hasn't reached our end
    	//AND if our v[i] is lesser than or equal our pivot, it's ok, since all lesser elements stay in the left.
    	while((i <= end) && (v[i] <= v[start]) ) //v[start] is our pivot
    		++i; //walks with i >> to check again

    	//if the end is greater than our pivot, it's ok (all elements bigger than the pivot go in the right)
    	while(v[j] > v[start]) 
    		--j; //walks with j << to check again

    	//at the point we are here, we can't proceed any further (meaning there are elements in the wrong place)
    	//so let's swap sides with them!
    	//the condition guarantees us that it won't be an unecessary swap (swapping back the same numbers, f.i.), since it only allows swaps from left to right.
    	if(i < j)
    		swap(&v[i], &v[j]);
	}

	//now we swap our pivot to the middle again
	swap(&v[start], &v[j]);

	//and return its position
	return j;
}

int pivot(int v[], int start, int end)
{
	//let's do a quicksort where our pivot is the number at the middle.

	int pos = (start+end)/2; //this gives us a random number from start to end.

	return pos;
}

void swap(int *a, int *b)
{
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}