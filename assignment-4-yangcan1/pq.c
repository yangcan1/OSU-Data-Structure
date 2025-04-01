/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name:Can Yang
 * Email:yangca@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>

#include "pq.h"
#include "dynarray.h"

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 */
struct element {
  int priority;
  void* val;
};

struct pq {
  struct dynarray* heap;
};

/* 
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	struct pq *pq = malloc(sizeof(struct pq));
    pq->heap = dynarray_create();
	return pq;
}


/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	dynarray_free(pq->heap);
    free(pq);
	return;
}


/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	if (dynarray_size(pq->heap) == 0) {
        return 1;
    }
	return 0;
}


/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */

void pq_insert(struct pq* pq, void* value, int priority) {
	struct element *element = malloc(sizeof(struct element));
    element->priority = priority;
    element->val = value;

    dynarray_insert(pq->heap, element);
    int curr_idx = dynarray_size(pq->heap) -1;
    int parent_idx = (curr_idx -1)/2;
    struct element *parent = dynarray_get(pq->heap, parent_idx);
    
    while (priority < parent->priority) {
        dynarray_set(pq->heap, parent_idx, element);
        dynarray_set(pq->heap, curr_idx, parent);
        curr_idx = parent_idx;
        parent_idx = (curr_idx -1)/2;
        parent = dynarray_get(pq->heap, parent_idx);
    }

	return;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
    struct element *element = dynarray_get(pq->heap, 0);
	return element->val;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
    struct element *element = dynarray_get(pq->heap, 0);
	return element->priority;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */

/*
  This function is to swap value of index with its parent.
*/
void swap(struct dynarray *da, int idx1, int idx2){
    struct element *ele1 = dynarray_get(da, idx1);
    struct element *ele2 = dynarray_get(da, idx2);
    dynarray_set(da, idx1, ele2);
    dynarray_set(da, idx2, ele1);
}

int cmp_smaller(struct dynarray *da, int left, int right) {
    struct element *l = dynarray_get(da, left);
    struct element *r = dynarray_get(da, right);
    if (l->priority < r->priority) {
        return left;
    }
    return right;
}

void* pq_remove_first(struct pq* pq) {
    int size = dynarray_size(pq->heap);
    struct element *return_ele = dynarray_get(pq->heap, 0);
    void* return_val = return_ele->val;
    if (size == 1) {
        dynarray_remove(pq->heap, 0);
        free(return_ele);
        return return_val;
    }
    free(return_ele);

    struct element *last_ele = dynarray_get(pq->heap, size-1);
    int left_idx, curr_idx = 0, right_idx;
    dynarray_set(pq->heap, 0, last_ele);
    dynarray_remove(pq->heap, size - 1);
    while (1) {
        size = dynarray_size(pq->heap);
        left_idx = 2 * curr_idx + 1;
        right_idx = 2 * curr_idx + 2;
        // only left child exist and smaller than curr element
        if (right_idx == size && (cmp_smaller(pq->heap, left_idx, curr_idx) == left_idx)) {
            swap(pq->heap, curr_idx, left_idx);
            curr_idx = left_idx;
            continue;
        }
        // both element exist and one of them is smaller 
        else if (right_idx < size) {
            int smaller_idx = cmp_smaller(pq->heap, left_idx, right_idx);
            if (cmp_smaller(pq->heap, smaller_idx, curr_idx) == smaller_idx) {
                swap(pq->heap, smaller_idx, curr_idx);
                curr_idx = smaller_idx;
                continue;
            }
        }
        break;
    }

    return return_val;
}

