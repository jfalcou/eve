#include <eve/function/normal_distribution.hpp>
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

  auto no = eve::normal_distribution(m, s);

  std::cout
    << "---- simd" << '\n'
    << "<- x                   = " << x << '\n'
    << "<- m                   = " << m << '\n'
    << "<- s                   = " << s << '\n'
    << "<- p                   = " << p << '\n'
    << "-> median(no)          = " << eve::median(no) << '\n'
    << "-> mode(no)            = " << eve::mode(no) << '\n'
    << "-> mean(no)            = " << eve::mean(no) << '\n'
    << "-> var(no)             = " << eve::var(no) << '\n'
    << "-> entropy(no)          = " << eve::entropy(no) << '\n'
    << "-> pdf(no, x)          = " << eve::pdf(no, x) << '\n'
    << "-> invcdf(no, p)       = " << eve::invcdf(no, p)  << '\n'
    << "-> cdf(no, x)          = " << eve::cdf(no, x)  << '\n';

  float xf = 9.0f;
  float mf = 10.0f;
  float sf = 2.0;
  auto nof = eve::normal_distribution(mf, sf);

  std::cout
    << "---- scalar"  << '\n'
    << "<- xf                  = " << xf << '\n'
    << "<- mf                  = " << mf << '\n'
    << "<- sf                  = " << sf << '\n'
    << "-> cdf(nof, xf)        = " << eve::cdf(nof, xf) << '\n'
    << "-> mode(nof)           = " << eve::mode(nof)    << '\n';


  auto d1 = eve::normal_distribution(1.0f, 5.0f);
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::cout
    << "generator \n"
    << "-> d1(gen, eve::as<wide_ft>()) "<< d1(gen, eve::as<wide_ft>()) << std::endl
    << "-> d1(gen)                     "<< d1(gen, eve::as<float>())    << std::endl;

  {
    auto d2 = eve::normal_distribution_01<double>;
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::cout
      << "generator \n"
      << "-> d2(gen, eve::as<wide_ft>()) "<< d2(gen, eve::as<wide_ft>()) << std::endl
      << "-> d2(gen)                     "<< d2(gen, eve::as<float>())    << std::endl;
  }

  {
    auto d3 = eve::normal_distribution(1.0, 1.0);
    std::array<double, 4> cov = {1.0, 0.0, 0.0, 1.0};
    auto [r, plo, phi] = eve::confidence(d3
                                        , 0.0
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
