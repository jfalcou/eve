#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "print.hpp"

int main()
{
  std::vector<int> v{2,4,6,8,10,12,14,16,18,20,22,24,26};
  std::vector<int> w{1,2,3,4,5,6,7,8};

  std::cout << " -> v                                                      = ";
  doc_utils::print(v);

  std::cout << " <- eve::algo::inclusive_scan_inplace(v, 0)                = ";
  eve::algo::inclusive_scan_inplace(v, 0);
  doc_utils::print(v);

  std::cout << " <- eve::algo::inclusive_scan_inplace(w, {eve::mul, 1}, 1) = ";
  eve::algo::inclusive_scan_inplace(w, std::pair{eve::mul, 1}, 1);
  doc_utils::print(w);

  return 0;
}
