#include "table.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    TableT *table = (TableT*)malloc(sizeof(TableT));
    initTable(table);
    if (loadTable(table, "table.in") != 0) {
        printf("Error loading table\n");
    }
    inputRecord(table);
    if (saveTable(table, "table.out") != 0) {
        printf("Error saving table\n");
    }
    printTable(table);
    printf("\n");
    sortTable(table, 0);
    printTable(table);
    printf("\n");
    int index = searchRecord(table, 0, (void*) "Ivanov");
    printf("Index of \"Ivanov\": %d\n", index);
    int id = 4;
    index = searchRecord(table, 1, (void*) &id);
    printf("Index of student with ID %d: %d\n", id, index);
    int group = 21202;
    index = searchRecord(table, 3, (void*) &group);
    printf("Index of student with group %d: %d\n", group, index);
    index = searchNearestRecord(table, 0, (void*) "Petrog");
    printf("Index of student with surname nearest to \"Petrog\": %d\n", index);
    editRecord(table, 1, table->records + 0);
    printTable(table);
    printf("\n");
    deleteRecord(table, 1);
    printTable(table);
    printf("\n");
    freeTable(table);
    return 0;
}
