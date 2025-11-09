// revision 0
#include <eve/module/core.hpp>
#include <iostream>

template <typename T> struct  wrap16_t
{
  wrap16_t(auto _a) : a(_a){};
  float a; //eve::float16_t<T> a;
};

template <typename T> std::ostream& operator <<(std::ostream & os, wrap16_t<T> const & f)
{
  auto m = eve::mantissa(f.a);
  auto e = eve::exponent(f.a);
  auto pos = eve::is_positive(m);
  auto im = eve::detail::bitinteger(eve::abs(m));
  os <<  (pos ? '+' : '-') << "0x" << std::hex << im << "p" << std::dec << e << 'h';
  return os; 
}

int main()
{
  using T = eve::float16_t;
  using I = eve::as_integer_t<T, signed>;
  T a(eve::mindenormal(eve::as(a)));
  auto nmb = eve::nbmantissabits(eve::as<T>());
  auto tnmb = I(1) << nmb;
  std::cout << "nmb    " << nmb << std::endl;
  std::cout << "tnmb   " << tnmb <<std::endl;
  auto ttnmb =  eve::twotonmb(eve::as<T>());
  std::cout << "ttnmb   " << float(ttnmb) <<std::endl;
  std::cout << std::hex << eve::detail::bitinteger(T(1024.0f))<<std::endl;
  std::cout << std::hex << eve::detail::bitinteger(T(1.0e-6f))<<std::endl;

  std::cout <<  wrap16_t<T>(a) << std::endl;

}
