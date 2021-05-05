#ifndef LAB4A_FUNCTIONS_H
#define LAB4A_FUNCTIONS_H

#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct Item {
    float info1;
    float info2;
    char *info3;
    struct Item *next;
} Info;

typedef struct Node {
    char *key;
    Info *info;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct Tree {
    FILE *fd_keys;
    FILE *fd_data;
    Node *root;
} Tree;


/**************************************************************************************************************************************************************/
/*Прототипы функций*/
int getFloat(float *);
int getInt(int *);
char *get_str();
char *fget_str(FILE *file);
void clean_stdin();
int dialog(const char *msgs[], int);


/* Функции для работы с деревом */
int insert(Node **, char *, Info*);                    // Деревянная функция вставки нового узла
Node *find(Node *, char *);                            // Деревянный поиск узла дерева
Node *findmin(Node *);                                 // Нахождение мнимального узла в поддереве
Node *delete(Node *, char *);                          // Деревянная функция удаления узла дерева
void Postorder(Node *, int);                                // Прямой обход дерева (в прямом порядке следования ключей)
void delTree(Node **);                                 // Удаление всего дерева путем рекурсивного удаления главного узла


// Массив диагностических сообщений об ошибках
const char *errmsgs[] = {"Ok", "Найден дубликат ключа", "Дерево пусто", "Ключ не найден"};


// Альтерантивы меню для организации диалога
const char *msgs[] = {"0. Выйти", "1. Добавить новый элемент", "2. Найти информацию по ключу",
                      "3. Найти минимальный ключ", "4. Удалить элемент",
                      "5. Вывести таблицу в порядке следования ключей",
                      "6. Таймирование дерева"};


// Кол-во альтернатив (Для вывода в for)
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

/* Диалоговые функции */
int D_Add(Tree *);                    // Диалоговая функция включения в дерево нового элемента
int D_Find(Tree *);                   // Диалоговая функция поиска узла дерева по условию лабы
int D_Find_Min_Key(Tree *);           // Диалоговая функция поиска минимального элемента в дереве
int D_Delete(Tree *);                 // Диалоговая функция удаления узла дерева по ключу
int D_Show(Tree *);                   // Диалоговая функция вывода всего дерева в нужном порядке следования ключей
int D_Timing(Tree *);                 // Диалоговая функция таймирования дерева

// Массив указателей на функции - для реализации выбора функции; порядок перечисления функций в списке инициализации должен соответсвовать порядку указания альтернатив в списке альернатив
int (*fptr[])(Tree *) = {NULL, D_Add, D_Find, D_Find_Min_Key, D_Delete, D_Show, D_Timing };

/* Функции для работы с файлом данных */

int D_Load(Tree *, char **);                                    // Диалоговая функция загрузки дерева из файла
int load(Tree *, char *);                                       // Функция загрузки существующих файлов (если таковые имеются)
int create(char *, FILE **, FILE **);                           // Создание обоих файлов для заполнения
int save(Node *, FILE *, FILE*);                          // Рекурсивное сохранение всех ключей и сопровождающих их данных в файлы

#endif //LAB4A_FUNCTIONS_H
