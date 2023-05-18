#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20
struct Student
{
    char nume[30];
    unsigned int nr_mat;
    float medie;
};

struct node
{
  char key[20];
  struct Student valoare;
  struct node *next;
};
struct hash_teibal
{
  int dim;
  struct node **buckets;
};
unsigned int hashFunction(const char* key, int tableSize) {
    unsigned int hash = 0;
    unsigned int keyLength = strlen(key);

    for (unsigned int i = 0; i < keyLength; i++) {
        hash += key[i];
    }

    return hash % tableSize;
}
void insert(struct hash_teibal* hashtable, const char* key, struct Student student) {
    unsigned int index = hashFunction(key, hashtable->dim);
    
    // Create a new node for the element
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    strcpy(newNode->key, key);
    newNode->valoare = student;
    newNode->next = NULL;

    if (hashtable->buckets[index] == NULL) {
        // If the bucket is empty, add the new node directly
        hashtable->buckets[index] = newNode;
    } else {
        // If there is already a node in the bucket, append the new node to the linked list
        struct node* currentNode = hashtable->buckets[index];
        
        while (currentNode->next != NULL) {
            currentNode = currentNode->next;
        }
        
        currentNode->next = newNode;
    }
}
struct Student* search(struct hash_teibal* hashtable, const char* key, unsigned int nr_mat) {
    unsigned int index = hashFunction(key, hashtable->dim);
    
    struct node* currentNode = hashtable->buckets[index];
    
    while (currentNode != NULL) {
        if (strcmp(currentNode->key, key) == 0 && currentNode->valoare.nr_mat == nr_mat) {
            return &(currentNode->valoare);
        }
        currentNode = currentNode->next;
    }
    
    return NULL;
}
void deleteStudent(struct hash_teibal* hashtable, const char* key, unsigned int nr_mat) {
    unsigned int index = hashFunction(key, hashtable->dim);

    struct node* currentNode = hashtable->buckets[index];
    struct node* previousNode = NULL;

    while (currentNode != NULL) {
        if (strcmp(currentNode->key, key) == 0 && currentNode->valoare.nr_mat == nr_mat) {
            if (previousNode == NULL) {
                // Node to be deleted is the first node in the bucket
                hashtable->buckets[index] = currentNode->next;
            } else {
                // Node to be deleted is not the first node in the bucket
                previousNode->next = currentNode->next;
            }

            free(currentNode);
            printf("Student deleted.\n");
            return;
        }

        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    printf("Student not found.\n");
}
int main()
{   
    struct hash_teibal tabelas;
    tabelas.dim = 10;
    tabelas.buckets =(struct node **) malloc(sizeof(struct node *)*tabelas.dim);
   int i;
    for (i=0; i<=tabelas.dim; i++)
      tabelas.buckets[i] = NULL;

    struct Student student1 = {"John", 12345, 8.5};
    struct Student student2 = {"Alice", 67890, 9.2};
    struct Student student3 = {"Bob", 54321, 7.8};
    struct Student student4 = student3;

    insert(&tabelas, "John", student1);
    insert(&tabelas, "Alice", student2);
    insert(&tabelas, "Bob", student3);
     insert(&tabelas, "Bob", student4);
     unsigned int index1 = hashFunction(student1.nume, tabelas.dim);

      const char* searchKey = "Bob";
    unsigned int searchIndex = hashFunction(searchKey, tabelas.dim);
    struct node* currentNode = tabelas.buckets[searchIndex];

    
    while (currentNode != NULL) {
        if (strcmp(currentNode->key, searchKey) == 0) {
            printf(" student %s: Nr matrcol: %u, medie: %.2f\n", currentNode->key, currentNode->valoare.nr_mat, currentNode->valoare.medie);
            break;
        }
        currentNode = currentNode->next;
    }


      searchKey = "John";
    unsigned int searchNrMat = 12345;
    struct Student* foundStudent = search(&tabelas, searchKey, searchNrMat);

    if (foundStudent != NULL) {
        printf("Found student %s: Number: %u, Average: %.2f\n", foundStudent->nume, foundStudent->nr_mat, foundStudent->medie);
    } else {
        printf("Student not found.\n");
    }

    const char* deleteKey = "John";
    unsigned int deleteNrMat = 12345;
    deleteStudent(&tabelas, deleteKey, deleteNrMat);

    // Searching for a deleted student
     foundStudent = search(&tabelas, deleteKey, deleteNrMat);

    if (foundStudent != NULL) {
        printf("Found student %s: Number: %u, Average: %.2f\n", foundStudent->nume, foundStudent->nr_mat, foundStudent->medie);
    } else {
        printf("Student not found.\n");
    }
  for (int i = 0; i < tabelas.dim; i++) {
        struct node* current = tabelas.buckets[i];
        while (current != NULL) {
            struct node* next = current->next;
            free(current);
            current = next;
        }
    }
    free(tabelas.buckets);
    return 0;
}