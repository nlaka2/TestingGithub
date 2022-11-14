// linkedListCommandLineArgs.c - Demo program to illustrate how to use
// command line args with linked lists, so a command line argument
// will determine whether to prepend or append, and whether to
// display the list after each new addition.

/* Nilufar Lakada and John Ho
The Class notes from 10/14 were a HUGE help in understanding the arguments
    let alone being able to "get" them and use them. Thank you Professor Reed.*/

#include <stdio.h>   // For printf and scanf
#include <stdlib.h>  // For malloc

typedef struct Node *NodePtr;  // Make:  NodePtr to be a synonym for: struct Node *
struct Node {
    int data;         // The data stored at the node
    NodePtr pNext;    // Pointer to the next node
};

// Define global constants
const int PREPEND = 0;  // PREPEND is 0
const int APPEND = 1;   // APPEND is 1
const int TRUE = 1;     // TRUE is 1, FALSE is 0
const int FALSE = 0;


//---------------------------------------------------------------------
// display_usage() - Display program usage message
void display_usage() {
    printf("USAGE:");
    printf("\n  ./main [-p a] [-i 0]");
    printf("\n");
    printf("\n  where the parameters are:");
    printf("\n     [-p c] = Append when c is a, Prepend when it is p");
    printf("\n     [-i n] = When n is 0 don't display list, when n is 1 display list\n");
}

// //---------------------------------------------------------------------
// // error() - Display program error message and exit program
void error(char *error_name,    // String describing type of error
           char *error_operand, // String describing specific data structure used
           int  error_number)   // Error number, also used to display subscripts
{
    printf("argcArgv program error: \n");
    printf("*** %s WHEN OPERATING ON: %s ", error_name, error_operand);
    if(error_number != 0)
    {
      printf("at %d\n", error_number);
    } else {
        printf("\n");
    }
    exit(-1);
}


//---------------------------------------------------------------------
// get_arguments() - Retrieve & store command line arguments
// based on the example from Lecture 10/14
void get_arguments(
                  int argc, //number of args
                  char *argv[], //array of strings
                  char *charValue, //character value command line
                  int *intValue //character value command line
                )
{
      if(argc == 1) //No arguments
      {
        display_usage();
      }
      else
      {
        while( (argc -= 2) > 0 ) // while there is another pair of strings
        {
            if( argv[1][0] != '-')// Invalid syntax, no "-" before option
            {
              display_usage();
            }
            switch(argv[1][1]) { // handle options
              case 'p': 
                        *charValue = argv[2][0];
                        break;
              case 'i':
                        *intValue = atoi(argv[2]);
                        break;
              default:
                error("Incorrect parameter", &argv[ 1][ 1], 0);
            } //end switch
            argv += 2; // advance to next pair of command line options
        }// end while
      } //end else
}//end get_arguments()

//---------------------------------------------------------------------
// change_mode() - change mode to prepend or append
void change_mode(
                char charValue,
                int *mode //will be changed to append or prepend
                )
{
  if(charValue == 'a') {
    *mode= APPEND; //if charValue is 'a', then change mode to append (1)
  } else if (charValue=='p') {
    *mode=PREPEND; //if charValue is 'p', then change mode to prepend (0)
  }
}


  
// change_display() - change display list to on or off
void change_display(
                int intValue,
                int *displayListOn //will be changed to on or off
                )
{
  if(intValue == 0){
    *displayListOn = FALSE; //if intValue is 0, then change displayListOn to off (0)
  } else if(intValue == 1) {
    *displayListOn = TRUE; //if intValue is 1, then change displayListOn to on (1)
  }
}


//------------------------------------------------------------
// Consider: Does this function destroy the head node pointer?
void displayList( NodePtr pHead)
{
   printf("List is: ");
   while( pHead != NULL) {
      printf("%d ", pHead->data);
      pHead = pHead->pNext;
   }
   printf("\n");
} // end displayList()


//--------------------------------------------------------------
// Prepend number at the beginning of the list
void prependNumber( NodePtr *pHead, int number)
{
    // Allocate space for new node and initialize it
    NodePtr pTemp;     // pointer to new Node
    pTemp = malloc( sizeof( struct Node));
    pTemp->data = number;
    pTemp->pNext = *pHead;
    
    // Prepend at head of list
    *pHead = pTemp;
} // end prependNumber()


//--------------------------------------------------------------
// Append number at the end of the list
void appendNumber( NodePtr *pHead, NodePtr *pTail, int number)
{
    // Allocate space for new node and initialize it
    NodePtr pTemp = malloc( sizeof( struct Node));
    pTemp->data = number;
    pTemp->pNext = NULL;

    // Special case if list is empty
    if( *pHead == NULL) {
        // List is empty, so set head to point to first node
        *pHead = pTemp;
    }
    else {
        // List is not empty, so connect last node to new node
        (*pTail)->pNext = pTemp;
    }
    
    // Set new tail pointer
    *pTail = pTemp;
} // end appendNumber()


//--------------------------------------------------------------
int main( int argc, char *argv[])
{
    NodePtr pHead = NULL;      // head of linked list
    NodePtr pTail = NULL;      // tail of linked list
    int number = 0;            // Used to store numbers read in
    
    int mode = PREPEND;        // Default mode
    int displayListOn = TRUE;  // Determine whether list should display each time
    // Use command line args to optionally reset the following two variables,
    // where command line args -p a switches mode to APPEND, and
    // commmand line arg -i 0 switches display mode to FALSE.
    // ...
    int intValue = 0;
    char charValue = 'a';

    get_arguments(argc, argv, &charValue, &intValue);
    change_mode(charValue, &mode);
    change_display(intValue, &displayListOn);
//    printf("%d",displayListOn);

    printf("Enter positive integers followed by -1: ");
    // Loop to allow adding values to the list.
    while( number != -1) {
        scanf("%d", &number);
        if( number == -1) {
            break;  // Exit loop, done with program.
        }
        else if( mode == PREPEND) {
            prependNumber( &pHead, number); // Prepend to front of list
        }
        else if( mode == APPEND) {
            appendNumber( &pHead, &pTail, number); // Append to end of list
        }
        
        if( displayListOn == TRUE) {
            displayList( pHead);
        }
    } //end while( number...

    // Always display the list at the end
    printf("Final Result: ");
    displayList(pHead);
    return 0;         // return value to keep C++ happy
} // end main()