from physical.const     import const;

import admiralty;
import apothecary;
import ap;              # dummy module for apothecary
import troy;            # dummy module for apothecary
import t;               # dummy module for apothecary
import arc;
import avoirdupois;
import avdp;            # dummy module for avoirdupois
import av;              # dummy module for avoirdupois
import bakers;
import British;
import English;         # dummy module for British
import Imperial;        # dummy module for British
import displacement;
import dose;
import engineers;
import equivalent;
import geodetic;
import geographical;
import Gunters;
import Hefner;
import metric;
import nautical;
import marine;          # dummy module for nautical
import statute;
import US;

from physical.Quantity  import Quantity;

import sys;
class unit(const):
    def __init__(self, prefix):
        const.__init__(self,prefix + 'unit');

        # #### BEGIN OF UNIT CREATION #### #

        # for each submodule, we pass in self to allow dependence on values
        # previously set.

        # conversion factor
        self.radian = Quantity(1,{'radian':1});
        self.radians = self.radian;
        self.rad = self.radian;
        self.steradian = Quantity(1,{'steradian':1});
        self.steradians = self.steradian;
        self.sr = self.steradian;

        # money
        self.dollar = Quantity(1,{'dollar':1});
        self.dollars = self.dollar;
        self.cent = self.dollar/100.0;
        self.cents = self.cent;


        self.dozen = 12.0;
        self.doz = self.dozen;
        self.dz = self.dozen;

        self.gross = 12.0*self.dozen;
        self.gro = self.gross;
        self.quire = 25.0;
        self.quires = self.quire;
        self.ream = 500.0;
        self.reams = self.ream;
        self.percent = 1.0/100.0;
        self.proof = self.percent/2.0;
        self.karat = 1.0/24.0;
        self.karats = self.karat;
        self.mole = 6.0221367e+23;
        self.moles = self.mole;
        self.mol = self.mole;
        self.pi = 3.14159265358979323846*self.radians;

                # SI units (mks)
        # length
        self.meter = Quantity(1,{'m':1});
        self.meters = self.meter;
        self.m = self.meter;
        self.kilometer = 1000.0*self.meters;
        self.kilometers = self.kilometer;
        self.km = self.kilometer;
        self.decimeter = self.meters/10.0;
        self.decimeters = self.decimeter;
        self.dm = self.decimeter;
        self.centimeter = self.meters/100.0;
        self.centimeters = self.centimeter;
        self.cm = self.centimeter;
        self.millimeter = self.meters/1000.0;
        self.millimeters = self.millimeter;
        self.mm = self.millimeter;
        self.micron = self.meter/1000000.0;
        self.microns = self.micron;
        self.um = self.micron;
        self.nanometer = self.meter/1000000000.0;
        self.nanometers = self.nanometer;
        self.nm = self.nanometer;
        self.decinanometer = self.meter/10000000000.0;
        self.decinanometers = self.decinanometer;
        self.Angstrom = self.decinanometer;
        self.Angstroms = self.Angstrom;
        self.Xunit = 1.00202e-13*self.meters;
        self.Xunits = self.Xunit;
        self.Fermi = self.meter/1000000000000000.0;
        self.Fermis = self.Fermi;

        # area
        self.hectare = 10000.0*self.meter*self.meter;
        self.hectares = self.hectare;
        self.ha = self.hectare;

        # volume
        self.stere = self.meter*self.meter*self.meter;
        self.steres = self.stere;
        self.liter = self.stere/1000.0;
        self.liters = self.liter;
        self.l = self.liter;
        self.milliliter = self.stere/1000000.0;
        self.milliliters = self.milliliter;
        self.ml = self.milliliter;
        self.cc = self.milliliter;

        # mass
        self.kilogram = Quantity(1,{'kg':1});
        self.kilograms = self.kilogram;
        self.kg = self.kilogram;
        self.quintal = 100.0*self.kilograms;
        self.quintals = self.quintal;
        self.doppelzentner = self.quintal;
        self.doppelzentners = self.doppelzentner;
        self.gram = self.kilograms/1000.0;
        self.grams = self.gram;
        self.g = self.gram;
        self.milligram = self.kilogram/1000000.0;
        self.milligrams = self.milligram;
        self.mg = self.milligram;

        # time
        self.second = Quantity(1,{'s':1});
        self.seconds = self.second;
        self.sec = self.second;
        self.s = self.second;
        self.millisecond = self.second/1000.0;
        self.milliseconds = self.millisecond;
        self.ms = self.millisecond;
        self.microsecond = self.second/1000000.0;
        self.microseconds = self.microsecond;
        self.us = self.microsecond;
        self.nanosecond = self.second/1000000000.0;
        self.nanoseconds = self.nanosecond;
        self.ns = self.nanosecond;
        self.picosecond = self.second/1000000000000.0;
        self.picoseconds = self.picosecond;
        self.minute = 60.0*self.seconds;
        self.minutes = self.minute;
        self.min = self.minute;
        self.hour = 60.0*self.minutes;
        self.hours = self.hour;
        self.hr = self.hour;
        self.day = 24.0*self.hours;
        self.days = self.day;
        self.da = self.day;
        self.week = 7.0*self.days;
        self.weeks = self.week;
        self.fortnight = 2.0*self.weeks;
        self.fortnights = self.fortnight;
        self.year = 365.2421896698*self.days;
        self.years = self.year;
        self.yr = self.year;
        self.month = self.year/12.0;
        self.months = self.month;
        self.mo = self.month;
        self.decade = 10.0*self.years;
        self.decades = self.decade;
        self.century = 100.0*self.years;
        self.centuries = self.century;
        self.millenium = 1000.0*self.years;
        self.millenia = self.millenium;
        # temporal frequency
        self.Hertz = 1.0/self.second;
        self.Hz = self.Hertz;
        self.kiloHertz = 1000.0*self.Hertz;
        self.kHz = self.kiloHertz;
        self.megaHertz = 1000000.0*self.Hertz;
        self.MHz = self.megaHertz;
        self.gigaHertz = 1000000000.0*self.Hertz;
        self.GHz = self.gigaHertz;
        self.teraHertz = 1000000000000.0*self.Hertz;
        self.THz = self.teraHertz;
        # spacial frequency
        self.diopter = 1.0/self.meter;
        self.diopters = self.diopter;
        # speed
        self.kph = self.kilometers/self.hour;
        # radioactivity
        self.Becquerel = 1.0/self.second;
        self.Becquerels = self.Becquerel;
        self.Bq = self.Becquerel;
        self.Rutherford = 1000000.0*self.Becquerels;
        self.Rutherfords = self.Rutherford;
        self.Curie = 3.7e+10*self.Becquerels;
        self.Curies = self.Curie;
        self.Ci = self.Curie;
        # force
        self.Newton = self.kilogram*self.meter/(self.second*self.second);
        self.Newtons = self.Newton;
        self.N = self.Newton;
        self.dyne = self.Newton/100000.0;
        self.dynes = self.dyne;
        self.dyn = self.dyne;
        # pressure
        self.Pascal = self.Newton/(self.meter*self.meter);
        self.Pascals = self.Pascal;
        self.Pa = self.Pascal;
        self.Barie = self.Pascal/10.0;
        self.Baries = self.Barie;
        self.Barye = self.Barie;
        self.Baryes = self.Barye;
        self.pieze = 1000.0*self.Pascals;
        self.piezes = self.pieze;
        self.pz = self.pieze;
        self.bar = 10000.0*self.Pascals;
        self.bars = self.bar;
        self.Torr = 133.3224*self.Pascals;
        self.atmosphere = 760.0*self.Torr;
        self.atmospheres = self.atmosphere;
        self.atm = self.atmosphere;
        # energy
        self.Joule = self.Newton*self.meter;
        self.Joules = self.Joule;
        self.J = self.Joule;
        self.erg = self.Joule/10000000.0;
        self.ergs = self.erg;
        self.kiloWatthour = 3600000.0*self.Joules;
        self.kiloWatthours = self.kiloWatthour;
        self.kWh = self.kiloWatthour;
        # power
        self.Watt = self.Joule/self.second;
        self.Watts = self.Watt;
        self.W = self.Watt;
        self.kiloWatt = 1000.0*self.Watts;
        self.kiloWatts = self.kiloWatt;
        self.kW = self.kiloWatt;
        self.megaWatt = 1000000.0*self.Watts;
        self.megaWatts = self.megaWatt;
        self.MW = self.megaWatt;
        self.milliWatt = self.Watt/1000.0;
        self.milliWatts = self.milliWatt;
        self.mW = self.milliWatt;
        self.microWatt = self.Watt/1000000.0;
        self.microWatts = self.microWatt;
        self.uW = self.microWatt;
        self.nanoWatt =  self.Watt/1000000000.0;
        self.nanoWatts = self.nanoWatt;
        self.nW = self.nanoWatt;

        # electrical current
        self.Ampere = Quantity(1,{'A':1});
        self.Amperes = self.Ampere;
        self.A = self.Ampere;
        self.Biot = 10.0*self.Amperes;
        self.Biots = self.Biot;
        self.abAmpere = self.Biot
        self.abAmperes = self.abAmpere
        self.abAmp = self.abAmpere
        self.aA = self.abAmpere
        self.statAmpere = self.Biot * 3.335641e-11 # == Biot * (cm/s)/c
        self.statAmperes = self.statAmpere
        self.statAmp = self.statAmpere
        self.statA = self.statAmpere

        # electrical potential
        self.Volt = self.Watt/self.Ampere;
        self.Volts = self.Volt;
        self.V = self.Volt;
        self.statVolt = self.erg / (self.statAmp * self.s)
        self.statVolts = self.statVolt
        self.statV = self.statVolt
        self.abVolt = (self.dyne * self.cm) / (self.abAmp * self.s)

        # electrical resistance
        self.Ohm = self.Volt/self.Ampere;
        self.Ohms = self.Ohm;
        self.statOhm = self.statVolt/self.statAmpere
        self.abOhm = self.abVolt/self.abAmpere

        # electrical conductance
        self.mho = 1.0/self.Ohm;
        self.mhos = self.mho;
        self.Siemens = self.mho;
        self.S = self.Siemens;

        # electrical charge
        self.Coulomb = self.Ampere*self.second;
        self.Coulombs = self.Coulomb;
        self.C = self.Coulomb;
        self.statCoulomb = self.statAmpere * self.second
        self.statCoulombs = self.statCoulomb
        self.statCoul = self.statCoulomb
        self.statC = self.statCoulomb
        self.abCoulomb = self.abAmpere * self.second
        self.abCoulombs = self.abCoulomb
        self.abCoul = self.abCoulomb
        self.Franklin = self.statCoulombs;
        self.Franklins = self.Franklin;

        # electrical capacity
        self.Farad = self.Coulomb/self.Volt;
        self.Farads = self.Farad;
        self.F = self.Farad;

        # magnetic flux
        self.Weber = self.Volt*self.second;
        self.Webers = self.Weber;
        self.Wb = self.Weber;
        self.Maxwell = self.Weber/100000000.0;
        self.Maxwells = self.Maxwell;
        self.M = self.Maxwell;
        self.statMaxwell = self.statVolt * self.second
        self.statMaxwells = self.statMaxwell
        self.statM = self.statMaxwell
        # magnetic field B
        self.Tesla = self.Weber/(self.meter*self.meter);
        self.Teslas = self.Tesla;
        self.T = self.Tesla;
        #self.Gauss = self.Tesla/10000.0;
        self.Gauss = self.abVolt * self.second / self.cm**2
        self.gamma = self.Tesla/1000000000.0;
        # magnetic field H
        self.Oerstedt = 79.57747*self.Ampere/self.meter; # = Gauss/mu0
        self.Oerstedts = self.Oerstedt;
        self.Oe = self.Oerstedt;
        # magnetic inductance
        self.Henry = self.Weber/self.Ampere;
        self.Henrys = self.Henry;
        self.H = self.Henry;
        self.milliHenry = self.Henry/1000.0;
        self.milliHenrys = self.milliHenry;
        self.mH = self.milliHenry;
        # temperature
        self.Kelvin = Quantity(1,{'K':1});
        self.Kelvins = self.Kelvin;
        self.K = self.Kelvin;
        self.milliKelvin = self.Kelvin*1e-3;
        self.mK = self.milliKelvin;
        self.microKelvin = self.Kelvin*1e-6;
        self.uK = self.microKelvin;
        self.nanoKelvin = self.Kelvin*1e-9;
        self.nK = self.nanoKelvin;
        # luminous intensity
        self.candela = Quantity(1,{'candela':1});
        self.candelas = self.candela;
        self.cd = self.candela;
        self.apostilb = self.candelas/self.meter/self.meter;
        self.apostilbs = self.apostilb;
        self.nit = self.apostilb;
        self.nits = self.nit;
        self.skot = self.apostilb/1000.0;
        self.skots = self.skot;
        self.stilb = 10000.0*self.apostilbs;
        self.stilbs = self.stilb;
        self.Blondel = self.apostilb/self.pi;
        self.Blondels = self.Blondel;
        self.Lambert = 10000.0*self.Blondels;
        self.Lamberts = self.Lambert;
        # light flux
        self.lumen = self.candela*self.steradian;
        self.lumens = self.lumen;
        self.lm = self.lumen;
        # light intensity
        self.lux = self.lumens/self.meter/self.meter;
        self.luxes = self.lux;
        self.luces = self.lux;
        self.lx = self.lux;
        self.nox = self.lux/1000.0;
        self.phot = self.lumens/self.centimeter/self.centimeter;
        self.phots = self.phot;

        # acceleration
        self.Galileo = self.centimeters/self.second/self.second;
        self.Galileos = self.Galileo;
        # standard gravitational acceleration at sea level
        self.gravity = 9.80665*self.meters/self.second/self.second;
        # mass
        self.kilohyl = self.kilogram*self.gravity*self.second*self.second/self.meter;
        self.kilohyls = self.kilohyl;
        self.hyl = self.kilohyl/1000.0;
        self.hyls = self.hyl;

                # English Units
        # length
        self.inch = 0.0254*self.meters;
        self.inches = self.inch;
        #self.in = self.inch;
        self.mil = self.inch/1000.0;
        self.mils = self.mil;
        self.point = self.inch/72.27;
        self.points = self.point;
        self.pt = self.point;
        self.bottommeasure = self.inch/40.0;
        self.bottommeasures = self.bottommeasure;
        self.line = self.inch/12.0;
        self.lines = self.line;
        self.pica = 12.0*self.points;
        self.picas = self.pica;
        self.barleycorn = self.inch/3.0;
        self.barleycorns = self.barleycorn;
        self.finger = 7.0*self.inches/8.0;
        self.fingers = self.finger;
        self.palm = 3.0*self.inches;
        self.palms = self.palm;
        self.hand = 4.0*self.inches;
        self.hands = self.hand;
        self.link = 7.92*self.inches;
        self.links = self.link;
        self.li = self.link;
        self.span = 9.0*self.inches;
        self.spans = self.span;
        self.foot = 12.0*self.inches;
        self.feet = self.foot;
        self.ft = self.foot;
        self.cubit = 18.0*self.inches;
        self.cubits = self.cubit;
        self.yard = 3.0*self.feet;
        self.yards = self.yard;
        self.yd = self.yard;
        self.nail = self.yard/16.0;
        self.nails = self.nail;
        self.ell = 45.0*self.inches;
        self.ells = self.ell;
        self.pace = 5.0*self.feet;
        self.paces = self.pace;
        self.fathom = 6.0*self.feet;
        self.fathoms = self.fathom;
        self.fm = self.fathom;
        self.rod = 198.0*self.inches;
        self.rods = self.rod;
        self.rd = self.rod;
        self.pole = self.rod;
        self.poles = self.pole;
        self.p = self.pole;
        self.perch = self.rod;
        self.perches = self.perch;
        self.rope = 20.0*self.feet;
        self.ropes = self.rope;
        self.bolt = 40.0*self.yards;
        self.bolts = self.bolt;
        self.chain = 4.0*self.rods;
        self.chains = self.chain;
        self.ch = self.chain;
        self.skein = 120*self.yards;
        self.skeins = self.skein;
        self.furlong = 220*self.yards;
        self.furlongs = self.furlong;
        self.spindle = 14400*self.yards;
        self.spindles = self.spindle;

        self.statute      = statute.statute(prefix + 'unit.', self);

        self.parasang = 3.5*self.statute.miles;
        self.parasangs = self.parasang;
        self.arpentcan = 27.52*self.statute.miles;
        self.arpentcans = self.arpentcan;
        self.arpentlin = 191.835*self.feet;
        self.arpentlins = self.arpentlin;
        self.astronomical_unit = 1.49597871e11*self.meters;
        self.astronomical_units = self.astronomical_unit;
        self.AU = self.astronomical_unit;
        self.lightyear = 9.4605e15*self.meters;
        self.lightyears = self.lightyear;
        self.ly = self.lightyear;

        self.arc          = arc.arc(prefix + 'unit.', self);

        self.parsec = self.AU*self.radians/self.arc.second;
        self.parsecs = self.parsec;
        self.pc = self.parsec;
        # area
        self.barn = 1.0e-28*self.meter*self.meter;
        self.barns = self.barn;
        self.b = self.barn;
        self.circular_inch = 0.25*self.pi*self.inch*self.inch;
        self.circular_inches = self.circular_inch;
        self.circular_mil = 0.25*self.pi*self.mil*self.mil;
        self.circular_mils = self.circular_mil;
        self.sabin = self.foot*self.foot;
        self.sabins = self.sabin;
        self.square = 100.0*self.sabin;
        self.squares = self.square;
        self.are = 100.0*self.meter*self.meter;
        self.ares = self.are;
        self.a = self.are;
        self.rood = 40.0*self.rod*self.rod;
        self.roods = self.rood;
        self.ro = self.rood;
        self.acre = 4.0*self.roods;
        self.acres = self.acre;
        self.section = self.statute.mile*self.statute.mile;
        self.sections = self.section;
        self.homestead = self.section/4.0;
        self.homesteads = self.homestead;
        self.township = 36.0*self.sections;
        self.townships = self.township;

        # mass
        self.grain = 0.06479891*self.grams;
        self.grains = self.grain;
        self.gr = self.grain;
        self.pennyweight = 24.0*self.grains;
        self.dwt = self.pennyweight;

        # volume
        self.minim = 6.161152e-8*(self.m*self.m*self.m);
        self.minims = self.minim;
        self.drop = 0.03*self.cc;
        self.drops = self.drop;
        self.teaspoon = 4.928922*self.cc;
        self.teaspoons = self.teaspoon;
        self.tablespoon = 3.0*self.teaspoons;
        self.tablespoons = self.tablespoon;

        self.avoirdupois  = avoirdupois.avoirdupois(prefix + 'unit.', self);
        self.avdp         = self.avoirdupois
        self.av           = self.avoirdupois
        self.US           = US.US(prefix + 'unit.', self);

        self.noggin = 2.0*self.US.liquid.ounces;
        self.noggins = self.noggin;
        self.cup = 8.0*self.US.liquid.ounces;
        self.cups = self.cup;
        self.fifth = self.US.liquid.gallon/5.0;
        self.fifths = self.fifth;
        self.jeroboam = 4.0*self.fifths;
        self.jeroboams = self.jeroboam;
        self.firkin = 9.0*self.US.liquid.gallons;
        self.firkins = self.firkin;
        self.kilderkin = 18.0*self.US.liquid.gallons;
        self.kilderkins = self.kilderkin;
        self.strike = 2.0*self.US.bushels;
        self.strikes = self.strike;
        self.sack = 3.0*self.US.bushels;
        self.sacks = self.sack;
        self.coomb = 4.0*self.US.bushels;
        self.coombs = self.coomb;
        self.seam = 8.0*self.US.bushels;
        self.seams = self.seam;
        self.wey = 40.0*self.US.bushels;
        self.weys = self.wey;
        self.last = 80.0*self.US.bushels;
        self.lasts = self.last;
        self.register_ton = 100.0*(self.ft*self.ft*self.ft);
        self.register_tons = self.register_ton;
        self.register_tn = self.register_ton;
        self.cord = 128.0*(self.ft*self.ft*self.ft);
        self.cords = self.cord;
        self.cordfoot = self.cord;
        self.cordfeet = self.cordfoot;
        self.boardfoot = 144.0*self.inch*self.inch*self.inch;
        self.boardfeet = self.boardfoot;
        self.timberfoot = self.foot*self.foot*self.foot;
        self.timberfeet = self.timberfoot;
        self.hogshead = 2.0*self.US.barrels;
        self.hogsheads = self.hogshead;
        self.pipe = 4.0*self.US.barrels;
        self.pipes = self.pipe;
        self.tun = 8.0*self.US.barrels;
        self.tuns = self.tun;


        self.stone = 14.0*self.avoirdupois.pounds;
        self.stones = self.stone;
        self.st = self.stone;


        self.crith = 0.0906*self.grams;
        self.criths = self.crith;
        self.bag = 94.0*self.avoirdupois.pounds;
        self.bags = self.bag;
        self.cental = 100.0*self.avoirdupois.pounds;
        self.centals = self.cental;
        self.weymass = 252.0*self.avoirdupois.pounds;
        # rate
        self.mgd = 1000000.0*self.US.liquid.gallons/self.day;
        self.cfs = self.foot*self.foot*self.foot/self.second;
        self.minersinch = 1.5*self.foot*self.foot*self.foot/self.minute;
        self.mpg = self.statute.miles/self.US.liquid.gallon;

        self.nautical     = nautical.nautical(prefix + 'unit.', self);

        # speed
        self.mph = self.statute.miles/self.hour;
        self.knot = self.nautical.miles/self.hour;
        self.knots = self.knot;

        # force
        self.poundal = self.avdp.pound*self.foot/(self.second*self.second);
        self.poundals = self.poundal;
        self.pdl = self.poundal;
        self.lbf = self.avoirdupois.pound*self.gravity;
        # pressure
        self.psi = self.lbf/(self.inch*self.inch);
        # energy
        self.calorie = 4.1868*self.Joules;
        self.calories = self.calorie;
        self.cal = self.calorie;
        self.kilocalorie = 1000.0*self.calories;
        self.kilocalories = self.kilocalorie;
        self.kcal = self.kilocalorie;
        self.Frigorie = self.kilocalorie;
        self.Frigories = self.Frigorie;
        self.Btu = 1055.06*self.Joules;
        self.therm = 10000.0*self.Btu;
        self.therms = self.therm;
        self.thermie = 1000000.0*self.calories;
        self.thermies = self.thermie;
        # power
        self.horsepower = 735.49875*self.Watts;
        self.HP = self.horsepower;
        # electrical current
        self.Gilbert = 0.795775*self.Amperes;
        self.Gilberts = self.Gilbert;
        # temperature
        self.Rankin = 1.8*self.Kelvins;
        self.Rankins = self.Rankin;
        self.R= self.Rankin;
        # luminous intensity
        self.candle = 1.02*self.candelas;
        self.candles = self.candle;
        # light intensity
        self.foot_candle = self.lumens/self.foot/self.foot;
        self.foot_candles = self.foot_candle;
        self.fc = self.foot_candle;
        self.foot_Lambert = self.candelas/self.foot/self.foot/self.pi;
        self.foot_Lamberts = self.foot_Lambert;



        # and now load all of the sub-modules that don't have
        # interdependencies with other unit stuff.
        self.admiralty    = admiralty.admiralty(prefix + 'unit.', self);
        self.apothecary   = apothecary.apothecary(prefix + 'unit.', self);
        self.bakers       = bakers.bakers(prefix + 'unit.', self);
        self.British      = British.British(prefix + 'unit.', self);
        self.displacement = displacement.displacement(prefix + 'unit.', self);
        self.dose         = dose.dose(prefix + 'unit.', self);
        self.engineers    = engineers.engineers(prefix + 'unit.', self);
        self.equivalent   = equivalent.equivalent(prefix + 'unit.', self);
        self.geodetic     = geodetic.geodetic(prefix + 'unit.', self);
        self.geographical = geographical.geographical(prefix + 'unit.', self);
        self.Gunters      = Gunters.Gunters(prefix + 'unit.', self);
        self.Hefner       = Hefner.Hefner(prefix + 'unit.', self);
        self.metric       = metric.metric(prefix + 'unit.', self);

        # #### END OF UNIT CREATION #### #

        # do some trickery to get modules set to instantiated classes
        # We expect each submodule to do likewise for those not already taken
        # care of here.
        self.admiralty.__name__ = admiralty.__name__
        sys.modules[admiralty.__name__] = self.admiralty

        self.apothecary.__name__ = apothecary.__name__
        sys.modules[apothecary.__name__] = self.apothecary
        sys.modules[ap.__name__] = self.apothecary
        sys.modules[troy.__name__] = self.apothecary
        sys.modules[t.__name__] = self.apothecary

        self.arc.__name__ = arc.__name__
        sys.modules[arc.__name__] = self.arc

        self.avoirdupois.__name__ = avoirdupois.__name__
        sys.modules[avoirdupois.__name__] = self.avoirdupois
        # fix dummies for avoirdupois
        sys.modules[avdp.__name__] = self.avoirdupois
        sys.modules[av.__name__] = self.avoirdupois

        self.bakers.__name__ = bakers.__name__
        sys.modules[bakers.__name__] = self.bakers

        self.British.__name__ = British.__name__
        sys.modules[British.__name__] = self.British
        sys.modules[English.__name__] = self.British
        sys.modules[Imperial.__name__] = self.British

        self.displacement.__name__ = displacement.__name__
        sys.modules[displacement.__name__] = self.displacement

        self.dose.__name__ = dose.__name__
        sys.modules[dose.__name__] = self.dose

        self.engineers.__name__ = engineers.__name__
        sys.modules[engineers.__name__] = self.engineers

        self.equivalent.__name__ = equivalent.__name__
        sys.modules[equivalent.__name__] = self.equivalent

        self.geodetic.__name__ = geodetic.__name__
        sys.modules[geodetic.__name__] = self.geodetic

        self.geographical.__name__ = geographical.__name__
        sys.modules[geographical.__name__] = self.geographical

        self.Gunters.__name__ = Gunters.__name__
        sys.modules[Gunters.__name__] = self.Gunters

        self.Hefner.__name__ = Hefner.__name__
        sys.modules[Hefner.__name__] = self.Hefner

        self.metric.__name__ = metric.__name__
        sys.modules[metric.__name__] = self.metric

        self.nautical.__name__ = nautical.__name__
        sys.modules[nautical.__name__] = self.nautical
        sys.modules[marine.__name__] = self.nautical

        self.statute.__name__ = statute.__name__
        sys.modules[statute.__name__] = self.statute

        self.US.__name__ = US.__name__
        sys.modules[US.__name__] = self.US

