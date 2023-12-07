#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int id;
  int **rounds;
} game;

#define AR_LENGTH 3
#define MAX_LINE_LENGTH 256
#define NUM_GAMES 100
#define INPUT "input.txt"

int get_nrounds(char *game) {
  char *token = strtok(game, ":");
  puts(token);
  token = strtok(NULL, ";");
  int num_rounds = 0;
  while (token) {
    puts(token);
    token = strtok(NULL, ";");
    num_rounds++;
  }
  return num_rounds;
}

char *find_next_num(char *input) {
  // Find the start of the first number in the string
  while (*input && !isdigit(*input)) {
    input++;
  }
  // If we reached the end of the string without finding a number, return NULL
  if (*input == '\0') {
    return NULL;
  }
  return input;
}

int main() {
  FILE *fp = fopen(INPUT, "r");
  if (!fp) {
    perror("File not opened!");
    return -1;
  }
  char line[MAX_LINE_LENGTH];
  game games[100];

  for (size_t i = 0; i < NUM_GAMES; i++) {
    fgets(line, MAX_LINE_LENGTH, fp);
    char cp_line[strlen(line) + 1];
    strcpy(cp_line, line);
    int nrounds = get_nrounds(cp_line);
    char *color = strtok(line, ":");
    char *end;
    int id = (int)strtol(color + 5, &end, 10);
    color = strtok(NULL, ";");
    games[i].id = id;
    games[i].rounds = calloc(nrounds, sizeof(int *));
    for (size_t j = 0; j < nrounds; j++) {
      games[i].rounds[j] = calloc(3, sizeof(int));
      int n = 0;
      while (n < 3 && color) {
        int amount = (int)strtol(color, &end, 10);
        if (end[1] == 'r') {
          games[i].rounds[j][0] = amount;
          color = find_next_num(end);
        } else if (end[1] == 'g') {
          games[i].rounds[j][1] = amount;
          color = find_next_num(end);
        } else if (end[1] == 'b') {
          games[i].rounds[j][2] = amount;
          color = find_next_num(end);
        }
        n++;
      }
      printf("Round %d: %d, %d, %d\n", j,
             games[i].rounds[j][0], games[i].rounds[j][1],
             games[i].rounds[j][2]);
      color = strtok(NULL, ";");
    }
  }
  fclose(fp);
}