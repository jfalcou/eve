#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <iostream>
#include <vector>
#include "print.hpp"

int main()
{
  std::vector<float> v(12);
  eve::algo::fill(v, 8.0);

  std::cout << " <- eve::algo::fill(v, 8.0);\n";

  std::cout << " -> v                      = ";
  doc_utils::print(v);

  return 0;
}
