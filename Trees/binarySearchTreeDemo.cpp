#include <iostream>
using namespace std;

typedef struct node{

	int64_t value;
	struct node *left;
	struct node *right;

}node;




//BST OPerations
node* BST_New(int64_t value);
node* BST_Search(node* root, int64_t v);
node* BST_Insert(node* root, int64_t v);
node* BST_Delete();
node* BST_DeleteMin();


//Testing
void printBST(node* root);
int treeHeight(node* root);


int main(int argc, char const *argv[])
{
	node* root = BST_New(50);

	BST_Insert(root, 95);
	BST_Insert(root, 87);
	BST_Insert(root, 56);
	BST_Insert(root, 88);
	BST_Insert(root, 39);
	BST_Insert(root, 49);
	BST_Insert(root, 22);
	BST_Insert(root, 77);
	BST_Insert(root, 45);
	BST_Insert(root, 14);
	BST_Insert(root, 1);


	printBST(root);

	cout << "BST Height: " << treeHeight(root) << endl;


	return 0;
}

node* BST_New(int64_t v)
{
	node* root = new node;
	root->value = v;
	root->left = NULL;
	root->right = NULL;

	return root;
}

node* BST_Insert(node* root, int64_t v)
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

node* BST_Search(node* root, int64_t v)
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