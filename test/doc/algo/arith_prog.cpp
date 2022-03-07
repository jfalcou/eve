#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "detail/print.hpp"

// arith_prog is not a good name arithmetic_progression is too long but better
int main()
{
  std::vector<float> r1(5);
//  eve::algo::arith_prog(r1, 0.5f, 2.0f); // why this does not exists ?
  auto vr = eve::algo::views::arith_prog(0.5f, 2.0f, 5);
  eve::algo::copy(vr, r1);

  std::cout << " <- std::vector<float> r1(5);\n";
  std::cout << " <- vr = eve::views::arith_prog(0.5f, 2.0, 5);\n";
  std::cout << " -> vr = "; eve::detail::print(vr);
  std::cout << " -> r1 = "; eve::detail::print(r1);
  return 0;
}
