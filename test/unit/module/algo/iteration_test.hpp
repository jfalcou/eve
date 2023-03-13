
#include "unit/module/algo/algo_test.hpp"

#include <string>

#include <string_view>

namespace algo_test
{

struct iteration_fixture
{
  iteration_fixture()
  {
    data.fill(0);
    data[0] = data[1] = data[2] = data[3] = '_';
  }

  auto aligned_begin()
  {
    using ap = eve::aligned_ptr<char, eve::fixed<4>>;
    return eve::algo::ptr_iterator<ap, eve::fixed<4>> {ap(data.begin())};
  }

  auto aligned_end() { return aligned_begin() + data.size(); }

  auto unaligned_begin() { return eve::unalign(aligned_begin()); }
  auto unaligned_end() { return eve::unalign(aligned_end()); }

  std::string_view res() { return data.data(); }

  alignas(64) std::array<char, 100> data;
};

template<typename I> struct test_delegate
{
  test_delegate(I base, std::ptrdiff_t stop_at) : base {base}, stop_at(stop_at) {}

  I              base;
  std::ptrdiff_t stop_at;
  std::ptrdiff_t overflow_tracker = -1;

  template<std::ptrdiff_t idx, eve::relative_conditional_expr Ignore>
  bool step(I it, Ignore ignore, eve::index_t<idx>)
  {
    auto  tgt = eve::as<eve::wide_value_type_t<I>> {};
    char *ptr = it.ptr;
    for( std::ptrdiff_t i = ignore.offset(tgt); i; --i ) { *ptr++ = 'i'; }

    for( std::ptrdiff_t i = ignore.count(tgt); i; --i ) { *ptr++ = 'a' + idx; }

    for( std::ptrdiff_t i = ignore.roffset(tgt); i; --i ) { *ptr++ = 'i' + idx; }

    if( overflow_tracker != -1 )
    {
      auto ptr         = base.ptr + overflow_tracker;
      *ptr             = *ptr - 'a' + 'A';
      overflow_tracker = -1;
    }

    if( stop_at != -1 )
    {
      if( stop_at < (it - base) ) { return true; }
    }
    return false;
  }

  template<std::size_t size> bool unrolled_step(std::array<I, size> arr)
  {
    for( const auto& it : arr )
    {
      char *ptr = it.ptr;
      for( int i = 0; i != 4; ++i ) { ptr[i] = 'a' + (&it - arr.data()); }
    }

    if( overflow_tracker != -1 )
    {
      auto ptr         = base.ptr + overflow_tracker;
      *ptr             = *ptr - 'a' + 'A';
      overflow_tracker = -1;
    }

    if( stop_at != -1 )
    {
      if( stop_at < (arr[0] - base) ) { return true; }
    }

    return false;
  }

  void overflow(auto ptr) { overflow_tracker = ptr - base; }
};

inline std::string
run_uu_test(auto iteration_selector, auto traits, int offset, int size, int stop_at)
{
  iteration_fixture fixture;
  auto              f    = fixture.unaligned_begin() + offset;
  auto              l    = f + size;
  auto              iter = iteration_selector(traits, f, l);
  test_delegate     delegate {iter.base, stop_at};
  iter(delegate);
  return std::string(fixture.res());
}

} // namespace algo_test
