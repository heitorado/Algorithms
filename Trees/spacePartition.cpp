#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef struct node{

	int value;
	struct node *left;
	struct node *right;

}node;



//Auxiliary Functions
int biggest(int a, int b);
int middleTerm(int a, int b, int c);
int binarySearch(int vet[], int v, int size);
void display(node* root);
void _display(node* root, int spaces);
node* searchAndDestroy(node* root, int startInterval, int endInterval, int* destroyCount);
bool evaluate(node* root, int startInterval, int endInterval);

//BST Operations
node* BST_New(int value);
node* BST_Search(node* root, int v);
node* BST_Insert(node* root, int v);
node* BST_Delete(node* root, int v);
node* BST_DeleteMin(node* root, int* val);
node* createBSPTree(node* root, int start, int end, int v[]);

//Sorting
void quickSort(int vet[], int start, int end);
int partition(int vet[], int start, int end);
int pivot(int vet[], int start, int end);
void swap(int *a, int *b);

//Testing
void printBST(node* root);
int treeHeight(node* root);
node* fillBST(node* root, int vet[], int start, int end);


void traverse(node* root)
{
	if(root == NULL)
		return;
	traverse(root->left);
	cout << root->value << " | ";
	traverse(root->right);

	return;
}


int main()
{
	long long int numObjects, M, seed, A, C;

	//Read the number of objects in scene, the distance limit, the random seed and the parameters A and C
	scanf("%lld %lld %lld %lld %lld", &numObjects, &M, &seed, &A, &C);

	//Creation of the distance array
	int *DA = new int[numObjects];
	DA[0] = seed;

	for(int i = 1; i < numObjects; ++i)
	{
		DA[i] = (A * DA[i-1] + C)%M;

		//DEBUG
		//printf("DA[%d]: %d\n\n", i, DA[i] );
	}
	//Array created and filled.

	node* root = createBSPTree(NULL, 0, numObjects-1, DA);

	

	//traverse(root);

	//quickSort(DA, 0, numObjects-1);

	/*
	for(int i = 0; i < numObjects; ++i)
	{
		//DEBUG
		printf("DA[%d]: %d\n", i, DA[i] );
	}
	*/

	/*
	//FOR TESTING
	node* root = NULL;

	root = BST_Insert(root, 75);
	BST_Insert(root, 27);
	BST_Insert(root, 88);
	BST_Insert(root, 14);
	BST_Insert(root, 53);
	BST_Insert(root, 79);
	BST_Insert(root, 92);
	BST_Insert(root, 1);
	BST_Insert(root, 40);
	BST_Insert(root, 66);
	//FOR TESTING 

	*/

	//node* root = fillBST(NULL, DA, 0, numObjects-1);

	//cout << "Your BST is: " << endl;
	//display(root);
	//printBST(root);
	//cout << endl;




	/*
	//if our number of objecs is less than 3, the base index is zero.
	int baseIndex = DA[0];
	if(numObjects >= 3)
	{
		//Now the base for our BST will be the medium between DA[0], D[(N-1)/2] and D[N-1]
		int B1 = DA[0], B2 = DA[(numObjects-1)/2], B3 = DA[numObjects-1];
		baseIndex = middleTerm(B1, B2, B3);

		printf("%d %d %d\n",B1, B2, B3 );

		printf("%d \n",baseIndex );

	}
	//This base will be the main root of our BST.
	*/



	/*
	//Now we'll create the BST
	node* root = BST_New(baseIndex);

	for(int i = 0; i < numObjects; ++i)
	{
		if(DA[i] != baseIndex)
			BST_Insert(root, DA[i]);
	}

	printBST(root);
	
	cout << treeHeight(root) << endl;

	*/




	//now we'll read the number of operations to be made
	int numOp;
	scanf("%d", &numOp);

	//here we'll store the operation we want to perform
	char op[25];
	//here we'll store the value we want to add.
	int add=0;
	//here we'll store the interval we want to remove.
	int delL=0, delR=0;

	printf("0: %d\n", treeHeight(root)); //print the BST height before the operations

	//traverse(root);

	for(int i = 0; i < numOp; ++i)
	{
			
		scanf(" %[^\n]s", op);
		if(op[0] == 'A')
		{
			sscanf(op, "ADD %d", &add);
			if(BST_Search(root, add) == NULL)
			{
				BST_Insert(root, add);
				printf("%d: 1\n", i+1); //sucessfully added element
				//DEBUG
				//display(root);
			}
			else
			{
				printf("%d: 0\n", i+1); //element is already there, can't add
				//DEBUG
				//display(root);
			}
		}
		else
		{
			sscanf(op, "DEL %d %d", &delL, &delR);
			int erasedObjects = 0;

			//cout << "VALOR DA ROOT" << root->value << endl;
			root = searchAndDestroy(root, delL, delR, &erasedObjects);
			//root = searchAndDestroy(root, delL, delR, &erasedObjects);
	
			//display(root);
			//cout << endl << endl << endl;

			printf("%d: %d\n", i+1, erasedObjects); //number of erased objects.
		}

		//printf("%d\n %d\n %d\n", add, delL, delR);

		/*if(i+1 == 144)
		{
			cout << endl << endl << endl << endl;
			traverse(root);
		}*/

	}

	//printf("%d: %d\n", numOp+1, treeHeight(root)); //print the tree height after the operations

	return 0;
}





/*node* fillBST(node* root, int vet[], int start, int end)
{
	if(start >= end)
	{
		BST_Insert(root, vet[start]);
		cout << "Valor de p: " << start << endl;
		return root;
	}

	int p = (start+end)/2;

	cout << "Valor de p: " << p << endl;

	if(root == NULL)
		root = BST_Insert(root, vet[p]);
	else
		BST_Insert(root, vet[p]);

	fillBST(root, vet, start, p-1);
	fillBST(root, vet, p+1, end);

	return root;
}*/

/*node* fillBST(node* root, int vet[], int start, int end)
{

	if(((end+1)-start) <= 2)
	{
		if(start !=end)
		{
			BST_Insert(root, vet[start]);
			BST_Insert(root, vet[end]);
		}
		else
			BST_Insert(root, vet[start]);
		return root;
	}

	int p = (start+end)/2;

	cout << "Valor de p: " << p << endl;

	if(root == NULL)
		root = BST_Insert(root, vet[p]);
	else
		BST_Insert(root, vet[p]);

	fillBST(root, vet, start, p-1);
	fillBST(root, vet, p+1, end);

	return root;
}*/



//Auxiliary Functions

int biggest(int a, int b)
{
	if(a>b)
		return a;
	else
		return b;
}

int middleTerm(int a, int b, int c)
{
	int val = biggest(a, biggest(b, c));

	if(val == a)
		return biggest(b,c);
	else if(val == b)
		return biggest(a,c);
	else
		return biggest(a,b);
}

node* BST_New(int v)
{
	node* root = new node;
	root->value = v;
	root->left = NULL;
	root->right = NULL;

	return root;
}

//Auxiliary Functions



//BST Functions
node* BST_Insert(node* root, int v)
{
	
	if(root == NULL)
	{
		node* leaf = new node;
		leaf->value = v;
		leaf->left = NULL;
		leaf->right = NULL;
		return leaf;
	}
	else if(v < root->value)
	{
		root->left = BST_Insert(root->left, v);
		return root;
	}
	else
	{
		root->right = BST_Insert(root->right, v);
		return root;
	}

}

node* searchAndDestroy(node* root, int startInterval, int endInterval, int *destroyCount)
{
	if(root == NULL)
		return root;

	//First we have to filter our node choice. Let's search for someone in the interval.
	if(root->value < startInterval)
		root->right = searchAndDestroy(root->right, startInterval, endInterval, destroyCount); //still not the guy, advance
	else if(root->value > endInterval)
		root->left = searchAndDestroy(root->left, startInterval, endInterval, destroyCount); //too much, go back.
	else
	{
		//now we are in the subtree with the desired range, let's start the extermination
		root->left = searchAndDestroy(root->left, startInterval, endInterval, destroyCount);
		root = BST_Delete(root, root->value);
		*destroyCount += 1;

		//if(root == NULL)
			//return root;

		if(root != NULL && evaluate(root, startInterval, endInterval))
			root = searchAndDestroy(root, startInterval, endInterval, destroyCount); //here we check for the possibility that the node we just deleted is still in the range

		if(root != NULL)
			root->left = searchAndDestroy(root->left, startInterval, endInterval, destroyCount);

		if(root != NULL)
			root->right = searchAndDestroy(root->right, startInterval, endInterval, destroyCount);
	}


	//root->left = searchAndDestroy(root->left, startInterval, endInterval, destroyCount);
	
	//cout << root->value << " | ";

	/*while(evaluate(root, startInterval, endInterval))
	{	
		*destroyCount += 1;
		root = BST_Delete(root, root->value);

		if(root == NULL)
			return root;
	}*/

	

	return root;
}

bool evaluate(node* root, int startInterval, int endInterval)
{
	if( (root->value >= startInterval) && (root->value <= endInterval))
	{
 		//cout <<  " |"<< root->value << "| \n";
		return 1;
 	}
	else
		return 0;
}



node* BST_Search(node* root, int v)
{
	if(root == NULL)
		return NULL;

	else if(root->value == v)
		return root;

	else if(v < root->value)
		return BST_Search(root->left, v);

	else
		return BST_Search(root->right, v);
}

node* BST_Delete(node* root, int v)
{	
	int x=0;
	int *val = &x;

	if(root == NULL)
	{
		return NULL;
	}
	
	else if(v < (root->value))
	{
		(root->left) = BST_Delete((root->left), v);
		return root;
	}

	else if((root->value) < v)
	{
		(root->right) = BST_Delete((root->right), v);
		return root;
	}

	else
	{
		if((root->left) == NULL)
		{
			node* right = (root->right);
			free(root);
			return right;
		}

		else if((root->right) == NULL)
		{
			node* left = (root->left);
			free(root);
			return left;
		}
		else
		{
			(root->right) = BST_DeleteMin((root->right), val);
			(root->value) = *val;
			return root;
		}
	}
}	
node* BST_DeleteMin(node* root, int* val)
{

	if(root->left == NULL)
	{
		node* r = root->right;
		*val = root->value;
		free(root);
		return r; 
	}
	else
	{
		root->left = BST_DeleteMin(root->left, val);
		return root;
	}
}

void printBST(node *root)
{
	if(root == NULL)
		return;
	printBST(root->left);
	cout << root->value << endl;
	printBST(root->right);
}

int treeHeight(node* root)
{
	int L, R;

	if(root ==  NULL)
		return 0;

	L = treeHeight(root->left);
	R = treeHeight(root->right);

	if(L > R)
		return 1 + L;
	else
		return 1 + R;
}


//Quicksort
void quickSort(int vet[], int start, int end)
{
	if(start >= end)
	{	
		//BST_Insert(RAIZ, vet[end]);
		return;
	}

	int p = partition(vet, start, end);
	quickSort(vet, start, p-1);
	quickSort(vet, p+1, end);
}

int partition(int vet[], int start, int end)
{
	int p = pivot(vet, start, end);

	/*if(RAIZ == NULL)
		RAIZ = BST_Insert(RAIZ, vet[p]);
	else
		BST_Insert(RAIZ, vet[p]);*/


	
	if(p != 0)
		swap(vet[start], vet[p]);

	int i = start, j = end;

	while(i < j)
	{
		while((i <= end) && (vet[i] <= vet[start]))
			++i;

		while(vet[j] > vet[start])
			--j;

		if(i<j)
			swap(vet[i],vet[j]);
	}

	swap(vet[start],vet[j]);
	return j;
}

int pivot(int vet[], int start, int end)
{
	int baseIndex = 0;

	//cout << "start: " << start << "    end: " << end << endl;

	if(((end-start)+1) >= 3)
	{
		//Now the base for our BST will be the medium between DA[0], D[(N-1)/2] and D[N-1]
		int B1 = vet[start], B2 = vet[(start+end)/2], B3 = vet[end];
		
		baseIndex = middleTerm(B1, B2, B3);

		//printf("BASES: %d %d %d\n",B1, B2, B3 );
		
		if(baseIndex == B1)
			baseIndex = start;
		else if(baseIndex == B2)
			baseIndex = (start+end)/2;
		else
			baseIndex = end;

		//printf("%d %d %d\n",B1, B2, B3 );
		//printf("[if]PIVOT ATUAL: %d \n", baseIndex);
		return baseIndex;
	}

	//printf("PIVOT ATUAL: %d \n", baseIndex);

	return 0;
}

void swap(int *a, int *b)
{
	int aux = *a;
	*a = *b;
	*b = aux;
}


int binarySearch(int vet[], int v, int size) //See if I can extend to find the first bigger number after the searched, in case it doesn't exist.
{
	int l = 0, r = size-1;
	int middle;

	do
	{
		middle = (l+r)/2;

		if(v == vet[middle])
			return middle;

		else if(v < vet[middle])
			r = middle-1;

		else
			l = middle+1;
	}while(l <= r);

	return -1;
}



void display(node* root)
{
	_display(root, 0);
}

void _display(node* root, int spaces)
{
	if(root == NULL)
		return;

	_display(root->right, spaces+5);

	for(int i = 0; i < spaces; ++i)
		printf(" ");

	printf("%d\n", root->value);

	_display(root->left, spaces+5);
	return;
}


node* createBSPTree(node* root, int start, int end, int v[])
{
	//cout << "START: " << start << "END: " << end << endl;

	if(start+1 >= end)
	{
		if(start==end)
		{
			BST_Insert(root, v[start]);
			//cout << "Adicionado Elemento: C1 ->" << v[start] << endl;
		}
		else
		{
			BST_Insert(root, v[start]);
			//cout << "Adicionado Elemento: C2 ->" << v[start] << endl;
			BST_Insert(root, v[end]);
			//cout << "Adicionado Elemento: C3 ->" << v[end] << endl;
		}
		return root;
	}

	int p = pivot(v, start, end);
	root = BST_Insert(root, v[p]);
	//cout << "Adicionado Elemento: C4 ->" << v[p] << endl;

	int* lessThan = new int[end-start];
	int* greaterThan = new int[end-start];

	int j=0,k=0;

	for(int i = start; i < end+1; ++i)
		if(v[i] < v[p])
		{
			lessThan[j] = v[i];
			++j;
		}
		else if(v[i] > v[p])
		{
			greaterThan[k] = v[i];
			++k;
		}

	if(j <= 0)
		j = 1;

	if(k <= 0)
		k = 1;

	createBSPTree(root, 0, j-1, lessThan);
	createBSPTree(root, 0, k-1, greaterThan);

	//delete[] lessThan;
	//delete[] greaterThan;

	return root;
}