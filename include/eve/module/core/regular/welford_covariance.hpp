//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/dot.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <iostream>
namespace eve
{

  namespace detail
  {
    template<floating_value T> struct welford_covariance_result
    {
      using type = T;
      operator T()   const noexcept { return covariance; };
      auto upgrade() const noexcept { return welford_covariance_result<upgrade_t<T>>(upgrade(count), count); };

      T averagex         = T(0);
      T averagey         = T(0);
      std::size_t count  = 0;
      T mxy              = T(0);
      T covariance       = T(0);
    };

    template<typename>    struct is_welford_covariance_result_helper                      : public std::false_type{};
    template<typename T>  struct is_welford_covariance_result_helper<welford_covariance_result<T>>   : public std::true_type{};
    template<typename T>  struct is_welford_covariance_result                             : public is_welford_covariance_result_helper<std::remove_cv_t<T>>::type{};
    template<typename T> constexpr auto is_welford_covariance_result_v =  is_welford_covariance_result<T>::value;

    // helper to treat in the same way values and welford_covariance results to compute common_value_t
    // without duplicating code
    template < typename T> struct internal_welford_covariance                               { using type = T;  };
    template < typename T> struct internal_welford_covariance<welford_covariance_result<T>> { using type = T;  };
    template < typename T> using  internal_welford_covariance_t = typename internal_welford_covariance<T>::type;
  }


  template<typename Options>
  struct welford_covariance_t : callable<welford_covariance_t, Options, kahan_option, widen_option, unbiased_option>
  {
//      template<eve::value T0, value T1, value... Ts>
//     requires(eve::same_lanes_or_scalar<T0, T1, Ts...> && !Options::contains(widen))
//       EVE_FORCEINLINE constexpr detail::welford_covariance_result<common_value_t<T0, T1, Ts...>>
//     operator()(T0 t0, T1 t1, Ts...ts) const noexcept
//     {
//       return EVE_DISPATCH_CALL(t0, t1, ts...);
//     }

//     template<eve::value T0, value T1, value... Ts>
//     requires(eve::same_lanes_or_scalar<T0, T1, Ts...> && Options::contains(widen))
//       EVE_FORCEINLINE detail::welford_covariance_result<common_value_t<upgrade_t<T0>, upgrade_t<T1>, upgrade_t<Ts>... >>
//     constexpr operator()(T0 t0, T1 t1, Ts...ts)  const noexcept
//     {
//       return EVE_DISPATCH_CALL(t0, t1, ts...);
//     }

    template<typename T, typename... Ts>
    requires(value<T> && (sizeof...(Ts) !=  0) && !Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_covariance_result<T>
    operator()(T t, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t, ts...);
    }

    template<typename T, typename... Ts>
    requires(value<T> && (sizeof...(Ts) !=  0) && Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_covariance_result<upgrade_t<T>>
    operator()(T t, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t, ts...);
    }

    template<typename T, typename... Ts>
    requires(detail::is_welford_covariance_result_v<T> && !Options::contains(widen))
      EVE_FORCEINLINE constexpr T
    operator()(T t, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t, ts...);
    }

    template<typename T, typename... Ts>
    requires(detail::is_welford_covariance_result_v<T> && Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_covariance_result<upgrade_t<typename T::type>>
    operator()(T t, Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t, ts...);
    }


 //    template<kumi::non_empty_product_type Tup>
//     requires(eve::same_lanes_or_scalar_tuple<Tup> && Options::contains(widen))
//       EVE_FORCEINLINE constexpr
//     detail::welford_covariance_result<upgrade_t<kumi::apply_traits_t<eve::common_value,Tup>>>
//     operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2)
//     { return EVE_DISPATCH_CALL(t); }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup> && !Options::contains(widen))
      EVE_FORCEINLINE constexpr
    detail::welford_covariance_result<kumi::apply_traits_t<eve::common_value,Tup>>
    operator()(Tup const& t) const noexcept requires(kumi::size_v<Tup> >= 2)
    { return EVE_DISPATCH_CALL(t); }

//     template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
//     requires(eve::same_lanes_or_scalar_tuple<Tup1> && eve::same_lanes_or_scalar_tuple<Tup2> && Options::contains(widen))
//       EVE_FORCEINLINE constexpr
//     detail::welford_covariance_result<eve::upgrade_t<kumi::apply_traits_t<eve::common_value, kumi::result::cat_t<Tup1, Tup2>>>>
//     operator()(Tup1 const& t1, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(kumi::cat(t1, t2)); }

//     template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
//     requires(eve::same_lanes_or_scalar_tuple<Tup1> && eve::same_lanes_or_scalar_tuple<Tup2> && !Options::contains(widen))
//       EVE_FORCEINLINE constexpr
//     detail::welford_covariance_result<kumi::apply_traits_t<eve::common_value, kumi::result::cat_t<Tup1, Tup2>>>
//     operator()(Tup1 const& t1, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(kumi::cat(t1, t2)); }

    template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
    requires(eve::same_lanes_or_scalar_tuple<Tup1> && eve::same_lanes_or_scalar_tuple<Tup2> && !Options::contains(widen))
      EVE_FORCEINLINE constexpr
    detail::welford_covariance_result<kumi::apply_traits_t<eve::common_value, Tup1>>
    operator()(Tup1 const& t1, Tup2 const& t2) const noexcept { return EVE_DISPATCH_CALL(kumi::cat(t1, t2)); }

    EVE_CALLABLE_OBJECT(welford_covariance_t, welford_covariance_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var welford_covariance
//!   @brief `elementwise_callable` object computing the elementwise  welford_covariance product
//!     of the vector of the first half parameter by thevector of the last half.
//!
//!   @warning This is not a reduction ! For reals the welford_covariance product is the product
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
//!      constexpr auto welford_covariance(auto value... xs, auto value... ys)        noexcept; // 1
//!      constexpr auto welford_covariance(kumi::tuple xs, kumi::tuple ys)            noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto welford_covariance[unbiased](/*any of the above overloads*/)  noexcept; // 3
//!      constexpr auto welford_covariance[widen]   (/*any of the above overloads*/)  noexcept; // 4
//!      constexpr auto welford_covariance[kahan]   (/*any of the above overloads*/)  noexcept; // 5
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`  :  [value arguments](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!      1. A struct containing The value of the arithmetic means (`averagex` and `averagey` ),
//!         the centered cross moment of order 2 (`mxy`), the (sample) covariance value
//!         normalized by the number of elements involved (`covariance)
//!         and the number of elements (`count`) involved is returned.
//!
//!         This struct is convertble to the covariance floating value. and possess four fields `covariance`,
//!          `averagex`, `averagey`, `mxy` and `count`.
//!
//!      2. The computation and result use the upgraded data type if available
//!      3. with this option the normalisation is done by by the number of elements involved, minus one.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/welford_covariance.cpp}
//================================================================================================
  inline constexpr auto welford_covariance = functor<welford_covariance_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    welford_covariance_(EVE_REQUIRES(cpu_), O const & o, Ts... args) noexcept
    requires( (sizeof...(Ts) > 0)&& (sizeof...(Ts)%2 == 0) && value<eve::common_value_t<Ts...>>)
    {
      constexpr auto siz = sizeof...(Ts)/2;
      using r_t =  eve::common_value_t<Ts...>;
      if constexpr(O::contains(widen))
      {
        auto up_it = [](auto a){
          if constexpr(requires { a.up(); }) return a.up();
          else return eve::upgrade(a);
        };
        return welford_covariance[o.drop(widen)](up_it(args)...);
      }
      else if constexpr(siz == 1)
      {
        return welford_covariance_result<r_t>();
      }
      else
      {
        auto[f,s]   = kumi::split(kumi::make_tuple(args...), kumi::index<siz>);
        auto ncov = welford_covariance_result<r_t>();
        auto doit = [&ncov, &f, &s](){
          auto welford_covariancestep = [&ncov](auto xnyn)
          {
            auto [xn, yn] = xnyn;
            ++ncov.count;
            auto deltay = yn-ncov.averagey;
            ncov.averagey  += deltay/ncov.count;
            ncov.mxy += (xn-ncov.averagex)*(yn-ncov.averagey);
            auto deltax = xn-ncov.averagex;
            ncov.averagex  += deltax/ncov.count;
            return ncov;
          };
          auto r = kumi::map([](auto xs,  auto ys){return eve::zip(xs, ys); }, f, s);
          kumi::apply([welford_covariancestep](auto ... xsys){((welford_covariancestep(xsys)), ...); }, r);
          if constexpr(O::contains(unbiased)) ncov.covariance = ncov.mxy/dec(ncov.count);
          else                                ncov.covariance = ncov.mxy/ncov.count;
          return ncov;
        };
        return  doit();
      }
    }


    template<typename T, typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto welford_covariance_(EVE_REQUIRES(cpu_), O const & o, T t, Ts... args) noexcept
    requires(detail::is_welford_covariance_result_v<T>)
    {
      using r_t =  std::remove_cv_t<typename T::type>;
      if constexpr(O::contains(widen))
      {
        auto up_it = [](auto a){
          if constexpr(requires { a.up(); }) return a.up();
          else return eve::upgrade(a);
        };
        return welford_covariance[o.drop(widen)](up_it(t), up_it(args)...);
      }
      else if constexpr(sizeof...(Ts) == 0)
      {
        return t;
      }
      else
      {
        T ncov = t;
        auto doit = [ & ](){
          auto welford_covariancestep = [&](auto cov)
          {
            auto nab = ncov.count+cov.count;
            std::cout << ncov.count << std::endl;
            std::cout <<  cov.count << std::endl;
            std::cout <<  nab       << std::endl;
            auto avgx = sum_of_prod(r_t(ncov.count), ncov.averagex, r_t(cov.count), cov.averagex)/nab;
            auto avgy = sum_of_prod(r_t(ncov.count), ncov.averagey, r_t(cov.count), cov.averagey)/nab;
            std::cout <<  avgx       << std::endl;
            std::cout <<  avgy       << std::endl;
            auto mxy = cov.mxy+ncov.mxy+((ncov.averagex-cov.averagex)*(ncov.averagey-cov.averagey)*cov.count*ncov.count)/nab;
            ncov = welford_covariance_result(avgx, avgy, nab, mxy);
             return ncov;
          };
          ((ncov = welford_covariancestep(args)),...);
          if constexpr(O::contains(unbiased)) ncov.covariance = ncov.mxy/dec(ncov.count);
          else                                ncov.covariance = ncov.mxy/ncov.count;
          return ncov;
        };
        return  doit();
      }
    }

    template< kumi::non_empty_product_type T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    welford_covariance_(EVE_REQUIRES(cpu_), O const & o, T t) noexcept
    {
      return kumi::apply([o](auto... m){return welford_covariance[o](m...); }, t);
    }
  }
}
