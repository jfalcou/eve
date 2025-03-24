//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/logical.hpp>
#include <eve/concept/options.hpp>
#include <eve/conditional.hpp>

namespace eve
{
  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @struct options
  //!   @brief  Wrapper class around bundle of options passed to eve::callable
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   eve::callable can be decorated with options. eve::options is used internally to gather all those options
  //!   in a @raberu settings instance for further processing.
  //!
  //!   @tparam Settings @raberu settings type to wrap.
  //! @}
  //====================================================================================================================
  template <rbr::concepts::settings Settings = rbr::settings<>>
  struct options : Settings
  {
    constexpr EVE_FORCEINLINE options() : Settings{} {}

    template <rbr::concepts::option... Options>
    constexpr EVE_FORCEINLINE explicit options(Options && ... opts) : Settings(EVE_FWD(opts) ...) {}

    template <typename... Options>
    constexpr EVE_FORCEINLINE explicit options(rbr::settings<Options...> const& opts) : Settings(opts) {}

    template <rbr::concepts::keyword K>
    constexpr EVE_FORCEINLINE auto drop(K const& k) const noexcept
    {
      auto dropped = rbr::drop(k, *this);
      return options<decltype(dropped)>{dropped};
    }

    template <rbr::concepts::keyword K0, rbr::concepts::keyword... Ks>
    constexpr EVE_FORCEINLINE auto drop(K0 const& k0, Ks const&... ks) const noexcept
    {
      auto dropped = rbr::drop(k0, *this);
      return options<decltype(dropped)>{dropped}.drop(ks...);
    }

    template<rbr::concepts::keyword Ks>
    constexpr EVE_FORCEINLINE auto extract(Ks const& kws) const noexcept
    {
      auto    value   = (*this)[kws];
      auto    dropped =  rbr::drop(kws, *this);
      return  kumi::tuple{value, options<decltype(dropped)>{dropped}};
    }
  };

  template <rbr::concepts::option ... Options>
  options(Options&& ... opts) -> options<decltype(rbr::settings(EVE_FWD(opts) ...))>;

  template <typename... Options>
  options(rbr::settings<Options...> const&)  -> options<rbr::settings<Options...>>;

  namespace detail
  {
    template <rbr::concepts::settings S0, rbr::concepts::settings S1>
    constexpr static EVE_FORCEINLINE auto merge_prefer_first(options<S0> const& base, options<S1> const& new_opts) noexcept
    {
      auto res_opts = rbr::merge(new_opts, base);
      return options<decltype(res_opts)>{res_opts};
    }
  }
}


//======================================================================================================================
// Overload's helpers
//======================================================================================================================
namespace eve
{
  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @var functor
  //!   @brief EVE's @callable generator
  //! @}
  //====================================================================================================================
  template<template<typename> class Func>
  inline constexpr auto functor = Func<eve::options<>>{};

  template<auto Func>
  using tag_t = std::remove_cvref_t<decltype(Func)>;

  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @struct decorated_with
  //!   @brief Helper class to aggregate options handlers and states
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   EVE's @callable can be decorated with options. eve::decorated_with is used to list all subset of options a
  //!   given EVE's @callable is allowed to support, how to handle the default values of such subsets and how to store
  //!   said options states.
  //!
  //!   @tparam OptionsValues Options state type
  //!   @tparam Options       List of options specifications to support
  //!
  //!   @groupheader{Example}
  //!
  //!   @subgroupheader{Interaction with eve::conditional}
  //!   @godbolt{doc/traits/callable_supports.cpp}
  //!
  //!   @subgroupheader{Interaction with custom specifications}
  //!   @godbolt{doc/traits/callable_specs.cpp}
  //! @}
  //====================================================================================================================
  template< typename OptionsValues, typename... Options>
  struct  decorated_with
#if !defined(EVE_DOXYGEN_INVOKED)
        : OptionsValues, Options...
#endif
  {
    using Options::process...;

    constexpr EVE_FORCEINLINE decorated_with() {}
    constexpr EVE_FORCEINLINE decorated_with(OptionsValues v) : OptionsValues(std::move(v)) {}

    //==================================================================================================================
    //! @brief Adds an option to current callable
    //!
    //! If the option `o` is supported by one of the specifications `Spec`, build a new @callable that will behave as
    //! an instance of `Tag` except the option `o` is passed inside an eve::options as an additional parameter.
    //!
    //! Does not participate in overload resolution if `o` is not supported by any option specifications.
    //!
    //! @param o Option to add to current's @callable setup
    //! @return A new @callable with the options `o` set.
    //==================================================================================================================
    template<typename O>
    EVE_FORCEINLINE constexpr auto operator[](O o) const
    requires( requires(OptionsValues const& ov) { this->process(ov,o);} )
    {
      return process(static_cast<OptionsValues const&>(*this), o);
    }

    /// Retrieves the current options' state, including processed default
    EVE_FORCEINLINE constexpr auto options() const
    {
      return kumi::fold_left( [&](auto acc, auto const& m) { return m.default_to(acc); }
                            , kumi::tuple<Options...>{}
                            , static_cast<OptionsValues const&>(*this)
                            );
    }
  };
}

//======================================================================================================================
// Helper options for conditional specs
//======================================================================================================================
namespace eve
{
  namespace detail
  {
    //==================================================================================================================
    // Internal option carrying conditional mask or conditional expressions
    //==================================================================================================================
    struct condition_key_t : rbr::as_keyword<condition_key_t>
    {
      using rbr::as_keyword<condition_key_t>::operator=;
    };
  }

  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @var condition_key
  //!   @brief Keyword for retrieving conditionals decorator
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   When a eve::decorated_callable is called with an option provided via eve::conditional, the value of the
  //!   conditional can be retrieved using eve::condition_key
  //!   @see eve::supports
  //! @}
  //====================================================================================================================
  inline constexpr detail::condition_key_t condition_key = {};

  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @struct relative_conditional_option
  //!   @brief Option specification for decoration via relative conditional value and expressions
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   eve::relative_conditional_option is an option specification that can be used when defining a eve::callable
  //!   type to make it supports decoration via  any eve::relative_conditional_expr.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/traits/callable_supports.cpp}
  //! @}
  //====================================================================================================================
  struct relative_conditional_option
  {
    EVE_FORCEINLINE constexpr auto process(auto const& base, eve::relative_conditional_expr auto opt) const
    {
      return merge_prefer_first(base, options{condition_key = opt});
    }

    /// Default settings of eve::relative_conditional is eve::ignore_none
    EVE_FORCEINLINE constexpr auto default_to(auto const& base) const
    {
      return merge_prefer_first(options{condition_key = ignore_none}, base);
    }
  };

  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @struct conditional_option
  //!   @brief Option specification for decoration via conditional value and expressions
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   eve::conditional_option is an option specification that can be used when defining a eve::callable type to make
  //!   it supports decoration via `bool`, eve::logical, any eve::conditional_expr or eve::relative_conditional_expr.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/traits/callable_supports.cpp}
  //! @}
  //====================================================================================================================
  struct conditional_option
  {
    EVE_FORCEINLINE constexpr auto process(auto const& base, rbr::concepts::exactly<condition_key> auto opt) const
    {
      return merge_prefer_first(base, options{opt});
    }

    template<std::same_as<bool> O>
    EVE_FORCEINLINE constexpr auto process(auto const& base, O opt) const
    {
      // Just delay the evaluation of the type by injecting some templates
      using type = std::conditional_t<std::same_as<bool,O>,std::uint8_t,O>;
      return process(base, condition_key = if_(logical<type>(opt)) );
    }

    EVE_FORCEINLINE constexpr auto process(auto const& base, eve::logical_value auto opt) const
    {
      return process(base, condition_key = if_(opt));
    }

    EVE_FORCEINLINE constexpr auto process(auto const& base, eve::conditional_expr auto opt) const
    {
      return process(base, condition_key = opt);
    }

    /// Default settings of eve::conditional is eve::ignore_none
    EVE_FORCEINLINE constexpr auto default_to(auto const& base) const
    {
      return merge_prefer_first(options{condition_key = ignore_none}, base);
    }
  };

  struct relative_conditional_no_alternative_option
  {
    template<relative_conditional_expr Opt>
    EVE_FORCEINLINE constexpr auto process(auto const& base, Opt opt) const
    requires( !Opt::has_alternative )
    {
      return merge_prefer_first(base, options{condition_key = opt});
    }

    EVE_FORCEINLINE constexpr auto default_to(auto const& base) const
    {
      return merge_prefer_first(options{condition_key = ignore_none}, base);
    }
  };
}

namespace eve::detail
{
  // Internal helper for decorator setup
  template<auto Decorator> struct exact_option
  {
    EVE_FORCEINLINE constexpr auto process(auto const& base, exactly<Decorator> auto const& opts) const
    {
      return merge_prefer_first(base, options{opts});
    }

    EVE_FORCEINLINE constexpr auto default_to(auto const& base) const { return base; }
  };
}
