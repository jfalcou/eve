//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
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

    std::ostream& show(std::ostream& os) const { return os << "Unroll factor"; }
  };

  inline constexpr unroll_key_t unroll_key = {};
  template<int N> inline constexpr auto unroll = (unroll_key = eve::index<N>);

  struct force_cardinal_key_t : rbr::any_keyword<force_cardinal_key_t>
  {
    template<typename Value> constexpr auto operator=(Value const&) const noexcept
    {
      return rbr::option<force_cardinal_key_t,Value>{};
    }

    std::ostream& show(std::ostream& os) const { return os << "Expected Cardinal"; }
  };

  inline constexpr force_cardinal_key_t force_cardinal_key = {};
  template<int N> inline constexpr auto force_cardinal = (force_cardinal_key = eve::fixed<N>{});

  struct common_with_type_key_t {};
  inline constexpr auto common_with_type_key = ::rbr::keyword( common_with_type_key_t{} );

  template <typename ...Ts>
  inline constexpr auto common_with_types = (common_with_type_key = std::common_type<Ts...>{});

  struct divisible_by_cardinal_tag {};
  inline constexpr auto divisible_by_cardinal = ::rbr::flag( divisible_by_cardinal_tag{} );

  struct disable_aligning_tag {};
  inline constexpr auto no_aligning = ::rbr::flag( disable_aligning_tag{} );

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
