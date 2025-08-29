// revision 1
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <iostream>
#include <iomanip>
int main()
{
  constexpr auto N = 100;
//  auto sqte = 2.1f; eve::exp(eve::eps(eve::as<float>()));
  std::cout << std::setprecision(7);
//  std::array<float, 6 >  x{eve::exp(1.0f), sqte,sqte,sqte,sqte,sqte};
//  std::array<float, 6 >  x{1.f, 1/2.f, 1/3.f, 1/4.f, 1/5.f, 1/6.f};
    std::array<float, N > x;

    for(int i=0; i <N ; ++i)
    {
      x[i] = 0.51f;
    }
  {
    auto p = x[0];
    auto e1 = eve::zero(eve::as(x[0]));

    for(int i=1; i < N ; ++i)
    {
      auto [p1, e] = eve::two_prod(p, x[i]);
      e1 = (e*x[i]+e1);
      p = p1;
    }
    auto res =  p+e1;
    std::cout << "kahan res  " <<  res << " p " << p << " e "<< e1 << "\n";
  }

  {
    auto p = x[0];
    for(int i=1; i < N ; ++i)
    {
      p = eve::mul(p, x[i]);
    }
    auto res =  p;
    std::cout << "res        " <<  res << "\n";
  }

  {
    auto p = double(x[0]);
    for(int i=1; i < N ; ++i)
    {
      p = eve::mul(p, double(x[i]));
    }
    auto res =  p;
    std::cout << "double res " <<  float(res) << "\n";
  }
};
