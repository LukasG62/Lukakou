/**
 * @file test_linked_list.c
 * @brief Test for linked list implementation
 */

#include "linked_list.h"

typedef struct {
    char *name;
    int age;
} person_t;

/**
 * @fn void free_person(person_t *person)
 * @brief free the person
 * @param person pointer to the person
 */
void free_person(person_t *person) {
    free(person->name);
    free(person);
}

person_t *create_person(char *name, int age) {
    person_t *person = (person_t *)malloc(sizeof(person_t));
    CHECK_ALLOC(person, "Failed to allocate memory for person");
    person->name = (char *)malloc(strlen(name) + 1);
    CHECK_ALLOC(person->name, "Failed to allocate memory for person name");
    strcpy(person->name, name);
    person->age = age;
    return person;
}

int main(int argc, char *argv[]) {
    DEBUG_PRINT("Linked list test\n");

    // Create a linked list
    linked_list_t *list = create_linked_list();
    if(list == NULL) {
        ERROR("Failed to create linked list");
    }

    push_linked_list(list, (void *) 1);
    push_linked_list(list, (void *) 2);
    push_linked_list(list, (void *) 3);

    // Pop the data from the linked list
    int *data = pop_linked_list(list);
    if(data == NULL) {
        ERROR("Failed to pop data from linked list");
    }
    DEBUG_PRINT("Popped data: %d\n", (int) data);

    // Pop everything from the linked list
    while(list->head != NULL) {
        data = (int *)pop_linked_list(list);
        if(data == NULL) {
            ERROR("Failed to pop data from linked list");
        }
        DEBUG_PRINT("Popped data: %d\n", (int) data);
    }

    // Create a linked list of persons
    linked_list_t *person_list = create_linked_list();
    if(person_list == NULL) {
        ERROR("Failed to create linked list");
    }

    person_t *person1 = create_person("Lukas", 21);
    person_t *person2 = create_person("Viixyy", 12);
    person_t *person3 = create_person("Manu D.", 56);

    push_linked_list(person_list, (void *) person1);
    push_linked_list(person_list, (void *) person2);
    push_linked_list(person_list, (void *) person3);

    // Try to get the person at index 1
    person_t *person = (person_t *) get_linked_list(person_list, 1);
    if(person == NULL) {
        ERROR("Failed to get person from linked list");
    }
    if(strcmp(person->name, "Viixyy") != 0) {
        ERROR("Failed to get the correct person from linked list");
    }

    DEBUG_PRINT("Person at index 1: %s, %d\n", person->name, person->age);

    // Free the linked list
    free_linked_list(person_list, (fn_free_data_t) free_person);

    // Free the linked list
    free_linked_list(list, NULL);

    return EXIT_SUCCESS;
}