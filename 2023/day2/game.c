#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for storing game data
struct game {
  int id;
  int nrounds;
  int **rounds;
  bool is_possible;
};

#define AR_LENGTH 3
#define MAX_LINE_LENGTH 256
#define NUM_GAMES 100
#define INPUT "input.txt"

// Function to calculate the number of rounds in a game
int get_nrounds(char *game) {
  char *token = strtok(game, ":");
  puts(token);  // Print the token for debugging
  token = strtok(NULL, ";");
  int num_rounds = 0;
  while (token) {
    puts(token);  // Print the token for debugging
    token = strtok(NULL, ";");
    num_rounds++;
  }
  return num_rounds;
}

// Function to find the next number in a string
char *find_next_num(char *input) {
  // Skip non-digit characters
  while (*input && !isdigit(*input)) {
    input++;
  }
  // Return NULL if the end of the string is reached
  if (*input == '\0') {
    return NULL;
  }
  return input;
}


// Function to parse the input file and populate the games array
void parse_input(struct game *games, FILE *fp) {
  char line[MAX_LINE_LENGTH]; // Buffer to store each line from the file
  for (size_t i = 0; i < NUM_GAMES; i++) {
    fgets(line, MAX_LINE_LENGTH, fp); // Read a line from the file
    char cp_line[strlen(line) + 1]; // Create a copy of the line for processing
    strcpy(cp_line, line); // Copy the str, because we will destruct in the get_rounds()
    games[i].nrounds = get_nrounds(cp_line); // Determine the number of rounds
    char *color = strtok(line, ":"); // Extract the part after the game ID
    char *end; // Pointer used for strtol
    int id = (int)strtol(color + 5, &end, 10); // Parse the game ID
    games[i].id = id; // Set the game ID
    games[i].rounds = calloc(games[i].nrounds, sizeof(int *)); // Allocate memory for rounds
    color = strtok(NULL, ";"); // Move to the first round's data
    for (size_t j = 0; j < games[i].nrounds; j++) {
      games[i].rounds[j] = calloc(3, sizeof(int)); // Allocate memory for each round
      int n = 0; // Counter for colors in each round
      // Parse the colors and amounts for each round
      while (n < 3 && color) {
        int amount = (int)strtol(color, &end, 10); // Parse the amount
        // Assign the amount to the appropriate color based on the character following the amount
        if (end[1] == 'r') {
          games[i].rounds[j][0] = amount; // Red
          color = find_next_num(end);
        } else if (end[1] == 'g') {
          games[i].rounds[j][1] = amount; // Green
          color = find_next_num(end);
        } else if (end[1] == 'b') {
          games[i].rounds[j][2] = amount; // Blue
          color = find_next_num(end);
        }
        n++; // Increment color counter
      }
      // Print the parsed round information
      printf("Round %d: %d, %d, %d\n", j, games[i].rounds[j][0],
             games[i].rounds[j][1], games[i].rounds[j][2]);
      color = strtok(NULL, ";"); // Move to the next round
    }
  }
}

int main() {
  // Open the input file
  FILE *fp = fopen(INPUT, "r");
  if (!fp) {
    perror("File not opened!");
    return -1;
  }

  struct game games[NUM_GAMES];  // Declare an array of game structures
  parse_input(games, fp);  // Parse the input file

  // Get user input for the number of colors
  int nred, ngreen, nblue;
  printf("Please input your values: ");
  scanf("%d %d %d", &nred, &ngreen, &nblue);

  int id_sum = 0;  // Variable to store the sum of IDs
  for (int i = 0; i < NUM_GAMES; i++) {
    games[i].is_possible = true;
    for (size_t j = 0; j < games[i].nrounds; j++) {
      int *colors = games[i].rounds[j];
      // Check if the game round is possible with the given color limits
      if (colors[0] > nred || colors[1] > ngreen || colors[2] > nblue) {
        games[i].is_possible = false;
      }
      free(games[i].rounds[j]);  // Free memory for each round
    }
    // Add game ID to the sum if the game is possible
    if (games[i].is_possible) {
      id_sum += games[i].id;
    }
    free(games[i].rounds);  // Free memory for rounds
  }
  printf("\nID sum: %d\n", id_sum);  // Print the sum of IDs

  fclose(fp);  // Close the input file
}
