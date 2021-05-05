#define Line printf("------------------------------------------------------------------------------------------------------------\n");
#include"functions.h"

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

int getFloat(float *a) {
    int n;
    do {
        n = scanf("%f", a);
        if (n < 0)      // Обнаружен конец файла
            return 0;
        if (n == 0) { // Обнаружен некорректный символ - ошибка
            printf("%s\n", "Ошибка! Повторите ввод:");
            clean_stdin();
        }
    } while (n == 0);
    return 1;
}

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
            int chunk_len = (int)strlen(buf);
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

char *fget_str(FILE *file) {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n;
    do {
        n = fscanf(file, "%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = (int)strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            fscanf(file, "%*c");
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

/**************************************************************************************************************************************************************/
/* Диалоговые функции */


/* Диалоговая функция включения в дерево нового узла. Требует ввести ключ и информацию, при этом эта информация должна быть введена в новой строке, в ответ на приглашение.
Если ключ задан неправильно, вся строка игнорируется.*/
int D_Add(Tree *ptree) {
    int rc, proverka;
    float info1, info2;
    char *info3 = NULL;
    Info *insert_info = malloc(sizeof(Info));
    printf("Введите ключ: --> ");
    char *k = NULL;
    getchar();
    k = get_str();
    if (k == NULL)
        return 0;
    printf("Введите информацию(float float string): --> ");
    proverka = getFloat(&info1);
    if (proverka != 1)
        return 0;
    proverka = getFloat(&info2);
    if (proverka != 1)
        return 0;
    info3 = get_str();
    if (info3 == NULL)
        return 0;
    insert_info->info1 = info1;
    insert_info->info2 = info2;
    insert_info->info3 = info3;
    //insert_info->next=NULL;
    rc = insert(&ptree->root, k, insert_info);
    return 1;
}


/* Диалоговая функция поиска узла дерева по ключу. */
int D_Find(Tree *ptree) {
    Line;
    printf("Введите ключ: --> ");
    char *k = NULL;
    getchar();
    k = get_str();
    if (k == NULL)
        return 0;
    Node *cur = NULL;
    if (!(cur = find(ptree->root, k)))
        printf("%s\n", errmsgs[3]);
    else {
        Info *ptr = cur->info;
        printf("%s: ", cur->key);
        while (ptr) {
            printf("%f %f %s;\t", ptr->info1, ptr->info2, ptr->info3);
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
        printf("%s: ",errmsgs[0]);
        Info *ptr=min->info;
        printf("%s: ",min->key);
        while(ptr) {
            printf("%f %f %s;\t", ptr->info1, ptr->info2, ptr->info3);
            ptr=ptr->next;
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
   /* printf("Прямой обход:\n");
    Line;*/
    if (!ptree->root)
        printf("%s\n", errmsgs[2]);
    else {
        int h=0;
        Postorder(ptree->root, h);
        Line;
    }
    return 1;
}

/*Рандомная генерация флотового значения*/
float random_float(float min, float max)
{
    return (float)(rand())/RAND_MAX*(max - min) + min;
}


/*Удаляем узел*/
void free_Node(Node *root){
    if(root) {
        free(root->key);
        free(root->info->info3);
        free(root->info);
        free(root);
    }
}


/* Диалоговая функция таймирования дерева. (Аргумент функции не нужен, т.к. создается новое дерево)*/
int D_Timing(Tree *p) {
    srand(time(NULL));
    int length1=(rand())%100, length2=(rand())%101;
    char *key=(char*)calloc(length1,sizeof(char));
    for(int i=0;i<length1-1;++i){
        key[i]=(char)(rand()%57+65);
    }
    key[length1-1]='\0';
   clock_t t=clock();
   find(p->root,key);
   t=clock()-t;
   double time = (double) t / CLOCKS_PER_SEC;
    printf("\nTime of find: %.8lf seconds\n", time);


    Info *info=malloc(sizeof(Info));
    info->info1=random_float(-1000.01,1000.1);
    info->info2=random_float(-1001.1, 1001.1);
    info->info3= calloc(length2, sizeof(char));
    for(int i=0;i<length2-1;++i) {
        (info->info3)[i] =(char)(rand()%57+65);
    }
    (info->info3)[length2-1]='\0';

    t=clock();
    insert(&p->root,key,info);
    t=clock()-t;

    time = (double) t / CLOCKS_PER_SEC;
    printf("Time of insert: %.8lf seconds\n", time);

    Node *ptr=find(p->root,key);
    if(ptr->info->next) {
        Info *proot=ptr->info;
        ptr->info =proot->next;
        free(proot->info3);
        free(proot);
    }else delete(p->root,key);

    return 1;
}
/**************************************************************************************************************************************************************/
/* Функции для работы с деревом */



/* Прямой обход дерева (в прямом порядке следования ключей)*/
void Postorder(Node *root,int h) {
    if (root != NULL) {
        Postorder(root->right, h+1);
            //Info* ptr=root->info;
            //printf("%s", root->key);
            for(int i=0;i<h;++i){
                printf("\t");
            }
            printf("%s\n", root->key);
            /*while (ptr != NULL){
                printf("%f %f %s;\t", ptr->info1, ptr->info2, ptr->info3);
                ptr = ptr->next;
            }*/
            //printf("\n");
        Postorder(root->left, h+1);
        //Postorder(root->right, h+1);
    }
}



/* Деревянная функция вставки нового узла. */
int insert(Node **proot, char *k, Info *info) {
    while (*proot) {
        if (strcmp((*proot)->key, k) == 0) {
            info->next=(*proot)->info;
            (*proot)->info=info;
            free(k);
            return 0;
        }
        else
            proot = strcmp(k, (*proot)->key) < 0 ? &(*proot)->left: &(*proot)->right;   // Если k < (*proot)->key, то двигаемся влево; либо вправо
    }
    (*proot) = (Node *) malloc(sizeof(Node));
    (*proot)->left = (*proot)->right = NULL;
    (*proot)->key = k;
    (*proot)->info=info;
    (*proot)->info->next=NULL;
    return 0;
}


/* Деревянный поиск узла для таймирования. */
Node *find(Node *root, char *k) {
    while (root) {
        if (strcmp(root->key, k) == 0)
            return root;
        else root = strcmp(k, root->key) < 0 ? root->left: root->right;
            /*(strcmp(k, root->key) < 0)
            return find(root->left, k);
        else
            return find(root->right, k);*/
    }
    return root;
}


/* Нахождение минимального узла в поддереве */
Node *findmin(Node *root) {
    while (root->left)
        root = root->left;
    return root;
}


/* Деревянная рекурсивная функция удаления узла дерева (Т.к. нет информации о родителе, юзаем именно ее).
Смысл рекурсивного удаления в "пересборке" дерева, во время которого мы пропускаем добавление удаляемого узла. */
Node *delete(Node *root, char *k) {
    /* Когда мы доходим до конца дерева (попадаем в узел), заканчиваем пересборку и возвращаем NULL. */
    if (!root) {
        printf("Ключ не найден. Попробуйте еще раз.\n");
        return NULL;
    }
    /* Теперь продолжаем сборку дерева до того момента, пока не найдем удаляемый узел. */
    if (strcmp(root->key, k) > 0) {
        root->left = delete(root->left, k);
        return root;
    } else if (strcmp(root->key, k) < 0) {
        root->right = delete(root->right, k);
        return root;
    }
        /* При нахождении нужного узла (root->key == k). */
    else {
        if (!root->info->next) {
            /* Если удаляемый узел имеет обоих потомков, заменяем удаляемый узел на минимум в правом поддереве и удаляем уже тот, на который заменяли (минимум левого поддерева). */
            if (root->left && root->right) {
                Node *localMin = findmin(root->right);
                root->key = malloc(strlen(localMin->key) * sizeof(char));
                root->key = localMin->key;
                root->right = delete(root->right, localMin->key);
                return root;
            }
                /* Если удаляемый узел имеет только одого потомка (левого, либо правого), то пропускаем его (и не забываем удалить). */
            else if (root->left) {
                Node *tmp = root->left;
                free_Node(root);
                printf("Ключ успешно удален из дерева.\n");
                return tmp;
            } else if (root->right) {
                Node *tmp = root->right;
                free_Node(root);
                printf("Ключ успешно удален из дерева.\n");
                return tmp;
            }
                /* Либо 3 вариант, удаляем лист, поэтому ничего, кроме удаления, делать не надо (Разве что возвращаем, естественно, NULL, */
            else {
                free_Node(root);
                printf("Ключ успешно удален из дерева.\n");
                return NULL;
            }
        }else{
            Info *ptr = root->info->next;
            Info *ptr_prev = root->info;
            while(ptr->next) {
                ptr_prev = ptr;
                ptr = ptr->next;
            }
            ptr_prev->next=NULL;
            free(ptr->info3);
            free(ptr);
            //printf("Удален наиболее старый элемент из списка с данным ключом.\n");
            return root;
        }
    }
}


/* Рекурсивная функция удаления поддерева из оперативной памяти. */
void delTree(Node **proot) {
    if (*proot) {
        delTree(&(*proot)->left);
        delTree(&(*proot)->right);
        while((*proot)->info->next)
            delete(*proot,(*proot)->key);
        free_Node(*proot);
    }
}

/**************************************************************************************************************************************************************/
/* Функции для работы с файлом данных */

/* Функция загрузки таблицы из файла  */
int D_Load(Tree *ptree, char **fname) {
    Line;
    printf("Введите имя файлов\n(без типа файла; файлы будут созданы автоматически: 'Имяфайла_data.bin'): --> ");
    *fname = get_str();
    Line;
    if (*fname == NULL)
        return 0;
    if (!load(ptree, *fname))
        create(*fname, &(*ptree).fd_keys, &(*ptree).fd_data);
    else{
        char *fname_keys = (char *) malloc((strlen(*fname) + 5)*sizeof(char));
        fname_keys = strcpy(fname_keys, *fname);
        fname_keys = strcat(fname_keys, ".bin");
        ptree->fd_keys = fopen(fname_keys, "w+");
            free(fname_keys);
        char *fname_data = (char *) malloc((strlen(*fname) + 10)*sizeof(char));
        fname_data = strcpy(fname_data, *fname);
        fname_data = strcat(fname_data, "_data.bin");
        ptree->fd_data = fopen(fname_data, "w+");
            free(fname_data);
    }
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
        Info *info= (Info*)malloc(sizeof(Info));

        fscanf(ptree->fd_data,"%f %f ",&info->info1, &info->info2);
        info->info3=fget_str(ptree->fd_data);
        info->next=NULL;
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

/* Рекурсивная выгрузка всего дерева с ключами в файл (с помощью прямого обхода). */
int save(Node *root, FILE *fd_keys, FILE *fd_data) {
    if (root) {
        while (root->info->next) {
            Info *ptr_prev = root->info;
            Info *ptr = root->info->next;
            while (ptr->next) {
                ptr_prev = ptr;
                ptr = ptr->next;
            }
            ptr_prev->next = NULL;
            fprintf(fd_keys, "%s\n", root->key);
            fprintf(fd_data, "%f %f %s\n", ptr->info1, ptr->info2, ptr->info3);
            free(ptr->info3);
            free(ptr);
        }
        fprintf(fd_keys, "%s\n", root->key);
        fprintf(fd_data, "%f %f %s\n", root->info->info1, root->info->info2, root->info->info3);


        if (root->left) {
            save(root->left, fd_keys, fd_data);

        }
        if (root->right) {
            save(root->right, fd_keys, fd_data);
            //fprintf(fd_dot, "\"%s - %f %f %s\" -> \"%s - %f %f %s\";", root->key, root->info->info1,root->info->info2, root->info->info3,
              //          root->right->key, root->right->info->info1, root->right->info->info2, root->right->info->info3);
        }
        return 1;
    }
}
/**************************************************************************************************************************************************************/

int save_to_dot(Node *root,FILE *fd_dot) {
    if (root->left) {
        fprintf(fd_dot, "\"%s: ", root->key);
        Info *ptr1 = root->info;
        while (ptr1->next) {
            fprintf(fd_dot, "%f %f %s \t", ptr1->info1, ptr1->info2, ptr1->info3);
            ptr1 = ptr1->next;
        }
        fprintf(fd_dot, "%f %f %s\" -> ", ptr1->info1, ptr1->info2, ptr1->info3);

        fprintf(fd_dot, "\"%s: ", root->left->key);
        Info *ptr2 = root->left->info;
        while (ptr2->next) {
            fprintf(fd_dot, "%f %f %s \t", ptr2->info1, ptr2->info2, ptr2->info3);
            ptr2 = ptr2->next;
        }
        fprintf(fd_dot, "%f %f %s\";", ptr2->info1, ptr2->info2, ptr2->info3);

        save_to_dot(root->left, fd_dot);

    }
    if (root->right) {
        fprintf(fd_dot, "\"%s: ", root->key);
        Info *ptr1 = root->info;
        while (ptr1->next) {
            fprintf(fd_dot, "%f %f %s \t", ptr1->info1, ptr1->info2, ptr1->info3);
            ptr1 = ptr1->next;
        }
        fprintf(fd_dot, "%f %f %s\" -> ", ptr1->info1, ptr1->info2, ptr1->info3);

        fprintf(fd_dot, "\"%s: ", root->right->key);
        Info *ptr2 = root->right->info;
        while (ptr2->next) {
            fprintf(fd_dot, "%f %f %s \t", ptr2->info1, ptr2->info2, ptr2->info3);
            ptr2 = ptr2->next;
        }
        fprintf(fd_dot, "%f %f %s\";", ptr2->info1, ptr2->info2, ptr2->info3);
        save_to_dot(root->right, fd_dot);
    }
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
        save(tree.root,tree.fd_keys,tree.fd_data);
    delTree(&tree.root);
    printf("Таблица сохранена.\n");
    fclose(tree.fd_keys);
    fclose(tree.fd_data);
    tree.fd_keys = NULL;
    tree.fd_data = NULL;
    free(fname);
    return 0;
}