#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using w_t = eve::wide<std::int16_t, eve::fixed<4>>;
  w_t pi = {3, 2, -32700, 32700}, qi = {4, 1, -100, 100};
  using wf_t = eve::wide<float, eve::fixed<4>>;
  wf_t pf = {3, 2.5, -32.7, 1327.43}, qf = {4.2, 1.5, -100.834, 10.02};

  std::cout << "---- simd" << '\n'
            << " <- pi          = " << pi << '\n'
            << " <- qi          = " << qi << '\n'
            << " -> add(pi, qi) = " << eve::add(pi, qi) << '\n'
            << " -> pi + qi                 = " << pi + qi << '\n'
            <<  " -> saturated(add)(pi, qi) = " << eve::saturated(eve::add)(pi, qi) << '\n'
            << " -> pf + qf                 = " << pf + qf << '\n'
            <<  " -> diff(add)(pf, qf)      = " << eve::diff(eve::add)(pf, qf) << '\n'
            <<  " -> diff_2nd(add)(pf, qf)  = " << eve::diff_2nd(eve::add)(pf, qf) << '\n';

  std::int16_t xi = 100, yi = 32700;

  std::cout << "---- scalar" << '\n'
            << " <- xi          = " << xi << '\n'
            << " <- yi          = " << yi << '\n'
            << " -> add(xi, yi) = " << eve::add(xi, yi) << '\n'
            << " -> xi + yi     = " << xi + yi << '\n'; // C++ promotion to int

  std::cout << "---- multi parameters" << '\n'
            << " -> add(pi,pi,pi,1)                     = " << eve::add(pi, pi, pi, 1) << '\n'
            << " -> saturated(add)(pi,12,pi,pi)         = " << eve::saturated(eve::add)(pi, 12, pi,pi) << '\n'
            << " -> diff(add)(pf,12.0f,pf,2*pf)         = " << eve::diff(eve::add)(pf,12.0f, pf, 2*pf)<< '\n'
            << " -> diff_2nd(add)(pf,12.0f,pf,2*pf)     = " << eve::diff_2nd(eve::add)(pf,12.0f, pf, 2*pf)<< '\n'
            << " -> diff_nth<5>(add)(pf,12.0f,pf,2*pf)  = " << eve::diff_nth<5>(eve::add)(pf,12.0f, pf, 2*pf)<< '\n';
  return 0;
}
