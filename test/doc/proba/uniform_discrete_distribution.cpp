//#include <eve/function/uniform_discrete_distribution.hpp>
#include <eve/module/proba.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <random>


int main()
{
  using wide_dt = eve::wide <float, eve::fixed<4>>;
  using wide_it = eve::wide <std::int32_t, eve::fixed<4>>;
  wide_dt x = { 0.0f, 1.0f, 5.0f, 12.0f };
  wide_it b = { 2, 3, 6, 20 };
  wide_it a = { -2, 0, 3, 4};

  auto d = eve::uniform_discrete_distribution(a,  b, eve::as<float>());

  std::cout
    << "---- simd initialization" << '\n'
    << "<- x                  = " << x << '\n'
    << "<- a                  = " << d.a << '\n'
    << "<- b                  = " << d.b << '\n'
    << "<- n                  = " << d.n << '\n'
    << "-> median(d)          = " << eve::median(d) << '\n'
    << "-> mode(d)            = " << eve::mode(d) << '\n'
    << "-> mean(d)            = " << eve::mean(d) << '\n'
    << "-> var(d)             = " << eve::var(d) << '\n'
    << "-> entropy(d)         = " << eve::entropy(d) << '\n'
    << "-> cdf(d, x)          = " << eve::cdf(d, x) << '\n'
    << "-> pmf(d, x)          = " << eve::pmf(d, x) << '\n'
    << "-> mgf(d, x)          = " << eve::mgf(d, x)  << '\n'
    ;

  auto d0 = eve::uniform_discrete_distribution_01<double>;

  std::cout
    << "---- 01 version" << '\n'
    << "<- x                  = " << x << '\n'
    << "-> median(d0)          = " << eve::median(d0) << '\n'
    << "-> mode(d0)            = " << eve::mode(d0) << '\n'
    << "-> mean(d0)            = " << eve::mean(d0) << '\n'
    << "-> var(d0)             = " << eve::var(d0) << '\n'
    << "-> entropy(d0)         = " << eve::entropy(d0) << '\n'
    << "-> cdf(d0, x)          = " << eve::cdf(d0, x) << '\n'
    << "-> pmf(d0, x)          = " << eve::pmf(d0, x) << '\n'
    << "-> mgf(d0, x)          = " << eve::mgf(d0, x)  << '\n'
    ;


  auto d1 = eve::uniform_discrete_distribution(1.0, 5.0);
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::cout
    << "generator \n"
    << "-> d1(gen, eve::as<wide_dt>()) "<< d1(gen, eve::as<wide_dt>()) << std::endl
    << "-> d1(gen)                     "<< d1(gen, eve::as<double>())    << std::endl;

  auto d2 = eve::uniform_discrete_distribution_01<double>;
  std::cout
    << "generator \n"
    << "-> d2(gen, eve::as<wide_dt>()) "<< d2(gen, eve::as<wide_dt>()) << std::endl
    << "-> d2(gen)                     "<< d2(gen, eve::as<double>())    << std::endl;

  return 0;
}
