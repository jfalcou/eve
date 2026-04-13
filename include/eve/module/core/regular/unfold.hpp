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
  struct unfold_t : callable<unfold_t, Options, widen_option>
  {
    template<typename ...Ts>
    struct cardinal_sum
    {
      static constexpr auto value = ((cardinal_v<Ts>) + ... + 0 );
      using type = std::integral_constant<std::size_t,value>;
    };

    template<typename T>
    using return_type = eve::element_type_t<eve::upgrade_if_t<Options,T>>;

    template<value... Ts>
    using result = kumi::result::fill_t<
      cardinal_sum<Ts...>::value
      , return_type<eve::common_value_t<Ts...>>>;

    template<product_type T>
    using tuple_result = kumi::result::fill_t<
      kumi::apply_traits_t<cardinal_sum, T>::value
      , return_type<kumi::apply_traits_t<eve::common_value, T>>>;

    template<value T, value ...Ts>
    EVE_FORCEINLINE constexpr result<T, Ts...>
    operator()(T t, Ts ... ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t, ts...);
    }

    template<non_empty_product_type T>
    EVE_FORCEINLINE constexpr tuple_result<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(unfold_t, unfold_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var unfold
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
//!      constexpr auto unfold(eve::value auto ... xs)                noexcept; // 1
//!      constexpr auto unfold(non_empty_product_type tup)            noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto unfold[widen](/*any of the above overloads*/) noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [value](@ref eve::value) arguments.
//!     * `xs...`: [values](@ref eve::value) arguments.
//!     * `tup`: kumi tuple of values.
//!
//!    **Return value**
//!
//!     1. return a kumi tuple of scalar values of the elements of all `xs` converted to the element type of the common value of the `xs`.
//!     2. same as 1., using the tuple elements.
//!     3. same of 1. or 2., but upgrading the elements of the result.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/unfold.cpp}
//================================================================================================
  inline constexpr auto unfold = functor<unfold_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {

    template<typename T, typename ...Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    unfold_(EVE_REQUIRES(cpu_), O const &, T x, Ts... xs) noexcept
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
        return kumi::cat(unfold(cvt(x)), unfold(cvt(xs)...));
      }
    }

    template<non_empty_product_type T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    unfold_(EVE_REQUIRES(cpu_), O const &, T tup) noexcept
    {
      return kumi::apply([](auto ... ts){return unfold(ts...); }, tup);
    }

  }
}
