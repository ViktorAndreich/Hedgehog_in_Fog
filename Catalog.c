#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Clients {
    char Phone_Number[12];
    char First_Name[20];
    char Last_Name[20];
    char Email[35];
};

void* Add(struct Clients* list, size_t *length, size_t *capacity) {
    if (*length >= *capacity) {
        (*capacity) *= 2;
        struct Clients* buffer = realloc(list, sizeof(struct Clients) * (*capacity));
        if (buffer == NULL)
            return list;
        list = buffer;
    }

    printf("Enter phone number: \n");
    scanf("%11s", list[*length].Phone_Number);
    printf("Enter First Name: \n");
    scanf("%19s", list[*length].First_Name);
    printf("Enter Last Name: \n");
    scanf("%19s", list[*length].Last_Name);
    printf("Enter Email: \n");
    scanf("%34s", list[*length].Email);

    (*length)++;

    return list;
}

void Display_All(struct Clients list[], size_t amount) {
    for (size_t i = 0; i < amount; i++) {
        printf("[%lu]\n Phone number: %s \n First name: %s \n Last name: %s \n Email: %s \n", 
               i + 1, list[i].Phone_Number, list[i].First_Name, list[i].Last_Name, list[i].Email);
    }
    return;
}

void* Delete(struct Clients* list, size_t *length, int index) {
    if (index < 0 || index >= *length) {
        printf("Invalid index!\n");
        return list;
    }
  
    if (*length > 1) {
        memmove(&list[index], &list[index + 1], sizeof(struct Clients) * (*length - index - 1));
    }
    (*length)--;
    
    return realloc(list, sizeof(struct Clients) * (*length));
}

int main() {
    size_t length = 0;
    size_t capacity = 1;
    struct Clients *c = malloc(sizeof(struct Clients) * capacity);

    int point_menu;
    do {
        printf("choose menu \n");
        printf("[1] Display all clients \n");
        printf("[2] Add new \n");
        printf("[3] Delete client \n");
        printf("[4] Exit\n");
        scanf("%d", &point_menu);

        switch (point_menu) {
            case 1: {
                Display_All(c, length);
                break;
            }
            case 2: {
                c = Add(c, &length, &capacity);
                break;
            }
            case 3: {
                int index;
                printf("Enter the index of the client to delete (1 to %lu): \n", length);
                scanf("%d", &index);
                index--;
                c = Delete(c, &length, index);
                break;
            }
            case 4: {
                break;
            }
            default: {
                printf("Invalid option!\n");
                break;
            }
        }
    } while (point_menu != 4);

    free(c);
    return 0;
}
