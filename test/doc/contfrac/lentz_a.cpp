#include <eve/module/contfrac.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <list>
#include <vector>

using w_t = eve::wide<double, eve::fixed<8>>;

template <class T>
struct golden_ratio_fraction
{
   typedef T result_type;

   result_type operator()()
   {
     return T{1, 2, 3, 4, 5, 6, 7, 8};
   }
};


int main()
{
  golden_ratio_fraction<w_t> func;
  auto gr = eve::lentz_a(func,eve::eps(eve::as<double>()), 100);
  std::cout << "The golden ratio is: " << gr << std::endl;

  return 0;
}
