/*This prgram was created by Cory Stanford*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 20
int generateHash(char *organization);
void deleteNode(char *organization, char *name);
void writeFile(char *organization, char *name, char *email);
void readFile(char *organization, char *name, char *email);
// node struct
typedef struct node{
	char *name;
	char *organization;
	char *email;
	struct node *next;
} node;
//hashArray
node *hashArray[SIZE];
//create node function
void createNode(char *organization, char *name, char *email){
	node *node1 = malloc(sizeof(node));
	node1->organization = organization;
	node1->name = name;
	node1->email = email;
	node1->next = NULL;
	printf("organization added: %s\nname: %s\nemail: %s\n", node1->organization, node1->name, node1->email);
	int key = generateHash(node1->organization);
	//printf("key %d\n", key);
	if(hashArray[key] != 0){
		node *temp = hashArray[key];
		while(true){
			if(temp->next == NULL){
				temp->next = node1;
				//printf("node added in next\n");
				break;
			}
			else{
				temp = temp->next;
			}
		}
	}
	else{
		hashArray[key] = node1;
		//printf("node added in empty spot\n");
	}
}
//delete node function
void deleteNode(char *organization, char *name){
	int index = generateHash(organization);
	if(hashArray[index]->next == NULL){
		free(hashArray[index]);
		hashArray[index] = 0;
		printf("solo node deleted\n");
	}
	else{
		node *tempCurrent = hashArray[index];
		node *tempPrevious = hashArray[index];
		int counter = 0;
		while(true){
			if(tempCurrent->name == name){
				if(tempCurrent->next == NULL){
					free(tempCurrent);
					printf("linked node deleted\n");
					break;
				}
				else{
					if(counter == 0){
						hashArray[index] = tempCurrent->next;
						free(tempCurrent);
					}
					else{
						tempPrevious->next = tempCurrent->next;
						free(tempCurrent);
					}
					printf("linked node deleted\n");
					break;
				}
			}
			else{
				if(counter == 0){
					tempCurrent = tempCurrent->next;
					counter++;
				}
				else{
					tempCurrent = tempCurrent->next;
					tempPrevious = tempPrevious->next;
				}
			}
		}
	}
}
// generate hash value from organization
int generateHash(char *organization){
	int total = 0;
	//printf("ogranization in generateHash: %s\n", organization);
	for(int i = 0;organization[i] != '\0'; ++i){
		total += organization[i];
	}
	return total % SIZE;
}
// write to file function
void writeFile(char *organization, char *name, char *email){
	FILE *fp;
	fp = fopen("data.txt", "w");
	fprintf(fp, "%s %s %s", organization, name, email);
	fclose(fp);
}
//read from file function
void readFile(char *organization, char *name, char *email){
	(void)organization;
	(void)name;
	(void)email;
	char var[1000];
	FILE *fp;
	fp = fopen("data.txt", "r");
	fgets(var, 1000, fp);
	//printf("read file: %s\n", var);
}
int main(int argc, char *argv[]){
	(void)argc;
	//printf("%s, %s, %s, %d\n", argv[1], argv[2], argv[3], argc);
	printf("the progam stores nodes in a hash table\n");
	if(strcmp(argv[1], "create") == 0){
		createNode(argv[2], argv[3], argv[4]);
	}
	if(strcmp(argv[1], "remove") == 0){
		deleteNode(argv[2], argv[3]);
	}
	//createNode("company", "john", "john@gmail.com");
	//deleteNode(argv[1], argv[2]);
	//deleteNode("company", "john");
	//writeFile(argv[1], argv[2], argv[3]);
	//readFile("company", "joe", "joe@gmail.com");

	return 0;
}
