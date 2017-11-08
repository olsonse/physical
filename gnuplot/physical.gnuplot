#** \file
#* A multitude of constants (mks where applicable) organized into a
#* bunch of namespaces.
#* */

#namespace physical {
#    namespace unit { # conversion factor
                     radian = 1.0;
                     radians = radian;
                     rad = radian;
                     steradian = 1.0;
                     steradians = steradian;
                     sr = steradian;
                     dollar = 1.0;
                     dollars = dollar;
                     cent = dollar/100.0;
                     cents = cent;
                     dozen = 12.0;
                     doz = dozen;
                     dz = dozen;
#        namespace bakers {
                  bakers_dozen = 13.0;
                  bakers_doz = bakers_dozen;
                  bakers_dz = bakers_dozen;
#        }
                     gross = 12.0*dozen;
                     gro = gross;
                     quire = 25.0;
                     quires = quire;
                     ream = 500.0;
                     reams = ream;
                     percent = 1.0/100.0;
                     proof = percent/2.0;
                     karat = 1.0/24.0;
                     karats = karat;
                     mole = 6.0221367e+23;
                     moles = mole;
                     mol = mole;
#                    pi = 3.14159265358979323846*radians;
#        namespace arc {
                     arc_degree = pi/180.0;
                     arc_degrees = arc_degree;
                     arc_minute = arc_degree/60.0;
                     arc_minutes = arc_minute;
                     arc_min = arc_minute;
                     arc_second = arc_minute/60.0;
                     arc_seconds = arc_second;
                     arc_sec = arc_second;
                     arc_grade = 0.9*arc_degrees;
                     arc_grades = arc_grade;
#            namespace centesimal {
            arc_centesimal_minute = arc_grade/100.0;
            arc_centesimal_minutes = arc_centesimal_minute;
            arc_centesimal_min = arc_centesimal_minute;
            arc_centesimal_second = arc_grade/10000.0;
            arc_centesimal_seconds = arc_centesimal_second;
            arc_centesimal_sec = arc_centesimal_second;
#              }
#            }

        # SI units (mks)
        # length
                     meter = 1.0;
                     meters = meter;
                     m = meter;
                     kilometer = 1000.0*meters;
                     kilometers = kilometer;
                     km = kilometer;
                     decimeter = meters/10.0;
                     decimeters = decimeter;
                     dm = decimeter;
                     centimeter = meters/100.0;
                     centimeters = centimeter;
                     cm = centimeter;
                     millimeter = meters/1000.0;
                     millimeters = millimeter;
                     mm = millimeter;
                     micron = meter/1000000.0;
                     microns = micron;
                     nanometer = meter/1000000000.0;
                     nanometers = nanometer;
                     nm = nanometer;
                     decinanometer = meter/10000000000.0;
                     decinanometers = decinanometer;
                     Angstrom = decinanometer;
                     Angstroms = Angstrom;
                     Xunit = 1.00202e-13*meters;
                     Xunits = Xunit;
                     Fermi = meter/1000000000000000.0;
                     Fermis = Fermi;
        # area
                     hectare = 10000.0*meter*meter;
                     hectares = hectare;
                     ha = hectare;
        # volume
                     stere = meter*meter*meter;
                     steres = stere;
                     liter = stere/1000.0;
                     liters = liter;
                     l = liter;
                     milliliter = stere/1000000.0;
                     milliliters = milliliter;
                     ml = milliliter;
                     cc = milliliter;
#        namespace displacement {
            displacement_ton = stere;
            displacement_tons = displacement_ton;
            displacement_t = displacement_ton;
#        }
        # mass
                     kilogram = 1.0;
                     kilograms = kilogram;
                     kg = kilogram;
                     quintal = 100.0*kilograms;
                     quintals = quintal;
                     doppelzentner = quintal;
                     doppelzentners = doppelzentner;
                     gram = kilograms/1000.0;
                     grams = gram;
                     g = gram;
                     milligram = kilogram/1000000.0;
                     milligrams = milligram;
                     mg = milligram;
#        namespace metric { # weight
                  metric_carat = gram/5.0;
                  metric_carats = metric_carat;
                  metric_ton = 1000.0*kilograms;
                  metric_tons = metric_ton;
                  metric_t = metric_ton;
#        }
        # time
                     second = 1.0;
                     seconds = second;
                     sec = second;
                     s = second;
                     millisecond = second/1000.0;
                     milliseconds = millisecond;
                     ms = millisecond;
                     microsecond = second/1000000.0;
                     microseconds = microsecond;
                     us = microsecond;
                     nanosecond = second/1000000000.0;
                     nanoseconds = nanosecond;
                     picosecond = second/1000000000000.0;
                     picoseconds = picosecond;
                     minute = 60.0*seconds;
                     minutes = minute;
#                    min = minute;
                     hour = 60.0*minutes;
                     hours = hour;
                     hr = hour;
                     day = 24.0*hours;
                     days = day;
                     da = day;
                     week = 7.0*days;
                     weeks = week;
                     fortnight = 2.0*weeks;
                     fortnights = fortnight;
                     year = 365.2421896698*days;
                     years = year;
                     yr = year;
                     month = year/12.0;
                     months = month;
                     mo = month;
                     decade = 10.0*years;
                     decades = decade;
                     century = 100.0*years;
                     centuries = century;
                     millenium = 1000.0*years;
                     millenia = millenium;
        # temporal frequency
                     Hertz = 1.0/second;
                     Hz = Hertz;
                     kiloHertz = 1000.0*Hertz;
                     kHz = kiloHertz;
                     megaHertz = 1000000*Hertz;
                     MHz = megaHertz;
                     gigaHertz = 1000000000.0*Hertz;
                     GHz = gigaHertz;
                     teraHertz = 1000000000000.0*Hertz;
                     THz = teraHertz;
        # spacial frequency
                     diopter = 1.0/meter;
                     diopters = diopter;
        # speed
                     kph = kilometers/hour;
        # radioactivity
                     Becquerel = 1.0/second;
                     Becquerels = Becquerel;
                     Bq = Becquerel;
                     Rutherford = 1000000.0*Becquerels;
                     Rutherfords = Rutherford;
                     Curie = 3.7e+10*Becquerels;
                     Curies = Curie;
                     Ci = Curie;
        # force
                     Newton = kilogram*meter/(second*second);
                     Newtons = Newton;
                     N = Newton;
                     dyne = Newton/100000.0;
                     dynes = dyne;
                     dyn = dyne;
        # pressure
                     Pascal = Newton/(meter*meter);
                     Pascals = Pascal;
                     Pa = Pascal;
                     Barie = Pascal/10.0;
                     Baries = Barie;
                     Barye = Barie;
                     Baryes = Barye;
                     pieze = 1000.0*Pascals;
                     piezes = pieze;
                     pz = pieze;
                     bar = 10000.0*Pascals;
                     bars = bar;
                     Torr = 133.3224*Pascals;
                     atmosphere = 760.0*Torr;
                     atmospheres = atmosphere;
                     atm = atmosphere;
        # energy
                     Joule = Newton*meter;
                     Joules = Joule;
                     J = Joule;
                     erg = Joule/10000000.0;
                     ergs = erg;
                     kiloWatthour = 3600000.0*Joules;
                     kiloWatthours = kiloWatthour;
                     kWh = kiloWatthour;
        # power
                     Watt = Joule/second;
                     Watts = Watt;
                     W = Watt;
                     kiloWatt = 1000.0*Watts;
                     kiloWatts = kiloWatt;
                     kW = kiloWatt;
                     megaWatt = 1000000.0*Watts;
                     megaWatts = megaWatt;
                     MW = megaWatt;
                     milliWatt = Watt/1000.0;
                     milliWatts = milliWatt;
                     mW = milliWatt;
                     microWatt = Watt/1000000.0;
                     microWatts = microWatt;
                     uW = microWatt;
#       namespace dose { # energy
                    dose_Gray = Joule/kilogram;
                    dose_Grays = dose_Gray;
                    dose_Gy = dose_Gray;
                    dose_Sievert = dose_Gray;
                    dose_Sieverts = dose_Sievert;
                    dose_rad = dose_Gray/100.0;
                    dose_rads = dose_rad;
                    dose_rd = dose_rad;
#       }
        # electrical current
                     Ampere = 1.0;
                     Amperes = Ampere;
                     A = Ampere;
                     Biot = 10.0*Amperes;
                     Biots = Biot;
        # electrical potential
                     Volt = Watt/Ampere;
                     Volts = Volt;
                     V = Volt;
        # electrical resistance
                     Ohm = Volt/Ampere;
                     Ohms = Ohm;
        # electrical conductance
                     mho = 1.0/Ohm;
                     mhos = mho;
                     Siemens = mho;
                     S = Siemens;
        # elsectrical charge
                     Coulomb = Ampere*second;
                     Coulombs = Coulomb;
                     C = Coulomb;
                     Franklin = 3.33564e-10*Coulombs;
                     Franklins = Franklin;
        # electrical capacity
                     Farad = Coulomb/Volt;
                     Farads = Farad;
                     F = Farad;
        # magnetic flux
                     Weber = Volt*second;
                     Webers = Weber;
                     Wb = Weber;
                     Maxwell = Weber/100000000.0;
                     Maxwells = Maxwell;
                     M = Maxwell;
        # magnetic field B
                     Tesla = Weber/(meter*meter);
                     Teslas = Tesla;
                     T = Tesla;
                     Gauss = Tesla/10000.0;
                     gamma = Tesla/1000000000.0;
        # magnetic field H
                     Oerstedt = 79.57747*Ampere/meter;
                     Oerstedts = Oerstedt;
                     Oe = Oerstedt;
        # magnetic inductivity
                     Henry = Weber/Ampere;
                     Henrys = Henry;
                     H = Henry;
                     milliHenry = Henry/1000.0;
                     milliHenrys = milliHenry;
                     mH = milliHenry;
        # temperature
                     Kelvin = 1.0;
                     Kelvins = Kelvin;
                     K = Kelvin;
                     milliKelvin = Kelvin / 1000.0;
                     milliKelvins = milliKelvin;
                     mK = milliKelvin;
                     microKelvin = Kelvin / 1000000.0;
                     microKelvins = microKelvin;
                     uK = microKelvin;
        # luminous intensity
                     candela = 1.0;
                     candelas = candela;
                     cd = candela;
                     apostilb = candelas/meter/meter;
                     apostilbs = apostilb;
                     nit = apostilb;
                     nits = nit;
                     skot = apostilb/1000.0;
                     skots = skot;
                     stilb = 10000.0*apostilbs;
                     stilbs = stilb;
                     Blondel = apostilb/pi;
                     Blondels = Blondel;
                     Lambert = 10000.0*Blondels;
                     Lamberts = Lambert;
        # light flux
                     lumen = candela*steradian;
                     lumens = lumen;
                     lm = lumen;
        # light intensity
                     lux = lumens/meter/meter;
                     luxes = lux;
                     luces = lux;
                     lx = lux;
                     nox = lux/1000.0;
                     phot = lumens/centimeter/centimeter;
                     phots = phot;
#       namespace equivalent {
#             equivalent_lux = unit_lux/pi;
              equivalent_lux = lux/pi;
              equivalent_luxes = equivalent_lux;
              equivalent_luces = equivalent_lux;
              equivalent_lx = equivalent_lux;
#             equivalent_lumen = unit_lumen/pi;
              equivalent_lumen = lumen/pi;
              equivalent_lumens = equivalent_lumen;
              equivalent_lm = equivalent_lumen;
              equivalent_phot = apostilb/pi;
              equivalent_phots = equivalent_phot;
#       }
        # acceleration
                     Galileo = centimeters/second/second;
                     Galileos = Galileo;
        # standard gavitational acceleration at sea level
                     gravity = 9.80665*meters/second/second;
        # mass
                     kilohyl = kilogram*gravity*second*second/meter;
                     kilohyls = kilohyl;
                     hyl = kilohyl/1000.0;
                     hyls = hyl;

        # English Units
        # length
                     inch = 0.0254*meters;
                     inches = inch;
                     in = inch;
                     mil = inch/1000.0;
                     mils = mil;
                     point = inch/72.27;
                     points = point;
                     pt = point;
                     bottommeasure = inch/40.0;
                     bottommeasures = bottommeasure;
                     line = inch/12.0;
                     lines = line;
                     pica = 12.0*points;
                     picas = pica;
                     barleycorn = inch/3.0;
                     barleycorns = barleycorn;
                     finger = 7.0*inches/8.0;
                     fingers = finger;
                     palm = 3.0*inches;
                     palms = palm;
                     hand = 4.0*inches;
                     hands = hand;
                     link = 7.92*inches;
                     links = link;
                     li = link;
                     span = 9.0*inches;
                     spans = span;
                     foot = 12.0*inches;
                     feet = foot;
                     ft = foot;
                     cubit = 18.0*inches;
                     cubits = cubit;
                     yard = 3.0*feet;
                     yards = yard;
                     yd = yard;
                     nail = yard/16.0;
                     nails = nail;
                     ell = 45.0*inches;
                     ells = ell;
                     pace = 5.0*feet;
                     paces = pace;
                     fathom = 6.0*feet;
                     fathoms = fathom;
                     fm = fathom;
                     rod = 198.0*inches;
                     rods = rod;
                     rd = rod;
                     pole = rod;
                     poles = pole;
                     p = pole;
                     perch = rod;
                     perches = perch;
                     rope = 20.0*feet;
                     ropes = rope;
                     bolt = 40.0*yards;
                     bolts = bolt;
                     chain = 4.0*rods;
                     chains = chain;
                     ch = chain;
#       namespace Gunters {
#                Gunters_chain = unit_chain;
                 Gunters_chain = chain;
                 Gunters_chains = Gunters_chain;
#       }
#       namespace engineers {
               engineers_link = foot;
               engineers_links = engineers_link;
               engineers_chain = 100.0*feet;
               engineers_chains = engineers_chain;
#       }
                     skein = 120*yards;
                     skeins = skein;
                     furlong = 220*yards;
                     furlongs = furlong;
                     spindle = 14400*yards;
                     spindles = spindle;
#       namespace US {
                      US_cable_length = 120.0*fathoms;
                      US_cable_lengths = US_cable_length;
#       }
#       namespace British {
                 British_cable_length = 100.0*fathoms;
                 British_cable_lengths = British_cable_length;
#       }
#       namespace statute {
                 statute_mile = 5280.0*feet;
                 statute_miles = statute_mile;
                 statute_mi = statute_mile;
                 statute_league = 3.0*statute_miles;
                 statute_leagues = statute_league;
#       }
#       namespace nautical {
                nautical_mile = 1852*meters;
                nautical_miles = nautical_mile;
                nautical_nm = nautical_mile;
                nautical_league = 3.0*nautical_miles;
                nautical_leagues = nautical_league;
#       }
#       namespace marine = nautical;
#                 marine = nautical;
#       namespace geodetic {
                geodetic_foot = (1200.0/3937.0)*meters;
                geodetic_feet = geodetic_foot;
                geodetic_ft = geodetic_foot;
#       }
#       namespace geographical {
            geographical_mile = nautical_mile;
            geographical_miles = geographical_mile;
            geographical_mi = geographical_mile;
#       }
                     parasang = 3.5*statute_miles;
                     parasangs = parasang;
                     arpentcan = 27.52*statute_miles;
                     arpentcans = arpentcan;
                     arpentlin = 191.835*feet;
                     arpentlins = arpentlin;
                     astronomical_unit = 1.49597871e11*meters;
                     astronomical_units = astronomical_unit;
                     AU = astronomical_unit;
                     lightyear = 9.4605e15*meters;
                     lightyears = lightyear;
                     ly = lightyear;
                     parsec = AU*radians/arc_second;
                     parsecs = parsec;
                     pc = parsec;
        # area
                     barn = 1.0e-28*meter*meter;
                     barns = barn;
                     b = barn;
                     circular_inch = 0.25*pi*inch*inch;
                     circular_inches = circular_inch;
                     circular_mil = 0.25*pi*mil*mil;
                     circular_mils = circular_mil;
                     sabin = foot*foot;
                     sabins = sabin;
                     square = 100.0*sabin;
                     squares = square;
                     are = 100.0*meter*meter;
                     ares = are;
                     a = are;
                     rood = 40.0*rod*rod;
                     roods = rood;
                     ro = rood;
                     acre = 4.0*roods;
                     acres = acre;
                     section = statute_mile*statute_mile;
                     sections = section;
                     homestead = section/4.0;
                     homesteads = homestead;
                     township = 36.0*sections;
                     townships = township;
        # volume
                     drop = 0.03*cc;
                     drops = drop;
                     teaspoon = 4.928922*cc;
                     teaspoons = teaspoon;
                     tablespoon = 3.0*teaspoons;
                     tablespoons = tablespoon;
#       namespace US {
#           namespace liquid {
                  US_liquid_gallon  = 231*inches**3;
                  US_liquid_gallons = US_liquid_gallon;
                  US_liquid_gal     = US_liquid_gallon;
                  US_liquid_quart   = US_liquid_gallon / 4.0;
                  US_liquid_quarts  = US_liquid_quart;
                  US_liquid_qt      = US_liquid_quart;
                  US_liquid_pint    = US_liquid_quart / 2.0;
                  US_liquid_pints   = US_liquid_pint;
                  US_liquid_pt      = US_liquid_pint;
                  US_liquid_gill    = US_liquid_pint / 4.0;
                  US_liquid_gills   = US_liquid_gill;
                  US_liquid_gl      = US_liquid_gill;
                  US_liquid_ounce   = US_liquid_pint / 16.0;
                  US_liquid_ounces  = US_liquid_ounce;
                  US_liquid_oz      = US_liquid_ounce;
                  US_liquid_dram    = US_liquid_ounce / 16.0;
                  US_liquid_drams   = US_liquid_dram;
                  US_liquid_dr      = US_liquid_dram;
#           }
#           namespace dry {
                  US_dry_pint = 550.61047*cc;
                  US_dry_pints = US_dry_pint;
                  US_dry_pt = US_dry_pint;
                  US_dry_quart = 2.0*US_dry_pints;
                  US_dry_quarts = US_dry_quart;
                  US_dry_qt = US_dry_quart;
#           }
                  US_minim = US_liquid_dram / 60.0;
                  US_minims = US_minim;
                  US_peck = 8.0*US_dry_quarts;
                  US_pecks = US_peck;
                  US_pk = US_peck;
                  US_bushel = 4.0*US_pecks;
                  US_bushels = US_bushel;
                  US_bu = US_bushel;
                  US_barrel = 31.5*US_liquid_gallons;
                  US_barrels = US_barrel;
                  US_bbl = US_barrel;
                  US_bl = US_barrel;
#       }
#       namespace British {
#           namespace fluid {
            British_fluid_gallon        = 4.54609 * liters;
            British_fluid_gallons       = British_fluid_gallon;
            British_fluid_gal           = British_fluid_gallon;
            British_fluid_quart         = British_fluid_gallon / 4.0;
            British_fluid_quarts        = British_fluid_quart;
            British_fluid_qt            = British_fluid_quart;
            British_fluid_pint          = British_fluid_quart / 2.0;
            British_fluid_pints         = British_fluid_pint;
            British_fluid_pt            = British_fluid_pint;
            British_fluid_gill          = British_fluid_pint / 4.0;
            British_fluid_gills         = British_fluid_gill;
            British_fluid_gl            = British_fluid_gill;
            British_fluid_ounce         = British_fluid_pint / 20.0;
            British_fluid_ounces        = British_fluid_ounce;
            British_fluid_oz            = British_fluid_ounce;
            British_fluid_drachm        = British_fluid_ounce / 8.0;
            British_fluid_drachms       = British_fluid_drachm;
            British_fluid_dr            = British_fluid_drachm;
            British_fluid_reputedquart  = British_fluid_quart * (2.0/3.0);
            British_fluid_reputedquarts = British_fluid_reputedquart;
            British_fluid_reputedpint   = British_fluid_reputedquart / 2.0;
            British_fluid_reputedpints  = British_fluid_reputedpint;
            British_fluid_magnum        = British_fluid_reputedquarts * 2.0;
            British_fluid_magnums       = British_fluid_magnum;
#             }
            British_minim = British_fluid_dram / 60.0;
            British_minims = British_minim;
            British_peck = 2.0*British_fluid_gallons;
            British_pecks = British_peck;
            British_pk = British_peck;
            British_bushel = 4.0*British_pecks;
            British_bushels = British_bushel;
            British_bu = British_bushel;
            British_barrel = 36.0*British_fluid_gallons;
            British_barrels = British_barrel;
            British_bbl = British_barrel;
            British_bl = British_barrel;
#       }
                     noggin = 2.0*US_liquid_ounces;
                     noggins = noggin;
                     cup = 8.0*US_liquid_ounces;
                     cups = cup;
                     fifth = US_liquid_gallon/5.0;
                     fifths = fifth;
                     jeroboam = 4.0*fifths;
                     jeroboams = jeroboam;
                     firkin = 9.0*US_liquid_gallons;
                     firkins = firkin;
                     kilderkin = 18.0*US_liquid_gallons;
                     kilderkins = kilderkin;
                     strike = 2.0*US_bushels;
                     strikes = strike;
                     sack = 3.0*US_bushels;
                     sacks = sack;
                     coomb = 4.0*US_bushels;
                     coombs = coomb;
                     seam = 8.0*US_bushels;
                     seams = seam;
                     wey = 40.0*US_bushels;
                     weys = wey;
                     last = 80.0*US_bushels;
                     lasts = last;
                     register_ton = 100.0*(ft*ft*ft);
                     register_tons = register_ton;
                     register_tn = register_ton;
                     cord = 128.0*(ft*ft*ft);
                     cords = cord;
                     cordfoot = cord;
                     cordfeet = cordfoot;
                     boardfoot = 144.0*inch*inch*inch;
                     boardfeet = boardfoot;
                     timberfoot = foot*foot*foot;
                     timberfeet = timberfoot;
                     hogshead = 2.0*US_barrels;
                     hogsheads = hogshead;
                     pipe = 4.0*US_barrels;
                     pipes = pipe;
                     tun = 8.0*US_barrels;
                     tuns = tun;
        # mass
                     grain = 0.06479891*grams;
                     grains = grain;
                     gr = grain;
                     pennyweight = 24.0*grains;
                     dwt = pennyweight;
#       namespace apothecary { # weight
              apothecary_scruple = 20.0*grains;
              apothecary_scruples = apothecary_scruple;
              apothecary_s = apothecary_scruple;
              apothecary_dram = 3.0*apothecary_scruples;
              apothecary_drams = apothecary_dram;
              apothecary_dr = apothecary_dram;
              apothecary_ounce = 8.0*apothecary_drams;
              apothecary_ounces = apothecary_ounce;
              apothecary_oz = apothecary_ounce;
              apothecary_pound = 12.0*apothecary_ounces;
              apothecary_pounds = apothecary_pound;
              apothecary_lb = apothecary_pound;
#       }
#       namespace troy = apothecary;
#       namespace ap = apothecary;
#       namespace t = apothecary;
#                 troy = apothecary;
#                 ap = apothecary;
#                 t = apothecary;
#       namespace avoirdupois { # weight
             avoirdupois_pound = 7000.0*grains;
             avoirdupois_pounds = avoirdupois_pound;
             avoirdupois_lb = avoirdupois_pound;
             avoirdupois_ounce = avoirdupois_pound/16.0;
             avoirdupois_ounces = avoirdupois_ounce;
             avoirdupois_oz = avoirdupois_ounce;
             avoirdupois_dram = avoirdupois_ounce/16.0;
             avoirdupois_drams = avoirdupois_dram;
             avoirdupois_dr = avoirdupois_dram;
#       }
#       namespace avdp = avoirdupois;
#       namespace av = avoirdupois;
#                 avdp = avoirdupois;
#                 av = avoirdupois;
                     stone = 14.0*avoirdupois_pounds;
                     stones = stone;
                     st = stone;
#       namespace US { # short
                     US_hundredweight = 100.0*avoirdupois_pounds;
                     US_cwt = US_hundredweight;
                     US_quarter = US_hundredweight/4.0;
                     US_quarters = US_quarter;
                     US_qr = US_quarter;
                     US_ton = 20.0*US_hundredweight;
                     US_tons = US_ton;
                     US_tn = US_ton;
                     US_deadweight = US_ton;
#       }
#       namespace British { # long
                 British_hundredweight = 112.0*avoirdupois_pounds;
                 British_cwt = British_hundredweight;
                 British_quarter = British_hundredweight/4.0;
                 British_quarters = British_quarter;
                 British_qr = British_quarter;
                 British_ton = 20.0*British_hundredweight;
                 British_tons = British_ton;
                 British_tn = British_ton;
#       }
#       namespace English = British;
#       namespace Imperial = British;
#                 English = British;
#                 Imperial = British;
                     crith = 0.0906*grams;
                     criths = crith;
                     bag = 94.0*avoirdupois_pounds;
                     bags = bag;
                     cental = 100.0*avoirdupois_pounds;
                     centals = cental;
                     weymass = 252.0*avoirdupois_pounds;
        # rate
                     mgd = 1000000.0*US_liquid_gallons/day;
                     cfs = foot*foot*foot/second;
                     minersinch = 1.5*foot*foot*foot/minute;
                     mpg = statute_miles/US_liquid_gallon;
        # speed
                     mph = statute_miles/hour;
                     knot = nautical_miles/hour;
                     knots = knot;
#       namespace admiralty {
              admiralty_knot = 6980.0*feet/hour;
              admiralty_knots = admiralty_knot;
#       }
        # force
                     poundal = avoirdupois_pound*foot/(second*second);
                     poundals = poundal;
                     pdl = poundal;
                     lbf = avoirdupois_pound*gravity;
        # pressure
                     psi = lbf/(inch*inch);
        # energy
                     calorie = 4.1868*Joules;
                     calories = calorie;
                     cal = calorie;
                     kilocalorie = 1000.0*calories;
                     kilocalories = kilocalorie;
                     kcal = kilocalorie;
                     Frigorie = kilocalorie;
                     Frigories = Frigorie;
                     Btu = 1055.06*Joules;
                     therm = 10000.0*Btu;
                     therms = therm;
                     thermie = 1000000.0*calories;
                     thermies = thermie;
        # power
                     horsepower = 735.49875*Watts;
                     HP = horsepower;
        # electrical current
                     Gilbert = 0.795775*Amperes;
                     Gilberts = Gilbert;
        # temperature
                     Rankin = 1.8*Kelvins;
                     Rankins = Rankin;
                     R = Rankin;
        # luminous intensity
                     candle = 1.02*candelas;
                     candles = candle;
#       namespace Hefner {
#                 Hefner_candle = 0.9*unit_candles;
                  Hefner_candle = 0.9*candles;
                  Hefner_candles = Hefner_candle;
#       }
        # light intensity
                     foot_candle = lumens/foot/foot;
                     foot_candles = foot_candle;
                     fc = foot_candle;
                     foot_Lambert = candelas/foot/foot/pi;
                     foot_Lamberts = foot_Lambert;
#       namespace equivalent {
#             equivalent_foot_candle = unit_foot_candle/pi;
              equivalent_foot_candle = foot_candle/pi;
              equivalent_foot_candles = equivalent_foot_candle;
              equivalent_fc = equivalent_foot_candle;
#       }
#   }
#   namespace units = unit;

#   namespace constant {
#       using namespace units;
        # speed of light
                     c = 2.99792458e8*meters/second;
        # speed of sound
                     Mach = 331.46*meters/second;
        # Planck constant
                     h = 6.6260755e-34*Joule*seconds;
                     h_bar = h/(2.0*pi);
        # standard gavitational acceleration at sea level
#                    g = units_gravity;
                     g = gravity;
        # electron charge
                     e = 1.60217733e-19*Coulombs;
        # elevtron Volt
                     eV = e*V;
                     keV = 1000.0*eV;
                     MeV = 1000000.0*eV;
                     GeV = 1000000000.0*eV;
                     Rydberg = 13.6054*eV;
                     Rydbergs = Rydberg;
        # electron mass
                     m_e = 9.1093897e-31*kilograms;
        # proton mass
                     m_P = 1.6726231e-27*kilograms;
        # deuteron mass
                     m_D = 1875.61339*MeV/(c*c);
        # unified atomic mass unit
                     atomic_mass_unit = 1.6605402e-27*kilograms;
                     atomic_mass_units = atomic_mass_unit;
                     amu = atomic_mass_unit;
                     Dalton = atomic_mass_unit;
                     Daltons = Dalton;
        # permittivity of free space
                     epsilon = 8.854187817e-12*Farads/meter;
        # permeability of free space
                     mu = 12.566370614e-7*Newtons/(A*A);
        # fine-structure constant
                     alpha = 1.0/137.0359895;
        # classical electron radius
                     r_e = 2.81794092e-15*meters;
        # electron Compton wavelength
                     lambda_bar = 3.86159323e-13*meters;
        # Bohr radius
                     a_0 = 0.529177249e-10*meters;
        # wavelength of 1 eV/c particle
                     lambda_1eV = 1.23984244e-6*meters;
        # Thomson cross section
                     sigma_0 = 0.66524616*barns;
        # Bohr magneton
                     mu_B = 5.78838263e-11*MeV/Tesla;
        # nuclear magneton
                     mu_N = 3.15245166e-14*MeV/Tesla;
        # electron cyclotron frequency/field
                     E_M_e = 1.75881962e11*C/kg*(rad/(s*T));
        # proton cyclotron frequency/field
                     E_M_P = 9.5788309e7*C/kg*(rad/(s*T));
        # gravitational constant
                     G = 6.67259e-11*m*m*m/(kg*s*s);
        # Avogadro's constant
                     N_A = 6.0221367e23;
        # Boltzmann constant
                     K_B = 1.380658e-23*Joules/Kelvin;
        # molar volume, ideal gas at standard temperature and pressure
                     V_molar = 2.897756e-3*meter*Kelvins;
        # Stefan-Boltzmann constant
                     sigma_SB = 5.67051e-8*W/(m*m*K*K*K*K);
        #
#   }
#   namespace constants = constant;
#} 
