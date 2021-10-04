//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pi.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/diff/cos.hpp>
#include <cmath>
#include <eve/module/real/math/detail/constant/rempio2_limits.hpp>
#include <eve/function/ulpdist.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
// EVE_TEST_TYPES( "Check return types of cos"
//             , eve::test::simd::ieee_reals
//             )
// <typename T>(eve::as<T>)
// {
//   using v_t = eve::element_type_t<T>;

//   TTS_EXPR_IS( eve::cos(T())  , T);
//   TTS_EXPR_IS( eve::cos(v_t()), v_t);
// };

//==================================================================================================
// cos  tests
//==================================================================================================
auto mrest  = []<typename T>(eve::as<T> const & tgt){  return -eve::pio_4(tgt); };
auto rest   = []<typename T>(eve::as<T> const & tgt){  return  eve::pio_4(tgt); };
auto msmall = []<typename T>(eve::as<T> const & tgt){  return -eve::pio_2(tgt); };
auto small  = []<typename T>(eve::as<T> const & tgt){  return  eve::pio_2(tgt); };
auto mcircle= []<typename T>(eve::as<T> const & tgt){  return -eve::pi(tgt);    };
auto circle = []<typename T>(eve::as<T> const & tgt){  return  eve::pi(tgt);    };
auto mmed   = []<typename T>(eve::as<T> const & tgt){  return -eve::detail::Rempio2_limit(eve::medium_type(), tgt); };
auto med    = []<typename T>(eve::as<T> const & tgt){  return  eve::detail::Rempio2_limit(eve::medium_type(), tgt); };

EVE_TEST( "Check behavior of cos on wide"
        , eve::test::simd::ieee_floats//reals
        , eve::test::generate( eve::test::randoms(mrest, rest)
                             , eve::test::randoms(msmall, small)
                             , eve::test::randoms(mcircle, circle)
                             , eve::test::randoms(mmed, med)
                             , eve::test::randoms(eve::valmin, eve::valmax))
                             )
<typename T>(T const& a0, T const& a1 , T const& a2, T const& a3, T const& a4)
{
  using eve::detail::map;
  using eve::cos;
  using eve::diff;
  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { return std::cos(e); };
  TTS_ULP_EQUAL(eve::restricted(cos)(a0)      , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::small(cos)(a0)           , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::small(cos)(a1)           , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::circle(cos)(a0)          , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::circle(cos)(a1)          , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::circle(cos)(a2)          , map(ref, a2), 2);
  TTS_ULP_EQUAL(eve::medium(cos)(a0)          , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::medium(cos)(a1)          , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::medium(cos)(a2)          , map(ref, a2), 2);
  TTS_ULP_EQUAL(eve::medium(cos)(a3)          , map(ref, a3), 2);
  TTS_ULP_EQUAL(eve::big(cos)(a0)             , map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::big(cos)(a1)             , map(ref, a1), 2);
  TTS_ULP_EQUAL(eve::big(cos)(a2)             , map(ref, a2), 2);
  TTS_ULP_EQUAL(eve::big(cos)(a3)             , map(ref, a3), 2);
  TTS_ULP_EQUAL(eve::big(cos)(a4)             , map(ref, a4), 2);
  TTS_ULP_EQUAL(cos(a0)                       , map(ref, a0), 2);
  TTS_ULP_EQUAL(cos(a1)                       , map(ref, a1), 2);
  TTS_ULP_EQUAL(cos(a2)                       , map(ref, a2), 2);
  TTS_ULP_EQUAL(cos(a3)                       , map(ref, a3), 2);
  TTS_ULP_EQUAL(cos(a4)                       , map(ref, a4), 2);
  TTS_ULP_EQUAL(diff(cos)(a0), map([](auto e) -> v_t { return  -std::sin(e); }, a0), 2);


//   TTS_ULP_EQUAL(diff(cos)(a0), map([](auto e) -> v_t { return  -std::sin(e); }, a0), 2);
//  std::cout << std::hexfloat << 1.0/180 << std::endl;
//   __float128 a = 1.0Q/180;
//   std::cout << std::hexfloat << double(a) << std::endl;
//   std::cout << std::hexfloat << double(a-double(a))<< std::endl;

//   double z = 0x1.6c16c16c16c16p-8;
//   std::cout << std::hexfloat << double(a-z)<< std::endl;

//   double a = 1.0/180;
//   std::cout << std::hexfloat << a << std::endl;
//   auto af = float(a);
//   auto a2f = float(a-af);
//   std::cout << std::hexfloat << af<< std::endl;
//   std::cout << std::hexfloat << a2f<< std::endl;
//   double z = double(af)+double(a2f);
// //   double z = 0x1.6c16c16c16c16p-8;
//    std::cout << std::hexfloat << z<< std::endl;

};
