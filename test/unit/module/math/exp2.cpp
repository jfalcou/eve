//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of exp2", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::exp2(T()), T);
  TTS_EXPR_IS(eve::exp2(v_t()), v_t);
};

//==================================================================================================
//==  exp2  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of exp2 on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::minlog2, eve::maxlog2), tts::randoms(-1.0, 1.0)))
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::exp2(a0), map([](auto e) -> v_t { return std::exp2(e); }, a0), 30);
  TTS_ULP_EQUAL(eve::exp2(a1), map([](auto e) -> v_t { return std::exp2(e); }, a1), 2);

  TTS_ULP_EQUAL(eve::exp2[eve::pedantic](a0), map([](auto e) -> v_t { return std::exp2(e); }, a0), 30);
  TTS_ULP_EQUAL(eve::exp2[eve::pedantic](a1), map([](auto e) -> v_t { return std::exp2(e); }, a1), 2);
};

TTS_CASE_TPL("Check return types of exp2", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  TTS_ULP_EQUAL(eve::exp2[eve::pedantic](T(1)), T(2), 0.5);
  TTS_IEEE_EQUAL(eve::exp2[eve::pedantic](T(0)), T(1));

  if constexpr( eve::floating_value<T> )
  {
    using elt_t = eve::element_type_t<T>;
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_IEEE_EQUAL(eve::exp2(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(eve::exp2(eve::inf(eve::as<T>())), eve::inf(eve::as<T>()));
      TTS_IEEE_EQUAL(eve::exp2(eve::minf(eve::as<T>())), T(0));
      TTS_IEEE_EQUAL(eve::exp2[eve::pedantic](eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(eve::exp2[eve::pedantic](eve::inf(eve::as<T>())), eve::inf(eve::as<T>()));
      TTS_IEEE_EQUAL(eve::exp2[eve::pedantic](eve::minf(eve::as<T>())), T(0));
    }

    TTS_IEEE_EQUAL(eve::exp2(T(-0.)), T(1));
    TTS_ULP_EQUAL(eve::exp2(T(-1)), T(0.5), 0.5);
    TTS_ULP_EQUAL(eve::exp2(eve::minlog2(eve::as<T>())), T(0), 0.5);
    TTS_ULP_EQUAL(eve::exp2(eve::prev(eve::minlog2(eve::as<T>()))), T(0), 0.5);

    TTS_ULP_EQUAL(eve::exp2(eve::minlog2denormal(eve::as<T>())),
                  T(std::exp2(eve::minlog2denormal(eve::as<elt_t>()))),
                  0.5);

    TTS_IEEE_EQUAL(eve::exp2[eve::pedantic](T(-0.)), T(1));
    TTS_ULP_EQUAL(eve::exp2[eve::pedantic](T(-1)), T(0.5), 0.5);
    if constexpr( eve::platform::supports_denormals )
    {
      TTS_ULP_EQUAL(eve::exp2[eve::pedantic](eve::minlog2(eve::as<T>())),
                    T(std::exp2(eve::minlog2(eve::as<elt_t>()))),
                    0.5);
      TTS_ULP_EQUAL(eve::exp2[eve::pedantic](eve::prev(eve::minlog2(eve::as<T>()))),
                    T(std::exp2(eve::prev(eve::minlog2(eve::as<elt_t>())))),
                    0.5);
    }
    TTS_ULP_EQUAL(eve::exp2[eve::pedantic](eve::minlog2denormal(eve::as<T>())),
                  T(std::exp2(eve::minlog2denormal(eve::as<elt_t>()))),
                  0.5);
    TTS_ULP_EQUAL(eve::exp2[eve::pedantic](eve::prev(eve::minlog2denormal(eve::as<T>()))),
                  T(std::exp2(eve::prev(eve::minlog2denormal(eve::as<elt_t>())))),
                  0.5);
  }
};

TTS_CASE_TPL("Check conversion behavior", eve::test::simd::integers)
<typename T>(tts::type<T>)
{
   using v_t  = eve::element_type_t<T>;
//   using fl_t = eve::as_floating_point_t<T>;
   if constexpr( eve::scalar_value<T> )
   {
     TTS_EXPR_IS(eve::exp2(T(), eve::as<double>()), double);
     TTS_EXPR_IS(eve::exp2(T(0), eve::as<float>()), float);
     TTS_IEEE_EQUAL(eve::exp2(T(37), eve::as<float>()), exp2(float(37)));
     TTS_IEEE_EQUAL(eve::exp2(T(126), eve::as<float>()), exp2(float(126)));
     if constexpr( sizeof(v_t) > 1 || std::is_unsigned_v<v_t> )
     {
       TTS_IEEE_EQUAL(eve::exp2(eve::next(T(127)), eve::as<float>()), eve::inf(eve::as<float>()));
       TTS_IEEE_EQUAL(eve::exp2(T(129), eve::as<float>()), eve::inf(eve::as<float>()));
     }

     TTS_IEEE_EQUAL(eve::exp2(T(37), eve::as<double>()), exp2(double(37)));
     TTS_IEEE_EQUAL(eve::exp2(T(127), eve::as<double>()), exp2(double(127)));
     if constexpr( sizeof(v_t) > 1 )
     {
       TTS_IEEE_EQUAL(eve::exp2(eve::next(T(1023)), eve::as<double>()), eve::inf(eve::as<double>()));
       TTS_IEEE_EQUAL(eve::exp2(T(1025), eve::as<double>()), eve::inf(eve::as<double>()));
     }
   }
   else
   {
     using d_t = eve::as_wide_as_t<double, T>;
     using f_t = eve::as_wide_as_t<float, T>;

     TTS_EXPR_IS(eve::exp2(T(), eve::as<double>()),d_t );
     TTS_EXPR_IS(eve::exp2(T(), eve::as<float >()), f_t );
     TTS_IEEE_EQUAL(eve::exp2(T(37), eve::as<float>()), eve::exp2(f_t(37)));
     TTS_IEEE_EQUAL(eve::exp2(T(126), eve::as<float>()), eve::exp2(f_t(126)));
     if constexpr( sizeof(v_t) > 1 || std::is_unsigned_v<v_t> )
     {
       TTS_IEEE_EQUAL(eve::exp2(eve::next(T(127)), eve::as<float>()), eve::inf(eve::as<f_t>()));
       TTS_IEEE_EQUAL(eve::exp2(T(129), eve::as<float>()), eve::inf(eve::as<f_t>()));
     }

     TTS_IEEE_EQUAL(eve::exp2(T(37), eve::as<double>()), eve::exp2(d_t(37)));
     TTS_IEEE_EQUAL(eve::exp2(T(127), eve::as<double>()), eve::exp2(d_t(127)));
     if constexpr( sizeof(v_t) > 1 )
     {
       TTS_IEEE_EQUAL(eve::exp2(eve::next(T(1023)), eve::as<double>()), eve::inf(eve::as<d_t>()));
       TTS_IEEE_EQUAL(eve::exp2(T(1025), eve::as<double>()), eve::inf(eve::as<d_t>()));
     }
   }
};


//==================================================================================================
// Tests for masked exp2
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::exp2)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::exp2[mask](a0),
            eve::if_else(mask, eve::exp2(a0), a0));
};
