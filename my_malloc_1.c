#include "my_malloc_1.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void * ff_malloc(size_t size) {

    if (head == NULL){

        Metadata* myData = allocate_block(size);

        return (void*)myData + sizeof(Metadata);

    }

    Metadata* trav = head;

    while (trav != NULL && trav->size < size){
        trav = trav->next;
    }

    if (trav == NULL){

        Metadata* myData = allocate_block(size);

        return (void*)myData + sizeof(Metadata);

    }

    else{

        return reuse_block(size, trav);


    }

}



void * reuse_block(size_t size, Metadata * p) {

    // remove_from_ll(trav);

    // free_size -= trav->sz + sizeof(Node); 

    // if (trav->sz - size > sizeof(Node)){
                
    //     Node* myNode = (void *)trav + sizeof(Node) + size;

    //     myNode -> sz = trav->sz - size - sizeof(Node);
    //     myNode -> next = NULL;
    //     myNode -> previous = NULL;
                    
    //     add_to_ll(myNode);

    //     free_size += myNode->sz + sizeof(Node);

    //     check_adjacent(myNode);

    //     trav->sz = size;

    // }

    // return (void*)trav + sizeof(Node);


  if (p->size > size + sizeof(Metadata)) {

    Metadata * splitted_block;
    splitted_block = (Metadata *)((char *)p + sizeof(Metadata) + size);
    splitted_block->size = p->size - size - sizeof(Metadata);
    
    splitted_block->next = NULL;
    splitted_block->previous = NULL;

    remove_block(p);
    add_block(splitted_block);
    p->size = size;
    free_size -= (size + sizeof(Metadata));
  }
  else {
    remove_block(p);
    free_size -= (p->size + sizeof(Metadata));
  }
  return (char *)p + sizeof(Metadata);


}



void * allocate_block(size_t size) {//!checked!

  data_size += size + sizeof(Metadata);

  Metadata * new_block = sbrk(size + sizeof(Metadata));
  
  new_block->size = size;
  
  new_block->previous = NULL;
  new_block->next = NULL;

  return new_block;

}

void add_block(Metadata * curr) {//!checked!

    if (head == NULL){

        head = curr;
        //curr->next = NULL;
        //curr->previous = NULL;
    
    }

    if (curr < head){

        curr->next = head;
        head = curr;
        curr->next->previous = curr;
        //curr->previous = NULL;

    }

    Metadata* trav = head;

    while (trav->next != NULL && curr > trav->next){
        trav = trav->next;
    }

    if (trav->next == NULL){

        trav->next = curr;
        curr->previous = trav;
        curr->next = NULL;

    }

    else{

        Metadata* store = trav->next;
        trav->next = curr;
        curr->next = store;
        curr->previous = trav;
        store->previous = curr;

    }

     

}

void remove_block(Metadata * curr) {//!checked!

    if (curr->next == NULL && curr->previous == NULL){
        head = NULL;
    }
    else if (curr->previous == NULL){
        head = curr->next;
        head->previous = NULL;
        //curr->next = NULL;
    
    }
    else if (curr->next == NULL){
        curr->previous->next = NULL;
        //curr->previous = NULL;
    }
    else{
        curr->previous->next = curr->next;
        curr->next->previous = curr->previous;
        //curr->next = NULL;
        //curr->previous = NULL;

    }

}


void check_adjacent(Metadata* curr){//!checked!

    if (curr->next != NULL && (void*) curr + sizeof(Metadata) + curr->size == (void*) curr->next){
        
        curr->size += curr->next->size + sizeof(Metadata);//changed
        remove_block(curr->next);//changed
        free_size -= sizeof(Metadata);
    }

    if (curr->previous != NULL && (void*) curr->previous + sizeof(Metadata) + curr->previous->size == (void*) curr){
        

        curr->previous->size += curr->size + sizeof(Metadata);//changed
        remove_block(curr);//changed
        free_size -= sizeof(Metadata);

    }

}

void ff_free(void * ptr) {

    Metadata* curr = (void *)ptr - sizeof(Metadata);

    free_size += curr->size + sizeof(Metadata);

    add_block(curr);

    check_adjacent(curr);

}

void * bf_malloc(size_t size) {

  Metadata * p = head;
  Metadata * min_ptr = NULL;
  while (p != NULL) {
    if (p->size > size) {
      if ((min_ptr == NULL) || (p->size < min_ptr->size)) {
        min_ptr = p;
      }
    }
    if (p->size == size) {
      min_ptr = p;
      break;
    }
    p = p->next;
  }
  if (min_ptr != NULL) {
    return reuse_block(size, min_ptr);
  }
  else {
    return (void*)allocate_block(size) + sizeof(Metadata);

  }
}

void bf_free(void * ptr) {
  return ff_free(ptr);
}



unsigned long get_data_segment_size() {
  return data_size;
}

unsigned long get_data_segment_free_space_size() {
  return free_size;
}