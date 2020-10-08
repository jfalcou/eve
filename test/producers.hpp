//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include "test_distribution.hpp"
#include <tts/ranges.hpp>
#include <eve/memory/align.hpp>
#include <eve/function/store.hpp>

#define TTS_RANGE_CHECK(Producer, Ref, New)                                                         \
  do                                                                                                \
  {                                                                                                 \
    if constexpr(eve::floating_value<EVE_VALUE>)                                                    \
      TTS_ULP_RANGE_CHECK(Producer, (EVE_VALUE), (EVE_TYPE), Ref, New, 2.0);                        \
    else                                                                                            \
      TTS_ULP_RANGE_CHECK(Producer, (EVE_VALUE), (EVE_TYPE), Ref, New, 0.0);                        \
  } while(::tts::detail::done())                                                                    \
/**/

#define TTS_RANGE_CHECK_WITH(Producer, Ref, New, Ulps)                                              \
TTS_ULP_RANGE_CHECK(Producer, (EVE_VALUE), (EVE_TYPE), Ref, New, Ulps);                             \
/**/

namespace eve
{
  template<typename T>
  using uniform_prng =  tts::prng_generator
                        < T
                        , std::conditional_t< std::is_floating_point_v<eve::element_type_t<T>>
                                            , eve::tests_real_distribution<eve::element_type_t<T>>
                                            , std::uniform_int_distribution<eve::element_type_t<T>>
                                            >
                        >;
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
//      auto p = eve::align(src, eve::under{type::static_alignment});
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
//      auto p = eve::align(src, eve::under{type::static_alignment});
      return type(src);
    }

    static void display(type const& v, std::ostream& os) noexcept
    {
      os << v;
    }
  };
}
