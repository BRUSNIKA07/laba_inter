#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *val;
    struct Node *next;
    struct Node *prev;
} Node;

void insert(Node **head, const char *val) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    
    newNode->val = malloc(strlen(val) + 1);
    if (newNode->val == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(newNode);
        return;
    }
    strcpy(newNode->val, val);

    newNode->next = NULL;
    newNode->prev = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
    newNode->prev = current;
}

Node *search(Node *head, const char *val) {
    while(head != NULL) {
        if (strcmp(head->val, val) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

void remove_node(Node **head, const char *val) {
    Node *node = search(*head, val);
    if (node == NULL) return;

    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        *head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    }

    free(node->val);
    free(node);
}

void printList(Node *head) {
    while (head != NULL) {
        printf("%s -> ", head->val); 
        head = head->next;
    }
    printf("NULL\n");
}

int main() {
    Node *head = NULL;

    insert(&head, "first");
    insert(&head, "second");
    insert(&head, "third");

    printList(head);

    remove_node(&head, "second");

    printList(head);

    while (head != NULL) {
        Node *next = head->next;
        free(head->val);
        free(head);
        head = next;
    }
    return 0;
}