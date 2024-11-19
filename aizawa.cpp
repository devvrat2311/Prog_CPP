#include <cstdio>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

int main() {
  string str1, str2;
  cout << "Enter 2 separate strings\n";
  getline(cin, str1);
  getline(cin, str2);
  cout << "You have entered two strings\n";

  if(str1.compare(str2) == 0) {
    cout << "\"" << str1 << "\" == \"" << str2 << "\"" << endl;
  } else if(str1 > str2) {
    cout << "\"" << str1 << "\" > \"" << str2 << "\"" << endl;
  } else {
    cout << "\"" << str1 << "\" < \"" << str2 << "\"" << endl;
  }

  int sizeofstring = str2.size();
  char *ptr = str1.data();
  int count = 0;
  while(*ptr != '\0'){
    count++;
    ptr++;
  }
  cout << count << endl;
  cout << str1.max_size()<< endl;

  return 0;
}
