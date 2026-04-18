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
#include <eve/module/core/detail/tuple_array_utils.hpp>

namespace eve
{
  template<typename Options>
  struct cumsum_t : callable<cumsum_t, Options, widen_option, saturated_option>
  {
    template<typename T>
    using return_type = eve::upgrade_if_t<Options,T>;

    template<value... Ts>
    using result = kumi::result::fill_t<sizeof...(Ts), return_type<eve::common_value_t<Ts...>>>;

    template<product_type T>
    using tuple_result = kumi::result::fill_t< T::size() , return_type<kumi::apply_traits_t<eve::common_value, T>>>;

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

    EVE_CALLABLE_OBJECT(cumsum_t, cumsum_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var cumsum
///!   @brief `callable` converting a pack of values into
//!     a tuple of the cumulative sum of its values.
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
//!      constexpr auto cumsum(eve::value auto ... xs)                noexcept; // 1
//!      constexpr auto cumsum(non_empty_product_type tup)            noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto cumsum[widen](/*any of the above overloads*/) noexcept; // 3
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
//!     1. return a kumi tuple of the values of the cumulated sums of all `xs` converted to
//!         the element type of the common value of the `xs`.
//!     2. same as 1., using the tuple elements.
//!     3. same of 1. or 2., but the computation is made on upgraded elements.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/cumsum.cpp}
//================================================================================================
  inline constexpr auto cumsum = functor<cumsum_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace _
  {

    template <eve::product_type PT, callable_options O>
    EVE_FORCEINLINE constexpr auto cumsum_(EVE_REQUIRES(cpu_), O const & o, PT tup) noexcept
    {
      if constexpr(PT::size() == 0)
        return kumi::make_tuple();
      else if constexpr(O::contains(widen))
        return cumsum[o.drop(widen)](upg(tup));
      else
      {
        auto constexpr SZ = PT::size();
        auto a = to_array(tup);
        for(std::size_t i=1; i < SZ; ++i) a[i] = add[o](a[i-1], a[i]);
        return to_tuple(a);
      }
    }

    template<value T, value ...Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    cumsum_(EVE_REQUIRES(cpu_), O const & o, T t0, Ts... ts) noexcept
    {
      return eve::cumsum[o](kumi::make_tuple(t0, ts...));
    }

  }
}
