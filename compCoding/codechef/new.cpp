#include <iostream>

int main() {
  int t;
  std::cin >> t; // testcases
  while (t--) {
    // input
    int n, k;
    std::cin >> n >> k;

    int count = k; // count of even integers to see if the input even has the number of evens required
    int *arr = new int[n];
    for (int i = 0; i < n; ++i) {
      std::cin >> arr[i];
      if (arr[i] % 2 == 0)
        count--;
    }

    if(count > 0) {
      std::cout << "NO";
    } else {
      std::cout << "YES";
    }

    delete[] arr;
  }
  return 0;
}
