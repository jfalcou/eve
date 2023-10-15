//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/logical.hpp>
#include <eve/detail/raberu.hpp>
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
  template <rbr::concepts::settings Settings>
  struct options : Settings
  {
    template <rbr::concepts::option... Options>
    constexpr EVE_FORCEINLINE explicit options(Options && ... opts) : Settings(EVE_FWD(opts) ...) {}

    template <typename... Options>
    constexpr EVE_FORCEINLINE explicit options(rbr::settings<Options...> const& opts) : Settings(opts) {}
  };

  template <rbr::concepts::option ... Options>
  options(Options&& ... opts) -> options<decltype(rbr::settings(EVE_FWD(opts) ...))>;

  template <typename... Options>
  options(rbr::settings<Options...> const&)  -> options<rbr::settings<Options...>>;
}

//======================================================================================================================
// Overload's helpers
//======================================================================================================================
namespace eve::detail
{
  //====================================================================================================================
  //  Delay the access to defaults() to after the proper operator() has been selected.
  //  Also returns an empty set of options by default
  //====================================================================================================================
  template<typename T, typename...> EVE_FORCEINLINE constexpr auto defaults()
  {
    if constexpr(requires { T::defaults(); }) return T::defaults();
    else                                      return options{};
  }

  //====================================================================================================================
  // Internal concept checking if an option is supported by a specification
  //====================================================================================================================
  template<typename Spec, typename O>
  concept supports_option = requires(Spec sp, O const& o) { { sp[o] }; };

  //====================================================================================================================
  // Internal concept checking if an option is supported by a any specification in a given subset
  //====================================================================================================================
  template<typename O, typename... Specs>
  concept is_supported = (supports_option<Specs,O> || ... );

  //====================================================================================================================
  // Internal option carrying conditional mask or conditional expressions
  //====================================================================================================================
  struct condition_key_t : rbr::as_keyword<condition_key_t>
  {
    using rbr::as_keyword<condition_key_t>::operator=;
    template<typename T> static constexpr bool check()
    {
      return conditional_expr<std::remove_cvref_t<T>> || logical_value<std::remove_cvref_t<T>>;
    }
  };
}

namespace eve
{
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
}

namespace eve::detail
{
  //====================================================================================================================
  // Intermediate type for handling chains of option like in func[opt1 = y][opt2 = x][ignore](...)
  //====================================================================================================================
  template<typename Tag, typename Settings, typename... Specs>
  struct decorated_fn : Specs...
  {
    protected:
    using Specs::process_option...;

    public:
    using callable_tag_type = void;

    explicit decorated_fn(Settings s) : opts(std::move(s)) {}

    template<typename O>
    EVE_FORCEINLINE auto operator[](O const& o) const
    -> decltype ( decorated_fn<Tag,decltype(process_option(std::declval<Settings>(), o)),Specs...>
                  {process_option(std::declval<Settings>(), o)}
                )
    {
      auto new_opts = process_option(opts, o);
      return decorated_fn<Tag,decltype(new_opts),Specs...>{new_opts};
    }

    // Behave as a callable but pass the current bundle of options to the deferred_call handler
    template<typename... Args>
    EVE_FORCEINLINE constexpr auto operator()(Args&&... args) const
    -> decltype(std::declval<Tag>().call(std::declval<Args>()...))
    {
      return Tag::deferred_call(eve::current_api, opts, EVE_FWD(args)...);
    }

    Settings opts;
  };
}

namespace eve
{
  //====================================================================================================================
  //! @addtogroup extensions
  //! @{
  //!   @struct supports
  //!   @brief Helper class to aggregate options handlers
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   eve::callable can be decorated with options. eve::supports is used to list all subset of options a given EVE
  //!   @callable is allowed to support and to handle the default values of such subsets.
  //!
  //!   @tparam Tag Type of current @callable being implemented
  //!   @tparam Specs List of options specifications to support
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
  template<typename Tag, typename... Specs>
  struct supports : Specs...
  {
    protected:
    using Specs::process_option...;

    public:
    // Aggregate all defaults from all Specs
    EVE_FORCEINLINE static constexpr auto defaults() noexcept
    {
      return  kumi::fold_left ( [](auto const& acc, auto const& e) { return options{rbr::merge(e,acc)}; }
                              , kumi::make_tuple(Specs::defaults()...)
                              );
    }

    //==================================================================================================================
    //! @brief Adds an option to current callable
    //!
    //! If the option `o` is supported by one of the specifications `Spec`, build a new @callable that will behave as
    //! an instance of `Tag` except the option `o` is passed inside an eve::options as an additional parameter.
    //!
    //! Does not participate in overload resolution if `o` is not support by any option specifications.
    //!
    //! @param o Option to add to current's @callable setup
    //! @return A eve::decorated_callable behaving as `Tag` but with the options `o` set.
    //==================================================================================================================
    template<typename O>
    EVE_FORCEINLINE auto operator[](O const& o) const
    -> decltype( detail::decorated_fn<Tag,decltype(process_option(defaults(), o)),Specs...>(process_option(defaults(), o)) )
    {
      auto opts = process_option(defaults(), o);
      return detail::decorated_fn<Tag,decltype(opts),Specs...>(opts);
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
    auto process_option(auto const& base, rbr::concepts::exactly<condition_key> auto opt) const
    {
      return options{rbr::merge(options{opt}, base)};
    }

    template<std::same_as<bool> O>
    auto process_option(auto const& base, O opt) const
    {
      // Just delay the evaluation of the type by injecting some templates
      using type = std::conditional_t<std::same_as<bool,O>,std::uint8_t,O>;
      return process_option(base, condition_key = if_(logical<type>(opt)) );
    }

    auto process_option(auto const& base, eve::logical_value auto opt) const
    {
      return process_option(base, condition_key = opt);
    }

    auto process_option(auto const& base, eve::conditional_expr auto opt) const
    {
      return process_option(base, condition_key = opt);
    }

    /// Default settings of eve::conditional is eve::ignore_none
    EVE_FORCEINLINE static constexpr auto defaults() noexcept { return options{condition_key = ignore_none};  }
  };

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
    auto process_option(auto const& base, eve::relative_conditional_expr auto opt) const
    {
      return options{rbr::merge(options{condition_key = opt}, base)};
    }

    /// Default settings of eve::relative_conditional is eve::ignore_none
    EVE_FORCEINLINE static constexpr auto defaults() noexcept { return options{condition_key = ignore_none};  }
  };

  /// Checks if the type associated to a given Keyword in a Option pack is equal to Type
  template<auto Keyword, typename Opts, typename Type>
  inline constexpr bool option_type_is =  std::same_as<Type, rbr::result::fetch_t<Keyword,Opts>>;
}