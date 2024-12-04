#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    if (*tail) {
        (*tail)->next = new_node;
    } else {
        *head = new_node;
    }
    *tail = new_node;
}

int delete(struct node **head, struct node **tail) {
    if (*head == NULL) return -1;
    struct node *temp = *head;
    int deleted_data = temp->data;
    *head = (*head)->next;
    if (*head == NULL) {
        *tail = NULL;
    }
    free(temp);
    return deleted_data;
}

void printQueue(struct node *head) {
    struct node *current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main() {
    struct node *head = NULL;
    struct node *tail = NULL;
    char input[20];

    while (1) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        char *endptr;
        int value = strtol(input, &endptr, 10);
        
        if (endptr == input) {
            printf("Print queue\n");
            printQueue(head);
            break;
        } else if (value > 0) {
            addq(&head, &tail, value);
        } else {
            printf("Print queue\n");
            printQueue(head);
            break;
        }
    }

    while (head != NULL) {
        delete(&head, &tail);
    }

    return 0;
}

