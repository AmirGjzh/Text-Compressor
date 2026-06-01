#ifndef COMPRESS_FUNCTIONS_H
#define COMPRESS_FUNCTIONS_H

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

// Tree node structure for Huffman tree
typedef struct tree {
    int data;
    int freq;
    struct tree *left;
    struct tree *right;
} Tree;

// Queue node for managing tree nodes
typedef struct queue {
    Tree *main;
    struct queue *next;
} Queue;

// Huffman code structure for storing character codes
typedef struct hf_code {
    char code[100];
    int data;
    struct hf_code *next;
} Hf_code;

// Console color enum for Windows
typedef enum {
    RED = 4, WHITE = 7, BLUE = 2, GREEN = 10, LIGHT_BLUE = 3
} ConsoleColors;

// Function declarations
void SetColor(ConsoleColors col);

Queue* add_to_queue(Queue *head1, int w);
Queue* delete_queue(Queue *head2);
void sort_queue(Queue *head1);
Queue* build_huffman_tree(Queue *head1);
void show_huffman_codes(Tree *main, char *code, int index, FILE *file);

Hf_code* add_to_hf_queue(Hf_code *node1, char *code, int val);
char* search_hf_queue(Hf_code *node1, int val);

void free_tree(Tree *main1);
void free_queue(Queue *head1);
void free_hf_queue(Hf_code *node1);

void binary(int n, FILE *file);
Tree* add_to_tree(Tree *main, char *s, int data);

#endif // COMPRESS_FUNCTIONS_H
