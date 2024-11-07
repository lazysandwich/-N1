#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct WordNode {
    char* word;
    int count;
    struct WordNode* left;
    struct WordNode* right;
} WordNode;

typedef struct {
    WordNode* root;
} BST;

WordNode* create_node(const char* word) {
    WordNode* newNode = (WordNode*)malloc(sizeof(WordNode));
    newNode->word = strdup(word);
    newNode->count = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void free_node(WordNode* node) {
    if (node) {
        free(node->word);
        free(node);
    }
}

void free_bst(WordNode* node) {
    if (node) {
        free_bst(node->left);
        free_bst(node->right);
        free_node(node);
    }
}

void insert_word(BST* tree, const char* word) {
    WordNode** current = &(tree->root);
    while (*current) {
        int cmp = strcmp(word, (*current)->word);
        if (cmp == 0) {
            (*current)->count++;
            return;
        }
        current = (cmp < 0) ? &((*current)->left) : &((*current)->right);
    }
    *current = create_node(word);
}

void in_order_traversal(WordNode* node) {
    if (node) {
        in_order_traversal(node->left);
        printf("%s: %d\n", node->word, node->count);
        in_order_traversal(node->right);
    }
}

int search_word(BST* tree, const char* word) {
    WordNode* current = tree->root;
    while (current) {
        int cmp = strcmp(word, current->word);
        if (cmp == 0) {
            return current->count;
        }
        current = (cmp < 0) ? current->left : current->right;
    }
    return 0;
}

void find_longest_shortest(BST* tree, char longest, char shortest) {
    if (!tree->root) return;
    WordNode* current = tree->root;
    longest = shortest = current->word;
    while (current) {
        if (strlen(current->word) > strlen(longest)) {
            longest = current->word;
        }
        if (strlen(current->word) < strlen(shortest)) {
            shortest = current->word;
        }
        current = (current->right) ? current->right : current->left;
    }
}

void save_bst_to_file(WordNode* node, FILE* file) {
    if (node) {
        fprintf(file, "%s %d\n", node->word, node->count);
        save_bst_to_file(node->left, file);
        save_bst_to_file(node->right, file);
    }
}

WordNode* restore_bst_from_file(FILE* file) {
    char word[256];
    int count;
    WordNode* root = NULL;

    while (fscanf(file, "%s %d", word, &count) == 2) {
        for (int i = 0; i < count; i++) {
            insert_word(&(BST){ .root = root }, word);
        }
    }
    return root;
}

void read_words_from_file(const char* filename, const char* separators[], int sep_count, BST* tree) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        char* token = strtok(buffer, separators[0]);
        while (token) {
            insert_word(tree, token);
            token = strtok(NULL, separators[0]);
        }
    }
    fclose(file);
}

void depth_first_search(WordNode* node) {
    if (node) {
        printf("%s: %d\n", node->word, node->count);
        depth_first_search(node->left);
        depth_first_search(node->right);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprint("неверное кол-во аргументов");
        return 1;
    }
    BST tree = { .root = NULL };
    read_words_from_file(argv[1], &argv[2], argc - 2, &tree);
    char command[100];
    while (1) {
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;
        if (strcmp(command, "exit") == 0) {
            break;
        } 
        else if (strcmp(command, "dfs") == 0) {
            depth_first_search(tree.root);
        } 
        else if (strcmp(command, "save") == 0) {
            FILE* file = fopen("bst_data.txt", "w");
            if (file) {
                save_bst_to_file(tree.root, file);
                fclose(file);
                printf("Tree saved to bst_data.txt\n");
            }
        } else if (strcmp(command, "restore") == 0) {
            FILE* file = fopen("bst_data.txt", "r");
            if (file) {
                tree.root = restore_bst_from_file(file);
                fclose(file);
                printf("Tree restored from bst_data.txt\n");
            }
        } else if (strncmp(command, "count ", 6) == 0) {
            printf("Count for word '%s': %d\n", command + 6, search_word(&tree, command + 6));
        } else if (strncmp(command, "top_n ", 6) == 0) {
            int n = atoi(command + 6);
        } else if (strcmp(command, "longest") == 0) {
            char* longest = NULL;
            char* shortest = NULL;
            find_longest_shortest(&tree, &longest, &shortest);
            printf("Longest word: %s\nShortest word: %s\n", longest, shortest);
        }
    }
    free_bst(tree.root);
    return 0;
}