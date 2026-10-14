#include <iostream>
#include <cmath>
bool clear(char* a);
bool text(char* a);
bool put(char* a);
bool print(char* a);
bool equal(char* a, char * b);
bool pre_equal(char* a, char * b);
bool InPlace(int x, int y);
char clear_char[] = {'c', 'l', 'e', 'a', 'r', '\0'};
char text_char[] = {'t', 'e', 'x', 't', '\0'};
char put_char[] = {'p', 'u', 't', '\0'};
char print_char[] = {'p', 'r', 'i', 'n', 't', '\0'};
char quit_char[] = {'q', 'u', 'i', 't', '\0'};

char arr[5][10] = {
  {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
  {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
  {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
  {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
  {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}
};



int main()
{
  int balance_int = 0;

  while (true) {
    char* a = new char[200];
    int i = 0;
    char c;
    int t;
    bool endline = false;
    std::pair<char*, bool (*)(char*)> funcions[] = {{clear_char, &clear},
                                          {text_char, &text},
                                          {put_char, &put},
                                          {print_char, &print}};
    while ((std::cin.get(c)) && (c != '\n')) {
      a[i++] = c;
    }
    a[i++] = '\0';
    if (equal(a, quit_char)) {
      break;
    }
    bool error_value = false;
    for (int i = 0; i < 4; i++) {
      if (pre_equal(a, funcions[i].first)) {
        error_value = funcions[i].second(a);
      }
    }
    if (not(error_value)) {
      std::cout << "error\n";
    }
    delete[] a;
  }
  return 0;
}
bool equal(char* a, char * b) {
  int i;
  for (i = 0; a[i] != '\0' && b[i] != '\0'; i++) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  if  (a[i] == '\0' && b[i] == '\0') {
    return true;
  }
  return false;
}

bool pre_equal(char* a, char * b) {
  for (int i = 0; a[i] != '\0' && b[i] != '\0'; i++) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}
bool GetNumber(char* a, int *start, int* ans, bool next) {
  int anscount = 0;
  int i = *start;
  for (i; a[i] != '\0' && a[i] != ' '; i++) {
    if (a[i] < '0' || a[i] > '9') {
      return false;
    }
    anscount *= 10; 
    anscount += (a[i] - '0');
  }
  if (i > *start && (next != (a[i] == '\0'))) {
    *ans = anscount;
    *start = i;
    return true;
  }
  return false;
}

bool putwithoutreading(char a, int x, int y) {
  if (InPlace(x, y)) {
    arr[y][x] = a;
    return true;
  } 
  return false;
}

bool InPlace(int x, int y) {
  if (0 <= x && x < 10 && 0 <= y && y <= 4) {
    return true;
  }
  return false;
}

bool GetWord (char* a, int *start, bool endline) {
  int i = *start;
  int j = 0;
  char ansstrorage[200];
  for (i; a[i] != '\0' && a[i] != ' '; i++) {
    ansstrorage[j] = a[i];
    j++;
  }
  ansstrorage [i] = '\0';
  if (i > *start && not(endline && a[i] != '\0')) {
    *start = i;
    return true;
  }
  return false;
} 
bool clear(char* a) {
  if (equal(a, clear_char)) {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 10; j++) {
        arr[i][j] = ' ';
      }
    }
    return true;
  }
  return false;
  }
bool text(char* a) {
  int x;
  int y;
  int iterator = 5;
  if(GetNumber(a, &iterator, &x, true)) {
    iterator++;
    if (GetNumber(a, &iterator, &y, true)) {
      iterator++;
      int StartWord = iterator;
      bool bool1 = GetWord(a, &iterator, true);
      bool bool2 = InPlace(x + iterator - StartWord - 1, y);
      if (bool1 && bool2) {
        for (int i = StartWord; i < iterator; i++) {
          putwithoutreading(a[i], x + i - StartWord, y);
        }
        return true;
      }
    }
  }
  return false;
}

bool put(char* a) {
  int x;
  int y;
  int iterator = 4;
  if(GetNumber(a, &iterator, &x, true)) {
    iterator++;
    if (GetNumber(a, &iterator, &y, true)) {
      if (a[iterator + 2] == '\0') {
        if (putwithoutreading (a[iterator + 1], x, y)) {
          return true;
        } 
      }
    }
  }
  return false;
}
bool print(char* a) {
  if (equal(a, print_char)) {
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 10; j++) {
        std::cout << arr[i][j];
      }
      std::cout << '\n';
    }
    return true;
  }
  return false;
}