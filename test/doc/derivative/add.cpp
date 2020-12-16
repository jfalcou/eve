#include <eve/function/derivative/add.hpp>
#include <eve/wide.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <iostream>

using wide_ft = eve::wide<float, eve::fixed<8>>;

int main()
{
  wide_ft pf = {2.0f, 3.0f, -4.0f, 2.0f, 2.0f,
                eve::inf(eve::as<float>()), eve::minf(eve::as<float>()), eve::nan(eve::as<float>())};
  wide_ft qf = {4.0f, 1.0f, -1.0f,  0.5f,  0.0f,
                -2.0f, -3.0f,  2.5f};

  std::cout << "---- simd" << '\n'
            << "<- pf          = " << pf << '\n'
            << "<- qf          = " << qf << '\n'
            << "-> add(pf, qf) = " << eve::add(pf, qf) << '\n'
            << "-> derivative_1st(add)(pf, qf) = " <<  eve::derivative_1st(eve::add)(pf, qf) << std::endl
            << "-> derivative_2nd(add)(pf, qf) = " <<  eve::derivative_2nd(eve::add)(pf, qf) << std::endl
            << "-> derivative(add)(pf, qf, 0u, 2u) = " <<  eve::derivative(eve::add)(pf, qf, 0u, 2u) << std::endl
            << "-> derivative(add)(pf, qf, 2u, 0u) = " <<  eve::derivative(eve::add)(pf, qf, 2u, 0u) << std::endl;

  float xf = 4.0f;
  float yf = -1.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf          = " << xf << '\n'
            << "<- yf          = " << yf << '\n'
            << "-> add(xf, yf) = " << eve::add(xf, yf) << '\n'
            << "-> derivative_1st(add)(xf, yf) = " <<  eve::derivative_1st(eve::add)(xf, yf) << std::endl
            << "-> derivative_2nd(add)(xf, yf) = " <<  eve::derivative_2nd(eve::add)(xf, yf) << std::endl;
  return 0;
}
