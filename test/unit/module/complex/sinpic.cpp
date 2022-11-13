//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>
#include <complex>

template < typename T >
auto cv(std::complex < T > sc)
{
  return eve::complex<T>(sc.real(), sc.imag());
}

TTS_CASE_WITH( "Check behavior of sinpic on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
        ,tts::generate(tts::randoms(-10, 10)
                             ,tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  auto p = eve::pi(eve::as<e_t>());
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_RELATIVE_EQUAL(eve::sinpic(eve::complex<e_t>(e, f)),  cv(std::sin(c_t(p*e, p*f))/c_t(p*e, p*f)), 5.0e-3);
    }
  }
};

TTS_CASE_WITH( "Check behavior of sinpic on wide"
             , eve::test::simd::ieee_reals
             ,tts::generate(tts::randoms(-5, 5)
                           ,tts::randoms(-5, 5)
                           )
             )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using ce_t = eve::complex<e_t>;
  using z_t = eve::as_complex_t<T>;
  using c_t = std::complex<e_t>;
  auto std_ch = [](auto xx, auto yy){auto x = eve::pi(eve::as<e_t>())*xx;
                                     auto y = eve::pi(eve::as<e_t>())*yy;return std::sin(c_t(x, y))/c_t(x, y); };
  auto init_with_std = [std_ch](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z = cv(std_ch(a0.get(i), a1.get(i)));
      b.set(i, z);
    }
    return b;
  };
  TTS_RELATIVE_EQUAL(eve::sinpic(z_t{a0,a1}), init_with_std(a0, a1), 5.0e-3);
};
