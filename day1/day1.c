#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int ctoi(int in) { return in - 48; }

int wordtoi(char letter) {
  // if (letter == 'o')
  return -1;
}

int main() {
  FILE *fp = fopen("input.txt", "r");
  int res = 0;
  int c = getc(fp);
  int all_lines[1200][200];
  int i = 0;
  int j = 0;
  for (int x = 0; x < 1200; x++) {
    for (int y = 0; y < 200; y++) {
      all_lines[x][y] = -1;
    }
  }
  while (c != EOF) {
    if (c == '\n') {
      j = 0;
      i++;
    } else {
      all_lines[i][j] = c;
      j++;
    }
    c = getc(fp);
  }
  fclose(fp);
  for (int curr_line = 0; curr_line < 1200; curr_line++) {
    int curr_col = 0;
    int curr_char = all_lines[curr_line][curr_col];
    int curr_res[2] = {-1, -1};
    while (curr_char != -1) {
      int as_int = -1;
      if (isdigit(curr_char)) {
        as_int = ctoi(curr_char);
      } else if (curr_char == 'o' &&
                 all_lines[curr_line][curr_col + 1] == 'n' &&
                 all_lines[curr_line][curr_col + 2] == 'e') {
        as_int = 1;
      } else if (curr_char == 't' &&
                 all_lines[curr_line][curr_col + 1] == 'w' &&
                 all_lines[curr_line][curr_col + 2] == 'o') {
        as_int = 2;
      } else if (curr_char == 't' &&
                 all_lines[curr_line][curr_col + 1] == 'h' &&
                 all_lines[curr_line][curr_col + 2] == 'r' &&
                 all_lines[curr_line][curr_col + 3] == 'e' &&
                 all_lines[curr_line][curr_col + 4] == 'e') {
        as_int = 3;
      } else if (curr_char == 'f' &&
                 all_lines[curr_line][curr_col + 1] == 'o' &&
                 all_lines[curr_line][curr_col + 2] == 'u' &&
                 all_lines[curr_line][curr_col + 3] == 'r') {
        as_int = 4;
      } else if (curr_char == 'f' &&
                 all_lines[curr_line][curr_col + 1] == 'i' &&
                 all_lines[curr_line][curr_col + 2] == 'v' &&
                 all_lines[curr_line][curr_col + 3] == 'e') {
        as_int = 5;
      } else if (curr_char == 's' &&
                 all_lines[curr_line][curr_col + 1] == 'i' &&
                 all_lines[curr_line][curr_col + 2] == 'x') {
        as_int = 6;
      } else if (curr_char == 's' &&
                 all_lines[curr_line][curr_col + 1] == 'e' &&
                 all_lines[curr_line][curr_col + 2] == 'v' &&
                 all_lines[curr_line][curr_col + 3] == 'e' &&
                 all_lines[curr_line][curr_col + 4] == 'n') {
        as_int = 7;
      } else if (curr_char == 'e' &&
                 all_lines[curr_line][curr_col + 1] == 'i' &&
                 all_lines[curr_line][curr_col + 2] == 'g' &&
                 all_lines[curr_line][curr_col + 3] == 'h' &&
                 all_lines[curr_line][curr_col + 4] == 't') {
        as_int = 8;
      } else if (curr_char == 'n' &&
                 all_lines[curr_line][curr_col + 1] == 'i' &&
                 all_lines[curr_line][curr_col + 2] == 'n' &&
                 all_lines[curr_line][curr_col + 3] == 'e') {
        as_int = 9;
      }
      curr_col++;
      curr_char = all_lines[curr_line][curr_col];
      if (curr_res[0] < 0 && as_int != -1) {
        curr_res[0] = as_int;
      } else if (as_int != -1) {
        curr_res[1] = as_int;
      }
    }
    if (curr_res[0] != -1) {
      int num;
      if (curr_res[1] == -1) {
        num = curr_res[0] * 11;
        printf("line %d %d\n", curr_line, num);
      } else {
        num = curr_res[0] * 10 + curr_res[1];
        printf("line %d %d\n", curr_line, num);
      }
      res += num;
    }
  }
  printf("final %d\n", res);
  return 0;
}
