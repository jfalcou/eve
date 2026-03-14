// revision 1 TODO
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  {
    kumi::tuple xd{1.0, 2.0};
    kumi::tuple yd = kumi::map([](auto x){return 2*x+1; }, xd);
    eve::wide<double, eve::fixed<4>> x(0.5, 2.0, -2.5, 5.0);

    std::cout << "<- xd                                   = " << xd << '\n';
    std::cout << "<- yd                                   = " << yd  << '\n';
    std::cout << "<- x                                    = " << x  << '\n';

    std::cout << "-> neville(x, xd, yd)                   = " << eve::neville(x, 1.0, 2.0, 3.0, 5.0)<< '\n';
    std::cout << "-> neville(x, xd, yd)                   = " << eve::neville(x, kumi::cat(xd, yd)) << '\n';
    std::cout << "-> neville(x, xd, yd)                   = " << eve::neville(x, xd, yd) << '\n';
  }
   {
    kumi::tuple xd{1.0, 2.0, 3.0, 4.0};
    kumi::tuple yd = kumi::map([](auto x){return x*x; }, xd);
    eve::wide<double, eve::fixed<8>> x(0.5, 2.0, -2.5, 5.0,0.5, 2.0, -2.5, 5.0 );

    std::cout << "<- xd                                   = " << xd << '\n';
    std::cout << "<- yd                                   = " << yd  << '\n';
    std::cout << "<- x                                    = " << x  << '\n';

    std::cout << "-> neville(x, xd, yd)                   = " << eve::neville(x, 1.0, 2.0, 3.0, 4.0, 1.0, 4.0, 9.0, 16.0) << '\n';
    std::cout << "-> neville(x, xd, yd)                   = " << eve::neville(x, kumi::cat(xd, yd)) << '\n';
    std::cout << "-> neville(x, xd, yd)                   = " << eve::neville(x, xd, yd) << '\n';
  }
}
