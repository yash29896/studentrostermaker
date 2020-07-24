#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_LENGTH 13
#define MAX_SUB 20

struct student{
	size_t noClass;
	char **classTaken;	
};
struct node{
	struct student* details; 
	struct node* next;
	char* name;
};
struct classData{
	int count;
	char sub[MAX_LENGTH];
};

void tstpt(void);
void prgmSt(void);
void initHead(void);
void scanCheck(int tst);
void alloCheck(void* ptr);
void inputCheck(int x);
void init(struct node** wptr);
void enterClassNo(struct node** yptr);
void enterName(struct node** xptr);
void enterClassTaken(struct node** zptr);
void checkStrDup(struct node** vptr);
int checkIn(char *str, char **arr, size_t N); 
struct classData* resolve(void);
int checkInArray( char* chara, struct classData* test, int N);
char** finalAlloc(struct classData* result);
void fileCreate(struct classData *result, char** final);
void headReset(void); 
void freeAll(void);

struct node *head=NULL;
struct node *headrst=NULL;
char **studentNames;
size_t noOfStudents = 0;
int studentNo = 0;
int cnt2=0;
int cnt3=0;
int cnt4=0;
int cnt5=0;

//resolve() returns an array of struct classData, having entries "sub[subject]" and "count[total hits in linked list]"
struct classData* resolve(void){
	struct classData *mydata = malloc(sizeof( *mydata )*MAX_SUB);//
	struct node* tmp1=head;
	struct node* tmp2=head;
	int cnt=0,x=0,flag=0;
	while(tmp1!=NULL){
	for(size_t i=0; i<tmp1->details->noClass; i++){
		while(tmp2!=NULL){
		if(tmp2!=tmp1){
			x = checkIn(tmp1->details->classTaken[i], tmp2->details->classTaken, tmp2->details->noClass );
			if(x!=-1){
				cnt++;
				flag=1;
			}
		}
		tmp2=tmp2->next;
		}
		if(flag == 0 && (checkInArray(tmp1->details->classTaken[i], mydata, cnt2)==-1) ){
			strncpy(mydata[cnt2].sub, tmp1->details->classTaken[i], MAX_LENGTH) ;
		    mydata[cnt2].count=cnt+1; 
			cnt2++;
		}
		if(flag==1 &&(checkInArray(tmp1->details->classTaken[i], mydata, cnt2)==-1)){
			strncpy(mydata[cnt2].sub, tmp1->details->classTaken[i], MAX_LENGTH) ;
			mydata[cnt2].count=cnt+1;
			flag=0;
			cnt2++;
		}
		cnt=0;
		tmp2=head;
		}
	    tmp1=tmp1->next;
}
	return mydata;
}	
//checkInArray returns a -1 if given str is not present in array of structs "test" else it returns 0
int checkInArray( char* chara, struct classData* test, int N){
    for(int i=0;i<N;i++){
        if(strcmp(chara, test[i].sub)==0){
            return 0;
        }
    }
    return -1;
}
//checkIn returns a -1 if given str is not present in array of (struct classData) else it returns the position in "details->classTaken" it is present
int checkIn(char *str, char **arr, size_t N){
	for(size_t i=0; i<N; i++){
		if (strcmp(str, arr[i])==0){
			return i;
		}
	}
	return -1;
}
//error control for malloc/realloc
void alloCheck(void* ptr){
	if(ptr==NULL){
				perror("ERROR ALLOCATING MEMORY:");
				exit(EXIT_FAILURE);
			}
}
//error control for scanf
void scanCheck(int tst){
	if(tst!=1){
		perror("SCANF ERROR:");
		exit(EXIT_FAILURE);
	}
}
//error control for string duplication in classes a particular student attended autocorrect repitition and details->noClass
void checkStrDup(struct node** vptr){
	int paraA = (*vptr)->details->noClass;
	int flag,cntr=0;
	for(int i=0;i<paraA-1;i++){ 
		for(int j=i; j<paraA-1; j++ ){
			if(strcmp((*vptr)->details->classTaken[i],"\0")!=0){
			        if(strcmp((*vptr)->details->classTaken[i], (*vptr)->details->classTaken[j+1])==0){
				        flag = 1;
					    strncpy((*vptr)->details->classTaken[j+1], "\0", MAX_LENGTH);
				        }
		    }
		}
	}
	if (flag==1){
    for(int i=0;i<paraA;i++){
		if(strcmp((*vptr)->details->classTaken[i],"\0")!=0){ 
			(*vptr)->details->classTaken[cntr] = (*vptr)->details->classTaken[i];
		cntr++;
		}
	}
	(*vptr)->details->classTaken = realloc((*vptr)->details->classTaken,cntr);
	(*vptr)->details->noClass = cntr;
	}
}
//exits program in case of invalid input
void inputCheck(int x){
	if(x){
		fprintf(stdout,"INVALID INPUT");
		exit(EXIT_FAILURE);
	}
}
//brings head node to default position
void headReset(void){
	head = headrst;
}
//enter name of the student 
void enterName(struct node** xptr){
	printf("\nEnter the name of Student(%d)(max 12)= ",studentNo+1);
		(*xptr)->name=malloc(MAX_LENGTH);
		    alloCheck((*xptr)->name);
		    scanCheck(scanf("%s", (*xptr)->name));
		studentNames[studentNo] = (*xptr)->name;
		studentNo++;
}
//enter the number of classes he attended
void enterClassNo(struct node** yptr){
	printf("\nEnter the number of Classes he attended= ");	
			scanCheck(scanf("%zu",&((*yptr)->details->noClass)));
}
//enter the respective classes 
void enterClassTaken(struct node** zptr){
	(*zptr)->details->classTaken = malloc(((*zptr)->details->noClass)*sizeof(char *)); //Assumed MAX_LIMIT of 12+1 characters for sub name
        alloCheck((*zptr)->details->classTaken);	
		for(size_t  j=0; j<((*zptr)->details->noClass); j++){
            (*zptr)->details->classTaken[j] = malloc(MAX_LENGTH*sizeof(char));
                alloCheck((*zptr)->details->classTaken[j]);
			printf("\nEnter class(%zu)(MAX 12 CHARACTERS) = ",j+1);
			scanCheck(scanf("%s",(*zptr)->details->classTaken[j]));
		}
}
//initialize linked list
void init(struct node** wptr){
	*wptr=malloc(sizeof(struct node));
	    alloCheck(wptr);
    (*wptr)->details = malloc(sizeof(struct student));
	    alloCheck((*wptr)->details);
	(*wptr)->next = NULL;
}
//free memory allocated to linked list only 
void freeAll(void){
	struct node *tstptr1=NULL;
	struct node *tstptr2=NULL;
	headReset();
	free(studentNames);
    tstptr1=head->next;
	tstptr2=head;
	while(tstptr1!=NULL ){
		free(tstptr1->name);
		for(size_t  j=0; j<(tstptr1->details->noClass); j++){
            free(tstptr1->details->classTaken[j]);
		}
		free(tstptr1->details->classTaken);
		free(tstptr1->details);
		free(tstptr1);
		tstptr1=tstptr2;
		if(tstptr2!=NULL){
			tstptr2=tstptr2->next;
		}
	}
}
void fileCreate(struct classData *result, char** final){
	char str[MAX_LENGTH+16];
	int a=0;
	for(int i=0; i<cnt2+1; i++){
	if(i!=0){
		strncpy(str, result[cnt5].sub, MAX_LENGTH+16 ); 
		strcat(str,".roster.txt");
		a = result[cnt5].count;
		cnt5++;
	}else{
		strncpy(str, "students.roster.txt", MAX_LENGTH+16);
	}
	int m=0;
	FILE *f = fopen(str, "w");
	    alloCheck(f);
	if(i==0){
	fprintf(f, "studentNames={");
	for(size_t k=0; k<noOfStudents; k++){
		fprintf(f, "%s ", studentNames[k]);
	}
	fprintf(f, "}");
	//onlyfor student.roster.txt
	while(head!=NULL){
		fprintf(f, "\n------------------");
		fprintf(f, "\nStudent(%d)",m+1);
		m++;
		fprintf(f, "\n|||name=%s|||",head->name);
		fprintf(f, "\n|||Attended=%zu classes|||", head->details->noClass);
		fprintf(f, " \n|||He attended: " );
		for(size_t p=0; p<head->details->noClass; p++){
		fprintf(f, " %s ",head->details->classTaken[p]);
		}
		fprintf(f, "|||" );
		fprintf(f, "\n------------------");
		head = head->next;
	}
	}
	else{
		for(int j=0; j<a; j++){
			fprintf(f, "\n========%s========", str);
			fprintf(f, "\n------------------");
			fprintf(f, "\n|||STUDENT NAME : Student(%d)|||",j);
			fprintf(f,"\n%s",final[cnt4]);
			cnt4++;
			fprintf(f, "\n------------------");
		}
	}
	fclose(f);
	headReset();
}
}
//Takes the input and makes structs by inputing the data
void initHead(void){	
    init(&head);
	enterName(&head);
	enterClassNo(&head);
    enterClassTaken(&head);	
    checkStrDup(&head);	
}
//makes an array of student attending a particular subject in order, to be used with ctr2 ctr3
char** finalAlloc(struct classData* result){
	char **arr=NULL;
	int p=0;
    headReset();
	for(int i=0; i<cnt2; i++){
		while(head!=NULL){
			p=checkIn(result[i].sub, head->details->classTaken, head->details->noClass);
		if(p!=-1){
			arr=realloc(arr, sizeof(char *)*(cnt3+1));
			arr[cnt3]=malloc(MAX_LENGTH);
			strncpy(arr[cnt3] ,head->name, MAX_LENGTH);
		    cnt3++;
		}
		head=head->next;
		}
		headReset();
}
return arr;
}
//Creates the linked list
void prgmSt(void){
	struct node *tmp=NULL;
	    inputCheck((noOfStudents<=0)|(isdigit(noOfStudents)!=0));
	initHead();
    for(size_t i=0; i<noOfStudents-1; i++){//
		//init struct
		struct node * studenti =NULL;
		init(&studenti);    
		//studentname
        enterName(&studenti);
		//no of classes
		enterClassNo(&studenti);
		//classesTaken
		enterClassTaken(&studenti);
		//assignment
		checkStrDup(&studenti);
		//initialize ptr for subnames
		if(i==0){
			head->next = studenti;
			tmp = studenti;
		} else{
			tmp->next = studenti;
			tmp = studenti;
		}
		studenti = studenti->next;
	}	
	headrst = head;
}
//driver program
int main(void){
    setbuf(stdout, NULL);
	printf("\n+++++++++++++++ROSTER MAKER v0.1++++++++++++++++++");
	printf("\n++++++++++++++ CODED BY:YASH R K +++++++++++++++++");
	printf("\n==========MAX NUMBER OF SUBJECT:30================");
	printf("\n==MAX LETTERS IN STUDENT|SUBJECT NAME(NOSPACES):12==");
	printf("\nWhat is the no of students in class:: ");
	    scanCheck(scanf("%zu", &noOfStudents));
    studentNames=malloc(noOfStudents*MAX_LENGTH);
	    alloCheck(studentNames);
	prgmSt();
	struct classData *result = resolve();
    char **final = finalAlloc(result);
	fileCreate(result, final);
	for(int i=0; i<cnt3; i++){
	free(final[i]);
	}
	free(final);
	free(result);
	freeAll();
	return EXIT_SUCCESS;
}