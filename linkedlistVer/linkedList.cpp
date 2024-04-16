#pragma once
#include "linkedList.h"

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = y;
    coord.Y = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}  

void ClearScreen(){
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
    cellCount = csbi.dwSize.X *csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR) ' ',
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

    /* Move the cursor home */
    SetConsoleCursorPosition( hStdOut, homeCoords );
}

node *createNode(int data){
    node *a = new node;
    a->key = data;
    a->next = NULL;
    return a;
}

void addNode(node *&pHead, int data, int &size){
    node *addedNode = createNode(data);
    if (pHead == NULL){
        pHead = addedNode;
        size++;
    }

    else {
        node *cur = pHead;
        while(cur->next != NULL){
            cur = cur->next;
        }
        cur->next = addedNode; 
        size++;
    }
}

void deleteNode(int pos, headerList *&head){
    if(head->size == 1){
        delete head->head;
        head->head = nullptr;
        head->size--;
    }

    else if(pos == 1){
        node *cur = head->head;
        cur = cur->next;
        delete head->head;
        head->head = cur;
        head->size--;
    }

    else if(pos == head->size){
        node *cur = head->head;
        while(cur->next->next != nullptr){
            cur = cur->next;
        }
        delete cur->next;
        cur->next = nullptr;
        head->size--;
    }

    else{
        int count = 1;
        node *cur = head->head;
        while(count++ < pos - 1){
            cur = cur->next;
        }
        node *cur2 = cur->next;
        cur->next = cur2->next;
        delete cur2;
        head->size--;
    }
}

node * trace(node *head, int m){
    node *cur = head;
    for (int i = 1; i < m; i++){
        cur = cur->next;
    }
    return cur;
}

headerList *createHeader(node *data){
    headerList *a = new headerList;
    a->head = data;
    a->next = nullptr;
    a->size = 0;
    return a;
}

void addHeader(headerList *&pHead, node* data, int &size){
    headerList *addedNode = createHeader(data);
    if (pHead == nullptr){
        pHead = addedNode;
        size = 1;
    }

    else {
        headerList *cur = pHead;
        while(cur->next != nullptr){
            cur = cur->next;
        }
        cur->next = addedNode; 
        size++;
    }
}

headerList *traceH(headerList *head, int m){
    headerList *cur = head;
    for (int i = 1; i < m; i++){
        cur = cur->next;
    }
    return cur;
}

void deleteH(headerList *&head){
    while(head != nullptr){
        headerList *cur = head;
        while(cur->next != nullptr){ 
            cur = cur->next;
        }
        // cur->prev->next = nullptr;
        delete cur;
    }   
}