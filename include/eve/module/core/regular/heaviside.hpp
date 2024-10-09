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
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_gtz.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/zero.hpp>

#include <eve/forward.hpp>

namespace eve
{

  template<typename Options>
  struct heaviside_t : elementwise_callable<heaviside_t, Options>
  {
    template<value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const noexcept
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), a);
    }

    template<value T, value U>
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T a, U s) const noexcept
    requires (same_lanes_or_scalar<T, U>)
    {
      return this->behavior(as<common_value_t<T, U>>{}, eve::current_api, this->options(), a, s);
    }

    EVE_CALLABLE_OBJECT(heaviside_t, heaviside_);
  };

  //================================================================================================
  //! @addtogroup core_arithmetic
  //! @{
  //!   @var heaviside
  //!   @brief `elementwise_callable` that return 1 if the input is greater than a threshold else 0.
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
  //!      // Regular overload
  //!      constexpr auto heaviside(value auto x)                                            noexcept; // 1
  //!      constexpr auto heaviside(value auto x, auto s)                                    noexcept; // 2
  //!
  //!      // Lanes masking
  //!      constexpr auto heaviside[conditional_expr auto c](/*any of the above overloads*/) noexcept; // 3
  //!      constexpr auto heaviside[logical_value auto m](/*any of the above overloads*/)    noexcept; // 3
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`: value.
  //!     * `s`: shift.
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!    **Return value**
  //!        1. Each [element](@ref glossary_elementwise)  of the result contains:
  //!           * `0`, if `x` is less or equal to zero.
  //!           * `1` otherwise.
  //!        2. Each [element](@ref glossary_elementwise)  of the result contains:
  //!           * `0`, if `x` is less or equal to `s` (default to zero).
  //!           * `1` otherwise.
  //!        3. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!  @groupheader{External references}
  //!   *  [wikipedia](https://en.wikipedia.org/wiki/Indicator_function)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/heaviside.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto heaviside = functor<heaviside_t>;

  namespace detail
  {

    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr auto heaviside_(EVE_REQUIRES(cpu_), O const&, T a) noexcept
    {
      if constexpr (scalar_value<T>)
        return a > 0;
      else
        return if_else(is_gtz(a), one(as{a}), zero);
    }

    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr auto heaviside_(EVE_REQUIRES(cpu_), O const&, T a, T s) noexcept
    {
      if constexpr (scalar_value<T>)
        return a > s;
      else
        return if_else(a > s, one(as{a}), zero);
    }
  }
}
