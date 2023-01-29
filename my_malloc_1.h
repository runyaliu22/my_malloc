#ifndef __MY_MALLOC_H__
#define __MY_MALLOC_H__

#include <stdio.h>
#include <stdlib.h>




struct metadata {
  size_t size;
  struct metadata * next;
  struct metadata * previous;
};

typedef struct metadata Metadata;

Metadata * head = NULL;


size_t data_size = 0;
size_t free_size = 0;


void check_adjacent(Metadata* curr);
void * reuse_block(size_t size, Metadata * p);
void * allocate_block(size_t size);
void add_block(Metadata * p);
void remove_block(Metadata * p);
void * ff_malloc(size_t size);
void ff_free(void * ptr);
void * bf_malloc(size_t size);
void bf_free(void * ptr);

unsigned long get_data_segment_size();             //in bytes
unsigned long get_data_segment_free_space_size();  //in bytes

#endif