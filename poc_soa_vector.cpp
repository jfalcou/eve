#include <iostream>
#include <eve/wide.hpp>
#include <eve/algo/container/soa_vector.hpp>
#include <eve/memory/aligned_allocator.hpp>

template< eve::product_type Type
        , typename Allocator = eve::aligned_allocator<unsigned char, eve::fixed<64>>
        >
struct soa_vector2
{
  template<typename T>
  static auto realign(std::size_t n) { return eve::align(sizeof(T)*n, eve::over{64}); }

  using flat_t      = kumi::result::flatten_all_t<Type>;
  using sub_span_t  = kumi::as_tuple_t<flat_t, std::add_pointer>;

  soa_vector2 ( std::size_t n)
              : storage_( 64 + kumi::fold_left( [n]<typename S>(auto a, S m)
                                              {
                                                return a + realign<S>(n);
                                              }, flat_t{}, 0ULL)
                        )
              , size_(n)
  {
    reindex(n);
  }

  //private:
  using internal_alloc_t = typename std::allocator_traits<Allocator>::rebind_alloc<unsigned char>;
  std::vector<unsigned char,internal_alloc_t> storage_;
  sub_span_t                                  indexes_;
  std::size_t                                 size_;

  private:
  void reindex(std::size_t n)
  {
    auto sub_span = eve::align(&storage_[0], eve::over{64});
    kumi::for_each( [&]<typename T>(T*& s) { s = new(sub_span) T[n]; sub_span += realign<T>(n); }
                  , indexes_
                  );
  }
};

soa_vector2 < kumi::tuple<short,double,int,short>
            , std::allocator<float>
            >           x(31);

int main()
{
  std::cout << x.indexes_ << "\n";
/*
  for(std::size_t i=0;i<64;++i)
  {
    get<0>(x.indexes_)[i] = 1./(1+i);
    get<1>(x.indexes_)[i] = (1+i);
    get<2>(x.indexes_)[i] = 3.7*(1+i);
  }

  for(std::size_t i=0;i<64;++i)
  {
    get<0>(x.indexes_)[i] *= get<2>(x.indexes_)[i];
    get<1>(x.indexes_)[i] += get<2>(x.indexes_)[i];
  }*/
}
