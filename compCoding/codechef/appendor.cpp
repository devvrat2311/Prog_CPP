//codechef APPENDOR - solved 
#include <iostream>
#include <ostream>
#include <vector>

int bitwise_result(const std::vector<int>);

int main() {
  int t;
  std::cout << "Enter the no. of test cases: ";
  std::cin >> t;
  std::cout << '\n';

  while(t--) {
    int n , target;
    std::cout << "Enter size of the array , target value(space separated): ";
    std::cin >> n >> target;
    std::cout << '\n';

    std::cout << "Enter the " << n << " array values (space separated): ";
    std::vector<int> array(n);
    for(int i = 0; i < n; ++i) {
      std::cin >> array[i];
    }
    std::cout << '\n';

    int bit_res = bitwise_result(array);

    int diff = target - bit_res;

    int exor = target ^ bit_res;

    if(exor == diff) {
      std::cout << "the element to be added is: ";
      std::cout << exor;
      std::cout << '\n';
    } else {
      std::cout << -1;
      std::cout << "no such element exists \n";
    }
    std::cout << '\n';
  }
}

int bitwise_result(const std::vector<int> array) {
  int result = 0;
  for(auto x : array) {
    result |= x;
  }
  return result;
}
