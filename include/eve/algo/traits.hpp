//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/concepts/value_type.hpp>

#include <eve/detail/raberu.hpp>

#include <eve/arch/cardinals.hpp>
#include <eve/traits.hpp>

#include <type_traits>
#include <utility>

namespace eve::algo
{
  template <typename Settings>
  struct traits : Settings
  {
    template <rbr::concepts::option... Options>
    constexpr explicit traits(Options && ... options) : Settings(std::forward<Options>(options) ...) {}

    template <typename... Options>
    constexpr traits(rbr::settings<Options...> const& options) : Settings(options) {}
  };

  template <rbr::concepts::option ... Options>
  traits(Options&& ... options) -> traits<decltype(rbr::settings(std::forward<Options>(options) ...))>;

  struct unroll_key_t : rbr::any_keyword<unroll_key_t>
  {
    template<typename Value> constexpr auto operator=(Value const&) const noexcept
    {
      return rbr::option<unroll_key_t,Value>{};
    }
  };
  inline constexpr unroll_key_t unroll_key;
  template<int N> inline constexpr auto unroll = (unroll_key = eve::index<N>);

  struct force_cardinal_key_t : rbr::any_keyword<force_cardinal_key_t>
  {
    template<typename Value> constexpr auto operator=(Value const&) const noexcept
    {
      return rbr::option<force_cardinal_key_t,Value>{};
    }
  };
  inline constexpr force_cardinal_key_t force_cardinal_key;
  template<int N> inline constexpr auto force_cardinal = (force_cardinal_key = eve::fixed<N>{});

  struct force_type_key_t {};
  inline constexpr auto force_type_key = ::rbr::keyword( force_type_key_t{} );
  template <typename T> auto force_type = (force_type_key = std::type_identity<T>{});

  struct common_with_types_key_t {};
  inline constexpr auto common_with_types_key = ::rbr::keyword( common_with_types_key_t{} );

  template <typename ...Ts>
  inline constexpr auto common_with_types = (common_with_types_key = eve::common_type<Ts...>{});

  inline constexpr auto common_type = common_with_types<>;

  struct divisible_by_cardinal_tag {};
  inline constexpr auto divisible_by_cardinal = ::rbr::flag( divisible_by_cardinal_tag{} );

  struct no_aligning_tag {};
  inline constexpr auto no_aligning = ::rbr::flag( no_aligning_tag{} );


  // getters -------------------

  template <typename Traits>
  constexpr std::ptrdiff_t get_unrolling() {
    return rbr::get_type_t<Traits, unroll_key, eve::fixed<1>>{}();
  }

  namespace detail
  {
    template <typename Traits, typename T>
    auto iterator_type_impl() {
      if constexpr (Traits::contains(force_type_key))
      {
        return rbr::get_type_t<Traits, force_type_key>{};
      }
      else if constexpr (Traits::contains(common_with_types_key))
      {
        using Param = typename rbr::get_type_t<Traits, common_with_types_key>::type;
        return eve::common_type<Param, T>{};
      }
      else
      {
        return std::type_identity<T>{};
      }
    }
  }

  template <typename Traits, typename T>
  using iteration_type_t = typename decltype(detail::iterator_type_impl<Traits, T>())::type;

template <typename Traits, typename T>
  using iteration_cardinal_t =
    rbr::get_type_t<Traits, force_cardinal_key,
    eve::expected_cardinal_t<iteration_type_t<Traits, T>>>;


  inline constexpr auto default_to =
     []<typename User, typename Default>(traits<User> const& user, traits<Default> const& defaults)
  {
    using settings_t = decltype(rbr::merge(user, defaults));
    return traits<settings_t>{rbr::merge(user, defaults)};
  };

  template <typename K, typename Traits>
  constexpr auto drop_key(K k, Traits tr)
  {
    using settings_t = decltype(rbr::drop(k, tr));
    return traits<settings_t>(rbr::drop(k, tr));
  }

  template <typename Traits>
  constexpr bool has_type_overrides_v = Traits::contains(force_type_key) || Traits::contains(common_with_types_key);

  inline constexpr algo::traits default_simple_algo_traits{algo::unroll<4>};
  inline constexpr algo::traits no_traits{};

  // Function helper
  namespace detail
  {
    template <template<typename> typename F, typename Traits>
    struct supports_traits
    {
      using traits_type = Traits;
      constexpr Traits get_traits() const { return tr_; }

      constexpr supports_traits() {}
      constexpr explicit supports_traits(Traits tr) : tr_(tr) {}

      template <typename Settings>
      constexpr auto operator[](traits<Settings> tr) const
      {
        auto sum = algo::default_to(tr, tr_);
        using rebound_t = supports_traits<F, decltype(sum)>;
        return F<rebound_t>{rebound_t{sum}};
      }

      template <rbr::concepts::option Trait>
      constexpr auto operator[](Trait one_tr) const
      {
        return operator[](eve::algo::traits(one_tr));
      }

      private:
        Traits tr_;
      };
  }

  template <template<typename> typename F>
  constexpr auto function_with_traits = F<detail::supports_traits<F, decltype(no_traits)>>{};
}
