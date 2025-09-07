//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <numeric>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of mean_value", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using wf_t = eve::detail::wf<T>;
  // regular
  TTS_EXPR_IS(eve::mean_value(T(), T()), wf_t);
  TTS_EXPR_IS(eve::mean_value(T(), v_t()), wf_t);
  TTS_EXPR_IS(eve::mean_value(v_t(), T()), wf_t);
  TTS_EXPR_IS(eve::mean_value(v_t(), v_t()), eve::detail::wf<v_t>);

  // multi
  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::mean_value(T(), T(), T()), wf_t);
    TTS_EXPR_IS(eve::mean_value(T(), v_t(), T()), wf_t);
    TTS_EXPR_IS(eve::mean_value(v_t(), T(), T()), wf_t);
    TTS_EXPR_IS(eve::mean_value(T(), T(), v_t()), wf_t);
    TTS_EXPR_IS(eve::mean_value(v_t(), v_t(), T()), wf_t);
    TTS_EXPR_IS(eve::mean_value(v_t(), T(), v_t()), wf_t);

    TTS_EXPR_IS(eve::mean_value(v_t(), v_t(), v_t()), eve::detail::wf<v_t>);
  }
};

//==================================================================================================
//== mean_value tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of mean_value(wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.),
                            tts::randoms(-1000., +1000.)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::mean_value;
  TTS_ULP_EQUAL(mean_value(a0, a1), (a0+a1)/2, 0.5);
  TTS_ULP_EQUAL(mean_value(a0, a1, a2),(a0+a1+a2)/3, 1.0);

//  std::cout << mean_value(1.0, 2.0) << std::endl;
//  std::cout << mean_value(eve::detail::wf(1.0, 1), 2.0) << std::endl;
//   auto wa0 = eve::detail::wf(a0, 1);
//   std::cout << T(wa0) << std::endl;
//   std::cout << (eve::value<decltype(wa0)>) << std::endl;
};

// TTS_CASE_WITH("Check behavior of mean_value(wide)",
//               eve::test::simd::integers,
//               tts::generate(tts::randoms(eve::valmin, eve::valmax)
//                            , tts::randoms(eve::valmin, eve::valmax)))
// <typename T>(T const& a0, T const& a1)
// {
//   using eve::mean_value;
//   using v_t = eve::element_type_t<T>;
//   TTS_ULP_EQUAL(mean_value(a0, a1), tts::map([](auto e, auto f) -> v_t { return std::midpoint(e, f); }, a0, a1), 2);
// };

// //==================================================================================================
// // //==  conditional mean_value tests
// // //==================================================================================================
// // // TTS_CASE_WITH("Check behavior of  mean_value[cond](wide)",
// // //               eve::test::simd::all_types,
// // //               tts::generate(tts::randoms(0, 127), tts::randoms(0, 127), tts::randoms(0, 127)))
// // // <typename T>(T const& a0, T const& a1, T const& a2)
// // // {
// // //   using eve::mean_value;
// // //   using v_t = eve::element_type_t<T>;
// // //   // values can differ by one on integral types from scalar to simd implementations (intrinsics may
// // //   // be at work)
// // //   TTS_ULP_EQUAL(
// // //       mean_value[a2 > T(64)](a0, a1),
// // //       tts::map([](auto e, auto f, auto g) { return g > v_t(64) ? mean_value(e, f) : e; }, a0, a1, a2),
// // //       2);
// // // };


// //==================================================================================================
// //=== Tests for masked mean_value
// //==================================================================================================
// TTS_CASE_WITH("Check behavior of eve::masked(eve::mean_value)(eve::wide)",
//               eve::test::simd::ieee_reals,
//               tts::generate(tts::randoms(eve::valmin, eve::valmax),
//                             tts::randoms(eve::valmin, eve::valmax),
//                             tts::logicals(0, 3)))
// <typename T, typename M>(T const& a0,
//                          T const& a1,
//                          M const& mask)
// {
//   TTS_IEEE_EQUAL(eve::mean_value[mask](a0, a1),
//             eve::if_else(mask, eve::mean_value(a0, a1), a0));
// };

// // //==================================================================================================
// // //===  Tests for lower upper  mean_value
// // //==================================================================================================
// TTS_CASE_WITH("Check behavior of eve::upper(eve::mean_value)(eve::wide)",
//               eve::test::simd::all_types,
//               tts::generate(tts::randoms(eve::valmin, eve::valmax),
//                             tts::randoms(eve::valmin, eve::valmax))
//               )
// <typename T>(T const& a0, T const& a1)
// {
//   using eve::mean_value;
//   using eve::lower;
//   using eve::upper;
//   using eve::strict;
//   TTS_EXPECT(eve::all(eve::mean_value(a0, a1) <= eve::mean_value[eve::upper](a0, a1)));
//   TTS_EXPECT(eve::all(eve::inc(eve::mean_value(a0, a1)) >=eve::mean_value[eve::upper](a0, a1)));
//   T  w0{0.1};
//   T  w1{0.12f};
//   TTS_EXPECT(eve::all(mean_value[upper](w0, w1)  >=  mean_value(w0, w1)));
//   TTS_EXPECT(eve::all(mean_value[lower](w0, -w1) <= mean_value(w0, -w1)));
//   if constexpr (eve::floating_value<T>)
//   {
//     TTS_EXPECT(eve::all(mean_value[strict][upper](w0, w1)  >  mean_value(w0, w1)));
//     TTS_EXPECT(eve::all(mean_value[strict][upper](w0, w1)  >= mean_value(w0, w1)));
//     TTS_EXPECT(eve::all(mean_value[strict][lower](w0, -w1) <  mean_value(w0, -w1)));
//     TTS_EXPECT(eve::all(mean_value[strict][upper](w0, w1)  >= mean_value[upper](w0, w1)));
//     TTS_EXPECT(eve::all(mean_value[strict][lower](w0, -w1) <= mean_value[lower](w0, -w1)));
//   }
// };


// TTS_CASE_WITH("Check behavior of mean_value kahan on wide",
//               eve::test::simd::ieee_reals,
//               tts::generate(tts::randoms(eve::valmin, eve::valmax),
//                             tts::randoms(eve::valmin, eve::valmax),
//                             tts::randoms(eve::valmin, eve::valmax)))
// <typename T>(T const& a0, T const& a1,  T const&a2)
// {
//   using eve::mean_value;
//   using eve::widen;
//   using eve::kahan;
//   using eve::welford;
//   using eve::as;
//   if constexpr(sizeof(eve::element_type_t<T>) < 8)
//   {
//     TTS_ULP_EQUAL(mean_value[kahan](a0, a1, a2), eve::downgrade(mean_value[widen](a0, a1, a2)), 0.5);
//     TTS_ULP_EQUAL(mean_value[welford](1u, a0, a1, a2), eve::downgrade(mean_value[widen](a0, a1, a2)), 0.5);
//     TTS_ULP_EQUAL(mean_value[welford](a0, a1, a2), eve::downgrade(mean_value[widen](a0, a1, a2)), 0.5);
//   }

// };
