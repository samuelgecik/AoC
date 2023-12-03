#include <ctype.h>
#include <stdio.h>

#define MAX_LENGTH 256

int main() {
  FILE *fp = fopen("input.txt", "r");
  char line[MAX_LENGTH];

  if (!fp) {
    perror("File not opened!");
    return -1;
  }

  int first = -1;
  int last = -1;
  int digit = 0;

  while (fgets(line, MAX_LENGTH, fp) != NULL) {
    int i = 0;
    while (line[i] != '\0') {
      if (isdigit(line[i])) {
        if (first < 0) {
          first = line[i] - '0';
        }
        last = line[i] - '0';
      }
      i++;
    }
    digit += 10 * first + last;
    first = -1;
  }

  fclose(fp);
  printf("Sum = %d", digit);
}