#include <eve/function/poisson_distribution.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <random>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft x = { 0.0f, 1.0f, 3.0f, 5.0f };
  wide_ft lambda = { 0.02f, 0.5f, 1.0f, 10.0f };



  auto po = eve::poisson_distribution(lambda);

  std::cout
    << "---- simd" << '\n'
    << "<- x                   = " << x << '\n'
    << "<- lambda              = " << lambda << '\n'
    << "-> median(po)          = " << eve::median(po) << "  \\\\  possibly approximate\n"
    << "-> mode(po)            = " << eve::mode(po) << '\n'
    << "-> mean(po)            = " << eve::mean(po) << '\n'
    << "-> var(po)             = " << eve::var(po) << '\n'
    << "-> pmf(po, x)          = " << eve::pmf(po, x) << '\n'
    << "-> cdf(po, x)          = " << eve::cdf(po, x)  << '\n'
    << "-> mgf(po, x)          = " << eve::mgf(po, x)  << '\n';

  float xf = 2.0f;
  float lf = 1.0f;
  auto pof = eve::poisson_distribution(lf);

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                  = " << xf << '\n'
    << "<- lf                  = " << lf << '\n'
    << "-> cdf(pof, xf)        = " << eve::cdf(pof, xf) << '\n'
    << "-> mean(pof)           = " << eve::mean(pof)    << '\n'
    << "-> var(pof)            = " << eve::var(pof)    << '\n';

  auto d1 = eve::poisson_distribution(15.0f);
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::cout
    << "generator \n"
    << "-> d1(gen, eve::as<wide_ft>()) "<< d1(gen, eve::as<wide_ft>()) << std::endl
    << "-> d1(gen)                     "<< d1(gen, eve::as<float>())    << std::endl;

  {
    auto d2 = eve::poisson_distribution_1<double>;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::cout
      << "generator \n"
      << "-> d2(gen, eve::as<wide_ft>()) "<< d2(gen, eve::as<wide_ft>()) << std::endl
      << "-> d2(gen)                     "<< d2(gen, eve::as<float>())    << std::endl;
  }


  return 0;
}
