//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

EVE_TEST_TYPES("Check basic constants behavior"
              , eve::test::simd::ieee_reals
              )
  <typename T>(eve::as<T>)
{
  using eve::as;
  using elt_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::allbits(as<T>()), eve::bit_not(T(0)));
  TTS_EQUAL(eve::true_(as<T>()), eve::as_logical_t<T>(1));
  TTS_EQUAL(eve::false_(as<T>()), eve::as_logical_t<T>(0));
  TTS_EQUAL(eve::one(as<T>()), T(1));
  TTS_EQUAL(eve::mone(as<T>()), T(-1));
  TTS_EQUAL(eve::zero(as<T>()), T(0));

  if constexpr(eve::floating_value < T>)
  {
    TTS_IEEE_EQUAL(eve::allbits(as<T>()), T(0.0/0.0));
    TTS_EQUAL(eve::mzero(as<T>()), T(-0));
    TTS_EQUAL(eve::half(as<T>()), T(0.5));
    TTS_EQUAL(eve::mhalf(as<T>()), T(-0.5));
    TTS_EXPECT(eve::all(eve::is_negative(eve::mzero(as<T>()))));
  }
  else if  constexpr(eve::integral_value < T>)
  {
    TTS_EQUAL(eve::allbits(as<T>()), T(elt_t(~0)));
  }
};

EVE_TEST_TYPES( "Check ieee754 constants"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using eve::as;
  using elt_t = eve::element_type_t<T>;
  using ilt_t = eve::as_integer_t<elt_t>;
  using  i_t  = eve::as_integer_t<T,   signed>;
  TTS_EQUAL(eve::bitincrement(as<T>()), T(eve::bit_cast(eve::one(as<ilt_t>()), as<elt_t>())));
  TTS_IEEE_EQUAL(eve::nan(as<T>()),  T(0.0/0.0));
  TTS_EQUAL(eve::signmask(as<T>()), T(eve::bit_cast(eve::one(as<ilt_t>()) << (sizeof(ilt_t)*8-1) , as<elt_t>())));
  TTS_EQUAL(eve::mindenormal(as<T>()), eve::bitincrement(as<T>()));
  TTS_ULP_EQUAL(eve::sqrteps(as<T>()), eve::sqrt(eve::eps(as<T>())),0.5);

  if constexpr(std::is_same_v<elt_t, float>)
  {
    TTS_EQUAL(eve::eps(as<T>()), eve::exp2(T(-23.0f)));
    TTS_EQUAL(eve::exponentmask(as<T>()), i_t(0x7f800000U));
    TTS_EQUAL(eve::maxexponentp1(as<T>()), i_t(128));
    TTS_EQUAL(eve::logeps(as<T>()), T(-15.942384719848632812f));
    TTS_EQUAL(eve::mantissamask(as<T>()), i_t(0x807FFFFFU));
    TTS_EQUAL(eve::oneosqrteps(as<T>()), T(2896.309326171875f));
    TTS_EQUAL(eve::maxexponent(as<T>()), i_t(127));
    TTS_EQUAL(eve::maxexponentm1(as<T>()), i_t(126));
    TTS_EQUAL(eve::nbmantissabits(as<T>()), i_t(23));
    TTS_EQUAL(eve::twotonmb(as<T>()), eve::exp2(T(23.0f)));
  }
  else if constexpr(std::is_same_v<elt_t, double>)
  {
    TTS_EQUAL(eve::eps(as<T>()), eve::exp2(T(-52.0)));
    TTS_EQUAL(eve::exponentmask(as<T>()), i_t(0x7ff0000000000000ULL));
    TTS_EQUAL(eve::maxexponentp1(as<T>()), i_t(1024));
    TTS_EQUAL(eve::logeps(as<T>()), T(-36.043653389117153552));
    TTS_EQUAL(eve::mantissamask(as<T>()), i_t(0x800FFFFFFFFFFFFFULL));
    TTS_EQUAL(eve::oneosqrteps(as<T>()), T(67108864.0));
    TTS_EQUAL(eve::maxexponent(as<T>()), i_t(1023));
    TTS_EQUAL(eve::maxexponentm1(as<T>()), i_t(1022));
    TTS_EQUAL(eve::nbmantissabits(as<T>()), i_t(52));
    TTS_EQUAL(eve::twotonmb(as<T>()), eve::exp2(T(52.0)));
  }
};
