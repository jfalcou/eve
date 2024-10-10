//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct true_t : constant_callable<true_t, Options, lower_option, upper_option>
  {
    template<typename T>
    static EVE_FORCEINLINE constexpr auto value(as<T>, auto const&)
    {
      return as_logical_t<T>(true);
    }

    template<typename T>
    EVE_FORCEINLINE constexpr as_logical_t<T> operator()(as<T> v) const
    {
      return this->behavior(as<as_logical_t<T>>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(true_t, true__);
  };

  //================================================================================================
  //! @addtogroup core_constants
  //! @{
  //!   @var true_
  //!   @brief Computes the logical true_ value.
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
  //!     template<typename T> constexpr as_logical<T> true_(as<T> x);
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::true_(as<T>{})` returns [elementwise](@ref glossary_elementwise), the true
  //!      logical value.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/constant/true_.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto true_ = functor<true_t>;
}
