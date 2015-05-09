/**
 *  linked.c

 *  Darren O'Connor
 *  @mellowdrifter
 *  https://www.mellowd.co.uk/ccie
 *
 *  Learning how to create and manipulate linked lists
 */
 
#include <stdio.h>
#include <stdlib.h>

// Struct node with pointer to struct node
typedef struct node {
    int number;
    struct node* next;
}node;

void printList(node* cur) {

    // Traverse through linked list
    while (cur != NULL) {
        printf("%i is is at position %p\n", cur->number, &cur->number);
        printf("Next node is at position %p\n\n", cur->next);
        
        // Move cursor to next node via pointer
        cur = cur->next;
    }
}

void addNode(node* cur) {

    // Traverse through linked list
    // Need to get to end of list in order to append
    if (cur != NULL) {
        while (cur->next != NULL) {
            cur = cur->next;
        }
    }
    
    // Now at the the end of the list, ensure the current last node
    // points to a new node we create dynamically
    cur->next = (node*) malloc(sizeof(node));
    
    // Move to the new node
    cur = cur->next;
    
    // Get a value inside that node
    printf("Please enter node value: ");
    scanf("%i", &cur->number);
}

void insertNode(node* cur, int match) {

    // Traverse through linked list to find value
    while (cur->next != NULL) {
        
        // We've found the node we're looking for
        if (cur->number == match) {
        
            // save pointer to rest of list
            node* temp = cur->next;
            
            // Create a new node and get current node to point to it
            cur->next = (node*) malloc(sizeof(node));
        
            // Move to the new node
            cur = cur->next;
            
            // Get a value to insert
            printf("What value do you want to insert? ");
            int number;
            scanf("%i", &number);
            cur->number = number;
            
            // Finally ensure new node connects to the rest of the list
            cur->next = temp;
            
            return;
        }
        
        // Otherwise keep going through the list
        cur = cur->next;
    }
}

void deleteNode(node* cur, int match) {

    // We need to keep note of previous node
    // otherwise we cannot reconnect it!
    node* previous = cur;

    // Traverse through linked list to find value
    while (cur->next != NULL) {
        
        // We've found the node we're looking for
        if (cur->number == match) {
        
            // Set pointer of last node around this node to new node
            node* temp = cur->next;
            free(cur); // Release node from RAM
            cur = previous;
            cur->next = temp;
            
            return;
        }
        
        // Otherwise keep going through the list
        previous = cur;
        cur = cur->next;
    }
}

void deleteList(node* cur) {

    // Traverse through linked list
    while (cur != NULL) {
        node* temp = cur;
        cur = cur->next;
        free (temp);
    }
}
        
int main(void) {

    // Root position of list
    node* root = (node*) malloc(sizeof(node));
    
    // Get initial value from user
    printf("Please enter inital node value: ");
    scanf("%i", &root->number);
    
    // Initial node's next should be end of list
    root->next = NULL;
    
    // Use cur as a cursor to move around
    node* cur;
    
    // User controls what to do next
    int choice;
    int match;
    do
    {
        printf("1 - Add new item to list\n");
        printf("2 - Print list\n");
        printf("3 - Insert node\n");
        printf("4 - Delete node\n");
        printf("5 - Exit\n# ");
        
        scanf("%i", &choice);
        
        switch (choice) {
            case 5:
                cur = root;
                deleteList(cur);
                return 0;
                
            case 4:
                cur = root;
                printf("Which value should I delete? ");
                scanf("%i", &match);
                deleteNode(cur, match);
                break;
                
            case 3:
                cur = root;
                printf("After which value should I insert? ");
                scanf("%i", &match);
                insertNode(cur, match);
                break;

            case 2:
                cur = root;
                printList(cur);
                break;
                
            case 1:
                cur = root;
                addNode(cur);
         }
                
    } while (choice != 5);
}
