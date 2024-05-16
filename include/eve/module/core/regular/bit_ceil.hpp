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
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/regular/bit_floor.hpp>
#include <eve/module/core/regular/dec.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/ifrexp.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/is_less_equal.hpp>
#include <eve/module/core/regular/ldexp.hpp>

namespace eve
{
  template<typename Options>
  struct bit_ceil_t : elementwise_callable<bit_ceil_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(bit_ceil_t, bit_ceil_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_ceil
//!   @brief Computes the smallest integral power of two that is not smaller than `x`.
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
//!      T bit_ceil(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of the smallest integral power of two that is not smaller than `x`
//!    is returned.
//!
//!   If that value is not representable in `T`, the behavior is undefined.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/bit_ceil.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_ceil[mask](x, ...)` provides a masked
//!     version of `bit_ceil` which is
//!     equivalent to `if_else(mask, bit_ceil(x, ...), x)`
//!
//! @}
//================================================================================================
  inline constexpr auto bit_ceil = functor<bit_ceil_t>;


  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    bit_ceil_(EVE_REQUIRES(cpu_), O const&, T const& v) noexcept
    {
      auto vle1 = v <= one(eve::as(v));
      if constexpr( scalar_value<T> )
      {
        if( vle1 ) return one(eve::as(v));
      }
      if constexpr( floating_value<T> )
      {
        auto [m, e] = ifrexp(v);
        e           = dec(e);
        auto tmp    = ldexp(one(eve::as(v)), e);
        auto tmpltv = tmp < v;
        if constexpr( scalar_value<T> )
          return tmpltv ? tmp + tmp : tmp;
        else
          return if_else(vle1, one(eve::as(v)), add[tmpltv](tmp, tmp));
      }
      else
      {
        auto tmp    = bit_floor(v);
        auto tmpltv = tmp < v;
        if constexpr( scalar_value<T> )
          return T(tmpltv ? tmp + tmp : tmp);
        else
          return if_else(vle1, one, add[tmpltv](tmp, tmp));
      }
    }
  }
}
