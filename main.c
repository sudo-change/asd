#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
  int id;
  char name[64];
  float price;
  struct Node* next;
};



void printList(struct Node* head) {
  struct Node* current = head;
  while (current != NULL) {
    printf("%d %s %.2f\n", current->id, current->name, current->price);
    current = current->next;
  }
}

void addElement(struct Node** head, int id, const char* name, float price) {
  struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
  new_node->id = id;
  strcpy(new_node->name, name);
  new_node->price = price;
  new_node->next = NULL;
  
  if (*head == NULL) {
    *head = new_node;
  } else {
    struct Node* current = *head;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = new_node;
  }
}

void removeElementById(struct Node** head, int id) {
  struct Node* current = *head;
  struct Node* temp_node = NULL;
  
  while (current != NULL) {
    if (current->id == id) {
      if (temp_node == NULL) {
        *head = current->next;
      } else {
        temp_node->next = current->next;
      }
      free(current);
      return;
    }
    temp_node = current;
    current = current->next;
  }
}

void updateElementById(struct Node* head, int id, const char* name, float price) {
  struct Node* current = head;
  while (current != NULL) {
    if (current->id == id) {
      strcpy(current->name, name);
      current->price = price;
      return;
    }
    current = current->next;
  }
}

void printMatchingElements(struct Node* head, const char* name) {
  struct Node* current = head;
  while (current != NULL) {
    if (strcmp(current->name, name) == 0) {
      printf("%d %s %.2f\n", current->id, current->name, current->price);
    }
    current = current->next;
  }
}

void findProductById(struct Node *head, int id) {
    struct Node * current = head;
    while (current != NULL) {
        if (current->id == id) {
            printf("%d, %s, %lf \n", current->id, current->name, current->price);
            return;
        }
        current = current->next;
    }
    printf("Product not found.\n");
}

void saveToFile(struct Node* head, const char* filename) {
  FILE* fp = fopen(filename, "w");

  struct Node* current = head;
  while (current != NULL) {
    fprintf(fp, "%d %s %.2f\n", current->id, current->name, current->price);
    current = current->next;
  }

  fclose(fp);
}

struct Node* readFromFile(const char* filename) {
  FILE* fp = fopen(filename, "r");

  struct Node* head = NULL;
  struct Node* current = NULL;

  while (1) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    int items_read = fscanf(fp, "%d %s %f\n", &node->id, node->name, &node->price);
    if (items_read != 3) break;
    node->next = NULL;

    if (head == NULL) {
      head = node;
      current = head;
    } else {
      current->next = node;
      current = current->next;
    }
  }

  fclose(fp);
  
  return head;
}

void printOptions() {
    printf("Enter one of the following options:\n");
    printf("1. Add\n");
    printf("2. Update\n");
    printf("3. Delete\n");
    printf("4. Search by name\n");
    printf("5. List\n");
    printf("6. Find by id\n");
    printf("7. Save\n");
    printf("8. Exit\n");
}

int main() {
  //Read LL from file
  struct Node* head = readFromFile("list2.txt");
  
  //Print LL
  printList(head);
  
  //Save LL to file
  saveToFile(head, "list2.txt");

    int decision;
    while (1) {
        printOptions();
        scanf("%d", &decision);
        switch (decision) {
            case 1: {
                printf("Enter id: ");
                int id;
                scanf("%d", &id);
                printf("Enter name: ");
                char name[100];
                scanf("%s", name);
                printf("Enter price: ");
                float price;
                scanf("%f", &price);
                addElement(&head, id , name, price);
                break;
            }
            case 2: {
                printf("Enter id of product to update: ");
                int id;
                scanf("%d", &id);
                printf("Enter new name: ");
                char name[100];
                scanf("%s", name);
                printf("Enter new price: ");
                float price;
                scanf("%f", &price);
                updateElementById(head, id, name, price);
                break;
            }
            case 3: {
                printf("Enter id of product to delete: ");
                int id;
                scanf("%d", &id);
                removeElementById(&head, id);
                break;
            }
            case 4: {
                printf("Enter name of product to search for: ");
                char name[100];
                scanf("%s", name);
                printMatchingElements(head, name);
                break;
            }
            case 5: {
                printList(head);
                break;
            }
            case 6: {
                printf("Enter id of product to search for: ");
                int id;
                scanf("%d", &id);
                findProductById(head, id);
                break;
            }
            case 7: {
                saveToFile(head, "list2.txt");
                break;
            }
            case 8: {
                //quit the program and save the list to a file
               saveToFile(head, "list2.txt");
                return 0;
                break;
            }
            default: {
                printf("Invalid option.\n");
                break;
            }
        }
    }
  
  return 0;
}
