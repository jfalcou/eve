#include <eve/module/core.hpp>
#include <eve/wide.hpp>
#include <vector>
#include <iostream>

float mean(std::vector<float>  ary) {
  float avg = 0;
  int t = 1;
  for (float x : ary) {
    avg += (x - avg) / t;
    ++t;
  }
  return avg;
}

int main()
{
  using w_t = eve::wide<std::uint32_t, eve::fixed<4>>;
  w_t pi = {3, 2, 3, 3}, qi = {4, 1, 1, ~0};

  std::cout << "---- simd" << '\n'
            << " <- pi              = " << pi << '\n'
            << " <- qi              = " << qi << '\n'
            << " -> average(pi, qi) = " << eve::average(pi, qi) << '\n';

  std::uint32_t xi = 3, yi = 4;

  std::cout << "---- scalar" << '\n'
            << " xi                 = " << xi << '\n'
            << " yi                 = " << yi << '\n'
            << " -> average(xi, yi) = " << eve::average(xi, yi) << '\n';

  using w_ft = eve::wide<float, eve::fixed<4>>;
  w_ft pf = {3, 4, 3, 10}, qf = {4, 1, 1, 15};;
  std::cout << "---- multi" << '\n'
            << " <- pf                               = " << pf << '\n'
            << " <- qf                               = " << qf << '\n'
            << " -> average(pf, 0.0f, qf, pf, 11.0f) = " << eve::average(pf, 0.0f, qf, pf, 11.0f) <<  '\n'
            << " -> diff_1st(average)(pf, qf)        = " << eve::diff_1st(eve::average)(pf, qf) << std::endl
            << " -> diff_2nd(average)(pf, qf)        = " << eve::diff_2nd(eve::average)(pf, qf) << std::endl;

  std::cout << "---- multi parameters" << '\n'
            << " -> diff(average)(pf,12.0f,pf,2*pf)         = " << eve::diff(eve::average)(pf,12.0f, pf, 2*pf)<< '\n'
            << " -> diff_2nd(average)(pf,12.0f,pf,2*pf)     = " << eve::diff_2nd(eve::average)(pf,12.0f, pf, 2*pf)<< '\n'
            << " -> diff_nth<5>(average)(pf,12.0f,pf,2*pf)  = " << eve::diff_nth<5>(eve::average)(pf,12.0f, pf, 2*pf)<< '\n';
  return 0;
}
