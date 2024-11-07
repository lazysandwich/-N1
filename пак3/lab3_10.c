#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    char bracket;
    struct TreeNode** children;
    int child_count;
} TreeNode;

TreeNode* create_node(char bracket) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->bracket = bracket;
    node->children = NULL;
    node->child_count = 0;
    return node;
}

void free_tree(TreeNode* node) {
    if (node) {
        for (int i = 0; i < node->child_count; i++) {
            free_tree(node->children[i]);
        }
        free(node->children);
        free(node);
    }
}

void print_tree(TreeNode* node, FILE* output, int level) {
    if (!node) return;
    for (int i = 0; i < level; i++) {
        fprintf(output, "    ");
    }
    fprintf(output, "%c\n", node->bracket);
    for (int i = 0; i < node->child_count; i++) {
        print_tree(node->children[i], output, level + 1);
    }
}

TreeNode* parse_expression(const char* expression, int* index) {
    TreeNode* root = NULL;
    while (expression[*index] != '\0') {
        char current = expression[*index];
        (*index)++;
        if (current == '(' || current == '[' || current == '{') {
            TreeNode* node = create_node(current);
            if (root == NULL) {
                root = node;
            }
            node->children = (TreeNode**)malloc(sizeof(TreeNode*) * 10);
            node->child_count = 0;
            while (expression[*index] != '\0' && expression[*index] != ')' && expression[*index] != ']' && expression[*index] != '}') {
                if (expression[*index] == '(' || expression[*index] == '[' || expression[*index] == '{') {
                    node->children[node->child_count] = parse_expression(expression, index);
                    node->child_count++;
                }
            }
            if (expression[*index] == ')'|| expression[*index] == ']' || expression[*index] == '}') {
                (*index)++;
            }
        } else if (current == ')' || current == ']' || current == '}') {
            break;
        }
    }
    return root;
}

void process_line(const char* line, FILE* output) {
    int index = 0;
    TreeNode* root = parse_expression(line, &index);
    print_tree(root, output, 0);
    free_tree(root);
}

void process_file(const char* input_file, const char* output_file) {
    FILE* infile = fopen(input_file, "r");
    if (!infile) {
        perror("Failed to open input file");
        return;
    }
    FILE* outfile = fopen(output_file, "w");
    if (!outfile) {
        perror("Failed to open output file");
        fclose(infile);
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), infile)) {
        line[strcspn(line, "\n")] = 0;
        process_line(line, outfile);
        fprintf(outfile, "\n");
    }
    fclose(infile);
    fclose(outfile);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        perror("файл не открыл");
        exit(EXIT_FAILURE);
    }
    process_file(argv[1], argv[2]);
    return EXIT_SUCCESS;
}