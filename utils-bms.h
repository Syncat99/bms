#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>

int rand_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_usec;
}
int generate_id() {
    srand((rand_ms()));
    int c;
    do {
        c = rand();
    } while (c < 10000 || c > 99999);
}
void p_exit(int m) {
    for (int i = m; i > 0; i--) {
        printf("\rle programme va quitter dans %d ..", i-1);
        fflush(stdout);
        sleep(1);
    }
    system("clear");
}

void terminal_size(int *cols) {
    struct winsize ws;
    ioctl(1, TIOCGWINSZ, &ws);
    *cols = ws.ws_col;
}

void center(const char *text, int cols) {
    
    int width = strlen(text);
    int margin = (cols / 2) - 10;
    int new_col = margin;
    // printf("\033[%d;%dH", (*row)++, new_col);
    if (cols < 150) {
        margin = (cols / 2) - 15;
    }
    if (cols < 70) {
        margin = cols / 4;
    }
    if (cols < 50) {
        margin = cols / 4 - 5;
    }
    
    for (int i = 0; i < margin; i++) {
        putchar(' ');
    }
    printf("%s", text);
    // printf("\n");
}
typedef struct creation_date {
    int day;
    int month;
    int year;
}c_date;

typedef struct client {
    char last_name[50];
    char first_name[50];
    char phone_num[10];
    char profession[50];
    int id_client;
    struct client *next_client;

}client;
typedef struct account {
    int id_account;
    int id_client;
    int balance;
    c_date creation_date;
    struct account *next_account;
}account;
void add_client(client **first_client) {
    int cols;
    terminal_size(&cols);
    client *last_client;
    client *ptr = malloc(sizeof(client));
    if (*first_client == NULL) {
        *first_client = ptr;
        (last_client) = *first_client;
        (last_client) -> next_client = NULL;
    }
    else {
        for (last_client = *first_client; (last_client -> next_client) != NULL; last_client = last_client -> next_client);
        last_client -> next_client = ptr;
        last_client = ptr;
        last_client -> next_client = NULL;
    }
    center("Nom : ", cols);
    scanf("%s", (last_client) -> last_name);
    center("Prenom : ", cols);
    scanf("%s", (last_client) -> first_name);
    center("Numero de telephone : ", cols);
    scanf("%s", (last_client) -> phone_num);
    center("Profession : ", cols);
    scanf("%s", (last_client) -> profession);
    (last_client) -> id_client = generate_id();
    getchar();
    putchar('\n');
    center("id du client : ", cols);
    printf("#%d", (last_client) -> id_client);
    fflush(stdout);
    sleep(2);
}
void *search_client_id(client *first_client, int id) {
    client *ptr;
    if (first_client == NULL) {
        return NULL;
    }
    ptr = first_client;
    while ((ptr -> id_client) != id && (ptr -> next_client) != NULL) {
        ptr = ptr -> next_client;
    }
    if (ptr -> id_client == id) {
        return ptr;
    }
    return NULL;
}

void *search_client_last_name(client *first_client, const char *l_name) {
    client *ptr = malloc(sizeof(client));
    if (first_client == NULL) {
        return NULL;
    }
    ptr = first_client;
    while ((strcmp(ptr->last_name, l_name) != 0 && ptr -> next_client != NULL)) {
        ptr = ptr -> next_client;
    }
    if ((strcmp(ptr->last_name, l_name) == 0)) {
        return ptr;
    }
    return 0;
}
void delete_last_client(client **head) {
    client *ptr = *head;
    client *last_client;
    while(ptr -> next_client != NULL) {
        last_client = ptr;
        ptr = ptr -> next_client;
    }
    free(ptr);
    last_client -> next_client = NULL;
}
int search_bool(client *first_client, const char *l_name, const char *f_name) {
    client *ptr;
    if (first_client == NULL) {
        return 0;
    }
    ptr = first_client;
    while (ptr != NULL) {
        if ((strcmp(ptr->last_name, l_name) == 0) && (strcmp(ptr->first_name, f_name) == 0)) {
            return 1;
        }
        ptr = ptr -> next_client;
    }
    return 0;
}
void menu(int menu_number) {
    int cols, inp;
    terminal_size(&cols);
    switch(menu_number) {
        case 1 : 
            {   
                system("clear");
                center("============================\n", cols);
                center("    ** MENU PRINCIPAL **\n", cols);
                center("============================\n", cols);
                center("[1] - Gestion des clients\n", cols);
                center("[2] - Gestion des comptes\n", cols);
                center("[3] - Gestion des opérations\n", cols);
                center("[4] - Quitter\n", cols);            
                center("============================\n\n", cols);
                center("> ", cols);
                break;
            }
        case 2 : 
            {
                system("clear");
                center("=============================\n", cols);
                center("  ** GESTION DES CLIENTS **\n", cols);
                center("=============================\n", cols);
                center("[1] - Ajouter un client\n", cols);
                center("[2] - Modifier client\n", cols);
                center("[3] - Supprimer client\n", cols);
                center("[4] - Rechercher client\n", cols);
                center("[5] - Revenir au Menu principal\n", cols);
                center("[6] - Quitter\n", cols);
                center("=============================\n\n", cols);
                center("> ", cols);
                break;
            }
        case 3 :
            {
                system("clear");
                center("================================\n", cols);
                center("    ** GESTION DES COMPTES **\n", cols);
                center("================================\n", cols);
                center("[1] - Ajouter un compte\n", cols);
                center("[2] - Modifier un compte\n", cols);
                center("[3] - Supprimer un compte\n", cols);
                center("[4] - Rechercher un compte\n", cols);
                center("[5] - Revenir au Menu principal\n", cols);
                center("[6] - Quitter\n", cols);
                center("================================\n\n", cols);
                center("> ", cols);
                break;
            }
        case 4 :
            {
                system("clear");
                center("================================\n", cols);
                center("  ** GESTION DES OPERATIONS **\n", cols);
                center("================================\n", cols);
                center("[1] - Retrait\n", cols);
                center("[2] - Virement\n", cols);
                center("[3] - Revenir au Menu principal\n", cols);
                center("[4] - Quitter\n", cols);
                center("================================\n\n", cols);
                center("> ", cols);
                break;
            }
        default : 
            p_exit;
    }
}

void modify_client(client **first_client, int id, int choice) {
    int cols, inp;
    terminal_size(&cols);
    client *ptr = *first_client;
    while (ptr -> id_client != id) {
        ptr = ptr -> next_client;
    }
    if ((ptr -> id_client) == id) {   
            switch(choice) {
                case 1 : {
                    center("Nouveau nom : ", cols);
                    scanf("%s", ptr -> last_name);
                    getchar();
                    break;
                }
                case 2 : {
                    center("Nouveau prenom : ", cols);
                    scanf("%s", ptr -> first_name);
                    getchar();
                    break;
                }
                case 3 : {
                    center("Nouveau numero : ", cols);
                    scanf("%s", ptr -> phone_num);
                    getchar();
                    break;
                }
                case 4 : {
                    center("Profession : ", cols);
                    scanf("%s", ptr -> profession);
                    getchar();
                    break;
                }
                default :
                    break;
            }
    }
    else {
        center("Client introuvable.\n", cols);
    }
}

void read_clients(client **first_client) {
    int cols;
    terminal_size(&cols);
    int number_of_clients;
    FILE* fd_r = fopen("save.txt", "r");
    client *ptr = malloc(sizeof(client));
    client *last_client;
    *first_client = ptr;
    (last_client) = (*first_client);
    (last_client) -> next_client = NULL;
    fscanf(fd_r, "%d\n", &number_of_clients);
    while ((fscanf(fd_r, "%[^,], %[^,], %[^,], %[^,], %d\n", (last_client) -> last_name, (last_client) -> first_name, (last_client) -> phone_num, (last_client) -> profession, &((last_client) -> id_client))) > 0) {
        (last_client) -> next_client = malloc(sizeof(client));
        (last_client) = (last_client) -> next_client;
        (last_client) -> next_client = NULL;
        // printf("%s %s %s %s %d", (*last_client) -> last_name, (*last_client) -> first_name, (*last_client) -> phone_num, (*last_client) -> profession, ((*last_client) -> id_client));
    }
    delete_last_client(first_client);
    
    fclose(fd_r);
}
void clients_list(client *first_client) {
    client *ptr;
    ptr = first_client;
    while (ptr != NULL) {
        printf("%s ", ptr -> last_name);
        fflush(stdout);
        sleep(3);
        ptr = ptr -> next_client;
    }
}
void save_client(client *head) {
    client *curr = head;
    FILE* fd_w = fopen("save.txt", "w");
    for (; curr != NULL; curr = curr -> next_client) {
        fprintf(fd_w, "%s, %s, %s, %s, %d\n", curr -> last_name, curr -> first_name, curr -> phone_num, curr -> profession, curr -> id_client);
    }
    fclose(fd_w);
}