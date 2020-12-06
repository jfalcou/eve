//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/arch/spec.hpp>
#include <eve/concept/range.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/detail/function/combine.hpp>
#include <eve/detail/function/compounds.hpp>
#include <eve/detail/function/fill.hpp>
#include <eve/detail/function/load.hpp>
#include <eve/detail/function/lookup.hpp>
#include <eve/detail/function/make.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/detail/function/subscript.hpp>

#include <type_traits>
#include <iosfwd>

namespace eve
{
  //================================================================================================
  // Wrapper for SIMD registers holding arithmetic types with compile-time size
  //================================================================================================
  template<typename Type, typename Size, typename ABI>
  struct EVE_MAY_ALIAS wide
  {
    private:
    //==============================================================================================
    // INTERNAL - Compute the type used as target for detail implementation
    //==============================================================================================
    template<typename P, typename A> struct tgt_      { using type = typename P::value_type;    };
    template<typename P> struct tgt_<P, emulated_>    { using type = typename P::storage_type;  };
    template<typename P> struct tgt_<P, aggregated_>  { using type = P;                         };

    public:
    using storage_type  = as_register_t<Type, Size, ABI>;
    using cardinal_type = Size;
    using abi_type      = ABI;
    using value_type    = Type;
    using size_type     = std::ptrdiff_t;
    using target_type   = typename tgt_<wide, abi_type>::type;

    template<typename T, typename N = expected_cardinal_t<T>>
    using rebind = wide<T,N>;

    static constexpr size_type  static_size       = Size::value;
    static constexpr size_type  static_alignment  = std::min( sizeof(Type)*Size::value
                                                            , alignof(storage_type)
                                                            );

    //==============================================================================================
    // Default constructor
    //==============================================================================================
    EVE_FORCEINLINE wide() noexcept {}

    //==============================================================================================
    // Constructs a wide from a native SIMD storage
    //==============================================================================================
    EVE_FORCEINLINE wide(storage_type const &r) noexcept : data_(r) {}

    //==============================================================================================
    // Constructs a wide from a Range
    //==============================================================================================
    template<std::input_iterator Iterator>
    EVE_FORCEINLINE explicit wide(Iterator b, Iterator e) noexcept
                  : data_(detail::load(eve::as_<wide>{}, abi_type{}, b, e))
    {
    }

    template<detail::range Range>
    EVE_FORCEINLINE explicit wide(Range &&r) noexcept
          requires( !std::same_as<storage_type, Range> )
        : wide(std::begin(std::forward<Range>(r)), std::end(std::forward<Range>(r)))
    {
    }

    //==============================================================================================
    // Constructs a wide from a pointer or an aligned pointer
    //==============================================================================================
    template<scalar_pointer Ptr>
    EVE_FORCEINLINE explicit wide(Ptr ptr) noexcept
    requires( std::is_pointer_v<Ptr> || pointer_alignment_v<Ptr> >= static_alignment )
        : data_(detail::load(eve::as_<wide>{}, abi_type{}, ptr))
    {
    }

    //==============================================================================================
    // Constructs a wide from a single value
    //==============================================================================================
    template<typename T>
    EVE_FORCEINLINE explicit  wide(T const &v)  noexcept requires( std::convertible_to<T, Type> )
                            : data_(detail::make(eve::as_<target_type>{}, abi_type{}, v))
    {
    }

    //==============================================================================================
    // Constructs a wide from a sequence of values
    //==============================================================================================
    template<typename T0, typename T1, typename... Ts>
    EVE_FORCEINLINE wide(T0 const &v0, T1 const &v1, Ts const &... vs) noexcept
          requires(     std::convertible_to<T0,Type> && std::convertible_to<T0,Type>
                    &&  (... && std::convertible_to<Ts,Type>)
                    &&  (static_size == 2 + sizeof...(Ts))
                  )
        : data_(detail::make(eve::as_<target_type>{}, abi_type{}, v0, v1, vs...))
    {
    }

    //==============================================================================================
    // Constructs a wide with a generator function
    //==============================================================================================
    template<typename Generator>
    EVE_FORCEINLINE wide(Generator &&g) noexcept
                    requires( std::invocable<Generator,size_type,size_type>)
                  : data_( detail::fill(eve::as_<wide>{}, abi_type{}, std::forward<Generator>(g)) )
    {}

    //==============================================================================================
    // Constructs a wide from a pair of sub-wide
    //==============================================================================================
    template<typename halfSize>
    EVE_FORCEINLINE wide( wide<Type, halfSize> const &l
                        , wide<Type, halfSize> const &h
                        ) noexcept
                    requires( static_size == 2 * halfSize::value )
                  : data_(detail::combine(EVE_CURRENT_API{}, l, h))
    {
    }

    //==============================================================================================
    // Assign a single value to a wide
    //==============================================================================================
    EVE_FORCEINLINE wide &operator=(Type v) noexcept
    {
      wide that(v);
      swap(that);
      return *this;
    }

    //==============================================================================================
    // Raw storage access
    //==============================================================================================
    EVE_FORCEINLINE storage_type const& storage() const & noexcept { return data_; }
    EVE_FORCEINLINE storage_type &      storage() &       noexcept { return data_; }
    EVE_FORCEINLINE storage_type        storage() &&      noexcept { return data_; }

    EVE_FORCEINLINE operator storage_type const& () const &  noexcept { return data_; }
    EVE_FORCEINLINE operator storage_type&       () &        noexcept { return data_; }
    EVE_FORCEINLINE operator storage_type        () &&       noexcept { return data_; }

    EVE_FORCEINLINE auto  begin() noexcept
    {
      return detail::at_begin(EVE_CURRENT_API{}, as_<wide>{}, data_);
    }

    EVE_FORCEINLINE auto  begin() const  noexcept
    {
      return detail::at_begin(EVE_CURRENT_API{}, as_<wide>{}, data_);
    }

    EVE_FORCEINLINE auto  end()        noexcept { return begin() + static_size; }
    EVE_FORCEINLINE auto  end() const  noexcept { return begin() + static_size; }

    //==============================================================================================
    // alignment interface
    //==============================================================================================
    static EVE_FORCEINLINE constexpr size_type alignment() noexcept
    {
      return static_alignment;
    }

    //==============================================================================================
    // array-like interface
    //==============================================================================================
    static EVE_FORCEINLINE constexpr size_type size()     noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr size_type max_size() noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr bool      empty()    noexcept { return false; }

    //==============================================================================================
    // slice interface
    //==============================================================================================
    EVE_FORCEINLINE auto slice() const { return detail::slice(*this); }

    template<typename Slice>
    EVE_FORCEINLINE auto slice(Slice const &s) const
    {
      return detail::slice(*this, s);
    }

    //==============================================================================================
    // swap
    //==============================================================================================
    EVE_FORCEINLINE void swap(wide &rhs) noexcept
    {
      using std::swap;
      swap(data_, rhs.data_);
    }

    //==============================================================================================
    // Dynamic index lookup
    //==============================================================================================
    template<typename Index>
    EVE_FORCEINLINE wide operator[](wide<Index,Size> const& idx) noexcept
    {
      return lookup(*this,idx);
    }

    //==============================================================================================
    // elementwise access
    //==============================================================================================
    EVE_FORCEINLINE void set(std::size_t i, value_type v) noexcept
    {
      detail::insert(EVE_CURRENT_API{}, as_<wide>{}, data_, i, v);
    }

    EVE_FORCEINLINE value_type operator[](std::size_t i) const noexcept
    {
      return detail::extract(EVE_CURRENT_API{}, as_<wide>{}, data_, i);
    }

    EVE_FORCEINLINE value_type back()  const noexcept { return this->operator[](static_size-1); }
    EVE_FORCEINLINE value_type front() const noexcept { return this->operator[](0);             }

    //===============================================================================================
    // Self-increment/decrement operators
    //==============================================================================================
    EVE_FORCEINLINE wide &operator++() noexcept
    {
      return detail::self_add(*this, Type{1});
    }

    EVE_FORCEINLINE wide operator++(int) noexcept
    {
      auto that(*this);
           operator++();
      return that;
    }

    EVE_FORCEINLINE wide &operator--() noexcept
    {
      return detail::self_sub(*this, Type{1});
      return *this;
    }

    EVE_FORCEINLINE wide operator--(int) noexcept
    {
      auto that(*this);
           operator--();
      return that;
    }

    //==============================================================================================
    // Compound operators
    //==============================================================================================
    template<typename Other>
    EVE_FORCEINLINE   auto operator+=(Other const &other) noexcept
                  ->  decltype(detail::self_add(*this, other))
    {
      return detail::self_add(*this, other);
    }

    template<typename Other>
    EVE_FORCEINLINE   auto operator-=(Other const &other) noexcept
                  ->  decltype(detail::self_sub(*this, other))
    {
      return detail::self_sub(*this, other);
    }

    template<typename Other>
    EVE_FORCEINLINE   auto operator*=(Other const &other) noexcept
                  ->  decltype(detail::self_mul(*this, other))
    {
      return detail::self_mul(*this, other);
    }

    template<typename Other>
    EVE_FORCEINLINE   auto operator/=(Other const &other) noexcept
                  ->  decltype(detail::self_div(*this, other))
    {
      return detail::self_div(*this, other);
    }

    template<typename Other>
    EVE_FORCEINLINE   auto operator%=(Other const &other) noexcept
                  ->  decltype(detail::self_rem(*this, other))
    {
      return detail::self_rem(*this, other);
    }

    // TODO
    // >>= <<=

    template<typename Other>
    EVE_FORCEINLINE   auto operator&=(Other const &other) noexcept
                  ->  decltype(detail::self_bitand(*this, other))
    {
      return detail::self_bitand(*this, other);
    }

    template<typename Other>
    EVE_FORCEINLINE   auto operator|=(Other const &other) noexcept
                  ->  decltype(detail::self_bitor(*this, other))
    {
      return detail::self_bitor(*this, other);
    }

    template<typename Other>
    EVE_FORCEINLINE   auto operator^=(Other const &other) noexcept
                  ->  decltype(detail::self_bitxor(*this, other))
    {
      return detail::self_bitxor(*this, other);
    }

    friend std::ostream &operator<<(std::ostream &os, wide const &p)
    {
      constexpr auto sz = sizeof(storage_type)/sizeof(Type);
      auto that = bit_cast( p, as_<std::array<Type,sz>>());

      os << '(' << +that[ 0 ];
      for(size_type i = 1; i != p.size(); ++i) os << ", " << +that[ i ];
      return os << ')';
    }

    //==============================================================================================
    // SIMD register storage
    //==============================================================================================
    private:
    storage_type data_;
  };

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE void swap(wide<T, N, ABI> &lhs, wide<T, N, ABI> &rhs) noexcept
  {
    lhs.swap(rhs);
  }
}
