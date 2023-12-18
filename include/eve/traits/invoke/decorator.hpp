//====================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//====================================================================================================
#pragma once

#include <eve/arch/spec.hpp>
#include <eve/conditional.hpp>
#include <eve/detail/raberu.hpp>
#include <eve/traits/is_logical.hpp>
#include <eve/traits/invoke/protocol.hpp>

#include <ostream>

namespace eve::detail
{
  struct mask_ : rbr::as_keyword<mask_>
  {
    using rbr::as_keyword<mask_>::operator=;
    template<typename T> static constexpr bool check()
    {
      return conditional_expr<std::remove_cvref_t<T>>;
    }

    std::ostream& show(std::ostream& os, auto v) const
    {
      return os << "Mask: " << std::boolalpha << v << std::noboolalpha;
    }
  };

  // This is an internal option to carry around the mask from options
  inline constexpr mask_ mask;
}

namespace eve
{
  template <rbr::concepts::settings Settings>
  struct decorators : Settings
  {
    template <rbr::concepts::option... Options>
    constexpr EVE_FORCEINLINE explicit decorators(Options && ... options) : Settings(EVE_FWD(options) ...) {}

    template <typename... Options>
    constexpr EVE_FORCEINLINE decorators(rbr::settings<Options...> const& options) : Settings(options) {}
  };

  template <rbr::concepts::option ... Options>
  decorators(Options&& ... options) -> decorators<decltype(rbr::settings(EVE_FWD(options) ...))>;

  template <typename... Options>
  decorators(rbr::settings<Options...> const&)  -> decorators<rbr::settings<Options...>>;

  template<typename Tag> struct support_options
  {
    template<typename Settings> struct fn
    {
      using callable_tag_type = void;

      template<typename Options>
      EVE_FORCEINLINE auto operator[](Options&& o) const
      {
        auto new_opts = decorators{rbr::merge(rbr::settings{o}, opts)};
        return fn<decltype(new_opts)>{new_opts};
      }

      EVE_FORCEINLINE auto operator[](conditional_expr auto m) const
      {
        return (*this)[detail::mask = m];
      }

      template<std::same_as<bool> T>
      EVE_FORCEINLINE constexpr auto operator[](T c) const noexcept
      {
        using type = std::conditional_t<std::same_as<bool,T>,std::uint8_t,T>;
        return (*this)[detail::mask = if_(logical<type>(c))];
      }

      template<typename... Args>
      EVE_FORCEINLINE auto operator()(Args&&... x) const
      -> tag_invoke_result<Tag, Settings, Args&&...>
      {
        return eve::tag_invoke(Tag{}, opts, EVE_FWD(x)...);
      }

      template<typename... T>
      unsupported_call<Tag(Settings, T...)> operator()(T&&...x) const noexcept
      requires(!requires(decorators<Settings> const& s)
                { eve::tag_invoke(Tag{}, s, EVE_FWD(x)...); }
              ) = delete;

      Settings opts;
    };

    template<rbr::concepts::option Options>
    EVE_FORCEINLINE auto operator[](Options const& o) const
    {
      return fn<decltype(decorators{o})>{decorators{o}};
    }

    EVE_FORCEINLINE auto operator[](conditional_expr auto m) const
    {
      return (*this)[detail::mask = m];
    }

    template<std::same_as<bool> T>
    EVE_FORCEINLINE constexpr auto operator[](T c) const noexcept
    {
      using type = std::conditional_t<std::same_as<bool,T>,std::uint8_t,T>;
      return (*this)[detail::mask = if_(logical<type>(c))];
    }
  };

}

namespace eve::tags
{
  template<typename S>
  EVE_FORCEINLINE constexpr auto tag_invoke ( deferred_callable auto tag, auto arch
                                            , decorators<S> opts, auto&&... x
                                            )
  noexcept(noexcept(tag.deferred_call(arch, opts, EVE_FWD(x)...)))
          ->  decltype(tag.deferred_call(arch, opts, EVE_FWD(x)...))
  {
    return tag.deferred_call(arch, opts, EVE_FWD(x)...);
  }
}
