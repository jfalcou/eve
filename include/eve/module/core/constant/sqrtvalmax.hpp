//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/regular/sqrt.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/floor.hpp>
#include <eve/module/core/constant/constant.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup constant
  //! @{
  //! @var sqrtvalmax
  //!
  //! @brief Callable object computing the greatest value less
  //! than the square root of the greatest value.
  //!
  //! **Required header:** #include <eve/module/core.hpp>
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the sqrtvalmax constant                           |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  tempate < value T > T operator()( as<T> const & t) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`t`:   [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //! **Return value**
  //!
  //! the call `eve::sqrtvalmax(as<T>())` is semantically equivalent to
  //! `T(floor(sqrt(eve::valmax(as<T>())))`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/sqrtvalmax.cpp}
  //!
  //! @}
  //================================================================================================

  EVE_MAKE_CALLABLE(sqrtvalmax_, sqrtvalmax);

  namespace detail
  {
    template<typename T>
    EVE_FORCEINLINE constexpr  auto sqrtvalmax_(EVE_SUPPORTS(cpu_), eve::as<T> const & = {}) noexcept
    {
      using t_t = element_type_t<T>;
      if constexpr(std::is_same_v<t_t, float>)              {
        return Constant<T, 0x5f7FFFFEU>(); }
      else if constexpr(std::is_same_v<t_t, double>)        {
        return Constant<T, 0X5FEFFFFFFFFFFFFFULL>(); }
      else if constexpr(std::is_same_v<t_t, std::uint8_t>)  {
        return T(15); }
      else if constexpr(std::is_same_v<t_t, std::uint16_t>) {
        return T(255); }
      else if constexpr(std::is_same_v<t_t, std::uint32_t>) {
        return T(65535); }
      else if constexpr(std::is_same_v<t_t, std::uint64_t>) {
        return T(4294967296ULL); }
      else if constexpr(std::is_same_v<t_t, std::int8_t>)   {
        return T(11); }
      else if constexpr(std::is_same_v<t_t, std::int16_t>)  {
        return T(181); }
      else if constexpr(std::is_same_v<t_t, std::int32_t>)  {
        return T(46340); }
      else if constexpr(std::is_same_v<t_t, std::int64_t>)  {
        return T(3037000499LL); }
    }
  }
}
