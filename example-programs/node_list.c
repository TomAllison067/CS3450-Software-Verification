#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

void insert(Node** head, int data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = (*head);
    (*head) = new_node;
}

void transfer(Node** source, Node** destination) {
    Node* temp = (*source);
    (*source) = temp->next;
    temp->next = (*destination);
    (*destination) = temp;
}

void print_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Node* source_head = NULL;
    Node* dest_head = NULL;

    // Insert nodes into source list
    insert(&source_head, 4);
    insert(&source_head, 3);
    insert(&source_head, 2);
    insert(&source_head, 1);

    // Print source list
    printf("Source list: ");
    print_list(source_head);

    // Transfer nodes from source to destination
    transfer(&source_head, &dest_head);
    transfer(&source_head, &dest_head);
    transfer(&source_head, &dest_head);

    // Print updated lists
    printf("Source list after transfer: ");
    print_list(source_head);
    printf("Destination list after transfer: ");
    print_list(dest_head);

    return 0;
}
