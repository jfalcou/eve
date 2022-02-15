//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

 #include <eve/module/core/regular/roundings.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <limits>

namespace eve
{
  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var valmin
  //!
  //! @brief Callable object computing the lowest representable value.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the valmin constant                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template < value T > T operator()( as<T> const & t ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::valmin(as<T>())` is semantically equivalent to  `T(std::numeric_limits<element_type_t<T>>::``lowest())`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/valmin.cpp}
  //!
  //! @}
  //================================================================================================

  EVE_MAKE_CALLABLE(valmin_, valmin);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE auto valmin_(EVE_SUPPORTS(cpu_),eve::as<T> const &) noexcept
    {
      using t_t = element_type_t<T>;
      return T(std::numeric_limits<t_t>::lowest());
    }

  template<typename T, typename D>
  EVE_FORCEINLINE constexpr auto valmin_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
  requires(is_one_of<D>(types<upward_type, downward_type> {}))
  {
    return valmin(as<T>());
  }
  }
}
