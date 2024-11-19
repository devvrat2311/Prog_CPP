#include <iostream>
#include <vector>

template<typename T> //Easier way to define this print function only once for all basic types
void print(int id, const std::vector<T>& container)
{
  std::cout << id << ". ";
  for( const T& x : container )
    std::cout << x << ' ';
  std::cout << std::endl;
}

int main()
{
  std::vector<char> c2(10, 'a');
  print(0, c2);

  std::vector<int> c1(10, 100);
  print(1, c1);

  auto it = c1.begin();
  it = c1.insert(it, 200);
  print(2, c1);

  auto it2 = c2.begin();
  it2 = c2.insert(it2, 'b');
  print(3, c2);

  c1.insert(it, 2, 300);
  print(4, c1);
}
