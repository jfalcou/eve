// revision 0
#include <eve/module/core.hpp>
#include <iostream>
#include <iomanip>

int main()
{
  using v_t = eve::float16_t;
  using i_t = eve::as_integer_t<v_t, signed>;
  v_t a = -1.0f;
  i_t bi = eve::detail::bitinteger(a);
  std::cout << "bi " << std::hex << bi << std::endl;
  v_t aa =  eve::detail::bitfloating(bi);
  std::cout << "aa " << float(aa)  << std::endl;

  using f_t = eve::as_floating_point_t<i_t>;
  std::cout << (std::same_as < v_t, f_t>) << std::endl;
//  std::cout << "a " << a << std::endl;
//   u_t i = eve::bit_cast(a, eve::as<u_t>());
//   std::cout << "i " << std::hex << i << std::endl;
//   auto r = eve::is_gez(a) ? u_t(a) : u_t(0);
//   auto cst = eve::bit_cast(i,  eve::as<v_t>());
//   std::cout << "cst " << float(cst)  << std::endl;

 for(short int i=0x2710; i < 0x2710+5; ++i)
 {
   auto aaa = eve::detail::bitfloating(i);
   std::cout <<"aaa             " << std::hexfloat << float(aaa) << std::endl;
   std::cout <<"bitinteger(aaa) " << std::hex      << eve::detail::bitinteger(aaa) << std::endl;
   std::cout <<"next(aaa)       " << std::hexfloat<< float(eve::next(aaa)) << std::endl;
   std::cout <<"prev(aaa)       " << std::hexfloat<< float(eve::prev(aaa)) << std::endl;
   std::cout << "expo           " << std::dec << eve::exponent(aaa) << std::endl;
   std::cout << "mant           " << float(eve::mantissa(aaa)) << std::endl;
   std::cout << "sign           " << float(eve::sign(aaa)) << std::endl;
   auto expo = eve::exponent(aaa);
   auto mant = eve::mantissa(aaa);

   std::cout << "ldexp(mant, expo) " << float(eve::ldexp(mant, expo)) << std::endl;
 }
}
