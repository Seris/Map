#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <types/disco.h>

Discotheque creer_discotheque_fichier(char* file){
    FILE* db_fd = fopen(file, "r"); 
    char* line;
    Discotheque d = NULL;
    music_t music;

    if(db_fd != NULL){
        d = creer_discotheque();
        fscanf(db_fd, "%m[^\n]", &line);
        while(line != NULL) { 
            music.title  = strtok(line, "|");
            music.author = strtok(NULL, "|");
            music.label  = strtok(NULL, "|");
            music.date   = strtok(NULL, "|");
            music.style  = strtok(NULL, "|");

            d = inserer(d,
                music.title,
                music.author,
                music.label,
                music.date,
                music.style);

            free(line);

            fseek(db_fd, 1, SEEK_CUR);
            fscanf(db_fd, "%m[^\n]", &line);
        }

        free(line);
        fclose(db_fd);
    }

    return d;
}
