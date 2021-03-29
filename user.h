#include <stdio.h>
#include <stdlib.h>
#include "book_management.h"
typedef struct _user {
		char *username; //register username
		char *password; //register password
		int number ;
	//	Book books;
		int borrow[10];  
}User;

typedef struct _UserArray {
	User userdata; 
	struct _UserArray* next; // pointer to array (or linked list) of struct Book.
}UserLink;

UserLink *createhead();
UserLink *createuser(User userdata);
int  Check_name(UserLink*head);
int checkname(UserLink *p);
int Check_password(char *usernames,char *userpasswords);
void add_user(User userdata,UserLink *head);
void Register_account(UserLink* head);
void Login_account(BookArray *headnode,UserLink *head);
void Borrow(UserLink *headNode,BookArray *headnode);
void Return_book();
int Store_users(UserLink *headnode);
int Load_users(UserLink *headnode);
