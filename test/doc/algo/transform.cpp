#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include <eve/test/doc/algo/detail/print.hpp>


int main()
{
  std::vector<float> r1{1.0f, -2.3f, 5.0f, 0.0f, -1.0f};
  std::vector<float> r2(r1.size());
  float a = 10.0;
  float b = 5.0;
  eve::algo::transform_to(r1, r2, [a, b](auto e){return a*e+b; });
  std::cout << " -> r1                                  = "; eve::detail::print(r1);
  std::cout << " -> r2  (a*r1+b)                        = "; eve::detail::print(r2);
  eve::algo::transform_inplace(r2, eve::log_abs);
  std::cout << " -> r2  (log(|r2|)                      = "; eve::detail::print(r2);
  return 0;
}
