#include <iostream>
#include <vector>

using namespace std;

vector<char> compress(vector<char> chars) {
  vector<char> newChars;
  char currentChar = chars[0]; //this value will not occur in original Chars vector 
  int currentCharCount = 0;

  for(int i = 0; i < chars.size(); ++i) {
    if(chars[i] == currentChar) {
      currentCharCount++;
    } else {
      currentChar = chars[i];
      currentCharCount = 1;
    }
    if(currentCharCount == 1){
      newChars.push_back(currentChar);
    }
  }
  return newChars;
}

int main() {
  vector<char> chars = {'a', 'a', 'a', 'b', 'b', 'b', 'b', 'c', 'c', 'c', 'c'};
  vector<char> newChars = compress(chars);
  for(int i = 0; i < newChars.size(); ++i)
    cout << newChars[i] << " ";
  cout << endl;
}