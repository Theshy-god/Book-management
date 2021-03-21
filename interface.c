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


static void main_menu(UserLink *headnode) {
	int option = 5; //These are the five options you just logged into the interface.
	int lib_option = 5;
	int user_option =5;
	do {
		char * answer = ask_question("\nPlease choose an option:\n1) Register an account\n2) Login\n3) Search for books\n4) Display all books\n5) Quit\nOption: ");
		option = atoi(answer);
		free(answer);
		switch (option) {
			case 1:
				Register_account(headnode);
				break;
			case 2:
				Login_account(headnode);
				break;
			case 3:
				
				break;
			case 4:
			
				break;
			case 5:
				printf("goodbye");
				break;
			default:
				printf("Sorry, the option you entered was invalid,please try again.\n");
		}

	} while (option!= 5);

	return;
}

int main() {

	UserLink* Head =createhead(); 
	main_menu(Head);
	return 0;
}
