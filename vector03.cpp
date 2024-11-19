#include <iostream>
#include <vector>
#include <iterator>

int main() {
  int N;
  std::vector<int> nums;
  nums.reserve(N);
  std::copy(std::istream_iterator<int>(std::cin),
            std::istream_iterator<int>(),
            std::back_inserter(nums));

  for(auto x : nums) {
    std::cout << x << ' ';
  }
  std::cout << std::endl;
}
