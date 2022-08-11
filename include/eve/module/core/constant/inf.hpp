//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/decorator/roundings.hpp>

#include <limits>

#include <type_traits>

namespace eve
{
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
EVE_MAKE_CALLABLE(inf_, inf);

namespace detail
{
  template<floating_value T>
  EVE_FORCEINLINE constexpr auto inf_(EVE_SUPPORTS(cpu_), as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    return T(std::numeric_limits<t_t>::infinity());
  }

  template<floating_value T, typename D>
  EVE_FORCEINLINE constexpr auto inf_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return inf(as<T>());
  }
}
}
