#include "user.h"
#include "book_management.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *username;
char *password;
char *remove_title;
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

UserLink *createhead()//create the user headnode;
{
	UserLink *head = (UserLink *)malloc(sizeof(UserLink));
	head->next=NULL;
	return head;	
}

UserLink *createuser(User userdata)
{
	UserLink *Newnode =(UserLink*)malloc(sizeof(UserLink));
	Newnode->userdata=userdata;
	Newnode->next=NULL;
	return Newnode;
}

int check_number(char* str)
{ 
	int check = 0;
    char* name = str;
    while (check==0 && *name)
	{
        if(*name >= '0' && *name <= '9') 
		{
			check++;
	}
        name++;
    }
    return check;
}

static void User_menu(char *username,BookArray *head,UserLink *headNode) {
	int user_option =5;
	UserLink* u = headNode;
	while(u){
		
		if(strcmp(u->userdata.username, username) == 0) 
		break;
		u = u->next;
	}// to find the user
	int id_s = 0;
	do {
		printf("\n(Logged in as %s...)\n",username);
		char * answer = ask_question("\nPlease choose an option:\n1) Borrow a book\n2) Return a book\n3) Search for books\n4) Display all books\n5) Quit\nOption: ");
		user_option = atoi(answer);
		BookArray *move=head;
		free(answer);
		switch (user_option) {
			case 1:
		
				Borrow(u,head);
			
				break;
			case 2:
				Return_book(u,head);
				break;
			case 3:
				Searchbook(head);
				break;
			case 4:
				printf("ID\t");
				printf("Title\t\t");
				printf("Author\t\t");
				printf("Year\t");
				printf("Copies\n");
				Displaybook(head);
				break;
			case 5:
				printf("goodbye\n");
				break;
			default:
				printf("Sorry, the option you entered was invalid,please try again.\n");
		}

	} while (user_option!= 5);

	return;
}

static void Lib_menu(BookArray *headnode) {
	int Lib_option =5;
		int flag1,flag2,flag3;
	Book book;
	do {
		printf("\n(Logged in as librarian)");
		char * answer = ask_question("\nPlease choose an option:\n1) Add a book\n2) Remove a book\n3) Search for books\n4) Display all books\n5) Quit\nOption: ");
		Lib_option = atoi(answer);
		BookArray *move=headnode->next;
		free(answer);
		switch (Lib_option) {
			case 1:
				
			book.id=atoi(ask_question("Enter the id of the book you wish to add:"));
			book.title=ask_question("Enter the title of the book you wish to add:");
			book.authors=ask_question("Enter the author of the book you wish to add:");
			book.year=atoi(ask_question("Enter the year that the book you wish to add was released:"));
			book.copies=atoi(ask_question("Enter the number of copies of the book you wish to add:"));
			while(move->book.id != book.id &&move->next != NULL )
			{
				move=move->next;
			}
			
			if(check_number(book.authors))
			{
				printf("Invalid Author names!\n");
				break;
		}
						 
			
			
			if(book.copies == 0 || book.year == 0)//book copies can not be zero.
				{
				printf("\ninvalid copies or year!\n");
				break;
				}
			if(move->book.id == book.id) // if the id is same,just add the number of book copies.
			{
				move->book.copies += book.copies;
				printf("Successfully added a book!\n");
				break;
			}
			else
			{
					add_book(book,headnode);
					printf("Book was successfully added!\n");
			}
		
				break;
			case 2:
				remove_book(book,headnode);
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

	} while (Lib_option!= 5);

	return;
}


int  Check_name(UserLink *head)
{
	UserLink *find;//qr is front pointer!
	find = head->next;
	while(find)
{
	if(find == NULL)//return 0 means never registe.
	{
		return 0;
	}
	if(strcmp(find->userdata.username,username) == 0)//It means the username has already regiested.
	{
		return 1;
    }
	find = find->next;
}
}


int Check_Password(UserLink *head )//0 means successful!
{ 
	UserLink *findpass;//qr is front pointer!
	findpass = head->next;
	while(findpass)
{
	if(findpass->userdata.username == username&&findpass->userdata.password == password) 
	{
		return 0;
    }
    else 
	findpass = findpass->next;
}
}

void add_user(UserLink *head)
{

	//UserLink *Newnode=(UserLink*)malloc(sizeof(UserLink)); 
	//Newnode->next = NULL;
	int i =0;
	UserLink *Newnode =(UserLink*)malloc(sizeof(UserLink));
//	Newnode->userdata=userdata;
	Newnode->userdata.number = 0;
	
	Newnode->next=head->next;
	head->next=Newnode; //Forward interpolation
	while(i<10)
	{
        Newnode->userdata.borrow[i]=0;
        i++;
    }
	Newnode->userdata.username=username;
	Newnode->userdata.password=password;
}
 
 
 
void Register_account(UserLink *head)
{
	User userdata;	
	username= ask_question("Please enter your username:");
	password= ask_question("Please enter your password:");
	while(strcmp(username,"librarian") == 0 &&strcmp(password,"librarian") == 0)//if someone registe the librarian menu 
	{
	  printf("Sorry,the username has already exists. Please try it again!\n");
	  return;
}
	if(Check_name(head) == 1) //check if the username has been registed
	{
		printf("sorry!failed in registed!\n");
	}
	else
	{
	add_user(head);
	printf("Register successful!\n");
}
}

void Login_account(BookArray *headnode,UserLink *head)
{
	
	UserLink *ppmove=head;
	username = ask_question("Please enter your username:");
	password = ask_question("Please enter your password:");
	char *libname ="librarian";
	char *libpassword = "librarian"; 
	if(strcmp(username,libname) == 0 &&strcmp(password,libpassword) == 0)//go to the librarian menu!
	{
	  printf("Librarian menu\n");
	  Lib_menu(headnode);
}
	else//enter the user menu!
	{
		while(ppmove->next != NULL&&strcmp(username,ppmove->userdata.username) != 0 )
		{
		ppmove=ppmove->next;
}
	if(Check_name(head) == 0)
	{
		printf("Sorry,no registration!\n");
		return;
	}
	if(strcmp(ppmove->userdata.username,username) ==0&&strcmp(ppmove->userdata.password ,password) !=0)//correct username,wrong password
	{
		printf("Sorry! Wrong password!\n");
	}
	if(strcmp(ppmove->userdata.username,username) ==0&&strcmp(ppmove->userdata.password ,password) ==0) //if the username and password are all correct;
	{
		printf("successful login!\n\n");
		User_menu(username,headnode,head);
	}

}
}

int Store_users(UserLink *headnode){
    FILE *file;
    UserLink *p = headnode->next;
    file = fopen("user.txt", "wb");
    int i = 0;
    while (p) 
	{
        fwrite(&(p->userdata.number), sizeof(int), 1, file);
        fwrite(p->userdata.username, 50*sizeof(char), 1, file);
        fwrite(p->userdata.password, 50*sizeof(char), 1, file);
        while(i < 10)
		{
            fwrite(&(p->userdata.borrow[i]), sizeof(int), 1, file);
            i++; 
        }
        p = p->next;
    }
    fclose(file);
    return 0;
}


int Load_users(UserLink *headnode){
	FILE *fp;
    UserLink *qn = headnode; //follow the node
    if ((fp = fopen("user.txt", "rb")) == NULL) {
        fp = fopen("user.txt", "wb");
        fclose(fp);
    }
    fp = fopen("user.txt", "rb");
    int a = 0;
    while (fread(&a, sizeof(int), 1, fp)) {
        UserLink *pn = (UserLink *) malloc(sizeof(UserLink));
        pn->userdata.number = a;
        pn->next = NULL;
        pn->userdata.username = (char *) malloc(50 * sizeof(char));
        pn->userdata.password = (char *) malloc(50 * sizeof(char));
        fread(pn->userdata.username, 50 * sizeof(char), 1, fp);
        fread(pn->userdata.password, 50 * sizeof(char), 1, fp);
        int i = 0;
        for (i = 0; i < 10; i++) {

            fread(&(pn->userdata.borrow[i]), sizeof(int), 1, fp);

        }
        qn->next = pn;
        qn = pn;
    }
    if (headnode->next != NULL) return 0;
    fclose(fp);
}

