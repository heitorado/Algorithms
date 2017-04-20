#include <iostream>
#include <cstdio>
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

//BST Operations
node* BST_New(int value);
node* BST_Search(node* root, int v);
node* BST_Insert(node* root, int v);
node* BST_Delete(node* root, int v);
node* BST_DeleteMin(node* root, int* val);

//Sorting
void quickSort(int vet[], int start, int end);
int partition(int vet[], int start, int end);
int pivot(int vet[], int start, int end);
void swap(int *a, int *b);

//Testing
void printBST(node* root);
int treeHeight(node* root);
node* fillBST(node* root, int vet[], int start, int end);


int main()
{
	long long int numObjects, M, seed, A, C;

	//Read the number of objects in scene, the distance limit, the random seed and the parameters A and C
	scanf("%lld %lld %lld %lld %lld", &numObjects, &M, &seed, &A, &C);

	//Creation of the distance array
	int *DA = new int[numObjects];
	for(int i = 0; i < numObjects; ++i)
	{
		if(i == 0)
			DA[0] = seed;
		else
			DA[i] = (A * DA[i-1] + C)%M;

		//DEBUG
		printf("DA[%d]: %d\n\n", i, DA[i] );
	}
	//Array created and filled with random distances.



	quickSort(DA, 0, numObjects-1);

	for(int i = 0; i < numObjects; ++i)
	{
		//DEBUG
		printf("DA[%d]: %d\n", i, DA[i] );
	}

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

	//node* root = fillBST(NULL, DA, 0, numObjects-1);


	//ÐEBUG
	cout << "Your BST is: " << endl;
	printBST(root);
	cout << endl;
	//ÐEBUG



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
	//here we'll store the distance we want to add.
	int add=0;
	//here we'll store the interval we want to remove.
	int delL=0, delR=0;

	printf("0: %d\n", treeHeight(root)); //print the BST height before the operations

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
			}
			else
				printf("%d: 0\n", i+1); //element is already there, can't add
		}
		else
		{
			sscanf(op, "DEL %d %d", &delL, &delR);
			int pos = binarySearch(DA, delL, numObjects);
			int erasedObjects = 0;

			for(int i = pos; DA[pos] <= delR; ++pos)
			{
				if(BST_Delete(root, DA[pos]) != NULL)
				{
					++erasedObjects;
				}
			}

			printf("%d: %d\n", i+1, erasedObjects); //number of erased objects.

		}

		//printf("%d\n %d\n %d\n", add, delL, delR);

	}

	printf("%d: %d\n", numOp+1, treeHeight(root)); //print the tree height after the operations

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
	int *val;

	if(root == NULL)
		return NULL;
	
	else if(v < root->value)
	{
		root->left = BST_Delete(root->left, v);
		return root;
	}

	else if(root->value < v)
	{
		root->right = BST_Delete(root->right, v);
		return root;
	}

	else
	{
		if(root->left == NULL)
		{
			node* right = root->right;
			free(root);
			return right;
		}

		else if(root->right == NULL)
		{
			node* left = root->left;
			free(root);
			return left;
		}
		else
		{
			root->right = BST_DeleteMin(root->right, val);
			return root;
		}
	}
}	
node* BST_DeleteMin(node* root, int* val)
{

	if(root->left == NULL)
	{
		node* r = root->right;
		//*val = root->value; //this is broken, see if i can fix it later.
		free(root);
		return r; //See if can return the value also
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

/*int pivot(int vet[], int start, int end)
{
	return (start+end)/2;
}*/

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