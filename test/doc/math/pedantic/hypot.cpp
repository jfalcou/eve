#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iomanip>
#include <iostream>
#include <cmath>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, eve::inf(eve::as(1.0f)), -3.0f, eve::smallestposval(eve::as<float>())/2};
  wide_ft qf = {-4,    eve::nan(eve::as(1.0f)), -2, -12};

  std::cout << "---- simd" << std::setprecision(10) << '\n'
            << "<- pf                       = " << pf << '\n'
            << "<- qf                       = " << qf << '\n'
            << "-> pedantic(hypot)(pf, qf)  = " << eve::pedantic(eve::hypot)(pf, qf) << '\n';


  std::cout << eve::pedantic(eve::hypot)(5.0, 1.0e-305) << std::endl;
  return 0;
}
