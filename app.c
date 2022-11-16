#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int value = -1; 
    int score = 0;
    int num_attempts = 0;

    char* line = NULL;
    size_t len = 0;
    while (true) {
        getline(&line, &len, stdin);
        line[strlen(line)-1] = '\0';
        char* command = strtok(line, " ");
        if(strcmp(command, "IJ") == 0) {
            if(value != -1) {
                printf("Já existe um jogo iniciado.\n");
            }
            else {
                value = 47; // FIXME: devia ser random
                printf("Jogo iniciado com sucesso.\n");
            }
        }
        else if (strcmp(command, "R") == 0) {
            num_attempts++;
            char* num = strtok(NULL, " ");
            int number = atoi(num);
            if(number == value) {
                if(num_attempts == 1) score = 10;
                else if(num_attempts == 2) score = 5;
                else if(num_attempts == 3) score = 2;
                printf("Ganhou com %d pontos\n", score);
                score = 0;
                value = -1;
                num_attempts = 0;
            }
            if(num_attempts > 3){
                printf("Perdeu.\n");
                score = 0;
                value = -1;
                num_attempts = 0;
            }
            if(number > value) printf("Acima!\n");
            else printf("Abaixo!\n");
        }
    }
    return 0;
}