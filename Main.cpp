#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
 
// Represents a node of the required tree
typedef struct node {
    char data;
    struct node *left, *right;
} node;
 
// Function to recursively build the expression tree
char* add(node** p, char* a)
{
 
    // If its the end of the expression
    if (*a == '\0')
        return nullptr;
 
    while (1) {
        char* q = NULL;
        if (*p == NULL) {
 
            // Create a node with *a as the data and
            // both the children set to null
            node* nn = (node*)malloc(sizeof(node));
            nn->data = *a;
            nn->left = NULL;
            nn->right = NULL;
            *p = nn;
        }
        else {
 
            // If the character is an operand
            if (*a >= 'a' && *a <= 'z') {
                return a;
            }
 
            // Build the left sub-tree
            q = add(&(*p)->left, a + 1);
 
            // Build the right sub-tree
            q = add(&(*p)->right, q + 1);
 
            return q;
        }
    }
}
 
// Function to print the infix expression for the tree
void inr(node* p) // recursion
{
    
    if (p == NULL) {
        return;
        
    }
    else {
        
        inr(p->left);
        
        printf("%c", p->data);
        inr(p->right);
    }
}
 
// Function to print the postfix expression for the tree
void postr(node* p)
{
    if (p == NULL) {
        return;
    }
    else {
        postr(p->left);
        postr(p->right);
        printf("%c", p->data);
    }
}
 
// Driver code
int main()
{
    node* s = NULL;
    char a[] = "+a**bcd";
    add(&s, a);
    printf("The Infix expression is:\n");
    inr(s);
    printf("\n");
    printf("The Postfix expression is:\n");
    postr(s);
    return 0;
}