#include "user.h"
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

UserLink *createhead()//创建头节点 
{
	UserLink *head = (UserLink *)malloc(sizeof(UserLink));
	head->next=NULL;
	return head;	
}

int  Check_name(char *usernames)//0是成功，1是失败； 
{
	UserLink *head = createhead();
	UserLink *find;//qr is front pointer!
	find = head->next;
	while(find)
{
	if(find == NULL)//返回0是指没有名字没有注册过 
	{
		return 0;
	}
	if(find->userdata.username == usernames)//有注册过 
	{
		return 1;
    }
	find = find->next;
}
}


int Check_Password(char *usernames,char *userpasswords)//0是成功，1是失败 ;
{
	UserLink *head = createhead();
	UserLink *findpass;//qr is front pointer!
	findpass = head->next;
	while(findpass)
{
	if(findpass->userdata.username == usernames&&findpass->userdata.password == userpasswords) 
	{
		return 0;
    }
    else 
	findpass = findpass->next;
}
}


void Login_account()
{
	User userdata;
	char *name = ask_question("Please enter your username:");
	char *password = ask_question("Please enter your password:");
	/*if(strcmp(name,"librarian") == 0 &&strcmp(password,"librarian") == 0)//进入图书管理员界面
	{
	  Librarian(); 
}*/ 
	if(strcmp(name,"librarian") != 0 &&strcmp(password,"librarian") != 0)
	{
		if(Check_name(name) == 0)
		{
			printf("Sorry,the username has not been registed!/n ");
		}
		else if(Check_Password(name,password) !=0 )
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


