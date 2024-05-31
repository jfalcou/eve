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
  struct mhalf_t : constant_callable<mhalf_t, Options, downward_option, upward_option>
  {
    template<floating_value T>
    static constexpr EVE_FORCEINLINE constexpr T value(eve::as<T> const&, auto const&)
    {
      using e_t = element_type_t<T>;

           if constexpr(std::same_as<e_t, float>  ) return T(-0x1p-1);
      else if constexpr(std::same_as<e_t, double> ) return T(-0x1p-1f);
    }

    template<floating_value T>
    requires(plain_scalar_value<element_type_t<T>>)
      EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(mhalf_t, mhalf_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var mhalf
//!   @brief Computes the constant \f$-1/2\f$.
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
//!      T mhalf(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::mhalf(as<T>())` is semantically equivalent to  `T(-0.5)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/mhalf.cpp}
//! @}
//================================================================================================
  inline constexpr auto mhalf = functor<mhalf_t>;
}
