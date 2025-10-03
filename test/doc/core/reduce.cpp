#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<std::int16_t, eve::fixed<4>>;

int main()
{
  wide_ft pf = {0.5f,1.5f,2.5f,3.f};
  wide_it qi = {2,3,4,5};

  auto const summ  = [](auto a, auto b) { return a+b; };
  auto const prod = [](auto a, auto b) { return a*b; };

  std::cout << "---- simd" << '\n'
            << "<- pf             = " << pf << '\n'
            << "-> reduce(pf,summ) = " << eve::reduce(pf, summ) << '\n'
            << "<- qi             = " << qi << '\n'
            << "-> reduce(qi,prod) = " << eve::reduce(qi, prod) << '\n';

  std::cout << "---- simd with splat" << '\n'
            << "<- pf                    = " << pf << '\n'
            << "-> reduce[splat](pf,summ) = " << eve::reduce[eve::splat](pf, summ) << '\n'
            << "<- qi                     = " << qi << '\n'
            << "-> reduce[splat](qi,prod) = " << eve::reduce[eve::splat](qi, prod) << '\n';

  return 0;
}
