#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

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
void actual_time(c_date *date) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    (date -> year) = (int)tm.tm_year + 1900;
    (date -> month) = (int)tm.tm_mon + 1;
    (date -> day) = (int)tm.tm_mday;
}
//structure compte
typedef struct account {
    int id_account;
    int id_client;
    int balance;
    c_date date;
    struct {
        c_date date_op;
        int op;
    };
    struct account *next_account;
}account;
//structure client
typedef struct client {
    char last_name[50];
    char first_name[50];
    char phone_num[12];
    char profession[50];
    int id_client;
    struct client *next_client;
}client;

//fonction d'ajout clients
void add_client(client **first_client) {
    static int id = 0;
    int cols;
    terminal_size(&cols);
    client *last_client;
    client *ptr = *first_client;
    if (*first_client == NULL) {
        id++;
        *first_client = malloc(sizeof(client));
        (*first_client) -> next_client = NULL;
    }
    else {
        if (id == 0) {
            while (ptr != NULL) {
                ptr = ptr -> next_client;
                id++;
            }
            ptr = *first_client;
        }
        while (ptr != NULL) {
            last_client = ptr;
            ptr = ptr -> next_client;
        }
        id++;
        ptr = malloc(sizeof(client));
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
    (last_client) -> id_client = id;
    getchar();
    putchar('\n');
    center("id du client : ", cols);
    printf("#%d", (last_client) -> id_client);
    fflush(stdout);
    sleep(2);
}
//fonction de recherche client par Id du client
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
//fonction de recherche client par Nom
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
//fonction de suppression du dernier client
void delete_last_client(client **head) {
    client *ptr = *head;
    client *last_client = NULL;
    while(ptr -> next_client != NULL) {
        last_client = ptr;
        ptr = ptr -> next_client;
    }
    if (last_client == NULL) {
        *head = NULL;
    }
    else {
        last_client -> next_client = NULL;
    }
    free(ptr);
}
//fonction de suppression d'un client
void delete_client(client **head_client) {
    int cols, inp;
    terminal_size(&cols);
    client *ptr = *head_client;
    client *last_client = NULL;
    system("clear");
    center("1 - un seul client.\n", cols);
    center("2 - tous les clients.\n", cols);
    center("> ", cols);
    do {
        scanf("%d", &inp);
    } while (inp < 1 || inp > 2);
    getchar();
    switch(inp) {
        case 1 :
            {
                int id;
                center("id du client : ", cols);
                scanf("%d", &id);
                getchar();
                while (ptr != NULL) {
                    if (ptr -> id_client == id) {
                        last_client -> next_client = ptr -> next_client;
                        free(ptr);
                        return;
                    }
                    last_client = ptr;
                    ptr = ptr -> next_client;
                }
                last_client -> next_client = NULL;
                return;
            }
        case 2 :
            {
                if (ptr == NULL) {
                    return;
                }
                while (ptr -> next_client != NULL) {
                    last_client = ptr -> next_client;
                    free(ptr);
                    ptr = last_client;
                }
                free(ptr);
                *head_client = NULL;
                return;
            }
    }
}
//fonction de modification client
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
//fonction pour enregistrer les donnees dans un fichier externe
void read_clients(client **first_client) {
    int cols;
    static int num, i = 0;
    terminal_size(&cols);
    FILE* fd_r = fopen("clients.txt", "r");
    if (fd_r == NULL) {
        fprintf(stderr, "Can't open saving file");
    }
    *first_client = malloc(sizeof(client));
    client *last_client = *first_client;
    (last_client) -> next_client = NULL;
    while (fscanf(fd_r, "%[^,], %[^,], %[^,], %[^,], %d\n", (last_client) -> last_name, (last_client) -> first_name, (last_client) -> phone_num, (last_client) -> profession, &((last_client) -> id_client)) > 0) {
        (last_client) -> next_client = malloc(sizeof(client));
        (last_client) = last_client -> next_client;
        (last_client) -> next_client = NULL;
        // printf("%s %s %s %s %d", (*last_client) -> last_name, (*last_client) -> first_name, (*last_client) -> phone_num, (*last_client) -> profession, ((*last_client) -> id_client));
    }
    delete_last_client(first_client);
    fclose(fd_r);
}
//fonction pour lire les donnees a partir d'un fichier externe
void save_client(client *head) {
    client *curr = head;
    FILE* fd_w = fopen("clients.txt", "w");
    for (; curr != NULL; curr = curr -> next_client) {
        fprintf(fd_w, "%s, %s, %s, %s, %05d\n", curr -> last_name, curr -> first_name, curr -> phone_num, curr -> profession, curr -> id_client);
    }
    fclose(fd_w);
}
//
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



//fonction pour enregistrer les donnees dans un fichier externe
void save_accounts(account *account_start) {
    FILE* fd_w = fopen("accounts.txt", "w");
    if (fd_w == NULL || account_start == NULL) {
        return;
    }
    account *ptr = account_start;
    while (ptr != NULL) {
        fprintf(fd_w, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", ptr -> id_account, ptr -> id_client, ptr -> balance, ptr -> date.day, ptr -> date.month, ptr -> date.year, ptr -> date_op.day, ptr -> date_op.month, ptr -> date_op.year, ptr -> op);
        ptr = ptr -> next_account;
    }
    fclose(fd_w);
}
//fonction de suppression du dernier compte 
void delete_last_account(account **head) {

    account *ptr = *head;
    account *last_account = NULL;
    while (ptr -> next_account != NULL) {
        last_account = ptr;
        ptr = ptr -> next_account;
    }
    if (last_account == NULL) {
        *head = NULL;
    }
    else {
        last_account -> next_account = NULL;
    }
    free(ptr);
}
//fonction pour lire les donnees a partir d'un fichier externe
void read_accounts(account **account_start) {
    FILE* fd_r = fopen("accounts.txt", "r");
    if (fd_r == NULL) {
        return;
    }
    *account_start = malloc(sizeof(account));
    account *ptr = *account_start;
    while(fscanf(fd_r, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", &(ptr -> id_account), &(ptr -> id_client), &(ptr -> balance), &(ptr -> date.day), &(ptr -> date.month), &(ptr -> date.year), &(ptr -> date_op.day), &(ptr -> date_op.month), &(ptr -> date_op.year), &(ptr -> op)) > 0) {
        ptr -> next_account = malloc(sizeof(account));
        ptr = ptr -> next_account;
        ptr -> next_account = NULL;
    }
    ptr -> next_account = NULL;
    delete_last_account(account_start);
    fclose(fd_r);
}
//fonction d'ajout de compte
void add_account(account **head_a, client *head_c) {
    int cols;
    terminal_size(&cols);
    int inp;
    account *ptr = *head_a;
    account *last_account;
    if (*head_a == NULL) {
        *head_a = malloc(sizeof(account));
        last_account = *head_a;
        last_account -> next_account = NULL;
    }
    else {
        while (ptr != NULL) {            
            last_account = ptr;
            ptr = ptr -> next_account;
        }
        ptr = malloc(sizeof(account));
        last_account -> next_account = ptr;
        last_account = ptr;
        last_account -> next_account = NULL;
    }





    center("id du client : ", cols);
    scanf("%d", &inp);
    getchar();
    client *check = (client*)(search_client_id(head_c, inp));
    if (check == NULL) {
        center("Creation de compte impossible, client introuvable.", cols);
        return;
    }
    last_account -> id_client = check -> id_client;
    center("Solde de base : ", cols);
    scanf("%d", &(last_account -> balance)); 
    getchar();
    putchar('\n');
    actual_time(&(last_account -> date));
    last_account -> id_account = generate_id();
    actual_time(&(last_account -> date_op));
    last_account -> op = last_account -> balance; 
    putchar('\n');
}
//fonction qui affiche tous les comptes d'un client 
void consultation(account *head_account, client *head_client, int client_id, int cols) {
    system("clear");
    putchar('\n');

    client *ptr_c = head_client;
    account *ptr_a = head_account;
    while (ptr_a != NULL && ptr_a -> id_client != client_id) {
        ptr_a = ptr_a -> next_account;
    }
    if (ptr_a == NULL || ptr_c == NULL) {
        return;
    }
    while (ptr_c != NULL && (ptr_c -> id_client) != (ptr_a -> id_client)) {
        ptr_c = ptr_c -> next_client;
    }
    int len = strlen(ptr_c -> first_name) + strlen(ptr_c -> last_name);
    center("id client : ", cols);
    printf("%d\n\n", ptr_a -> id_client);
    for (int i = 0; i < cols; i++) {
        printf("-");
    }
    putchar('\n');
    for (int i = 0; i < ((cols / 4) - 14)/2 ; i++) {
        putchar(' ');
    }
    printf("account ID");
    for (int i = 0; i < ((cols / 4) - 10)/2; i++) {
        putchar(' ');
    }
    putchar('|');
    for (int i = 0; i < ((cols / 4) - 13)/2; i++) {
        putchar(' ');
    }
    printf(" Nom & Prenom ");
    for (int i = 0; i < ((cols / 4) - 13)/2; i++) {
        putchar(' ');
    }
    putchar('|');
    for (int i = 0; i < ((cols / 4) - 15)/2; i++) {
        putchar(' ');
    }
    printf(" Solde de base ");
    for (int i = 0; i < ((cols / 4) - 15)/2; i++) {
        putchar(' ');
    }
    putchar('|');
    for (int i = 0; i < ((cols / 4) - 21)/2; i++) {
        putchar(' ');
    }
    printf(" Operations effectuees\n");
    
    ptr_a = head_account;
    while (ptr_a != NULL) {
        if (ptr_a -> id_client == client_id) {
            for (int i = 0; i < cols; i++) {
                putchar('-');
            }
            for (int i = 0; i < ((cols / 4) - 8)/2 ; i++) {
                putchar(' ');
            }
            printf("%d", ptr_a -> id_account);
            for (int i = 0; i < ((cols / 4) - 7)/2; i++) {
                putchar(' ');
            }
            putchar('|');
            for (int i = 0; i < ((cols / 4) - len+1)/2; i++) {
                putchar(' ');
            }
            printf("%s %s", ptr_c -> last_name, ptr_c -> first_name);
            for (int i = 0; i < ((cols / 4) - len+1)/2 -1; i++) {
                putchar(' ');
            }
            putchar('|');
            for (int i = 0; i < ((cols / 4) - (floor(log10(abs(ptr_a -> balance)) + 1)))/2; i++) {
                putchar(' ');
            }
            printf("%d", ptr_a -> balance);
            for (int i = 0; i < ((cols / 4) - (floor(log10(abs(ptr_a -> balance)) + 1)))/2; i++) {
                putchar(' ');
            }
            putchar('|');
            for (int i = 0; i < ((cols / 4) - 14)/2; i++) {
                putchar(' ');
            }
            printf("%d/%d/%d : ", ptr_a -> date_op.day, ptr_a -> date_op.month, ptr_a -> date_op.year);
            if (ptr_a -> op > 0) {
                printf("+%dDH\n", ptr_a -> op);
            }
            else {
                printf("%dDH\n", ptr_a -> op);
            }

        }
        
        ptr_a = ptr_a -> next_account;
    }
    for(int i = 0; i < cols; i++) {
        putchar('-');
    }
    fflush(stdout);
    sleep(10);

}
//fonction pour le retrait d'une somme depuis un compte
void withdraw(account **head) {
    int cols, id, sum;
    terminal_size(&cols);
    account *ptr = *head;
    system("clear");

    center("id du compte : ", cols);
    scanf("%d", &id);
    getchar();
    putchar('\n');
    if (*head == NULL) {
        center("Compte introuvable\n", cols);
        sleep(3);
        system("clear");
        return;
    }
    while (ptr -> id_account != id && ptr -> next_account != NULL) {
        ptr = ptr -> next_account;
    }
    if (ptr -> id_account == id) {
        center("Somme a retirer : ", cols);
        do {
            scanf("%d", &sum);
            if (sum <= 0 || sum > 700) {
                center("la somme doit etre inferieure a 700DH", cols);
            }
        } while (sum <= 0 || sum > 700);        
        getchar();

        ptr -> balance = ptr -> balance - sum;
        ptr -> op = -sum;
        actual_time(&(ptr -> date_op));
    }
    else {
        center("Compte introuvable", cols);
        fflush(stdout);
        sleep(3);
        system("clear");
        return;
    }
}
//fonction pour le transfert d'une somme a un compte
void transfer(account **head) {
    int cols, id, sum;
    terminal_size(&cols);
    account *ptr = *head;
    system("clear");

    center("id du compte : ", cols);
    scanf("%d", &id);
    getchar();
    putchar('\n');
    if (*head == NULL) {
        center("Compte introuvable\n", cols);
        fflush(stdout);
        sleep(3);
        return;
    }
    while (ptr -> id_account != id && ptr -> next_account != NULL) {
        ptr = ptr -> next_account;
    }
    if (ptr -> id_account == id) {
        center("Somme a transferer : ", cols);
        do {
            scanf("%d", &sum);
            if (sum <= 49) {
                center("la somme doit etre superieure a 50DH", cols);
            }
        } while (sum <= 49);
        getchar();
        ptr -> balance = ptr -> balance + sum;
        ptr -> op = sum;
        actual_time(&(ptr -> date_op));
    }
    else {
        center("Compte introuvable\n", cols);
        fflush(stdout);
        sleep(3);
        return;
    }
}
//fonction de suppression d'un compte
void delete_account(account **head) {
    int cols, id;
    account *ptr = *head;
    account *last_account;
    terminal_size(&cols);
    system("clear");
    center("ID du compte a fermer : ", cols);
    scanf("%d", &id);
    getchar();
    if (*head == NULL) {
        center("Compte introuvable, la suppression a echoue", cols);
        return;
    }
    while (ptr -> id_account != id && ptr -> next_account != NULL) {
        last_account = ptr;
        ptr = ptr -> next_account;
    }
    if (ptr -> id_account == id) {
        if (ptr -> next_account == NULL) {
            last_account -> next_account = NULL;
        }
        last_account -> next_account = ptr -> next_account;
        free(ptr);
        return;
    }
    return;
    
}


//
void free_all(client **client_start, account **account_start) {
    client *ptr = *client_start;
    client *lastc = ptr;
    account *ptr1 = *account_start;
    account *lasta = ptr1;

    while(ptr != NULL) {
        lastc = ptr -> next_client;
        free(ptr);
        ptr = lastc;
    }
    while(ptr1 != NULL) {
        lasta = ptr1 -> next_account;
        free(ptr1);
        ptr1 = lasta;
    }

}
//fonction qui affiche le menu voulu
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
                center("[2] - Consulter un compte\n", cols);
                center("[3] - Supprimer un compte\n", cols);
                center("[4] - Revenir au Menu principal\n", cols);
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
                center("================================\n\n", cols);
                center("> ", cols);
                break;
            }
        default : 
            p_exit;
    }
}