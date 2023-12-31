#include <stdio.h>

int main() {
  FILE *fp = fopen("input.txt", "r");

  if (!fp) {
    perror("File not opened!");
    return -1;
  }

  int floor = 0;
  char c = fgetc(fp);
  while (c != EOF) {
    if (c == '(') {
      floor++;
    } else {
      floor--;
    }
    c = fgetc(fp);
  }

  fclose(fp);
  printf("Floor = %d", floor);
}