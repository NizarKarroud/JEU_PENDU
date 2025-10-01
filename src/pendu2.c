#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    char letter;
    int freq;                  
    float probability;         
    int num_children;
    struct Node **children;
} Node;

typedef struct MarkovTree {
    int num_roots;
    Node **roots;
} MarkovTree;

Node *create_node(char letter) ;
Node *find_or_create_child(Node *parent, char letter) ;
void insert_word(MarkovTree *tree, const char *word) ;
void compute_probabilities_tree(Node **nodes, int num_nodes, Node *parent) ;
void print_tree(Node *node, int depth) ;
void free_tree(Node *node);
void print_banner(void);



int main() {
    char *list[] = {"apple", "banana", "cherry", "grapes", "goranges" ,"belt" , "best"};
    int N = sizeof(list) / sizeof(list[0]);
    srand(time(NULL));

    int random_index = rand() % N ;

    char *random_word = list[random_index];
    int nombre_tentative = (rand() %  10 ) + strlen(random_word) ;

    MarkovTree tree = {0, NULL};

    print_banner();

    for (int i = 0; i < N; i++) {
        insert_word(&tree, list[i]);
    }

    compute_probabilities_tree(tree.roots, tree.num_roots, NULL);

    

    
    



    printf("=== Markov Tree ===\n");
    for (int i = 0; i < tree.num_roots; i++) {
        print_tree(tree.roots[i], 0);
    }
    
    for (int i = 0; i < tree.num_roots; i++) {
        free_tree(tree.roots[i]);
    }
    free(tree.roots);

    return 0;
}


Node *create_node(char letter) {
    Node *node = malloc(sizeof(Node));
    node->letter = letter;
    node->freq = 1;
    node->probability = 0.0f;
    node->num_children = 0;
    node->children = NULL;
    return node;
}

Node *find_or_create_child(Node *parent, char letter) {
    for (int i = 0; i < parent->num_children; i++) {
        if (parent->children[i]->letter == letter) {
            parent->children[i]->freq++;
            return parent->children[i];
        }
    }
    parent->num_children++;
    parent->children = realloc(parent->children, parent->num_children * sizeof(Node*));
    parent->children[parent->num_children-1] = create_node(letter);
    return parent->children[parent->num_children-1];
}

void insert_word(MarkovTree *tree, const char *word) {

    char first = word[0];
    Node *root = NULL;
    for (int i = 0; i < tree->num_roots; i++) {
        if (tree->roots[i]->letter == first) {  // si la 1er lettre se trouve dans les roots des mots , just increment the freq
            root = tree->roots[i];
            root->freq++;
            break;
        }
    }
    if (!root) { // si la letter n'est pas dans la list 
        tree->num_roots++;
        tree->roots = realloc(tree->roots, tree->num_roots * sizeof(Node*)); // on agrandit la list des noeuds pour ajouter la lettre 
        root = create_node(first);
        tree->roots[tree->num_roots-1] = root;
    }

    Node *current = root;

    for (int i = 1; word[i] != '\0'; i++) {
        current = find_or_create_child(current, word[i]);
    }
}

void compute_probabilities_tree(Node **nodes, int num_nodes, Node *parent) {
    int total = 0;

    if (parent == NULL) {
        for (int i = 0; i < num_nodes; i++) {
            total += nodes[i]->freq;
        }
    } else {
        for (int i = 0; i < parent->num_children; i++) {
            total += parent->children[i]->freq;
        }
    }

    for (int i = 0; i < num_nodes; i++) {
        nodes[i]->probability = (float)nodes[i]->freq / total;

        if (nodes[i]->num_children > 0) {
            compute_probabilities_tree(nodes[i]->children, nodes[i]->num_children, nodes[i]);
        }
    }
}


void print_tree(Node *node, int depth) {
    for (int i = 0; i < depth; i++) printf("  ");
    printf("'%c' (freq=%d, prob=%.2f)\n", node->letter, node->freq, node->probability);

    for (int i = 0; i < node->num_children; i++) {
        print_tree(node->children[i], depth + 1);
    }
}

void free_tree(Node *node) {
    for (int i = 0; i < node->num_children; i++) {
        free_tree(node->children[i]);
    }
    free(node->children);
    free(node);
}


void print_banner(void){


    printf("\n");

    printf("     ▄█    ▄████████ ███    █▄       ████████▄  ███    █▄          ▄███████▄    ▄████████ ███▄▄▄▄   ████████▄  ███    █▄  \n");
    printf("    ███   ███    ███ ███    ███      ███   ▀███ ███    ███        ███    ███   ███    ███ ███▀▀▀██▄ ███   ▀███ ███    ███ \n");
    printf("    ███   ███    █▀  ███    ███      ███    ███ ███    ███        ███    ███   ███    █▀  ███   ███ ███    ███ ███    ███ \n");
    printf("    ███  ▄███▄▄▄     ███    ███      ███    ███ ███    ███        ███    ███  ▄███▄▄▄     ███   ███ ███    ███ ███    ███ \n");
    printf("    ███ ▀▀███▀▀▀     ███    ███      ███    ███ ███    ███      ▀█████████▀  ▀▀███▀▀▀     ███   ███ ███    ███ ███    ███ \n");
    printf("    ███   ███    █▄  ███    ███      ███    ███ ███    ███        ███          ███    █▄  ███   ███ ███    ███ ███    ███ \n");
    printf("    ███   ███    ███ ███    ███      ███   ▄███ ███    ███        ███          ███    ███ ███   ███ ███   ▄███ ███    ███ \n");
    printf("█▄ ▄███   ██████████ ████████▀       ████████▀  ████████▀        ▄████▀        ██████████  ▀█   █▀  ████████▀  ████████▀  \n");
    printf("▀▀▀▀▀▀                                                                                                                     \n");

    printf("\n");

}