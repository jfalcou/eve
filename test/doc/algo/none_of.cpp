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
  auto vr2 = eve::views::iota(-3.0, 5);
  eve::algo::copy(vr2, r2);
  std::cout << " <- std::vector<float> r1(5), r2(5);\n";
  std::cout << " <- auto vr1 = eve::views::iota_with_step(0.5f, 2.0f, 5);\n";
  std::cout << " <- eve::algo::copy(vr1, r1);\n";
  std::cout << " <- auto vr2 = eve::views::iota(-3.0, 5);\n";
  std::cout << " <- eve::algo::copy(vr2, r2);\n";
  std::cout << " <- std::vector<float> r2(5);\n";
  std::cout << " <- eve::algo::copy(vr, r2);;\n\n";
  std::cout << " -> eve::algo::none_of(r1, eve::is_ltz)  = "<< std::boolalpha << eve::algo::none_of(r1, eve::is_ltz)<< '\n';
  std::cout << " -> eve::algo::none_of(vr1, eve::is_ltz) = "<< std::boolalpha << eve::algo::none_of(vr1, eve::is_ltz)<< '\n';
  std::cout << " -> eve::algo::none_of(r2, eve::is_gtz)  = "<< std::boolalpha << eve::algo::none_of(r2, eve::is_gtz)<< '\n';
  std::cout << " -> eve::algo::none_of(vr2, eve::is_gtz) = "<< std::boolalpha << eve::algo::none_of(vr2, eve::is_gtz)<< '\n';

  std::cout << " -> r1                                  = "; eve::detail::print(r1);
  std::cout << " -> r2                                  = "; eve::detail::print(r2);
  return 0;
}
