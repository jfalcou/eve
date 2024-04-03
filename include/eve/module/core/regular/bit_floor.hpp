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
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/bit_width.hpp>
#include <eve/module/core/dec.hpp>
#include <eve/module/core/if_else.hpp>
#include <eve/module/core/ifrexp.hpp>
#include <eve/module/core/is_eqz.hpp>
#include <eve/module/core/is_ltz.hpp>
#include <eve/module/core/ldexp.hpp>

namespace eve
{
  template<typename Options>
  struct bit_floor_t : elementwise_callable<bit_floor_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(bit_floor_t, bit_floor_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_floor
//!   @brief If `x` is not zero, computes the largest integral power of two
//!   that is not greater than `x`.
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
//!      T bit_floor(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!      * The value of the largest integral power of two
//!        that is not greater than `x` is returned.
//!
//!      * If `x` is zero returns zero.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/bit_floor.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_floor[mask](x, ...)` provides a masked
//!     version of `bit_floor` which is
//!     equivalent to `if_else(mask, bit_floor(x, ...), x)`
//!
//! @}
//================================================================================================
  inline constexpr auto bit_floor = functor<bit_floor_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    bit_floor_(EVE_REQUIRES(cpu_), O const&, T const& v) noexcept
    {
      auto vlt1 = v < one(eve::as(v));
      if constexpr( scalar_value<T> )
        if( vlt1 ) return zero(eve::as(v));
      if constexpr( floating_ordered_value<T> )
      {
        auto [m, e] = ifrexp(v);
        e           = dec(e);
        auto r      = eve::ldexp(one(eve::as(v)), e);
        if constexpr( scalar_value<T> ) return r;
        else return if_else(vlt1, eve::zero, r);
      }
      else if constexpr( signed_integral_value<T> )
      {
        auto uz = bit_floor(uint_(v));
        return if_else(is_ltz(v), zero, to_<T>(uz));
      }
      else
      {
        return if_else(is_eqz(v), zero, T {1} << dec(bit_width(v)));
      }
    }
  }
}
