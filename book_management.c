#include "book_management.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *search_title;
char *search_author;
int search_year;
int search_copies; 

BookArray *createheadnode()//创建头节点 
{
	BookArray *head;
	head=(BookArray *)malloc(sizeof(BookArray));
	head->next=NULL;
	head->length = 0;
	return head;	
}
BookArray *createnode(Book books)//创建头节点 
{
	BookArray *Newnode;
	Newnode=(BookArray *)malloc(sizeof(BookArray));
	Newnode->book = books;
	Newnode->next=NULL;
	return Newnode;	
}

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


int add_book(Book book,BookArray *headnode2)//add the book! 
{
	/*BookArray *Newnode=(BookArray*)malloc(sizeof(BookArray)); 
	Newnode->book=books; 
	Newnode->next = NULL;*/
//	BookArray *Newnode = createnode(book);
/*	if (p->next != NULL)
	{
		p = p->next;
	}
	if(p->next==NULL){
		p->next = Newnode;//此时Newnode成为链表的最后一个结点 要让他的next指向0； 
	}*/
	//head->length += 1;
	/*while(Newnode->book.title == book.title || Newnode->book.year == book.year ||Newnode->book.authors == book.authors) 
	{
		book.copies += 1;
	}*/
//	Newnode->next=headnode->next;
	//headnode->next=Newnode;
//	return 0;
	//BookArray *pmove=headnode2;
	BookArray *pmove = headnode2;
	/*while(pmove->next!=NULL)
	{
		
		if(strcmp(pmove->book.title,book.title) == 0 && strcmp(pmove->book.authors,book.authors) == 0)
		{
		pmove->book.copies += book.copies;
		return 0;
	}
		pmove=pmove->next;
	}
	pmove = headnode2;*/
	BookArray *Newnode =(BookArray*)malloc(sizeof(BookArray));
	Newnode -> book = book;
//	Newnode -> book.copies = 300; 
	Newnode -> next = NULL; 
	while(headnode2 != NULL && pmove->next != NULL)
	{
		pmove=pmove->next;
	}
	if(headnode2->next == NULL)
	{
		headnode2->next=Newnode;
	}
	if(headnode2->next != NULL)
	{
		pmove->next =Newnode;
	}
	headnode2->length += 1; 
    /*Newnode->next=headnode2->next;
	headnode2->next=Newnode;*/ //前插法  
	return 0;
	
}


int remove_book(Book book,BookArray *head)
{
	BookArray *qr,*q;//qr is front pointer!
	qr=head;
	q = head->next;
	
	int remove_id=atoi(ask_question("Please enter the id of the book that you want to remove:"));
	if(head->next == NULL)
	{
		printf("There is no book in this library!\n") ;
	}
	while(q)
	{
	if(q->book.id == remove_id)
	{	
		qr->next = q->next;
		head->length -= 1;	
		free(q);
		break;
	}
	else
	{
		qr = q;
		q = qr->next;
	}
	}
	printf("The book with id %i has been deleted!\n",remove_id);
	return 0;
}


void Displaybook(BookArray *headnode)
{
	if (headnode->next == NULL)
	{	
	printf("No books in the library\n");
		return;
	}
	 
	headnode = headnode -> next;
	while(headnode !=NULL)
	{
		printf("%i\t",headnode->book.id);
		printf("%s\t",headnode->book.title);
		printf("%s\t",headnode->book.authors);
		printf("%i\t",headnode->book.year);
		printf("%i\n",headnode->book.copies);
		headnode=headnode->next;
} 
}

void ShowFindbook(BookArray *head)
{
		printf("%i\t",head->book.id);
		printf("%s\t",head->book.title);
		printf("%s\t",head->book.authors);
		printf("%i\t",head->book.year);
		printf("%i\n",head->book.copies);

} 
	
	
/*int store_books(FILE *file)
{
	BookArray*head = createheadnode();
	file = fopen(".\\book.txt", "r");
	if (file == NULL) {
		printf("Failed opening the file.\n");
		return 0;
	}
	BookArray* p = head;
	while (p != NULL)
	{
		fwrite(&p->book, sizeof(BookArray), 1, file);
		p = p->next;
	}

	fclose(file);
	printf("Successfully stored!\n");
}
*/
BookArray *find_book_by_title (const char *title,BookArray *headNode)
{
	BookArray *qr1 = headNode->next;
	while(qr1 != NULL&&strcmp(qr1->book.title,title) != 0)
	{
		qr1 = qr1->next;
	}
	return qr1;
	
	
}

	

BookArray *find_book_by_author (const char *author,BookArray *head)
{
	BookArray *qr2 = head->next;
	while(qr2 != NULL&&strcmp(qr2->book.authors,author) != 0)
	{
		qr2 = qr2->next;
	}
	return qr2;
	
}

BookArray *find_book_by_year (unsigned int year,BookArray *head)
{
	BookArray *qr3 = head->next;
	while(qr3 != NULL&&qr3->book.year != year)
	{
		qr3 = qr3->next;
	}
	return qr3;
	
}


void Searchbook(BookArray *headnode)
{
	int Search_option =5;
	Book book;
	do {
		char * answer = ask_question("\nPlease choose an option:\n1)Find books by title:\n2)Find books by author:\n3)Find books by year:\n4)Back to the previous menu!\nOption: ");
		Search_option = atoi(answer);
		free(answer);
		switch (Search_option) {
			case 1:
			Search_title(headnode);
			break;
		
			case 2:
			Search_author(headnode);
			break;
		
			case 3:
			Search_year(headnode);
				break;
			case 4:
				break;
			default:
				printf("Sorry, the option you entered was invalid,please try again.\n");
		}

	} while (Search_option!= 4);

	return;
	
}
void Search_title(BookArray *headnode)
{
	search_title=ask_question("Please enter the title:");
	BookArray *p =NULL;//书里面移动的指针 
	BookArray *pmove=NULL;//新链表移动的指针 
	BookArray *Newlist =NULL;
	p=find_book_by_title(search_title,headnode);
	Newlist=p;
	pmove=p;
	while(p != NULL)
	{
		p=find_book_by_title(search_title,p);//找到下一个书 
		if(p==NULL)
		{
		pmove->pnext=NULL; 
		break;
		}
		else
		{
			pmove->pnext= p;
            pmove =pmove->pnext;
            pmove->pnext=NULL;
            
        }
    }
    while (Newlist != NULL)
	{
        ShowFindbook(Newlist);
        Newlist = Newlist->pnext;
	 }
}

void Search_author(BookArray *headnode)
{
	search_author=ask_question("Please enter the authors:");
	BookArray *p =NULL;//书里面移动的指针 
	BookArray *pmove=NULL;//新链表移动的指针 
	BookArray *Newlist =NULL;
	p=find_book_by_author(search_author,headnode);
	Newlist=p;
	pmove=p;
	while(p != NULL)
	{
		p=find_book_by_author(search_author,p);//找到下一个书 
		if(p==NULL)
		{
		pmove->pnext=NULL; 
		break;
		}
		else
		{
			pmove->pnext= p;
            pmove =pmove->pnext;
            pmove->pnext=NULL;
            
        }
    }
    while (Newlist != NULL)
	{
        ShowFindbook(Newlist);
        Newlist = Newlist->pnext;
	 }
 } 
 
void Search_year(BookArray *headnode)
{
	search_year=atoi(ask_question("Please enter the year:"));
	BookArray *p =NULL;//书里面移动的指针 
	BookArray *pmove=NULL;//新链表移动的指针 
	BookArray *Newlist =NULL;
	p=find_book_by_year(search_year,headnode);
	Newlist=p;
	pmove=p;
	while(p != NULL)
	{
		p=find_book_by_year(search_year,p);//找到下一个书 
		if(p==NULL)
		{
		pmove->pnext=NULL; 
		break;
		}
		else
		{
			pmove->pnext= p;
            pmove =pmove->pnext;
            pmove->pnext=NULL;
            
        }
    }
    while (Newlist != NULL)
	{
        ShowFindbook(Newlist);
        Newlist = Newlist->pnext;
	 }
 } 
 

