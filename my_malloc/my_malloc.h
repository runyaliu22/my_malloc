#ifndef __MY_MALLOC_H__
#define __MY_MALLOC_H__

#include <stdio.h>
#include <stdlib.h>


struct node {
  size_t size;
  struct node * next;
  struct node * prev;
};

typedef struct node Metadata;

Metadata * head = NULL;
//Metadata * tail = NULL;

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

#endif