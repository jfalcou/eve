//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/module/core/decorator/roundings.hpp>

#include <limits>

namespace eve
{
//================================================================================================
//! @addtogroup core_constants
//! @{
//!   @var valmin
//!   @brief Computes the the lowest representable value.
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
//!      T valmin(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::valmin(as<T>())` is semantically equivalent to
//!     `T(std::numeric_limits<element_type_t<T>>::``lowest())`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/constant/valmin.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(valmin_, valmin);

namespace detail
{
  template<typename T> EVE_FORCEINLINE auto valmin_(EVE_SUPPORTS(cpu_), eve::as<T> const&) noexcept
  {
    using t_t = element_type_t<T>;
    return T(std::numeric_limits<t_t>::lowest());
  }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto valmin_(EVE_SUPPORTS(cpu_), D const&, as<T> const&) noexcept
      requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return valmin(as<T>());
  }
}
}
