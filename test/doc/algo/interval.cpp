#include <eve/algo.hpp>
#include <iostream>
#include <vector>
#include "detail/print.hpp"

int main()
{
  using eve::detail::print;
  using eve::views::interval_with_step;
  using eve::views::interval;

  std::cout << " -> interval_with_step(0.0f,  2.0f,  0.1f)  = "; print(interval_with_step(0.0f,  2.0f,  0.1f));
  std::cout << " -> interval_with_step(0.0f,  2.0f,  0.5f)  = "; print(interval_with_step(0.0f,  2.0f,  0.5f));
  std::cout << " -> interval_with_step(0.0f,  2.0f, -0.5f)  = "; print(interval_with_step(0.0f,  2.0f, -0.5f));
  std::cout << " -> interval_with_step(0.0f,  2.0f, -0.5f)  = "; print(interval_with_step(0.0f, -2.0f, -0.5f));
  std::cout << " -> interval_with_step(0.0f, -2.0f,  0.5f)  = "; print(interval_with_step(0.0f, -2.0f,  0.5f));

  std::cout << " -> raw(interval_with_step)(0.0f,  2.0f,  0.1f)  = "; print(eve::raw(interval_with_step)(0.0f,  2.0f,  0.1f));
  std::cout << " -> raw(interval_with_step)(0.0f,  2.0f,  0.5f)  = "; print(eve::raw(interval_with_step)(0.0f,  2.0f,  0.5f));
  std::cout << " -> raw(interval_with_step)(0.0f,  2.0f, -0.5f)  = "; print(eve::raw(interval_with_step)(0.0f,  2.0f, -0.5f));
  std::cout << " -> raw(interval_with_step)(0.0f,  2.0f, -0.5f)  = "; print(eve::raw(interval_with_step)(0.0f, -2.0f, -0.5f));
  std::cout << " -> raw(interval_with_step)(0.0f, -2.0f,  0.5f)  = "; print(eve::raw(interval_with_step)(0.0f, -2.0f,  0.5f));

  std::cout << " -> interval(-3.2, 4.5)                       = "; print(interval(-3.2, 4.5));
  std::cout << " -> interval(1.0f+2*eve::eps(as<float>(), 3.0f) = "; print(interval(1.0f+2*eve::eps(eve::as<float>()), 3.0f));
  std::cout << " -> raw(interval)(1.0f+2*eve::eps(as<float>(), 3.0f) = "; print(eve::raw(interval)(1.0f+2*eve::eps(eve::as<float>()), 3.0f));
   print(eve::raw(interval[eve::algo::unroll<1>])(1.0f+2*eve::eps(eve::as<float>()), 3.0f));
  return 0;
}
