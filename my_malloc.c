#include "my_malloc.h"
#include <unistd.h>
#include "limits.h"

void* allocate_new(size_t size){

    Node* myNode = sbrk(size + sizeof(Node));
   
    myNode -> sz = size;
    myNode -> next = NULL;
    myNode -> previous = NULL;

    occupied_size += size + sizeof(Node);

    return myNode;

}


void remove_from_ll(Node* curr){

    if (curr->next == NULL && curr->previous == NULL){
        head = NULL;
    }
    else if (curr->previous == NULL){
        head = curr->next;
        head->previous = NULL;
    }
    else if (curr->next == NULL){
        curr->previous->next = NULL;
    }
    else{
        curr->previous->next = curr->next;
        curr->next->previous = curr->previous;

    }
  
  
}


void *ff_malloc(size_t size){

    if (head == NULL){

        Node* myNode = allocate_new(size);

        return (void*)myNode + sizeof(Node);
    }

    else{

        Node* trav = head;

        while (trav != NULL && trav->sz < size){
            trav = trav->next;
        }

        if (trav == NULL){

            Node* myNode = allocate_new(size);

            return (void*)myNode + sizeof(Node);

        }

        else{

            return reuse(trav, size);
        }
    }
}


void* reuse(Node* trav, size_t size){

    remove_from_ll(trav);

    free_size -= trav->sz + sizeof(Node); 

    if (trav->sz - size > sizeof(Node)){
                
        Node* myNode = (void *)trav + sizeof(Node) + size;

        myNode -> sz = trav->sz - size - sizeof(Node);
        myNode -> next = NULL;
        myNode -> previous = NULL;
                    
        add_to_ll(myNode);

        free_size += myNode->sz + sizeof(Node);

        check_adjacent(myNode);

        trav->sz = size;//////!!!!!!!原来如此！

    }

    return (void*)trav + sizeof(Node);

}

void add_to_ll(Node* curr){
    
    if (head == NULL){
        head = curr;
        return;
    }

    if (curr < head){
        curr->next = head;
        head = curr;
        curr->next->previous = curr;
        curr->previous = NULL;
        return;
    }

    Node* trav = head;

    while (trav->next != NULL && curr > trav->next){
        trav = trav->next;
    }

    if (trav->next == NULL){

        trav->next = curr;
        curr->previous = trav;
        curr->next = NULL;

    }

    else{

        Node* store = trav->next;
        trav->next = curr;
        curr->next = store;
        curr->previous = trav;
        store->previous = curr;

    }

    check_adjacent(curr);

}


void check_adjacent(Node* curr){

    if (curr->next != NULL && (void*) curr + sizeof(Node) + curr->sz == (void*) curr->next){
        
        curr->sz += curr->next->sz + sizeof(Node);//changed
        remove_from_ll(curr->next);//changed
        //free_size -= sizeof(Node);
    }

    if (curr->previous != NULL && (void*) curr->previous + sizeof(Node) + curr->previous->sz == (void*) curr){
        

        curr->previous->sz += curr->sz + sizeof(Node);//changed
        remove_from_ll(curr);//changed
        //free_size -= sizeof(Node);

    }

}

void ff_free(void *ptr){

    Node* curr = (void *)ptr - sizeof(Node);

    free_size += curr->sz + sizeof(Node);

    add_to_ll(curr);

}

unsigned long get_data_segment_size() {
    return occupied_size;
}

unsigned long get_data_segment_free_space_size() {
    
    return free_size;
  
}

//Best Fit malloc/free
void *bf_malloc(size_t size){


    Node* myNode = NULL;

    Node* trav = head;
    
    while (trav != NULL){

        if (trav->sz == size){
            remove_from_ll(trav);
            free_size -= trav->sz + sizeof(Node);
            return (void*)trav + sizeof(Node);
        }


        if (trav->sz > size){

            if (myNode== NULL || trav->sz < myNode->sz){
                myNode = trav;
            }

        }

        trav = trav->next;

    }

    if (myNode == NULL){

        Node* myNode = allocate_new(size);

        return (void*)myNode + sizeof(Node);

    }
    else{

        return reuse(myNode, size);

    }

}


void bf_free(void *ptr){

    ff_free(ptr);

}