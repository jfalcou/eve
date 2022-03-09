#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "detail/print.hpp"

int main()
{
  std::vector<float> r1(5), r2(5);
  auto vr1 = eve::views::iota_with_step(0.5f, 2.0f, 5);
  eve::algo::copy(vr1, r1);
  eve::algo::copy(vr1, r2);
  r2[2] = 100.0f;
  r2[4] = 12.0f;
  auto [m1, m2] = eve::algo::mismatch(r1, r2);
  std::cout << " <- auto [m1, m2] = eve::algo::mismatch(r1, r2);\n";
  std::cout << " -> first mismatch is " << eve::read(m1) << " != " << eve::read(m2) << std::endl;

  auto [n1, n2] = eve::algo::mismatch(vr1, r2);
  std::cout << " -> first mismatch is             " << eve::read(n1) << " != " << eve::read(n2) << std::endl;
  std::cout << " -> we have for the previous pair " << eve::read(--n1) << " == " << eve::read(--n2) << std::endl;
  auto print =  [](auto v){ for(auto i : v) {std::cout << i << ' ';};  std::cout << '\n';};
  std::cout << " -> r1                                  = "; print(r1);
  std::cout << " -> r2                                  = "; print(r2);
  return 0;
}
