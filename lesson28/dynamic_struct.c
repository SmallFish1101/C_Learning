#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[32];
    int  age;
} Person;

int main(void) {
    // 动态分配一个 Person
    Person *p = (Person *)malloc(sizeof(Person));
    if (p == NULL) return 1;

    strcpy(p->name, "Zhang San");
    p->age = 20;

    printf("Person: %s, %d years old\n", p->name, p->age);
    printf("Size of Person: %zu bytes\n", sizeof(Person));

    free(p);
    p = NULL;   // 释放后置空

    return 0;
}