#include <ctype.h>
#include <stdio.h>

int issymbol(int in_char) {
  return (in_char != '.') && !isdigit(in_char) && (in_char != -1) &&
         (in_char != '\n');
}

int main() {
  printf("%d", issymbol(49));
  char *path = "input.txt";
  FILE *file = fopen(path, "r");
  const int MAX_LINES = 150;
  const int MAX_COLS = 150;
  int all_lines[MAX_LINES][MAX_COLS] = {0};
  for (int m = 0; m < MAX_LINES; m++) {
    for (int n = 0; n < MAX_COLS; n++) {
      all_lines[m][n] = -1;
    }
  }
  int c = getc(file);
  int i = 1;
  int j = 1;
  while (c != EOF) {
    all_lines[i][j] = c;
    if (c == '\n') {
      j = 1;
      i++;
    } else {
      j++;
    }
    c = getc(file);
  }

  int res = 0;
  int line_i = 1;
  while (line_i < MAX_LINES && all_lines[line_i][1] != -1) {
    int col_i = 1;
    int *curr_line = all_lines[line_i];
    while (col_i < MAX_COLS && all_lines[line_i][col_i] != '\n') {
      int curr_char = curr_line[col_i];
      int next_char = curr_line[col_i + 1];
      int next_next_char = curr_line[col_i + 2];
      if (isdigit(curr_char) && isdigit(next_char) && isdigit(next_next_char)) {
        int num = (curr_char - 48) * 100 + (next_char - 48) * 10 +
                  (next_next_char - 48);
        if (issymbol(all_lines[line_i - 1][col_i - 1]) ||
            issymbol(all_lines[line_i - 1][col_i]) ||
            issymbol(all_lines[line_i - 1][col_i + 1]) ||
            issymbol(all_lines[line_i - 1][col_i + 2]) ||
            issymbol(all_lines[line_i - 1][col_i + 3]) ||
            issymbol(all_lines[line_i][col_i - 1]) ||
            issymbol(all_lines[line_i][col_i + 3]) ||
            issymbol(all_lines[line_i + 1][col_i - 1]) ||
            issymbol(all_lines[line_i + 1][col_i]) ||
            issymbol(all_lines[line_i + 1][col_i + 1]) ||
            issymbol(all_lines[line_i + 1][col_i + 2]) ||
            issymbol(all_lines[line_i + 1][col_i + 3])) {
          printf("symbol");
          res += num;
        }
        printf("%d%d: %d\t", line_i, col_i, num);
        col_i += 3;
      } else if (isdigit(curr_char) && isdigit(next_char)) {
        int num = (curr_char - 48) * 10 + (next_char - 48);
        if (issymbol(all_lines[line_i - 1][col_i - 1]) ||
            issymbol(all_lines[line_i - 1][col_i]) ||
            issymbol(all_lines[line_i - 1][col_i + 1]) ||
            issymbol(all_lines[line_i - 1][col_i + 2]) ||
            issymbol(all_lines[line_i][col_i - 1]) ||
            issymbol(all_lines[line_i][col_i + 2]) ||
            issymbol(all_lines[line_i + 1][col_i - 1]) ||
            issymbol(all_lines[line_i + 1][col_i]) ||
            issymbol(all_lines[line_i + 1][col_i + 1]) ||
            issymbol(all_lines[line_i + 1][col_i + 2])) {
          printf("symbol");
          res += num;
        }
        printf("%d%d: %d\t", line_i, col_i, num);
        col_i += 2;
      } else if (isdigit(curr_char)) {
        int num = curr_char - 48;
        if (issymbol(all_lines[line_i - 1][col_i - 1]) ||
            issymbol(all_lines[line_i - 1][col_i]) ||
            issymbol(all_lines[line_i - 1][col_i + 1]) ||
            issymbol(all_lines[line_i][col_i - 1]) ||
            issymbol(all_lines[line_i][col_i + 1]) ||
            issymbol(all_lines[line_i + 1][col_i - 1]) ||
            issymbol(all_lines[line_i + 1][col_i]) ||
            issymbol(all_lines[line_i + 1][col_i + 1])) {
          printf("symbol");
          res += num;
        }
        printf("%d%d: %d\t", line_i, col_i, num);
        col_i++;
      } else {
        printf("%d%d: %c\t", line_i, col_i, curr_char);
        col_i++;
      }
    }
    printf("\n");
    line_i++;
  }
  printf("Result: %d\n", res);

  return 0;
}
