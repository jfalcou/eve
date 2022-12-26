//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include "test.hpp"
#include <tts/ranges.hpp>
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
  template<typename T> using uniform_prng = tts::realistic_generator<T>;
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

    static void display(type const& v, std::ostream& os) noexcept
    {
      os << v;
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

    static void display(type const& v, std::ostream& os) noexcept
    {
      os << v;
    }
  };
}
