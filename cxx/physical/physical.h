/** \file
 * A multitude of physical constants and units (mks where applicable)
 * organized into a bunch of namespaces.
 *
 * Much of the data for the units and constants listed in this header are
 * freely available on usenet servers.  The reference for the original
 * header is comp.lang.cpp/2004-10/2217 by E. Robert Tisdale (10/17/04).
 * The namespace layout is original to the posting by E. Robert Tisdale.
 *
 * E. R. Tisdale <E.Robert.Tisdale_at_jpl.nasa.gov>.
 *
 * There were a lot of other comments on usenet for improving the header from
 * Tisdale, including British spelling of various units and so on.  This file
 * is based on the unaltered version from E. R. Tisdale.
 *
 * */

#if defined (PHYSICAL_DATA_FOR_RUNTIME) || !defined(PHYSICAL_DATA_H)
#  if !defined (PHYSICAL_DATA_FOR_RUNTIME)
#    define PHYSICAL_DATA_H
#  endif

#ifndef PHYSICAL_QUANTITY
/** The units/constants library defaults to just providing the information via
 * doubles. */
#  define PHYSICAL_QUANTITY double
#endif

#ifndef PHYSICAL_QUANTITY_CLASS
#  define PHYSICAL_QUANTITY_CLASS PHYSICAL_QUANTITY
#  define _QUANTITY(name,c)       const Quantity name = c
#  define _QUANTITYu(name,c,u)    const Quantity name = c
#  define _QUANTITYn(name,c,n)    const Quantity name = c
#  define _QUANTITYun(name,c,u,n) const Quantity name = c
#else
   /** Sets only the coefficient of the physical::quantity. */
#  define _QUANTITY(name,c)       const Quantity name = PHYSICAL_QUANTITY_CLASS(c,"",#name)
   /** Sets the value of the coefficient and the units of the physical::quantity
    * (if using the runtime library of course).
    */
#  define _QUANTITYu(name,c,u)    const Quantity name = PHYSICAL_QUANTITY_CLASS(c,u,"",#name)
   /** Sets the value of the coefficient and the name of the physical::quantity
    * (if using the runtime library of course).
    */
#  define _QUANTITYn(name,c,n)    const Quantity name = PHYSICAL_QUANTITY_CLASS(c,n,#name)
   /** Sets the value of the coefficient, the units, and the name of the
    * physical::quantity (if using the runtime library of course). 
    */
#  define _QUANTITYun(name,c,u,n) const Quantity name = PHYSICAL_QUANTITY_CLASS(c,u,n,#name)
#endif

#ifndef _OPEN_NAMESPACE
#  define _OPEN_NAMESPACE(i,id)   namespace id
#  define _CLOSE_NAMESPACE(i)
#endif

#ifndef _ALIAS_NAMESPACE
#  define _ALIAS_NAMESPACE(alias,ns) namespace alias = ns
#endif

#define _BEGIN_NAMESPACE(id)    _OPEN_NAMESPACE(0,id)
#define _END_NAMESPACE          _CLOSE_NAMESPACE(0)


_BEGIN_NAMESPACE(physical) {

    /** The base type for all items in the library depends.
     * This type can be a scalar value, or perhaps a class that checks type
     * information.
     *
     * @see PHYSICAL_QUANTITY_CLASS
     * */
    typedef PHYSICAL_QUANTITY_CLASS Quantity;

    // #### BEGIN OF UNIT CREATION #### #
    _BEGIN_NAMESPACE(unit) { // conversion factor
        _QUANTITYu(radian,              1.0,units_pair("radian",1));
        _QUANTITY(radians,              radian);
        _QUANTITY(rad,                  radian);
        _QUANTITYu(steradian,           1.0, units_pair("steradian",1));
        _QUANTITY(steradians,           steradian);
        _QUANTITY(sr,                   steradian);
        _QUANTITYu(dollar,              1.0, units_pair("dollar",1));
        _QUANTITY(dollars,              dollar);
        _QUANTITY(cent,                 dollar/100.0);
        _QUANTITY(cents,                cent);
        _QUANTITY(dozen,                12.0);
        _QUANTITY(doz,                  dozen);
        _QUANTITY(dz,                   dozen);
        _BEGIN_NAMESPACE(bakers) {
            _QUANTITY(dozen,            13.0);
            _QUANTITY(doz,              dozen);
            _QUANTITY(dz,               dozen);
        _END_NAMESPACE}
        _QUANTITY(gross,                12.0*dozen);
        _QUANTITY(gro,                  gross);
        _QUANTITY(quire,                25.0);
        _QUANTITY(quires,               quire);
        _QUANTITY(ream,                 500.0);
        _QUANTITY(reams,                ream);
        _QUANTITY(percent,              1.0/100.0);
        _QUANTITY(proof,                percent/2.0);
        _QUANTITY(karat,                1.0/24.0);
        _QUANTITY(karats,               karat);
        _QUANTITY(mole,                 6.0221367e+23);
        _QUANTITY(moles,                mole);
        _QUANTITY(mol,                  mole);
        _QUANTITY(pi,                   3.14159265358979323846*radians);
        _BEGIN_NAMESPACE(arc) {
            _QUANTITY(degree,           pi/180.0);
            _QUANTITY(degrees,          degree);
            _QUANTITY(minute,           degree/60.0);
            _QUANTITY(minutes,          minute);
            _QUANTITY(min,              minute);
            _QUANTITY(second,           minute/60.0);
            _QUANTITY(seconds,          second);
            _QUANTITY(sec,              second);
            _QUANTITY(grade,            0.9*degrees);
            _QUANTITY(grades,           grade);
            _BEGIN_NAMESPACE(centesimal) {
              _QUANTITY(minute,         grade/100.0);
              _QUANTITY(minutes,        minute);
              _QUANTITY(min,            minute);
              _QUANTITY(second,         grade/10000.0);
              _QUANTITY(seconds,        second);
              _QUANTITY(sec,            second);
              _END_NAMESPACE}
            _END_NAMESPACE}

        // SI units (mks)
        // length
        _QUANTITYu(meter,               1.0,units_pair("m",1));
        _QUANTITY(meters,               meter);
        _QUANTITY(m,                    meter);
        _QUANTITY(kilometer,            1000.0*meters);
        _QUANTITY(kilometers,           kilometer);
        _QUANTITY(km,                   kilometer);
        _QUANTITY(decimeter,            meters/10.0);
        _QUANTITY(decimeters,           decimeter);
        _QUANTITY(dm,                   decimeter);
        _QUANTITY(centimeter,           meters/100.0);
        _QUANTITY(centimeters,          centimeter);
        _QUANTITY(cm,                   centimeter);
        _QUANTITY(millimeter,           meters/1000.0);
        _QUANTITY(millimeters,          millimeter);
        _QUANTITY(mm,                   millimeter);
        _QUANTITY(micron,               meter/1000000.0);
        _QUANTITY(microns,              micron);
        _QUANTITY(um,                   micron);
        _QUANTITY(nanometer,            meter/1000000000.0);
        _QUANTITY(nanometers,           nanometer);
        _QUANTITY(nm,                   nanometer);
        _QUANTITY(decinanometer,        meter/10000000000.0);
        _QUANTITY(decinanometers,       decinanometer);
        _QUANTITY(Angstrom,             decinanometer);
        _QUANTITY(Angstroms,            Angstrom);
        _QUANTITY(Xunit,                1.00202e-13*meters);
        _QUANTITY(Xunits,               Xunit);
        _QUANTITY(Fermi,                meter/1000000000000000.0);
        _QUANTITY(Fermis,               Fermi);
        // area
        _QUANTITY(hectare,              10000.0*meter*meter);
        _QUANTITY(hectares,             hectare);
        _QUANTITY(ha,                   hectare);
        // volume
        _QUANTITY(stere,                meter*meter*meter);
        _QUANTITY(steres,               stere);
        _QUANTITY(liter,                stere/1000.0);
        _QUANTITY(liters,               liter);
        _QUANTITY(l,                    liter);
        _QUANTITY(milliliter,           stere/1000000.0);
        _QUANTITY(milliliters,          milliliter);
        _QUANTITY(ml,                   milliliter);
        _QUANTITY(cc,                   milliliter);
        _BEGIN_NAMESPACE(displacement) {
            _QUANTITY(ton,              stere);
            _QUANTITY(tons,             ton);
            _QUANTITY(t,                ton);
        _END_NAMESPACE}
        // mass
        _QUANTITYu(kilogram,            1.0, units_pair("kg",1));
        _QUANTITY(kilograms,            kilogram);
        _QUANTITY(kg,                   kilogram);
        _QUANTITY(quintal,              100.0*kilograms);
        _QUANTITY(quintals,             quintal);
        _QUANTITY(doppelzentner,                quintal);
        _QUANTITY(doppelzentners,               doppelzentner);
        _QUANTITY(gram,                 kilograms/1000.0);
        _QUANTITY(grams,                gram);
        _QUANTITY(g,                    gram);
        _QUANTITY(milligram,            kilogram/1000000.0);
        _QUANTITY(milligrams,           milligram);
        _QUANTITY(mg,                   milligram);
        _BEGIN_NAMESPACE(metric) { // weight
            _QUANTITY(carat,            gram/5.0);
            _QUANTITY(carats,           carat);
            _QUANTITY(ton,              1000.0*kilograms);
            _QUANTITY(tons,             ton);
            _QUANTITY(t,                ton);
        _END_NAMESPACE}
        // time
        _QUANTITYu(second,              1.0, units_pair("s", 1));
        _QUANTITY(seconds,              second);
        _QUANTITY(sec,                  second);
        _QUANTITY(s,                    second);
        _QUANTITY(millisecond,          second/1000.0);
        _QUANTITY(milliseconds,         millisecond);
        _QUANTITY(ms,                   millisecond);
        _QUANTITY(microsecond,          second/1000000.0);
        _QUANTITY(microseconds,                 microsecond);
        _QUANTITY(us,                   microsecond);
        _QUANTITY(nanosecond,           second/1000000000.0);
        _QUANTITY(nanoseconds,          nanosecond);
        _QUANTITY(ns,                   nanosecond);
        _QUANTITY(picosecond,           second/1000000000000.0);
        _QUANTITY(picoseconds,          picosecond);
        _QUANTITY(minute,               60.0*seconds);
        _QUANTITY(minutes,              minute);
        _QUANTITY(min,                  minute);
        _QUANTITY(hour,                 60.0*minutes);
        _QUANTITY(hours,                hour);
        _QUANTITY(hr,                   hour);
        _QUANTITY(day,                  24.0*hours);
        _QUANTITY(days,                 day);
        _QUANTITY(da,                   day);
        _QUANTITY(week,                 7.0*days);
        _QUANTITY(weeks,                week);
        _QUANTITY(fortnight,            2.0*weeks);
        _QUANTITY(fortnights,           fortnight);
        _QUANTITY(year,                 365.2421896698*days);
        _QUANTITY(years,                year);
        _QUANTITY(yr,                   year);
        _QUANTITY(month,                year/12.0);
        _QUANTITY(months,               month);
        _QUANTITY(mo,                   month);
        _QUANTITY(decade,               10.0*years);
        _QUANTITY(decades,              decade);
        _QUANTITY(century,              100.0*years);
        _QUANTITY(centuries,            century);
        _QUANTITY(millenium,            1000.0*years);
        _QUANTITY(millenia,             millenium);
        // temporal frequency
        _QUANTITY(Hertz,                1.0/second);
        _QUANTITY(Hz,                   Hertz);
        _QUANTITY(kiloHertz,            1000.0*Hertz);
        _QUANTITY(kHz,                  kiloHertz);
        _QUANTITY(megaHertz,            1000000.0*Hertz);
        _QUANTITY(MHz,                  megaHertz);
        _QUANTITY(gigaHertz,            1000000000.0*Hertz);
        _QUANTITY(GHz,                  gigaHertz);
        _QUANTITY(teraHertz,            1000000000000.0*Hertz);
        _QUANTITY(THz,                  teraHertz);
        // spacial frequency
        _QUANTITY(diopter,              1.0/meter);
        _QUANTITY(diopters,             diopter);
        // speed
        _QUANTITY(kph,                  kilometers/hour);
        // radioactivity
        _QUANTITY(Becquerel,            1.0/second);
        _QUANTITY(Becquerels,           Becquerel);
        _QUANTITY(Bq,                   Becquerel);
        _QUANTITY(Rutherford,           1000000.0*Becquerels);
        _QUANTITY(Rutherfords,          Rutherford);
        _QUANTITY(Curie,                3.7e+10*Becquerels);
        _QUANTITY(Curies,               Curie);
        _QUANTITY(Ci,                   Curie);
        // force
        _QUANTITY(Newton,               kilogram*meter/(second*second));
        _QUANTITY(Newtons,              Newton);
        _QUANTITY(N,                    Newton);
        _QUANTITY(dyne,                 Newton/100000.0);
        _QUANTITY(dynes,                dyne);
        _QUANTITY(dyn,                  dyne);
        // pressure
        _QUANTITY(Pascal,               Newton/(meter*meter));
        _QUANTITY(Pascals,              Pascal);
        _QUANTITY(Pa,                   Pascal);
        _QUANTITY(Barie,                Pascal/10.0);
        _QUANTITY(Baries,               Barie);
        _QUANTITY(Barye,                Barie);
        _QUANTITY(Baryes,               Barye);
        _QUANTITY(pieze,                1000.0*Pascals);
        _QUANTITY(piezes,               pieze);
        _QUANTITY(pz,                   pieze);
        _QUANTITY(bar,                  10000.0*Pascals);
        _QUANTITY(bars,                 bar);
        _QUANTITY(Torr,                 133.3224*Pascals);
        _QUANTITY(atmosphere,           760.0*Torr);
        _QUANTITY(atmospheres,          atmosphere);
        _QUANTITY(atm,                  atmosphere);
        // energy
        _QUANTITY(Joule,                Newton*meter);
        _QUANTITY(Joules,               Joule);
        _QUANTITY(J,                    Joule);
        _QUANTITY(erg,                  Joule/10000000.0);
        _QUANTITY(ergs,                 erg);
        _QUANTITY(kiloWatthour,         3600000.0*Joules);
        _QUANTITY(kiloWatthours,        kiloWatthour);
        _QUANTITY(kWh,                  kiloWatthour);
        // power
        _QUANTITY(Watt,                 Joule/second);
        _QUANTITY(Watts,                Watt);
        _QUANTITY(W,                    Watt);
        _QUANTITY(kiloWatt,             1000.0*Watts);
        _QUANTITY(kiloWatts,            kiloWatt);
        _QUANTITY(kW,                   kiloWatt);
        _QUANTITY(megaWatt,             1000000.0*Watts);
        _QUANTITY(megaWatts,            megaWatt);
        _QUANTITY(MW,                   megaWatt);
        _QUANTITY(milliWatt,            Watt/1000.0);
        _QUANTITY(milliWatts,           milliWatt);
        _QUANTITY(mW,                   milliWatt);
        _QUANTITY(microWatt,            Watt/1000000.0);
        _QUANTITY(microWatts,           microWatt);
        _QUANTITY(uW,                   microWatt);
        _QUANTITY(nanoWatt,             Watt/1000000000.0);
        _QUANTITY(nanoWatts,            nanoWatt);
        _QUANTITY(nW,                   nanoWatt);
        _BEGIN_NAMESPACE(dose) { // energy
            _QUANTITY(Gray,             Joule/kilogram);
            _QUANTITY(Grays,            Gray);
            _QUANTITY(Gy,               Gray);
            _QUANTITY(Sievert,          Gray);
            _QUANTITY(Sieverts,         Sievert);
            _QUANTITY(rad,              Gray/100.0);
            _QUANTITY(rads,             rad);
            _QUANTITY(rd,               rad);
        _END_NAMESPACE}
        // electrical current
        _QUANTITYu(Ampere,              1.0, units_pair("A",1));
        _QUANTITY(Amperes,              Ampere);
        _QUANTITY(A,                    Ampere);
        _QUANTITY(Biot,                 10.0*Amperes);
        _QUANTITY(Biots,                Biot);
        _QUANTITY(statAmpere,           Biot * 3.335641e-11); /* == (Biot * cm) / (s * c) */
        _QUANTITY(statAmperes,          statAmpere);
        _QUANTITY(statAmp,              statAmpere);
        _QUANTITY(statA,                statAmpere);
        // electrical potential
        _QUANTITY(Volt,                 Watt/Ampere);
        _QUANTITY(Volts,                Volt);
        _QUANTITY(V,                    Volt);
        _QUANTITY(statVolt,             erg / (statAmp * s));
        _QUANTITY(statVolts,            statVolt);
        _QUANTITY(statV,                statVolt);
        // electrical resistance
        _QUANTITY(Ohm,                  Volt/Ampere);
        _QUANTITY(Ohms,                 Ohm);
        // electrical conductance
        _QUANTITY(mho,                  1.0/Ohm);
        _QUANTITY(mhos,                 mho);
        _QUANTITY(Siemens,              mho);
        _QUANTITY(S,                    Siemens);
        // electrical charge
        _QUANTITY(Coulomb,              Ampere*second);
        _QUANTITY(Coulombs,             Coulomb);
        _QUANTITY(C,                    Coulomb);
        _QUANTITY(statCoulomb,          statAmpere*second);
        _QUANTITY(statCoulombs,                 statCoulomb);
        _QUANTITY(statC,                statCoulomb);
        _QUANTITY(Franklin,             statCoulomb);
        _QUANTITY(Franklins,            Franklin);
        // electrical capacity
        _QUANTITY(Farad,                Coulomb/Volt);
        _QUANTITY(Farads,               Farad);
        _QUANTITY(F,                    Farad);
        // magnetic flux
        _QUANTITY(Weber,                Volt*second);
        _QUANTITY(Webers,               Weber);
        _QUANTITY(Wb,                   Weber);
        _QUANTITY(Maxwell,              Weber/100000000.0);
        _QUANTITY(Maxwells,             Maxwell);
        _QUANTITY(M,                    Maxwell);
        // magnetic field B
        _QUANTITY(Tesla,                Weber/(meter*meter));
        _QUANTITY(Teslas,               Tesla);
        _QUANTITY(T,                    Tesla);
        _QUANTITY(Gauss,                Tesla/10000.0);
        _QUANTITY(gamma,                Tesla/1000000000.0);
        // magnetic field H
        _QUANTITY(Oerstedt,             79.57747*Ampere/meter);
        _QUANTITY(Oerstedts,            Oerstedt);
        _QUANTITY(Oe,                   Oerstedt);
        // magnetic inductivity
        _QUANTITY(Henry,                Weber/Ampere);
        _QUANTITY(Henrys,               Henry);
        _QUANTITY(H,                    Henry);
        _QUANTITY(milliHenry,           Henry/1000.0);
        _QUANTITY(milliHenrys,          milliHenry);
        _QUANTITY(mH,                   milliHenry);
        // temperature
        _QUANTITYu(Kelvin,              1.0,units_pair("K",1));
        _QUANTITY(Kelvins,              Kelvin);
        _QUANTITY(K,                    Kelvin);
        _QUANTITY(milliKelvin,          Kelvin*1e-3);
        _QUANTITY(milliKelvins,                 milliKelvin);
        _QUANTITY(mK,                   milliKelvin);
        _QUANTITY(microKelvin,          Kelvin*1e-6);
        _QUANTITY(microKelvins,                 microKelvin);
        _QUANTITY(uK,                   microKelvin);
        // luminous intensity
        _QUANTITYu(candela,             1.0,units_pair("candela",1));
        _QUANTITY(candelas,             candela);
        _QUANTITY(cd,                   candela);
        _QUANTITY(apostilb,             candelas/meter/meter);
        _QUANTITY(apostilbs,            apostilb);
        _QUANTITY(nit,                  apostilb);
        _QUANTITY(nits,                 nit);
        _QUANTITY(skot,                 apostilb/1000.0);
        _QUANTITY(skots,                skot);
        _QUANTITY(stilb,                10000.0*apostilbs);
        _QUANTITY(stilbs,               stilb);
        _QUANTITY(Blondel,              apostilb/pi);
        _QUANTITY(Blondels,             Blondel);
        _QUANTITY(Lambert,              10000.0*Blondels);
        _QUANTITY(Lamberts,             Lambert);
        // light flux
        _QUANTITY(lumen,                candela*steradian);
        _QUANTITY(lumens,               lumen);
        _QUANTITY(lm,                   lumen);
        // light intensity
        _QUANTITY(lux,                  lumens/meter/meter);
        _QUANTITY(luxes,                lux);
        _QUANTITY(luces,                lux);
        _QUANTITY(lx,                   lux);
        _QUANTITY(nox,                  lux/1000.0);
        _QUANTITY(phot,                 lumens/centimeter/centimeter);
        _QUANTITY(phots,                phot);
        _BEGIN_NAMESPACE(equivalent) {
            _QUANTITY(lux,              unit::lux/pi);
            _QUANTITY(luxes,            lux);
            _QUANTITY(luces,            lux);
            _QUANTITY(lx,               lux);
            _QUANTITY(lumen,            unit::lumen/pi);
            _QUANTITY(lumens,           lumen);
            _QUANTITY(lm,               lumen);
            _QUANTITY(phot,             apostilb/pi);
            _QUANTITY(phots,            phot);
        _END_NAMESPACE}
        // acceleration
        _QUANTITY(Galileo,              centimeters/second/second);
        _QUANTITY(Galileos,             Galileo);
        // standard gravitational acceleration at sea level
        _QUANTITYn(gravity,             9.80665*meters/second/second,"standard gravitational acceleration at sea level");
        // mass
        _QUANTITY(kilohyl,              kilogram*gravity*second*second/meter);
        _QUANTITY(kilohyls,             kilohyl);
        _QUANTITY(hyl,                  kilohyl/1000.0);
        _QUANTITY(hyls,                 hyl);

        // English Units
        // length
        _QUANTITY(inch,                 0.0254*meters);
        _QUANTITY(inches,               inch);
        _QUANTITY(in,                   inch);
        _QUANTITY(mil,                  inch/1000.0);
        _QUANTITY(mils,                 mil);
        _QUANTITY(point,                inch/72.27);
        _QUANTITY(points,               point);
        _QUANTITY(pt,                   point);
        _QUANTITY(bottommeasure,        inch/40.0);
        _QUANTITY(bottommeasures,       bottommeasure);
        _QUANTITY(line,                 inch/12.0);
        _QUANTITY(lines,                line);
        _QUANTITY(pica,                 12.0*points);
        _QUANTITY(picas,                pica);
        _QUANTITY(barleycorn,           inch/3.0);
        _QUANTITY(barleycorns,          barleycorn);
        _QUANTITY(finger,               7.0*inches/8.0);
        _QUANTITY(fingers,              finger);
        _QUANTITY(palm,                 3.0*inches);
        _QUANTITY(palms,                palm);
        _QUANTITY(hand,                 4.0*inches);
        _QUANTITY(hands,                hand);
        _QUANTITY(link,                 7.92*inches);
        _QUANTITY(links,                link);
        _QUANTITY(li,                   link);
        _QUANTITY(span,                 9.0*inches);
        _QUANTITY(spans,                span);
        _QUANTITY(foot,                 12.0*inches);
        _QUANTITY(feet,                 foot);
        _QUANTITY(ft,                   foot);
        _QUANTITY(cubit,                18.0*inches);
        _QUANTITY(cubits,               cubit);
        _QUANTITY(yard,                 3.0*feet);
        _QUANTITY(yards,                yard);
        _QUANTITY(yd,                   yard);
        _QUANTITY(nail,                 yard/16.0);
        _QUANTITY(nails,                nail);
        _QUANTITY(ell,                  45.0*inches);
        _QUANTITY(ells,                 ell);
        _QUANTITY(pace,                 5.0*feet);
        _QUANTITY(paces,                pace);
        _QUANTITY(fathom,               6.0*feet);
        _QUANTITY(fathoms,              fathom);
        _QUANTITY(fm,                   fathom);
        _QUANTITY(rod,                  198.0*inches);
        _QUANTITY(rods,                 rod);
        _QUANTITY(rd,                   rod);
        _QUANTITY(pole,                 rod);
        _QUANTITY(poles,                pole);
        _QUANTITY(p,                    pole);
        _QUANTITY(perch,                rod);
        _QUANTITY(perches,              perch);
        _QUANTITY(rope,                 20.0*feet);
        _QUANTITY(ropes,                rope);
        _QUANTITY(bolt,                 40.0*yards);
        _QUANTITY(bolts,                bolt);
        _QUANTITY(chain,                4.0*rods);
        _QUANTITY(chains,               chain);
        _QUANTITY(ch,                   chain);
        _BEGIN_NAMESPACE(Gunters) {
            _QUANTITY(chain,            unit::chain);
            _QUANTITY(chains,           chain);
        _END_NAMESPACE}
        _BEGIN_NAMESPACE(engineers) {
            _QUANTITY(link,             foot);
            _QUANTITY(links,            link);
            _QUANTITY(chain,            100.0*feet);
            _QUANTITY(chains,           chain);
        _END_NAMESPACE}
        _QUANTITY(skein,                120.*yards);
        _QUANTITY(skeins,               skein);
        _QUANTITY(furlong,              220.*yards);
        _QUANTITY(furlongs,             furlong);
        _QUANTITY(spindle,              14400.*yards);
        _QUANTITY(spindles,             spindle);
        _BEGIN_NAMESPACE(US) {
            _QUANTITY(cable_length,     120.0*fathoms);
            _QUANTITY(cable_lengths,    cable_length);
        _END_NAMESPACE}
        _BEGIN_NAMESPACE(British) {
            _QUANTITY(cable_length,     100.0*fathoms);
            _QUANTITY(cable_lengths,    cable_length);
        _END_NAMESPACE}
        _BEGIN_NAMESPACE(statute) {
            _QUANTITY(mile,             5280.0*feet);
            _QUANTITY(miles,            mile);
            _QUANTITY(mi,               mile);
            _QUANTITY(league,           3.0*miles);
            _QUANTITY(leagues,          league);
        _END_NAMESPACE}
        _BEGIN_NAMESPACE(nautical) {
            _QUANTITY(mile,             1852.*meters);
            _QUANTITY(miles,            mile);
            _QUANTITY(nm,               mile);
            _QUANTITY(league,           3.0*miles);
            _QUANTITY(leagues,          league);
        _END_NAMESPACE}
        _ALIAS_NAMESPACE(marine, nautical);
        _BEGIN_NAMESPACE(geodetic) {
            _QUANTITY(foot,             (1200.0/3937.0)*meters);
            _QUANTITY(feet,             foot);
            _QUANTITY(ft,               foot);
        _END_NAMESPACE}
        _BEGIN_NAMESPACE(geographical) {
            _QUANTITY(mile,             nautical::mile);
            _QUANTITY(miles,            mile);
            _QUANTITY(mi,               mile);
        _END_NAMESPACE}
        _QUANTITY(parasang,             3.5*statute::miles);
        _QUANTITY(parasangs,            parasang);
        _QUANTITY(arpentcan,            27.52*statute::miles);
        _QUANTITY(arpentcans,           arpentcan);
        _QUANTITY(arpentlin,            191.835*feet);
        _QUANTITY(arpentlins,           arpentlin);
        _QUANTITY(astronomical_unit,    1.49597871e11*meters);
        _QUANTITY(astronomical_units,   astronomical_unit);
        _QUANTITY(AU,                   astronomical_unit);
        _QUANTITY(lightyear,            9.4605e15*meters);
        _QUANTITY(lightyears,           lightyear);
        _QUANTITY(ly,                   lightyear);
        _QUANTITY(parsec,               AU*radians/arc::second);
        _QUANTITY(parsecs,              parsec);
        _QUANTITY(pc,                   parsec);
        // area
        _QUANTITY(barn,                 1.0e-28*meter*meter);
        _QUANTITY(barns,                barn);
        _QUANTITY(b,                    barn);
        _QUANTITY(circular_inch,        0.25*pi*inch*inch);
        _QUANTITY(circular_inches,      circular_inch);
        _QUANTITY(circular_mil,         0.25*pi*mil*mil);
        _QUANTITY(circular_mils,        circular_mil);
        _QUANTITY(sabin,                foot*foot);
        _QUANTITY(sabins,               sabin);
        _QUANTITY(square,               100.0*sabin);
        _QUANTITY(squares,              square);
        _QUANTITY(are,                  100.0*meter*meter);
        _QUANTITY(ares,                 are);
        _QUANTITY(a,                    are);
        _QUANTITY(rood,                 40.0*rod*rod);
        _QUANTITY(roods,                rood);
        _QUANTITY(ro,                   rood);
        _QUANTITY(acre,                 4.0*roods);
        _QUANTITY(acres,                acre);
        _QUANTITY(section,              statute::mile*statute::mile);
        _QUANTITY(sections,             section);
        _QUANTITY(homestead,            section/4.0);
        _QUANTITY(homesteads,           homestead);
        _QUANTITY(township,             36.0*sections);
        _QUANTITY(townships,            township);
        // volume
        _QUANTITY(minim,                6.161152e-8*(m*m*m));
        _QUANTITY(minims,               minim);
        _QUANTITY(drop,                 0.03*cc);
        _QUANTITY(drops,                drop);
        _QUANTITY(teaspoon,             4.928922*cc);
        _QUANTITY(teaspoons,            teaspoon);
        _QUANTITY(tablespoon,           3.0*teaspoons);
        _QUANTITY(tablespoons,          tablespoon);
        _OPEN_NAMESPACE(1,US) {
            _BEGIN_NAMESPACE(liquid) {
                _QUANTITY(dram,         60.0*minims);
                _QUANTITY(drams,        dram);
                _QUANTITY(dr,           dram);
                _QUANTITY(ounce,        8.0*drams);
                _QUANTITY(ounces,       ounce);
                _QUANTITY(oz,           ounce);
                _QUANTITY(gill,         4.0*ounces);
                _QUANTITY(gills,        gill);
                _QUANTITY(gl,           gill);
                _QUANTITY(pint,         4.0*gills);
                _QUANTITY(pints,        pint);
                _QUANTITY(pt,           pint);
                _QUANTITY(quart,        2.0*pints);
                _QUANTITY(quarts,       quart);
                _QUANTITY(qt,           quart);
                _QUANTITY(magnum,       2.0*quarts);
                _QUANTITY(magnums,      magnum);
                _QUANTITY(gallon,       4.0*quarts);
                _QUANTITY(gallons,      gallon);
                _QUANTITY(gal,          gallon);
            _END_NAMESPACE}
            _BEGIN_NAMESPACE(dry) {
                _QUANTITY(pint,         550.61047*cc);
                _QUANTITY(pints,        pint);
                _QUANTITY(pt,           pint);
                _QUANTITY(quart,        2.0*pints);
                _QUANTITY(quarts,       quart);
                _QUANTITY(qt,           quart);
            _END_NAMESPACE}
            _QUANTITY(peck,             8.0*dry::quarts);
            _QUANTITY(pecks,            peck);
            _QUANTITY(pk,               peck);
            _QUANTITY(bushel,           4.0*pecks);
            _QUANTITY(bushels,          bushel);
            _QUANTITY(bu,               bushel);
            _QUANTITY(barrel,           31.5*liquid::gallons);
            _QUANTITY(barrels,          barrel);
            _QUANTITY(bbl,              barrel);
            _QUANTITY(bl,               barrel);
        _CLOSE_NAMESPACE(1)}
        _OPEN_NAMESPACE(1,British) {
            _BEGIN_NAMESPACE(fluid) {
              _QUANTITY(drachm,         60.0*minims);
              _QUANTITY(drachms,        drachm);
              _QUANTITY(dr,             drachm);
              _QUANTITY(ounce,          8.0*drachms);
              _QUANTITY(ounces,         ounce);
              _QUANTITY(oz,             ounce);
              _QUANTITY(gill,           5.0*ounces);
              _QUANTITY(gills,          gill);
              _QUANTITY(gi,             gill);
              _QUANTITY(pint,           4.0*gills);
              _QUANTITY(pints,          pint);
              _QUANTITY(pt,             pint);
              _QUANTITY(quart,          2.0*pints);
              _QUANTITY(quarts,         quart);
              _QUANTITY(qt,             quart);
              _QUANTITY(gallon,         4.0*quarts);
              _QUANTITY(gallons,        gallon);
              _QUANTITY(gal,            gallon);
              _END_NAMESPACE}
            _QUANTITY(peck,             2.0*fluid::gallons);
            _QUANTITY(pecks,            peck);
            _QUANTITY(pk,               peck);
            _QUANTITY(bushel,           4.0*pecks);
            _QUANTITY(bushels,          bushel);
            _QUANTITY(bu,               bushel);
            _QUANTITY(barrel,           36.0*fluid::gallons);
            _QUANTITY(barrels,          barrel);
            _QUANTITY(bbl,              barrel);
            _QUANTITY(bl,               barrel);
        _CLOSE_NAMESPACE(1)}
        _QUANTITY(noggin,               2.0*US::liquid::ounces);
        _QUANTITY(noggins,              noggin);
        _QUANTITY(cup,                  8.0*US::liquid::ounces);
        _QUANTITY(cups,                 cup);
        _QUANTITY(fifth,                US::liquid::gallon/5.0);
        _QUANTITY(fifths,               fifth);
        _QUANTITY(jeroboam,             4.0*fifths);
        _QUANTITY(jeroboams,            jeroboam);
        _QUANTITY(firkin,               9.0*US::liquid::gallons);
        _QUANTITY(firkins,              firkin);
        _QUANTITY(kilderkin,            18.0*US::liquid::gallons);
        _QUANTITY(kilderkins,           kilderkin);
        _QUANTITY(strike,               2.0*US::bushels);
        _QUANTITY(strikes,              strike);
        _QUANTITY(sack,                 3.0*US::bushels);
        _QUANTITY(sacks,                sack);
        _QUANTITY(coomb,                4.0*US::bushels);
        _QUANTITY(coombs,               coomb);
        _QUANTITY(seam,                 8.0*US::bushels);
        _QUANTITY(seams,                seam);
        _QUANTITY(wey,                  40.0*US::bushels);
        _QUANTITY(weys,                 wey);
        _QUANTITY(last,                 80.0*US::bushels);
        _QUANTITY(lasts,                last);
        _QUANTITY(register_ton,         100.0*(ft*ft*ft));
        _QUANTITY(register_tons,        register_ton);
        _QUANTITY(register_tn,          register_ton);
        _QUANTITY(cord,                 128.0*(ft*ft*ft));
        _QUANTITY(cords,                cord);
        _QUANTITY(cordfoot,             cord);
        _QUANTITY(cordfeet,             cordfoot);
        _QUANTITY(boardfoot,            144.0*inch*inch*inch);
        _QUANTITY(boardfeet,            boardfoot);
        _QUANTITY(timberfoot,           foot*foot*foot);
        _QUANTITY(timberfeet,           timberfoot);
        _QUANTITY(hogshead,             2.0*US::barrels);
        _QUANTITY(hogsheads,            hogshead);
        _QUANTITY(pipe,                 4.0*US::barrels);
        _QUANTITY(pipes,                pipe);
        _QUANTITY(tun,                  8.0*US::barrels);
        _QUANTITY(tuns,                 tun);
        // mass
        _QUANTITY(grain,                0.06479891*grams);
        _QUANTITY(grains,               grain);
        _QUANTITY(gr,                   grain);
        _QUANTITY(pennyweight,          24.0*grains);
        _QUANTITY(dwt,                  pennyweight);
        _BEGIN_NAMESPACE(apothecary) { // weight
            _QUANTITY(scruple,          20.0*grains);
            _QUANTITY(scruples,         scruple);
            _QUANTITY(s,                scruple);
            _QUANTITY(dram,             3.0*scruples);
            _QUANTITY(drams,            dram);
            _QUANTITY(dr,               dram);
            _QUANTITY(ounce,            8.0*drams);
            _QUANTITY(ounces,           ounce);
            _QUANTITY(oz,               ounce);
            _QUANTITY(pound,            12.0*ounces);
            _QUANTITY(pounds,           pound);
            _QUANTITY(lb,               pound);
        _END_NAMESPACE}
        _ALIAS_NAMESPACE(troy, apothecary);
        _ALIAS_NAMESPACE(ap, apothecary);
        _ALIAS_NAMESPACE(t, apothecary);
        _BEGIN_NAMESPACE(avoirdupois) { // weight
            _QUANTITY(pound,            7000.0*grains);
            _QUANTITY(pounds,           pound);
            _QUANTITY(lb,               pound);
            _QUANTITY(ounce,            pound/16.0);
            _QUANTITY(ounces,           ounce);
            _QUANTITY(oz,               ounce);
            _QUANTITY(dram,             ounce/16.0);
            _QUANTITY(drams,            dram);
            _QUANTITY(dr,               dram);
        _END_NAMESPACE}
        _ALIAS_NAMESPACE(avdp, avoirdupois);
        _ALIAS_NAMESPACE(av, avoirdupois);
        _QUANTITY(stone,                14.0*avoirdupois::pounds);
        _QUANTITY(stones,               stone);
        _QUANTITY(st,                   stone);
        _OPEN_NAMESPACE(2,US) { // short
            _QUANTITY(hundredweight,    100.0*avoirdupois::pounds);
            _QUANTITY(cwt,              hundredweight);
            _QUANTITY(quarter,          hundredweight/4.0);
            _QUANTITY(quarters,         quarter);
            _QUANTITY(qr,               quarter);
            _QUANTITY(ton,              20.0*hundredweight);
            _QUANTITY(tons,             ton);
            _QUANTITY(tn,               ton);
            _QUANTITY(deadweight,       ton);
        _CLOSE_NAMESPACE(2)}
        _OPEN_NAMESPACE(2,British) { // long
            _QUANTITY(hundredweight,    112.0*avoirdupois::pounds);
            _QUANTITY(cwt,              hundredweight);
            _QUANTITY(quarter,          hundredweight/4.0);
            _QUANTITY(quarters,         quarter);
            _QUANTITY(qr,               quarter);
            _QUANTITY(ton,              20.0*hundredweight);
            _QUANTITY(tons,             ton);
            _QUANTITY(tn,               ton);
        _CLOSE_NAMESPACE(2)}
        _ALIAS_NAMESPACE(English, British);
        _ALIAS_NAMESPACE(Imperial, British);
        _QUANTITY(crith,                0.0906*grams);
        _QUANTITY(criths,               crith);
        _QUANTITY(bag,                  94.0*avoirdupois::pounds);
        _QUANTITY(bags,                 bag);
        _QUANTITY(cental,               100.0*avoirdupois::pounds);
        _QUANTITY(centals,              cental);
        _QUANTITY(weymass,              252.0*avoirdupois::pounds);
        // rate
        _QUANTITY(mgd,                  1000000.0*US::liquid::gallons/day);
        _QUANTITY(cfs,                  foot*foot*foot/second);
        _QUANTITY(minersinch,           1.5*foot*foot*foot/minute);
        _QUANTITY(mpg,                  statute::miles/US::liquid::gallon);
        // speed
        _QUANTITY(mph,                  statute::miles/hour);
        _QUANTITY(knot,                 nautical::miles/hour);
        _QUANTITY(knots,                knot);
        _BEGIN_NAMESPACE(admiralty) {
            _QUANTITY(knot,             6980.0*feet/hour);
            _QUANTITY(knots,            knot);
        _END_NAMESPACE}
        // force
        _QUANTITY(poundal,              avdp::pound*foot/(second*second));
        _QUANTITY(poundals,             poundal);
        _QUANTITY(pdl,                  poundal);
        _QUANTITY(lbf,                  avoirdupois::pound*gravity);
        // pressure
        _QUANTITY(psi,                  lbf/(inch*inch));
        // energy
        _QUANTITY(calorie,              4.1868*Joules);
        _QUANTITY(calories,             calorie);
        _QUANTITY(cal,                  calorie);
        _QUANTITY(kilocalorie,          1000.0*calories);
        _QUANTITY(kilocalories,         kilocalorie);
        _QUANTITY(kcal,                 kilocalorie);
        _QUANTITY(Frigorie,             kilocalorie);
        _QUANTITY(Frigories,            Frigorie);
        _QUANTITY(Btu,                  1055.06*Joules);
        _QUANTITY(therm,                10000.0*Btu);
        _QUANTITY(therms,               therm);
        _QUANTITY(thermie,              1000000.0*calories);
        _QUANTITY(thermies,             thermie);
        // power
        _QUANTITY(horsepower,           735.49875*Watts);
        _QUANTITY(HP,                   horsepower);
        // electrical current
        _QUANTITY(Gilbert,              0.795775*Amperes);
        _QUANTITY(Gilberts,             Gilbert);
        // temperature
        _QUANTITY(Rankin,               1.8*Kelvins);
        _QUANTITY(Rankins,              Rankin);
        _QUANTITY(R,                    Rankin);
        // luminous intensity
        _QUANTITY(candle,               1.02*candelas);
        _QUANTITY(candles,              candle);
        _BEGIN_NAMESPACE(Hefner) {
            _QUANTITY(candle,           0.9*unit::candles);
            _QUANTITY(candles,          candle);
        _END_NAMESPACE}
        // light intensity
        _QUANTITY(foot_candle,          lumens/foot/foot);
        _QUANTITY(foot_candles,         foot_candle);
        _QUANTITY(fc,                   foot_candle);
        _QUANTITY(foot_Lambert,         candelas/foot/foot/pi);
        _QUANTITY(foot_Lamberts,        foot_Lambert);
        _OPEN_NAMESPACE(1,equivalent) {
            _QUANTITY(foot_candle,      unit::foot_candle/pi);
            _QUANTITY(foot_candles,     foot_candle);
            _QUANTITY(fc,               foot_candle);
        _CLOSE_NAMESPACE(1)}
    _END_NAMESPACE}
    _ALIAS_NAMESPACE(units, unit);
    // ####   END OF UNIT CREATION #### #

    // #### BEGIN OF CONSTANT CREATION #### #
    _BEGIN_NAMESPACE(constant) {
        /* These using clauses will import these symbols into the constant
         * namespace, but oh well... */
        using unit::pi;
        using unit::m;
        using unit::s;
        using unit::J;
        using unit::C;
        using unit::V;
        using unit::kg;
        using unit::F;
        using unit::K;
        using unit::A;
        using unit::barns;
        using unit::T;
        using unit::rad;
        using unit::W;
        using unit::N;
        _QUANTITYn(c,                 2.99792458e8*m/s,            "speed of light");
        _QUANTITYn(Mach,              331.46*m/s,                  "speed of sound");
        _QUANTITYn(h,                 6.6260755e-34*J*s,           "Planck constant");
        _QUANTITYn(h_bar,             h/(2.0*pi),                  "Plank constant");
        _QUANTITYn(g,                 unit::gravity,               "standard gravitational acceleration at sea level");
        _QUANTITYn(e,                 1.60217733e-19*C,            "electron charge");
        _QUANTITYn(eV,                e*V,                         "electron Volt");
        _QUANTITYn(keV,               1000.0*eV,                   "kilo-electron Volt");
        _QUANTITYn(MeV,               1000000.0*eV,                "Mega-electron Volt");
        _QUANTITYn(GeV,               1000000000.0*eV,             "Giga-electron Volt");
        _QUANTITYn(Rydberg,           13.6054*eV,                  "Rydberg energy");
        _QUANTITY(Rydbergs,           Rydberg);
        _QUANTITYn(Hartree,           2*Rydberg,                   "Atomic energy unit");
        _QUANTITY(Hartrees,           Hartree);
        _QUANTITYn(m_e,               9.1093897e-31*kg,            "electron mass");
        _QUANTITYn(m_P,               1.6726231e-27*kg,            "proton mass");
        _QUANTITYn(m_D,               1875.61339*MeV/(c*c),        "deuteron mass");
        _QUANTITYn(atomic_mass_unit,  1.6605402e-27*kg,            "unified atomic mass unit");
        _QUANTITY(atomic_mass_units,  atomic_mass_unit);
        _QUANTITY(amu,                atomic_mass_unit);
        _QUANTITY(Dalton,             atomic_mass_unit);
        _QUANTITY(Daltons,            Dalton);
        _QUANTITYn(epsilon,           8.854187817e-12*F/m,         "permittivity of free space");
        _QUANTITYn(mu,                12.566370614e-7*N/(A*A),     "permeability of free space");
        _QUANTITYun(alpha,            1.0/137.0359895, units_map(),"fine-structure constant");
        _QUANTITYn(r_e,               2.81794092e-15*m,            "classical electron radius");
        _QUANTITYn(lambda_bar,        3.86159323e-13*m,            "electron Compton wavelength");
        _QUANTITYn(a_0,               0.529177249e-10*m,           "Bohr radius");
        _QUANTITYn(lambda_1eV,        1.23984244e-6*m,             "wavelength of 1 eV/c particle");
        _QUANTITYn(sigma_0,           0.66524616*barns,            "Thomson cross section");
        _QUANTITYn(mu_B,              5.78838263e-11*MeV/T,        "Bohr magneton");
        _QUANTITYn(mu_N,              3.15245166e-14*MeV/T,        "nuclear magneton");
        _QUANTITYn(E_M_e,             1.75881962e11*C/kg*(rad/(s*T)), "electron cyclotron frequency/field");
        _QUANTITYn(E_M_P,             9.5788309e7*C/kg*(rad/(s*T)),"proton cyclotron frequency/field");
        _QUANTITYn(G,                 6.67259e-11*m*m*m/(kg*s*s),  "gravitational constant");
        _QUANTITYun(N_A,              6.0221367e23, units_map(),   "Avogadro's constant");
        _QUANTITYn(K_B,               1.380658e-23*J/K,            "Boltzmann constant");
        _QUANTITYn(V_molar,           2.897756e-3*m*K,             "molar volume, ideal gas at standard temperature and pressure");
        _QUANTITYn(sigma_SB,          5.67051e-8*W/(m*m*K*K*K*K),  "Stefan-Boltzmann constant");
    _END_NAMESPACE}
    _ALIAS_NAMESPACE(constants, constant);
    // ####   END OF CONSTANT CREATION #### #


    // #### BEGIN OF ELEMENT CREATION #### #
    // FIXME:  finish filling out this periodic table data
    /* This data is taken from physics.nist.gov. */
#define _ELEMENT(name,sym,n,m,i) \
    _BEGIN_NAMESPACE(name) { \
        _QUANTITYn(number,      n,                 "atomic number of "     #name); \
        _QUANTITYn(mass,        m * constant::amu, "atomic mass of "       #name); \
        _QUANTITYn(ionization,  i * constant::eV,  "ionization energy of " #name); \
    _END_NAMESPACE} \
    _ALIAS_NAMESPACE(sym, name);

    /** Periodic table information.
     * @see http://physics.nist.gov/PhysRefData/Elements/index.html
     */
    _BEGIN_NAMESPACE(element) {
        //       long-name    abrv.   n        mass       outer-electron ionization (eV)
        _ELEMENT(hydrogen,      H,    1,      1.00794,      13.5984 );
        _ELEMENT(helium,        He,   2,      4.002602,     24.5874 );
        _ELEMENT(lithium,       Li,   3,      6.941,         5.3917 );
        _ELEMENT(beryllium,     Be,   4,      9.012182,      9.3227 );
        _ELEMENT(boron,          B,   5,     10.812,         8.2980 );
        _ELEMENT(carbon,         C,   6,      12.0107,      11.2603 );
        _ELEMENT(nitrogen,       N,   7,      14.0067,      14.5341 );
        _ELEMENT(oxygen,         O,   8,      15.9994,      13.6181 );
        _ELEMENT(fluorine,       F,   9,      18.9984032,   17.4228 );
        _ELEMENT(neon,          Ne,  10,      20.1797,      21.5645 );
        _ELEMENT(sodium,        Na,  11,      22.989770,     5.1391 );
        _ELEMENT(magnesium,     Mg,  12,      24.3051,       7.6462 );
        _ELEMENT(aluminium,     Al,  13,      26.981538,     5.9858 );
        _ELEMENT(silicon,       Si,  14,      28.0855,       8.1517 );
        _ELEMENT(phosphorus,     P,  15,      30.973761,    10.4867 );
        _ELEMENT(sulfur,         S,  16,      32.065,       10.3600 );
        _ELEMENT(chlorine,      Cl,  17,      35.453,       12.9676 );
        _ELEMENT(argon,         Ar,  18,      39.948,       15.7596 );
        _ELEMENT(potassium,      K,  19,      39.0983,       4.3407 );
        _ELEMENT(calcium,       Ca,  20,      40.078,        6.1132 );
        _ELEMENT(scandium,      Sc,  21,      44.955911,     6.5615 );
        _ELEMENT(titanium,      Ti,  22,      47.867,        6.8281 );
        _ELEMENT(vanadium,       V,  23,      50.9415,       6.7462 );
        _ELEMENT(chromium,      Cr,  24,      51.9961,       6.7665 );
        _ELEMENT(manganese,     Mn,  25,      54.9380499,    7.4340 );
        _ELEMENT(iron,          Fe,  26,      55.845,        7.9024 );
        _ELEMENT(cobalt,        Co,  27,      58.9332009,    7.8810 );
        _ELEMENT(nickel,        Ni,  28,      58.6934,       7.6398 );
        _ELEMENT(copper,        Cu,  29,      63.546,        7.7264 );
        _ELEMENT(zinc,          Zn,  30,      65.409,        9.3942 );
        _ELEMENT(krypton,       Kr,  36,      83.798,       13.9996 );
        _ELEMENT(rubidium,      Rb,  37,      85.4678,       4.1771 );
        _ELEMENT(xenon,         Xe,  54,     131.293,       12.1298 );
        _ELEMENT(cesium,        Cs,  55,     132.90545,      3.8939 );
        _ELEMENT(mercury,       Hg,  80,     200.59,        10.4375 );
        _ELEMENT(francium,      Fr,  87,     223,            4.0727 );
    _END_NAMESPACE}
    _ALIAS_NAMESPACE(elements, element);
    // ####   END OF ELEMENT CREATION #### #
_END_NAMESPACE}


/* now do some cleanup for the macros used internally here. */
#undef PHYSICAL_QUANTITY_CLASS
#undef _QUANTITY
#undef _QUANTITYu
#undef _QUANTITYn
#undef _QUANTITYun
#undef _OPEN_NAMESPACE
#undef _CLOSE_NAMESPACE
#undef _ALIAS_NAMESPACE
#undef _BEGIN_NAMESPACE
#undef _END_NAMESPACE
#undef _ELEMENT



#endif // PHYSICAL_DATA_H
