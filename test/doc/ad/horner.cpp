#include <eve/module/polynomial.hpp>
#include <eve/module/ad.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <list>
#include <vector>

using wide_ft = eve::wide<float, eve::fixed<4>>;
using wide_it = eve::wide<int   , eve::fixed<8>>;

int main()
{
  using eve::der;
  wide_ft x(0.5);

  std::cout << "---- simd" << '\n'
            << "<- x                                        = " << x  << '\n'
            << "-> horner(x, 1, 0, 0, 0)                  = " << eve::horner(x, 1, 0, 0, 0)     << '\n';
  {
    auto zz = eve::horner(eve::var(x), 1);
    std::cout          << "-> der(eve::horner(var(x), 1))          " << der(zz)  << '\n';
    auto zzz = eve::diff(eve::horner)(x, 1);
    std::cout          << "-> diff(horner)(x, 1)                   " << zzz  << '\n';
  }

  {
    auto zz = eve::horner(eve::var(x), 1, 0);
    std::cout          << "->  der(eve::horner(var(x), 1, 0))      " << der(zz)  << '\n';
    auto zzz = eve::diff(eve::horner)(x, 1, 0);
    std::cout          << "-> diff(horner)(x, 1, 0)                " << zzz  << '\n';
  }

  {
    auto zz = eve::horner(eve::var(x), 1, 0, 0);
    std::cout          << "-> der(eve::horner(var(x), 1, 0, 0))    " << der(zz)  << '\n';
    auto zzz = eve::diff(eve::horner)(x, 1, 0, 0);
    std::cout          << "-> diff(horner)(x, 1, 0, 0)             " << zzz  << '\n';
  }
  {
    auto zz = eve::horner(eve::var(x), 1, 0, 0, 0);
    std::cout          << "-> der(eve::horner(var(x), 1, 0, 0, 0)) " << der(zz)  << '\n';
    auto zzz = eve::diff(eve::horner)(x, 1, 0, 0, 0);
    std::cout          << "-> diff(horner)(x, 1, 0, 0, 0)          " << zzz  << '\n';
  }
   {
    auto zz = eve::horner(eve::var(x), 1, 0, 0, 0, 0);
    std::cout          << "-> der(eve::horner(var(x), 1, 0, 0, 0, 0)) " << der(zz)  << '\n';
    auto zzz = eve::diff(eve::horner)(x, 1, 0, 0, 0, 0);
    std::cout          << "-> diff(horner)(x, 1, 0, 0, 0, 0)          " << zzz  << '\n';
  }
   std::array<float, 5> p = {1, 0, 3, 0}; // x^3+x
   auto zz = eve::horner(eve::var(x), p);
   std::cout          << "-> der(eve::horner(var(x), p)) " << der(zz)  << '\n';
   return 0;
}
