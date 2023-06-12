#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

bool debug_enabled = false;

#include "hash_table.h"

list_element data[HASH_TABLE_M_SIZE];

void hash_table_init() {
    if (debug_enabled) {
        printf("\n--------------------\n");

        printf("Hash table init");
    }

    // Init all elements of the array to an empty element
    list_element init_element = {
            .key = -1,
            .next = NULL,
    };

    for (int i = 0; i < HASH_TABLE_M_SIZE; ++i) {
        data[i] = init_element;
    }
}

int hash_table_get(int user_key) {
    // Do not accept keys lower than 0
    if (user_key < 0) {
        return -1;
    }

    // Calculate the h function value of the key
    int data_index = h_index(user_key);

    if (debug_enabled) {
        printf("\n--------------------\n");

        printf("hash_table_get: h_index value %d with user_key %d\n", data_index, user_key);
    }

    list_element current_element = data[data_index];

    if (debug_enabled) {
        printf("hash_table_get: first element has key %d\n", current_element.key);
    }

    // Check if the first value is already valid
    if (current_element.key == user_key) {
        if (debug_enabled) {
            printf("hash_table_get: first element is valid\n");
        }

        return current_element.value;
    } else {
        // Iterate the concatenated list starting from the first element
        while (current_element.next != NULL) {
            // Get the next element
            current_element = *current_element.next;

            if (debug_enabled) {
                printf(
                        "hash_table_get: iterating element with key %d and h_index %d\n",
                        current_element.key,
                        data_index
                );
            }

            if (current_element.key == user_key) {
                if (debug_enabled) {
                    printf("hash_table_get: element found\n");
                }

                return current_element.value;
            }
        }
    }

    if (debug_enabled) {
        printf("hash_table_get: element not found\n");
    }

    return -1;
}

hash_table_put_result hash_table_put(int user_key, int value) {
    // Do not accept keys lower than 0
    if (user_key < 0) {
        return 0;
    }

    // Calculate the h function value of the key
    int data_index = h_index(user_key);

    if (debug_enabled) {
        printf("\n--------------------\n");

        printf("hash_table_put: h_index value %d with user_key %d\n", data_index, user_key);
    }

    // Get the reference to the first element in order to allow the creation of new elements
    list_element *current_element = &data[data_index];

    if (debug_enabled) {
        printf("hash_table_put: first element has key %d\n", current_element->key);
    }

    // If the first element corresponds, just update the value
    if (current_element->key == user_key) {
        if (debug_enabled) {
            printf("hash_table_put: first element is valid. updating it \n");
        }

        current_element->value = value;

        return 1;
    } else {
        // Iterate the concatenated list starting from the first element
        while (current_element->next != NULL) {
            // Get the next element
            current_element = current_element->next;

            if (debug_enabled) {
                printf(
                        "hash_table_put: iterating element with key %d and h_index %d\n",
                        current_element->key,
                        data_index
                );
            }

            // If the value is the one we are searching, update the value
            if (current_element->key == user_key) {
                if (debug_enabled) {
                    printf("hash_table_put: element found - updating the value\n");
                }

                current_element->value = value;
                return 1;
            }
        }

        // If we reach here, it means the element does not exist, so we need to create a new one.

        if (debug_enabled) {
            printf("hash_table_put: element not found - creating a new one \n");
        }

        // Create the new element
        list_element *new_element = (list_element *) malloc(sizeof(list_element));
        new_element->key = user_key;
        new_element->value = value;
        new_element->next = NULL;

        // Put it at the end of the concatenated list
        current_element->next = new_element;

        if (debug_enabled) {
            printf(
                    "hash_table_put: new element added with h_index %d and user_key %d\n",
                    data_index,
                    new_element->key
            );
        }

        return 1;
    }
}

int h_index(int user_key) {
    // Division method. Keep it simple.
    return user_key % HASH_TABLE_M_SIZE;
}

void hash_table_print() {
    for (int i = 0; i < HASH_TABLE_M_SIZE; ++i) {
        printf("H_INDEX: %d", i);

        list_element element = data[i];

        printf("| KEY: %d - VALUE: %d |", element.key, element.value);

        while (element.next != NULL) {
            element = *element.next;

            printf("| KEY: %d - VALUE: %d |", element.key, element.value);
        }

        printf("\n");
    }
}

void hash_table_enable_debug() {
    debug_enabled = true;
}