#include <eve/module/core.hpp>
#include <eve/module/algo.hpp>
#include <iostream>
#include <vector>
#include "print.hpp"

int main()
{
  std::vector<double>  v = {2.5,6.8,-10.62,3.2,-8.8,2.7,-6.66,8.5,-2.01,4.8};

  std::cout << " -> v                                              = ";
  doc_utils::print(v);

  std::cout << " -> eve::views::convert(v, eve::as<std::int8_t>{}) = ";
  doc_utils::print(eve::views::convert(v, eve::as<std::int8_t>{}));

  return 0;
}
