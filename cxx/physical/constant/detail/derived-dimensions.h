/** \file The types in this detail namespace are for facilitating conversion of
 * physical constants which have various aggregate units. */

namespace detail {
  using dimension::make_dim;
  using dimension::exp_dim;

  template < typename T, int U = 0 >
  struct capacitance_per_length :
    make_dim<
      dimension::electric::capacitance,
      exp_dim<dimension::length,-1>::type
    >::dim<T,U> {};

  template < typename T, int U = 0 >
  struct length_per_capacitance :
    make_dim< exp_dim<capacitance_per_length,-1>::type >::dim<T,U> {};

  template < typename T, int U = 0 >
  struct sigma_SB_dims :
    make_dim<
      dimension::power,
      exp_dim<dimension::length,-2>::type,
      exp_dim<dimension::temperature,-4>::type
    >::dim<T,U> {};

  template < typename T, int U = 0 >
  struct G_dims :
    make_dim<
      exp_dim<dimension::length,3>::type,
      exp_dim<dimension::mass,-1>::type,
      exp_dim<dimension::time,-2>::type
    >::dim<T,U> {};

  template < typename T, int U = 0 >
  struct K_B_dims :
    make_dim<
      dimension::energy,
      exp_dim<dimension::temperature,-1>::type
    >::dim<T,U> {};
}
