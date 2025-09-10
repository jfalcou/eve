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
#include <eve/module/core/regular/sum_of_prod.hpp>
#include <eve/module/core/regular/two_fma_approx.hpp>
#include <eve/module/core/regular/fma.hpp>

namespace eve
{
  namespace detail
  {
    template < floating_value T> struct wf
    {
      using wf_t = T;

      wf() : avg_(T(0)), n_(1u){}
      wf(T avg)                                 : avg_(avg), n_(1u){}
      wf(T avg,  std::size_t n) : avg_(avg), n_(n){}
      operator T()   const  noexcept {return avg_; };
      std::size_t n()const  noexcept {return n_; };

      auto up() const noexcept { return wf<upgrade_t<T>>(upgrade(avg_), n_); };

      T avg_;
      std::size_t n_;
    };

//    template<floating_value T> wf(T t) -> wf<T>;

    template<typename>    struct is_wf_helper          : public std::false_type{};
    template<typename T>  struct is_wf_helper<wf<T>>   : public std::true_type{};
    template<typename T>  struct is_wf                 : public is_wf_helper<std::remove_cv_t<T>>::type{};
    template<typename T> constexpr auto is_wf_v =  is_wf<T>::value;

    template < typename T> struct internal_welford { using val_t = T;  };
    template < typename T> struct internal_welford<wf<T>> { using val_t = T;  };
    template < typename T> using  internal_welford_t = typename internal_welford<T>::val_t;
  }

  template<typename Options>
  struct mean_value_t : conditional_callable<mean_value_t, Options, upper_option, lower_option, strict_option,
                                                        widen_option, welford_option, kahan_option>
  {

    template<typename... Ts>
    requires( (sizeof...(Ts) !=  0) && eve::same_lanes_or_scalar<detail::internal_welford_t<Ts>...>
                                    && !Options::contains(widen) && !Options::contains(welford))
      EVE_FORCEINLINE common_value_t<detail::internal_welford_t<Ts>...>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<typename... Ts>
    requires(sizeof...(Ts) !=  0 && eve::same_lanes_or_scalar<detail::internal_welford_t<Ts>...>
                                 && Options::contains(widen) && !Options::contains(welford))
    EVE_FORCEINLINE upgrade_t<common_value_t<detail::internal_welford_t<Ts>...>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<typename... Ts>
    requires(sizeof...(Ts) !=  0 && eve::same_lanes_or_scalar<detail::internal_welford_t<Ts>...>
             && !Options::contains(widen) && Options::contains(welford))
      EVE_FORCEINLINE constexpr detail::wf<common_value_t<detail::internal_welford_t<Ts>...>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<typename... Ts>
    requires(sizeof...(Ts) !=  0 && eve::same_lanes_or_scalar<detail::internal_welford_t<Ts>...>
                                 && Options::contains(widen) && Options::contains(welford))
      EVE_FORCEINLINE constexpr detail::wf<upgrade_t<common_value_t<detail::internal_welford_t<Ts>...>>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    EVE_CALLABLE_OBJECT(mean_value_t, mean_value_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var mean_value
//!   @brief `tuple_callable` computing the arithmetic mean of its arguments.
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
//!      constexpr auto mean_value(eve::integral_value auto x, eve::integral_value auto y)             noexcept; // 1
//!      constexpr auto mean_value(eve::floating_value auto x, eve::floating_value auto ... xs)        noexcept; // 2
//!      constexpr auto mean_value(kumi::non_empty_product_type auto const& tup)                       noexcept; // 3
//!
//!      // Lanes masking
//!      constexpr auto mean_value[conditional_expr auto c](/* any of the above overloads */)          noexcept; // 4
//!      constexpr auto mean_value[logical_value auto m](/* any of the above overloads */)             noexcept; // 4
//!
//!      // Semantic options
//!      constexpr auto mean_value[raw] (/* any of the above overloads */)                             noexcept; // 5
//!      constexpr auto mean_value[upper](eve::value auto x, eve::value auto y)                        noexcept; // 6
//!      constexpr auto mean_value[lower](eve::value auto x, eve::value auto y)                        noexcept; // 7
//!      constexpr auto mean_value[upper][strict](eve::value auto x, eve::value auto y)                noexcept; // 6
//!      constexpr auto mean_value[lower][strict](eve::value auto x, eve::value auto y)                noexcept; // 7
//!      constexpr auto mean_value[widen](/* any of the above overloads */)                            noexcept; // 8
//!      constexpr auto mean_value[kahan](/* any of the above overloads */)                            noexcept; // 9
//!      constexpr auto mean_value[welford] (eve::floating_value auto ... x)                           noexcept; // 10
//!      constexpr auto mean_value[welford](size_t n,  eve::floating_value auto prevavg,
//!                                                 eve::floating_value auto ... x)                 noexcept; // 11
//!
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [integral value](@ref eve::integral_value) arguments.
//!     * `xs...`: [floating value](@ref eve::floating_value) arguments.
//!     * `tup`: [non empty tuple](@ref kumi::non_empty_product_type) of arguments.
//!     * `n': number of elements on which the mean was previously computed
//!     * `prvavg': previously computed mean_value of n elements.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!    The value of the arithmetic mean  of the arguments is returned.
//!
//!     1. For two integral parameters half the sum of `x` and `y`. No overflow occurs.
//!        If the sum is odd, the result is a rounded value at a distance guaranteed
//!        to be less than or equal to 0.5 of the mean_value floating value, but may differ
//!        by unity from the truncation given by `(x+y)/2`. Moreover, as some architectures provide
//!        simd intrinsics to perform the operation, the scalar results may differ by one unit from
//!        simd ones which are system dependent.
//!
//!        However the `dowward` (respectively `upward`) options can be used to ensure the result is equivalent to
//!        the integral conversion of `floor((x+y)/2)`, (respectively  `ceil((x+y)/2)`).
//!     2. the arithmetic mean of its arguments. No overflow occurs.
//!     3. the arithmetic mean of the tuple arguments. No overflow occurs.
//!     4. [The operation is performed conditionnaly](@ref conditional)
//!     5. No provision is made to avoid overflows for more than 2 parameters.
//!     6. The mean_value is computed in a 'round toward \f$-\infty\f$ mode. The result is guaranted
//!        to be less or equal to the exact one (except for Nans). Combined with `strict` the option
//!        ensures generally faster computation, but strict inequality.
//!        For integral type entries, these are similar to `ceil((x+y)/2)`, but converted to an integral value.
//!     7. The mean_value is computed in a 'round toward \f$ +\infty\f$ mode. The result is guaranted
//!        to be greater or equal to the exact one (except for Nans). Combined with `strict` the option
//!        ensures generally faster computation, but strict inequality.
//!        For integral type entries,  these are similar to `floor((x+y)/2)` but converted to an integral value.
//!     8. The mean_value is computed in the double sized element type (if available).
//!     9. Kahan like Compensated algorithm for better precision.
//!     10. Uses the Welford incremental algorithm.
//!     11. Uses incremental version of welford from a previously computed mean of n elements stored in
//!         `prevavg` and other new values
//!
//!  @note
//!     1.  with raw option is a spurious overflow can be obtained.
//!     2.  `mean`can be used as an alias to `mean_value`.
//!
//!
//!  @groupheader{External references}
//!   *  [Wikipedia Mean](https://en.wikipedia.org/wiki/Mean)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/mean_value.cpp}
//================================================================================================
  inline constexpr auto mean_value = functor<mean_value_t>;
//================================================================================================
//! @}
//================================================================================================

}

namespace eve::detail
{

  template<value T0, value ... Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto
  mean_value_(EVE_REQUIRES(cpu_), O const & o, T0 a0, Ts const &... args) noexcept
  requires(!O::contains(welford))
  {
    using r_t =  eve::common_value_t<T0, Ts...>;
    using e_t =  eve::element_type_t<r_t>;
    using C = rbr::result::fetch_t<condition_key, O>;
    if constexpr( !std::same_as<C,ignore_none_> )
    {
      auto cond = o[condition_key];
      auto z = mean_value[o.drop(condition_key)](a0, args...);
      return if_else(cond, z, r_t(a0));
    }
    else if constexpr(O::contains(widen))
    {
      return mean_value[o.drop(widen)](upgrade(a0), upgrade(args)...);
    }
    else if constexpr(sizeof...(Ts) == 0)
      return a0;
    else if constexpr(sizeof...(Ts) == 1)
    {
      const auto b = r_t(args...);
      const auto a = r_t(a0);
      if constexpr(integral_value<r_t>)
      {
       if constexpr(O::contains(upper))
          return (a | b) - ((a ^ b) >> 1);   //compute ceil( (a+b)/2 )
        else
          return (a & b) + ((a ^ b) >> 1);   //compute floor( a+b)/2 )  default
      }
      else
      {
        const auto h = eve::half(eve::as<e_t>());
        return fma[o][pedantic](a, h, b*h);
      }
    }
    else
    {
      constexpr auto N = sizeof...(Ts)+1;
      constexpr e_t invn = 1/(e_t(N));
      if constexpr(O::contains(raw))
      {
        if constexpr(integral_value<r_t>)
        {
          return add[o.drop(raw)](a0, args...)/N;
        }
        else
        {
          return eve::mul[o](add[o.drop(raw)](a0, args...), invn);
        }
      }
      else if constexpr(O::contains(kahan))
      {
        auto pair_add = [invn](auto pair0, auto r1){
          auto [r, e0] = pair0;
          auto [s, e1] = eve::two_fma_approx(r1, invn, r);
          return zip(s, e0+e1);
        };
        auto p0 = two_prod(r_t(a0), invn);
        ((p0 = pair_add(p0,args)),...);
        auto [r, e] = p0;
        return r+e;
      }
      else
      {
        r_t that(a0 * invn);
        auto lfma = fma[o];
        auto  next = [invn, lfma](auto avg, auto x) { return lfma(x, invn, avg); };
        ((that = next(that, r_t(args))), ...);
        return that;
      }
    }
  }

  template<typename T0, typename ... Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto
  mean_value_(EVE_REQUIRES(cpu_), O const & o, T0 a0, Ts const &... args) noexcept
  requires(O::contains(welford))
  {
    using r_t =  common_value_t<detail::internal_welford_t<T0>,  detail::internal_welford_t<Ts>...>;
    using C = rbr::result::fetch_t<condition_key, O>;
    if constexpr( !std::same_as<C,ignore_none_> )
    {
      auto cond = o[condition_key];
      auto z = mean_value[o.drop(condition_key)](a0, args...);
      auto n = []<typename T>(T t){
        if constexpr(value<T>) return  std::size_t(1);
        else return t.n_;
      };
      auto avg = []<typename T>(T t){
        if constexpr(value<T>) return  r_t(t);
        else return r_t(t.avg_);
      };

      return eve::detail::wf<r_t>(eve::if_else(cond, avg(z), avg(a0)), n(z)); //eve::if_else(cond, n(z), n(a0)));
    }
    else if constexpr(O::contains(widen))
    {
      auto up_it = [](auto a){
        if constexpr(value<decltype(a)>) return eve::upgrade(a);
        else                             return a.up();
      };
      return mean_value[o.drop(widen)](up_it(a0), up_it(args)...);
    }
    else if constexpr(sizeof...(Ts) == 0)
    {
      if constexpr(value<T0>)
        return a0;
      else
        return a0.avg_;
    }
    else if constexpr(value<T0>)
    {
      auto wa0 = wf<r_t>(a0, 1u);
      return mean_value[o](wa0, args...);
    }
    else
    {
      auto na0 = wf<r_t>(a0.avg_, a0.n_);
      auto doit = [&na0](auto... as){
        auto welfordstep = [&na0](auto a)
        {
          if constexpr(value<decltype(a)>)
          {
            ++na0.n_;
            na0.avg_ += (a-na0.avg_)/na0.n_;
            return na0;
          }
          else
          {
            auto nab = na0.n_+a.n_;
            auto avg = sum_of_prod(r_t(na0.n_), na0.avg_, r_t(a.n_), a.avg_)/nab;
            return  wf<r_t>(avg, nab);
          }
        };
        ((na0 = welfordstep(as)),...);
        return na0;
      };
      return  doit(args...);
    }
  }


//   template<kumi::non_empty_product_type Tup, callable_options O>
//   EVE_FORCEINLINE constexpr auto mean_value_(EVE_REQUIRES(cpu_), O const & o, Tup tup) noexcept
//   requires(!O::contains(welford))
//   {
//     return kumi::apply([o](auto...m){return mean_value[o](m...);}, tup);
//   }

//   template<kumi::non_empty_product_type Tup, callable_options O>
//   EVE_FORCEINLINE constexpr auto mean_value_(EVE_REQUIRES(cpu_), O const & o, std::size_t n, Tup tup) noexcept
//   requires(O::contains(welford))
//   {
//     return kumi::apply([n, o](auto...m){return mean_value[o](n, m...);}, tup);
//   }

}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/mean_value.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/mean_value.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/mean_value.hpp>
#endif
