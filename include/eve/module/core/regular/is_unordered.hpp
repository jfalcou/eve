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
  struct is_unordered_t : elementwise_callable<is_unordered_t, Options>
  {
    template<value T,  value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE common_logical_t<T,U>  operator()(T a, U b) const
    {
      return EVE_DISPATCH_CALL(a, b);
    }

    EVE_CALLABLE_OBJECT(is_unordered_t, is_unordered_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_unordered
//!   @brief `elementwise callable` returning a logical true  if and only if at least one of the parameters is NaN.
//!
//!   @groupheader{Header file}
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
//!      constexpr auto is_unordered(value auto x, value auto y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    The call `eve::is_unordered(x,y)`  is semantically  equivalent
//!    to `eve::is_nan(x) || eve::is_nan(y)`:
//!
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_unordered.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_unordered[mask](x,y)` provides a masked version of `eve::is_unordered`
//!     which is equivalent to `if_else (mask, is_unordered(x), eve::false( eve::as(x,y)))`.
//!
//! @}
//================================================================================================
  inline constexpr auto is_unordered = functor<is_unordered_t>;

  namespace detail
  {
    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr auto
    is_unordered_(EVE_REQUIRES(cpu_),
                  O const & ,
                  logical<T> const& , logical<U> const& ) noexcept
    {
      using r_t =  common_logical_t<logical<T>, logical<U>>;
      return false_(as<r_t>());
    }


    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr auto
    is_unordered_(EVE_REQUIRES(cpu_),
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
          return (a != a) || (b != b);
        }
      }
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_unordered.hpp>
#endif
