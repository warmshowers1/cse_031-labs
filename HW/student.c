#include<stdio.h>
#include<malloc.h>
#include<string.h>

#define MAX_NAME_LEN 128
typedef struct {
    char name[MAX_NAME_LEN];
    unsigned long sid;
} Student;

const char* getName(const Student* s){ return s->name; }
void setName(Student* s, const char* name){ strcpy(s->name,name); }
unsigned long getStudentID(const Student* s){ return s->sid; }
void setStudentID(Student* s, unsigned long sid){ s->sid = sid; }
Student* makeDefault(void){
    Student* s = (Student*)malloc(sizeof(Student));
    setName(s, "John");
    setStudentID(s, 12345678);
    return s;
}

int main(){
    Student* p = makeDefault();
    printf("Name: %s\n", getName(p));
    printf("ID:: %li\n", getStudentID(p));
    return 0;
}
