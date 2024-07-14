/**
 * @file linked_list.h
 * @brief generic linked list implementation
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "common.h"

/**
 * @typedef fn_free_data_t(void *)
 * @brief function used to free the data stored in the linked list
 * It takes a pointer to the data as an argument and returns a boolean value
 * @note if the function returns TRUE, the data is freed successfully
 */
typedef char (*fn_free_data_t)(void *);

/**
 * @struct linked_list_node_t
 * @brief Node of a linked list
 */
typedef struct __linked_list_node_t {
    void *data; //!< Data stored in the node
    struct __linked_list_node_t *next; //!< Pointer to the next node
    struct __linked_list_node_t *prev; //!< Pointer to the previous node
} linked_list_node_t;

/**
 * @struct linked_list_t
 * @brief Linked list
 */
typedef struct {
    linked_list_node_t *head; //!< Pointer to the head of the linked list
    linked_list_node_t *tail; //!< Pointer to the tail of the linked list
    size_t size; //!< Size of the linked list
} linked_list_t;

/**
 * @fn linked_list_node_t *create_linked_list()
 * @brief create a new linked list
 * @return pointer to the linked list
 * @note the linked is allocated on the heap and must be freed by the user
 */
linked_list_t *create_linked_list();

/**
 * @fn char push_linked_list(linked_list_t *list, void *data)
 * @brief push data to the linked list
 * @param list pointer to the linked list
 * @param data pointer to the data to be pushed
 * @return TRUE if the data was pushed successfully, FALSE otherwise
 * @note the data is pushed to the end of the linked list
 */
char push_linked_list(linked_list_t *list, void *data);

/**
 * @fn void *pop_linked_list(linked_list_t *list)
 * @brief pop data from the linked list
 * @param list pointer to the linked list
 * @return pointer to the data that was popped
 * @note the data is popped from the end of the linked list
 */
void *pop_linked_list(linked_list_t *list);

/**
 * @fn void *get_linked_list(linked_list_t *list, size_t index)
 * @brief get data from the linked list
 * @param list pointer to the linked list
 * @param index index of the data to be retrieved
 * @return pointer to the data at the specified index
 * @note if the index is out of bounds, NULL is returned
 * @note the index is zero-based
 */
void *get_linked_list(linked_list_t *list, size_t index);

/**
 * @fn void *iter_linked_list(linked_list_t *list, linked_list_node_t **node)
 * @brief iterator for the linked list nodes
 * When the node is NULL, the iterator starts from the head of the list otherwise it starts from the node
 * and returns the next node in the list until the end of the list is reached
 * When the end of the list is reached, NULL is returned
 * @param list pointer to the linked list
 * @param node adress of the pointer to the node in the list (this will be updated to the next node automatically)
 * @return pointer to the next node in the list
 * @warning the node mustn't be modified by the user otherwise it may cause unexpected behavior
 * @note the node is updated to the next node in the list automatically and must be passed as an argument in the next call (same as the str_tok function)
 */
void *iter_linked_list(linked_list_t *list, linked_list_node_t **node);

/**
 * @fn void *iter_linked_list_reverse(linked_list_t *list, linked_list_node_t **node)
 * @brief iterator for the linked list nodes in reverse order 
 * @see iter_linked_list
 */
void *iter_linked_list_reverse(linked_list_t *list, linked_list_node_t **node);

/**
 * @fn void free_linked_list(linked_list_t *list)
 * @brief free the linked list
 * @param list pointer to the linked list
 * @param free_data_function function used to free the data stored in the linked list
 * @note if the free_data_function is NULL, the data inside the linked list is not freed
 * @warning the data inside the linked list is freed using the free_data_function otherwise it is not freed and may be lost (memory leak)
 * @note the linked list is freed and the pointer is set to NULL
 */
void free_linked_list(linked_list_t *list, fn_free_data_t free_data_function);




#endif // LINKED_LIST_H