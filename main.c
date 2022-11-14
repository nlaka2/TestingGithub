//git and github is hard to use

// Lab 8: Dynamic array implemented using a linked list.
// UIC CS 211, Fall 2022, Kidane and Reed
//Nilufar Lakada and Filip Toloczko

#include <stdio.h>
#include <stdlib.h>

#define true 1         // Make true a synonym for 1
const int Delta = 3;   // Array growth increment

typedef struct Node *NodePtr;  // NodePtr is a synonym for: struct Node *
struct Node {
    int data;        // The data stored at the node
    int index;       // Index position of this node, when viewed as array
    NodePtr pNext;   // Pointer to the next node
};


//-------------------------------------------------
void displayArray(  NodePtr pCurrent)  // Pointer to the first list Node
{
    // Display the index values stored on the array nodes.
    printf("Array indices: ");
    NodePtr pTemp = pCurrent;    // make a copy, so original can still be used below.
    while( pTemp != NULL) {
      // Don't print the sentinel Node value
      if( pTemp->data != -1) {
        printf("%3d", pTemp->index);
      }
      pTemp = pTemp->pNext;
    }
    printf("\n");
    
    // Display the numbers stored on the array nodes.
    printf("       values: ");
    while( pCurrent != NULL) {
      // Don't print the sentinel Node value
      if( pCurrent->data != -1) {
        printf("%3d", pCurrent->data);
      }
      pCurrent = pCurrent->pNext;
    }
    printf("\n");
} //end displayArray(..)


//----------------------------------------------------
// Find and return the pointer to the nth Node on the list.
// Return NULL if the index value we are searching for is
// not found.
NodePtr findNthNode(
            NodePtr pCurrent,   // Starts at head of list
            int indexToFind)    // Index value we are looking for
{
    // Advance past the sentinel Node to the first Node, if there is one.
    if( pCurrent != NULL && pCurrent->index == -1) {
        pCurrent = pCurrent->pNext;
    }
    
    // Iterate down the list looking for the indexToFind.
    // Make sure we stop at the end of the list, in case indexToFind
    // is larger than the index at the end of the list.
    while( pCurrent != NULL && pCurrent->index < indexToFind) {
        // Advance pCurrent to point to next node
        pCurrent = pCurrent->pNext;
    }
    
    // Return pointer to the Node where index was found, or NULL if not found.
    if( pCurrent != NULL && indexToFind == pCurrent->index) {
        return pCurrent;
    }
    else {
        return NULL;
    }
} //end findNthNode(..)


//----------------------------------------------------
// Add newNumber into array. If index is larger than
// the current array size, then grow the array in groups
// of 3 nodes at a time until index is now in range.

// Once this is done, add the new element and update
// the new current size.

void addValueAt(
                  NodePtr pCurrent, //start at the head
                  NodePtr pTail,
                  int newNumberIndex,
                  int* maxSize,
                  int newNumber)    
{
    NodePtr pTemp = pCurrent;
    if(newNumberIndex < *maxSize)
    {
      while(pTemp->index != newNumberIndex)
      {
        pTemp = pTemp->pNext;
      }
      pTemp->data = newNumber;
    }
    // NodePtr pHeadTemp = (NodePtr) malloc( sizeof( struct Node));
    // pHeadTemp->index = -1;
    // pHeadTemp->data = -1;
    // pHeadTemp->pNext = NULL;
    // NodePtr pTailTemp = pHeadTemp;
  
    // while( newNumberIndex > *maxSize)
    // {
    //   *maxSize += Delta;
    // }

    // for(int i = 0; i < *maxSize; i++)
    // {
    //   appendNumber(pHeadTemp, &pTailTemp, index);
    // }
    // If newNumberIndex is larger than the current number of Nodes on the list,
    // then keep growing the list three nodes at a time until it is in range.
    // ...

    // List is now large enough to accomodate the newNumberIndex.
    // Find the node where it should go using findNthNode(..);
    // ...
    
    // Add the new element
    // ...
} //end addValueAt(...)


//-----------------------------------------------
void appendNumber(NodePtr pHead, NodePtr *pTail, int index)
{
  // Allocate space for new node and initialize it
  NodePtr pTemp;  // pointer to new Node
  pTemp = malloc(sizeof(struct Node));  

  *pTail = pHead;
  pTemp->data  = 0;
  pTemp->index = index;
  pTemp->pNext = NULL;
  
  if (pHead == NULL) {
     pHead = pTemp;
     return;
  } 
  while ((*pTail)->pNext != NULL) {
      (*pTail) = (*pTail)->pNext;
  }
  // Append at tail of list
  (*pTail)->pNext = pTemp;
  
} // end appendNumber()


//-----------------------------------------------
int main()
{
    int moveNumber = 1;     // Numbers user inputs.
    int maxSize = 0;        // Number of Nodes in storage, not counting the sentinel Node.
    int newNumber = 0;      // User input of new number to be added.
    int newNumberIndex = 0; // User input of index position where new number should go.
    int index = 0;
    
    // Allocate space for the initial sentinel Node and initialize its values.
    NodePtr pHead = (NodePtr) malloc( sizeof( struct Node));
    pHead->index = -1;
    pHead->data = -1;
    pHead->pNext = NULL;
    NodePtr pTail = pHead;  // Tail initially points to sentinel node
    
    // Allocate the first set of 3 nodes
    //...
    appendNumber(pHead, &pTail, index);
    index++;
    appendNumber(pHead, &pTail, index);
    index++;
    appendNumber(pHead, &pTail, index);
    index++;
    maxSize = 3;
  
    // Prompt for, get and store new number
	printf("Give input of -1 to exit the program.\n");
    do {
        printf("%2d. Enter value and index: ", moveNumber);
        scanf("%d", &newNumber);
        if( newNumber == -1) {
            break;   // Exit when -1 is entered
        }
        else {
            // Also scan the index
            scanf("%d", &newNumberIndex);
        }

        // Add the new value, growing storage if needed.
        addValueAt(pHead, pTail, newNumberIndex, &maxSize, newNumber);

        // Display the array with this new element
        displayArray( pHead);
        
        // Increment the moveNumber
        moveNumber++;
     } while( true);

    printf("Done.\n");
    return 0;
}