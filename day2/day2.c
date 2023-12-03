#include <ctype.h>
#include <stdio.h>

int main() {
  const char *path = "input.txt";
  FILE *file = fopen(path, "r");
  const int MAX_LINES = 150;
  const int MAX_ROWS = 250;
  const int MAX_RED = 12;
  const int MAX_GREEN = 13;
  const int MAX_BLUE = 14;
  int all_lines[MAX_LINES][MAX_ROWS] = {0};
  int i = 0;
  int j = 0;
  int c = getc(file);
  while (c != EOF) {
    if (c == '\n') {
      all_lines[i][j] = c;
      j = 0;
      i++;
    } else {
      all_lines[i][j] = c;
      j++;
    }
    c = getc(file);
  }

  int res = 0;
  int line_i = 0;
  while (line_i < MAX_LINES && all_lines[line_i][0] != 0) {
    int *curr_line = all_lines[line_i];
    int col_i = 0;
    int multiplier = 1;
    while (col_i < MAX_ROWS && all_lines[line_i][col_i] != '\n') {
      int curr_char = curr_line[col_i];
      int next_char = curr_line[col_i + 1];
      if (isdigit(curr_char) && isdigit(next_char)) {
        int color = curr_line[col_i + 3];
        int num = 10 * (curr_char - 48) + (next_char - 48);
        if ((color == 'g' && num > MAX_GREEN) ||
            (color == 'r' && num > MAX_RED) ||
            (color == 'b' && num > MAX_BLUE)) {
          multiplier = 0;
        }
        printf("%d%c", num, color);
        col_i++;
      } else if (isdigit(curr_char) && next_char == ' ') {
        int color = curr_line[col_i + 2];
        int num = curr_char - 48;
        printf("%d%c", num, color);
      }
      col_i++;
    }
    res += (line_i + 1) * multiplier;
    printf("\tResult: %d", res);
    printf("\tIs_valid = %d", multiplier);
    printf("\n");
    line_i++;
  }
  printf("Final Result: %d\n", res);
  return 0;
}
