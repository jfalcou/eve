//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math
  //! @{
  //! @var rsqrt_2pi
  //!
  //! @brief Callable object computing the constant \f$1/\sqrt{2\pi}\f$.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the aforementioned constant                              |
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
  //! the rsqrt_2pi constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/rsqrt_2pi.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(rsqrt_2pi_, rsqrt_2pi);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto rsqrt_2pi_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.988454p-2);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.9884533d43651p-2);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto rsqrt_2pi_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.988454p-2);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.9884533d43651p-2);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.988452p-2);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.9884533d4365p-2);
      }
    }
  }
}
