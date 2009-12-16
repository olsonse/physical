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

  template < typename System, template <typename,int> class Dim >
  struct DimQuantity {
    DimQuantity( const Quantity & q ) : value(q) {}
    operator Quantity&() { return value; }
    operator const Quantity&() const { return value; }
    Quantity value;
  };


  template< typename To, typename From, template <typename,int> class Dim >
  struct make_convert_ratio {
    static const Quantity value;
  };

  template< typename To, typename From, template <typename,int> class Dim >
  const Quantity make_convert_ratio<To,From,Dim>::value = Dim<From,0>::value / Dim<To,0>::value;
  
  template< typename From, template <typename,int> class Dim >
  inline Quantity convert_ratio( const system::id::SYSTEM toId ) {
    switch (toId) {
      case system::si::Id:
        return make_convert_ratio<system::si, From, Dim>::value;
      case system::esu::Id:
        return make_convert_ratio<system::esu, From, Dim>::value;
      case system::emu::Id:
        return make_convert_ratio<system::emu, From, Dim>::value;
      case system::atomic::Id:
        return make_convert_ratio<system::atomic, From, Dim>::value;
      case system::gaussian::Id:
        return make_convert_ratio<system::gaussian, From, Dim>::value;
      case system::heaviside_lorentz::Id:
        return make_convert_ratio<system::heaviside_lorentz, From, Dim>::value;
      default:
        throw runtime::physical::exception("unknown output units on conversion");
    }
  }

  template< typename From, template <typename,int> class Dim >
  inline DimQuantity<From,Dim> convert( const DimQuantity<From,Dim> & q, const system::id::SYSTEM toId ) {
    DimQuantity<From,Dim> result( q.value * convert_ratio<From, Dim>(toId) );
    return result;
  }

  template< typename To, typename From, template <typename,int> class Dim >
  inline DimQuantity<From,Dim> convert( const DimQuantity<From,Dim> & q ) {
    DimQuantity<From,Dim> result( q.value * make_convert_ratio<To, From, Dim>::value );
    return result;
  }

}

#  if defined (PHYSICAL_DATA_FOR_RUNTIME)
}/* namespace runtime. */
#  endif


#endif // physical_dimension_convert_h
