#include "code.h"
#include "trie.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

//constructor
TrieNode *trie_node_create(uint16_t code) {

    //allocate mem for the entire node
    TrieNode *node = (TrieNode *) malloc(sizeof(TrieNode));

    //if allocation is successful
    if (node) {

        //set code val to code
        node->code = code;

        //allocate mem for the children array
        //node->children = (TrieNode *) malloc( sizeof(TrieNode) );

        for (int i = 0; i < ALPHABET; i++) {

            node->children[i] = NULL;
        }

    } else {
        //unsuccessful allocation, null pointer and free mem
        free(node);

        node = NULL;
    }

    //return pointer to the specific created trie node object, if failure in allocation, returns null
    return node;
}

//delete a node
void trie_node_delete(TrieNode *n) {

    //free and null
    free(n);
    n = NULL;
}

//create the root of the tree
TrieNode *trie_create(void) {

    //run the constructor function
    TrieNode *root = trie_node_create(EMPTY_CODE);

    return root;
}

//delete a node, and its children
void trie_delete(TrieNode *n) {

    //loop through the children array in n
    for (int i = 0; i < ALPHABET; i++) {

        //if there is a child at arr[i], run trie delete on that node to clear its children
        if (n->children[i] != NULL) {

            trie_delete(n->children[i]);
        }
    }

    //delete the node
    trie_node_delete(n);
}

//clear root, and delete the entire trie branching off the root
void trie_reset(TrieNode *root) {

    //this will free and null the root, and everything else
    trie_delete(root);

    //remake root
    root = trie_node_create(START_CODE);
}

//checks for a node called sym among n's children
TrieNode *trie_step(TrieNode *n, uint8_t sym) {

    if (n->children[sym] != NULL) {

        return n->children[sym];
    }

    return NULL;
}
