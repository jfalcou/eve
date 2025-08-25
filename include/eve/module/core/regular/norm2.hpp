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
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/sqr.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/two_fma_approx.hpp>

namespace eve
{
  template<typename Options>
  struct norm2_t : tuple_callable<norm2_t, Options, pedantic_option, saturated_option, lower_option,
                                upper_option, strict_option, kahan_option>
  {
    template<value T0, eve::value T1, value... Ts>
    requires(eve::same_lanes_or_scalar<T0, T1, Ts...>)
    EVE_FORCEINLINE constexpr common_value_t<T0,T1, Ts...> operator()(T0 t0, T1 t1, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1, ts...);
    }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>)
    EVE_FORCEINLINE constexpr
    kumi::apply_traits_t<eve::common_value,Tup>
    operator()(Tup const& t) const noexcept { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(norm2_t, norm2_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var norm2
//!   @brief `tuple_callable` object computing the norm2 norm (\f$l_1\f$)  of its arguments.
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
//!      constexpr auto norm2(value auto x, value auto ... xs)                          noexcept; // 1
//!      constexpr auto norm2(kumi::non_empty_product_type auto const& tup)             noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto norm2[conditional_expr auto c](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto norm2[logical_value auto m](/*any of the above overloads*/)     noexcept; // 3
//!
//!      // Semantic options
//!      constexpr auto norm2[saturated](/*any of the above overloads*/)                noexcept; // 4
//!      constexpr auto norm2[pedantic](/*any of the above overloads*/)                 noexcept; // 5
//!      constexpr auto norm2[kahan](/*any of the above overloads*/)                    noexcept; // 6
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs ...` : [real](@ref eve::value) arguments.
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!       1. The value of the sum of the absolute value of the arguments is returned.
//!       2. equivalent to the call on the elements of the tuple.
//!       3. [The operation is performed conditionnaly](@ref conditional)
//!       4. internally uses `saturated` options.
//!       5. returns \f$\infty\f$ as soon as one of its parameter is infinite, regardless of possible `Nan` values.
//!       6. uses kahan compensated algorihtm for better accuracy.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/norm2.cpp}
//================================================================================================
  inline constexpr auto norm2 = functor<norm2_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    norm2_(EVE_REQUIRES(cpu_), O const &, T a0) noexcept
    {
      if constexpr (!O::contains(saturated) || floating_value<T>)
        return eve::sqr(a0);
      else
        return eve::sqr[saturated](a0);
    }

    template<typename T0, typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T0, Ts...>
    norm2_(EVE_REQUIRES(cpu_), O const & o , T0 a0, Ts... args) noexcept
    requires(sizeof...(Ts) != 0)
    {
      using r_t = common_value_t<T0, Ts...>;
      if constexpr(O::contains(kahan))
      {
//        std::cout << "icitte0" << std::endl;
        auto pair_sqr_add = [](auto pair0, auto r1){
          auto [r0, e0] = pair0;
          //        std::cout << "r0 " << r0 <<  "  r& " << r1 << std::endl;
          auto [s, e1] = eve::two_fma_approx(r1, r1, r0);
          return zip(s, e0+e1);
        };
        auto p0   = two_prod(a0, a0);
        ((p0 = pair_sqr_add(p0,args)),...);
        auto [r, e] = p0;
        auto res = r+ e;
        return res;
      }
      else
      {
        auto l_sqr = [](){
          if constexpr(integral_value<r_t> && O::contains(saturated))
          return eve::sqr[saturated];
          else
            return eve::sqr;
        };
        r_t r = eve::add[o](l_sqr()(r_t(a0)), l_sqr()(r_t(args))...);
        if constexpr(O::contains(pedantic))
        {
          auto inf_found = is_infinite(r_t(a0));
          inf_found =  (inf_found || ... || is_infinite(r_t(args)));
          return if_else(inf_found, inf(as(r)), r);
        }
        else
          return r;
      }
    }
  }
}
