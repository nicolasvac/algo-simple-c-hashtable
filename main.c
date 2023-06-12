#include <stdio.h>

#include "hash_table.h"

int main() {
    // Enable the verbose debug output
    hash_table_enable_debug();

    // Initialize the hash table to all empty values
    hash_table_init();

    // Add some random data
    hash_table_put(2, 45);
    hash_table_put(4, 29);
    hash_table_put(6, 34);
    hash_table_put(7, 23);
    hash_table_put(8, 52);
    hash_table_put(9, 5);

    // Print the entire table to stdout
    hash_table_print();

    // Get a specific value from the hash table
    printf("Value obtained from hash value: %d\n", hash_table_get(9));
}
