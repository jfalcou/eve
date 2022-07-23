//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/decorator/roundings.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>
#include <limits>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_constants
  //! @{
  //!   @var minf
  //!   @brief Computes the -infinity ieee value.
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
  //!      T minf(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::minf(as<T>())` is semantically equivalent to
  //!      `T(-std::numeric_limits<eve::element_type_t<T>>::``infinity())`
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/constant/minf.cpp}
  //! @}
  //================================================================================================
  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var minf
  //!
  //! @brief Callable object computing the negative infinity value.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the minf constant                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template < floating_value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::minf(as<T>())` is semantically equivalent to
  //! `T(-std::numeric_limits<t_t>::``infinity())`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/minf.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(minf_, minf);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr auto minf_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;
      return T(-std::numeric_limits<t_t>::infinity());
    }

    template<floating_value T, typename D>
    EVE_FORCEINLINE constexpr auto minf_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      return minf(as<T>());
    }
  }
}
