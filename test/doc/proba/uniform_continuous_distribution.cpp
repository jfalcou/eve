//#include <eve/function/uniform_continuous_distribution.hpp>
#include <eve/module/proba.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <random>


int main()
{
   using wide_dt = eve::wide <double, eve::fixed<4>>;
  wide_dt x = { 0.0f, 1.0f, 5.0f, 12.0f };
  wide_dt b = { 2, 3, 6, 20 };
  wide_dt a = { -2, 0, 3, 4};

  auto d = eve::uniform_continuous_distribution(a,  b);

  std::cout
    << "---- simd with wide double initialization continuous distribution" << '\n'
    << "<- x                  = " << x << '\n'
    << "<- a                  = " << d.a << '\n'
    << "<- b                  = " << d.b << '\n'
    << "-> median(d)          = " << eve::median(d) << '\n'
    << "-> mode(d)            = " << eve::mode(d) << '\n'
    << "-> mean(d)            = " << eve::mean(d) << '\n'
    << "-> var(d)             = " << eve::var(d) << '\n'
    << "-> entropy(d)         = " << eve::entropy(d) << '\n'
    << "-> pdf(d, x)          = " << eve::pdf(d, x) << '\n'
    << "-> cdf(d, x)          = " << eve::cdf(d, x)  << '\n'
    << "-> mgf(d, x)          = " << eve::mgf(d, x)  << '\n';

  auto d1 = eve::uniform_continuous_distribution(1.0, 5.0);
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::cout
    << "generator \n"
    << "-> d1(gen, eve::as<wide_dt>()) "<< d1(gen, eve::as<wide_dt>()) << std::endl
    << "-> d1(gen)                     "<< d1(gen, eve::as<double>())    << std::endl;

  auto d2 = eve::uniform_continuous_distribution_01<double>;
  std::cout
    << "generator \n"
    << "-> d2(gen, eve::as<wide_dt>()) "<< d2(gen, eve::as<wide_dt>()) << std::endl
    << "-> d2(gen)                     "<< d2(gen, eve::as<double>())    << std::endl;



  return 0;
}
