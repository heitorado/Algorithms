//This code implements stacks and linked lists without using the C++ libraries.
//The implementation for this exercise consists in a "linked list of stacks"

#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

//Structs
typedef struct stackNode{
  int val;
  struct stackNode* next;
}stackNode;

typedef struct listNode{
  stackNode* stack;
  struct listNode* next;
}listNode;

//Stack Functions
stackNode* newStack();
stackNode* push(stackNode* top, int value);
stackNode* pop(stackNode* top);
int top(stackNode* top);
bool isEmpty(stackNode* top);

//List Functions
listNode* newList();
listNode* insert(listNode* cur, stackNode* top);
listNode* listPos(listNode* head, int pos);
listNode* destroy(listNode* cur);

//print function
void print(listNode* head);

int main()
{
  //stores the number of games to test
  int games(0);
  cin >> games;

  //stores the values to be entered on the stacks and the total number of stacks created
  int column(0),value(0),totalColumns(0);
  char move[25];

  //pointers to head and to current element of the linked list
  listNode* head;
  listNode* cur;

  for(int i = 0; i < games; ++i)
  {
    //initializes a new list for each game
    head = newList();

    do {

      scanf(" %[^\n]s", move);

      if(move[0] != 'E')
      {
        sscanf(move,"%d %d", &column, &value);

        //in this case, we will add a column to the left
        //that means adding a node at the beginning of the list.
        if(column == 0)
        {
          cur = insert(head,newStack());
          push(cur->next->stack, value);
          ++totalColumns;

          //print(head);
        }

        //in this case, we will add a column to the right
        //that means adding a node at the end of the list.
        else if(column == totalColumns+1)
        {
          cur = insert(listPos(head, totalColumns), newStack());
          push(cur->next->stack, value);
          ++totalColumns;

          //print(head);
        }

        //in this case, we will stack a value on top of other, in a already existent node.
        //that means just navigating to such node, and putting a value on its stack.
        else
        {
          //it's -1 because the 0-th element is the first one.
          //in other words, the linked list starts counting from zero.
          cur = listPos(head, column-1);

          //check if the value you're going to stack is the same at the top of the pile.
          //if it is, don't bother stacking, just pop the existant.
          if(value == top(cur->next->stack))
          {
            pop(cur->next->stack);
            if(isEmpty(cur->next->stack))
            {
              destroy(cur);
              --totalColumns;
            }
          }

          //if it's not the same value, just stack it.
          else
            push(cur->next->stack, value);

          //print(head);
        }
      }
    } while(move[0] != 'E');

    //now, we print the results for this game
    //the result consist on the game number, starting at zero
    //followed by the top value of all stacks, from left to right

    cout << "caso " << i << ":";
    print(head);

    free(head);
    totalColumns = 0;
  }

  return 0;
}



//Stack Function Definitions
stackNode* newStack()
{
  stackNode* sentinela = new stackNode;
  sentinela->next = NULL;

  return sentinela;
}

stackNode* push(stackNode* top, int value)
{
  stackNode* S = new stackNode;
  S->val = value;
  S->next = top->next;
  top->next = S;

  return top;
}

stackNode* pop(stackNode* top)
{
  stackNode* X;
  X = top->next;
  top->next = X->next;
  free(X);

  return top;
}

int top(stackNode* top)
{
  return top->next->val;
}

bool isEmpty(stackNode* top)
{
  if(top->next == NULL)
    return 1;
  else
    return 0;
}

//Linked List Function Definitions
listNode* newList()
{
  listNode* sentinela =  new listNode;
  sentinela->next = NULL;

  return sentinela;
}

listNode* insert(listNode* cur, stackNode* top)
{
  listNode* N = new listNode;
  N->stack = top;
  N->next = cur->next;
  cur->next = N;

  return cur;
}

listNode* listPos(listNode* head, int pos)
{
  int i = 0;
  listNode* cur = head;

  while((i < pos) && (cur != NULL))
  {
    cur = (cur->next);
    ++i;
  }

  return cur;
}

listNode* destroy(listNode* cur)
{
  listNode* P;
  P = cur->next;
  cur->next = P->next;
  free(P->stack);
  free(P);

  return cur;
}


//Function to print all top elements from the stacks on each node of the linked list
void print(listNode* head)
{
  listNode* cur = head;

  while(cur->next != NULL)
  {
    cout << " " << top(cur->next->stack);
    cur = (cur->next);
  }
  cout << endl;
}
