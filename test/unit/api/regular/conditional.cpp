//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
#include <eve/module/core.hpp>
//==================================================================================================
#include "test.hpp"
#include <cstddef>

#include <eve/wide.hpp>

#if defined(SPY_SIMD_IS_X86_AVX512)
template<typename Type, typename Cond> void check_conditional_bits()
{
  if constexpr( !eve::has_aggregated_abi_v<Type> )
  {
    using m_t = typename eve::logical<Type>::storage_type::type;
    m_t bits_mask = m_t(~eve::detail::set_lower_n_bits<m_t>(Type::size()));

    for(std::ptrdiff_t i = 0;i <= Type::size();i++)
    {
      auto ignore_mask = Cond(i).mask(eve::as<Type>()).storage().value;
      TTS_EQUAL( m_t(ignore_mask & bits_mask), m_t(0) );
    }
  }
}
#endif

TTS_CASE_TPL( "ignore_all behavior", eve::test::simd::all_types)
<typename type>(tts::type<type>)
{
  using eve::logical;
  using eve::relative_conditional_expr;
  using eve::ignore_all;
  using eve::if_else;
  using eve::as;

  TTS_EXPECT( relative_conditional_expr<eve::ignore_all_>  );

  TTS_EXPR_IS(ignore_all.mask( as<type>() ), logical<type> );

  TTS_EQUAL( ignore_all.mask( as<type>() )           , eve::false_( as<type>()) );
  TTS_EQUAL( (if_else(ignore_all,type(42), type(69))) , type(69)                );

#if defined(SPY_SIMD_IS_X86_AVX512)
  if constexpr( !eve::has_aggregated_abi_v<type> )
    TTS_EQUAL( ignore_all.mask(as<type>()).storage().value, 0U );
#endif

  // For half_c wide, checks we don't have spurious true in the outside values
  using abi = typename type::abi_type;
  if constexpr( abi::is_wide_logical && !eve::use_complete_storage<type> )
  {
    using e_t   = eve::element_type_t<type>;
    using abi_t = typename type::abi_type;
    using w_t   = eve::wide<e_t, eve::expected_cardinal_t<e_t, abi_t> >;

    eve::logical<w_t> values = eve::bit_cast( ignore_all.mask(as<type>())
                                            , eve::as<eve::logical<w_t>>()
                                            );

    TTS_EQUAL(values, eve::false_(as(values)));
  }
};

TTS_CASE_TPL( "ignore_none behavior", eve::test::simd::all_types)
<typename type>(tts::type<type>)
{
  using eve::logical;
  using eve::relative_conditional_expr;
  using eve::ignore_none;
  using eve::if_else;
  using eve::as;

  TTS_EXPECT( relative_conditional_expr<eve::ignore_none_>  );

  TTS_EXPR_IS(ignore_none.mask( as<type>() ), logical<type> );

  TTS_EQUAL( ignore_none.mask( as<type>() )            , eve::true_( as<type>() )  );
  TTS_EQUAL( (if_else(ignore_none,type(42), type(69)))  , type(42)                  );

#if defined(SPY_SIMD_IS_X86_AVX512)
  if constexpr( !eve::has_aggregated_abi_v<type> )
  {
    using m_t = typename eve::logical<type>::storage_type::type;
    TTS_EQUAL ( ignore_none.mask(as<type>()).storage().value
              , eve::detail::set_lower_n_bits<m_t>(type::size())
              );
  }
#endif

  // For half_c wide, checks we don't have spurious true in the outside values
  using abi = typename type::abi_type;
  if constexpr( abi::is_wide_logical && !eve::use_complete_storage<type> )
  {
    using e_t   = eve::element_type_t<type>;
    using abi_t = typename type::abi_type;
    using w_t   = eve::wide<e_t, eve::expected_cardinal_t<e_t, abi_t> >;

    eve::logical<w_t> values = eve::bit_cast( ignore_none.mask(as<type>())
                                            , eve::as<eve::logical<w_t>>()
                                            );

    eve::logical<w_t> mask_ref = [=](auto i, auto) { return i<type::size(); };

    TTS_EQUAL(values, mask_ref);
  }
};

TTS_CASE_TPL( "keep_first behavior", eve::test::simd::all_types)
<typename type>(tts::type<type>)
{
  using eve::logical;
  using eve::relative_conditional_expr;
  using eve::keep_first;
  using eve::if_else;
  using eve::as;

  TTS_EXPECT( relative_conditional_expr<eve::keep_first>  );

  type value = [](auto i, auto) { return 1+i; };

  TTS_EXPR_IS(keep_first(0).mask( as<type>() ), logical<type> );

  TTS_EQUAL( keep_first(type::size()).mask(as<type>()).bits(), eve::true_(as<type>()).bits());
  TTS_EQUAL( (if_else(keep_first(type::size()),value, type(69))), value                   );

  for(std::ptrdiff_t i = 1;i < type::size();i++)
  {
    logical<type> mref  = [i](auto j, auto) { return j < i; };
    type          ref   = [i,&value](auto j, auto) { return (j < i) ? value.get(j) : 69.f; };

    TTS_EQUAL( keep_first(i).mask(as<type>()).bits(), mref.bits() );
    TTS_EQUAL( (if_else(keep_first(i),value, type(69))), ref);
  }

  TTS_EQUAL( keep_first(0).mask(as<type>()).bits(), eve::false_(as<type>()).bits());
  TTS_EQUAL( (if_else(keep_first(0),value, type(69))) , type(69)                  );

#if defined(SPY_SIMD_IS_X86_AVX512)
  check_conditional_bits<type, keep_first>();
#endif

  // For half_c wide, checks we don't have spurious true in the outside values
  if constexpr( type::abi_type::is_wide_logical && !eve::use_complete_storage<type> )
  {
    for(std::ptrdiff_t i = 0;i <= type::size();i++)
    {
      using e_t   = eve::element_type_t<type>;
      using abi_t = typename type::abi_type;
      using w_t   = eve::wide<e_t, eve::expected_cardinal_t<e_t, abi_t> >;

      eve::logical<w_t> values = eve::bit_cast( keep_first(i).mask(as<type>())
                                                , eve::as<eve::logical<w_t>>()
                                                );
      eve::logical<w_t> mask_ref = [=](auto n, auto) { return n<i; };

      TTS_EQUAL(values, mask_ref);
    }
  }
};

TTS_CASE_TPL( "ignore_last behavior", eve::test::simd::all_types)
<typename type>(tts::type<type>)
{
  using eve::logical;
  using eve::relative_conditional_expr;
  using eve::ignore_last;
  using eve::if_else;
  using eve::as;

  TTS_EXPECT( relative_conditional_expr<eve::ignore_last>  );

  type value = [](auto i, auto) { return 1+i; };

  TTS_EXPR_IS(ignore_last(0).mask( as<type>() ), logical<type> );

  TTS_EQUAL( ignore_last(0).mask(as<type>()).bits(), eve::true_(as<type>()).bits());
  TTS_EQUAL( (if_else(ignore_last(0),value, type(69))), value                   );

  for(std::ptrdiff_t i = 1;i < type::size();i++)
  {
    logical<type> mref  = [i](auto j, auto c) { return j < c-i; };
    type          ref   = [i,&value](auto j, auto c) { return (j < c-i) ? value.get(j) : 69; };

    TTS_EQUAL( ignore_last(i).mask(as<type>()).bits(), mref.bits() );
    TTS_EQUAL( (if_else(ignore_last(i),value, type(69))), ref);
  }

  TTS_EQUAL( ignore_last(type::size()).mask(as<type>())          , eve::false_( as<type>() ) );
  TTS_EQUAL( (if_else(ignore_last(type::size()),value, type(69))) , type(69)                  );

#if defined(SPY_SIMD_IS_X86_AVX512)
  check_conditional_bits<type, ignore_last>();
#endif

  // For half_c wide, checks we don't have spurious true in the outside values
  if constexpr( type::abi_type::is_wide_logical && !eve::use_complete_storage<type> )
  {
    for(std::ptrdiff_t i = 0;i <= type::size();i++)
    {
      using e_t   = eve::element_type_t<type>;
      using abi_t = typename type::abi_type;
      using w_t   = eve::wide<e_t, eve::expected_cardinal_t<e_t, abi_t> >;

      eve::logical<w_t> values = eve::bit_cast( ignore_last(i).mask(as<type>())
                                              , eve::as<eve::logical<w_t>>()
                                              );
      eve::logical<w_t> mask_ref = [=](auto n, auto) { return n<(type::size()-i); };

      TTS_EQUAL(values, mask_ref);
    }
  }
};

TTS_CASE_TPL( "keep_last behavior", eve::test::simd::all_types)
<typename type>(tts::type<type>)
{
  using eve::logical;
  using eve::relative_conditional_expr;
  using eve::keep_last;
  using eve::if_else;
  using eve::as;

  TTS_EXPECT( relative_conditional_expr<eve::keep_last>  );

  type value = [](auto i, auto) { return 1+i; };

  TTS_EXPR_IS(keep_last(0).mask( as<type>() ), logical<type> );

  TTS_EQUAL( keep_last(type::size()).mask(as<type>()).bits(), eve::true_(as<type>()).bits());
  TTS_EQUAL( (if_else(keep_last(type::size()),value, type(69))), value                   );

  for(std::ptrdiff_t i = 1;i < type::size();i++)
  {
    logical<type> mref  = [i](auto j, auto c) { return j >= c-i; };
    type          ref   = [i,&value](auto j, auto c) { return (j >= c-i) ? value.get(j) : 69.f; };

    TTS_EQUAL( keep_last(i).mask(as<type>()).bits(), mref.bits() );
    TTS_EQUAL( (if_else(keep_last(i),value, type(69))), ref);
  }

  TTS_EQUAL( keep_last(0).mask(as<type>()).bits(), eve::false_(as<type>()).bits() );
  TTS_EQUAL( (if_else(keep_last(0),value, type(69))) , type(69)                     );

#if defined(SPY_SIMD_IS_X86_AVX512)
  check_conditional_bits<type, keep_last>();
#endif

  // For half_c wide, checks we don't have spurious true in the outside values
  if constexpr( type::abi_type::is_wide_logical && !eve::use_complete_storage<type> )
  {
    for(std::ptrdiff_t i = 0;i <= type::size();i++)
    {
      using e_t   = eve::element_type_t<type>;
      using abi_t = typename type::abi_type;
      using w_t   = eve::wide<e_t, eve::expected_cardinal_t<e_t, abi_t> >;

      eve::logical<w_t> values = eve::bit_cast( keep_last(i).mask(as<type>())
                                              , eve::as<eve::logical<w_t>>()
                                              );
      eve::logical<w_t> mask_ref = [=](auto n, auto)  { return    n>=(type::size()-i)
                                                              &&  n < type::size();
                                                      };

      TTS_EQUAL(values, mask_ref);
    }
  }
};

TTS_CASE_TPL( "ignore_first behavior", eve::test::simd::all_types)
<typename type>(tts::type<type>)
{
  using eve::logical;
  using eve::relative_conditional_expr;
  using eve::ignore_first;
  using eve::if_else;
  using eve::as;

  TTS_EXPECT( relative_conditional_expr<eve::ignore_first>  );

  type value = [](auto i, auto) { return 1+i; };

  TTS_EXPR_IS(ignore_first(0).mask( as<type>() ), logical<type> );

  TTS_EQUAL( ignore_first(0).mask(as<type>()).bits(), eve::true_(as<type>()).bits());
  TTS_EQUAL( (if_else(ignore_first(0),value, type(69))), value  );

  for(std::ptrdiff_t i = 1;i < type::size();i++)
  {
    logical<type> mref  = [i](auto j, auto) { return j >= i; };
    type          ref   = [i,&value](auto j, auto) { return (j >= i) ? value.get(j) : 69.f; };

    TTS_EQUAL( ignore_first(i).mask(as<type>()).bits(), mref.bits() );
    TTS_EQUAL( (if_else(ignore_first(i),value, type(69))), ref);
  }

  TTS_EQUAL( ignore_first(type::size()).mask(as<type>()).bits(), eve::false_(as<type>()).bits());
  TTS_EQUAL( (if_else(ignore_first(type::size()),value, type(69))) , type(69)                );

#if defined(SPY_SIMD_IS_X86_AVX512)
  check_conditional_bits<type,ignore_first>();
#endif

  // For half_c wide, checks we don't have spurious true in the outside values
  if constexpr( type::abi_type::is_wide_logical && !eve::use_complete_storage<type> )
  {
    for(std::ptrdiff_t i = 0;i <= type::size();i++)
    {
      using e_t   = eve::element_type_t<type>;
      using abi_t = typename type::abi_type;
      using w_t   = eve::wide<e_t, eve::expected_cardinal_t<e_t, abi_t> >;

      eve::logical<w_t> values = eve::bit_cast( ignore_first(i).mask(as<type>())
                                              , eve::as<eve::logical<w_t>>()
                                              );
      eve::logical<w_t> mask_ref = [=](auto n, auto)  { return    n>= i
                                                              &&  n < type::size();
                                                      };

      TTS_EQUAL(values, mask_ref);
    }
  }
};

TTS_CASE_TPL( "keep_between behavior", eve::test::simd::all_types)
<typename type>(tts::type<type>)
{
  using eve::logical;
  using eve::relative_conditional_expr;
  using eve::keep_between;
  using eve::if_else;
  using eve::as;

  TTS_EXPECT( relative_conditional_expr<eve::keep_between>  );

  type value = [](auto i, auto) { return 1+i; };

  TTS_EXPR_IS(keep_between(0,1).mask( as<type>() ), logical<type> );

  for(int fi = 0;fi < type::size();fi++)
  {
    for(int li = 0;li <= type::size();li++)
    {
      if(fi<=li)
      {
        logical<type> mref  = [&](auto j, auto) { return (j >= fi && j < li); };
        type          ref   = [&](auto j, auto) { return (j >= fi && j < li) ? 1+j : 69.f; };

        TTS_EQUAL( keep_between(fi,li).mask(as<type>()).bits(), mref.bits() );
        TTS_EQUAL( (if_else(keep_between(fi,li),value, type(69))), ref);

#if defined(SPY_SIMD_IS_X86_AVX512)
  if constexpr( !eve::has_aggregated_abi_v<type> )
  {
    using m_t = typename eve::logical<type>::storage_type::type;
    m_t bits_mask = m_t(~eve::detail::set_lower_n_bits<m_t>(type::size()));

    auto ignore_mask = keep_between(fi,li).mask(eve::as<type>()).storage().value;
    TTS_EQUAL( m_t(ignore_mask & bits_mask), m_t(0) );
  }
#endif
      }
    }
  }

  // For half_c wide, checks we don't have spurious true in the outside values
  if constexpr( type::abi_type::is_wide_logical && !eve::use_complete_storage<type> )
  {
    for(std::ptrdiff_t i = 0;i <= type::size();i++)
    {
      for(std::ptrdiff_t j = 0;j <= type::size();j++)
      {
        using e_t   = eve::element_type_t<type>;
        using abi_t = typename type::abi_type;
        using w_t   = eve::wide<e_t, eve::expected_cardinal_t<e_t, abi_t> >;

        if(i<=j)
        {
          eve::logical<w_t> values = eve::bit_cast( keep_between(i,j).mask(as<type>())
                                                  , eve::as<eve::logical<w_t>>()
                                                  );
          eve::logical<w_t> mask_ref = [=](auto n, auto) { return n >= i && n < j; };

          TTS_EQUAL(values, mask_ref);
        }
      }
    }
  }
};

TTS_CASE_TPL( "ignore_first/last behavior", eve::test::simd::all_types)
<typename type>(tts::type<type>)
{
  using eve::logical;
  using eve::relative_conditional_expr;
  using eve::ignore_first;
  using eve::ignore_last;
  using eve::if_else;
  using eve::as;

  TTS_EXPECT( relative_conditional_expr<eve::ignore_extrema>  );

  type value = [](auto i, auto) { return 1+i; };

  TTS_EXPR_IS( ((ignore_first(1) && ignore_last(0)).mask( as<type>() )), logical<type> );

  // All masks combo
  for(std::ptrdiff_t li = 0;li <=type::size();li++)
  {
    for(std::ptrdiff_t fi =0;fi <=type::size();fi++)
    {
      auto mref  = ignore_first(fi).mask(as<type>()) && ignore_last(li).mask(as<type>());
      type ref   = if_else(mref, value,  type(69));

      if(fi+li <= type::size())
      {
        TTS_EQUAL( (ignore_first(fi) && ignore_last(li)).mask(as<type>()).bits(), mref.bits() );
        TTS_EQUAL( (if_else(ignore_first(fi) && ignore_last(li),value, type(69))), ref);

#if defined(SPY_SIMD_IS_X86_AVX512)
  if constexpr( !eve::has_aggregated_abi_v<type> )
  {
    using m_t = typename eve::logical<type>::storage_type::type;
    m_t bits_mask = m_t(~eve::detail::set_lower_n_bits<m_t>(type::size()));

    auto ignore_mask = (ignore_first(fi) && ignore_last(li)).mask(eve::as<type>()).storage().value;
    TTS_EQUAL( m_t(ignore_mask & bits_mask), m_t(0) );
  }
#endif
      }
    }
  }


  // For half_c wide, checks we don't have spurious true in the outside values
  if constexpr( type::abi_type::is_wide_logical && !eve::use_complete_storage<type> )
  {
    for(std::ptrdiff_t i = 0;i <= type::size();i++)
    {
      for(std::ptrdiff_t j = 0;j <= type::size();j++)
      {
        using e_t   = eve::element_type_t<type>;
        using abi_t = typename type::abi_type;
        using w_t   = eve::wide<e_t, eve::expected_cardinal_t<e_t, abi_t> >;

        if(i+j <= type::size())
        {
          eve::logical<w_t> values = eve::bit_cast( (ignore_first(i) && ignore_last(j)).mask(as<type>())
                                                  , eve::as<eve::logical<w_t>>()
                                                  );
          eve::logical<w_t> mask_ref = [=](auto n, auto) { return n >= i && n < (type::size()-j); };

          TTS_EQUAL(values, mask_ref);
        }
      }
    }
  }
};

TTS_CASE("conditional/reverse")
{
  using T = eve::wide<int, eve::fixed<4>>;

  auto rev = [](auto c) {
    return eve::reverse_conditional(c, eve::as<T>{});
  };

  TTS_CONSTEXPR_EQUAL(rev(eve::keep_first(3)),       eve::keep_last(3));
  TTS_CONSTEXPR_EQUAL(rev(eve::keep_last(3)),        eve::keep_first(3));
  TTS_CONSTEXPR_EQUAL(rev(eve::keep_between(0, 1)),  eve::keep_between(3, 4));

  TTS_CONSTEXPR_EQUAL(rev(eve::ignore_first(3)),      eve::ignore_last(3));
  TTS_CONSTEXPR_EQUAL(rev(eve::ignore_last(3)),       eve::ignore_first(3));
  TTS_CONSTEXPR_EQUAL(rev(eve::ignore_extrema(1, 2)), eve::ignore_extrema(2, 1));

  TTS_CONSTEXPR_EQUAL(rev(eve::keep_first(1).else_(0)), eve::keep_last(1).else_(0));
};

TTS_CASE("conditional/drop_alternative")
{
  TTS_CONSTEXPR_EQUAL(eve::drop_alternative(eve::keep_first(3)), eve::keep_first(3));
  TTS_CONSTEXPR_EQUAL(eve::drop_alternative(eve::keep_first(3).else_(1)), eve::keep_first(3));
};
