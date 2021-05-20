#if 0
namespace eve
{
  template<kumi::product_type Base, typename Cardinal>
  struct bundle
  {
    template<kumi::product_type Tuple>
    explicit bundle(Tuple const& t)
                    : contents{
                        [&]<std::size_t... I>(std::index_sequence<I...>)
                        {
                          return content_t{std::tuple_element_t<I,content_t>( get<I>(t) )...};
                        }( std::make_index_sequence<kumi::size<content_t>::value>{})
                      }
    {}

    template<std::size_t I>
    friend auto const& get(bundle const& s) noexcept { return kumi::get<I>(s.contents); }

    template<std::size_t I>
    friend auto & get(bundle& s) noexcept { return kumi::get<I>(s.contents); }

    template<typename Function, kumi::product_type... Bundles>
    friend decltype(auto) map(Function&& f, bundle b, bundle<Bundles,Cardinal> const&... bs)
    {
      return bundle{kumi::map(f, b, bs...)};
    }

    friend decltype(auto) flatten(bundle const& b)      { return bundle{kumi::flatten(b)}; }
    friend decltype(auto) flatten_all(bundle const& b)  { return bundle{kumi::flatten_all(b)}; }
  };

  template<simd_value... Ms> bundle(kumi::tuple<Ms...> const&) -> bundle<Ms...>;
}
#endif
