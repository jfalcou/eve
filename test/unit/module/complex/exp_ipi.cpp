//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
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

TTS_CASE_WITH( "Check behavior of exp_ipi on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
        , tts::generate( tts::randoms(1, 10)
                             , tts::randoms(1, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  using eve::as;
  auto pis = eve::pi(as<e_t>());
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_ULP_EQUAL(eve::exp_ipi(eve::complex<e_t>(e, f)),  cv(std::exp(c_t(-pis*f, pis*e))), 300.0);
      TTS_ULP_EQUAL(eve::exp_ipi(eve::complex<e_t>(e, f)),  cv(std::exp(c_t(-pis*f, pis*e))), 300.0);
    }
  }
};

TTS_CASE_WITH( "Check behavior of exp_ipi on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(1, 10), tts::randoms(1, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using ce_t = eve::complex<e_t>;
  using z_t =  eve::as_complex_t<T>;
  using c_t = std::complex<e_t>;
  auto pis = eve::pi(eve::as<e_t>());
  auto std_exp_ipi = [pis](auto x, auto y){return cv(std::exp(c_t(-pis*y, pis*x))); };
  auto init_with_std = [std_exp_ipi](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z = std_exp_ipi(a0.get(i), a1.get(i));
      b.set(i, z);
    }
    return b;
  };
  TTS_ULP_EQUAL(eve::exp_ipi(z_t{a0,a1}), init_with_std(a0, a1), 600.0);
};
