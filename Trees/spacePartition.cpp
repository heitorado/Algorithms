#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef struct node{

	int value;
	struct node *left;
	struct node *right;

}node;



//Auxiliary/Debug Functions
int biggest(int a, int b);
int middleTerm(int a, int b, int c);
void display(node* root);
void _display(node* root, int spaces);
void traverse(node* root);

//BST Operations
node* BST_New(int value);
node* BST_Search(node* root, int v);
node* BST_Insert(node* root, int v);
node* BST_Delete(node* root, int v);
node* BST_DeleteMin(node* root, int* val);
int treeHeight(node* root);

//Exercise Specific - BSPT Creation and Interval Destruction.
node* createBSPTree(node* root, int start, int end, int v[]);
int pivot(int vet[], int start, int end);
node* searchAndDestroy(node* root, int startInterval, int endInterval, int* destroyCount);
bool evaluate(node* root, int startInterval, int endInterval);

int main()
{
	long long int numObjects, M, seed, A, C;

	//Read the number of objects in scene, the distance limit, the random seed and the parameters A and C
	scanf("%lld %lld %lld %lld %lld", &numObjects, &M, &seed, &A, &C);

	//Creation of the distance array
	int *DA = new int[numObjects];
	DA[0] = seed;

	for(int i = 1; i < numObjects; ++i)
		DA[i] = (A * DA[i-1] + C)%M;
	
	//Array created and filled.
	node* root = createBSPTree(NULL, 0, numObjects-1, DA);

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
			int erasedObjects = 0;

			root = searchAndDestroy(root, delL, delR, &erasedObjects);
			printf("%d: %d\n", i+1, erasedObjects); //number of erased objects.
		}
	}
	return 0;
}

//Auxiliary/Debug Functions
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

void traverse(node* root)
{
	if(root == NULL)
		return;
	traverse(root->left);
	cout << root->value << " | ";
	traverse(root->right);

	return;
}
//Auxiliary/Debug Functions




//BST Operations

node* BST_New(int v)
{
	node* root = new node;
	root->value = v;
	root->left = NULL;
	root->right = NULL;

	return root;
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
//BST Operations

//Exercise Specific - BSPT Creation and Interval Destruction.
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
		return 1;
	else
		return 0;
}

//Exercise Specific - BSPT Creation and Interval Destruction.