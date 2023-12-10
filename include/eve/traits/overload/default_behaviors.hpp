//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/forward.hpp>

namespace eve
{
  namespace detail
  {
    inline constexpr struct { EVE_FORCEINLINE auto operator()(auto, auto x) const { return x; } } return_2nd = {};
  }

  //====================================================================================================================

  //====================================================================================================================
  template< template<typename> class Func
          , typename OptionsValues
          , typename... Options
          >
  struct callable : decorated_with<OptionsValues, Options...>
  {
    using base = decorated_with<OptionsValues, Options...>;

    template<callable_options O> constexpr auto operator[](O const& opts) const
    {
      return  Func<O>{opts};
    }

    template<typename T> constexpr auto operator[](T t) const requires( requires(base const& b) { b[t];} )
    {
      auto new_traits = base::operator[](t);
      return  Func<decltype(new_traits)>{new_traits};
    }

    // TEMPORARY - Map old decorator to the new ones
    template<typename T> auto operator[](T const& t) const requires(decorator<T>)
    {
      return (*this)[as_option(t)];
    }

    template<typename T> void operator[](T t) const
    // This requires is also TEMPORARY
    requires( !callable_options<T> && !requires(base const& b) { b[t];} && !decorator<T>) =delete;

    template<typename... Args> constexpr auto behavior(auto arch, Args&&... args) const
    {
      return Func<OptionsValues>::deferred_call(arch, EVE_FWD(args)...);
    }

    protected:
    constexpr Func<OptionsValues> const& derived() const { return static_cast<Func<OptionsValues>>(*this); }
  };

  //====================================================================================================================
  //====================================================================================================================
  template< template<typename> class Func
          , typename OptionsValues
          , typename... Options
          >
  struct elementwise_callable : callable<Func, OptionsValues, conditional_option, Options...>
  {
    using func_t =  Func<OptionsValues>;

    struct ignore { template<typename T> operator T() { return T{}; } };

    template<callable_options O, typename T, typename... Ts>
    constexpr auto behavior(auto arch, O const& opts, T x0,  Ts const&... xs) const
    requires(match_option<condition_key,O,ignore_none_>)
    {
      constexpr bool supports_call = requires{ func_t::deferred_call(arch, opts, x0, xs...); };
      constexpr bool any_simd     = (simd_value<T> || ... || simd_value<Ts>);

      // If a deferred call is present, let's call it
      if      constexpr( supports_call )  return func_t::deferred_call(arch, opts, x0, xs...);
      else if constexpr( any_simd )
      {
        // if not, try to slice/aggregate from smaller wides or to map the scalar version
        if constexpr((has_aggregated_abi_v<Ts> || ...)) return aggregate(this->derived(), x0, xs...);
        else                                            return map(this->derived(), x0, xs...);
      }
      else
      {
        static_assert(any_simd, "[EVE] - Missing scalar implementation for current callable");
        return ignore{};
      }
    }

    template<callable_options O, typename T, typename... Ts>
    constexpr auto behavior(auto arch, O const& opts, T x0,  Ts const&... xs) const
    requires(!match_option<condition_key,O,ignore_none_>)
    {
        // Grab the condition and drop it from the callable
        auto cond     = opts[condition_key];
        auto rmv_cond = options{rbr::drop(condition_key, opts)};

        [[maybe_unused]] Func<decltype(rmv_cond)> const f{rmv_cond};

        // Check that the mask and the value are of same kind if simd
        constexpr bool compatible_mask = !(   simd_value<decltype(cond.mask(as(x0)))>
                                          &&  scalar_value<decltype(f(x0,xs...))>
                                          );
        static_assert(compatible_mask, "[EVE] - Scalar values can't be masked by SIMD logicals.");

        // Shush any other cascading errors
        if constexpr(!compatible_mask) return ignore{};
        // Or proceed to find the proper way to handle this masked call
        else
        {
          // Check if func_(arch, cond, opts, ...) exists
          constexpr bool supports_mask  = requires{ func_t::deferred_call(arch, cond, opts, x0, xs...); };

          // If the conditional call is supported, call it
          // Note that as we pruned out ignore_none earlier, the only special cases inside this call is ignore_all
          if      constexpr( supports_mask ) return func_t::deferred_call(arch, cond, opts, x0, xs...);
          else
          {
            // if not, call the non-masked version then mask piecewise
            return detail::mask_op(cond, detail::return_2nd, x0, f(x0,xs...));
          }
        }
      }
  };

  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @struct constant_callable
  //!   @brief CRTP base class giving an EVE's @callable the constant function semantic
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   Constants functions in EVE are built using a very common pattern. Inheriting from eve::constant simplifies the
  //!   implementation of such eve::callable by just requiring your eve::callable type to implement a static `value`
  //!   member function that provides the constant value using two parameters:
  //!     * an eve::options pack containing potential decorators passed to the constant.
  //!     * an eve::as instance to specify the output type.
  //!
  //!   Constant functions in EVE also supports masking, which is directly implemented in eve::constant.
  //!
  //!   @note The deferred overload named in the EVE_CALLABLE_OBJECT macro process is still available if an architecture
  //!   specific implementation of any given constant is required.
  //!
  //!   @tparam Tag Type of current @callable being implemented
  //!
  //!   @groupheader{Example}
  //!   @godbolt{doc/traits/callable_constant.cpp}
  //! @}
  //====================================================================================================================
  template< template<typename> class Func
          , typename OptionsValues
          , typename... Options
          >
  struct constant_callable : callable<Func, OptionsValues, conditional_option, Options...>
  {
    template<typename O, typename T>
    constexpr auto behavior(auto arch, O const& opts, as<T> const& target) const
    {
      using func_t                =  Func<OptionsValues>;
      if constexpr( requires{ func_t::deferred_call(arch, opts, target); } )
      {
        return func_t::deferred_call(arch, opts, target);
      }
      else
      {
        // Compute the raw constant
        auto const constant_value = Func<OptionsValues>::value(target,opts);

        // Apply a mask if any and replace missing values with 0 if no alternative is provided
        if constexpr(match_option<condition_key, O, ignore_none_>) return constant_value;
        else  return detail::mask_op(opts[condition_key], detail::return_2nd, 0, constant_value);
      }
    }
  };
}
