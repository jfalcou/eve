//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include "test.hpp"
#include <eve/memory/align.hpp>
#include <eve/concept/value.hpp>
#include <eve/traits.hpp>

#define EVE_ULP_RANGE_CHECK(Type, Producer, Ref, New)                                               \
  [&]()                                                                                             \
  {                                                                                                 \
    if constexpr(eve::floating_value<eve::element_type_t<T>>)                                       \
      TTS_ULP_RANGE_CHECK(Producer, (eve::element_type_t<T>), (Type), Ref, New, 2.0);               \
    else                                                                                            \
      TTS_ULP_RANGE_CHECK(Producer, (eve::element_type_t<T>), (Type), Ref, New, 0.0);               \
  }()                                                                                               \
/**/

#define EVE_ULP_RANGE_CHECK_WITH(Type, Producer, Ref, New, Ulps)                                    \
TTS_ULP_RANGE_CHECK(Producer, (eve::element_type_t<T>), (Type), Ref, New, Ulps);                    \
/**/


#define TTS_RANGE_CHECK(Producer, Ref, New)                                                         \
  [&]()                                                                                             \
  {                                                                                                 \
    if constexpr(eve::floating_value<EVE_VALUE>)                                                    \
      TTS_ULP_RANGE_CHECK(Producer, (EVE_VALUE), (T), Ref, New, 2.0);                               \
    else                                                                                            \
      TTS_ULP_RANGE_CHECK(Producer, (EVE_VALUE), (T), Ref, New, 0.0);                               \
  }()                                                                                               \
/**/

#define TTS_RANGE_CHECK_WITH(Producer, Ref, New, Ulps)                                              \
TTS_ULP_RANGE_CHECK(Producer, (EVE_VALUE), (T), Ref, New, Ulps);                                    \
/**/

namespace eve
{
  //================================================================================================
  // EVE gives no guarantee on denormals, so the random suite keeps its bounds inside
  // [eps, 1/eps] in magnitude. Integral bounds pass through untouched.
  //================================================================================================
  template<typename T> struct uniform_prng : tts::realistic_generator<T>
  {
    uniform_prng(T mn, T mx) : tts::realistic_generator<T>(bounded(mn), bounded(mx)) {}

    static constexpr T bounded(T v)
    {
      if constexpr(std::floating_point<T>)
      {
        constexpr T lo = std::numeric_limits<T>::epsilon();
        constexpr T hi = T(1) / lo;

        T m = v < 0 ? -v : v;
        if(m > hi)              m = hi;
        else if(m != 0 && m < lo) m = lo;

        return v < 0 ? -m : m;
      }
      else return v;
    }
  };
}

namespace tts
{
  template<typename T>
  struct display<eve::uniform_prng<T>> : display<tts::realistic_generator<T>>
  {};
}

namespace tts
{
  template<typename T,typename N> struct adapter<eve::wide<T,N>>
  {
    using type = eve::wide<T,N>;

    template<typename U, typename Func>
    static void run(T const*& src, U*& dst, Func f) noexcept
    {
      // Load and compute
      type that(src);
      auto res = f(that);
      eve::store(res,dst);

      // Advance pointers to next one
      dst += that.size();
      src += that.size();
    }

    static auto retrieve(T const* src) noexcept
    {
      // realign on SIMD boundaries
      return type(src);
    }

    static void display(type const& v) noexcept
    {
      ::tts::output().write(::tts::as_text(v));
    }
  };

  template<typename T,typename N> struct adapter<eve::logical<eve::wide<T,N>>>
  {
    using type = eve::logical<eve::wide<T,N>>;

    template<typename U, typename Func>
    static void run(eve::logical<T> const*& src, U*& dst, Func f) noexcept
    {
      // Load and compute
      type that(src);
      auto res = f(that);
      eve::store(res,dst);

      // Advance pointers to next one
      dst += that.size();
      src += that.size();
    }

    static auto retrieve(eve::logical<T> const* src) noexcept
    {
      // realign on SIMD boundaries
      return type(src);
    }

    static void display(type const& v) noexcept
    {
      ::tts::output().write(::tts::as_text(v));
    }
  };
}
