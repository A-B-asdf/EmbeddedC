#include "table.h"
#include <stdlib.h>
#include <stdio.h>

int myCondition(struct Record *record) {
    return record->group == 4;
}

void func(struct Record *record) {
    printf("WOW\n");
}

int main() {
    TableT *table = (TableT*)malloc(sizeof(TableT));
    initTable(table);  // инициализация таблицы
    if (loadTable(table, "table.in") != 0) {  // загрузка из файла
        printf("Error loading table\n");
    }
    inputRecord(table);  // ввод записи таблицы с клавиатуры
    if (saveTable(table, "table.out") != 0) {  // сохранение в файл
        printf("Error saving table\n");
    }
    printTable(table);  // просмотр таблицы
    printf("\n");
    sortTable(table, 0);  // сортировка по первому полю
    printTable(table);  // просмотр таблицы
    printf("\n");
    int index = searchRecord(table, 0, (void*) "Ivanov");  // поиск Иванова
    printf("Index of \"Ivanov\": %d\n", index);
    int id = 4;
    index = searchRecord(table, 1, (void*) &id);  // поиск по ID
    printf("Index of student with ID %d: %d\n", id, index);
    int group = 21202;
    index = searchRecord(table, 3, (void*) &group);  // поиск по номеру группы
    printf("Index of student with group %d: %d\n", group, index);
    index = searchNearestRecord(table, 0, (void*) "Petrog");  // поиск с наиболее близким значением
    printf("Index of student with surname nearest to \"Petrog\": %d\n", index);
    editRecord(table, 1, table->records + 0);  // редактирование записи
    printTable(table);  // просмотр таблицы
    printf("\n");
    int ammount = countByCondition(table, myCondition);  // подсчет по условию
    printf("Ammount of students with group 4: %d\n", ammount);
    deleteRecord(table, 1);
    printTable(table);
    printf("\n");
    processRecords(table, func);  // обработка всех записей
    freeTable(table);
    return 0;
}
