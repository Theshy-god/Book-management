#include "book_management.h"
#include "user.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *search_title;
char *search_author;
int search_year;
int borrow_id;

BookArray *createheadnode()//create the book headnode;
{
	BookArray *head;
	head=(BookArray *)malloc(sizeof(BookArray));
	head->next=NULL;
	head->length = 0;
	return head;	
}
BookArray *createnode(Book books)//create the head(never used)
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
	
	BookArray *pmove = headnode2;
	BookArray *Newnode =(BookArray*)malloc(sizeof(BookArray));
	Newnode -> book = book;
	Newnode -> next = NULL; 
	while(headnode2 != NULL && pmove->next != NULL)
	{
		pmove=pmove->next;//if not move to the next;
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
	return 0;
	
}


int remove_book(Book book,BookArray *head)
{
	BookArray *qr,*q;//qr is front pointer!
	qr=head;
	q = head->next;
	
	int remove_id=atoi(ask_question("Please enter the id of the book that you want to remove:"));
	if(head->next == NULL)//there is no book in the library;
	{
		printf("There is no book in this library!\n") ;
	}
	while(q != NULL)
	{
	if(q->book.id == remove_id)
	{	
		qr->next = q->next;
		head->length -= 1;	
		free(q);
		printf("The book with id %i has been deleted!\n",remove_id);
		break;
	}
	else
	{
		qr = q;
		q = qr->next;
	}
	if(q == NULL)
	{
		printf("There are no such book in this library!\n");//if there is no such book id or input the wrong id;
	}
	}
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
		printf("%s\t\t",headnode->book.title);
		printf("%s\t\t",headnode->book.authors);
		printf("%i\t",headnode->book.year);
		printf("%i\n",headnode->book.copies);
		headnode=headnode->next;
} 
}

void ShowFindbook(BookArray *head)
{
		printf("ID\t");
		printf("Title\t\t");
		printf("Author\t\t");
		printf("Year\t");
		printf("Copies\n");
		printf("%i\t",head->book.id);
		printf("%s\t\t",head->book.title);
		printf("%s\t\t",head->book.authors);
		printf("%i\t",head->book.year);
		printf("%i\n",head->book.copies);

} 

void ShowBorrowbook(BookArray *head)
{
		printf("ID\t");
		printf("Title\t\t");
		printf("Author\t\t");
		printf("Year\t");
		printf("%i\t",head->book.id);
		printf("%s\t\t",head->book.title);
		printf("%s\t\t",head->book.authors);
		printf("%i\n",head->book.year);

} 
	
int store_books(BookArray* headnode){
    FILE*file;
    BookArray *p = headnode->next;
    file = fopen("file.txt", "wb");
    while(p)
    {
        fwrite(&(p->book.id), sizeof(int), 1,file);//store the id
        fwrite(p->book.title, 50*sizeof(char), 1,file);//store the title
        fwrite(p->book.authors, 50*sizeof(char), 1,file);//store the authors
        fwrite(&(p->book.year), sizeof(int), 1,file);//store the year
        fwrite(&(p->book.copies), sizeof(int), 1,file);//store the copies
        p=p->next;
    }
    fclose(file);
    return 0;
}

int load_books(BookArray* headnode){
    FILE*file;
    int a = 0;
    BookArray* q=headnode;
    if ((file=fopen("file.txt","rb"))==NULL)
    {
        file=fopen("file.txt","wb");
        fclose(file);
    }
    file = fopen("file.txt","rb");
    while (fread(&a,sizeof(int),1,file)) 
	{
        BookArray* p = (BookArray*)malloc(sizeof(BookArray));
        p->next=NULL;
        p->book.id = a;
        p->book.title =(char*)malloc(50*sizeof(char));//create the space for the title
        p->book.authors =(char*)malloc(50*sizeof(char));//create the space for the authors
        fread(p->book.title,50*sizeof(char),1,file);//load the title;
        fread(p->book.authors,50*sizeof(char),1,file);//load the authors;
        fread(&(p->book.year), sizeof(int), 1,file);//load the year;
        fread(&(p->book.copies), sizeof(int), 1,file);//load the copies;
        q->next=p;
        q=p;
        if(feof(file)) break;
    }
    if(headnode->next != NULL) 
	{
		return 0;
	}
    fclose(file);
}
BookArray *find_book_by_title (const char *title,BookArray *head)
{
	BookArray *qr1 = head->next;
	while(qr1 != NULL&&strcmp(qr1->book.title,title) != 0)
	{
		qr1 = qr1->next;
	}
	return qr1;//qr1 is the address of the title we want to find or null;
	
	
}

	

BookArray *find_book_by_author (const char *author,BookArray *head)
{
	BookArray *qr2 = head->next;
	while(qr2 != NULL&&strcmp(qr2->book.authors,author) != 0)
	{
		qr2 = qr2->next;
	}
	return qr2;//qr2 is the address of the author we want to find or null;
	
}

BookArray *find_book_by_year (unsigned int year,BookArray *head)
{
	BookArray *qr3 = head->next;
	while(qr3 != NULL&&qr3->book.year != year)
	{
		qr3 = qr3->next;
	}
	return qr3;//qr3 is the address of the year we want to find or null;
	
}


void Searchbook(BookArray *headnode)
{
	int Search_option =5;
	Book book;
	do {
		char * answer = ask_question("\nPlease choose an option:\n1)Find books by title:\n2)Find books by author:\n3)Find books by year:\n4)Return to the previous menu\nOption: ");
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
				printf("\nReturning to the previous menu...\n");
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
	BookArray *p =NULL;//it is the move pointer in the book;
	BookArray *pmove=NULL;//it is the move pointer  in the new linked list;
	BookArray *Newlist =NULL;//it is the new linked list
	p=find_book_by_title(search_title,headnode);
	Newlist=p;
	pmove=p;
		if( p == NULL)
	{
		printf("Invalid title!\n");
	}
	while(p != NULL)
	{
		p=find_book_by_title(search_title,p);//find next book which have the same title
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
	BookArray *p =NULL;//it is the move pointer in the book;
	BookArray *pmove=NULL;//it is the move pointer  in the new linked list;
	BookArray *Newlist =NULL;//it is the new linked list
	p=find_book_by_author(search_author,headnode);
	Newlist=p;
	pmove=p;
		if( p == NULL)
	{
		printf("Invalid author!\n");
	}
	while(p != NULL)
	{
		p=find_book_by_author(search_author,p);//find next book which have the same suthor;
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
	BookArray *p =NULL;//it is the move pointer in the book;
	BookArray *pmove=NULL;//it is the move pointer  in the new linked list;
	BookArray *Newlist =NULL;//it is the new linked list
	p=find_book_by_year(search_year,headnode);
	Newlist=p;
	pmove=p;
	if( p == NULL)
	{
		printf("Invalid year!\n");
	}
	while(p != NULL)
	{
		p=find_book_by_year(search_year,p);//find next book which have the same year;
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
 
 BookArray *find_book_by_id (unsigned int id,BookArray *head)
{
	BookArray *qr4 = head->next;
	while(qr4 != NULL&&qr4->book.id != id)
	{
		qr4 = qr4->next;
	}
	return qr4;//qr4 is the address of the book id we want to find or NULL;
	
}

void Borrow(UserLink *headNode,BookArray *headnode)
{
	
	Displaybook(headnode);
	BookArray *p =NULL;
	int i =0;
	int s = 0;
	int borrow_id=atoi(ask_question("Please enter the id of the book that you want to borrow:"));
	p=find_book_by_id(borrow_id,headnode);
	if(p == NULL)
	{
		printf("Invalid Input ID!\n");
		return;
	}
	else
	{
	for( i=0;i< headNode->userdata.number;i++)
	{
		if(headNode->userdata.borrow[i] == p->book.id)//if the book has already been borrowed.
		{
			printf("Sorry,you already have a copy of this book on loan\n");
			return;
		}
	}
	if(p->book.copies > 0 &&  headNode->userdata.number < 10)//the users can only borrow when the copies more than zero and his(her) usernumber less or equal to 10;
	{
        p->book.copies--;
        headNode->userdata.borrow[headNode->userdata.number] = p->book.id;
      //  headNode->userdata.books.id = p->book.id;
        headNode->userdata.number   ++;
        printf("Borrowed succeeded. \n");
    }
	else
	{
        printf("Sorry, you can not borrow this book.\n");
    }

}
}
void Return_book(UserLink *find,BookArray *headnode)
{
	int n = 0;
    int i = 0;
    int j =0;
    int s = 0;
    BookArray *pi = NULL;
    BookArray *show = NULL;
    printf("\nThe books you have borrowed: \n");
    for(n=0;n< find->userdata.number;n++)
	{
        show=find_book_by_id(find->userdata.borrow[n],headnode);//first display the books you have already borrowed;
        ShowBorrowbook(show);
    }
    
    n=0;
    int answer = atoi(ask_question("\nThe id of book you want to return: "));
   	pi =find_book_by_id(answer,headnode);
	while(n<find->userdata.number)
	{
        if(find->userdata.borrow[n] == answer)
		 {    
        	for(j=n;j <= find->userdata.number;j++)
        	{
        		find->userdata.borrow[j] = find->userdata.borrow[j+1];//When the book is changed, the subscript of the array is reconstructed.
			}
			s=1;
            find->userdata.number --;
            pi->book.copies ++;
            break;
        }
        
    n++;   
    }
    if(s==1)
    {
    	printf("Successfully returned!\n");
	}
	else{
		printf("\nInvalid Return ID\n");
	}
}


