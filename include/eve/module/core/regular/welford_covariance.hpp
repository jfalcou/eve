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
      auto print(std::string s){
        std::cout << s << std::endl; 
        std::cout << "averagex   " << averagex << std::endl;
        std::cout << "averagey   " << averagey << std::endl;
        std::cout << "mxy        " << mxy      << std::endl;
        std::cout << "covariance " << covariance  << std::endl;
        std::cout << "count      " << count       << std::endl << std::endl;
      };
      
      T averagex         = T(0);
      T averagey         = T(0);
      std::size_t count  = 0;
      T mxy              = T(0);
      T covariance       = T(0);
    };

    template<typename>    struct is_welford_covariance_result_helper                               : public std::false_type{};
    template<typename T>  struct is_welford_covariance_result_helper<welford_covariance_result<T>> : public std::true_type{};
    template<typename T>  struct is_welford_covariance_result                                      : public is_welford_covariance_result_helper<std::remove_cv_t<T>>::type{};
    template<typename T> constexpr auto is_welford_covariance_result_v =  is_welford_covariance_result<T>::value;

    // helper to treat in the same way values and welford_covariance results to compute common_value_t
    // without duplicating code
    template < typename T> struct internal_welford_covariance                               { using type = T;  };
    template < typename T> struct internal_welford_covariance<welford_covariance_result<T>> { using type = T;  };
    template < typename T> using  internal_welford_covariance_t = typename internal_welford_covariance<T>::type;
  }

  template<typename Options>
  struct welford_covariance_t : callable<welford_covariance_t, Options, widen_option, unbiased_option>
  {

    template<typename... Ts>
    requires(value<common_value_t<Ts...>> && (sizeof...(Ts) !=  0) && !Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_covariance_result<common_value_t<detail::internal_welford_covariance_t<Ts>...>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<typename... Ts>
    requires(value<common_value_t<Ts...>> && (sizeof...(Ts) !=  0) && Options::contains(widen))
       EVE_FORCEINLINE constexpr detail::welford_covariance_result<upgrade_t<common_value_t<detail::internal_welford_covariance_t<Ts>...>>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<typename... Ts>
    requires((detail::is_welford_covariance_result_v<Ts > && ...) && !Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_covariance_result<common_value_t<detail::internal_welford_covariance_t<Ts>...>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<typename... Ts>
    requires((detail::is_welford_covariance_result_v<Ts> && ...) && Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_covariance_result<common_value_t<detail::internal_welford_covariance_t<Ts>...>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    EVE_CALLABLE_OBJECT(welford_covariance_t, welford_covariance_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var welford_covariance
//!   @brief `elementwise_callable` object computing the elementwise  welford_covariance product
//!     of the vector of the first half parameter by thevector of the last half.
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
//!      constexpr auto welford_covariance(auto value ... xs, auto value ... ys)      noexcept; // 1
//!      constexpr auto welford_covariance(kumi::tuple xs, kumi::tuple ys)            noexcept; // 2
//!      constexpr auto welford_covariance(auto wcs...)                               noexcept; // 3
//!      constexpr auto welford_covariance(kumi;::tuple wcs)                          noexcept; // 4
//!
//!      // Semantic options
//!      constexpr auto welford_covariance[widen]   (/*any of the above overloads*/)  noexcept; // 5
//!      constexpr auto welford_covariance[unbiased](/*any of the above overloads*/)  noexcept; // 6
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs`, `ys`  : [arguments](@ref eve::value) or tuple of them.
//!     * `wcs`       : [arguments](@ref eve::value) or tuple of them. The arguments must all be results
//!                      of previous `welford_covariance` calls,
//!    **Return value**
//!
//!      1. A struct containing The value of the arithmetic means (`averagex` and `averagey` ),
//!         the centered cross moment of order 2 (`mxy`), the (sample) covariance value
//!         normalized by the number of elements involved (`covariance`)
//!         and the number of elements (`count`) involved is returned.<br/>
//!         This struct is convertible to the covariance floating value. and possess four fields `covariance`,
//!          `averagex`, `averagey`, `mxy` and `count`.
//!      2. The computation is made on the tuples elements.
//!      3. The parameters are composed in a unique covariance struct as if the covariance was  computed on the whole original data set.
//!         Moreover if only one covariance result simd parameter is present, the the lanes individual corariance are grouped in an unique
//!         scalar covariance result, computed from all the datas of all the lanes.
//!      4. same as 3. on the tuple elements.
//!      5. the computation is done in the upgraded element type.
//!      6. with this option the normalisation is done by the number of elements involved, minus one.
//!
//!  @note The Welford algorithm does not provides as much option as the [`covariance`](@ref covariance) function, but is a quite stable algorithm
//!        that have the advantage to allow spliting the computation of the covariance in
//!        multiple calls.  For instance: the call with four tuples:<br/>
//!        &nbsp;   `cwv = welford_corariance(kumi::cat(xs, ys), kumi::cat(ws, zs))`<br/>
//!        is equivalent to the sequence:<br/>
//!        &nbsp;  `cwxs =  welford_covariance(xs, ws);  cwys = welford_covariance(ys, zs)); cwv = welford_covariance(wxs, wys);`<br/>
//!        But the first two instructions can easily be executed in parallel.
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
      std::cout << "iciitte 0" << std::endl;
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
      else
      {
        auto[f,s]   = kumi::split(kumi::make_tuple(args...), kumi::index<siz>);
        std::cout << "sizes " << f.size() <<  " " << s.size() << std::endl;
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
    requires(detail::is_welford_covariance_result_v<T> && (detail::is_welford_covariance_result_v<Ts> && ...))
    {
      std::cout << "iciitte 1" << std::endl;
      using r_t =  common_value_t<detail::internal_welford_covariance_t<T>, detail::internal_welford_covariance_t<Ts>...>;
      if constexpr(O::contains(widen))
      {
        auto up_it = [](auto a){
          if constexpr(requires { a.up(); }) return a.up();
          else return eve::upgrade(a);
        };
        return welford_covariance[o.drop(widen)](up_it(t), up_it(args)...);
      }
//       else
//       {
//         std::cout << "r_t() " << r_t(0)<< std::endl;
//         return detail::welford_covariance_result<r_t>();
//       }
//       else if constexpr(sizeof...(Ts) == 0)
//       {
//         auto scalarize = []<typename U>(U w){
//           using e_t =  element_type_t<typename U::type>;
//           auto getit = [w](auto i){return welford_covariance_result<e_t>(w.averagex.get(i), w.averagey.get(i), w.count, w.mxy.get(i), w.covariance.get(i)); };
//           return kumi::generate<w.averagex.size()>(getit);
//         };
//         if constexpr(simd_value<typename T::type>)
//           return t;
//         else
//           return welford_covariance(scalarize(t));
//       }
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

  }
}
