#include <stdio.h>
#include <stdlib.h>
//Doubly Linked List
struct node
{
	struct node *prev;
	int data;
	struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;

void display();
void insert_beg();
void insert_end();
void delete_beg();
void delete_end();
void insert_after();
void insert_before();
void delete_key();
void sort();

void main() {
	int option;
	do
	{
		printf("\n\n 1: Display the list");
		printf("\n 2: Insert at the beginning");
		printf("\n 3: Insert at the end");
		printf("\n 4: Delete from the beginning");
		printf("\n 5: Delete from the end");
		printf("\n 6: Insert after");
		printf("\n 7: Insert before");
		printf("\n 8: Delete key");
		printf("\n 9: Sort List");

		printf("\n 0: EXIT");
		printf("\n\n Enter your option : ");
		scanf_s("%d", &option);
		switch (option)
		{
			case 1: display();	  break;
			case 2: insert_beg(); break;
			case 3: insert_end(); break;
			case 4: delete_beg(); break;
			case 5: delete_end(); break;
			case 6: insert_after(); break;
			case 7: insert_before(); break;
			case 8: delete_key(); break;
			case 9: sort(); break;
		}
	} while (option != 0);
	return;
}

void display(){
	struct node *ptr = tail;
	if (ptr == NULL)
	{
		printf("\nList is empty!");
	}
	else{
		while(ptr != NULL)
		{
			printf("\t%d", ptr->data);
			ptr = ptr->prev;
		}
	}
	printf("\n");
}

void insert_beg(){
	struct node *ptr;
	ptr = (struct node *)malloc(sizeof(struct node));

	if (ptr == NULL)
	{
		printf("\nThere is an error in Malloc!");
	}
	else{
		printf("\nEnter the node data value: ");
		scanf_s("%d",&ptr->data);

		if (head == NULL)
		{
			ptr->next = NULL;
			head = ptr;
			tail = head;
		}
		else{
			ptr->prev = NULL;
			ptr->next = head;
			head->prev = ptr;

			head = ptr;
		}
	}
}

void insert_end(){
	struct node *ptr;
	ptr = (struct node *)malloc(sizeof(struct node));

	if (ptr == NULL)
	{
		printf("\nThere is an error in Malloc!");
	}
	else{
		printf("\nEnter the node data value: ");
		scanf_s("%d",&ptr->data);

		if (head == NULL)
		{
			ptr->prev = NULL;
			ptr->next = NULL;
			head = ptr;
			tail = head;
		}
		else{
			struct node *temp = head;
			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = ptr;
			ptr->prev = temp;
			ptr->next = NULL;
			tail = ptr;
		}
	}
}

void delete_beg(){
	struct node *ptr=head;
	if (head == NULL)
	{
		printf("\nThere isn't any element in the list!");
	}
	else{
		head = head->next;
		ptr->next = NULL;
		head->prev = NULL;
		free(ptr);
		printf("\nFirst node is deleted!");
	}
}

void delete_end(){
	struct node *ptr, *temp;
	if (head == NULL)
	{
		printf("\nThere isn't any element in the list!");
	}
	else if(head->next == NULL){
		free(head);
		head = NULL;
		tail = NULL;
	}
	else{
		temp = head;
		ptr = temp->next;

		while(ptr->next !=NULL){
			temp = temp->next;
			ptr = ptr->next;
		}
		temp->next = NULL;
		ptr->prev = NULL;
		free(ptr);
		tail = temp;
	}
}

void insert_after() {
	struct node* p;
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	int keynode;
	p = head;

	printf("\nEnter the key you want to insert after: ");
	scanf("%d", &keynode);

	while (p) {
		if (keynode == p->data) {
			printf("\nEnter the data value of the node: ");
			scanf("%d", &new_node->data);
			break;
		}
		p = p->next;
	}

	if (p == NULL)
	{
		printf("\nThe key is not in the list!\n");
		return;
	}

	else {

		new_node->prev = p->prev;
		p->prev = new_node;
		new_node->next = p;

		if (new_node->prev != NULL)
			new_node->prev->next = new_node;
	}
	return new_node;
}
void insert_before() {
	struct node* p;
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	int keynode;
	p = head;

	printf("\nEnter the key you want to insert before: ");
	scanf("%d", &keynode);

	while (p) {
		if (keynode == p->data) {
			printf("\nEnter the node data value: ");
			scanf("%d", &new_node->data);
			break;
		}
		p = p->next;
	}

	if (p == NULL)
	{
		printf("\nThe key is not in the list!\n");
		return;
	}

	else {
		new_node->next = p->next;
		p->next = new_node;
		new_node->prev = p;

		if (new_node->next != NULL)
			new_node->next->prev = new_node;
	}
	return new_node;
}
void delete_key() {
	struct node* p;
	int keynode;
	p = head;

	printf("\nEnter the key you want to delete: ");
	scanf("%d", &keynode);

	while (p) {
		if (keynode == p->data) {
			break;
		}
		p = p->next;
	}

	if (p == NULL) {
		printf("\nThe element to be deleted is not in the list\n");
			return NULL;
	}
	if (p == head) {
		if (head == tail) {
			head = NULL;
			tail = NULL;
		}
		else {
			head = p->next;
			head->prev = NULL;
		}
	}
	else {
		if (p == tail) {
			tail = p->prev;
			tail->next = NULL;
		}
		else {
			p->prev->next = p->next;
			p->next->prev = p->prev;
		}
	}
	free(p);
	return p;

}
void sort() {
	int swap;
	struct node* ptr;
	struct node* lptr = NULL;
	if (head == NULL)
		return;
	do{ 
		ptr = head;
		swap = 0;
		while (ptr->next != lptr)
		{
			if (ptr->data < ptr->next->data)
			{
				int temp = ptr->data;
				ptr->data = ptr->next->data;
				ptr->next->data = temp;
				swap = 1;
			}
			ptr = ptr->next;
		}
		lptr = ptr;
	} while (swap);
}
