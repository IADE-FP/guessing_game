#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int number;
    int attempts;
} tGame, *Game;

void reset(Game game) {
    game->number = -1;
    game->attempts = 0;
}

int main() {
    Game game = (Game)malloc(sizeof(tGame));
    reset(game);
    char *line = NULL, *command;
    size_t len = 0;
    while (true) {
        getline(&line, &len, stdin);
        line[strlen(line) - 1] = '\0';
        if (strlen(line) == 0) break;
        command = strtok(line, " ");
        if (strcmp(command, "IJ") == 0) {
            if (game->number != -1)
                printf("Já existe um jogo iniciado.\n");
            else {
                game->number = random() % 100 + 1;  // Gerar número aleatório entre 0 1 e 100
                printf("Jogo iniciado com sucesso.\n");
            }
        } else if (strcmp(command, "R") == 0) {
            if(game->number == -1) {
                printf("Sem jogo iniciado.\n");
                continue;
            }
            game->attempts++;
            char *num = strtok(NULL, " ");
            int number = strtol(num, NULL, 10);
            if (number == game->number) {
                if (game->attempts == 1)
                    printf("Ganhou com 10 pontos.\n");
                else if (game->attempts == 2)
                    printf("Ganhou com 5 pontos.\n");
                else if (game->attempts == 3)
                    printf("Ganhou com 2 pontos.\n");
                else
                    printf("Ganhou com 1 ponto.\n");
                reset(game);
            }
            else if (game->attempts > 3) {
                printf("Perdeu.\n");
                reset(game);
            }
            else if (number > game->number)
                printf("Acima.\n");
            else printf("Abaixo.\n");
        } else if (strcmp(command, "G") == 0) {
            char *filename = strtok(NULL, " ");
            FILE *file = fopen(filename, "w");
            fprintf(file, "%d %d", game->number, game->attempts);
            fclose(file);
            printf("Jogo gravado com sucesso.\n");
        } else if (strcmp(command, "L") == 0) {
            char *filename = strtok(NULL, " ");
            FILE *file = fopen(filename, "r");
            if (file == NULL)
                printf("Não existe nenhum jogo guardado.\n");
            else {
                fscanf(file, "%d %d", &game->number, &game->attempts);
                fclose(file);
                printf("Jogo carregado com sucesso.\n");
            }
        } else {
            printf("Instrução inválida.\n");
        }
        free(line);
        line = NULL;
    }
    if(line) free(line);
    free(game);
    return 0;
}