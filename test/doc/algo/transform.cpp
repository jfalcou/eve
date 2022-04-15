#include <eve/module/math.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "print.hpp"

int main()
{
  std::vector<double> v = {2.5,6.8,-10.62,3.2,-8.8,2.7,-6.66,8.5,-2.01,4.8};
  std::vector<double> w(v.size());

  std::cout << " -> v                                                           =\n";
  doc_utils::print(v);

  std::cout << " <- eve::algo::transform_to(v,w,[](auto e){return e*2.5+1.3; })\n";
  eve::algo::transform_to(v, w, [](auto e){return e*2.5+1.3; });
  std::cout << " -> w                                                           =\n";
  doc_utils::print(w);

  std::cout << " <- eve::algo::transform_inplace(v, eve::log_abs)\n";
  eve::algo::transform_inplace(v, eve::log_abs);
  std::cout << " -> v                                                           =\n";
  doc_utils::print(v);

  return 0;
}
