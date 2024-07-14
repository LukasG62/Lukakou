#include "linked_list.h"

/**
 * @fn void free_linked_list_node(linked_list_node_t *node, fn_free_data_t free_data_function)
 * @brief free the linked list node
 * @param node pointer to the linked list node
 * @param free_data_function function used to free the data stored in the linked list node
 */
void free_linked_list_node(linked_list_node_t *node, fn_free_data_t free_data_function) {
    if(free_data_function != NULL) {
        free_data_function(node->data);
    }
    free(node);
}

/**
 * @fn linked_list_node_t *create_linked_list()
 * @brief create a new linked list
 * @return pointer to the linked list
 * @note the linked is allocated on the heap and must be freed by the user
 */
linked_list_t *create_linked_list() {
    linked_list_t *list = (linked_list_t *)malloc(sizeof(linked_list_t));
    CHECK_ALLOC(list, "Failed to allocate memory for linked list");

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

/**
 * @fn char push_linked_list(linked_list_t *list, void *data)
 * @brief push data to the linked list
 * @param list pointer to the linked list
 * @param data pointer to the data to be pushed
 * @return TRUE if the data was pushed successfully, FALSE otherwise
 * @note the data is pushed to the end of the linked list
 */
char push_linked_list(linked_list_t *list, void *data) {
    linked_list_node_t *node = (linked_list_node_t *) malloc(sizeof(linked_list_node_t));
    CHECK_ALLOC(node, "Failed to allocate memory for linked list node");

    node->data = data;
    node->prev = NULL;
    node->next = NULL;

    // two case to verify (empty list/ not empty list)
    if(list->head == NULL) {
        list->head = node;
        list->tail = node;
    } else {
        node->prev = list->tail;
        list->tail->next = node;
        list->tail = node;
    }
    
    list->size++;
    return TRUE;
}

/**
 * @fn void *pop_linked_list(linked_list_t *list)
 * @brief pop data from the linked list
 * @param list pointer to the linked list
 * @return pointer to the data that was popped
 * @note the data is popped from the end of the linked list
 * @warning The node is freed but the data is not freed. The user is responsible for freeing the data. 
 */
void *pop_linked_list(linked_list_t *list) {
    if(list->head == NULL) return NULL;

    // two case to verify (one element in the list/ more than one element in the list)
    linked_list_node_t *node = list->tail;

    if(list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
    } else {
        list->tail = list->tail->prev;
        list->tail->next = NULL;
    }

    void *data = node->data;
    free_linked_list_node(node, NULL);

    list->size--;
    return data;
}

/**
 * @fn void *get_linked_list(linked_list_t *list, size_t index)
 * @brief get data from the linked list
 * @param list pointer to the linked list
 * @param index index of the data to be retrieved
 * @return pointer to the data at the specified index
 * @note if the index is out of bounds, NULL is returned
 * @note the index is zero-based
 */
void *get_linked_list(linked_list_t *list, size_t index) {
    if(index >= list->size) return NULL;

    linked_list_node_t *node;

    size_t mid = list->size / 2; // optimization to start from the head or the tail of the list
    DEBUG_PRINT("mid: %zu\n", mid);

    if(index > mid) {
        node = list->tail;
        for(size_t i = list->size - 1; i > index; i--) {
            node = node->prev;
        }
    } else {
        node = list->head;
        for(size_t i = 0; i < index; i++) {
            node = node->next;
        }
    }

    return node->data;
}

/**
 * @fn void free_linked_list(linked_list_t *list)
 * @brief free the linked list
 * @param list pointer to the linked list
 * @param free_data_function function used to free the data stored in the linked list
 * @note if the free_data_function is NULL, the data inside the linked list is not freed
 * @warning the data inside the linked list is freed using the free_data_function otherwise it is not freed and may be lost (memory leak)
 * @note the linked list is freed and the pointer is set to NULL
 */
void free_linked_list(linked_list_t *list, fn_free_data_t free_data_function) {
    linked_list_node_t *node = list->head;
    linked_list_node_t *next;

    while(node != NULL) {
        next = node->next;
        free_linked_list_node(node, free_data_function);
        node = next;
    }
    free(list);
}