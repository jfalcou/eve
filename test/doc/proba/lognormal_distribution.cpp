#include <eve/module/proba.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <random>
#include <array>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft x = { 0.0f, 1.0f, -1.0f, 5.0f };
  wide_ft p = { 0.0f, 0.5f, 0.75f, 1.0f };
  wide_ft m = { 0.0f, -1.0f, 1.0f, 2.0f };
  wide_ft s = { 1.0f,  2.0f, 3.0f, 4.0f };

  auto d = eve::lognormal_distribution(m, s);

  std::cout
    << "---- simd" << '\n'
    << "<- x                  = " << x << '\n'
    << "<- m                  = " << m << '\n'
    << "<- s                  = " << s << '\n'
    << "<- p                  = " << p << '\n'
    << "-> median(d)          = " << eve::median(d) << '\n'
    << "-> mode(d)            = " << eve::mode(d) << '\n'
    << "-> mean(d)            = " << eve::mean(d) << '\n'
    << "-> var(d)             = " << eve::var(d) << '\n'
    << "-> entropy(d)         = " << eve::entropy(d) << '\n'
    << "-> pdf(d, x)          = " << eve::pdf(d, x) << '\n'
    << "-> invcdf(d, p)       = " << eve::invcdf(d, p)  << '\n'
    << "-> cdf(d, x)          = " << eve::cdf(d, x)  << '\n';

  float xf = 9.0f;
  float mf = 10.0f;
  float sf = 2.0;
  auto df = eve::lognormal_distribution(mf, sf);

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                 = " << xf << '\n'
    << "<- mf                 = " << mf << '\n'
    << "<- sf                 = " << sf << '\n'
    << "-> cdf(df, xf)        = " << eve::cdf(df, xf) << '\n'
    << "-> mode(df)           = " << eve::mode(df)    << '\n';


  auto d1 = eve::lognormal_distribution(1.0f, 5.0f);
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::cout
    << "generator \n"
    << "-> d1(gen, eve::as<wide_ft>()) "<< d1(gen, eve::as<wide_ft>()) << std::endl
    << "-> d1(gen)                     "<< d1(gen, eve::as<float>())    << std::endl;

  {
    auto d2 = eve::lognormal_distribution_01<double>;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::cout
      << "generator \n"
      << "-> d2(gen, eve::as<wide_ft>()) "<< d2(gen, eve::as<wide_ft>()) << std::endl
      << "-> d2(gen)                     "<< d2(gen, eve::as<float>())    << std::endl;
  }

  {
    auto d3 = eve::lognormal_distribution(0.0, 1.0);
    std::array<double, 4> cov = {1.0, 0.0, 0.0, 1.0};
    auto [r, plo, phi] = eve::confidence(d3
                                        , 5.0
                                        , cov
                                        , 0.05);
    std::cout
      << "confidence \n"
      << "r          " << r << std::endl
      << "plo        " << plo<< std::endl
      << "phi        " << phi<< std::endl;
  }

  return 0;
}
