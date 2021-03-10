#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_t {
    struct torrent_t* torrent;
    struct node_t* next;
};

struct list_t {
    struct node_t* head;
};

struct torrent_t {
    char title[21];
    int grade;
    float size;
};

struct torrent_server_t {
    char address[21];
    struct list_t list; 
};

void insert_node(struct list_t* list, struct torrent_t* torrent) {
    struct node_t* new_node = malloc(sizeof(struct node_t));
    new_node->torrent = torrent;

    new_node->next = list->head;
    list->head = new_node;
}

void remove_node(struct list_t* list) {
    if (list->head == NULL) {
        printf("No nodes!\n");
        return;
    }

    struct node_t* old_node = list->head;
    list->head = old_node->next;
    free(old_node);
}

void destroy_list(struct list_t* list) {
    while (list->head != NULL) {
        remove_node(list);
    }
}
// It is not working properly
struct list_t find_sort_and_return(struct torrent_server_t* server, char to_find[16], int flag) {
    struct list_t list_finded = {NULL};
    struct node_t* help_node = server->list.head;
    int count = 0;
    printf("Debug 1\n");
    while (help_node != NULL) {
        printf("Debug 2\n");
        if (strstr(help_node->torrent->title, to_find) != NULL) {
            insert_node(&list_finded, help_node->torrent);
            count++;
            printf("Debug 3\n");
        }
        help_node = help_node->next;
    }

    //This is for sorting the array
    if (flag == 0) {
        return list_finded;
    } else {
        struct list_t array[count];
        struct node_t* help_node2 = list_finded.head;
        struct list_t help_swap; 

        //Copy the info from the list to the array
        for (int index = 0; index < count; index++) {
            array[index].head->torrent = help_node2->torrent;
            help_node2 = help_node2->next;
        }

        //Bubble sort the array
        for (int index = 0; index < count; index++) {
            for (int index_2 = index + 1; index_2 < count; index_2++) {
                if (array[index].head->torrent->grade < array[index_2].head->torrent->grade) {
                    help_swap.head->torrent = array[index].head->torrent;
                    array[index].head->torrent = array[index_2].head->torrent;
                    array[index_2].head->torrent = help_swap.head->torrent;
                }
            }
        }

        help_node2 = list_finded.head;

        //Copy the info from the array to the list
        for (int index = 0; index < count; index++) {
            help_node2->torrent = array[index].head->torrent;
            help_node2 = help_node2->next;
        }
    }
}

void print_list(struct list_t* list) {
    struct node_t* temp_node = list->head;

    while (temp_node != NULL) {
        printf("Value = %s\n", temp_node->torrent->title);
        temp_node = temp_node->next;
    }
}

int main() {
    struct torrent_server_t zamunda;
    struct torrent_t torrent1 = {"Film and more", 4, 140.0};
    struct torrent_t torrent2 = {"Game", 5, 150.0};
    struct torrent_t torrent3 = {"Music", 3, 160.0};
    struct torrent_t torrent4 = {"Film", 1, 170.0};
    printf("DEBUG!\n");
    insert_node(&zamunda.list, &torrent1);
    insert_node(&zamunda.list, &torrent2);
    insert_node(&zamunda.list, &torrent3);
    insert_node(&zamunda.list, &torrent4);
    printf("DEBUG@\n");
    print_list(&zamunda.list);
    //Stop working here
    printf("DEBUG#\n");
    struct list_t result = find_sort_and_return(&zamunda, "Film", 0);
    printf("DEBUG$\n");
    print_list(&result);

    return 0;
}