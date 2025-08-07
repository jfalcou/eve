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

namespace eve
{
  template<typename Options>
  struct fma_two_prod_t : callable<fma_two_prod_t, Options>
  {
    template<eve::floating_value T, eve::floating_value U>
    constexpr EVE_FORCEINLINE kumi::tuple<common_value_t<T, U>, common_value_t<T, U>>
    operator()(T t, U u) const noexcept
    { return EVE_DISPATCH_CALL(t, u); }

    EVE_CALLABLE_OBJECT(fma_two_prod_t, fma_two_prod_);
  };

//================================================================================================
//! @addtogroup core_accuracy
//! @{
//!   @var two_prod
//!   @brief Computes the [elementwise](@ref glossary_elementwise)
//!   pair of  product and error,
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
//!      template< eve::floating_value T, eve::floating_value U  >
//!      auto two_prod(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     Computes [elementwise](@ref glossary_elementwise) a pair of values `[a,e]` such that:
//!
//!     * `a` is `x*y`
//!     * `e` is a value such that `a`\f$\oplus\f$`e` is equal to `x`\f$\otimes\f$`y`
//!
//!    where \f$\oplus\f$ (resp. \f$\otimes\f$) adds (resp. multiplies) its two parameters with
//!    infinite precision.
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/two_prod.cpp}
//!
//! @}
//================================================================================================
  inline constexpr auto fma_two_prod = functor<fma_two_prod_t>;

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    EVE_FORCEINLINE auto
    fma_two_prod_(EVE_REQUIRES(cpu_), O const&
                 , T a
                 , U b) noexcept
    {
      auto m = a * b;
      auto err = fms[pedantic](a, b, m);
      return eve::zip(m, err);
    }
  }
}
