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
template < typename T >
auto sc(eve::complex < T > cv)
{
  return std::complex<T>(eve::real(cv), eve::imag(cv));
}

TTS_CASE_WITH( "Check behavior of atanh on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
        , tts::generate( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_RELATIVE_EQUAL(eve::atanh(eve::complex<e_t>(e, f)),  cv(std::atanh(c_t(e, f))), 1.0e-4);
    }
  }
};

TTS_CASE_WITH( "Check behavior of atanh on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(-10, 10)
                             , tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using ce_t = eve::complex<e_t>;
  using z_t = eve::as_complex_t<T>;
  using c_t = std::complex<e_t>;
  auto std_ch = [](auto x, auto y){return cv(std::atanh(c_t(x, y))); };
  auto init_with_std = [std_ch](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z(std_ch(a0.get(i), a1.get(i)));
      b.set(i, z);
    }
    return b;
  };
  TTS_RELATIVE_EQUAL(eve::atanh(z_t{a0,a1}), init_with_std(a0, a1), 1.0e-4);
};


TTS_CASE_TPL( "Check return types of eve::abs", tts::bunch<eve::test::scalar::ieee_reals>)
  <typename T>(tts::type<T>)
{
  auto ulp = (spy::stdlib == spy::libcpp_) ? 100.0 : 0.5;
  using e_t = typename T::value_type;
  using c_t = eve::complex<e_t>;
  using eve::as;
  const int N = 16;
  std::array<c_t, N> inputs =
    { c_t(eve::zero(as<e_t>()),eve::zero(as<e_t>())),//0
      c_t(eve::inf(as<e_t>()),eve::zero(as<e_t>())), //1
      c_t(eve::minf(as<e_t>()),eve::zero(as<e_t>())),//2
      c_t(eve::nan(as<e_t>()),eve::zero(as<e_t>())), //3
      c_t(eve::zero(as<e_t>()),eve::inf(as<e_t>())), //4
      c_t(eve::inf(as<e_t>()),eve::inf(as<e_t>())),  //5
      c_t(eve::minf(as<e_t>()),eve::inf(as<e_t>())), //6
      c_t(eve::nan(as<e_t>()),eve::inf(as<e_t>())),  //7
      c_t(eve::zero(as<e_t>()),eve::minf(as<e_t>())),//8--
      c_t(eve::inf(as<e_t>()),eve::minf(as<e_t>())), //9
      c_t(eve::minf(as<e_t>()),eve::minf(as<e_t>())),//10
      c_t(eve::nan(as<e_t>()),eve::minf(as<e_t>())), //11
      c_t(eve::zero(as<e_t>()),eve::nan(as<e_t>())), //12
      c_t(eve::inf(as<e_t>()),eve::nan(as<e_t>())),  //13
      c_t(eve::minf(as<e_t>()),eve::nan(as<e_t>())), //14
      c_t(eve::nan(as<e_t>()),eve::nan(as<e_t>())),  //15
    };

  for(int i=0; i < N; ++i)
  {
    if((i != 2 && i != 1)){
      // this curious test corresponds to the fact that neither std::atanh nor std::atanh are correct for inputs (0, inf) or (0, -inf)
      // peculiarly they contredict the C99 specification that atanh is odd
      // atanh should behave "the same as C99 function catanh, defined in subclause 7.3.6.3 and G.5.2.3."
      // the if clause has to be removed if/when libc++ will be corrected
      TTS_ULP_EQUAL(eve::atanh(inputs[i]), cv(std::atanh(sc(inputs[i]))), ulp);
      TTS_ULP_EQUAL(eve::atanh(-inputs[i]), cv(std::atanh(sc(-inputs[i]))), ulp);
    }
  }
};
