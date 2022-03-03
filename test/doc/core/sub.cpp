#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::int16_t, eve::fixed<4>>;
  w_t pi = {3, 2, -32700, 32700}, qi = {4, 1, 100, -100};
  using wf_t = eve::wide<float, eve::fixed<4>>;
  wf_t pf = {3, 2.5, -32.7, 1327.43}, qf = {4.2, 1.5, -100.834, 10.02};

  std::cout << "---- simd" << '\n'
            << " <- pi          = " << pi << '\n'
            << " <- qi          = " << qi << '\n'
            << " -> sub(pi, qi) = " << eve::sub(pi, qi) << '\n'
            << " -> pi + qi     = " << pi + qi << '\n'
            <<  " -> saturated(sub)(pi, qi) = " << eve::saturated(eve::sub)(pi, qi) << '\n'
            << " -> pf + qf                 = " << pf + qf << '\n'
            <<  " -> diff(sub)(pf, qf)      = " << eve::diff(eve::sub)(pf, qf) << '\n'
            <<  " -> diff_2nd(sub)(pf, qf)  = " << eve::diff_2nd(eve::sub)(pf, qf) << '\n';

  std::int16_t xi = 100, yi = 32700;

  std::cout << "---- scalar" << '\n'
            << " <- xi          = " << xi << '\n'
            << " <- yi          = " << yi << '\n'
            << " -> sub(xi, yi) = " << eve::sub(xi, yi) << '\n'
            << " -> xi + yi     = " << xi + yi << '\n'; // C++ promotion to int

  std::cout << "---- multi parameters" << '\n'
            << " -> sub(pi, pi, pi, 1)                = " << eve::sub(pi, pi, pi, 1) << '\n'
            << " -> saturated(eve::sub)(pi,12, pi,pi) = " << eve::saturated(eve::sub)(pi, 12, pi,pi) << '\n';
  return 0;
}
