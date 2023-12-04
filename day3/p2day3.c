#include <ctype.h>
#include <stdio.h>

int issymbol(int in_char) {
  return (in_char != '.') && !isdigit(in_char) && (in_char != -1) &&
         (in_char != '\n');
}

int get_num(int prev_prev_char, int prev_char, int curr_num, int next_char,
            int next_next_char) {
  int num = 0;
  if (isdigit(prev_prev_char) && isdigit(prev_char)) {
    num = (prev_prev_char - 48) * 100 + (prev_char - 48) * 10 + (curr_num - 48);
  } else if (isdigit(prev_char) && isdigit(next_char)) {
    num = (prev_char - 48) * 100 + (curr_num - 48) * 10 + (next_char - 48);
  } else if (isdigit(next_char) && isdigit(next_next_char)) {
    num = (curr_num - 48) * 100 + (next_char - 48) * 10 + (next_next_char - 48);
  } else if (isdigit(prev_char)) {
    num = (prev_char - 48) * 10 + (curr_num - 48);
  } else if (isdigit(next_char)) {
    num = (curr_num - 48) * 10 + (next_char - 48);
  } else {
    num = curr_num - 48;
  }
  return num;
}

int main() {
  char *path = "input.txt";
  FILE *file = fopen(path, "r");
  const int MAX_LINES = 500;
  const int MAX_COLS = 500;
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

  int final_res = 0;
  int line_i = 1;
  while (line_i < MAX_LINES && all_lines[line_i][1] != -1) {
    int col_i = 1;
    int *curr_line = all_lines[line_i];
    while (col_i < MAX_COLS && all_lines[line_i][col_i] != '\n') {
      int curr_char = curr_line[col_i];
      if (curr_char == '*') {
        int connections = 0;
        int curr_num;
        int prev_char;
        int prev_prev_char;
        int next_char;
        int next_next_char;
        int top_left = 0;
        int top_middle = 0;
        int top_right = 0;
        int left = 0;
        int right = 0;
        int all_top = 0;
        int bottom_left = 0;
        int bottom_middle = 0;
        int all_bottom = 0;
        int bottom_right = 0;
        if (isdigit(all_lines[line_i - 1][col_i - 1]) &&
            isdigit(all_lines[line_i - 1][col_i]) &&
            isdigit(all_lines[line_i - 1][col_i + 1])) {
          connections += 1;
          curr_num = all_lines[line_i - 1][col_i];
          prev_char = all_lines[line_i - 1][col_i - 1];
          prev_prev_char = all_lines[line_i - 1][col_i - 2];
          next_char = all_lines[line_i - 1][col_i + 1];
          next_next_char = all_lines[line_i - 1][col_i + 2];
          all_top = get_num(prev_prev_char, prev_char, curr_num, next_char,
                            next_next_char);
          printf("Connection top: %d   ", all_top);
        } else {
          if (isdigit(all_lines[line_i - 1][col_i - 1])) {
            connections += 1;
            curr_num = all_lines[line_i - 1][col_i - 1];
            prev_char = all_lines[line_i - 1][col_i - 2];
            prev_prev_char = all_lines[line_i - 1][col_i - 3];
            next_char = all_lines[line_i - 1][col_i];
            next_next_char = all_lines[line_i - 1][col_i + 1];
            top_left = get_num(prev_prev_char, prev_char, curr_num, next_char,
                               next_next_char);
            printf("Connection top left: %d   ", top_left);
          }
          if (isdigit(all_lines[line_i - 1][col_i + 1])) {
            connections += 1;
            curr_num = all_lines[line_i - 1][col_i + 1];
            prev_char = all_lines[line_i - 1][col_i];
            prev_prev_char = all_lines[line_i - 1][col_i - 1];
            next_char = all_lines[line_i - 1][col_i + 2];
            next_next_char = all_lines[line_i - 1][col_i + 3];
            top_right = get_num(prev_prev_char, prev_char, curr_num, next_char,
                                next_next_char);
            printf("Connection top right: %d   ", top_right);
          }
          if (isdigit(all_lines[line_i - 1][col_i]) && top_left == 0 &&
              top_right == 0) {
            connections += 1;
            curr_num = all_lines[line_i - 1][col_i];
            prev_char = all_lines[line_i - 1][col_i - 1];
            prev_prev_char = all_lines[line_i - 1][col_i - 2];
            next_char = all_lines[line_i - 1][col_i + 1];
            next_next_char = all_lines[line_i - 1][col_i + 2];
            top_middle = get_num(prev_prev_char, prev_char, curr_num, next_char,
                                 next_next_char);
            printf("Connection middle: %d   ", top_middle);
          }
        }
        if (isdigit(all_lines[line_i][col_i - 1])) {
          connections += 1;
          curr_num = all_lines[line_i][col_i - 1];
          prev_char = all_lines[line_i][col_i - 2];
          prev_prev_char = all_lines[line_i][col_i - 3];
          next_char = all_lines[line_i][col_i];
          next_next_char = all_lines[line_i][col_i + 1];
          left = get_num(prev_prev_char, prev_char, curr_num, next_char,
                         next_next_char);
          printf("Connection left: %d   ", left);
        }
        if (isdigit(all_lines[line_i][col_i + 1])) {
          connections += 1;
          curr_num = all_lines[line_i][col_i + 1];
          prev_char = all_lines[line_i][col_i];
          prev_prev_char = all_lines[line_i][col_i - 1];
          next_char = all_lines[line_i][col_i + 2];
          next_next_char = all_lines[line_i][col_i + 3];
          right = get_num(prev_prev_char, prev_char, curr_num, next_char,
                          next_next_char);
          printf("Connection right: %d   ", right);
        }
        if (isdigit(all_lines[line_i + 1][col_i - 1]) &&
            isdigit(all_lines[line_i + 1][col_i]) &&
            isdigit(all_lines[line_i + 1][col_i + 1])) {
          connections += 1;
          curr_num = all_lines[line_i + 1][col_i];
          prev_char = all_lines[line_i + 1][col_i - 1];
          prev_prev_char = all_lines[line_i + 1][col_i - 2];
          next_char = all_lines[line_i + 1][col_i + 1];
          next_next_char = all_lines[line_i + 1][col_i + 2];
          all_bottom = get_num(prev_prev_char, prev_char, curr_num, next_char,
                               next_next_char);
          printf("Connection bottom: %d   ", all_bottom);
        } else {
          if (isdigit(all_lines[line_i + 1][col_i - 1])) {
            connections += 1;
            curr_num = all_lines[line_i + 1][col_i - 1];
            prev_char = all_lines[line_i + 1][col_i - 2];
            prev_prev_char = all_lines[line_i + 1][col_i - 3];
            next_char = all_lines[line_i + 1][col_i];
            next_next_char = all_lines[line_i + 1][col_i + 1];
            bottom_left = get_num(prev_prev_char, prev_char, curr_num,
                                  next_char, next_next_char);
            printf("Connection bottom left: %d   ", bottom_left);
          }
          if (isdigit(all_lines[line_i + 1][col_i + 1])) {
            connections += 1;
            curr_num = all_lines[line_i + 1][col_i + 1];
            prev_char = all_lines[line_i + 1][col_i];
            prev_prev_char = all_lines[line_i + 1][col_i - 1];
            next_char = all_lines[line_i + 1][col_i + 2];
            next_next_char = all_lines[line_i + 1][col_i + 3];
            bottom_right = get_num(prev_prev_char, prev_char, curr_num,
                                   next_char, next_next_char);
            printf("Connection bottom right: %d   ", bottom_right);
          }
          if (isdigit(all_lines[line_i + 1][col_i]) && bottom_right == 0 &&
              bottom_left == 0) {
            connections += 1;
            curr_num = all_lines[line_i + 1][col_i];
            prev_char = all_lines[line_i + 1][col_i - 1];
            prev_prev_char = all_lines[line_i + 1][col_i - 2];
            next_char = all_lines[line_i + 1][col_i + 1];
            next_next_char = all_lines[line_i + 1][col_i + 2];
            bottom_middle = get_num(prev_prev_char, prev_char, curr_num,
                                    next_char, next_next_char);
            printf("Connection bottom middle: %d   ", bottom_middle);
          }
        }
        col_i++;
        int res = 1;
        printf("connections: %d ", connections);
        if (connections == 2) {
          if (top_left > 0) {
            res *= top_left;
          }
          if (top_middle > 0) {
            res *= top_middle;
          }
          if (top_right > 0) {
            res *= top_right;
          }
          if (bottom_left > 0) {
            res *= bottom_left;
          }
          if (bottom_middle > 0) {
            res *= bottom_middle;
          }
          if (bottom_right > 0) {
            res *= bottom_right;
          }
          if (right > 0) {
            res *= right;
          }
          if (left > 0) {
            res *= left;
          }
          if (all_top > 0) {
            res *= all_top;
          }
          if (all_bottom > 0) {
            res *= all_bottom;
          }
          printf("Res: %d ", res);
          final_res += res;
        }
      } else {
        printf("%d%d: %c\t", line_i, col_i, curr_char);
        col_i++;
      }
    }
    printf("\n");
    line_i++;
  }
  printf("Result: %d\n", final_res);

  return 0;
}
