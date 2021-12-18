//#include <eve/function/cauchy_distribution.hpp>
#include <eve/module/proba.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <random>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft x = { 0.0f, 1.0f, -1.0f, 5.0f };
  wide_ft p = { 0.0f, 0.5f, 0.75f, 1.0f };
  wide_ft m = { 0.0f, -1.0f, 1.0f, 2.0f };
  wide_ft s = { 1.0f,  2.0f, 3.0f, 4.0f };

  auto ca = eve::cauchy_distribution(0.0f, s);

  std::cout
    << "---- simd" << '\n'
    << "<- x                   = " << x << '\n'
    << "<- m                   = " << m << '\n'
    << "<- s                   = " << s << '\n'
    << "<- p                   = " << p << '\n'
    << "-> median(ca)          = " << eve::median(ca) << '\n'
    << "-> mode(ca)            = " << eve::mode(ca) << '\n'
    << "-> fisher(ca)          = " << eve::fisher(ca) << '\n'
    << "-> pdf(ca, x)          = " << eve::pdf(ca, x) << '\n'
    << "-> invcdf(ca, p)       = " << eve::invcdf(ca, p)  << '\n'
    << "-> cdf(ca, x)          = " << eve::cdf(ca, x)  << '\n';

  float xf = 9.0f;
  float mf = 10.0f;
  float sf = 2.0;
  auto caf = eve::cauchy_distribution(mf, sf);

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                  = " << xf << '\n'
    << "<- mf                  = " << mf << '\n'
    << "<- sf                  = " << sf << '\n'
    << "-> cdf(caf, xf)        = " << eve::cdf(caf, xf) << '\n'
    << "-> mode(caf)           = " << eve::mode(caf)    << '\n';

  auto ca0= eve::cauchy_distribution{eve::zero, s};

  std::cout
    << "---- simd" << '\n'
    << "<- x                   = " << x << '\n'
    << "<- m                   = " << m << '\n'
    << "<- s                   = " << s << '\n'
    << "<- p                   = " << p << '\n'
    << "-> median(ca0)          = " << eve::median(ca0) << '\n'
    << "-> mode(ca0)            = " << eve::mode(ca0) << '\n'
    << "-> fisher(ca0)          = " << eve::fisher(ca0) << '\n'
    << "-> pdf(ca0, x)          = " << eve::pdf(ca0, x) << '\n'
    << "-> invcdf(ca0, p)       = " << eve::invcdf(ca0, p)  << '\n'
    << "-> cdf(ca0, x)          = " << eve::cdf(ca0, x)  << '\n';


  auto d1 = eve::cauchy_distribution(1.0f, 5.0f);
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::cout
    << "generator \n"
    << "-> d1(gen, eve::as<wide_ft>()) "<< d1(gen, eve::as<wide_ft>()) << std::endl
    << "-> d1(gen)                     "<< d1(gen, eve::as<float>())    << std::endl;

  return 0;
}
