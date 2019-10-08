//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef AS_INTEGER_HPP
#define AS_INTEGER_HPP

#include <eve/function/abs.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/wide.hpp>
#include <eve/logical.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL("Check as_integer modificator on scalar and wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using eve::logical; 

  if constexpr( sizeof(Type) == 8)
  {
    TTS_EXPR_IS((eve::detail::as_integer_t<Type>()),                                 std::int64_t);
    TTS_EXPR_IS((eve::detail::as_integer_t<Type, unsigned>()),                      std::uint64_t);
    TTS_EXPR_IS((eve::detail::as_integer_t<Type,   signed>()),                       std::int64_t);
    TTS_EXPR_IS((eve::detail::as_integer_t<wide<Type, T>>()),             (wide<std::int64_t, T>));
    TTS_EXPR_IS((eve::detail::as_integer_t<wide<Type, T>, unsigned>()) , (wide<std::uint64_t, T>));
    TTS_EXPR_IS((eve::detail::as_integer_t<wide<Type, T>,   signed>()) ,  (wide<std::int64_t, T>));
  }
  if constexpr( sizeof(Type) == 4)
  {
    TTS_EXPR_IS((eve::detail::as_integer_t<Type>()),                               std::int32_t);
    TTS_EXPR_IS((eve::detail::as_integer_t<Type, unsigned>()),                    std::uint32_t);
    TTS_EXPR_IS((eve::detail::as_integer_t<Type,   signed>()),                     std::int32_t);
    TTS_EXPR_IS((eve::detail::as_integer_t<wide<Type, T>>()),             (wide<std::int32_t, T>));
    TTS_EXPR_IS((eve::detail::as_integer_t<wide<Type, T>, unsigned>()) ,  (wide<std::uint32_t, T>));
    TTS_EXPR_IS((eve::detail::as_integer_t<wide<Type, T>,   signed>()) ,  (wide<std::int32_t, T>));
  }
  if constexpr( sizeof(Type) == 2)
  {
    TTS_EXPR_IS((eve::detail::as_integer_t<Type>()),                               std::int16_t);
    TTS_EXPR_IS((eve::detail::as_integer_t<Type, unsigned>()),                    std::uint16_t); 
    TTS_EXPR_IS((eve::detail::as_integer_t<Type,   signed>()),                     std::int16_t);
    TTS_EXPR_IS((eve::detail::as_integer_t<wide<Type, T>>()),             (wide<std::int16_t, T>));
    TTS_EXPR_IS((eve::detail::as_integer_t<wide<Type, T>, unsigned>()) ,  (wide<std::uint16_t, T>));
    TTS_EXPR_IS((eve::detail::as_integer_t<wide<Type, T>,   signed>()) ,  (wide<std::int16_t, T>));
  }
  if constexpr( sizeof(Type) == 1)
  {
    TTS_EXPR_IS((eve::detail::as_integer_t<Type>()),                               std::int8_t);
    TTS_EXPR_IS((eve::detail::as_integer_t<Type, unsigned>()),                    std::uint8_t);
    TTS_EXPR_IS((eve::detail::as_integer_t<Type,   signed>()),                     std::int8_t);
    TTS_EXPR_IS((eve::detail::as_integer_t<wide<Type, T>>()),             (wide<std::int8_t, T>));
    TTS_EXPR_IS((eve::detail::as_integer_t<wide<Type, T>, unsigned>()) ,  (wide<std::uint8_t, T>));
    TTS_EXPR_IS((eve::detail::as_integer_t<wide<Type, T>,   signed>()) ,  (wide<std::int8_t, T>));
  }

  
}

#endif
