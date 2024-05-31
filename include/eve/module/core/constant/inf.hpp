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
  struct inf_t : constant_callable<inf_t, Options, downward_option, upward_option>
  {
    template<floating_value T>
    static constexpr EVE_FORCEINLINE constexpr T value(eve::as<T> const&, auto const&)
    {
      using e_t = element_type_t<T>;

      return T(std::numeric_limits<e_t>::infinity());
   }

    template<floating_value T>
    requires(plain_scalar_value<element_type_t<T>>)
      EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(inf_t, inf_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var inf
//!   @brief Computes the infinity ieee value.
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
//!      T inf(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::inf(as<T>())` is semantically equivalent to
//!      `T(std::numeric_limits<eve::element_type_t<T>>::``infinity())`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/inf.cpp}
//! @}
//================================================================================================
  inline constexpr auto inf = functor<inf_t>;
}
