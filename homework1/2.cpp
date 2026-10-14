#include <iostream>


char deposit_char[8] = {'d', 'e', 'p', 'o', 's', 'i', 't', '\0'};
char balance_char[8] = {'b', 'a', 'l', 'a', 'n', 'c', 'e', '\0'};
char withdraw_char[9] = {'w', 'i', 't', 'h', 'd', 'r', 'a', 'w', '\0'};
char reset_char[6] = {'r', 'e', 's', 'e', 't', '\0'};
char stop_char[5] = {'s', 't', 'o', 'p', '\0'};
int deposit(int bal, char* a);
int balance(int bal, char* a);
int withdraw(int bal, char* a);
int reset(int bal, char* a);
bool equal(char* a, char * b);
bool pre_equal(char* a, char * b);

int main()
{
  int balance_int = 0;
  char deposit_char[8] = {'d', 'e', 'p', 'o', 's', 'i', 't', '\0'};
  char balance_char[8] = {'b', 'a', 'l', 'a', 'n', 'c', 'e', '\0'};
  char withdraw_char[9] = {'w', 'i', 't', 'h', 'd', 'r', 'a', 'w', '\0'};
  char reset_char[6] = {'r', 'e', 's', 'e', 't', '\0'};
  char stop_char[5] = {'s', 't', 'o', 'p', '\0'};
  std::pair <char*, int (*)(int, char*)> funcs[] = { {deposit_char, &deposit},
                                              {withdraw_char, &withdraw},
                                              {balance_char, &balance},
                                              {reset_char, &reset}};
  while (true) {
    char* a = new char[200];
    int i = 0;
    char c;
    bool endline = false;
    while ((std::cin.get(c)) && (c != '\n')) {
      a[i++] = c;
    }
    a[i++] = '\0';
    if (equal(a, stop_char)) {
      break;
    }
    bool acting = false;
    int j = 0;
    int t = -1;
    for (j; j < 4; j++) { 
      if (pre_equal(funcs[j].first, a)) {
        t = funcs[j].second(balance_int, a);
      }
    }
    if (t == -1) {
      std::cout << "error" << "\n";
    }
    else {
      balance_int = t;
    }
    delete[] a;
  }
  return 0;
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

bool pre_equal(char* a, char * b) {
  for (int i = 0; a[i] != '\0' && b[i] != '\0'; i++) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
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

int deposit (int bal, char* a) {
  int i = 0;
  char c;
  int iterator = 8;
  int k;
  if (GetNumber(a, &iterator, &k, false) && k >= 0) {
    return bal + k;
  }
  return -1;
}

int balance (int bal, char* a) {
  if (equal(a, balance_char)) {
    std::cout << bal << "\n";
    return bal;
  }
  return -1;
}

int withdraw (int bal, char* a) {
  int i = 0;
  char c;
  int iterator = 9;
  int k;
  if (GetNumber(a, &iterator, &k, false) && k >= 0 && k <= bal) {
    return bal - k;
  }
  return -1;
}

int reset (int bal, char* a) {
  if (equal(a, reset_char)) {
    return 0;
  }
  return -1;
}