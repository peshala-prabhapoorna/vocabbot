#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char* word;
    struct node* next;
    struct node* prev;
} word_node;

word_node* insert_node(word_node* head_ptr, char* word);
word_node* delete_node(word_node* head_ptr, char* word);
int find_word(word_node* head_ptr, char* word);
void print_list(word_node* head_ptr);
void to_lowercase(char* word);
bool only_letters(char* word);
void free_nodes(word_node* head_ptr);

int main() {
    printf("commands: -delete=WORD | -find=WORD | -quit\n");

    word_node* head_ptr = NULL;
    char input_string[54];

    while (true) {
        printf("insert word to the list or enter command: ");
        if (scanf("%s", input_string) != 1) {
            printf("error: failed to get input");
            continue;
        }
        to_lowercase(input_string);

        if (input_string[0] == '-') {
            if (strncmp(input_string, "-delete=", 8) == 0) {
                head_ptr = delete_node(head_ptr, input_string + 8);
                continue;
            } else if (strncmp(input_string, "-find=", 6) == 0) {
                find_word(head_ptr, input_string + 6);
                continue;
            } else if (strcmp(input_string, "-quit") == 0) {
                break;
            }

            printf("error: invalid command\n");
            continue;
        }

        head_ptr = insert_node(head_ptr, input_string);
    }

    print_list(head_ptr);
    free_nodes(head_ptr);

    return 0;
}

word_node* insert_node(word_node* head_ptr, char* word) {
    if (!only_letters(word)) {
        printf(
            "invalid input: '%s' contains non alphabetical characters\n",
            word
        );

        return head_ptr;
    }

    word_node* new_node = malloc(sizeof(word_node)); 
    new_node -> word = strdup(word);
    new_node -> next = NULL;
    new_node -> prev = NULL;

    if (head_ptr == NULL) {
        printf("word '%s' inserted as the first word\n", new_node -> word);

        return new_node;
    }

    word_node* ptr = head_ptr;
    while (true) {
        int comparison = strcmp(ptr -> word, new_node -> word);

        if (comparison == 0) {
            printf("word '%s' is already in the list\n", word);
            free(new_node -> word);
            free(new_node);

            return head_ptr;
        }

        if (comparison > 0) {
            new_node -> next = ptr;
            new_node -> prev = ptr -> prev;

            if (ptr -> prev) {
                ptr -> prev -> next = new_node; 
            } else {
                head_ptr = new_node;
            }
            ptr -> prev = new_node;

            printf("word '%s' inserted to the list\n", word);

            return head_ptr;
        }

        // enter new node as the last node
        if (ptr -> next == NULL) {
            ptr -> next = new_node;

            new_node -> prev = ptr;

            printf(
                "word '%s' inserted at the end of the list\n", new_node -> word
            );

            return head_ptr;
        }

        ptr = ptr -> next;
    }

    return head_ptr;
}

word_node* delete_node(word_node* head_ptr, char* word) {
    if (head_ptr == NULL) {
        printf("the list has no words\n");

        return NULL;
    }

    word_node* ptr = head_ptr;
    while (ptr != NULL) {
        if (strcmp(ptr -> word, word) == 0) {
            if (ptr -> prev) {
                ptr -> prev -> next = ptr -> next;
            } else {
                head_ptr = ptr -> next;
            }
            if (ptr -> next) {
                ptr -> next -> prev = ptr -> prev;
            }

            printf("word '%s' deleted from the list\n", word);

            free(ptr -> word);
            free(ptr);

            return head_ptr;
        }

        ptr = ptr -> next;
    }
    printf("word '%s' is not in the list\n", word);

    return head_ptr;
}

int find_word(word_node* head_ptr, char* word) {
    if (head_ptr == NULL) {
        printf("the list has no words\n");

        return 0;
    }

    word_node* ptr = head_ptr;
    while (ptr != NULL) {
        if (strcmp(ptr -> word, word) == 0) {
            printf("word '%s' is in the list\n", word);

            return 0;
        }

        ptr = ptr -> next;
    }
    printf("word '%s' is not in the list\n", word);

    return 0;
}

// visualize list (runs at SIGINT or -quit)
void print_list(word_node* head_ptr) {
    if (head_ptr == NULL) {
        printf("the list has no words\n");
    }

    word_node* ptr = head_ptr;
    int count = 0;
    while (ptr != NULL) {
        count++;
        printf("%d. %s\n", count, ptr -> word);

        ptr = ptr -> next;
    }
}

void to_lowercase(char* word) {
    for (int i = 0, n = strlen(word); i < n; i++) {
        word[i] = tolower(word[i]);
    }
}

bool only_letters(char* word) {
    for (int i = 0, n = strlen(word); i < n; i++) {
        if (isalpha(word[i]) == 0) {
            return false;
        }
    }
    return true;
}

void free_nodes(word_node* head_ptr) {
    word_node* ptr = head_ptr;
    while (ptr != NULL) {
        word_node* next = ptr -> next;

        free(ptr -> word);
        free(ptr);

        ptr = next;
    }
}
