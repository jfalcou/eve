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
  struct mone_t : constant_callable<mone_t, Options, downward_option, upward_option>
  {
    template<typename T>
    static constexpr EVE_FORCEINLINE T value(eve::as<T> const&, auto const&)
    {
      return T(-1);
    }

    template<typename T>
    requires(plain_scalar_value<element_type_t<T>>)
      constexpr EVE_FORCEINLINE T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(mone_t, mone_);
  };

//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var mone
//!   @brief Computes the constant \f$-1\f$
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
//!      T mone(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::mone(as<T>())` is semantically equivalent to  `T(-1)`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/mone.cpp}
//! @}
//================================================================================================
inline constexpr auto mone = functor<mone_t>;

// Required for if_else optimisation detections
using callable_mone_ = tag_t<mone>;
}
