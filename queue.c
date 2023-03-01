#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head =
        (struct list_head *) malloc(sizeof(struct list_head));

    if (!head) {
        free(head);
        return NULL;
    }

    INIT_LIST_HEAD(head);

    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *l)
{
    if (!l)
        return;

    element_t *entry, *safe;

    list_for_each_entry_safe (entry, safe, l, list)
        q_release_element(entry);

    free(l);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *new_element = malloc(sizeof(element_t));

    if (!new_element)
        return false;

    new_element->value = strdup(s);

    if (!new_element->value) {
        free(new_element);
        return false;
    }

    list_add(&new_element->list, head);

    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;

    element_t *new_element = malloc(sizeof(element_t));

    if (!new_element)
        return false;

    new_element->value = strdup(s);

    if (!new_element->value) {
        free(new_element);
        return false;
    }

    list_add_tail(&new_element->list, head);

    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *target = list_first_entry(head, element_t, list);
    list_del_init(&target->list);

    if (sp) {
        strncpy(sp, target->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }

    return target;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *target = list_last_entry(head, element_t, list);
    list_del_init(&target->list);

    if (sp) {
        strncpy(sp, target->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }

    return target;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head || list_empty(head))
        return 0;

    int size = 0;
    struct list_head *li;

    list_for_each (li, head)
        size++;

    return size;
}

/* Delete the middle node in queue */
// https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
bool q_delete_mid(struct list_head *head)
{
    if (!head || list_empty(head))
        return false;

    struct list_head *pre = head->prev;
    struct list_head *nex = head->next;

    // Fifd the middle of list
    do {
        pre = pre->prev;
        nex = nex->next;
    } while (pre != nex && pre != nex->next);

    list_del(pre);
    element_t *target = list_entry(pre, element_t, list);
    q_release_element(target);

    return true;
}

/* Delete all nodes that have duplicate string */
// https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
bool q_delete_dup(struct list_head *head)
{
    if (!head || list_empty(head))
        return false;

    bool dup = false;
    element_t *target, *temp;

    list_for_each_entry_safe (target, temp, head, list) {
        if (target->list.next != head && !strcmp(target->value, temp->value)) {
            dup = true;
            list_del(&target->list);
            q_release_element(target);
        } else if (dup) {
            dup = false;
            list_del(&target->list);
            q_release_element(target);
        }
    }

    return true;
}

/* Swap every two adjacent nodes */
// https://leetcode.com/problems/swap-nodes-in-pairs/
/*
void q_swap(struct list_head *head)
{

    struct list_head *node = NULL;
    for (node = head->next; node != head && node->next != head;
         node = node->next) {
        struct list_head *next = node->next;
        list_move_tail(node, next);
    }
}
*/

void q_swap(struct list_head *head)
{
    if (!head || list_empty(head))
        return;

    q_reverseK(head, 2);
}

/* Reverse elements in queue */

void q_reverse(struct list_head *head)
{
    element_t *entry, *safe;
    list_for_each_entry_safe (entry, safe, head, list)
        list_move(&entry->list, head);
}

/* Reverse the nodes of the list k at a time */
// https://leetcode.com/problems/reverse-nodes-in-k-group/
void q_reverseK(struct list_head *head, int k)
{
    if (!head || list_empty(head))
        return;

    struct list_head *node = NULL, *safe = NULL, *insert = head;
    int count = 0;

    list_for_each_safe (node, safe, head) {
        if (k > count)
            list_move(node, insert);
        else {
            count = 0;
            insert = node->prev;
        }
        count++;
    }
}

/* Sort elements of queue in ascending order */
void q_sort(struct list_head *head)
{
    if (!head || list_empty(head))
        return;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
// https://leetcode.com/problems/remove-nodes-from-linked-list/
int q_descend(struct list_head *head)
{
    /*if (!head || list_empty(head))
        return 0;

    struct list_head *greater = head->prev;
    struct list_head *temp = greater->prev;
    element_t *g, *t;
    int len = 1;

    while (temp != head) {
        g = list_entry(greater, element_t, list);
        t = list_entry(temp, element_t, list);

        if (strcmp(t->value, g->value) < 0) {
            temp = temp->prev;
            list_del_init(&t->list);
        } else {
            greater = temp;
            temp = greater->prev;
            len++;
        }
    }*/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending order */
// https://leetcode.com/problems/merge-k-sorted-lists/
int q_merge(struct list_head *head)
{
    return 0;
}
