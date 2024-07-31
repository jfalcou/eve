// revision 1
#include <eve/module/math.hpp>
#include <iostream>

template <class T>
struct const_fraction
{
   typedef T result_type;

   result_type operator()()
   {
     return T{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
   }
};

int main()
{
  eve::wide z{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0};
  auto ref = (-z+eve::sqrt(eve::sqr(z)+4))/2;
  std::cout << "ref constant fracs are: " << ref << std::endl;
  const_fraction<decltype(z)> func;
  auto gr = eve::lentz_a(func,eve::eps(eve::as<double>()), 100);
  std::cout << "    constant fracs are: " << gr << std::endl;
}
