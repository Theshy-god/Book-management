#include "book_management.h"
#include <stdlib.h>
#include <string.h>
BookArray *createheadnode()//创建头节点 
{
	BookArray *head;
	head=(BookArray *)malloc(sizeof(BookArray));
	head->next=NULL;
	head->length = 0;
	return head;	
}

int add_book(Book book,BookArray *head)//add the book! 
{
	BookArray *Newnode=(BookArray*)malloc(sizeof(BookArray)); 
	BookArray* p = head;
	while(Newnode->book.title != book.title || Newnode->book.year != book.year ||Newnode->book.authors != book.authors) 
	{
	if (head->next != NULL && p->next != NULL)
	{
		p = p->next;
	}
	if (head->next == NULL) {
		head->next = Newnode;
	}
	else {
		p->next = Newnode;
		Newnode->next = NULL;//此时Newnode成为链表的最后一个结点 要让他的next指向0； 
	}
	head->length += 1;
	}
	while(Newnode->book.title == book.title || Newnode->book.year == book.year ||Newnode->book.authors == book.authors) 
	{
		book.copies += 1;
	}
	return 0;
}

int remove_book(Book book,BookArray *head)
{
	BookArray *qr,*q;//qr is front pointer!
	qr=head;
	q = head->next;
	if(head->next = NULL)
	{
		printf("There is no book in this library!\n") ;
	}
	if(q->book.title == book.title&&q->book.authors == book.authors&&q->book.year == book.year)
	{
		qr->next = q->next;
		head->length -= 1;
	}
	else
	{
		qr = q;
		q = qr->next;
	}
	free(q);
	return 0;
}

int store_books(FILE *file)
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

BookArray *find_book_by_title (const char *title,BookArray *head)
{
	BookArray *qr1 = head ->next;
	if(head->next == NULL)
	{
		printf("There is no book in this library!\n");
		return NULL;
	}
	while(strcmp(qr1->book.title,title)!= 0){
		qr1 = qr1->next;
		if(qr1->next == NULL)
		{
			printf("No book named this was found in this library\n");
			return NULL;
		}
	}
	while (strcmp(qr1->book.title,title) == 0)
	{
		return qr1;
	}
	return NULL;
}

BookArray *find_book_by_author (const char *author,BookArray *head)
{
	BookArray *qr2 = head->next;
	if(head->next == NULL)
	{
		printf("There is no book in this library!\n");
		return NULL;
	}
	if(strcmp(qr2->book.authors,author) != 0){
		qr2=qr2->next;
		if(qr2->next = NULL)
		{
			printf("No book named this was found in this library\n");
			return NULL;
		}	
	}
	else if(strcmp(qr2->book.authors,author) == 0)
	{
		return qr2;
	}
	return NULL;
}

BookArray *find_book_by_year (unsigned int year,BookArray *head)
{
	BookArray *qr3 = head->next;
	int i = 0;
	while(i<head->length)
	{
		if(qr3->book.year != year)
		{
			qr3 = qr3->next;
		}
		else
		{
			return qr3;
		}
	}
	return NULL;
 } 
 


