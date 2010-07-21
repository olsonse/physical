/** \file
 * A registry for physical::quantity types that have been initialized
 * properly.
 *
 * */

#if ( defined(PHYSICAL_DATA_FOR_RUNTIME) && \
     !defined(runtime_physical_dimension_define_h) ) || \
    (!defined(PHYSICAL_DATA_FOR_RUNTIME) && \
     !defined(physical_dimension_define_h) )

#  if defined(PHYSICAL_DATA_FOR_RUNTIME)
#    define runtime_physical_dimension_define_h
#  else
#    define physical_dimension_define_h
#  endif

#include <physical/constant/si.h>


#  if defined (PHYSICAL_DATA_FOR_RUNTIME)
namespace runtime {
#  endif



namespace physical {
  /** little SQR function because I don't want to have to depend on
   * olson_tools::power for this. */
  template < typename T >
  T SQR( const T & t ) {
    return t*t;
  }

  /** little CUBE function because I don't want to have to depend on
   * olson_tools::power for this. */
  template < typename T >
  T CUBE( const T & t ) {
    return t*t*t;
  }

  /** little x^4 function to ease things a bit. */
  template < typename T >
  T POW4( const T & t ) {
    return t*t*t*t;
  }

  namespace dimension {
#define PHYSICAL_DIM_W_VAL(D,VAL) \
    template< typename T > \
    struct D { \
      static const Quantity & value() { \
        static const Quantity _value = VAL; \
        return _value; \
      } \
    };

#define PHYSICAL_DIM(D) \
      PHYSICAL_DIM_W_VAL(D,T::DIMENSION_DOES_NOT_EXIST_FOR_THIS_SYSTEM)

    /* fundamental dimensions must be specified per system. */ 
    PHYSICAL_DIM(length);
    PHYSICAL_DIM(mass);
    PHYSICAL_DIM(time);
    PHYSICAL_DIM(charge);

    /* derived dimensions can generally be used without specializing. */

    /* Note:  BEFORE you consider adding dimensions to this list, please first
     * determine whether:
     * 1.  you would be adding a generally very useful dimension
     * 2.  you can not use the make_dim<> and exp_dim<> classes to get what you
     *     need local to your code.
     */
    PHYSICAL_DIM_W_VAL(frequency,     1. / time<T>::value() );
    PHYSICAL_DIM_W_VAL(charge_to_mass, charge<T>::value() / mass<T>::value() );
    PHYSICAL_DIM_W_VAL(inverse_length,1. / length<T>::value() );
    PHYSICAL_DIM_W_VAL(area,          1. / SQR(length<T>::value()) );
    PHYSICAL_DIM_W_VAL(volume,        CUBE(length<T>::value()) );
    PHYSICAL_DIM_W_VAL(number_density,1. / volume<T>::value() );
    PHYSICAL_DIM_W_VAL(density,       mass<T>::value()
                                    * number_density<T>::value() );
    PHYSICAL_DIM_W_VAL(velocity,      length<T>::value() / time<T>::value() );
    PHYSICAL_DIM_W_VAL(acceleration,  velocity<T>::value() / time<T>::value() );
    PHYSICAL_DIM_W_VAL(force,         mass<T>::value()
                                    * acceleration<T>::value() );
    PHYSICAL_DIM_W_VAL(energy,        force<T>::value() * length<T>::value() );
    PHYSICAL_DIM_W_VAL(power,         energy<T>::value() / time<T>::value() );
    PHYSICAL_DIM_W_VAL(temperature,   energy<T>::value() / constant::si::K_B );
    PHYSICAL_DIM_W_VAL(pressure,      force<T>::value()
                                    / SQR(length<T>::value()) );
    PHYSICAL_DIM_W_VAL(momentum,      velocity<T>::value() * mass<T>::value() );
    PHYSICAL_DIM_W_VAL(angular_momentum, momentum<T>::value()
                                    * length<T>::value() );
    PHYSICAL_DIM_W_VAL(viscosity,     force<T>::value() * time<T>::value()
                                    / area<T>::value() );
    PHYSICAL_DIM_W_VAL(kinematic_viscosity,     viscosity<T>::value()
                                              / density<T>::value() );
    namespace electric {
      PHYSICAL_DIM_W_VAL(potential,   energy<T>::value() / charge<T>::value() );
      PHYSICAL_DIM_W_VAL(field,       potential<T>::value()
                                    / length<T>::value() );
      PHYSICAL_DIM_W_VAL(current,     charge<T>::value() / time<T>::value() );
      PHYSICAL_DIM_W_VAL(resistance,  potential<T>::value()
                                    / current<T>::value() );
      PHYSICAL_DIM_W_VAL(conductance, 1. / resistance<T>::value() );
      PHYSICAL_DIM_W_VAL(resistivity, resistance<T>::value()
                                    * length<T>::value() );
      PHYSICAL_DIM_W_VAL(conductivity,1. / resistivity<T>::value() );
      PHYSICAL_DIM_W_VAL(capacitance, charge<T>::value()
                                    / potential<T>::value() );
    } /* electric */
    namespace magnetic {
      PHYSICAL_DIM_W_VAL(flux,        electric::potential<T>::value()
                                    * time<T>::value() );
      PHYSICAL_DIM_W_VAL(flux_density, flux<T>::value()
                                    / SQR(length<T>::value()) );
      PHYSICAL_DIM_W_VAL(field,       flux_density<T>::value() );
      PHYSICAL_DIM_W_VAL(inductance,  flux<T>::value()
                                    / electric::current<T>::value() );
      PHYSICAL_DIM_W_VAL(permeability, inductance<T>::value()
                                    / length<T>::value() );
      PHYSICAL_DIM_W_VAL(moment,      energy<T>::value()
                                    / flux_density<T>::value() );
    } /* magnetic */

    PHYSICAL_DIM_W_VAL(unity, Quantity(1.0));



    /** Exponentiates a dimension by an integer power. */
    template < template <typename> class dim, int power >
    struct exp_dim {
      template < typename T >
      struct type {
        static const Quantity & value() {
          static const Quantity _value = pow( dim<T>::value(), power );
          return _value;
        }
      };
    };



    /** Exponentiation specialization for power = -1. */
    template < template <typename> class dim>
    struct exp_dim<dim,-1> {
      template < typename T >
      struct type {
        static const Quantity & value() {
          static const Quantity _value = 1./ dim<T>::value();
          return _value;
        }
      };
    };


    /** Exponentiation specialization for power = -2. */
    template < template <typename> class dim>
    struct exp_dim<dim,-2> {
      template < typename T >
      struct type {
        static const Quantity & value() {
          static const Quantity _value = 1./ SQR( dim<T>::value() );
          return _value;
        }
      };
    };


    /** Exponentiation specialization for power = -3. */
    template < template <typename> class dim>
    struct exp_dim<dim,-3> {
      template < typename T >
      struct type {
        static const Quantity & value() {
          static const Quantity _value = 1./ CUBE( dim<T>::value() );
          return _value;
        }
      };
    };


    /** Exponentiation specialization for power = -4. */
    template < template <typename> class dim>
    struct exp_dim<dim,-4> {
      template < typename T >
      struct type {
        static const Quantity & value() {
          static const Quantity _value = 1./ POW4( dim<T>::value() );
          return _value;
        }
      };
    };


    /** Exponentiation specialization for power =  1. */
    template < template <typename> class dim>
    struct exp_dim<dim,1> {
      template < typename T >
      struct type {
        static const Quantity & value() {
          static const Quantity _value = dim<T>::value();
          return _value;
        }
      };
    };


    /** Exponentiation specialization for power =  2. */
    template < template <typename> class dim>
    struct exp_dim<dim,2> {
      template < typename T >
      struct type {
        static const Quantity & value() {
          static const Quantity _value = SQR( dim<T>::value() );
          return _value;
        }
      };
    };


    /** Exponentiation specialization for power =  3. */
    template < template <typename> class dim>
    struct exp_dim<dim,3> {
      template < typename T >
      struct type {
        static const Quantity & value() {
          static const Quantity _value = CUBE( dim<T>::value() );
          return _value;
        }
      };
    };


    /** Exponentiation specialization for power =  4. */
    template < template <typename> class dim>
    struct exp_dim<dim,4> {
      template < typename T >
      struct type {
        static const Quantity & value() {
          static const Quantity _value = POW4( dim<T>::value() );
          return _value;
        }
      };
    };



    /** Dimension aggregation class.
     * This class can be used to define a new dimension that is the aggregate of
     * several other dimensions.  As an example, consider the Steffan-Boltzmann
     * constant \f$ \sigma_{\rm SB} \f$.  To convert \f$ \sigma_{\rm SB} \f$
     * from one unit system to another, local to physical::constant::detail::*
     * we define the aggregate dimension <code>sigma_SB_dims</code> as:<br>
     \verbatim
       template < typename T, int U >
       struct sigma_SB_dims :
         make_dim<
           dimension::power,
           exp_dim<dimension::length,-2>::type,
           exp_dim<dimension::temperature,-4>::type
         >::dim<T,U> {};
     \endverbatim
     */
    template < template <typename> class D0,
               template <typename> class D1 = unity,
               template <typename> class D2 = unity,
               template <typename> class D3 = unity,
               template <typename> class D4 = unity,
               template <typename> class D5 = unity,
               template <typename> class D6 = unity,
               template <typename> class D7 = unity,
               template <typename> class D8 = unity,
               template <typename> class D9 = unity >
    struct make_dim {
      template < typename T >
      struct dim {
        static const Quantity & value() {
          static const Quantity _value
            = D0<T>::value() * D1<T>::value() * D2<T>::value() * D3<T>::value()
            * D4<T>::value() * D5<T>::value() * D6<T>::value() * D7<T>::value()
            * D8<T>::value() * D9<T>::value();
          return _value;
        }
      };
    };

  }/* namespace physical::dimension */
  
#undef PHYSICAL_DIM_W_VAL
#undef PHYSICAL_DIM
}


#  if defined (PHYSICAL_DATA_FOR_RUNTIME)
}/* namespace runtime. */
#  endif

#endif // physical_dimension_define_h
