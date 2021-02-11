#include <eve/function/gamma_distribution.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <random>
#include <array>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft x = { 0.0f, 1.0f, -1.0f, 5.0f };
  wide_ft p = { 0.0f, 0.5f, 0.75f, 1.0f };
  wide_ft theta = { 0.5f, 2.0f, 0.3f, 4.0f };
  wide_ft k = { 1.0f,  2.0f, 3.0f, 0.5f };

  auto ga = eve::gamma_distribution(k, theta);

  std::cout
    << "---- simd" << '\n'
    << "<- x                   = " << x << '\n'
    << "<- theta               = " << theta << '\n'
    << "<- k                   = " << k << '\n'
    << "<- p                   = " << p << '\n'
    << "-> mode(ga)            = " << eve::mode(ga) << '\n'
    << "-> mean(ga)            = " << eve::mean(ga) << '\n'
    << "-> var(ga)             = " << eve::var(ga) << '\n'
    << "-> entropy(ga)         = " << eve::entropy(ga) << '\n'
    << "-> pdf(ga, x)          = " << eve::pdf(ga, x) << '\n'
    << "-> invcdf(ga, p)       = " << eve::invcdf(ga, p)  << '\n'
    << "-> cdf(ga, x)          = " << eve::cdf(ga, x)  << '\n';

  float xf = 9.0f;
  float thetaf = 10.0f;
  float kf = 2.0;
  auto gaf = eve::gamma_distribution(kf, thetaf);

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                  = " << xf << '\n'
    << "<- thetaf              = " << thetaf << '\n'
    << "<- kf                  = " << kf << '\n'
    << "-> cdf(gaf, xf)        = " << eve::cdf(gaf, xf) << '\n'
    << "-> mode(gaf)           = " << eve::mode(gaf)    << '\n';


  auto d1 = eve::gamma_distribution(2.0f, 5.0f);
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::cout
    << "generator \n"
    << "-> d1(gen, eve::as<wide_ft>()) "<< d1(gen, eve::as<wide_ft>()) << std::endl
    << "-> d1(gen)                     "<< d1(gen, eve::as<float>())    << std::endl;

  {
    auto d2 = eve::gamma_distribution_11<double>;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::cout
      << "generator \n"
      << "-> d2(gen, eve::as<wide_ft>()) "<< d2(gen, eve::as<wide_ft>()) << std::endl
      << "-> d2(gen)                     "<< d2(gen, eve::as<float>())    << std::endl;
  }

  {
    auto d3 = eve::gamma_distribution(2.0, 4.0);
    std::array<double, 4> cov = {0.5, 0.0, 0.0, 0.5};
    auto [r, plo, phi] = eve::confidence(d3
                                        , 0.2
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
