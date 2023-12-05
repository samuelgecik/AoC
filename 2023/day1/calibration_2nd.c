#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  char *word;
  int digit;
} word_to_int_lut;

#define MAX_LENGTH 256
#define MAX_DIGIT_LENGTH 5
#define INPUT "input.txt"

void replace_word_w_digit(char *line, word_to_int_lut *lut, size_t lut_size) {
  for (int i = 0; i < strlen(line) + 1 - fmin(strlen(line), MAX_DIGIT_LENGTH);
       i++) {
    char buffer[MAX_DIGIT_LENGTH + 1] = "\0";
    strncpy(buffer, line + i, fmin(strlen(line), MAX_DIGIT_LENGTH));
    for (int n = lut_size - 1; n >= 0; n--) {
      char *word;
      if ((word = strstr(buffer, lut[n].word))) {
        int position = word - buffer;
        line[i + position] = (char)lut[n].digit + '0';
        line[i + position + 1] = '.';
      }
    }
  }
}

int main() {
  FILE *fp = fopen(INPUT, "r");
  if (!fp) {
    perror("File not opened!");
    return -1;
  }
  char line[MAX_LENGTH];
  word_to_int_lut lut[] = {{"one", 1},   {"two", 2},   {"three", 3},
                           {"four", 4},  {"five", 5},  {"six", 6},
                           {"seven", 7}, {"eight", 8}, {"nine", 9}};
  size_t lut_size = sizeof(lut) / sizeof(lut[0]);

  int first = -1;
  int last = -1;
  int digit = 0;
  int n_line = 1;
  bool found_on_line = false;

  while (fgets(line, MAX_LENGTH, fp) != NULL) {
    printf("Line %d: %s", n_line++, line);
    replace_word_w_digit(line, lut, lut_size);
    printf("%s\n", line);
    int i = 0;
    while (line[i] != '\0') {
      if (isdigit(line[i])) {
        if (first < 0) {
          first = line[i] - '0';
          found_on_line = true;
        }
        last = line[i] - '0';
      }
      i++;
    }
    printf("%d\n", 10 * first + last);
    if (found_on_line) {
      digit += 10 * first + last;
    }
    first = -1;
    found_on_line = false;
  }

  fclose(fp);
  printf("\nSum = %d", digit);
}