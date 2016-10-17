#include <stdio.h>
#include <stdlib.h>
#include <mcheck.h>
#include <string.h>

#include <types/clist.h>
#include <types/map.h>
#include <types/music.h>

int main(int argc, char* argv[]){

    #ifdef DEBUG
    mtrace();
    #endif // DEBUG

    map_t* map = map_create();
   
    FILE* db_fd = fopen("./prod.dat", "r"); 
    music_t* database = NULL;
    char** cursor;

    int max_elem = 10, count = 0;
    char* line;
    int ret = 0;
 
    do {
        database = realloc(database, max_elem * sizeof(music_t));
        for(; count < max_elem && ret != EOF; count++){
            ret = fscanf(db_fd, "%m[^\n]", &line);
            fseek(db_fd, 1, SEEK_CUR);

            cursor = (char**) &database[count];
            cursor[0] = strtok(line, "|");
            for(int i = 1; i < 5; i++){
               cursor[i] = strtok(NULL, "|");
            }
        }

        max_elem = (int) (1.2 * max_elem);
        printf("count=%d\n", count);
    } while(ret != EOF);

    fclose(db_fd);

    database = realloc(database, --count * sizeof(music_t));

    printf("database loaded\n");


    for(int i = 0; i < count; i++){
        map_set(map, &database[i]);
    }
    map_resize_to_fit(map);

    printf("map loaded\n");
    printf("%d\n", map->table_size);

    int j;
    for(j = 0; j < count; j++){
        if(map_get(map, database[j].title, NULL) != 0){
            printf("can't find %s\n", database[j].title);
        }
    }

    map_show_stack(map);


    printf("freeing...");
    for(int i = 0; i < count; i++){
        free(database[i].title);
    }
    free(database);

    map_delete(map);


    #ifdef DEBUG
    muntrace();
    #endif // DEBUG

    return EXIT_SUCCESS;
}

