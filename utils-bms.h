#include "utils-bms.c"

int rand_ms();
int generate_id();
void center(const char *text, int cols);
void p_exit(int m);
void terminal_size(int *cols);
void actual_time(c_date *date);
void add_client(client **first_client);
void *search_client_id(client *first_client, int id);
void *search_client_last_name(client *first_client, const char *l_name);
void delete_last_client(client **head);
void free_all(client **client_start, account **account_start);
void delete_client(client **head_client);
void menu(int menu_number);
void modify_client(client **first_client, int id, int choice);
void read_clients(client **first_client);
void clients_list(client *first_client);
void save_client(client *head);
void save_accounts(account *account_start);
void delete_last_account(account **head);
void read_accounts(account **account_start);
void add_account(account **head_a, client *head_c);
void consultation(account *head_account, client *head_client, int client_id, int cols);
void withdraw(account **head);
void transfer(account **head);
void delete_account(account **head);