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
  struct mzero_t : constant_callable<mzero_t, Options, lower_option, upper_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, auto const&)
    {
      if      constexpr(std::integral<T>        ) return T(0);
      else if constexpr(std::same_as<T, float>  ) return T(-0.0f);
      else if constexpr(std::same_as<T, double> ) return T(-0.0);
   }

    template<plain_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(mzero_t, mzero_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var mzero
//!   @brief Computes the negative zero value
//!
//!    For integral type there is no difference between eve::zero and eve::mzero,
//!    but for floating ones the bit of sign differs.
//!
//!     However, eve::mzero always satisfies the equality predicate with eve::zero
//!     and `eve::mzero` satisfies the predicate `is_negative`, but not the predicate `is_ltz`.
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
//!     template<eve::plain_value T> constexpr T mzero(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::mzero(as<T>())` is semantically equivalent to `T(-0.0)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/mzero.cpp}
//!
//================================================================================================
  inline constexpr auto mzero = functor<mzero_t>;
//================================================================================================
//! @}
//================================================================================================
}
