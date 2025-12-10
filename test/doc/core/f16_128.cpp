// revision 0
#include <eve/module/core.hpp>
#include <iostream>

// namespace eve::detail
// {
//   template<callable_options O, floating_scalar_value U>
//   EVE_FORCEINLINE auto convert_(EVE_REQUIRES(cpu_), O const& opts, long double const& v0, eve::as<U>)
//   {
//     if constexpr(std::same_as<U, long double>) return v0;
//     else return static_cast<U>(v0);
//   }
// }

int main()
{
  long double ld(1.23456789101112l);
  std::cout << "size(ld)                        " << sizeof(ld) << std::endl;
  std::cout << "ld                              " << ld << std::endl;
  std::cout << "convert(ld, eve;::as<double>()) " << eve::convert(ld, eve::as<double>()) << std::endl;
  std::cout << "convert(ld, eve;::as<float> ()) " << eve::convert(ld, eve::as<float> ()) << std::endl;
  using f16_t = eve::float16_t;
  std::cout << "convert(ld, eve;::as<f16_t> ()) " << float(eve::convert(ld, eve::as<f16_t> ())) << std::endl;

  f16_t f16(static_cast<f16_t>(1.23456789101112));
  std::cout << "convert(f16, eve;::as<float>()) " << eve::convert(f16, eve::as<float>()) << std::endl;
  std::cout << "convert(f16, eve;::as<double> ()) " << eve::convert(f16, eve::as<double> ()) << std::endl;
//  std::cout << "convert(f16, eve;::as<long double> ()) " << eve::convert(f16, eve::as<long double> ()) << std::endl;

}
