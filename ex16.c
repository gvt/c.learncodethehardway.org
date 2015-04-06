#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

// initializes a Person without memory allocation (on the stack, passed by ref)
struct Person *Person_init(struct Person *who, char *name, int age, int height, int weight)
{
	assert(who != NULL);
	
	(*who).name = strdup(name);
	(*who).age = age;
	(*who).height = height;
	(*who).weight = weight;
	
	return who;
}

// initializes a Person with memory allocation (on the heap)
struct Person *Person_create(char *name, int age, int height, int weight)
{
	struct Person *who = malloc(sizeof(struct Person));
	assert(who != NULL);
	
	(*who).name = strdup(name);
	(*who).age = age;
	(*who).height = height;
	(*who).weight = weight;
	
	return who;
}

// frees the Person object (returns memory to the heap)
void Person_destroy(struct Person *who)
{
	assert(who != NULL);

	free(who->name);
	free(who);
}

void Person_print(struct Person *who, char *label)
{
	printf("Person:: %s\n", label);
	printf("\tName: %s\n"  , (*who).name);
	printf("\tAge: %d\n"   , (*who).age);
	printf("\tHeight: %d\n", (*who).height);
	printf("\tWeight: %d\n", (*who).weight);
}

// makes two Person structs: one on the stack and one on the heap
int main(int argc, char *argv[])
{
	// this Person will be on the stack
	struct Person joe;
	joe.name = "Joe Smith";
	joe.age = 32;
	joe.height = 64;
	joe.weight = 140;
	// this Person will be on the heap
	struct Person *frank = Person_create("Frank Valentine", 20, 72, 180);
	
	// print them out and where they are in memory
	printf("Joe is at memory location: %p\n", &joe);
	Person_print(&joe, "on the stack");
	printf("Frank is at memory location: %p\n", frank);
	Person_print(frank, "on the heap");
	
	// make everyone age 20 years and print them again
	joe.age += 20;
	joe.height -= 2;
	joe.weight += 40;
	Person_print(&joe, "on the stack; 2nd print");
	frank->age += 20;
	frank->weight += 20;
	Person_print(frank, "on the heap, 2nd print");
	
	// desroy the one on the heap to clean up after ourselves
	Person_destroy(frank);
	
	return 0;
}
