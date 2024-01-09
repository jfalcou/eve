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
  struct maxflint_t : constant_callable<maxflint_t, Options, downward_option, upward_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, auto const&)
    {
      using e_t = element_type_t<T>;

           if      constexpr(std::integral<e_t>   ) return T(std::numeric_limits<e_t>::max());
      else if constexpr(std::same_as<e_t, float>  ) return T(0x1p+24);
      else if constexpr(std::same_as<e_t, double> ) return T(0x1p+53);
    }

    template<typename T>
    requires(plain_scalar_value<element_type_t<T>>)
      EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(maxflint_t, maxflint_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var maxflint
//!   @brief Computes the the greatest floating point representing an integer and
//!   such that n != n+1.
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
//!      T maxflint(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::maxflint(as<T>())` is semantically equivalent to:
//!        * `T(16777216.0f)` if `eve::element_type_t<T>` is float.
//!        * `T(9007199254740992.0)` if `eve::element_type_t<T>` is double.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/maxflint.cpp}
//! @}
//================================================================================================
  inline constexpr auto maxflint = functor<maxflint_t>;
}
