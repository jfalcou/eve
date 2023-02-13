//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/algo/algo/concepts/types_to_consider.hpp>

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
    constexpr explicit traits(Options && ... options) : Settings(EVE_FWD(options) ...) {}

    template <typename... Options>
    constexpr traits(rbr::settings<Options...> const& options) : Settings(options) {}
  };

  template <rbr::concepts::option ... Options>
  traits(Options&& ... options) -> traits<decltype(rbr::settings(EVE_FWD(options) ...))>;

  struct unroll_key_t : rbr::as_keyword<unroll_key_t>
  {
    template<typename Value> constexpr auto operator=(Value const&) const noexcept
    {
      return rbr::option<unroll_key_t,Value>{};
    }
  };
  inline constexpr unroll_key_t unroll_key;
  template<int N> inline constexpr auto unroll = (unroll_key = eve::index<N>);

  struct force_cardinal_key_t : rbr::as_keyword<force_cardinal_key_t>
  {
    template<typename Value> constexpr auto operator=(Value const&) const noexcept
    {
      return rbr::option<force_cardinal_key_t,Value>{};
    }
  };
  inline constexpr force_cardinal_key_t force_cardinal_key;
  template<int N> inline constexpr auto force_cardinal = (force_cardinal_key = eve::fixed<N>{});

  struct consider_types_key_t {};
  inline constexpr auto consider_types_key = ::rbr::keyword( consider_types_key_t{} );
  template <typename ...Ts> auto consider_types = ( consider_types_key = kumi::tuple<Ts...>{} );

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

  //================================================================================================
  //! @addtogroup algorithms
  //! @{
  //!   @var no_aligning
  //!
  //!   @brief Traits for disabling alignment handling in algorithm
  //!
  //!   Modify an algorithm semantic to not perform any additional operations to force the
  //!   exploitation of the alignment of processed data.
  //! @}
  //================================================================================================
  inline constexpr auto no_aligning = ::rbr::flag( no_aligning_tag{} );


  //================================================================================================
  //! @addtogroup algorithms
  //! @{
  //!   @var no_unrolling
  //!
  //!   @brief Convinient equivalent to unroll<1>.
  //! @}
  //================================================================================================
  inline constexpr auto no_unrolling = unroll<1>;

  struct expensive_callable_tag {};

  //================================================================================================
  //! @addtogroup algorithms
  //! @{
  //!   @var expensive_callable
  //!
  //!   @brief *NOTE*: equivalent to no_aligning + no_unrolling
  //!          By default eve algorithms will assume that the passed predicates/computation
  //!          are failry simple and will unroll and align data accesses.
  //!
  //!          However, if your callback and/or iterators are very heavy, those transformations
  //!          will not help you. In that case passing `expensive_callable` trait will help.
  //! @}
  //================================================================================================
  inline constexpr auto expensive_callable = ::rbr::flag( expensive_callable_tag{} );

  struct fuse_operations_tag {};
  //================================================================================================
  //! @addtogroup algorithms
  //! @{
  //!   @var fuse_operations
  //!
  //!   @brief Some algorithms (for example `transform_reduce`) can be implemented more efficient
  //!   if you fuse multiple operations provided in a single function.
  //!
  //!   Example: if you want to use `fma` instead of doing `multiply` + `add`.
  //!
  //!   This flag replaces the functions with their more parameter equivalents.
  //! @}
  //================================================================================================
  inline constexpr auto fuse_operations = ::rbr::flag( fuse_operations_tag{} );

  struct allow_frequency_scaling_tag {};
  //================================================================================================
  //! @addtogroup algorithms
  //! @{
  //!   @var allow_frequency_scaling
  //!
  //!   @brief On intel using 64 byte registers requires processor to scale down it's frequency.
  //!          This is only benefitial if you have a very large set of data to process. Otherwise
  //!          it will likely degrade performance not only of the SIMD code but also of the code
  //!          that follows.
  //!
  //!          By default this flag is off.
  //!
  //!    **See also nofs**
  //! @}
  //================================================================================================
  inline constexpr auto allow_frequency_scaling = ::rbr::flag( allow_frequency_scaling_tag{} );

  // getters -------------------

  template <typename Traits>
  constexpr std::ptrdiff_t get_unrolling()
  {
    return rbr::result::fetch_t<(unroll_key | index<1>), Traits>{};
  }

  template <typename Traits>
  using extra_types_to_consider = rbr::result::fetch_t<(consider_types_key | kumi::tuple{}), Traits>;

  template <typename Traits, typename RorI>
  using get_types_to_consider_for =
    kumi::result::cat_t<extra_types_to_consider<Traits>, types_to_consider_for_t<RorI>>;

  namespace detail {
    template <typename Traits, typename RorI>
    using default_cardinal_to_use_t = eve::fixed<
      Traits::contains(allow_frequency_scaling) ?
        expected_cardinal_v<get_types_to_consider_for<Traits, RorI>> :
        nofs_cardinal_v    <get_types_to_consider_for<Traits, RorI>>
    >;
  }

  template <typename Traits, typename RorI>
  using iteration_cardinal_t =
    rbr::result::fetch_t< (force_cardinal_key | detail::default_cardinal_to_use_t<Traits, RorI>{})
                        , Traits
                        >;

  inline constexpr auto default_to =
     []<typename User, typename Default>(traits<User> const& user, traits<Default> const& defaults)
  {
    if constexpr ( User::contains(consider_types_key) &&
                   Default::contains(consider_types_key) )
    {
      auto consider_all_types = kumi::result::cat_t < rbr::result::fetch_t<consider_types_key, User   >
                                                    , rbr::result::fetch_t<consider_types_key, Default>
                                                    >{};
      auto settings = rbr::merge(rbr::merge(rbr::settings(consider_types_key = consider_all_types),
                                            user),
                                 defaults);
      return traits<decltype(settings)>{settings};
    }
    else
    {
      using settings_t = decltype(rbr::merge(user, defaults));
      return traits<settings_t>{rbr::merge(user, defaults)};
    }
  };

  template <typename K, typename Traits>
  EVE_FORCEINLINE constexpr auto drop_key(K k, Traits tr)
  {
    using settings_t = decltype(rbr::drop(k, tr));
    return traits<settings_t>(rbr::drop(k, tr));
  }

  template <bool cond, typename K, typename Traits>
  EVE_FORCEINLINE constexpr auto drop_key_if(K k, Traits tr)
  {
    if constexpr( cond ) return drop_key(k, tr);
    else                 return tr;
  }

  template <typename Traits>
  constexpr bool has_type_overrides_v = Traits::contains(force_type_key) || Traits::contains(common_with_types_key);

  template <typename Traits>
  constexpr bool has_cardinal_overrides_v = Traits::contains(force_cardinal_key);

  template <typename Settings>
  inline constexpr auto process_equivalents(traits<Settings> tr) {
    if constexpr ( Settings::contains(expensive_callable) ) {
      return default_to(traits{no_aligning, unroll<1>}, drop_key(expensive_callable, tr));
    } else {
      return tr;
    }
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
