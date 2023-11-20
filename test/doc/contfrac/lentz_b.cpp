#include <eve/module/contfrac.hpp>
#include <eve/module/math.hpp>
#include <eve/wide.hpp>
#include <iostream>


template <class T>
struct golden_ratio_fraction
{
  typedef T result_type;

  result_type operator()()
  {
    return T{1, 2, 3, 4};
  }
};

template <typename T>
struct tan_fraction
{
private:
  T a, b;
public:
  tan_fraction(T v)
    : a(-v * v), b(-1)
  {
    std::cout << "init a " << a << std::endl;
    std::cout << "init b " << b << std::endl;
  }

  using result_type = kumi::tuple<T, T>;
  result_type operator()()
  {
//     std::cout << " a " << a << std::endl;
//     std::cout << " b " << b << std::endl;
    b += T(2);
    return kumi::tuple{a, b};
  }
};

template <class T>
T tan(T a)
{
  tan_fraction<T> fract(a);
  return a/eve::lentz_b(fract, eve::eps(eve::as<eve::underlying_type_t<T>>()), 100);
}

int main()
{
  using w_t = eve::wide<double, eve::fixed<4>>;
  golden_ratio_fraction<w_t> func;
  auto gr = eve::lentz_b(func,eve::eps(eve::as<double>()), 100);
  std::cout << "The constant fracs are: " << gr << std::endl;
  w_t zz{1, 2, 3, 4};
  std::cout << "The constant fracs are: " << (zz+eve::sqrt(eve::sqr(zz)+4))/2 << std::endl;
  w_t z(eve::pio_4(eve::as<double>())); //w_t*/{eve::pio_4(eve::as<double>()), eve::pio_3(eve::as<double>()), 0.0, 1.0};
  std::cout << "     tan(" << z << ") is: " << tan(z) << std::endl;
  std::cout << "eve::tan(" << z << ") is: " << eve::tan(z) << std::endl;

  return 0;
}
