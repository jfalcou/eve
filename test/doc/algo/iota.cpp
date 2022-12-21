#include <eve/module/algo.hpp>
#include <iostream>
#include "print.hpp"

int main()
{
  auto vr = eve::views::iota(0.5f, 5);

  std::cout << " <- eve::views::iota(0.5f, 5) = ";
  doc_utils::print(vr);

  return 0;
}
