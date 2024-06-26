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
#include <eve/module/core/regular/is_flint.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/detail/assert_utils.hpp>

namespace eve
{
  template<typename Options>
  struct sign_alternate_t : elementwise_callable<sign_alternate_t, Options>
  {
    template<eve::signed_value T>
    constexpr EVE_FORCEINLINE T operator()(T n) const noexcept
    {
      EVE_ASSERT(eve::all(is_flint(n)), "sign_alternate : some entries are not flint");
      return EVE_DISPATCH_CALL(n);
    }

    EVE_CALLABLE_OBJECT(sign_alternate_t, sign_alternate_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var sign_alternate
//!   @brief Computes \f$(-1)^n\f$.
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
//!      template< eve::signed_value T >
//!      T sign_alternate(T n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [argument](@ref eve::value). Must be signed integral or flint.
//!
//!    **Return value**
//!
//!      \f$(-1)^n\f$ is returned.
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/sign_alternate.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::sign_alternate[mask](x)` provides a masked version of `eve::sign_alternate`
//!     which is equivalent to `if_else (mask, sign_alternate(x), x)`.
//!
//! @}
//================================================================================================
  inline constexpr auto sign_alternate = functor<sign_alternate_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    sign_alternate_(EVE_REQUIRES(cpu_), O const &, T const& n) noexcept
    {
      if constexpr(integral_scalar_value<T>)
        return n&1 ? T(-1) : T(1);
      else
        return if_else(is_odd(n), mone, one(as(n)));
    }
  }
}
