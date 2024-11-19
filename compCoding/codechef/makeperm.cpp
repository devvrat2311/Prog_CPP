// codechef MAKEPERM - solved 
#include <iostream>
#include <limits>
#include <vector>

void merge_sort(std::vector<int> &A, int begin_index, int end_index);
void merge(std::vector<int> &A, int begin_index, int mid_index, int end_index);

int main() {
  int n;
  std::cin >> n;

  std::vector<int> array(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> array[i];
  }

  merge_sort(array, 0, n - 1);

  bool verdict = true;
  for (int i = 0; i < n; ++i) {
    if (array[i] > i + 1) {
      verdict = false;
      break;
    }
  }

  if (verdict) {
    std::cout << "YES \n";
  } else {
    std::cout << "NO \n";
  }

  return 0;
}

// Merge Sort
void merge_sort(std::vector<int> &A, int begin_index, int end_index) {
  if (begin_index < end_index) {
    int mid_index =
        (begin_index + end_index) / 2; // int automatically sets as floor int
    merge_sort(A, begin_index, mid_index);
    merge_sort(A, mid_index + 1, end_index);
    merge(A, begin_index, mid_index, end_index);
  }
  return;
}

// Merge procedure
void merge(std::vector<int> &A, int begin_index, int mid_index, int end_index) {
  int n1 = mid_index - begin_index + 1;
  int n2 = end_index - mid_index;

  std::vector<int> L(n1 + 1);
  std::vector<int> R(n2 + 1);

  for (int i = 0; i < n1; ++i) {
    L[i] = A[begin_index + i];
  }
  L[n1] = std::numeric_limits<int>::max(); // represents infinity, called a
                                           // sentinel card

  for (int i = 0; i < n2; ++i) {
    R[i] = A[mid_index + 1 + i];
  }
  R[n2] = std::numeric_limits<int>::max(); // represents infinity, called a
                                           // sentinel card

  /*we add the last entry as infinity so that if either
  of the arrays (Left or Right) reaches the end of all elements,
  there is still one infinite element left to compare the
  elements of the the other array with, which will result in
  a straightforward dumping of all the elements left in the other
  array into the merged array*/

  int i = 0;
  int j = 0;

  for (int k = begin_index; k < end_index + 1; ++k) {
    if (L[i] <= R[j]) {
      A[k] = L[i];
      i = i + 1;
    } else {
      A[k] = R[j];
      j = j + 1;
    }
  }
}
