// revision 1
#include <eve/module/math.hpp>
#include <iostream>

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
  w_t z{1, 2, 3, 4, 5, 6, 7, 8};
  auto ref = (-z+eve::sqrt(eve::sqr(z)+4))/2;
  std::cout << "ref constant fracs are: " << ref << std::endl;
  const_fraction<w_t> func;
  auto gr = eve::lentz_a(func,eve::eps(eve::as<double>()), 100);
  std::cout << "    constant fracs are: " << gr << std::endl;

  return 0;
}
