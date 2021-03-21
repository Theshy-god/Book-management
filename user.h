#include <stdio.h>

typedef struct _user {
		char *username; //register username
		char *password; //register password
}User;

typedef struct _UserArray {
	User userdata; 
	struct _UserArray* next; // pointer to array (or linked list) of struct Book.
}UserLink;

UserLink *createhead();
int  Check_name(UserLink*head);
int checkname(UserLink *p);
int Check_password(char *usernames,char *userpasswords);
void add_user(User userdata,UserLink *head);
void Register_account(UserLink* head);
void Login_account(UserLink *head);
void Librarian(); 
