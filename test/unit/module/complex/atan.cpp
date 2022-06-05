//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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

// EVE_TEST( "Check behavior of atan on scalar"
//         , eve::test::scalar::ieee_reals
//         , eve::test::generate( eve::test::randoms(-10, 10)
//                              , eve::test::randoms(-10, 10))
//         )
//   <typename T>(T const& a0, T const& a1 )
// {
//   using e_t = typename T::value_type;
//   using c_t = std::complex<e_t>;
//   for(auto e : a0)
//   {
//     for(auto f : a1)
//     {
//       TTS_ULP_EQUAL(eve::atan(eve::complex<e_t>(e, f)),  cv(std::atan(c_t(e, f))), 2.0);
//     }
//   }
// };

// EVE_TEST( "Check behavior of atan on wide"
//         , eve::test::simd::ieee_reals
//         , eve::test::generate(eve::test::randoms(-10, 10)
//                              , eve::test::randoms(-10, 10))
//         )
//   <typename T>(T const& a0, T const& a1 )
// {
//   using e_t = typename T::value_type;
//   using ce_t = eve::complex<e_t>;
//   using z_t = eve::as_complex_t<T>;
//   using c_t = std::complex<e_t>;
//   auto std_ch = [](auto x, auto y){return cv(std::atan(c_t(x, y))); };
//   auto init_with_std = [std_ch](auto a0,  auto a1){
//     z_t b;
//     for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
//     {
//       ce_t z(std_ch(a0.get(i), a1.get(i)));
//       b.set(i, z);
//     }
//     return b;
//   };
//   TTS_ULP_EQUAL(eve::atan(z_t{a0,a1}), init_with_std(a0, a1), 2);
// };


EVE_TEST_TYPES( "Check return types of eve::abs", eve::test::scalar::ieee_reals)
  <typename T>(eve::as<T>)
{
  using e_t = eve::element_type_t<T>;
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

  auto atanine = (eve::atan);
  auto tatanine= [](auto z){return -(eve::i*eve::atanh(eve::i*z));};
  for(int i=0; i < N; ++i)
  {
    TTS_IEEE_EQUAL(atanine(inputs[i]), -atanine(-inputs[i]));
    TTS_IEEE_EQUAL(atanine(inputs[i]), tatanine(inputs[i]));
  }
};
