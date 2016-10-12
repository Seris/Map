#include <stdlib.h>
#include <types/clist.h>
#include <assert.h>

clist_t* clist_push(clist_t** head_ptr, music_t* music){
    clist_t* head = *head_ptr;
    clist_t* new;
   
    if(head != NULL){
        new = clist_push(&head->next, music);
    } else {
        new = malloc(sizeof(clist_t));
        assert_malloc(new, "new list element"),
        new->music = music;
        new->next = NULL;
        *head_ptr = new;
    }

    return new;
}

int clist_pop(clist_t** head_ptr, music_t** music){
    clist_t* head = *head_ptr;
    int deleted = -1;

    if(head != NULL){
        if(head->next != NULL){
            deleted = clist_pop(&head->next, music);
        } else {
            if(music != NULL) *music = head->music;
            free(head);
            *head_ptr = NULL;
            deleted = 0;
        }
    }

    return deleted;
}

int clist_shift(clist_t** head_ptr, music_t** music){
    clist_t* head = *head_ptr;
    int deleted = -1;

    if(head != NULL){
        if(music != NULL) *music = head->music;
        *head_ptr = head->next;
        free(head);
        deleted = 0;
    }

    return deleted;
}

int clist_next(clist_t** list){
    if(*list != NULL){
        *list = (*list)->next;
        return 0;
    }
    return -1;
}

int clist_count(clist_t* list){
    int count = 0;
    while(list != NULL){
        count++;
        list = list->next;
    }
    return count;
}

