#include <stdio.h>
#include <stdlib.h>



struct metadata {
  size_t size;
  struct metadata * next;
  struct metadata * prev;
};

typedef struct metadata Metadata;

Metadata * head = NULL;


size_t data_segment = 0;
size_t data_segment_free = 0;


void check_adjacent(Metadata* curr);
void * reuse_block(size_t size, Metadata * p);
void * allocate_new_block(size_t size);
void add_to_ll(Metadata * p);
void remove_from_ll(Metadata * p);
void * ff_malloc(size_t size);
void ff_free(void * ptr);
void * bf_malloc(size_t size);
void bf_free(void * ptr);

unsigned long get_data_segment_size();             //in bytes
unsigned long get_data_segment_free_space_size();  //in bytes

