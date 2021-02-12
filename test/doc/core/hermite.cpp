#include <eve/function/hermite.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>
#include <boost/math/special_functions/hermite.hpp>

using wide_ft = eve::wide<double, eve::fixed<8>>;
using wide_it = eve::wide<int   , eve::fixed<8>>;

int main()
{

  wide_ft pd = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  wide_it n = {0, 1, 2, 3, 4, 5, 6, 7};
  wide_ft x(2.0);

   std::cout << "---- simd" << '\n'
            << "<- pd               = " << pd << '\n'
            << "<- n                = " << n  << '\n'
            << "-> hermite(n, pd)   = " << eve::hermite(n, pd) << '\n'
            << "-> hermite(3, pd)   = " << eve::hermite(3, pd) << '\n'
            << "-> hermite(n, 2.0)  = " << eve::hermite(n, 2.0) << '\n'
            << "-> hermite(n, x)    = " << eve::hermite(n, x)   << '\n';

//  std::cout << "---- boost" << '\n'
//            << "-> hermite(0, 2.0)  = " << boost::math::hermite(0, 2.0) << '\n'
//            << "-> hermite(1, 2.0)  = " << boost::math::hermite(1, 2.0) << '\n'
//            << "-> hermite(2, 2.0)  = " << boost::math::hermite(2, 2.0) << '\n'
//            << "-> hermite(3, 2.0)  = " << boost::math::hermite(3, 2.0) << '\n'
//            << "-> hermite(4, 2.0)  = " << boost::math::hermite(4, 2.0) << '\n'
//            << "-> hermite(5, 2.0)  = " << boost::math::hermite(5, 2.0) << '\n'
//            << "-> hermite(6, 2.0)  = " << boost::math::hermite(6, 2.0) << '\n'
//            << "-> hermite(7, 2.0)  = " << boost::math::hermite(7, 2.0) << '\n';
//  std::cout << "---- scalar" << '\n'
//            << "-> hermite(0, 2.0)  = " << eve::hermite(0, 2.0) << '\n'
//            << "-> hermite(1, 2.0)  = " << eve::hermite(1, 2.0) << '\n'
//            << "-> hermite(2, 2.0)  = " << eve::hermite(2, 2.0) << '\n'
//            << "-> hermite(3, 2.0)  = " << eve::hermite(3, 2.0) << '\n'
//            << "-> hermite(4, 2.0)  = " << eve::hermite(4, 2.0) << '\n'
//            << "-> hermite(5, 2.0)  = " << eve::hermite(5, 2.0) << '\n'
//            << "-> hermite(6, 2.0)  = " << eve::hermite(6, 2.0) << '\n'
//            << "-> hermite(7, 2.0)  = " << eve::hermite(7, 2.0) << '\n';

//  double xd = 3.0;

//   std::cout << "---- scalar" << '\n'
//             << "<- xd               = " << xd << '\n'
//             << "-> hermite(4, xd)   = " << eve::hermite(4, xd) << '\n';


//   using wf = eve::wide<double, eve::fixed<2>>;
//   using wi = eve::wide<int   , eve::fixed<2>>;

//   wi i{0, 1};
//   wf f{2, 2};
//   wf g{1, 1};
//   wf ii{0, 1};
//   wf r = eve::if_else(eve::is_eqz(i), g, f);
//   wf r1= eve::if_else(eve::is_eqz(ii), g, f);
//   wf r2= eve::if_else(eve::is_eqz(i), eve::one, f);
//   std::cout << "i" << i << std::endl;
//   std::cout << "f" << f << std::endl;
//   std::cout << "r" << r << std::endl;
//   std::cout << "r1" << r1 << std::endl;
//   std::cout << "r2" << r2 << std::endl;

  return 0;
}
