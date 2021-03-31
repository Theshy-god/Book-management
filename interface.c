#include "user.h"
#include "book_management.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *ask_question(const char *question) {

	printf("%s",question);

	const int size_step = 2;
	char *answer = malloc(size_step);
	answer[0] = 0; //now it's a string of length 0.

	//read until a new line in blocks of size_step  bytes at at time
	char *next_chunk = answer;
	int iteration = 0;
	do {
		answer = realloc(answer, size_step + iteration*size_step);
		next_chunk = answer + strlen(answer); //answer may have moved.
		fgets(next_chunk, size_step, stdin);

		next_chunk = answer + strlen(answer); //take the new read into account
		++iteration;
	} while (* (next_chunk-1) != '\n');

	*(next_chunk-1) = 0; //truncate the string eliminating the new line.

	return answer;
}



static void main_menu(BookArray *headnode,UserLink *head) {//Ö÷²Ëµ¥ 
	int option = 5; //These are the five options you just logged into the interface.
	int lib_option = 5;
	int user_option =5;
	do {
		char * answer = ask_question("\nPlease choose an option:\n1) Register an account\n2) Login\n3) Search for books\n4) Display all books\n5) Quit\nOption: ");
	//	BookArray *move=headnode;
		option = atoi(answer);
		free(answer);
		switch (option) {
			case 1:
				Register_account(head);
				break;
			case 2:
				Login_account(headnode,head);
				break;
			case 3:
				Searchbook(headnode);
				break;
			case 4:
				printf("ID\t");
				printf("Title\t\t");
				printf("Author\t\t");
				printf("Year\t");
				printf("Copies\n");
				Displaybook(headnode);
				break;
			case 5:
				printf("goodbye\n");
				break;
			default:
				printf("Sorry, the option you entered was invalid,please try again.\n");
		}

	} while (option!= 5);

	return;
}

int main() {
/*	Book A1 = {
		1,"Math","Chen",2020,10
	};
	Book A2 = {
		2,"Chinese","Liu",2020,90
	};
	Book A3 = {
		3,"English","Hu",2020,90
	};
		Book A4 = {
		4,"Math","Chen",2021,90
	};
	Book A5 = {
		5,"Math","Li",2021,90
	};
	Book A6 = {
		6,"Chinese","Wang",2022,90
	};*/
	BookArray* Headnode = createheadnode(); 
	UserLink* Head =createhead(); 
	/*add_book(A1,Headnode);
	add_book(A2,Headnode);
 	add_book(A3,Headnode); 
 	add_book(A4,Headnode);
	add_book(A5,Headnode);
 	add_book(A6,Headnode);*/
 	load_books(Headnode);
 	Load_users(Head);
	main_menu(Headnode,Head);
	store_books(Headnode);
	Store_users(Head);
	return 0;
}
