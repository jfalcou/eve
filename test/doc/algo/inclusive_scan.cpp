#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "detail/print.hpp"

int main()
{
  std::vector<float> r1(5) , r2(5);
  eve::algo::fill(r1, 2.0f);
  eve::algo::fill(r2, 2.0f);

  eve::algo::inclusive_scan_inplace(r1, std::pair{eve::add, eve::zero}, 0.0f);
  eve::algo::inclusive_scan_inplace(r2, std::pair{eve::mul, 1.0f}, 1.0f);

  std::cout << " <- eve::algo::inclusive_scan_inplace(r1, std::pair{eve::add, eve::zero}, 0.0f);\n";
  std::cout << " <- eve::algo::inclusive_scan_inplace(r2, std::pair{eve::mul, 1.0f}, 1.0f);\n";
  std::cout << " -> r1                         = "; eve::detail::print(r1);
  std::cout << " -> r2                         = "; eve::detail::print(r2);
  return 0;
}
