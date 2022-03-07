#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include <eve/views/iota.hpp>
#include <eve/views/reverse.hpp>
#include "detail/print.hpp"

int main()
{
  std::vector<int> v(10);
  eve::algo::iota(v, 1);
  auto v_as_doubles = eve::views::convert(v, eve::as<double>{});
  std::vector<float> vm(10);
  eve::algo::transform_to(v_as_doubles, vm, [](auto i){return i*20.3; });
  auto v_as_int8 = eve::views::convert(vm, eve::as<std::int8_t>{});


  std::cout << " <- std::vector<int> v(10);\n";
  std::cout << " -> auto v_as_doubles = eve::views::convert(v, eve::as<double>{});\n";
  std::cout << " -> std::vector<float> vm(10);\n";
  std::cout << " <- eve::algo::transform_to(v_as_doubles, vm, [](auto i){return i*20.3; });\n";
  std::cout << " <- auto v_as_int8 = eve::views::convert(vm, eve::as<std::int8_t>{});\n";
  std::cout << " <- auto v_as_int8 = eve::views::convert(vm, eve::as<std::int8_t>{});\n";

  std::cout << " -> v                                   = "; eve::detail::print(v);
  std::cout << " -> v_as_doubles                        = "; eve::detail::print(v_as_doubles);
  std::cout << " -> vm                                  = "; eve::detail::print(vm);
  std::cout << " -> v_as_int8                           = "; eve::detail::print(v_as_int8);
  return 0;
}
