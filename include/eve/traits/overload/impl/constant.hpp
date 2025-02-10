//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/traits/overload/impl/callable.hpp>

namespace eve
{
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
  //!     * an eve::as instance to specify the translated element type of the output.
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
    EVE_FORCEINLINE constexpr auto behavior(auto arch, O const& opts, as<T> target) const
    {
      using func_t                =  Func<OptionsValues>;
      if constexpr( requires{ func_t::deferred_call(arch, opts, target); } )
      {
        return func_t::deferred_call(arch, opts, target);
      }
      else
      {
        // Compute the raw-est type we need to build
        using tgt_type = translate_element_type_t<T>;

        // Compute the raw constant
        auto constant_value = Func<OptionsValues>::value(as<tgt_type>{},opts);
        using type          = decltype(constant_value);
        using out_t         = typename std::conditional_t< std::same_as<type,tgt_type>
                                                         , detail::always<T>
                                                         , as_wide_as<type, T>
                                                         >::type;

        using e_t = eve::element_type_t<out_t>;
        out_t that(static_cast<e_t>(constant_value));

        // Apply a mask if any and replace missing values with 0 if no alternative is provided
        if constexpr(match_option<condition_key, O, ignore_none_>) return that;
        else return detail::mask_op(opts[condition_key], detail::return_2nd, out_t{e_t(0)}, that);
      }
    }
  };
}
