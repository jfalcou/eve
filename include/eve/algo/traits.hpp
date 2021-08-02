//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/raberu.hpp>

#include <eve/arch/cardinals.hpp>

#include <type_traits>
#include <utility>

namespace eve::algo
{
  template <typename Settings>
  struct traits : Settings
  {
    template <rbr::keyword_parameter... Options>
    constexpr explicit traits(Options && ... options) : Settings(std::forward<Options>(options) ...) {}

    template <typename... Options>
    constexpr traits(rbr::settings<Options...> const& options) : Settings(options) {}
  };

  template <rbr::keyword_parameter ... Options>
  traits(Options&& ... options) -> traits<decltype(rbr::settings(std::forward<Options>(options) ...))>;

  inline constexpr auto unroll_key = rbr::keyword<struct unroll_key>;

  template<int N>
  inline constexpr auto unroll = (unroll_key = eve::index<N>);

  inline constexpr auto force_cardinal_key = rbr::keyword<struct force_cardinal_key>;

  template <int N>
  inline constexpr auto force_cardinal = (force_cardinal_key = eve::fixed<N>{});

  inline constexpr auto common_with_type_key = rbr::keyword<struct common_with_type_key>;

  template <typename ...Ts>
  inline constexpr auto common_with_types = (common_with_type_key = std::common_type<Ts...>{});

  inline constexpr auto divisible_by_cardinal = rbr::flag<struct divisible_by_cardinal_tag>;

  inline constexpr auto no_aligning = rbr::flag<struct disable_aligning_tag>;


  template <typename Traits>
  constexpr std::ptrdiff_t get_unrolling() {
    return rbr::get_type_t<Traits, unroll_key, eve::fixed<1>>{}();
  }

  template <typename Traits, typename T>
  using forced_cardinal_t = rbr::get_type_t<Traits, force_cardinal_key, eve::expected_cardinal_t<T>>;

  namespace detail
  {
    template <typename Traits, typename I>
    auto iterator_type_impl() {
      if constexpr (!Traits::contains(common_with_type_key)) return typename I::value_type{};
      else
      {
        using Param = typename rbr::get_type_t<Traits, common_with_type_key>::type;
        return std::common_type_t<Param, typename I::value_type>{};
      }
    }
  }

  template <typename Traits, typename I>
  using iteration_type_t = decltype(detail::iterator_type_impl<Traits, I>());

  template <typename User, typename Default>
  constexpr auto default_to(traits<User> const& user, traits<Default> const& defaults)
  {
    using settings_t = decltype(rbr::merge(user, defaults));
    return traits<settings_t>{rbr::merge(user, defaults)};
  }

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

      template <typename Trait>
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
