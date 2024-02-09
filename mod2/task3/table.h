#include <stdio.h>

#define SURNAME_LEN 50
#define FACULTY_LEN 50
#define INITIAL_CAPACITY 10

struct Record {
    char surname[SURNAME_LEN];
    long int studentID;
    char faculty[FACULTY_LEN];
    int group;
};

struct Table {
    struct Record* records;
    size_t size;
    size_t capacity;
};

typedef struct Table TableT;

int initTable(TableT *table);
int addRecord(TableT *table, struct Record *record);
int inputRecord(TableT *table); // ввод записи таблицы с клавиатуры
int loadTable(TableT *table, char* filename); // загрузка таблицы из текстового файла
int saveTable(TableT *table, char* filename); // сохранение таблицы в текстовый файл
void printTable(TableT *table); // просмотр таблицы
void sortTable(TableT *table, int field); // сортировка таблицы по возрастанию заданного поля
struct Record* searchRecord(TableT *table, int field, int value); // поиск записи с заданным значением поля
void deleteRecord(TableT *table, int index); // удаление записи
void editRecord(TableT *table, int index, struct Record* record); // изменение (редактирование) записи
int countByGroupNumber(TableT *table, int group_number); // подсчет записей по номеру группы
void processRecords(TableT *table, void (*processFunc)(struct Record*)); // обработка записей заданной фукнцией
void freeTable(TableT *table);
