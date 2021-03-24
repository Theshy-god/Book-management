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

UserLink *createhead()//创建头节点 
{
	UserLink *head = (UserLink *)malloc(sizeof(UserLink));
	head->next=NULL;
	return head;	
}

/*UserLink *createuser(User userdata)
{
	UserLink *Newnode =(UserLink*)malloc(sizeof(UserLink));
	Newnode->userdata=userdata;
	Newnode->next=NULL;
	return Newnode;
}*/

static void User_menu(BookArray *head) {
	int user_option =5;
	do {
		char * answer = ask_question("\nPlease choose an option:\n1) Borrow a book\n2) Return a book\n3) Search for books\n4) Display all books\n5) Quit\nOption: ");
		user_option = atoi(answer);
		BookArray *move=head;
		free(answer);
		switch (user_option) {
			case 1:
				break;
			case 2:
				break;
			case 3:
				Searchbook(head);
				break;
			case 4:
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
	Book book;
	BookArray *test;
	do {
		char * answer = ask_question("\nPlease choose an option:\n1) Add a book\n2) Remove a book\n3) Search for books\n4) Display all books\n5) Quit\nOption: ");
		Lib_option = atoi(answer);
		BookArray *move=headnode;
		free(answer);
		switch (Lib_option) {
			case 1:
			book.id=atoi(ask_question("Enter the id of the book you wish to add:"));
			book.title=ask_question("Enter the title of the book you wish to add:");
			book.authors=ask_question("Enter the author of the book you wish to add:");
			book.year=atoi(ask_question("Enter the year that the book you wish to add was released:"));
			book.copies=atoi(ask_question("Enter the number of copies of the book you wish to add:"));
			add_book(book,headnode);
			printf("Book was successfully added!\n");
				break;
			case 2:
				remove_book(book,headnode);
				 break;
			case 3:
				Searchbook(headnode);
				break;
			case 4:
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


int  Check_name(UserLink *head)//0是系统没有这个名字可以注册，1是名字存在不能注册； 
{
	UserLink *find;//qr is front pointer!
	find = head->next;
	while(find)
{
	if(find == NULL)//返回0是指没有名字没有注册过 
	{
		return 0;
	}
	if(strcmp(find->userdata.username,username) == 0)//有注册过 
	{
		return 1;
    }
	find = find->next;
}
}


int Check_Password(UserLink *head )//0是成功
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

void add_user(User userdata,UserLink *head)
{

	//UserLink *Newnode=(UserLink*)malloc(sizeof(UserLink)); 
	//Newnode->next = NULL;
	UserLink *pmove=head;
	UserLink *Newnode =(UserLink*)malloc(sizeof(UserLink));
	Newnode->userdata=userdata;
	Newnode->next=NULL;
	if(head->next != NULL)
	{
		pmove=pmove->next;
	}
	if(head->next == NULL)
	{
		head->next=Newnode;
	}
	if(pmove->next==NULL)
	{
		pmove->next =Newnode;
	}
	Newnode->userdata.username=username;
	Newnode->userdata.password=password;
}
 
 
 
void Register_account(UserLink *head)
{
	User userdata;	
	username= ask_question("Please enter your username:");
	password= ask_question("Please enter your password:");
	while(strcmp(username,"librarian") == 0 &&strcmp(password,"librarian") == 0)//进入图书管理员界面
	{
	  printf("Sorry,the username has already exists. Please try it again!\n");
	  return;
}
	if(Check_name(head) == 1)
	{
		printf("sorry!failed in registed!\n");
	}
	else
	{
	add_user(userdata,head);
	printf("Register successful!\n");
}
}

void Login_account(BookArray *headnode,UserLink *head)
{
	User userdata;
	UserLink *ppmove=head;
	username = ask_question("Please enter your username:");
	password = ask_question("Please enter your password:");
	char *libname ="librarian";
	char *libpassword = "librarian"; 
	if(strcmp(username,libname) == 0 &&strcmp(password,libpassword) == 0)//进入图书管理员界面
	{
	  printf("Librarian menu\n");
	  Lib_menu(headnode);
}
	else//进入用户界面 
	{
		while(strcmp(username,ppmove->userdata.username) != 0 )
		{
		ppmove=ppmove->next;
    if(Check_name(head) == 0)
	{
		printf("Sorry,no registration!\n");
		break;
	}
}
	if(strcmp(ppmove->userdata.username,username) ==0&&strcmp(ppmove->userdata.password ,password) !=0)//用户名对，密码不对； 
	{
		printf("Sorry! Wrong password!\n");
	}
	if(strcmp(ppmove->userdata.username,username) ==0&&strcmp(ppmove->userdata.password ,password) ==0) //用户名和密码都对的时候 
	{
		printf("successful login!\n");
		User_menu(headnode);
	}
	
}
}


