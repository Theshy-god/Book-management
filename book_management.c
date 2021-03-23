#include "book_management.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *title;
char *authors;
int year;
int copies; 

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
	BookArray *Newnode =(BookArray*)malloc(sizeof(BookArray));
//	Newnode->book=book;
//	Newnode->next=NULL;
	//headnode2 -> next = Newnode;
	Newnode -> book = book;
//	Newnode -> book.copies = 300; 
	Newnode -> next = NULL; 
	Newnode->book.id=atoi(ask_question("Enter the id of the book you wish to add:"));
	Newnode->book.title=ask_question("Enter the title of the book you wish to add:");
	Newnode->book.authors=ask_question("Enter the author of the book you wish to add:");
	Newnode->book.year=atoi(ask_question("Enter the year that the book you wish to add was released:"));
	Newnode->book.copies=atoi(ask_question("Enter the number of copies of the book you wish to add:"));
	BookArray *pmove = headnode2;
	/*if (pmove->next != NULL)
	{
		pmove= pmove->next;
	}
	if(pmove->next==NULL){
		pmove->next = Newnode;//此时Newnode成为链表的最后一个结点 要让他的next指向0； 
	}*/
/*	if(headnode2->next != NULL && pmove->next != NULL)
	{
		pmove=pmove->next;
	}
	if(headnode2->next == NULL)
	{
		headnode2->next=Newnode;
	}
	if(headnode2->next != NULL && pmove->next == NULL)
	{
		pmove->next =Newnode;
	}*/
/*	if(strcmp(Newnode->book.title,book.title == 0) ||strcmp(Newnode->book.year,book.year) == 0 ||strcmp(Newnode->book.authors,book.authors) == 0) 
	{
		book.copies += Newnode->book.copies;
		
	}*/
    Newnode->next=headnode2->next;
	headnode2->next=Newnode;
	printf("Book was successfully added!\n");
	return 1;
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


void Displaybook(BookArray *headnode)
{
	//headnode1=(BookArray *)malloc(sizeof(BookArray));
	//headnode1->next=NULL;
	//if (headnode == NULL)
//	headnode=createheadnode();
	if (headnode->next == NULL)
	{	
	printf("No books in the library\n");
		return;
	}
	headnode = headnode -> next;
//	printf("GGGHGGGGGGGGG");
	while(headnode !=NULL)
	{	
		printf("%i\t",headnode->book.id);
		printf("%s\t",headnode->book.title);
		printf("%s\t",headnode->book.authors);
		printf("%i\t",headnode->book.year);
		printf("%i\n",headnode->book.copies);
		headnode=headnode->next;
} 
	//printf("UIUIUIUIUIUIUIUIUIUIU");
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
BookArray *find_book_by_title (const char *title,BookArray *head)
{
	BookArray *qr1 = head ->next;
	while(qr1 != NULL&&qr1->book.title!= title)
	{
		qr1 = qr1->next;
	}
	return qr1;
	
}

BookArray *find_book_by_author (const char *author,BookArray *head)
{
	BookArray *qr2 = head->next;
	while(qr2 != NULL&&qr2->book.authors!= author)
	{
		qr2 = qr2->next;
	}
	return qr2;
	
}

BookArray *find_book_by_year (unsigned int year,BookArray *head)
{
	BookArray *qr3 = head->next;
	while(qr3 != NULL&&qr3->book.title!= title)
	{
		qr3 = qr3->next;
	}
	return qr3;
	
}
 
 
 


