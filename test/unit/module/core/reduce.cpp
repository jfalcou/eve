//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "unit/module/core/reduction_test.hpp"

//==================================================================================================
// Types tests
//==================================================================================================
// TTS_CASE_TPL("Check return types of eve::reduce(wide)", eve::test::simd::all_types)
// <typename T>(tts::type<T>)
// {
//   using v_t = eve::element_type_t<T>;
//   TTS_EXPR_IS((eve::reduce(T {})), v_t);
//   TTS_EXPR_IS((eve::reduce(T {}, eve::add)), v_t);
//   TTS_EXPR_IS((eve::reduce[eve::splat](T {})), T);
//   TTS_EXPR_IS((eve::reduce[eve::splat](T {}, eve::add)), T);
// };

// //==================================================================================================
// // Arithmetic tests
// //==================================================================================================
// TTS_CASE_TPL("Check behavior of eve::reduce(eve::wide)", eve::test::simd::all_types)
// <typename T>(tts::type<T>)
// {
//   T data = [](auto i, auto c) { return i < c / 2 ? 10 * (i + 1) : -(10 * (i + 1) + 1); };
//   data += 1;

//   typename T::value_type ref = 0;
//   for( std::ptrdiff_t i = 0; i < T::size(); ++i ) ref += data.get(i);

//   TTS_EQUAL(eve::reduce(data, [](auto a, auto b) { return a + b; }), ref);
//   TTS_EQUAL(eve::reduce(data, eve::add), ref);
//   TTS_EQUAL(eve::reduce(data), ref);

//   TTS_EQUAL(eve::reduce[eve::splat](data, [](auto a, auto b) { return a + b; }), T(ref));
//   TTS_EQUAL(eve::reduce[eve::splat](data, eve::add), T(ref));
//   TTS_EQUAL(eve::reduce[eve::splat](data), T(ref));
// };

// //==================================================================================================
// // Logical tests
// //==================================================================================================
// TTS_CASE_WITH("Check behavior of eve::reduce(eve::wide)",
//               eve::test::simd::all_types,
//               tts::generate(tts::logicals(0, 3)))
// <typename T>(T const& a0)
// {
//   TTS_EQUAL(eve::reduce(a0, eve::logical_and), eve::all(a0));
//   TTS_EQUAL(eve::reduce(a0, eve::logical_or), eve::any(a0));
// };

//==================================================================================================
// Neutral tests
//==================================================================================================
struct ManualProd
{
  template<typename T, typename C>
  eve::element_type_t<T> operator()(T v, C mask) const
  {
    auto res = eve::one(eve::as<eve::element_type_t<T>>{});

    for (std::ptrdiff_t i = 0; i < v.size(); ++i)
      if (mask_at(mask, i))
        res *= v.get(i);

    return res;
  }
};

namespace eve
{
  template<typename Options>
  struct reduce_proxy_t : conditional_callable<reduce_proxy_t, Options, splat_option>
  {
    template <typename T>
    EVE_FORCEINLINE auto operator()(T v) const noexcept { return eve::reduce[this->options()](v, eve::mul, eve::one); }
  };
}

TTS_CASE_WITH("Check behavior of eve::reduce with a neutral element",
              eve::test::simd::integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T v)
{
  arithmetic_reduction_test_case<ManualProd>(eve::functor<eve::reduce_proxy_t>, v);
};
