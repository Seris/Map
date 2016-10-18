#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <types/map.h>
#include <types/mlist.h>
#include <music.h>

int load_database(char* file, music_t** db){
    FILE* db_fd = fopen(file, "r"); 
    *db = malloc(0);
    char** cursor;

    int max_elem = 10, count = 0;
    char* line;
    int ret = 0;
 
    do {
        *db = realloc(*db, max_elem * sizeof(music_t));
        for(; count < max_elem && ret != EOF; count++){
            ret = fscanf(db_fd, "%m[^\n]", &line);
            fseek(db_fd, 1, SEEK_CUR);

            cursor = (char**) &(*db)[count];
            cursor[0] = strtok(line, "|");
            for(int i = 1; i < 5; i++){
               cursor[i] = strtok(NULL, "|");
            }
        }

        max_elem = (int) (1.2 * max_elem);
    } while(ret != EOF);

    fclose(db_fd);

    *db = realloc(*db, --count * sizeof(music_t));

    return count;
}

void free_database(music_t* db, int size){
    for(int i = 0; i< size; i++){
        free(db[i].title);
    }
    free(db);
}

int count_artist(map_t* db){
    mlist_t* elem;
    music_t* music;
    map_t* artist = map_new();
    int count;

    for(int i = 0; i < db->table_size; i++){
        elem = db->table[i];
        while(elem != NULL){
            music = (music_t*) elem->value;
            if(map_set(artist, music->author, artist)){
                printf("%s|%s\n", music->author, music->title);
            }
            elem = elem->next;
        }
    }

    count = artist->elem_count;
    map_del(artist);

    return count;
}

int main(int argc, char* argv[]){
    map_t* map = map_new();
    music_t* database;
    int elem = load_database("./database", &database);
    // printf("successfully loaded %d elements\n", elem);

    for(int i = 0; i < elem; i++){
        map_set(map, database[i].title, &database[i]);         
    }
    // printf("map loaded\n");

    count_artist(map);

    map_del(map);

    free_database(database, elem);
    
    return EXIT_SUCCESS;
}

