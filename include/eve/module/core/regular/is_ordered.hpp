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

namespace eve
{
  template<typename Options>
  struct is_ordered_t : elementwise_callable<is_ordered_t, Options>
  {
    template<value T,  value U>
    constexpr EVE_FORCEINLINE common_logical_t<T,U>  operator()(logical<T> a, logical<U> b) const
    {
      return EVE_DISPATCH_CALL(a, b);
    }

    EVE_CALLABLE_OBJECT(is_ordered_t, is_ordered_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_ordered
//!   @brief Returns a logical true  if and only no parameter is NaN.
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
//!      template< eve::value T, eve::value U >
//!      eve::as_logical<T> is_ordered(T x,U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    The call `eve::is_ordered(x,y)`  is semantically  equivalent
//!    to `eve::is_not_nan(x) && eve::is_not_nan(y)`:
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_ordered.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_ordered[mask](x,y)` provides a masked version of `eve::is_ordered` which
//!     is equivalent to `if_else (mask, is_ordered(x), eve::false( eve::as(x,y)))`.
//!
//! @}
//================================================================================================
  inline constexpr auto is_ordered = functor<is_ordered_t>;

  namespace detail
  {
    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr common_logical_t<T,U>
    is_ordered_(EVE_REQUIRES(cpu_),
                  O const & ,
                  logical<T> const& , logical<U> const& ) noexcept
    {
      using r_t =  common_value_t<T, U>;
      return true_(as<r_t>());
    }


    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr common_logical_t<T,U>
    is_ordered_(EVE_REQUIRES(cpu_),
                  O const & ,
                  T const& aa, U const& bb) noexcept
    {
      using w_t =  common_value_t<T, U>;
      {
        if constexpr(integral_value<T> )
          return false_(as<w_t>());
        else
        {
          auto a = w_t(aa);
          auto b = w_t(bb);
          return (a == a) && (b == b);
        }
      }
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_ordered.hpp>
#endif
