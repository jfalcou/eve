#include <eve/function/legendre.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>
#include <boost/math/special_functions/legendre.hpp>

using wide_ft = eve::wide<double, eve::fixed<8>>;
using wide_it = eve::wide<int   , eve::fixed<8>>;

int main()
{

  wide_ft xd = {0.5, -1.5, 0.1, -1.0, 19.0, 25.0, 21.5, 10000.0};
  wide_it n = {0, 1, 2, 3, 4, 5, 6, 7};
  wide_ft x(2.0);

  std::cout << "---- simd" << '\n'
            << "<- xd               = " << xd << '\n'
            << "<- n                = " << n  << '\n'
            << "<- x                = " << x  << '\n'
            << "-> legendre(n, xd)   = " << eve::legendre(n, xd) << '\n'
            << "-> legendre(3, xd)   = " << eve::legendre(3, xd) << '\n'
            << "-> legendre(n, 2.0)  = " << eve::legendre(n, 2.0) << '\n'
            << "-> legendre(n, x)    = " << eve::legendre(n, x)   << '\n';

//   std::cout << eve::legendre(0, 0.5) << " < -> " << boost::math::legendre(0, 0.5) << std::endl;
//   std::cout << eve::legendre(1, -1.5) << " < -> " << boost::math::legendre(1, -1.5) << std::endl;
//   std::cout << eve::legendre(2, 0.1   ) << " < -> " << boost::math::legendre(2, 0.1    ) << std::endl;
//   std::cout << eve::legendre(3, -1.0   ) << " < -> " << boost::math::legendre(3, -1.0    ) << std::endl;
//   std::cout << eve::legendre(4, 19.0   ) << " < -> " << boost::math::legendre(4,  19.0   ) << std::endl;
//   std::cout << eve::legendre(5, 25.0  ) << " < -> " << boost::math::legendre(5,   25.0   ) << std::endl;
//   std::cout << eve::legendre(6, 21.5   ) << " < -> " << boost::math::legendre(6,   21.5  ) << std::endl;
//   std::cout << eve::legendre(7, 10000.0   ) << " < -> " << boost::math::legendre(7, 10000.0    ) << std::endl;

//   std::cout << eve::legendre(0, wide_ft(0.5)) << " < -> " << boost::math::legendre(0, 0.5) << std::endl;
//   std::cout << eve::legendre(1, wide_ft(-1.5)) << " < -> " << boost::math::legendre(1, -1.5) << std::endl;
//   std::cout << eve::legendre(2, wide_ft(0.1)   ) << " < -> " << boost::math::legendre(2, 0.1    ) << std::endl;
//   std::cout << eve::legendre(3, wide_ft(-1.0)   ) << " < -> " << boost::math::legendre(3, -1.0    ) << std::endl;
//   std::cout << eve::legendre(4, wide_ft(19.0)   ) << " < -> " << boost::math::legendre(4,  19.0   ) << std::endl;
//   std::cout << eve::legendre(5, wide_ft(25.0)  ) << " < -> " << boost::math::legendre(5,   25.0   ) << std::endl;
//   std::cout << eve::legendre(6, wide_ft(21.5)   ) << " < -> " << boost::math::legendre(6,   21.5  ) << std::endl;
//   std::cout << eve::legendre(7, wide_ft(10000.0)   ) << " < -> " << boost::math::legendre(7, 10000.0    ) << std::endl;

  double xs = 3.0;

  std::cout << "---- scalar" << '\n'
            << "<- xs               = " << xs << '\n'
            << "-> legendre(4, xs)   = " << eve::legendre(4, xs) << '\n';

  return 0;
}
