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
#include <eve/traits/updown.hpp>

namespace eve
{
  template<typename Options>
  struct deploy_t : tuple_callable<deploy_t, Options, widen_option>
  {

    template<typename T, typename ...Ts>  static constexpr auto len(){return ((cardinal_v<Ts>) + ... + 0 )+cardinal_v<T>; };
    template<value T, value... Ts>
    struct result : kumi::result::iota<len<T, Ts...>(), eve::element_type_t<eve::upgrade_if_t<Options, eve::common_value_t<T, Ts...>>>> {};

    template<value T, value ...Ts>
    EVE_FORCEINLINE constexpr result<T, Ts...>::type
    operator()(T t, Ts ... ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t, ts...);
    }

    EVE_CALLABLE_OBJECT(deploy_t, deploy_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var deploy
//!   @brief `tuple_callable` utility to convert a pack of values into a tuple of scalar values.
//!
//!   @groupheader{Header file}
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
//!      // Regular overloads
//!      constexpr auto deploy(eve::value auto ... xs)                noexcept; // 1
//!
//!      // Semantic options
//!      constexpr auto deploy[widen](/*any of the above overloads*/) noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [integral value](@ref eve::integral_value) arguments.
//!     * `xs...`: [floating value](@ref eve::floating_value) arguments.
//!
//!    **Return value**
//!
//!     1. return a kumi tuple of scalar values of the elements of all `xs` converted to the element type of the common value of the `xs`.
//!     2. same of 1. or 2. but upgrading the elements of the result.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia Mean](https://en.wikipedia.org/wiki/Mean)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/deploy.cpp}
//================================================================================================
  inline constexpr auto deploy = functor<deploy_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {

    template<typename T, typename ...Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    deploy_(EVE_REQUIRES(cpu_), O const &, T x, Ts... xs) noexcept
    {
      auto constexpr S = sizeof...(Ts);
      using r_t = eve::common_value_t<element_type_t<T>, element_type_t<Ts>...>;
      if constexpr(S == 0)
      {
        if constexpr(eve::simd_value<T>)
        {
          constexpr auto N = eve::cardinal_v<T>;
          auto g = [x](auto i){ return x.get(i); };
          return kumi::generate<N>(g) ;
        }
        else
        {
          return kumi::make_tuple(x);
        }
      }
      else
      {
        auto cvt =  []<typename Y>(Y y){
          if constexpr(scalar_value<Y>)  return r_t(y);
          else return y;
        };
        return kumi::cat(deploy(cvt(x)), deploy(cvt(xs)...));
      }
    }
  }
}
