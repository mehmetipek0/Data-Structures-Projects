#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define dataSize 273
#define tableSize 273

typedef struct{
	char name[25];
	int no;
	int grade;
	
}STUDENT;
STUDENT table[tableSize];

int TableSize = 273;
int collision = 0;

void readStudentData(STUDENT* student);
void ShowandClearTable();
int insertTableQP(STUDENT student, int size, int selection);
int insertTableLP(STUDENT student,int size, int selection);
int hashingNumberMod(int studentNo);
int hashingNameSquareMod(char* name);
int hashingGradeMod(int studentGrade);
int hashingNameTruncation(char* studentName);
int hashingNameFolding(char* studentName);

int main(){
	setlocale(LC_ALL, "Turkish");
	int i;
	STUDENT students[dataSize];
	
	readStudentData(students);
	
	//HASHING WITH LINEAR PROBING
	printf("TableSize is 273 for each array. \nCollision resolution type is Linear Probing.\n\n");
	printf("Number modding hash function:\n");
	for(i=0;i<273;i++){
		insertTableLP(students[i],TableSize,1);  //HASHING 1
	}
	ShowandClearTable();

	printf("Name square modding hash function:\n");
	for(i=0;i<273;i++){
		insertTableLP(students[i],TableSize,2);   //HASHING 2
	}
	ShowandClearTable();
	
	printf("Grade modding hash function:\n");
	for(i=0;i<273;i++){
		insertTableLP(students[i],TableSize,3);   //HASHING 3
	}
	ShowandClearTable();
	
	printf("Name truncation hash function:\n");
	for(i=0;i<273;i++){
		insertTableLP(students[i],TableSize,4);   //HASHING 4
	}
	ShowandClearTable();
	
	printf("Name folding hash function:\n");
	for(i=0;i<273;i++){
		insertTableLP(students[i],TableSize,5);   //HASHING 5
	}
	ShowandClearTable();

	
	//HASHING WITH QUADRATIC PROBING
	printf("TableSize is 273 for each array. \nCollision resolution type is Quadratic Probing.\n\n");
	printf("Number modding hash function:\n");
	for(i=0;i<273;i++){
		insertTableQP(students[i],TableSize,1);   //HASHING 1
	}
	ShowandClearTable();

	printf("Name square modding hash function:\n");
	for(i=0;i<273;i++){
		insertTableQP(students[i],TableSize,2);   //HASHING 2
	}
	ShowandClearTable();
	
	printf("Grade modding hash function:\n");
	for(i=0;i<273;i++){
		insertTableQP(students[i],TableSize,3);   //HASHING 3
	}
	ShowandClearTable();
	
	printf("Name truncation hash function:\n");
	for(i=0;i<273;i++){
		insertTableQP(students[i],TableSize,4);   //HASHING 4
	}
	ShowandClearTable();
	
	printf("Name folding hash function:\n");
	for(i=0;i<273;i++){
		insertTableQP(students[i],TableSize,5);   //HASHING 5
	}
	ShowandClearTable();
	printf("\nWhen table size is 273, the best hash function is Key mod N \n(number modding) hashing with numbers.\n ");
	

	return 0;
}


int insertTableQP(STUDENT student,int size, int selection){
	int x;
	switch (selection){
			case 1:
				x = hashingNumberMod(student.no);
				break;
			case 2:
				x = hashingNameSquareMod(student.name);
				break;
			case 3:
				x = hashingGradeMod(student.grade);
				break;	
			case 4:
				x=hashingNameTruncation(student.name);
				break;
			case 5:
				x=hashingNameFolding(student.name);
				break;
	}			
	if(strcmp(table[x].name, "") == 0){
		table[x].no = student.no;
		strcpy(table[x].name, student.name);
		table[x].grade = student.grade;
		return 1;
	}
	else{
		collision++;
		int i = 1;
		while (i < size){
			x = x+i*i;
			x = x % size;
			if(strcmp(table[x].name, "") == 0){
				table[x].no = student.no;
				strcpy(table[x].name, student.name);
				table[x].grade = student.grade;
				return 1;
			}
			i++;
		}
		return 1;
	}	
}
int insertTableLP(STUDENT student,int size, int selection){
	int x;
	switch (selection){
			case 1:
				x = hashingNumberMod(student.no);
				break;
			case 2:
				x = hashingNameSquareMod(student.name);
				break;
			case 3:
				x = hashingGradeMod(student.grade);
				break;	
			case 4:
				x=hashingNameTruncation(student.name);
				break;
			case 5:
				x=hashingNameFolding(student.name);
				break;
	}			
	if(strcmp(table[x].name, "") == 0){
		table[x].no = student.no;
		strcpy(table[x].name, student.name);
		table[x].grade = student.grade;
		return 1;
	}
	else{
		collision++;
		int i = 1;
		while (i < size){
			x = x+i;
			x = x % size;
			if(strcmp(table[x].name, "") == 0){
				table[x].no = student.no;
				strcpy(table[x].name, student.name);
				table[x].grade = student.grade;
				return 1;
			}
			i++;
		}
		return 1;
	}	
}
void ShowandClearTable(){
	int i;
	printf("There are %d collisions\n\n",collision);
	collision=0;
	for(i=0;i<TableSize;i++){
		table[i].no=0;
		strcpy(table[i].name, "");
		table[i].grade=0;
	}
}
int hashingNumberMod(int studentNo){
	return ((studentNo%7919)*1091)%TableSize;
}
int hashingNameSquareMod(char* name){
	int hashVal=0,i,a;
	for(i=0;name[i]!='\0';i++){
		a = name[i]*name[i];
		hashVal = hashVal+a;
	}
	hashVal = hashVal % TableSize;
	if(hashVal<0)
		hashVal += TableSize;
	return hashVal;
}
int hashingGradeMod(int studentGrade){
	int hashVal = 0, i;
	hashVal = ((studentGrade*563)%673);
	return hashVal % TableSize;
}
int hashingNameTruncation(char* studentName){
	int hashVal = 0;
	hashVal = studentName[3]+studentName[5]+studentName[7];
	return hashVal % TableSize;
}
int hashingNameFolding(char* studentName){
	int i,hashVal = 0,a,b,c;
	a=studentName[0]+studentName[1]+studentName[2];
	b=studentName[3]+studentName[4]+studentName[5];
	c=studentName[6]+studentName[7]+studentName[8];
	hashVal = a+b+c;
	return hashVal % TableSize;
}
void readStudentData(STUDENT* student) {
	int* size;
	int i = 0;
	FILE* f;
	f = fopen("data.txt", "r");
	while (!feof(f)) {
		if(i==0){
			fscanf(f,"%d\n",&size);
		}	
		fscanf(f, "%d,%[^,],%d\n", &student[i].no, student[i].name, &student[i].grade);
		i++;
	}
	fclose(f);
}
