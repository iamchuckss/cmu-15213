/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
        return q;
    // instantiates values
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* Remember to free the queue structure and list elements */
    // free queue structure
    if (q == NULL)
        return;
    // free nodes
    list_ele_t* ele = q->head;
    while (ele != NULL) {
        list_ele_t *point = ele;
        ele = ele->next;
        free(point);
    }
    free(q);  // free queue
    return;
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    // if q is NULL
    if (q == NULL)
        return false;

    list_ele_t* temp = malloc(sizeof(list_ele_t));
    /* What if malloc returned NULL? */
    if (temp == NULL)
        return false;

    temp->value = v;
    temp->next = q->head;
    q->head = temp;
    if (q->size == 0) {
        q->tail = temp;
    }
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    /* Remember: It should operate in O(1) time */

    // if q is NULL
    if (q == NULL)
        return false;

    list_ele_t* temp = malloc(sizeof(list_ele_t));
    if (temp == NULL)
        return false;
    temp->value = v;
    temp->next = NULL;
    if (q->size == 0) {
        q->tail = temp;
        q->head = temp;
    } else {
        q->tail->next = temp;
        q->tail = q->tail->next;
    }
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    if (q == NULL || q->size == 0)
        return false;
    list_ele_t* temp = q->head;
    q->head = q->head->next;
    q->size--;
    if (vp != NULL) {
        *vp = temp->value;
    }
    free(temp);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
        return 0;
    return q->size;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->size == 0)
        return;
    list_ele_t* left = q->head;
    list_ele_t* right = q->head->next;

    q->tail = q->head;
    q->tail->next = NULL;
    while (right != NULL) {
        list_ele_t* temp = right->next;
        right->next = left;
        left = right;
        right = temp;
    }
    q->head = left;
}

