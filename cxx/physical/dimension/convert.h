/** \file
 * A registry for physical::quantity types that have been initialized
 * properly.
 *
 * */

#if ( defined(PHYSICAL_DATA_FOR_RUNTIME) && \
     !defined(runtime_physical_dimension_convert_h) ) || \
    (!defined(PHYSICAL_DATA_FOR_RUNTIME) && \
     !defined(physical_dimension_convert_h) )

#  if defined(PHYSICAL_DATA_FOR_RUNTIME)
#    define runtime_physical_dimension_convert_h
#  else
#    define physical_dimension_convert_h
#  endif

#  include <physical/except.h>
#  include <physical/system.h>

#  if defined (PHYSICAL_DATA_FOR_RUNTIME)
namespace runtime {
#  endif


namespace physical {

  template< typename From, template <typename> class Dim, typename To >
  struct make_convert_ratio {
    static Quantity value;
  };

  template< typename From, template <typename> class Dim, typename To >
  Quantity make_convert_ratio<From,Dim,To>::value = Dim< From >::value / Dim< To >::value;
  
  template< typename From, template <typename> class Dim >
  inline Quantity convert_ratio( const system::id::SYSTEM toId ) {
    switch (toId) {
      case system::si::Id:
        return make_convert_ratio<From, Dim, system::si>::value;
      case system::esu::Id:
        return make_convert_ratio<From, Dim, system::esu>::value;
      case system::emu::Id:
        return make_convert_ratio<From, Dim, system::emu>::value;
      case system::atomic::Id:
        return make_convert_ratio<From, Dim, system::atomic>::value;
      case system::gaussian::Id:
        return make_convert_ratio<From, Dim, system::gaussian>::value;
      case system::heaviside_lorentz::Id:
        return make_convert_ratio<From, Dim, system::heaviside_lorentz>::value;
      default:
        throw runtime::physical::exception("unknown output units on conversion");
    }
  }

  template< typename From, template <typename> class Dim >
  inline Quantity convert( const Quantity & q, const system::id::SYSTEM toId ) {
    return q * convert_ratio<From, Dim>(toId);
  }

  template< typename From, template <typename> class Dim, typename To >
  inline Quantity convert( const Quantity & q ) {
    return q * make_convert_ratio<From, Dim, To>::value;
  }

}

#  if defined (PHYSICAL_DATA_FOR_RUNTIME)
}/* namespace runtime. */
#  endif


#endif // physical_dimension_convert_h
