//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>

#include <eve/traits/value_type.hpp>

#include <concepts>
#include <compare>

namespace eve
{
  //================================================================================================
  //! @addtogroup memory
  //! @{
  //!    @struct soa_ptr
  //!    @brief a low level abstruction that is like a tuple of pointers to parallel arrays.
  //!           We think that in code one should use `views::zip_iterator` instead,
  //!           it can do everything `soa_ptr` can and more.
  //!           We are still trying to figure out how/where these abstructions should live.
  //!
  //!   **Required header:** `#include <eve/memory/soa_ptr.hpp>`
  //! @}
  //================================================================================================
  template <typename ... Ptrs>
  struct soa_ptr
  {
    using value_type = kumi::tuple<value_type_t<Ptrs>...>;
    using tuple_type = kumi::tuple<Ptrs...>;

    // product type
    using is_product_type = void;

    template <std::size_t idx, typename Self>
      requires std::same_as<std::remove_cvref_t<Self>, soa_ptr>
    friend decltype(auto) get(Self&& self)
    {
      return get<idx>(EVE_FWD(self).storage);
    }
    // ~product type

    // constructors ================================

    soa_ptr() = default;

    template <typename ...Ptrs1>
      requires (std::convertible_to<Ptrs1, Ptrs> && ...)
    explicit soa_ptr(Ptrs1 ... ptrs) : storage{ptrs...} {}

    template <typename ...Ptrs1>
      requires (std::convertible_to<Ptrs1, Ptrs> && ...)
    explicit soa_ptr(kumi::tuple<Ptrs1...> storage) : storage{storage} {}

    template <typename ...Ptrs1>
      requires (std::convertible_to<Ptrs1, Ptrs> && ...)
    soa_ptr(soa_ptr<Ptrs1...> x)
    {
      storage = kumi::map([]<typename I1, typename I>(I1 from, I) -> I { return from; },
                          x.storage,
                          storage);
    }

    // ordering

    template <typename ...Ptrs1>
      requires (std::totally_ordered_with<Ptrs, Ptrs1> && ...)
    bool operator==(soa_ptr<Ptrs1...> x) const
    {
      return get<0>(storage) == get<0>(x.storage);
    }

    template <typename ...Ptrs1>
      requires (std::totally_ordered_with<Ptrs, Ptrs1> && ...)
    std::strong_ordering operator<=>(soa_ptr<Ptrs1...> x) const
    {
      return get<0>(storage) <=> get<0>(x.storage);
    }

    // airthmetics

    soa_ptr& operator+=(std::ptrdiff_t n)
    {
      kumi::for_each([&](auto& x) { x += n; }, storage);
      return *this;
    }

    friend soa_ptr operator+(soa_ptr x,        std::ptrdiff_t n) { x += n; return x; }
    friend soa_ptr operator+(std::ptrdiff_t n, soa_ptr x       ) { return x + n; }

    soa_ptr& operator-=(std::ptrdiff_t n) { return *this += -n; }

    friend soa_ptr        operator-(soa_ptr x,        std::ptrdiff_t n) { x -= n; return x; }
    friend std::ptrdiff_t operator-(soa_ptr x,        soa_ptr y       ) { return get<0>(x) - get<0>(y); }

    soa_ptr& operator++() { *this += 1; return *this; }
    soa_ptr operator++(int)
    {
      soa_ptr tmp = *this;
      ++(*this);
      return tmp;
    }

    soa_ptr& operator--() { *this -= 1; return *this; }
    soa_ptr operator--(int)
    {
      soa_ptr tmp = *this;
      --(*this);
      return tmp;
    }

    tuple_type storage;
  };

  template <typename ...Ptrs>
  soa_ptr(Ptrs...) -> soa_ptr<Ptrs...>;
}

// tuple opt in
namespace std
{
  template<std::size_t I, typename ...Ptrs>
  struct  tuple_element<I, eve::soa_ptr<Ptrs...>> : tuple_element<I, typename eve::soa_ptr<Ptrs...>::tuple_type>
  {
  };

  template<typename ...Ptrs>
  struct tuple_size<eve::soa_ptr<Ptrs...>> : std::tuple_size<typename eve::soa_ptr<Ptrs...>::tuple_type>
  {
  };
}
// ~tuple opt in
