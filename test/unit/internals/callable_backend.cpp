//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

namespace eve
{
  template<typename Options>
  struct func_t : elementwise_callable<func_t, Options>
  {
    template<simd_value T, typename U>
    T operator()(T a, U b) const { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(func_t, func_);
  };

  inline constexpr auto func = functor<func_t>;

  namespace _ {
    template<eve::callable_options O, simd_value T>
    T func_(EVE_REQUIRES(cpu_), O const&, T, T)
    {
      return T { 11 };
    }

    template<eve::callable_options O, typename T, typename N>
    wide<T, N> func_(EVE_REQUIRES(cpu_), O const&, wide<T, N>, T)
    {
      return wide<T, N> { 22 };
    }

    template<eve::callable_options O, conditional_expr C, simd_value T>
    T func_(EVE_REQUIRES(cpu_), C const&, O const&, T, T)
    {
      return T { 33 };
    }

    template<eve::callable_options O, conditional_expr C, typename T, typename N>
    wide<T, N> func_(EVE_REQUIRES(cpu_), C const&, O const&, wide<T, N>, T)
    {
      return wide<T, N> { 44 };
    }
  }
}

TTS_CASE("Check elementwise callable backend selection")
{
  using W = eve::wide<float>;

  W w{1};
  float s = 55.0f;
  int si = 55;

  TTS_EQUAL(eve::func(w, w), W { 11 });
  TTS_EQUAL(eve::func(w, s), W { 22 });
  TTS_EQUAL(eve::func(w, si), W { 22 });

  TTS_EQUAL(eve::func[eve::ignore_none](w, w), W { 11 });
  TTS_EQUAL(eve::func[eve::ignore_none](w, s), W { 22 });
  TTS_EQUAL(eve::func[eve::ignore_none](w, si), W { 22  });

  TTS_EQUAL(eve::func[true](w, w), W { 33 });
  TTS_EQUAL(eve::func[true](w, s), W { 44 });
  TTS_EQUAL(eve::func[true](w, si), W { 44 });
};
