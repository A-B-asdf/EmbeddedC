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
    editRecord(table, 1, table->records + 0);
    printTable(table);
    printf("\n");
    deleteRecord(table, 1);
    printTable(table);
    printf("\n");
    freeTable(table);
    return 0;
}
