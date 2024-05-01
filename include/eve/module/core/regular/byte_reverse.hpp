//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/bit_swap_adjacent.hpp>
#include <eve/detail/builtin_detect.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/bit_shl.hpp>
#include <eve/module/core/regular/bit_shr.hpp>
#include <eve/module/core/regular/shuffle.hpp>
#
namespace eve
{

  template<typename Options>
  struct byte_reverse_t : elementwise_callable<byte_reverse_t, Options>
  {
    template<eve::integral_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(byte_reverse_t, byte_reverse_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var byte_reverse
//!   @brief elementwise reverses the byte order.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::value T >
//!      T byte_reverse(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    The values of the parameter elements are returned with bytes in reversed order.
//!
//!   @note eve::byte_reverse is the functional equivalent to std::byte_swap.
//!   However, we decided to name it byte_reverse in order to keep a proper naming
//!   scheme aligned with the eve::bit_swap/eve::bit_reverse functions.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/byte_reverse.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::byte_reverse[mask](x, ...)` provides a masked
//!     version of `byte_reverse` which is
//!     equivalent to `if_else(mask, byte_reverse(x, ...), x)`
//!
//! @}
//================================================================================================
  inline constexpr auto byte_reverse = functor<byte_reverse_t>;

  namespace detail
  {
    template<unsigned_scalar_value T> T bswap(T x)
    {
      constexpr size_t S = sizeof(T);
      auto bs=[](auto x){
        auto b = std::bit_cast<std::array<std::uint8_t, S>>(x);
        std::reverse(b.begin(), b.end());
        return std::bit_cast<T>(b);
      };
      if      constexpr(sizeof(T)==1) return x;
      else if constexpr(sizeof(T)==2) return bit_shl(x, 8) | bit_shr(x, 8);
      else if constexpr(sizeof(T)==4)
      {
        if constexpr(has_builtin_swap32())  return builtin_bswap32(x);
        else return bs(x);
      }
      else if constexpr(sizeof(T)==8)
      {
        if constexpr(has_builtin_swap64()) return builtin_bswap64(x);
        else return bs(x);
      }
    }

    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    byte_reverse_(EVE_REQUIRES(cpu_), O const&, T const& x) noexcept
    {
      if constexpr(scalar_value<T>)
      {
        using u_t = as_uinteger_t<T>;
        return std::bit_cast<T>(bswap(std::bit_cast<u_t>(x)));
      }
      else
      {
        using e_t =  element_type_t<T>;
        constexpr auto S = sizeof(e_t);
        if constexpr(S == 1) return x;
        else
        {
          constexpr auto C = cardinal_v<T>;
          using u8_t = wide<uint8_t, fixed<S*C>>;
          auto p = [] (auto i, auto ) { auto S = sizeof(e_t); return (i/S+1)*S-1-i%S; };
          auto y = eve::shuffle(bit_cast(x, as<u8_t>()), eve::as_pattern(p));
          return bit_cast(y, as<T>());
        }
      }
    }
  }
}
