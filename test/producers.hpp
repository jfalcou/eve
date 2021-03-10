//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#define TTS_MAIN
#include "test_distribution.hpp"
#include <tts/ranges.hpp>
#include <eve/memory/align.hpp>
#include <eve/function/store.hpp>

#define TTS_RANGE_CHECK(Producer, Ref, New)                                                         \
  do                                                                                                \
  {                                                                                                 \
    if constexpr(eve::floating_value<EVE_VALUE>)                                                    \
      TTS_ULP_RANGE_CHECK(Producer, (EVE_VALUE), (T), Ref, New, 2.0);                               \
    else                                                                                            \
      TTS_ULP_RANGE_CHECK(Producer, (EVE_VALUE), (T), Ref, New, 0.0);                               \
  } while(::tts::detail::done())                                                                    \
/**/

#define TTS_RANGE_CHECK_WITH(Producer, Ref, New, Ulps)                                              \
TTS_ULP_RANGE_CHECK(Producer, (EVE_VALUE), (T), Ref, New, Ulps);                                    \
/**/

namespace eve
{
  template<typename T> using uniform_prng = tts::prng_generator< T, prng<T>>;
}

namespace tts
{
  template<typename T,typename N,typename ABI> struct adapter<eve::wide<T,N,ABI>>
  {
    using type = eve::wide<T,N,ABI>;

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

  template<typename T,typename N,typename ABI> struct adapter<eve::logical<eve::wide<T,N,ABI>>>
  {
    using type = eve::logical<eve::wide<T,N,ABI>>;

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
