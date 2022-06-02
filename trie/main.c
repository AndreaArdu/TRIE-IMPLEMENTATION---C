//
//  main.c
//  trie
//
//  Created by Andrea Ardu on 26/05/22.
//


#include <stdio.h>
#include <stdlib.h>

#define NUM_CHARS 256
#define WORD_LEN 4

typedef enum { false, true } bool;

typedef struct trieNode{
    struct trienNode* children[NUM_CHARS];
    bool terminal;
}trieNode;

trieNode *create_node();
bool trie_insert(trieNode **, unsigned char *);
bool trie_delete_string(trieNode **, unsigned char *);
trieNode* trie_delete_string_recursive(trieNode *, unsigned char *, bool *);
void trie_print(trieNode *);
void trie_print_recursive(trieNode *, unsigned char *, int);
void builtin_memcy(void *, void *, size_t);
bool trie_search(trieNode *, unsigned char *text);

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("TRIE NODE DRIVER!\n\n");
    
    trieNode* root = NULL;
    printf("DATA INSERTION:\n");
    trie_insert(&root, "POCA");
    trie_insert(&root, "ONCA");
    trie_insert(&root, "CASA");
    trie_insert(&root, "COSA");
    trie_insert(&root, "SERA");
    trie_insert(&root, "CARA");
    trie_insert(&root, "CARO");
    printf("\nPRINTING TRIE NODE:\n");
    trie_print(root);
    printf("\nSEARCHING:\n");
    printf("Searching in TRIE for CASA: %d", trie_search(root, "CASA"));
    printf("\nSearching in TRIE for ACSO: %d", trie_search(root, "ACSO"));
    return 0;
}

trieNode *create_node() {
    trieNode *newNode = malloc(sizeof(* newNode));
    
    for(int i = 0; i < NUM_CHARS; i++){
        newNode->children[i] = NULL;
    }
    newNode->terminal = false;
    return newNode;
}

bool trie_insert(trieNode **root, unsigned char *text){
    if(*root == NULL)
        *root = create_node();
    
    trieNode *tmp = *root;
    
    for(int i = 0; i < WORD_LEN; i++) {
        if(tmp->children[text[i]] == NULL){
            // Create a new node
            tmp->children[text[i]] = create_node();
        }
        
        tmp = tmp->children[text[i]];
    }
    printf("ADDING: %s\n",text);

    if(tmp->terminal) {
        return false;
    } else {
        tmp-> terminal = true;
        return true;
    }
}

bool trie_delete_string(trieNode **root, unsigned char *text){
    bool result = false;
    
    if(*root == NULL){
        printf("TRIE IS EMPTY");
        return result;
    }
    
    *root = trie_delete_string_recursive(*root, text, &result);
    return result;
}

trieNode* trie_delete_string_recursive(trieNode *node, unsigned char *text, bool* result){
    if(node == NULL){
        return node;
    }
    
    if(*text == '\0'){
        if(node->terminal){
            node->terminal = false;
            *result = true;
            
            if(node_has_children(node) == false){
                free(node);
                node = NULL;
            }
        }
        return node;
    }
    
    node->children[text[0]] = trie_delete_string_re(node->children[text[0]], text+1, result);
}

bool trie_search(trieNode *root, unsigned char* text){
    
    trieNode *tmp= root;
    for(int i = 0; i < WORD_LEN; i++){
        if(tmp->children[text[i]] == NULL){
            return false;
        }
        
        tmp = tmp->children[text[i]];
    }
    if(tmp->terminal)
        return true;
    return false;
}

void trie_print_recursive(trieNode *node, unsigned char *prefix, int lenght){
    unsigned char newPrefix[lenght+2];
    builtin_memcy(newPrefix,prefix, lenght);
    newPrefix[lenght+1] = 0;
    
    if(node->terminal){
        printf("WORD IS %s \n", prefix);
    }
    
    for(int i = 0; i < NUM_CHARS; i++){
        if(node->children[i] != NULL){
            newPrefix[lenght] = i;
            trie_print_recursive(node->children[i], newPrefix, lenght+1);
        }
    }
}

void trie_print(trieNode* root){
    if (root == NULL){
        printf("TRIE IS EMPTY");
        return;
    }
    
    trie_print_recursive(root, NULL, 0);
}


void builtin_memcy(void *dest, void *src, size_t n)
{
   // Typecast src and dest addresses to (char *)
   char *csrc = (char *)src;
   char *cdest = (char *)dest;
  
   // Copy contents of src[] to dest[]
   for (int i=0; i<n; i++)
       cdest[i] = csrc[i];
}
