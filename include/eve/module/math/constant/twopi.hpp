//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/math.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math
  //! @{
  //! @var twopi
  //!
  //! @brief Callable object computing the \f$2\pi\f$ value.
  //!
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the twopi constant                               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate < floating_value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! `eve::twopi(as<T>())` is semantically equivalent to `8*eve::atan``(T(1))`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/twopi.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(twopi_, twopi);

  namespace detail
  {
    template<floating_value T>
    EVE_FORCEINLINE auto twopi_(EVE_SUPPORTS(cpu_), eve::as<T> const & = {}) noexcept
    {
      using t_t = element_type_t<T>;

      if constexpr(std::is_same_v<t_t, float>)
      {
        return Constant<T, 0X40C90FDBU>();
      }
      else if constexpr(std::is_same_v<t_t, double>)
      {
        return Constant<T, 0X401921FB54442D18ULL>();
      }
    }

    template<typename T, typename D>
    EVE_FORCEINLINE constexpr auto twopi_(EVE_SUPPORTS(cpu_), D const &, as<T> const &) noexcept
    requires(is_one_of<D>(types<upward_type, downward_type> {}))
    {
      using t_t           = element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)
      {
        if constexpr(std::is_same_v<D, upward_type>)
          return eve::twopi(as<T>());
        else
          return Constant<T, 0X40C90FDAU>();
      }
      else
      {
        if constexpr(std::is_same_v<D, downward_type>)
          return eve::twopi(as<T>());
        else
          return Constant<T, 0X401921FB54442D19ULL>();
      }
    }
  }
}
