#include <stdio.h>
#include <stdlib.h>


// #define NEW_NODE { 0, NULL, NULL}

struct node{
    size_t sz;
    struct node* next;
    struct node* previous;
};
typedef struct node Node;

Node* head = NULL;


size_t free_size = 0;
size_t occupied_size = 0;


//First Fit malloc/free
void remove_from_ll(Node* curr);
void *ff_malloc(size_t size);
void ff_free(void *ptr);
void* reuse(Node* trav, size_t size);

//Best Fit malloc/free
void *bf_malloc(size_t size);
void bf_free(void *ptr);

void add_to_ll(Node* curr);
void check_adjacent(Node* curr);
void* allocate_new(size_t size);


unsigned long get_data_segment_size();
unsigned long get_data_segment_free_space_size();
