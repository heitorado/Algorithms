#include <iostream>
using namespace std;

const int vectorLenght = 100000;

int binarySearch(int vet[], int value);


int main()
{
	int array[vectorLenght];
	int numSearch;
	int pos;

	for(int i = 0; i < vectorLenght; ++i)
		array[i] =  i + 1;

	cout << "Insert value to search for: ";
	cin >> numSearch;

	pos = binarySearch(array, numSearch);

	if(pos != -1)
		cout << "Number found at position: " << pos;
	else
		cout << "The number entered is not present in the array." << endl;
}

int binarySearch(int vet[], int value)
{

	int l(0), r(vectorLenght-1), m(0);
	do
	{
		m = (l+r)/2;
		if(value == vet[m])
			return m;
		else if(value < vet[m])
			r = m-1;
		else
			l = m+1;

	}while(l <= r);
	return -1;
}