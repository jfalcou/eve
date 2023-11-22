#include <eve/module/contfrac.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <list>
#include <vector>

using w_t = eve::wide<double, eve::fixed<8>>;

template <class T>
struct const_fraction
{
   typedef T result_type;

   result_type operator()()
   {
     return T{1, 2, 3, 4, 5, 6, 7, 8};
   }
};


int main()
{
  const_fraction<w_t> func;
  auto gr = eve::lentz_a(func,eve::eps(eve::as<double>()), 100);
  std::cout << "The golden ratio is: " << gr << std::endl;
  w_t z{1, 2, 3, 4, 5, 6, 7, 8};
  auto ref = (-z+eve::sqrt(eve::sqr(z)+4))/2;
  std::cout << "ref golden ratio is: " << ref << std::endl;

  return 0;
}
