#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>


using w_t = eve::wide<float, eve::fixed<4>>;

int main()
{

  w_t xd = {-0.3, 0.5, 0.0, 2.0};
  w_t x(0.2);
  kumi::tuple<float, float, float> cs {1, 2, 3};
  kumi::tuple<float, float >       ns {6, 7};

  std::cout << "---- simd" << '\n'
            << "<- xd                        = " << xd << '\n'
            << "<- x                         = " << x  << '\n'
            << "-> newton(x, 1, 2, 3, 6, 7)  = " << eve::newton(x, 1, 2, 3, 6, 7) << '\n'
            << "-> newton(xd, 1, 2, 3, 6, 7) = " << eve::newton(xd, 1, 2, 3, 6, 7) << '\n'
            << "-> newton(x, cs, ns)         = " << eve::newton(x, cs, ns) << '\n'
            << "-> newton(xd, cs, ns)        = " << eve::newton(xd, cs, ns) << '\n'
           ;

  double xs = 0.2;

  std::cout << "---- scalar" << '\n'
            << "<- xs                                  = " << xs << '\n'
            << "-> newton(xs, 1.0, 2.0, 3.0, 6.0, 7.0) = " << eve::newton(xs, 1.0, 2.0, 3.0, 6.0, 7.0) << '\n';


  return 0;
}
