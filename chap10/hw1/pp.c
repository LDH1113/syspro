#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node **top, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = *top;
    *top = new_node;
}

void printStack(struct node *top) {
    struct node *current = top;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main() {
    struct node *top = NULL;
    char input[20];

    while (1) {
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        char *endptr;
        double value = strtod(input, &endptr);
        
        if (endptr == input) {
            printf("Print Stack\n");
            printStack(top);
            break;
        } else if (value > 0) {
            push(&top, (int)value);
            if (value != (int)value) {
                printf("Print Stack\n");
                printStack(top);
                break;
            }
        } else {
            printf("Print Stack\n");
            printStack(top);
            break;
        }
    }

    return 0;
}

