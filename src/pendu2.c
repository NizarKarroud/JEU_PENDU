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
int compare_root_nodes(const void *a, const void *b) ;
Node *guess_first_node(Node **roots_copy, int num_roots , char *random_word , char *mot_copy);

void guess_rest(Node *current_node , char *random_word , char *mot_copy , int index );

int main() {
    char *list[] = {
        "apple", "banana", "cherry", "grapes", "orange",
        "tiger", "elephant", "sparrow", "dolphin", "lizard",
        "mountain", "river", "desert", "ocean", "forest",
        "computer", "keyboard", "screen", "robot", "algorithm",
        "philosophy", "dream", "memory", "chaos", "harmony",
        "castle", "village", "bridge", "tunnel", "tower",
        "guitar", "violin", "drum", "trumpet", "flute",
        "energy", "gravity", "quantum", "nebula", "galaxy",
        "sunrise", "thunder", "hurricane", "avalanche", "volcano",
        "justice", "truth", "illusion", "destiny", "silence"
    };
    int N = sizeof(list) / sizeof(list[0]);
    srand(time(NULL));

    int random_index = rand() % N ;

    char *random_word = list[random_index];
    char *mot_copy = malloc((strlen(random_word) + 1) * sizeof(char));

    printf("The word to guess is : %s\n" , random_word);
    int nombre_tentative = (rand() %  10 ) + strlen(random_word) ;

    MarkovTree tree = {0, NULL};

    print_banner();

    for (int i = 0; i < N; i++) {
        insert_word(&tree, list[i]);
    }

    compute_probabilities_tree(tree.roots, tree.num_roots, NULL);

    int word_len = strlen(random_word);
    

    Node **roots_copy = malloc(sizeof(Node) * tree.num_roots);
    memcpy(roots_copy , tree.roots , tree.num_roots *sizeof(Node) );
    
    qsort(roots_copy, tree.num_roots, sizeof(Node*), compare_root_nodes);
    
    printf("\nGuessing the word .... \n");
    
    Node *first_node =  guess_first_node(roots_copy, tree.num_roots , random_word , mot_copy);
    free(roots_copy);
    guess_rest(first_node, random_word , mot_copy ,1 );
   
    // printf("=== Markov Tree ===\n");
    // for (int i = 0; i < tree.num_roots; i++) {
    //     print_tree(tree.roots[i], 0);
    // }
    
    for (int i = 0; i < tree.num_roots; i++) {
        free_tree(tree.roots[i]);
    }
    free(tree.roots);

    return 0;
}


int compare_root_nodes(const void *a, const void *b) {
    Node *nodeA = *(Node **)a;
    Node *nodeB = *(Node **)b;

    if (nodeA->probability < nodeB->probability) return 1;
    if (nodeA->probability > nodeB->probability) return -1;
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

Node *guess_first_node(Node **roots_copy, int num_roots , char *random_word , char *mot_copy){
    for (int i = 0; i < num_roots; i++) {
        if (roots_copy[i]->letter == random_word[0]){
            mot_copy[0] = roots_copy[i]->letter;

            printf("correct guess (%c) : %s\n" ,roots_copy[i]->letter, mot_copy) ; 
            return roots_copy[i];
        }
        else {
            printf("Incorrect guess (%c) the current word is : %s\n" , roots_copy[i]->letter , mot_copy);
        }
    }
}


void guess_rest(Node *current_node , char *random_word , char *mot_copy , int index ){

    if(current_node->num_children ==0){
        return ;  // c'est la fin du mot
    }

    Node **children_array_copy = malloc(sizeof(Node) * current_node->num_children);
    memcpy(children_array_copy , current_node->children , current_node->num_children *sizeof(Node) );

    qsort(children_array_copy, current_node->num_children, sizeof(Node*), compare_root_nodes);

    for (int i= 0 ; i < current_node->num_children ; i++){
        if (children_array_copy[i]->letter == random_word[index]){
            mot_copy[index] = children_array_copy[i]->letter;
            printf("correct guess (%c) : %s\n" ,children_array_copy[i]->letter, mot_copy) ; 
            guess_rest(children_array_copy[i], random_word, mot_copy, index + 1);
        }
        else {
            printf("Incorrect guess (%c) the current word is : %s\n" , children_array_copy[i]->letter , mot_copy);
        }

    }
}
