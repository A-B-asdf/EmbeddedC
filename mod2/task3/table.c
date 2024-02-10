#include "table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdlib.h>

int initTable(TableT *table) {
    table->size = 0;
    table->capacity = INITIAL_CAPACITY;
    table->records = (struct Record*)malloc(INITIAL_CAPACITY * sizeof(struct Record));
    if (table->records == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        return 1;
    }
    return 0;
}

void freeTable(TableT *table) {
    free(table->records);
    table->size = 0;
    table->capacity = 0;
}

int reallocTable(TableT *table) {
    void *res = realloc(
        table->records, table->capacity * 2 * sizeof(struct Record));
    if (res == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        return 1;
    }
    table->capacity *= 2;
    return 0;
}

int addRecord(TableT *table, struct Record *record) {
    if (table->size >= table->capacity) {
        if (reallocTable(table) != 0) {
            return 1;
        }
    }
    memcpy(&(table->records[table->size]), record, sizeof(struct Record));
    (table->size)++;

    return 0;
}

int loadTable(TableT *table, char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }
    if (table->records == NULL) {
        int e = initTable(table);
        if (e == 1) {
            fclose(file);
            return 1;
        }
    }
    struct Record new_rec;
    
    while (fscanf(
        file, "%[^;];%ld;%[^;];%d\n", 
            new_rec.surname, &(new_rec.studentID), new_rec.faculty, &(new_rec.group)) == 4) {
        if (addRecord(table, &new_rec) != 0) {
            return 1;
        }
    }
    return 0;
}

int saveTable(TableT *table, char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }
    for (int i = 0; i < table->size; ++i) {
        fprintf(file, "%s;%ld;%s;%d\n", 
            table->records[i].surname, 
            table->records[i].studentID, 
            table->records[i].faculty, 
            table->records[i].group);
    }
    return 0;
}

int inputRecord(TableT *table) {
    printf("Enter a record in the following format: Surname;Student ID;Faculty;GroupNumber\n");
    struct Record new_rec;
    char input[100];
    fgets(input, sizeof(input), stdin);
    while (sscanf(input, "%[^;];%ld;%[^;];%d", 
            new_rec.surname, &(new_rec.studentID), new_rec.faculty, &(new_rec.group)) != 4) {
        printf("Input error\n");
        fgets(input, sizeof(input), stdin);
    }
    if (addRecord(table, &new_rec) != 0) {
        return 1;
    }
    return 0;
}

void printTable(TableT *table) {
    for (int i = 0; i < table->size; ++i) {
        printf("%s;%ld;%s;%d\n", 
            table->records[i].surname, 
            table->records[i].studentID, 
            table->records[i].faculty, 
            table->records[i].group);
    }
}

void deleteRecord(TableT *table, int index) {
    if (index >= table->size) {
        fprintf(stderr, "Index out of range\n");
        return;
    }
    for (int i = index; i < table->size; ++i) {
        memcpy(table->records + i - 1, table->records + i, sizeof(struct Record));
    }
    table->size--;
}

void editRecord(TableT *table, int index, struct Record* record) {
    if (index >= table->size) {
        fprintf(stderr, "Index out of range\n");
        return;
    }
    memcpy(&(table->records[index]), record, sizeof(struct Record));
}

int compareSurname(const void *a, const void *b) {
    const struct Record *record1 = (const struct Record *)a;
    const struct Record *record2 = (const struct Record *)b;
    return strcmp(record1->surname, record2->surname);
}

int compareID(const void *a, const void *b) {
    const struct Record *record1 = (const struct Record *)a;
    const struct Record *record2 = (const struct Record *)b;
    return record1->studentID - record2->studentID;
}

int compareFaculty(const void *a, const void *b) {
    const struct Record *record1 = (const struct Record *)a;
    const struct Record *record2 = (const struct Record *)b;
    return strcmp(record1->faculty, record2->faculty);
}

int compareGroup(const void *a, const void *b) {
    const struct Record *record1 = (const struct Record *)a;
    const struct Record *record2 = (const struct Record *)b;
    return record1->group - record2->group;
}

int (*comparators[4])(const void *a, const void *b) = {
    &compareSurname, 
    &compareID, 
    &compareFaculty, 
    &compareGroup
};

void sortTable(TableT *table, int field) {
    qsort(table->records, table->size, sizeof(struct Record), comparators[field]);
}

void *num2Field(const struct Record *record, int field) {
    switch (field) {
    case 0:
        return (void *)record->surname;
    case 1:
        return (void *)&(record->studentID);
    case 2:
        return (void *)record->faculty;
    case 3:
        return (void *)&(record->group);
    default:
        return NULL;
    }
}

int compareWithValue(const struct Record *record, const void *value, int field) {
    switch (field) {
    case 0:
        return strcmp(record->surname, (char *)value);
    case 1:
        return record->studentID - *((int *)value);
    case 2:
        return strcmp(record->faculty, (char *)value);
    case 3:
        return record->group - *((int *)value);
    default:
        return 0;
    }
}

int searchRecord(TableT *table, int field, void *value) {
    for (int index = 0; index < table->size; ++index) {
        if (compareWithValue(table->records + index, value, field) == 0) {
            return index;
        }
    }
    return -1;
}

int searchNearestRecord(TableT *table, int field, void *value) {
    TableT *table_copy = (TableT*)malloc(sizeof(TableT));
    table_copy->records = (struct Record*)malloc(table->size * sizeof(struct Record));
    memcpy(table_copy->records, table->records, table->size * sizeof(struct Record));
    table_copy->size = table->size;
    table_copy->capacity = table->capacity;
    
    sortTable(table_copy, field);

    int l = 0, r = table_copy->size;
    while (l < r) {
        int mid = (l + r) / 2;
        if(compareWithValue(table_copy->records + l, value, field) <= 0) {
            l = mid;
        } else {
            r = mid;
        }
    }
    int index = searchRecord(table, field, num2Field(table_copy->records + l, field));
    freeTable(table_copy);
    return index;
}

int countByCondition(TableT *table, int (*condition)(struct Record*)) {
    int counter = 0;
    for (int i = 0; i < table->size; ++i) {
        if (condition(table->records + i)) {
            counter++;
        }
    }
    return counter;
}

void processRecords(TableT *table, void (*processFunc)(struct Record*)) {
    for (int i = 0; i < table->size; ++i) {
        processFunc(table->records + i);
    }
}
