#include "utils-bms.h"

void main() {
    int cols;
    terminal_size(&cols);
    int input;
    account *head_account = NULL;
    client *head_client = NULL;
    read_clients(&head_client);
    read_accounts(&head_account);
    // clients_list(head_client);
    
    start :
        menu(1);
        do {
            input = getchar() - '0';
            getchar();
            if (input < 1 || input > 4) {
                putchar('\n');
                center("/!\\ Choix incorrect.\n\n", cols);
                center("> ", cols);
            }
        }while(input < 1 || input > 4);
        switch (input) {
            case 1 :
                menu(2); // debut de la gestion clients
                do {
                    input = getchar() - '0';
                    getchar();
                    if (input < 1 || input > 4) {
                        putchar('\n');
                        center("/!\\ Choix incorrect.\n\n", cols);
                        center("> ", cols);
                    }
                }while(input < 1 || input > 6);
                switch (input) {
                    case 1 :
                            add_client(&head_client);                           // ajout client
                            
                            goto start;
                            break;
                    case 2 :
                            {   
                                int input, choix;
                                system("clear");
                                center("ID du client : ", cols);
                                scanf("%d", &input);
                                getchar();
                                center("1 - Nom\n", cols);
                                center("2 - Prenom\n", cols);
                                center("3 - Numero\n", cols);
                                center("4 - Profession\n", cols);
                                center("> ", cols);
                                scanf("%d", &choix);
                                getchar();
                                modify_client(&head_client, input, choix);      // modifier client
                                goto start;
                                break;
                            }
                    case 3 :    
                            {
                                delete_client(&head_client);             // supprimer client
                                goto start;
                                break;
                            }
                    case 4 :
                            {   
                                system("clear");
                                int inp;
                                center("===========================\n\n", cols);
                                center(" [1] - recherche par ID \n\n", cols);
                                center(" [2] - recherche par nom \n\n", cols);
                                center(" [3] - Revenir au Menu principal\n\n", cols);
                                center("===========================\n\n", cols);
                                center("> ", cols);

                                do {
                                    inp = getchar() - '0';
                                } while (inp < 1 || inp > 3);
                                putchar('\n');
                                switch(inp) {
                                    case 1 : {
                                            center("ID du client : ", cols);
                                            int id;
                                            scanf("%d", &id);
                                            getchar();
                                            client *ptr = (client*)search_client_id(head_client, id);// rechercher client
                                            if (ptr == NULL) {
                                                putchar('\n');
                                                center("Client introuvable.\n", cols);
                                                fflush(stdout);
                                                sleep(3);
                                                goto start;
                                            }
                                            putchar('\n');
                                            center("Nom :", cols);
                                            printf("%s\n", ptr -> last_name);
                                            center("Prenom : ", cols);
                                            printf("%s\n", ptr -> first_name);
                                            center("Numero de telephone : ", cols);
                                            printf("%s\n", ptr -> phone_num);
                                            center("Profession : ", cols);
                                            printf("%s\n", ptr -> profession);
                                            sleep(8);
                                            goto start;
                                    }
                                    case 2 : {
                                            center("Nom du client : ", cols);
                                            char lname[50];
                                            scanf("%s", lname);
                                            getchar();
                                            client *ptr = (client*)search_client_last_name(head_client, lname);// rechercher client
                                            if (ptr == NULL) {
                                                putchar('\n');  
                                                center("client introuvable !", cols);
                                                fflush(stdout);
                                                sleep(3);
                                                goto start;
                                            }
                                            putchar('\n');
                                            center("Nom : ", cols);
                                            printf("%s\n", ptr -> last_name);
                                            center("Prenom : ", cols);
                                            printf("%s\n", ptr -> first_name);
                                            center("Numero de telephone : ", cols);
                                            printf("%s\n", ptr -> phone_num);
                                            center("Profession : ", cols);
                                            printf("%s\n", ptr -> profession);
                                            center("ID du client : ", cols);
                                            printf("#%d\n", ptr -> id_client);
                                            sleep(5);
                                            goto start;
                                    }
                                    case 3 :
                                        {
                                            goto start;
                                            break;
                                        }
                                }
                                break;
                            }
                    case 5 :
                        putchar('\n');
                        goto start;
                        break;
                    case 6 :
                        save_client(head_client);
                        save_accounts(head_account);

                        free_all(&head_client, &head_account);
                        p_exit(3);
                }
                break;
            case 2 : 
                menu(3); // debut de la gestion de comptes
                do {
                    input = getchar() - '0';
                    getchar();
                    if (input < 1 || input > 6) {
                        putchar('\n');
                        center("/!\\ Choix incorrect.\n\n", cols);
                        center("> ", cols);
                    }
                }while(input < 1 || input > 6);
                switch (input) {
                    case 1 :
                            add_account(&head_account, head_client);// ajout compte
                            goto start;
                            break;
                    case 2 :
                            // consultation
                            {
                                int inp;
                                center("client id : ", cols);
                                scanf("%d", &inp);
                                getchar();
                                consultation(head_account, head_client, inp, cols);

                                goto start;
                                break;
                            }
                            
                    case 3 :
                            delete_account(&head_account); // supprimer compte
                            goto start;
                            break;
                    case 4 :
                        goto start;
                }

                break;
            case 3 : 
                menu(4); // debut de la gestion des operations
                do {
                    input = getchar() - '0';
                    getchar();
                    if (input < 1 || input > 4) {
                        putchar('\n');
                        center("/!\\ Choix incorrect.\n\n", cols);
                        center("> ", cols);
                    }
                }while(input < 1 || input > 4);
                switch (input) {
                    case 1 :
                            withdraw(&head_account);// retrait
                            goto start;
                            break;
                    case 2 :
                            transfer(&head_account);// virement
                            goto start;
                            break;
                    case 3 :
                        goto start;
                }
                break;
            case 4 : 
                save_client(head_client);
                save_accounts(head_account);

                
    
                free_all(&head_client, &head_account);
                p_exit(3);
                break;
        }
}




