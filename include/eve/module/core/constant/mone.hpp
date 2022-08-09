//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/decorator/roundings.hpp>

#include <type_traits>

namespace eve
{
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
EVE_MAKE_CALLABLE(mone_, mone);

namespace detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto mone_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    return T(-1);
  }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto mone_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return mone(as<T>());
  }
}
}
