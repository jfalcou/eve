//==================================================================================================
/**
  TTS - Tiny Test System
  Copyright : TTS Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

//==================================================================================================
// Dependencies
//==================================================================================================
#include <tts/tts.hpp>
#include <random>
#include <chrono>

//==================================================================================================
// Extension point for data management outside of basic types
// See documentation for proper usage
//==================================================================================================
namespace tts
{
  template<typename Base> struct adapter
  {
    template<typename U, typename Func>
    static void run(Base const*& src, U*& dst, Func f)    noexcept  { *dst++ = f(*src++);       }
    static auto retrieve(Base const* src)                 noexcept  { return *src;              }
    static void display(Base const& v, std::ostream& os)  noexcept  { os << tts::as_string(v);  }
  };

  template<typename Generator, typename Args>
  concept initializable = requires(Generator g, Args args) { g.init(args); };
}

//==================================================================================================
// Display settings
//==================================================================================================
namespace tts::detail
{
  class text_field
  {
    int width_, precision_;

    public:
    text_field( int width, int prec = 2  ) : width_( width ), precision_(prec)  {}
    friend std::ostream& operator<<( std::ostream& os, text_field const& manip )
    {
      os.setf( std::ios_base::left, std::ios_base::adjustfield );
      os.fill( ' ' );
      os.width( manip.width_ );
      os.precision( manip.precision_ );
      return os;
    }
  };

  class value_field
  {
    int width_, precision_;

    public:
    value_field( int width, int prec = 2 ) : width_( width ), precision_(prec) {}

    friend std::ostream& operator<<( std::ostream& os, value_field const& manip )
    {
      os.setf( std::ios_base::left  , std::ios_base::adjustfield );
      os.setf( std::ios_base::fixed , std::ios_base::floatfield  );
      os.fill( ' ' );
      os.precision( manip.precision_ );
      os.width( manip.width_ );
      return os;
    }
  };

  template<typename... S> void header( std::ostream& os, S const&... s)
  {
    ((os << std::left << detail::text_field(16) << s), ...);
    os << std::endl;
  }

  template<typename U, typename C, typename R, typename V>
  void results( std::ostream& os
              , U ulp, C count, R ratio, std::string const& desc, V const& v
              )
  {
    os  << std::left << std::noshowpos;
    os  << detail::text_field(16,1)   << ulp
        << detail::text_field(16)     << count
        << detail::value_field(16)    << ratio
        << detail::value_field(16,7)  << desc
        << std::showpos;
    adapter<V>::display(v,os);
    os << std::fixed << std::endl;
  }
}

//==================================================================================================
// ULP-related computations
//==================================================================================================
namespace tts::detail
{
  std::size_t next2( double x ) noexcept
  {
    auto v = static_cast<std::size_t>(std::ceil(x));
    v--;
    v |= v >> 1; v |= v >> 2; v |= v >> 4; v |= v >> 8; v |= v >> 16;
    v++;

    return v;
  }

  std::size_t last_bucket_less(std::size_t nb_buckets, double ulp) noexcept
  {
    std::size_t bucket;
    if     (ulp <= 1.5     ) bucket = static_cast<std::size_t>(std::ceil(ulp*2));
    else if(std::isinf(ulp)) bucket = nb_buckets-1;
    else                     bucket = std::min( nb_buckets-2
                                              , static_cast<std::size_t>(std::log2(next2(ulp))+4)
                                              );
    return bucket;
  }

  template<typename Type,typename In, typename Out, typename Func>
  void compute(In const& inputs, Out& outputs, Func fn)
  {
    auto in   = inputs.data();
    auto end  = inputs.data() + inputs.size();
    auto out  = outputs.data();
    while(in != end)
      adapter<Type>::run(in,out,fn);
  }
}

//==================================================================================================
// Main function for ULP histograms testing
//==================================================================================================
namespace tts
{
  template< typename RefType, typename NewType
          , typename Generator, typename RefFun, typename NewFun
          >
  double ulp_histogram(Generator g, RefFun reference, NewFun challenger,  std::ostream& output)
  {
    using out_type  = std::decay_t<decltype( reference( std::declval<RefType>() ))>;
    using nout_type = std::decay_t<decltype( challenger( std::declval<NewType>() ))>;

    //-- Find how many elements in a block
    std::size_t count = ::tts::arguments().value( "--block", 4096ULL);

    //-- Prepare blocks
    std::vector<out_type> ref_out(count), new_out(count);
    std::vector<RefType>  inputs(count);

    for(std::size_t i=0;i<inputs.size();++i)
      inputs[i] = g(i,count);

    std::size_t repetition  = ::tts::arguments().value( "--loop", 1ULL);

    double max_ulp = 0.;
    std::size_t nb_buckets  = 2+1+16;
    std::size_t nb_ulps     = 0;
    std::vector<std::size_t> ulp_map(nb_buckets,0);

    std::vector<std::tuple<bool,NewType,nout_type,nout_type> > samples(nb_buckets, {false,{},{},{}});

    for(std::size_t r=0;r<repetition;++r)
    {
      //--- Compute reference & challenger outputs
      detail::compute<RefType>(inputs,ref_out,reference);
      detail::compute<NewType>(inputs,new_out,challenger);

      //--- Compute ulp distances
      std::vector<double> ulpdists(count);

      for(std::size_t i=0;i<ulpdists.size();++i)
      {
        nb_ulps++;

        ulpdists[i] = ::tts::ulp_distance(ref_out[i], new_out[i]);
        max_ulp     = std::max(max_ulp,ulpdists[i]);

        auto idx = detail::last_bucket_less(nb_buckets,ulpdists[i]);
        ulp_map[ idx ]++;

        if( !std::get<0>( samples[ idx ] ) )
        {
          samples[idx]  = { true
                          , adapter<NewType>::retrieve(&inputs[i])
                          , adapter<nout_type>::retrieve(&new_out[i])
                          , adapter<nout_type>::retrieve(&ref_out[i])
                          };
        }
      }
    }

    detail::header(output, "Max ULP", "Count (#)", "Cum. Ratio (%)", "Samples");
    output << std::string(80,'-') << '\n';

    double ratio = 0.;

    for(std::size_t i=0;i<ulp_map.size();++i)
    {
      if(ulp_map[i] != 0)
      {
        double  ulps = 0;

        ratio += (100.*ulp_map[i])/nb_ulps;

        if     (i <= 3            ) ulps = i/2.0;
        else if(i == nb_buckets-1 ) ulps = std::numeric_limits<double>::infinity();
        else                        ulps = 1<<(i-4);

        detail::results (output, ulps , ulp_map[i], ratio, "Input: ", std::get<1>(samples[i]) );
        detail::results (output, "" , "" , "", "Found: " , std::get<2>( samples[i]) );
        detail::results (output, "" , "" , "", "instead of: " , std::get<3>( samples[i]) );
        output << std::string(80,'-') << '\n' << std::noshowpos;
      }
    }

    return max_ulp;
  }

  template<typename P>
  void print_producer(P const& producer, const char* alt, std::ostream& output)
  {
    if constexpr(   tts::support_std_to_string<P>
                ||  tts::streamable<P>
                ||  tts::support_to_string<P>
                )
    {
      output << ::tts::as_string(producer) << "\n";
    }
    else
    {
      output << alt << "\n";
    }
  }
}

//==================================================================================================
// Generate a range based test between two function
//==================================================================================================
#define TTS_ULP_RANGE_CHECK(Producer, RefType, NewType, RefFunc, NewFunc, Ulpmax)                   \
  [&]()                                                                                             \
  {                                                                                                 \
    std::ostringstream output;                                                                      \
    auto generator = TTS_REMOVE_PARENS(Producer);                                                   \
    tts::print_producer(generator, TTS_STRING(Producer), output );                                  \
                                                                                                    \
    auto local_tts_threshold  = ::tts::arguments().value( "--ulpmax", Ulpmax );                     \
    auto local_tts_max_ulp    = ::tts::ulp_histogram< TTS_REMOVE_PARENS(RefType)                    \
                                                    , TTS_REMOVE_PARENS(NewType)                    \
                                                    >                                               \
                                ( generator                                                         \
                                , RefFunc, NewFunc                                                  \
                                , output                                                            \
                                );                                                                  \
                                                                                                    \
    if(local_tts_max_ulp <= local_tts_threshold)                                                    \
    {                                                                                               \
      ::tts::global_runtime.pass();                                                                 \
    }                                                                                               \
    else                                                                                            \
    {                                                                                               \
      std::cout << "Comparing: " << TTS_STRING(RefFunc)                                             \
                << "<" << TTS_STRING(TTS_REMOVE_PARENS(RefType)) << ">"                             \
                << " with " << TTS_STRING(NewFunc)                                                  \
                << "<" << TTS_STRING(TTS_REMOVE_PARENS(NewType))                                    \
                << "> using ";                                                                      \
      std::cout << output.str() << "\n";                                                            \
      TTS_FAIL(     "Expecting: "   << TTS_STRING(NewFunc)                                          \
                <<  " similar to "  << TTS_STRING(RefFunc)                                          \
                <<  " within "      << std::setprecision(2)                                         \
                                    << local_tts_threshold  << " ULP"                               \
                <<  " but found: "  << std::setprecision(2)                                         \
                                    << local_tts_max_ulp    << " ULP instead"                       \
              );                                                                                    \
    }                                                                                               \
  }()
/**/

//==================================================================================================
// Ready-to-use PRNGs
//==================================================================================================
namespace tts
{
  //================================================================================================
  // Standard random distribution generator wrapper
  //================================================================================================
  template<typename T, typename Distribution>
  struct prng_generator
  {
    using param_type = typename Distribution::param_type;

    template<typename... Args>
    prng_generator(Args... args) : distribution_(std::forward<Args>(args)...)
    {
      seed_ = random_seed();
      generator_.seed(seed_);

      auto mn = ::tts::arguments().value( "--valmin", distribution_.min() );
      auto mx = ::tts::arguments().value( "--valmax", distribution_.max() );

      distribution_.param(param_type(mn, mx));
    }

    template<typename Idx, typename Count> T operator()(Idx, Count)
    {
      return distribution_(generator_);
    }

    friend std::string to_string(prng_generator const& p)
    {
      std::ostringstream txt;
      txt << typename_<Distribution>
          << "(" << p.distribution_.min() << ", " << p.distribution_.max() << ")"
          << "[seed = " << p.seed_ << "]";
      return txt.str();
    }

    private:
    Distribution              distribution_;
    std::mt19937              generator_;
    std::mt19937::result_type seed_;
  };

  //================================================================================================
  // Uniform PRNG generator
  //================================================================================================
  template<typename T>
  using realistic_generator = prng_generator<T, ::tts::realistic_distribution<T>>;
}
