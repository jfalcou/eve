//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/roundings.hpp>.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/traits/as_integer.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/module/core/regular/roundings.hpp>.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var allbits
  //!
  //! @brief Callable object computing the allbits value.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the allbits constant                              |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template < value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::allbits(as<T>())` returns a value of type T such as each element has all
  //! its bits set to one.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/allbits.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(allbits_, allbits);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr auto allbits_(EVE_SUPPORTS(cpu_), as<T> const &) noexcept
    {
      using t_t           = element_type_t<T>;
      using i_t           = as_integer_t<t_t, unsigned>;
      constexpr auto mask = ~0ULL;

      if constexpr(std::is_integral_v<t_t>) return T(mask);
      else                                  return T(bit_cast(i_t(mask), as<t_t>() ));
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto allbits_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type, to_nearest_type, toward_zero_type > {}))
    {
      return allbits(as<T>());
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto allbits_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      return allbits(as<T>());
    }
  }
}
