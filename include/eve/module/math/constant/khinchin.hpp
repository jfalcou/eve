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
  struct khinchin_t : constant_callable<khinchin_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.57bce6p+1};
        else if constexpr (Opts::contains(lower)) return T{0x1.57bce4p+1};
        else                                      return T{0x1.57bce4p+1};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.57bce423c6d0ep+1};
        else if constexpr (Opts::contains(lower)) return T{0x1.57bce423c6d0dp+1};
        else                                      return T{0x1.57bce423c6d0dp+1};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }

    EVE_CALLABLE_OBJECT(khinchin_t, khinchin_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var khinchin
  //!   @brief Callable object computing the Khinchin constant.
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/math.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::floating_value T >
  //!      T khinchin(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::khinchin(as<T>())` returns a value of type T with all bits set.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/khinchin.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto khinchin = functor<khinchin_t>;
}
