#include <eve/module/algo.hpp>
#include <iostream>
#include "print.hpp"

int main()
{
  auto vr = eve::views::iota_with_step(0.5f, 2.0f, 5);

  std::cout << " <- eve::views::iota_with_step(0.5f, 2.0, 5) = ";
  doc_utils::print(vr);

  return 0;
}
