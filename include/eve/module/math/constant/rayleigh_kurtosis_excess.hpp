//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
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
  //! @var rayleigh_kurtosis_excess
  //!
  //! @brief Callable object computing the Rayleigh kurtosis excess value : \f$-(6\pi^2-24\pi+16)/(4-\pi^2)\f$.
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
  //! the rayleigh_kurtosis_excess constant in the chosen type.
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/rayleigh_kurtosis_excess.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(rayleigh_kurtosis_excess_, rayleigh_kurtosis_excess);

  namespace detail
  {
    template<floating_real_value T>
    EVE_FORCEINLINE auto rayleigh_kurtosis_excess_(EVE_SUPPORTS(cpu_), eve::as<T> const & ) noexcept
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)       return T(0x1.f5f162p-3);
      else if constexpr(std::is_same_v<t_t, double>) return T(0x1.f5f161186c5f2p-3);
    }

    template<floating_real_value T, typename D>
    EVE_FORCEINLINE constexpr auto rayleigh_kurtosis_excess_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t =  element_type_t<T>;
      if constexpr(std::is_same_v<D, upward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.f5f162p-3);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.f5f161186c5f2p-3);
      }
      else if constexpr(std::is_same_v<D, downward_type>)
      {
        if constexpr(std::is_same_v<t_t, float>)  return T(0x1.f5f16p-3);
        else if constexpr(std::is_same_v<t_t, double>) return T(0x1.f5f161186c5f1p-3);
      }
    }
  }
}
