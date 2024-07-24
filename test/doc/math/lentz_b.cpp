// revision 1
#include <eve/module/math.hpp>
#include <iostream>

template <class T>
struct const_fraction
{
  auto operator()(){ return T{1.0, 2.0, 3.0, 4.0}; }
};

template <typename T>
struct tan_fraction
{
  T a, b;
  tan_fraction(T v) : a(-v * v), b(-1) {}
  auto operator()()
  {
    b += T(2);
    return kumi::tuple{a, b};
  }
};

template <class T>
T mytan(T a)
{
  tan_fraction<T> fract(a);
  return a/eve::lentz_b(fract, eve::eps(eve::as<eve::underlying_type_t<T>>()), 100);
}

int main()
{
  using w_t = eve::wide<double, eve::fixed<4>>;
  const_fraction<w_t> func;
  eve::wide zz{1.0, 2.0, 3.0, 4.0};
  std::cout << "ref constant fracs " << (zz+eve::sqrt(eve::sqr(zz)+4))/2 << std::endl;
  auto gr = eve::lentz_b(func,eve::eps(eve::as<double>()), 100);
  std::cout << "    constant fracs " << gr << std::endl;
  w_t z{eve::pio_4(eve::as<double>()), eve::pio_3(eve::as<double>()), 0.0, 1.0};
  std::cout << "frac tan(" << z << ") is: " << mytan(z) << std::endl;
  std::cout << "ref  tan(" << z << ") is: " << eve::tan(z) << std::endl;
}
