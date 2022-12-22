#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <iostream>
#include <vector>
#include "print.hpp"

int main()
{
  std::vector<int> v{1,2,3,4,5,6,7,8,9,10,11,12};
  std::vector<int> w(v.size());

  std::cout << " -> v                                                      = ";
  doc_utils::print(v);

  std::cout << " <- eve::algo::inclusive_scan_to(v, w, {eve::mul, 1}, 1)   = ";
  eve::algo::inclusive_scan_to(v, w, std::pair{eve::mul, 1}, 1);
  doc_utils::print(w);

  std::cout << " <- eve::algo::inclusive_scan_inplace(v, 0)                = ";
  eve::algo::inclusive_scan_inplace(v, 0);
  doc_utils::print(v);

  return 0;
}
