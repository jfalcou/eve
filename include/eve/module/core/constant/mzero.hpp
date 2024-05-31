//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve
{
  template<typename Options>
  struct mzero_t : constant_callable<mzero_t, Options, downward_option, upward_option>
  {
    template<typename T>
    static constexpr EVE_FORCEINLINE T value(eve::as<T> const&, auto const&)
    {
      using e_t = element_type_t<T>;

           if constexpr(std::integral<e_t>        ) return T(0);
      else if constexpr(std::same_as<e_t, float>  ) return T(-0.0f);
      else if constexpr(std::same_as<e_t, double> ) return T(-0.0);
   }

    template<typename T>
    requires(plain_scalar_value<element_type_t<T>>)
      constexpr EVE_FORCEINLINE T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

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
//!      template< eve::value T >
//!      T mzero(as<T> x) noexcept;
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
//! @}
//================================================================================================
  inline constexpr auto mzero = functor<mzero_t>;

}
