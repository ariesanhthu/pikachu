#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;

// Struct for the node in a linkedlist
struct node{
    int key;
    node* next = NULL;
};

// Struct for the list of header pointer to a linked list
struct headerList{
    node *head = NULL;
    headerList* next = NULL;
    int size = 0;
};

// Move the console cursor
void gotoxy(int x, int y);

// Clear the console screen
void ClearScreen();

// Create a node
node *createNode(int data);

// Add a node to the linked list
void addNode(node *&head, int data, int &size);

// Delete a node from the link list
void deleteNode(int pos, headerList *&head);

// Retrieving the data in the linked list
node * trace(node * head, int m);

// Create a header pointer which is a node of a header list
headerList *createHeader(node *data);

// Add the header to the header list
void addHeader(headerList *&head, node* data, int &size);

// Retrieving data in the header list
headerList * traceH(headerList * head, int m);

// Delete all of the header list
void deleteH(headerList *&head);