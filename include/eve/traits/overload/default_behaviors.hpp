//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/overload.hpp>  // TEMPORARY
#include <eve/forward.hpp>

namespace eve
{
  namespace detail
  {
    inline constexpr struct { EVE_FORCEINLINE auto operator()(auto, auto x) const { return x; } } return_2nd = {};
  }

  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @struct callable
  //!   @brief CRTP base class defining an EVE's @callable.
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/traits/overload.hpp>
  //!   @endcode
  //!
  //!   All EVE @callable use a similar protocol to find and call proper architecture or type specific implementation.
  //!   This protocol includes options checks and management and proper level of error reporting.
  //!   eve::callable is the most general base class for defining such a @callable without having to manually handles
  //!   all these details.
  //!
  //!   @tparam Func          Type of current @callable being implemented.
  //!   @tparam OptionsValues Type of stored options.
  //!   @tparam Options       List of supported option specifications.
  //!
  //!   @groupheader{Example}
  //!   @godbolt{doc/traits/callable_object.cpp}
  //! @}
  //====================================================================================================================
  template< template<typename> class Func
          , typename OptionsValues
          , typename... Options
          >
  struct callable : decorated_with<OptionsValues, Options...>
  {
    using base = decorated_with<OptionsValues, Options...>;

    template<callable_options O> EVE_FORCEINLINE constexpr auto operator[](O const& opts) const
    {
      return  Func<O>{opts};
    }

    template<typename T>
    EVE_FORCEINLINE constexpr auto operator[](T t) const requires( requires(base const& b) { b[t];} )
    {
      auto new_traits = base::operator[](t);
      return  Func<decltype(new_traits)>{new_traits};
    }

    // TEMPORARY - Map old decorator to the new ones
    template<typename T> EVE_FORCEINLINE auto operator[](T const& t) const requires(decorator<T>)
    {
      return (*this)[as_option(t)];
    }

    template<typename T> EVE_FORCEINLINE void operator[](T const& t) const
    // This requires is also TEMPORARY
    requires( !callable_options<T> && !requires(base const& b) { b[t];} && !decorator<T>) =delete;

    template<typename... Args>
    EVE_FORCEINLINE constexpr auto behavior(auto arch, Args&&... args) const
    {
      return Func<OptionsValues>::deferred_call(arch, EVE_FWD(args)...);
    }

    protected:
    EVE_FORCEINLINE constexpr
    Func<OptionsValues> const& derived() const { return static_cast<Func<OptionsValues>const&>(*this); }
  };


  template< template<typename> class Func
          , typename OptionsValues
          , typename... Options
          >
  struct strict_elementwise_callable : callable<Func, OptionsValues, conditional_option, Options...>
  {
    using func_t =  Func<OptionsValues>;

    struct ignore { template<typename T> operator T() { return T{}; } };

    template<callable_options O, typename T, typename... Ts>
    constexpr EVE_FORCEINLINE constexpr auto adapt_call(auto a, O const& o, T x,  Ts const&... xs) const
    {
      constexpr bool has_implementation         = requires{ func_t::deferred_call(a, o, x, xs...); };
      constexpr bool supports_map_no_conversion = requires{ map(this->derived(), x, xs...); };
      constexpr bool any_emulated               = (has_emulated_abi_v<T> || ... || has_emulated_abi_v<Ts>);
      constexpr bool any_aggregated             = (has_aggregated_abi_v<T> || ... || has_aggregated_abi_v<Ts>);

      if      constexpr(any_aggregated)                             return aggregate(this->derived(), x, xs...);
      else if constexpr(any_emulated && supports_map_no_conversion) return map(this->derived(), x, xs...);
      else if constexpr(has_implementation)                         return func_t::deferred_call(a, o, x, xs...);
      else                                                          return ignore{};
    }

    template<callable_options O, typename T, typename... Ts>
    constexpr EVE_FORCEINLINE auto behavior(auto arch, O const& opts, T x0,  Ts const&... xs) const
    requires(match_option<condition_key,O,ignore_none_>)
    {
      constexpr bool supports_call = !std::same_as<ignore, decltype(adapt_call(arch,opts,x0,xs...))>;
      static_assert(supports_call, "[EVE] - Missing implementation for current strict elementwise callable");
      return adapt_call(arch,opts,x0,xs...);
    }

    template<callable_options O, typename T, typename... Ts>
    EVE_FORCEINLINE constexpr auto behavior(auto arch, O const& opts, T x0,  Ts const&... xs) const
    requires(!match_option<condition_key,O,ignore_none_>)
    {
      // Grab the condition and drop it from the callable
      auto[cond, rmv_cond] = opts.extract(condition_key);
      using cond_t =  decltype(cond);
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
        constexpr bool supports_mask  = requires(cond_t c){ func_t::deferred_call(arch, c, opts, x0, xs...); };

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
  //!   @struct elementwise_callable
  //!   @brief CRTP base class giving an EVE's @callable the elementwise function semantic
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/traits/overload.hpp>
  //!   @endcode
  //!
  //!   Elementwise functions in EVE are built using a very common pattern. Inheriting from eve::elementwise_callable
  //!   simplifies the implementation of such @callable by just requiring the definition of the architecture specific
  //!   implementations functions.
  //!
  //!   Elementwise functions in EVE automatically supports masking, aggregated and emulated cases.
  //!   Elementwise @callable are also able to handle mixed SIMD/Scalar calls by performing all the required
  //!   conversions, letting the implementation of the deferred overload named in the EVE_CALLABLE_OBJECT to only
  //!   handle common type cases.
  //!
  //!   @tparam Func          Type of current @callable being implemented.
  //!   @tparam OptionsValues Type of stored options.
  //!   @tparam Options       List of supported option specifications.
  //!
  //!   @see strict_elementwise_callable
  //! @}
  //====================================================================================================================
  template< template<typename> class Func
          , typename OptionsValues
          , typename... Options
          >
  struct elementwise_callable : strict_elementwise_callable<Func, OptionsValues, Options...>
  {
    using base_t = strict_elementwise_callable<Func, OptionsValues, Options...>;
    using ignore = typename base_t::ignore;
    using func_t = typename base_t::func_t;

    template<callable_options O, typename T, typename... Ts>
    constexpr EVE_FORCEINLINE auto adapt_call(auto a, O const& o, T x,  Ts const&... xs) const
    {
      using          cv_t           = common_value_t<T,Ts...>;
      constexpr bool is_callable    = !std::same_as<ignore, decltype(base_t::adapt_call(a,o,x,xs...))>;
      constexpr bool is_convertible = requires{ func_t::deferred_call(a, o, cv_t{x}, cv_t{xs}...); };

      if      constexpr(is_callable   ) return base_t::adapt_call(a,o,x,xs...);
      else if constexpr(is_convertible) return func_t::deferred_call(a, o, cv_t{x}, cv_t{xs}...);
      else                              return ignore{};
    }

    template<callable_options O, typename T, typename... Ts>
    constexpr EVE_FORCEINLINE auto behavior(auto arch, O const& opts, T x0,  Ts const&... xs) const
    requires(match_option<condition_key,O,ignore_none_>)
    {
      constexpr bool supports_call = !std::same_as<ignore, decltype(adapt_call(arch,opts,x0,xs...))>;
      static_assert(supports_call, "[EVE] - Missing implementation for current elementwise callable");
      return adapt_call(arch,opts,x0,xs...);
    }

    template<callable_options O, typename T, typename... Ts>
    EVE_FORCEINLINE constexpr auto behavior(auto arch, O const& opts, T x0,  Ts const&... xs) const
    requires(!match_option<condition_key,O,ignore_none_>)
    {
      return base_t::behavior(arch,opts,x0,xs...);
    }
  };

  //====================================================================================================================
  //====================================================================================================================
  template< template<typename> class Func
          , typename OptionsValues
          , typename... Options
          >
  struct strict_tuple_callable : strict_elementwise_callable<Func, OptionsValues, Options...>
  {
    using base_t = strict_elementwise_callable<Func, OptionsValues, Options...>;

    template<callable_options O, kumi::product_type T>
    constexpr EVE_FORCEINLINE auto behavior(auto arch, O const& opts, T const& x) const
    {
      return kumi::apply( [&](auto... a) { return static_cast<base_t const&>(*this).behavior(arch,opts,a...); }, x);
    }

    template<callable_options O, typename T, typename... Ts>
    constexpr EVE_FORCEINLINE auto behavior(auto arch, O const& opts, T const& x0,  Ts const&... xs) const
    {
      return base_t::behavior(arch,opts,x0,xs...);
    }
  };

  //====================================================================================================================
  //====================================================================================================================
  template< template<typename> class Func
          , typename OptionsValues
          , typename... Options
          >
  struct tuple_callable : elementwise_callable<Func, OptionsValues, Options...>
  {
    using base_t = elementwise_callable<Func, OptionsValues, Options...>;

    template<callable_options O, kumi::product_type T>
    constexpr EVE_FORCEINLINE auto behavior(auto arch, O const& opts, T const& x) const
    {
      return kumi::apply( [&](auto... a) { return static_cast<base_t const&>(*this).behavior(arch,opts,a...); }, x);
    }

    template<callable_options O, typename T, typename... Ts>
    constexpr EVE_FORCEINLINE auto behavior(auto arch, O const& opts, T const& x0,  Ts const&... xs) const
    {
      return base_t::behavior(arch,opts,x0,xs...);
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
  //!   #include <eve/traits/overload.hpp>
  //!   @endcode
  //!
  //!   Constants functions in EVE are built using a very common pattern. Inheriting from eve::constant_callable
  //!   simplifies the implementation of such eve::callable by just requiring your eve::callable type to implement a
  //!   static `value` member function that provides the constant value using two parameters:
  //!     * an eve::options pack containing potential decorators passed to the constant.
  //!     * an eve::as instance to specify the output type.
  //!
  //!   Constant functions in EVE also supports masking, which is directly implemented in eve::constant_callable.
  //!
  //!   @note The deferred overload named in the EVE_CALLABLE_OBJECT macro process is still available if an architecture
  //!   specific implementation of any given constant is required.
  //!
  //!   @tparam Func          Type of current @callable being implemented.
  //!   @tparam OptionsValues Type of stored options.
  //!   @tparam Options       List of supported option specifications.
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
    using constant_callable_tag = void;
    template<typename O, typename T>
    EVE_FORCEINLINE constexpr auto behavior(auto arch, O const& opts, as<T> const& target) const
    {
      using func_t                =  Func<OptionsValues>;
      if constexpr( requires{ func_t::deferred_call(arch, opts, target); } )
      {
        return func_t::deferred_call(arch, opts, target);
      }
      else
      {
        // Compute the raw constant
        auto constant_value = Func<OptionsValues>::value(target,opts);
        using type = decltype(constant_value);

        // Apply a mask if any and replace missing values with 0 if no alternative is provided
        if constexpr(match_option<condition_key, O, ignore_none_>) return constant_value;
        else  return detail::mask_op(opts[condition_key], detail::return_2nd, type{0}, constant_value);
      }
    }
  };
}
