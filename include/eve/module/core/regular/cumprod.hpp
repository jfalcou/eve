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
  struct cumprod_t : callable<cumprod_t, Options, widen_option, saturated_option>
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

    EVE_CALLABLE_OBJECT(cumprod_t, cumprod_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var cumprod
//!   @brief `callable` converting a pack of values into
//!     a tuple of the cumulative product of its values.
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
//!      constexpr auto cumprod(eve::value auto ... xs)                noexcept; // 1
//!      constexpr auto cumprod(non_empty_product_type tup)            noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto cumprod[widen](/*any of the above overloads*/) noexcept; // 3
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
//!     1. return a kumi tuple of the values of the cumulated products of all `xs` converted to
//!         the element type of the common value of the `xs`.
//!     2. same as 1., using the tuple elements.
//!     3. same of 1. or 2., but the computation is made on upgraded elements.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/cumprod.cpp}
//================================================================================================
  inline constexpr auto cumprod = functor<cumprod_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace _
  {

    template <eve::product_type PT, callable_options O>
    EVE_FORCEINLINE constexpr auto cumprod_(EVE_REQUIRES(cpu_), O const & o, PT tup) noexcept
    {
      if constexpr(PT::size() == 0)
        return kumi::make_tuple();
      else if constexpr(O::contains(widen))
        return cumprod[o.drop(widen)](upg(tup));
      else
      {
        using e_t = kumi::apply_traits_t<eve::common_value, PT>;
        if constexpr(scalar_value<e_t>)
        {
          using w_t = eve::wide<e_t>;
          if constexpr((PT::size() >= eve::expected_cardinal_v<w_t>) && !O::contains(saturated))
          {

            constexpr auto Last = w_t::size()-1;
            auto head = eve::as_wides(eve::zero(eve::as<e_t>()), tup);
            e_t neutral(1);
            auto sc =  [ neutral, o](auto h){return eve::scan(h, eve::mul[o], neutral); };
            auto xxx = kumi::map(sc, head);
            auto last =  [](auto g){return g.get(Last); };
            auto yyy =  kumi::push_front(kumi::pop_back(kumi::map(last, xxx)), neutral);
            auto r = kumi::map(eve::mul[o], xxx, yyy);
            auto rr = kumi::extract(eve::unfold(r),  kumi::index_t<0>(), kumi::index_t<PT::size()>());;
            return rr;
          }
          else
          {
            return kumi::inclusive_scan_left(eve::mul[o], tup, e_t(1));
          }
        }
        else
        {
          return kumi::inclusive_scan_left(eve::mul[o], tup, e_t(1));
        }
      }
    }

    template<value T, value ...Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    cumprod_(EVE_REQUIRES(cpu_), O const & o, T t0, Ts... ts) noexcept
    {
      return eve::cumprod[o](kumi::make_tuple(t0, ts...));
    }

  }
}
