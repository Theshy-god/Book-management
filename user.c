#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *username;
char *password;

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
	if(Check_name(head) == 1)
	{
		printf("sorry!failed in registed!");
	}
	else{
	add_user(userdata,head);
	printf("Register successful!");
}
}

void Login_account(UserLink *head)
{
	User userdata;
	UserLink *ppmove=head;
	username = ask_question("Please enter your username:");
	password = ask_question("Please enter your password:");
	char *libname ="librarian";
	char *libpassword = "librarian"; 
	if(strcmp(username,libname) == 0 &&strcmp(password,libpassword) == 0)//进入图书管理员界面
	{
	  printf("Librarian menu");
}
	else//进入用户界面 
	{
		while(strcmp(username,ppmove->userdata.username) != 0 )
		{
		ppmove=ppmove->next;
    if(Check_name(head) == 0)
	{
		printf("Sorry,no registration!");
		break;
	}
}
	if(strcmp(ppmove->userdata.username,username) ==0&&strcmp(ppmove->userdata.password ,password) !=0)//用户名对，密码不对； 
	{
		printf("Sorry! Wrong password!");
	}
	if(strcmp(ppmove->userdata.username,username) ==0&&strcmp(ppmove->userdata.password ,password) ==0) //用户名和密码都对的时候 
	{
		printf("successful login!");
	}
	
}
}
		/*else if(Check_Password(name,password) == 0 )
		{
			printf("Sorry,wrong password.Please try it again!\n");
		}
}
}
	/*if(strcmp(UserLink->userdata.username,name ==0) && strcmp(UserLink->userdata.password,password) == 0)
	{
		printf("Login successfully!");
	}
} */


