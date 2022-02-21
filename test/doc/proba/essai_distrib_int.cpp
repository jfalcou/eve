#include <eve/module/proba.hpp>
#include <generator.hpp>
#include <eve/wide.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <iostream>
#include <vector>
#include <random>

int main()
{
  using i_t = std::int64_t;
  using eve::as;
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  eve::tests_integral_distribution<i_t> d(eve::valmin(as<i_t>()), -1); //eve::valmax(as<i_t>()));
  std::vector<i_t> v;
  i_t minipos = eve::valmax(as<i_t > ());
  i_t maxipos = 0;
  i_t maxineg = eve::valmin(as<i_t > ());
  i_t minineg = 0;
  for(std::size_t i = 0; i < 10000; ++i)
  {
    auto val = d(gen);
    if (val > 0)
    {
      if (val > maxipos) maxipos = val;
      if (val < minipos) minipos = val;
    }
    else
    {
      if (val > maxineg) maxineg = val;
      if (val < minineg) minineg = val;
    }
    v.push_back(val);
  }
  std::cout << "minipos " << +minipos << std::endl;
  std::cout << "maxipos " << +maxipos << std::endl;
  std::cout << "minineg " << +minineg << std::endl;
  std::cout << "maxineg " << +maxineg << std::endl;
}
