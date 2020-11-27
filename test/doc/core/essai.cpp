#include <eve/function/if_else.hpp>
#include <eve/function/is_less.hpp>
#include <eve/wide.hpp>
#include <eve/function/converter.hpp>
#include <iostream>
#include <boost/core/demangle.hpp>
// template <typename T> void find()
// {
//    auto func = eve::cosh;
//     using v_t = eve::element_type_t<T>;
//     auto vmax = eve::range_min<T>(func)*v_t(0.9);
//     auto vmin = eve::range_min<T>(func)*v_t(1.1);
//     if(eve::is_finite(func(vmax)) && !eve::is_finite(func(vmin)))
//     {
//       while(true)
//       {
//         auto v =  eve::average(vmin, vmax);
//         if (eve::is_finite(func(v))) vmax = v;  else vmin = v;
// //         std::cout << "vmin " << vmin <<  std::endl;
// //         std::cout << "vmax " << vmax <<  std::endl;
// //         std::cout << "vmax > vmin   " << (vmax > vmin) <<  std::endl;
//         if(vmin >=   eve::prev(vmax))
//         {
//           std::cout << std::hexfloat << eve::next(v) << " -> " << func(eve::next(v)) << " -> "
//                     << std::defaultfloat << std::setprecision(16) << eve::next(v) << std::endl;
//           std::cout << std::hexfloat << v << " -> " << func(v) << std::endl;
//           std::cout << std::hexfloat << eve::prev(v) << " -> " << func(eve::prev(v)) << " -> "
//                     << std::defaultfloat << std::setprecision(16) << eve::next(v) << std::endl;
//           break;
//         }
//       }
//     }
//     else
//       std::cout << "zut" << std::endl;
//   }
//   return 0;
// }

int main()
{
  using  t8_t = eve::wide<std::int8_t, eve::fixed<4>>;
  using t16_t = eve::wide<std::int32_t, eve::fixed<4>>;
  t8_t a8{1, 2, 3, 2 };
  t16_t a16{1, 3, 0, 4 };
//   auto z =  eve::is_less(a8, a16);
//   std::cout << z << std::endl;
//   const char *name = typeid(z).name();
//   std::cout << boost::core::demangle(name) << std::endl;
  auto z1 =  a8 % a16;
//  auto z1 = eve::int32(a8) < a16;
  std::cout << typeid(z1).name() << std::endl;
  std::cout << sizeof(a8) << std::endl;
  std::cout << sizeof(a16)<< std::endl;
  std::cout << z1 << std::endl;
  auto z2 =  a8 < a8;
  std::cout << z2 << std::endl;  return 0;
}
