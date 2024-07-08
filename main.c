#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>

struct Date{
 int Day;
 int Month;
 int Year;
};
struct Cocurricular{
 float sports;
 float contests;
 float quality;
};
typedef struct{
 int Roll;
 char Name[100];
 struct Date DateOfBirth;
 char Dept[100];
 char Section;
 float Grade;
 struct Cocurricular Extra;
}Student;

typedef struct{
 int field;
 int order;//1(for ascending) or -1(for descending)
}ControlSort;
/*
*/

char *optionArr[]={"Roll","Name","DateOfBirth","Dept","Section","Grade","Sports score","Contests Score","Quality Score"};
void displayOptions();
void addStudents(Student* stArr,int* n);
//formatted display
void printStudentTableHeader() ;
void printStudent(int i,const Student *student);
void displayStudents(const Student *stArr,int n);
//search students by property
void displayPropTypes(const char *label);
void giveFloatPropSearch(Student student,Student *filteredStudents,int *filteredCount,float propVal,float inputedVal );
void giveStringPropSearch(Student student,Student *filteredStudents,int *filteredCount,const char* propVal,const char* inputedVal);
void searchStudent(const Student *stArr,int n);
//delete student by roll
void deleteStudent(Student *stArr,int* n);
//sort students by property
int getCompValByField(const Student* a,const Student* b,int field);
int compareStudents(const void *a, const void *b,const void *control);
void swapStudents(Student* a,Student* b);
void generalSort(Student *stArr,int size,int (*compareFunction)(const void*,const void*,const void*),ControlSort *control);//this is the general sort function mentioned
void sortStudentLists(Student *stArr,int n);

//add student function
void addStudents(Student* stArr,int* n){
  printf("Please provide the number of students: ");
  scanf("%d",n);
  int studentNum=*n;
  stArr=realloc(stArr,studentNum*sizeof(Student));
  if(stArr==NULL){
   printf("Memory allocation failed!");
   exit(EXIT_FAILURE);
  }
  printf("Now enter their info respectively: \n");

  for(int i=0;i<studentNum;i++){
   printf("Info for student %d:\n",i+1);
   printf("Roll: ");
   scanf("%d",&stArr[i].Roll);

   printf("Name: ");
   fflush(stdin);
   gets(stArr[i].Name);

   printf("Date of Birth (please follow the specific format DD-MM-YYYY): ");
   scanf("%d-%d-%d",&stArr[i].DateOfBirth.Day,&stArr[i].DateOfBirth.Month,&stArr[i].DateOfBirth.Year);

   printf("Dept: ");
   fflush(stdin);
   gets(stArr[i].Dept);

   printf("Section: ");
   scanf("%c",&stArr[i].Section);

   printf("Grade: ");
   scanf("%f",&stArr[i].Grade);

   printf("Cocurricular Scores:\n");
      printf("\tSports score: ");
      scanf("%f",&stArr[i].Extra.sports);
      printf("\tContests score: ");
      scanf("%f",&stArr[i].Extra.contests);
      printf("\tQuality score: ");
      scanf("%f",&stArr[i].Extra.quality);
  }
}

//display students in formatted way
void printStudentTableHeader() {
    printf("| %-4s | %-7s | %-25s | %-10s | %-25s | %-8s | %-5s | %-43s |\n",
           "S/N", "Roll", "Name", "DOB", "Department", "Section", "Grade", "Cocurricular Scores");
}
void printStudent(int i,const Student *student) {
    printf("| %-4d | %-7d | %-25s | %02d-%02d-%04d | %-25s | %-8c | %-5.2f | sports-%.2f, contests-%.2f, quality-%.2f |\n",
           i+1, student->Roll, student->Name,
           student->DateOfBirth.Day, student->DateOfBirth.Month, student->DateOfBirth.Year,
           student->Dept, student->Section, student->Grade,
           student->Extra.sports, student->Extra.contests, student->Extra.quality);
}

void displayStudents(const Student *stArr,int n){
 if(n<1){
  printf("No student data to display! Please add the students first!\n");
  return;
 }
 printf("\nDisplaying Student informations: \n\n");
 printStudentTableHeader();
 for(int i=0;i<n;i++){
  printStudent(i,(stArr+i));
 }
}


//search students
void giveFloatPropSearch(Student student,Student *filteredStudents,int *filteredCount,float propVal,float inputedVal ){
  if(propVal==inputedVal){
    filteredStudents[*filteredCount]=student;
    ++(*filteredCount);
   }
}
void giveStringPropSearch(Student student,Student *filteredStudents,int *filteredCount,const char* propVal,const char* inputedVal){
  if(strcmp(propVal,inputedVal)==0){
    filteredStudents[*filteredCount]=student;
    ++(*filteredCount);
   }
}

void searchStudent(const Student *stArr,int n){
 int op,filteredCount=0;
 if(n<1){
  printf("No student data to search! Please add students first.\n");
  return;
 }

 displayPropTypes("search");
 scanf("%d",&op);
 Student *filteredStudents= (Student*)malloc(n*sizeof(Student));
 printf("Please Enter the value of %s: ",optionArr[op-1]);

 switch (op)
 {
 case 1:{
  int rollNum;
  scanf("%d",&rollNum);
  for(int i=0;i<n;i++){
   if(stArr[i].Roll==rollNum){
    filteredStudents[filteredCount]=stArr[i];
    ++filteredCount;
   }
  }
  break;
 }
 case 2:{
  char name[100];
  fflush(stdin);
  gets(name);
  for(int i=0;i<n;i++){
   giveStringPropSearch(stArr[i],filteredStudents,&filteredCount,stArr[i].Name,name);
  }
  break;
 }
 case 3:{
  struct Date inputedDOF;
  printf("\nplease follow the format DD-MM-YYYY: ");
  scanf("%d-%d-%d",&inputedDOF.Day,&inputedDOF.Month,&inputedDOF.Year);
  for(int i=0;i<n;i++){
   if((inputedDOF.Day==stArr[i].DateOfBirth.Day) && (inputedDOF.Month==stArr[i].DateOfBirth.Month) && (inputedDOF.Year==stArr[i].DateOfBirth.Year)){
    filteredStudents[filteredCount]=stArr[i];
    ++filteredCount;
   }
  }
  break;
 }
 case 4:{
  char dept[100];
  fflush(stdin);
  gets(dept);
  for(int i=0;i<n;i++){
   giveStringPropSearch(stArr[i],filteredStudents,&filteredCount,stArr[i].Dept,dept);
  }
  break;
 }
 case 5:{
  char sec;
  fflush(stdin);
  scanf("%c",&sec);
  for(int i=0;i<n;i++){
   if(stArr[i].Section==sec){
    filteredStudents[filteredCount]=stArr[i];
    ++filteredCount;
   }
  }
  break;
 }
 case 6:{
  float grade;
  scanf("%f",&grade);
  for(int i=0;i<n;i++){
   giveFloatPropSearch(stArr[i],filteredStudents,&filteredCount,stArr[i].Grade,grade);
  }
  break;
 }
 case 7:{
  float sportsScore;
  scanf("%f",&sportsScore);
  for(int i=0;i<n;i++){
   giveFloatPropSearch(stArr[i],filteredStudents,&filteredCount,stArr[i].Extra.sports,sportsScore);
  }
  break;
 }
 case 8:{
  float contestsScore;
  scanf("%f",&contestsScore);
  for(int i=0;i<n;i++){
   giveFloatPropSearch(stArr[i],filteredStudents,&filteredCount,stArr[i].Extra.contests,contestsScore);
  }
  break;
 }
 case 9:{
  float qualityScore;
  scanf("%f",&qualityScore);
  for(int i=0;i<n;i++){
   giveFloatPropSearch(stArr[i],filteredStudents,&filteredCount,stArr[i].Extra.quality,qualityScore);
  }
  break;
 }
 default:
  printf("Invalid option selected");
  break;
 }
 if(filteredCount<1){
  printf("No student found with this value! Please provide available values.\n");
 }else{
 displayStudents(filteredStudents,filteredCount);
 }
 free(filteredStudents);
}

//delete student by roll
void deleteStudent(Student *stArr,int* n){
 int inputedRoll;
 if(*n<1){
  printf("\nNo student data to delete! Please add students first.\n");
  return;
 }
 printf("\nEnter Roll of the student that you want to delete: ");
 scanf("%d",&inputedRoll);

 int targetDelIndex=-1;
 for(int i=0;i<*n;i++){
  if(stArr[i].Roll==inputedRoll){
   targetDelIndex=i;
   break;
  }
 }
 if(targetDelIndex==-1){
  printf("No student found with the Roll no! Please provide the correct Roll no.\n");
  return;
 }

 for(int i=targetDelIndex;i<(*n)-1;i++){
  stArr[i]=stArr[i+1];
 }
 --(*n);
 printf("Student with Roll %d deleted successfully!\n",inputedRoll);
}

//sorting students info by their property in ascending and descending order
int getCompValByField(const Student* a,const Student* b,int field){
 switch (field)
 {
 case 1:
  return (a->Roll - b->Roll);
 case 2:
  return strcmp(a->Name,b->Name);
 case 3:{
  if(a->DateOfBirth.Year<b->DateOfBirth.Year){
   return -1;
  }else if(a->DateOfBirth.Year>b->DateOfBirth.Year){
   return 1;
  }else{
    if(a->DateOfBirth.Month<b->DateOfBirth.Month){
     return -1;
    }else if(a->DateOfBirth.Month>b->DateOfBirth.Month){
     return 1;
    }else{
     if(a->DateOfBirth.Day<b->DateOfBirth.Day){
      return -1;
     }else if(a->DateOfBirth.Day>b->DateOfBirth.Day){
      return 1;
     }else{
      return 0;
     }
    }
  }
 }
 case 4:
  return strcmp(a->Dept,b->Dept);
 case 5:
  return ((int)(a->Section) - (int)(b->Section));
 case 6:
  return ((int)(a->Grade*100)-(int)(b->Grade*100));
 case 7:
  return ((int)(a->Extra.sports*100)-(int)(b->Extra.sports*100));
 case 8:
  return ((int)(a->Extra.contests*100)-(int)(b->Extra.contests*100));
 case 9:
  return ((int)(a->Extra.quality*100)-(int)(b->Extra.quality*100));
 default:
  return 0;
 }
}

int compareStudents(const void *a, const void *b,const void *control){
 ControlSort *ctrl=(ControlSort*)control;
 return getCompValByField((const Student*)a,(const Student*)b,ctrl->field) * ctrl->order;
}

void swapStudents(Student* a,Student* b){
 Student temp;
 temp=*b;
 *b=*a;
 *a=temp;
}

void generalSort(Student *stArr,int size,int (*compareFunction)(const void*,const void*,const void*),ControlSort *control){
 int n;
 for(int i=0,j;i<size-1;i++){
  for(j=0;j<size-i-1;j++ ){
  n= compareFunction(&stArr[j],&stArr[j+1],control);
   if(n>0){
   swapStudents(&stArr[j],&stArr[j+1]);
  }
  }
 }
}

void sortStudentLists(Student *stArr,int n){
 int op;
 ControlSort ctrlS;
 if(n<1){
  printf("\nNo data to sort! Please Add student data first.\n");
  return;
 }
 displayPropTypes("sort");
 scanf("%d",&ctrlS.field);
 printf("Choose the order system: \n\t1.Ascending\n\t2.Descending\nChoose option: ");
 scanf("%d",&op);
 ctrlS.order=(op==1)?1:-1;

 generalSort(stArr,n,compareStudents,&ctrlS);
 printf("\nSorted student list:");
 displayStudents(stArr,n);
}



//menu function
void displayOptions(){
 printf("\nPlease select an option: \n");
 printf("1.Add Students.\n");
 printf("2.Display Students.\n");
 printf("3.Search Student by type.\n");
 printf("4.Delete Student.\n");
 printf("5.Sort Students by type.\n");
 printf("6.Exit.\n");
}

void displayPropTypes(const char* label){
 printf("\nPlease select the type you want to %s by: \n",label);
 printf("\t1.Roll\n");
 printf("\t2.Name\n");
 printf("\t3.Date of Birth\n");
 printf("\t4.Department\n");
 printf("\t5.Section\n");
 printf("\t6.Grade\n");
 printf("\t7.Sports score\n");
 printf("\t8.Contests score\n");
 printf("\t9.Quality Score\n");
 printf("\nPlease choose your option: ");
}

int main(){
 Student *students=NULL;
 int op,n=0;
 printf("----Student Management System----\n");
 students=(Student*)malloc(sizeof(Student)*3);


 while(1){
  displayOptions();
  printf("Option no: ");
  scanf("%d",&op);
  if(op==6){
   break;
  }

  switch (op)
  {
  case 1:
   addStudents(students,&n);
   break;
  case 2:
   displayStudents(students,n);
   break;
  case 3:
   searchStudent(students,n);
   break;
  case 4:
   deleteStudent(students,&n);
   break;
  case 5:
   sortStudentLists(students,n);
   break;
  default:
   printf("Invalid option selected! Please Enter a correct one.\n");
   break;
  }
 }

 free(students);
 return 0;
}