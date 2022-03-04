#include <eve/module/proba.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <random>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft x = { 0.0f, 1.0f, 3.0f, 5.0f };
  wide_ft n = { 2.0f, 3.0f, 6.0, 20.0f };
  wide_ft p = { 0.1f, 0.5f, 0.75, 0.9f };

  auto bi = eve::binomial_distribution(n,  p);

  std::cout
    << "---- simd" << '\n'
    << "<- x                   = " << x << '\n'
    << "<- n                   = " << n << '\n'
    << "<- p                   = " << p << '\n'
    << "-> median(bi)          = " << eve::median(bi) << '\n'
    << "-> mode(bi)            = " << eve::mode(bi) << '\n'
    << "-> mean(bi)            = " << eve::mean(bi) << '\n'
    << "-> var(bi)             = " << eve::var(bi) << '\n'
    << "-> entropy(bi)         = " << eve::entropy(bi) << '\n'
    << "-> pmf(bi, x)          = " << eve::pmf(bi, x) << '\n'
    << "-> cdf(bi, x)          = " << eve::cdf(bi, x)  << '\n'
    << "-> mgf(bi, x)          = " << eve::mgf(bi, x)  << '\n';

  float xf = 9.0f;
  float mf = 10.0f;
  float sf = 0.5;
  auto bif = eve::binomial_distribution(mf, sf);

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                  = " << xf << '\n'
    << "<- mf                  = " << mf << '\n'
    << "<- sf                  = " << sf << '\n'
    << "-> cdf(bif, xf)        = " << eve::cdf(bif, xf) << '\n'
    << "-> mode(bif)           = " << eve::mode(bif)    << '\n';



  auto d1 = eve::binomial_distribution(10.0f, eve::half);
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::cout
    << "generator \n"
    << "-> d1(gen, eve::as<wide_ft>()) "<< d1(gen, eve::as<wide_ft>()) << std::endl
    << "-> d1(gen)                     "<< d1(gen, eve::as<float>())    << std::endl;

  auto d2 = eve::binomial_distribution(30.0f, eve::half);
  std::cout
    << "generator \n"
    << "-> d2(gen, eve::as<wide_ft>()) "<< d2(gen, eve::as<wide_ft>()) << std::endl
    << "-> d2(gen)                     "<< d2(gen, eve::as<float>())    << std::endl;

  auto d3 = eve::binomial_distribution(30.0f, 0.3f);
  std::cout
    << "generator \n"
    << "-> d3(gen, eve::as<wide_ft>()) "<< d3(gen, eve::as<wide_ft>()) << std::endl
    << "-> d3(gen)                     "<< d3(gen, eve::as<float>())    << std::endl;

  auto d4 = eve::binomial_distribution(eve::one, 0.3f);
  std::cout
    << "generator \n"
    << "-> d4(gen, eve::as<wide_ft>()) "<< d4(gen, eve::as<wide_ft>()) << std::endl
    << "-> d4(gen)                     "<< d4(gen, eve::as<float>())    << std::endl;


  return 0;
}
