#include "table.h"
#include <stdlib.h>

int main() {
    TableT *table = (TableT*)malloc(sizeof(TableT));
    initTable(table);
    if (loadTable(table, "table.in") != 0) {
        printf("Error loading table\n");
    }
    if (saveTable(table, "table.out") != 0) {
        printf("Error saving table\n");
    }
    freeTable(table);
    return 0;
}
