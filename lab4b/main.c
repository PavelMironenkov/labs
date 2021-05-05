#include "functions.h"


void clean_stdin() {
    int c;
    do
        c = getchar();                 // Присваивание c символа из входного потока
    while (c != '\n' && c != EOF);
}


int getInt(int *a) {
    int n;
    do {
        n = scanf("%d", a);
        if (n < 0)      // Обнаружен конец файла
            return 0;
        if (n == 0) { // Обнаружен некорректный символ - ошибка
            printf("%s\n", "Ошибка! Повторите ввод:");
            clean_stdin();
        }
    } while (n == 0);
    //clean_stdin();
    return 1;
};


char *get_str() {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = (int) strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }

    return res;
}

/* Выбор номера альтернативы (Функция для выбора номера альтернативы. Возвращает правильный номер альтернативы. В строке может быть указан только номер альтернативы; если в строке
после номера альтернативы есть что-то еще, весь остаток строки удаляется из буфера) */
int dialog(const char *msgs[], int N) {
    char *errmsg = "";
    int rc, i, n;
    do {
        puts(errmsg);
        errmsg = "Ошибка! Повторите ввод:!";
        for (i = 0; i < N; ++i)       // вывод списка альтернатив
            puts(msgs[i]);
        printf("Выберите: --> ");
        n = getInt(&rc);              // Ввод номера альтернативы
        if (n == 0)                   // Конец файла - конец работы
            rc = 0;
    } while (rc < 0 || rc >= N);
    return rc;
}


/* Деревянная функция вставки нового узла. */
int insert(Node **proot, Item *insert_info) {
    int i = -1;
    while (*proot) {
        i++;
        if ((*proot)->item->key[0] == insert_info->key[0] && (*proot)->item->key[1] == insert_info->key[1]) {
            insert_info->next = (*proot)->item;
            (*proot)->item = insert_info;
            //free(k);
            return 0;
        } else
            proot = insert_info->key[i % 2] < (*proot)->item->key[i % 2] ? &(*proot)->left
                                                                         : &(*proot)->right;   // Если k < (*proot)->key, то двигаемся влево; либо вправо
    }
        (*proot) = (Node *) malloc(sizeof(Node));
        (*proot)->left = (*proot)->right = NULL;
        (*proot)->item = insert_info;
        (*proot)->item->next = NULL;
        return 0;
    }
}


/* Диалоговая функция включения в дерево нового узла. Требует ввести ключ и информацию, при этом эта информация должна быть введена в новой строке, в ответ на приглашение.
Если ключ задан неправильно, вся строка игнорируется.*/
int D_Add(Tree *ptree) {
    int rc, proverka, k[Numbers];
    char *info = NULL;
    printf("Введите ключи k1 и k2: --> ");
    proverka = getInt(&k[0]);
    if (proverka != 1)
        return 0;
    proverka = getInt(&k[1]);
    if (proverka != 1)
        return 0;
    printf("Введите информацию(string): --> ");
    info = get_str();
    if (info == NULL)
        return 0;
    Item *insert_info = malloc(sizeof(Item));
    insert_info->key[0] = k[0];
    insert_info->key[1] = k[1];
    insert_info->info = calloc(strlen(info), sizeof(char));
    insert_info->info = info;
    rc = insert(&ptree->root, insert_info);
    return 1;
}

/* Диалоговая функция поиска узла дерева по ключу. */
int D_Find(Tree *ptree) {
    Line;
    int proverka;
    int k[2];
    printf("Введите ключи k1 и k2: --> ");
    proverka = getInt(&k[0]);
    if (proverka != 1)
        return 0;
    proverka = getInt(&k[1]);
    if (proverka != 1)
        return 0;
    Node *cur = NULL;
    if (!(cur = find(ptree->root, k[0], k[1])))
        printf("%s\n", errmsgs[3]);
    else {
        Item *ptr = cur->item;
        printf("%d %d: ", k[0], k[1]);
        while (ptr) {
            printf("%s;\t", ptr->info);
            ptr = ptr->next;
        }
        printf("\n");
    }
    free(k);
    Line;
    return 1;
}


/* Диалоговая функция поиска узла дерева по условию лабы. */
int D_Find_Min_Key(Tree *ptree) {
    Line;
    Node *min = findmin(ptree->root);
    if (!min)
        printf("%s\n", errmsgs[2]);
    else {
        printf("%s: ", errmsgs[0]);
        Info *ptr = min->info;
        printf("%s: ", min->key);
        while (ptr) {
            printf("%f %f %s;\t", ptr->info1, ptr->info2, ptr->info3);
            ptr = ptr->next;
        }
        printf("\n");
    }
    Line;
    return 1;
}


/* Диалоговая функция удаления узла дерева по значению ключа. */
int D_Delete(Tree *ptree) {
    Line;
    printf("Введите ключ: --> ");
    char *k = NULL;
    getchar();
    k = get_str();
    if (k == NULL)
        return 0;
    ptree->root = delete(ptree->root, k);
    free(k);
    Line;
    return 1;
}


/* Диалоговая функцяи вывода всего дерева в правильном порядке следования ключей. (Центрированный обход: Левое-Корень-Правое) */
int D_Show(Tree *ptree) {
    Line;
    printf("Прямой обход:\n");
    Line;
    if (!ptree->root)
        printf("%s\n", errmsgs[2]);
    else
        Postorder(ptree->root);
    Line;
    return 1;
}


/* Функция загрузки существующего файла (если таковой имеется). */
int load(Tree *ptree, char *fname) {
    /* Открываем существующие файлы на чтение и запись; в случае не нахождения одного из нужных файлов, выдается сообщение об ошибке */
    char *fname_keys = (char *) malloc(strlen(fname) + 5);
    fname_keys = strcpy(fname_keys, fname);
    fname_keys = strcat(fname_keys, ".bin");
    ptree->fd_keys = fopen(fname_keys, "r");
    if (ptree->fd_keys == NULL) {
        free(fname_keys);
        return 0;
    }
    char *fname_data = (char *) malloc(strlen(fname) + 10);
    fname_data = strcpy(fname_data, fname);
    fname_data = strcat(fname_data, "_data.bin");
    ptree->fd_data = fopen(fname_data, "r");
    if (ptree->fd_data == NULL) {
        free(fname_data);
        return 0;
    }
    printf("Файлы успешно найдены и загружены.\n");
    Line;
    // Считывваем данные из файла, пока программа не считает EOF в k
    char *k = NULL;
    k = fget_str(ptree->fd_keys);
    while (k != NULL) {
        Info *info = (Info *) malloc(sizeof(Info));

        fscanf(ptree->fd_data, "%f %f ", &info->info1, &info->info2);
        info->info3 = fget_str(ptree->fd_data);
        info->next = NULL;
        insert(&ptree->root, k, info);

        k = fget_str(ptree->fd_keys);
    }
    //free(k);
    free(fname_data);
    free(fname_keys);
    fclose(ptree->fd_data);
    fclose(ptree->fd_keys);
    return 1;
}


/* Создание и открытие обоих файлов для записи.*/
int create(char *fname, FILE **fd_keys, FILE **fd_data) {
    printf("Файл (или файлы) с указанным именем не найден/ы. Будут созданы новые файлы.\n");
    Line;
    // fname_keys и fname_data - два дескриптора на файлы
    char *fname_keys = (char *) malloc(strlen(fname) + 5);
    fname_keys = strcpy(fname_keys, fname);
    fname_keys = strcat(fname_keys, ".bin");
    (*fd_keys) = fopen(fname_keys, "w+b");
    free(fname_keys);
    char *fname_data = (char *) malloc(strlen(fname) + 10);
    fname_data = strcpy(fname_data, fname);
    fname_data = strcat(fname_data, "_data.bin");
    (*fd_data) = fopen(fname_data, "w+b");
    free(fname_data);
    return 1;
}


int main() {
    setlocale(LC_ALL, "Russian");
    Tree tree = {NULL, NULL, NULL};
    int rc;
    char *fname = NULL;
    if (D_Load(&tree, &fname) == 0)
        return 1;
    while (rc = dialog(msgs, NMsgs))
        if (!fptr[rc](&tree))
            break;
    fname = (char *) realloc(fname, strlen(fname) + 5);
    fname = strcat(fname, ".bin");
    fopen(fname, "w+b");
/*Открытие файла, по которому в последсвие будет построен граф*/
    char *name = (char *) malloc(strlen(fname) + 5);
    strcpy(name, fname);
    strcat(name, ".dot");
    FILE *fd_dot = fopen(name, "w+");
    fprintf(fd_dot, "digraph G {");
    save_to_dot(tree.root, fd_dot);
    fprintf(fd_dot, "}");
    free(name);
    fclose(fd_dot);
    fd_dot = NULL;
    save(tree.root, tree.fd_keys, tree.fd_data);
    delTree(&tree.root);
    printf("Таблица сохранена.\n");
    fclose(tree.fd_keys);
    fclose(tree.fd_data);
    tree.fd_keys = NULL;
    tree.fd_data = NULL;
    free(fname);
    return 0;
}
