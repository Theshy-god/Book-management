#include <stdio.h>

typedef struct _user {
		char *username; //register username
		char *password; //register password
}User;

typedef struct _UserArray {
	User userdata; 
	struct _UserArray* next; // pointer to array (or linked list) of struct Book.
}UserLink;

int  Check_name(char *usernames);
int Check_password(char *usernames,char *userpasswords);
void Register_account();
void Login_account();
void Librarian(); 
