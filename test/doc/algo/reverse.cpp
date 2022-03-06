#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include <eve/views/iota.hpp>
#include <eve/views/reverse.hpp>
#include "detail/print.hpp"

int main()
{
  std::vector<float> v(10), r1(10);
  auto vv = eve::views::iota(1.0f, 10);
  eve::algo::copy(vv, v);
  eve::algo::reverse_copy(v, r1);
  auto r2 = eve::views::reverse(vv);

  std::cout << " <- std::vector<float> r1(10);\n";
  std::cout << " <- auto vv = eve::views::iota(1.0f, 10);;\n";
  std::cout << " -> eve::algo::reverse_copy(v, r1);\n";
  std::cout << " -> auto r2 = eve::views::reverse(vv);\n";

  std::cout << " -> v                                   = "; eve::detail::print(v);
  std::cout << " -> r1                                  = "; eve::detail::print(r1);
  std::cout << " -> r2                                  = "; eve::detail::print(r2);
  return 0;
}
