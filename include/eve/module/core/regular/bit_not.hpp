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
#include <eve/forward.hpp>
#include <eve/module/core/regular/bit_cast.hpp>

namespace eve
{

  template<typename Options>
  struct bit_not_t : elementwise_callable<bit_not_t, Options, saturated_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(bit_not_t, bit_not_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_not
//!   @brief computes the ones complement of the parameter.
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
//!      T bit_not(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of the bitwise NOT of the parameter is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/bit_not.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_not[mask](x, ...)` provides a masked
//!     version of `bit_not` which is
//!     equivalent to `if_else(mask, bit_not(x, ...), x)`
//!
//! @}
//================================================================================================
  inline constexpr auto bit_not = functor<bit_not_t>;
  
  namespace detail
  {
    template<ordered_value T, callable_options O>
    constexpr T  bit_not_(EVE_REQUIRES(cpu_), O const&, T const& v) noexcept
    {
      if constexpr( floating_scalar_value<T> )
        return bit_cast(~bit_cast(v, as<as_integer_t<T>> {}), as(v));
      else
        return T(~v);
    }
  }
}
