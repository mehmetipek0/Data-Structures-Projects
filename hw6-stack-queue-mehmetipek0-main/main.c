#include <stdio.h>
#include <stdlib.h>

typedef struct dt{
	int item;
	struct dt *next;
}DATA;
DATA *front = NULL;
DATA *last = NULL;

typedef struct st{
	int item;
	struct st *next;
}STACK;
STACK *sp = NULL;


int push(int item);
int pop();
void reset_all();
void read_insertData(int line);
void insert_odd_to_stack();
void reverse_data();
void show_stack();
void show_queue();


int main() {
	int i;
	
	for(i=1;i<=10;i++){
		read_insertData(i);	
		printf("%d. line is:\n", i);
		show_queue();
		insert_odd_to_stack();
		printf("\nReversing the order of the odd integers:\n");
		reverse_data();
		show_queue();
		reset_all();
		printf("\n\n\n");	
	}
	
	system("PAUSE");
	return 0;

}


int push(int item){
	STACK* p;
	p = (STACK*)malloc(sizeof(STACK));
	if(p == NULL){
		printf("Error, not enough memory\n");
		return -1;
	}
	else{
		p->item = item;
		p->next = sp;
		sp = p;
		return 0;
	}
}

int pop(){
	STACK* p;
	int i;
	if (sp == NULL){
		printf("Stack is empty\n");
		return -1;
	}
	else{
		p = sp;
		i = sp->item;
		sp = sp->next;
		free(p);
		return i;
	}
}

void reset_all(){
	STACK* p;
	DATA* t;
	while(sp != NULL){
		p = sp;
		sp = sp->next;
		free(p);
	}
	t = front;
	while(t != NULL){
		front = front->next;
		free(t);
		t = front;
	}
	last = NULL;
}

void read_insertData(int line){
	int size, i = 0;
	DATA* temp;
	temp = (DATA*)malloc(sizeof(DATA));
	DATA* queue;
	queue = (DATA*)malloc(sizeof(DATA));
	FILE* f;
	f = fopen("data.txt", "r");
	fscanf(f,"%d",&size);
	
	for(i=0; i<(size*line)-10; i++){
		if(front == NULL){
			fscanf(f,"%d,",&temp->item);
			last = temp;
			front = temp;
			temp->next = NULL;
		}
		else{
			temp = (DATA*)malloc(sizeof(DATA));
			fscanf(f,"%d,",&temp->item);
			last->next = temp;
			temp->next = NULL;
			last = temp;
		}
	}
	
	front = NULL;
	last = NULL;
	
	for(i=0; i<10; i++){
		if(front == NULL){
			fscanf(f,"%d,",&queue->item);
			last = queue;
			front = queue;
			queue->next = NULL;
		}
		else{
			queue = (DATA*)malloc(sizeof(DATA));
			fscanf(f,"%d,",&queue->item);
			last->next = queue;
			queue->next = NULL;
			last = queue;
		}
	}
	
	fclose(f);
}

void insert_odd_to_stack(){
	DATA *p;
	p = front;
	printf("\nOdds: ");
	while(p != NULL){
		if(p->item%2 != 0){
			printf("%d ",p->item);
			push (p->item);
		}
		p = p->next;	
	}
}

void reverse_data(){
	DATA* p;
	STACK* t;
	p = front;
	t = sp;
	if (p == NULL){
		printf("Queue is empty\n");
	}
	if (sp == NULL){
		printf("Stack is empty\n");
	}
	while (p != NULL){
		if(p->item%2 != 0){
			p->item = pop();
		}
		p = p->next;
	}
}

void show_stack(){
		while(sp != NULL){
		printf("%d ", *sp);
		pop();
	}
}

void show_queue(){
	DATA* p;
	p = front;
	while(p != NULL){
		printf("%d ",p->item);
		p = p->next;
	}
}
