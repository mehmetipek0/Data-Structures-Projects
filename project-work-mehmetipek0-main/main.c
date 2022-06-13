#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define sortSize 10000
#define dataSize 1000
#define tableSize 4987

typedef struct srt{
	char password[20];
}PASS;
PASS data[sortSize];

typedef struct hsh{
	char password[20];
}PASS_H;
PASS_H data_h[dataSize];
PASS_H table[tableSize];

typedef struct list{
	char password[20];
	int rating;
	struct list *next;
}PASS_L;
PASS_L* first = NULL;
PASS_L* last = NULL;

typedef struct stack{
	char password[20];
	int rating;
	struct stack* next;
}PASS_S;
PASS_S* sp = NULL;


void password_searching();
int password_reading_for_sorting();
void sort_data_ascending();
void sort_data_descending();
void initialize_hash_table();
int hashing_password(char* password);
int insert_table();
void search_password_hash();
int push(PASS_L* data);
void pop();
void insert_password_list();
int rate_password_list(char* password);
void sort_list(PASS_L *first);


int main() {
	int choice = 1,flag;

	while(choice){
		flag = 1;
		system("cls");
		printf("Please enter your decision.\n1.Searching.\n2.Sorting.\n");
		printf("3.Hashing.\n4.Linked List.\n0.Exit\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				system("cls");
				while(flag){
					flag = 0;
					system("cls");
					password_searching();
					printf("Do you want to search again?(enter '1' for yes, '0' for no)\n");
					scanf("%d",&flag);
					printf("\n");
				}
				break;
			
			case 2:
				system("cls");
				password_reading_for_sorting();
				sort_data_ascending(data, sortSize);
				password_reading_for_sorting();
				sort_data_descending(data, sortSize);
				system("pause");
				break;
			
			case 3:
				while(flag){
					flag = 0;
					system("cls");
					initialize_hash_table();
					insert_table();
					search_password_hash();
					printf("\nDo you want to search again?(enter '1' for yes, '0' for no)\n");
					scanf("%d",&flag);
					printf("\n");
				}
				break;
			
			case 4:
				system("cls");
				insert_password_list();
				system("pause");
				break;
				
			default:
				if(choice){
					printf("Please enter a valid value!\n");
					system("pause");
				}
				break;
		}
	}
	
	return 0;
}


//SEARCHING
void password_searching(){
	//defining and opening file
	char data[30], password[30];
	int found = 0, choice = 1;
	FILE* f;
	f = fopen("10-million-password-list-top/100000.txt","r");
	//reading and comparing data by given password	

	printf("Enter a password to search:\n");
	scanf("%s", password);
	while(!feof(f)){
		
		fscanf(f, "%s", data);
		if(strcmp(password, data) == 0){
			printf("Password is in the list!\n\n");	
			found = 1;
		}	
	}
	
	if(found != 1){
			printf("\nPassword is in not the list!\n");
	}

	
	fclose(f);	
}


//SORTING
int password_reading_for_sorting(){
	//defining and reading
	int i = 0;
	FILE* f;
	f = fopen("10-million-password-list-top/10000.txt","r");
	
	while(!feof(f)){
		fscanf(f, "%s\n", &data[i].password);
		i++;
	}
	
	fclose(f);
	return 0;
}


void sort_data_ascending(struct srt data[], int size){
    int i, changed;
    printf("Data is sorting ascending order...\n");
    PASS temp;
	do{
        changed = 0;
        for (i=0; i<(size)-1; i++)
        {
            if (strcmp(data[i].password, data[i+1].password) > 0)
            {
                memcpy(&temp, data + i, sizeof (struct srt));
                memcpy(data + i, data + i + 1, sizeof (struct srt));
                memcpy(data + i + 1, &temp, sizeof (struct srt));
                changed = 1;
           }
        }
    }while (changed != 0);
    
	for(i=0; i<10; i++){
		printf("%d.\t%s\n",i+1,data[i].password);
	}
}


void sort_data_descending(struct srt data[], int size){
	int i, changed;
	printf("\nData is sorting descending order...\n");
    PASS temp;
   do{
        changed = 0;
        for (i=0; i<(size)-1; i++)
        {
            if (strcmp(data[i].password, data[i+1].password) <= 0)
            {
                memcpy(&temp, data + i, sizeof (struct srt));
                memcpy(data + i, data + i + 1, sizeof (struct srt));
                memcpy(data + i + 1, &temp, sizeof (struct srt));
                changed = 1;
           }
        }
	}while (changed != 0);
	
	for(i=0; i<10; i++){
		printf("%d.\t%s\n",i+1,data[i].password);
	}
}


//HASHING
void initialize_hash_table(){
	int i;
	FILE* f;
	f = fopen("10-million-password-list-top/1000.txt","r");
	
	printf("\nPreparing hash table...\n\n");
	
	for(i=0; i<tableSize; i++){
		strcpy(table[i].password,"");
	}
	i = 0;

	while(!feof(f)){
		fscanf(f, "%s", data_h[i].password);
		i++;
	}

	fclose(f);
	printf("Prepared.\n\n");
}


int hashing_password(char* password){
	int hashVal = 0, i = 0;
	
	while(password[i]!='\0'){
		hashVal = hashVal + pow(password[i],3);
		i++;
	}
	hashVal = hashVal % tableSize;

	if(hashVal < 0){   //in case overflows occurs
		hashVal += tableSize;
	}

	return hashVal;
}


int insert_table(){
	int hashVal, i, collision = 0; 
	
	for(i = 0; i<tableSize;i++){
		hashVal = hashing_password(data_h[i].password);
		
		if(strcmp(table[hashVal].password,"") == 0){
			strcpy(table[hashVal].password, data_h[i].password);
		}
		
		else{
			collision++;
			int k = 1;
			while(k<tableSize){
				hashVal = hashVal + k*k;
				hashVal = hashVal % tableSize;
				if(strcmp(table[hashVal].password,"") == 0){
					strcpy(table[hashVal].password, data[i].password);
					break;
				}
				k++;
			}		
		}
	}
	
	printf("Collision count is %d.\n\n", collision);
	return 0;
}


void search_password_hash(){
	int i = 1, hashVal, flag = 0, collision = 0;;
	char password[30];
	
	printf("Please enter your password for searching in hash table:\n");
	scanf("%s",password);		
	hashVal = hashing_password(password);	
		
	if(strcmp(table[hashVal].password,password) == 0){
		printf("Password is found!\n");
		printf("Collision count for that search is %d.",collision);
		flag = 1;
	}
	else{
		while(i<tableSize/2){
			collision++;
			hashVal = hashVal + i*i;
			hashVal = hashVal % tableSize;
			if(strcmp(table[hashVal].password,password) == 0){
				printf("Password is found!\n");
				printf("Collision count for that search is %d.\n",collision);
				flag = 1;
			}
			i++;
		}			
	}
	if(flag != 1){
		printf("Password is not found.\n");
	}	
}


//LINKED LIST
void insert_password_list(){
	int i = 0;
	PASS_L* list;
	list = (PASS_L*)malloc(sizeof(PASS_L));	
	
	FILE* f;
	f = fopen("10-million-password-list-top/1000.txt", "r");
	
	while(!feof(f)){
		if(first == NULL){
			fscanf(f,"%s",&list->password);
			last = list;
			first = list;
			list->next = NULL;
		}
		
		else{
			list = (PASS_L*)malloc(sizeof(PASS_L));
			fscanf(f,"%s",&list->password);
			last->next = list;
			list->next = NULL;
			last = list;
			
		}
	}
	
	PASS_L* p;
	p = first;
	while(p!=NULL){
		p->rating = rate_password_list(p->password);
		p = p->next;		
	}
	p = first;
	sort_list(p);
	
	printf("Top 10 most weakest passwords:\n");
	for(i = 0;i < 10;i++){
		printf("%d: rate = %d\t%s\n",i+1, p->rating, p->password);
		p = p->next;		
	}
	p = first;
		
	while(p != NULL){
		push(p);
		p = p->next;
	}
	
	printf("\nTop 10 most strongest passwords:\n");
	for(i = 0;i < 10;i++){
		printf("%d: ",i+1);
		pop();
	}
	
	fclose(f);
}


void sort_list(PASS_L *first){ 
    int swapped, i,temp;
    PASS_L *ptr1; 
    PASS_L *lptr = NULL; 

    do
    { 
        swapped = 0; 
        ptr1 = first; 
        while (ptr1->next != lptr) { 
        	
            if (ptr1->rating > ptr1->next->rating) {  
				temp = ptr1->rating;
				ptr1->rating = ptr1->next->rating;
				ptr1->next->rating = temp;
				
				char tempc[20]; 
				strcpy(tempc,ptr1->password);
				strcpy(ptr1->password,ptr1->next->password);
				strcpy(ptr1->next->password,tempc);
                
				swapped = 1; 
            } 
            ptr1 = ptr1->next; 
        } 
        lptr = ptr1; 
    } 
    while (swapped); 
} 


int rate_password_list(char* password){
	int i = 0,rating = 0;
	int hasNumber = 0,hasLetter = 0,hasUpper = 0,hasLower = 0,numbercnt = 0,lettercnt = 0;
	
	rating = rating + strlen(password); 

	while(password[i]!='\0'){
		if(isdigit(password[i]))
			numbercnt++;
			hasNumber = 1;
		if(isalpha(password[i]))
			lettercnt++;
			hasLetter = 1;
		if(isupper(password[i]))
			hasUpper = 1;		
		if(islower(password[i]))
			hasLower = 1;
		
		i++;
	}	
	
	
	if(hasNumber && hasLetter && hasUpper && hasLower){    //if password contains upper letter, lower letter and number
		rating = rating * 11;		
	}
	if(!hasNumber && hasLetter && hasUpper && hasLower){	 //if password contains upper letter and lower letter 
		rating = rating * 9; 
	}
	if(hasNumber && hasLetter && !hasUpper && hasLower){	 //if password contains number and lower letter 
		rating = rating * 7; 
	}
	if(!hasNumber && hasLetter && !hasUpper && hasLower){	 //if password contains only lower letter 
		rating = rating * 3; 
	}
	if(!hasNumber && !hasLetter){							 //if password contains only numbers 
		rating = rating * 1 ; 
	}
	
	if(numbercnt > 0 && lettercnt > 0)						 //because of add more score if letters are more 
		rating = rating + lettercnt;
	
	return rating;
}


int push(PASS_L* data){
	PASS_S* p;
	p = (PASS_S*)malloc(sizeof(PASS_S));
	
	if(p == NULL){
		printf("Error, not enough memory\n");
		return -1;
	}

	else{
		p->rating = data->rating;
		strcpy(p->password,data->password);
		p->next = sp;
		sp = p;
		return 0;
	}
	
}


void pop(){
	PASS_S* p;
	int rt;
	char ps[20];
	
	if(sp == NULL){
		printf("Stack is empty!\n");
	}
	
	else{
		p = sp;
		rt = sp->rating;
		strcpy(ps, sp->password);
		sp = sp->next;
		free(p);
	}
	
	printf(" rate = %d\t%s\n",rt,ps);
}
