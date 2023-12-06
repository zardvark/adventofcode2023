#include <ctype.h>
#include <stdio.h>

#define MAX_LINES 250
#define MAX_COLS 250
#define WINNING_NO_COUNT 10
int ctoi(int in_c) { return in_c - 48; }

int main() {
  char *path = "input.txt";
  FILE *fp = fopen(path, "r");
  int all_lines[MAX_LINES][MAX_COLS] = {0};
  int i = 0;
  int j = 0;
  int c = getc(fp);
  while (c != EOF) {
    all_lines[i][j] = c;
    if (c == '\n') {
      j = 0;
      i++;
    } else {
      j++;
    }
    c = getc(fp);
  }

  int res = 0;
  int line_i = 0;
  static int copies[MAX_LINES + 1] = {0};
  int m_i = 0;
  while (line_i < MAX_LINES && all_lines[line_i][0] != 0) {
    int winning_numbers[WINNING_NO_COUNT] = {0};
    int winning_numbers_i = 0;
    int col_i = 0;
    int game_gone = 0;
    int winning_numbers_gone = 0;
    int matches = 0;
    while (col_i < MAX_COLS && all_lines[line_i][col_i] != '\n') {
      int curr_char = all_lines[line_i][col_i];
      int next_char = all_lines[line_i][col_i + 1];
      if (curr_char == ':') {
        game_gone = 1;
      }
      if (game_gone && isdigit(next_char) && isdigit(curr_char)) {
        int curr_num = ctoi(curr_char) * 10 + ctoi(next_char);
        winning_numbers[winning_numbers_i] = curr_num;
        winning_numbers_i++;
        col_i++;
      } else if (game_gone && isdigit(curr_char)) {
        int curr_num = ctoi(curr_char);
        winning_numbers[winning_numbers_i] = curr_num;
        winning_numbers_i++;
      }
      if (curr_char == '|') {
        winning_numbers_gone = 1;
      }
      if (winning_numbers_gone && isdigit(next_char) && isdigit(curr_char)) {
        int curr_num = ctoi(curr_char) * 10 + ctoi(next_char);
        for (int y = 0; y < WINNING_NO_COUNT; y++) {
          if (winning_numbers[y] == curr_num) {
            matches++;
          }
        }
        col_i++;
      } else if (winning_numbers_gone && isdigit(curr_char)) {
        int curr_num = ctoi(curr_char);
        winning_numbers[winning_numbers_i] = curr_num;
        winning_numbers_i++;
        for (int z = 0; z < WINNING_NO_COUNT; z++) {
          if (winning_numbers[z] == curr_num) {
            matches++;
          }
        }
      }
      col_i++;
    }

    int curr_copies = copies[line_i];
    int total_copies = 1 + curr_copies;
    for (int j = 0; j < total_copies; j++) {
      for (int i = line_i; i < line_i + matches; i++) {
        copies[i + 1] = copies[i + 1] + 1;
      }
    }
    res += total_copies;
    printf("curr copies %d", total_copies);

    if (matches > 0) {
      int points = 1 << (matches - 1);
      // res += points;
      printf("Points found: %d\n", points);
    }
    for (int m_i = 0; m_i < 50; m_i++) {
      printf("i: %d\t, m[i] %d", m_i, copies[m_i]);
    }
    printf("%c", '\n');
    line_i++;
  }
  printf("Result: %d\n", res);
  return 0;
}
