//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct mhalf_t : constant_callable<mhalf_t, Options, lower_option, upper_option>
  {
    template<floating_value T>
    static EVE_FORCEINLINE constexpr T value(as<T>, auto const&)
    {
      if      constexpr (std::same_as<T, float> ) return T{-0x1p-1};
      else if constexpr (std::same_as<T, double>) return T{-0x1p-1f};
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(mhalf_t, mhalf_);
  };

  //================================================================================================
  //! @addtogroup core_constants
  //! @{
  //!   @var mhalf
  //!   @brief Computes the constant \f$-1/2\f$.
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
  //!     template<eve::floating_value T> constexpr T mhalf(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!    The call `eve::mhalf(as<T>())` is semantically equivalent to `T(-0.5)`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/constant/mhalf.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto mhalf = functor<mhalf_t>;
}
