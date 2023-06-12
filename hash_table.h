#ifndef HASH_TABLE_HASH_TABLE_H
#define HASH_TABLE_HASH_TABLE_H

// Prime number
#define HASH_TABLE_M_SIZE 7

typedef struct ListElement {
    int key; // User inserted key
    int value; // User inserted value
    struct ListElement *next; // Next value in the concatenated list
} list_element;

/**
 * 0 - insert failed
 * 1 - insert success
 */
typedef int hash_table_put_result;

/**
 * Initializes the hash table with empty values.
 */
void hash_table_init();

/**
 * Retrieves the value of a specific key.
 * @param user_key Only values >= 0.
 * @return Returns -1 if the key is not found.
 */
int hash_table_get(int user_key);

/**
 * Saves the value in the hash table associated to the user_key.
 * @param user_key Value must be >= 0.
 * @param value Can be any integer number.
 * @return 0 if insert failed, 1 if insert success.
 */
hash_table_put_result hash_table_put(int user_key, int value);

/**
 * Calculates the h_index value of a specific key
 * @param user_key
 * @return
 */
int h_index(int user_key);

/**
 * Prints the entire hash table to stdout.
 */
void hash_table_print();

/**
 * Enables some debug output in order to understand how it works.
 * The output its printed to stdout.
 */
void hash_table_enable_debug();

#endif //HASH_TABLE_HASH_TABLE_H
