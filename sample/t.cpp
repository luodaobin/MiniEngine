//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2011 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <map>
#include <time.h>
#include <set>
#include <string>
#include <vector>

int a[]={
101951202,
145725456,
145737150,
145737154,
145737158,
145737170,
145737173,
145737177,
137599036,
145737182,
145737185,
145737187,
145737196,
145737201,
145737205,
145737207,
145737209,
145737212,
145737217,
145737219,
145737227,
145737228,
145737235,
145737238,
145737242,
145737245,
145737250,
145737253,
145737256,
145737258,
145737261,
104371498,
145737263,
145737266,
145737267,
145737268,
145737269,
145737272,
94729721,
145737278,
145737281,
145737286,
145737288,
145737300,
145737306,
145737311,
145737312,
145737315,
145737362,
145737368,
145737370,
145737372,
145737378,
145737384,
145737387,
145737391,
145737394,
145737396,
145737398,
145737400,
145737402,
145737405,
145737406,
145737409,
145737411,
145737415,
120788831,
132671565,
145737418,
145737423,
145737427,
145737431,
145737434,
145737438,
145737442,
145737444,
145737460,
93303619,
145737468,
145737471,
145737472,
145737475,
145737003,
145737479,
145737485,
145737489,
93303619,
145737495,
145737498,
145737501,
97284536,
145737506,
125359359,
145737511,
145737513,
145737517,
145737522,
145737525,
145737531,
145737533,
145737535,
138429757,
145737538,
145737539,
145737542,
145737548,
145737551,
145737555,
145737558,
145737560,
145737562,
145737565,
145737569,
145737573,
145737576,
145737578,
145737579,
145737582,
145737585,
145737589,
145737590,
145737591,
145737593,
145737595,
145737598,
145737602,
145737605,
145737609,
145737617,
145737619,
145737623,
145737624,
145737625,
145737627,
145737633,
145737636,
145737652,
145737656,
101985818,
145737664,
145737668,
145737671,
145737674,
90719754,
145737679,
145737683,
145737688,
145737690,
145737695,
137870030,
145737699,
145737701,
145737704,
145737707,
126929573,
145737712,
91368188,
145737717,
145737720,
145737723,
145737724,
145737726,
145737731,
145737732,
145737735,
145737739,
145737741,
145737744,
145737751,
145737754,
145737758,
145737762,
145737765,
145737769,
145737771,
124479829,
145737775,
145737778,
145737785,
145737788,
145737791,
124810614,
135664177,
145737800,
145737802,
145737806,
145737810,
145737815,
145737817,
145737820,
145737825,
145737829,
145737830,
145737833,
145737836,
145737843,
145737847,
145737850,
145737854,
91363609,
90752561,
145737862,
145737865,
145737868,
145737870,
145737875,
145737877,
145737881,
145737883,
118136625,
145737889,
145737892,
145737895,
145737896,
145737902,
145737906,
145737908,
145737911,
145737914,
145737916,
145737918,
145737921,
90732913,
143712080,
145737931,
145737935,
145737938,
145737941,
145737942,
145737944,
145737949,
145737952,
145737953,
145737956,
145737958,
145737961,
145737962,
145737968,
145737972,
145737974,
145737977,
135175454,
145737983,
145737986,
145737988,
145737990,
145737991,
145737993,
145737994,
145738001,
145738005,
145738012,
145738015,
145738019,
145738023,
145738025,
145738029,
145738031,
145738035,
145738037,
145738039,
145738049,
145738058,
145738061,
145738065,
145738066,
145738068,
145738072,
145738075,
145738078,
145738081,
145738084,
145738087,
145738089,
145738091,
145738095,
145738097,
145738101,
145738104,
145738105,
145738108,
145738111,
145738122,
145738125,
145738126,
145738129,
133233976,
145738134,
145738136,
145738150,
145738153,
138429757,
145738158,
145738160,
145738163,
145738165,
145738167,
145738169,
145738173,
139672353,
145737762,
145738181,
145738184,
138283257,
145738191,
145738194,
145738197,
145738199,
145738200,
145738202,
145738207,
145738208,
145738209,
145738212,
145738215,
145738221,
145738225,
145738226,
145738229,
145738230,
145738231,
138055938,
145738237,
80312523,
145738247,
145738160,
145738256,
145738260,
145738263,
145738266,
145738273,
145738278,
145738281,
145738283,
145738285,
145738290,
145738293,
145738295,
145738297,
145738300,
145738302,
145738305,
145738306,
145738309,
145738310,
145738313,
145738317,
145738321,
145738323,
145738328,
144957640,
145738335,
145738338,
126354511,
145738342,
145738344,
145738349,
145738353,
145738356,
145738361,
145738365,
145738368,
145738370,
145738374,
145738376,
145738378,
145738382,
145738387,
145738390,
145738392,
145738393,
145738401,
145738417,
84332136,
145738420,
145738422,
145738425,
145738431,
137838195,
145738437,
145738439,
145738441,
145738442,
145738448,
145738449,
145738452,
145738456,
145738458,
145738463,
145738466,
145738469,
145737485,
145738474,
125123666,
145738479,
145738483,
145738487,
145738490,
145738495,
145738498,
145738502,
145738504,
145738507,
145738510,
145738517,
145738521,
145738524,
145738526,
145738531,
145738536,
145738538,
122251194,
145738543,
145738544,
145738546,
145738548,
145738552,
132507535,
145738566,
145738571,
145738574,
145738581,
145738585,
128059180,
145738590,
145738592,
145738595,
145738596,
145738601,
145738605,
145738608,
145738614,
145738616,
141061720,
145738622,
145738625,
145738627,
145738630,
145738634,
145738638,
145738640,
145738646,
145738648,
144978177,
90549298,
145738651,
145738653,
145738654,
141261092,
122203915,
145738661,
145738663,
145738666,
145738669,
145738677,
145738679,
145738685,
125301465,
145738687,
145738693,
145738696,
145738698,
90755314,
145738702,
145738705,
145738709,
145738711,
145738712,
145738719,
145738723,
145738727,
145738731,
145738736,
145738739,
145738742,
145738745,
145738748,
145738751,
145738753,
145738755,
145738759,
145738762,
145738764,
145738766,
145738767,
145738770,
145738771,
145738776,
145738779,
145738787,
145738790,
145738792,
145738795,
145738798,
145738800,
145738804,
145738807,
145738811,
145738815,
145738818,
145738824,
145738827,
145738833,
145738835,
145738838,
145738844,
145738847,
145738854,
145738858,
145738861,
145738863,
145738864,
145738865,
145738868,
145738871,
145738873,
145738879,
145738883,
121108941,
145738892,
145738894,
145738897,
145738901,
145738711,
138035317,
145738544,
145738913,
145738919,
145738924,
119152512,
145738931,
145738937,
145738941,
145738944,
145738948,
145738951,
145738955,
145738961,
145738965,
145738977,
145738983,
145738226,
141267280,
145738994,
145739000,
145738571,
145739022,
145739028,
145739030,
145739034,
145739036,
145739038,
145739041,
145739045,
145739052,
145739055,
145739058,
145739063,
107267535,
145739074,
145739093,
127232138,
145739099,
145739102,
145739109,
145739111,
145739114,
145739121,
145739124,
145739132,
145739136,
145739141,
145739143,
145739147,
145739149,
145739152,
145739155,
145739157,
145739160,
145739165,
145739177,
145739182,
145739198,
145739205,
145739210,
145739216,
145739221,
145739226,
145739233,
145739236,
145739246,
145739249,
145739251,
145739257,
145739262,
145739283,
145739286,
131612248,
145739290,
145739294,
145739297,
145739299,
145739301,
145739303,
145739316,
145739319,
127150998,
145739323,
145739328,
145739331,
145739332,
145739334,
145739338,
145739341,
145739344,
145739347,
145739352,
145739354,
145739356,
145739359,
145739363,
145739367,
145739370,
145739375,
145739378,
121483455,
145739382,
145739386,
145739391,
145739392,
145739395,
145739400,
145739401,
145739405,
145739407,
145739412,
134764242,
145739420,
145739423,
145739424,
145739427,
144978177,
145739430,
145739432,
145739435,
145739436,
120851739,
145739439,
145739444,
145739446,
122229865,
145739454,
145739455,
145739458,
145739461,
145739462,
145739467,
145739470,
145738748,
81847487,
145739476,
145739479,
145739484,
145739486,
145739489,
126295041,
125104285,
145739497,
145739499,
145739319,
145739504,
145739509,
145739517,
145739519,
145739522,
145739523,
145739527,
145739530,
145739531,
145739534,
145739537,
145739539,
145739540,
145739544,
141063450,
132521136,
145739552,
145739556,
145739557,
145739559,
145739562,
145739566,
145739568,
145739571,
145739572,
145739575,
145739578,
90561976,
145739585,
145739586,
145739591,
145739594,
145739596,
145739600,
145739602,
120797843,
145739608,
90732913,
145739612,
145739614,
145739626,
145739630,
145739632,
124470122,
145739636,
145739640,
145739645,
145739648,
145739653,
145739657,
145739658,
145739660,
145739664,
145739671,
145739676,
145739682,
145739685,
145739687,
145739690,
145739694,
145739696,
145739698,
145739703,
145739704,
145739710,
145739713,
145739716,
145739720,
145739724,
122241605,
145739729,
145739731,
145739735,
141056668,
145739740,
145739748,
145739752,
145739753,
145739758,
145739762,
134979244,
145739767,
145739770,
145739773,
145739775,
145739779,
145739783,
145739784,
145739786,
145739789,
145738544,
145739794,
145739796,
145739800,
145739803,
145739807,
90561812,
145739809,
145739812,
145739814,
145739815,
145739819,
107434835,
139389737,
145739826,
145739828,
145739832,
145739833,
145739840,
145739843,
145739847,
145739851,
145739855,
145739859,
145739863,
145739868,
140847988,
145737942,
145739879,
145739883,
145739886,
145739889,
145739892,
145739894,
125336420,
145737258,
145739899,
145739903,
134073347,
145738061,
145739906,
145739913,
145739916,
90720368,
145739925,
145739927,
145739929,
145739932,
145738356,
145739935,
145739937,
145739941,
145739944,
145739946,
145739947,
145739950,
145739955,
145739956,
128847045,
145739960,
145739964,
145739967,
145739973,
145739975,
145739977,
145739979,
145739984,
145739986,
145739988,
145739992,
145740004,
145740017,
145740021,
145740022,
145740025,
145740029,
145740031,
145740033,
145740034,
145740036,
90580956,
145740043,
145740046,
88127967,
145740049,
145740052,
145740053,
145740055,
139397437,
145740059,
145740067,
145740070,
145740071,
145740074,
145740078,
145740081,
145740084,
145740088,
145740092,
145740095,
145740100,
145740106,
145740109,
145740110,
145740111,
135374862,
145740116,
145740118,
145740122,
145740124,
145740130,
145740133,
145740134,
145740137,
145740139,
145740142,
145740148,
145740154,
145740156,
145740160,
145740163,
145740164,
145740168,
145740172,
145740176,
145740179,
145740183,
145740185,
145740189,
145740193,
145740197,
145740199,
145740203,
145740207,
145740211,
145740213,
145740215,
145740218,
145740221,
145740226,
134491521,
145740228,
145740232,
145740236,
145740243,
145740245,
145740246,
145740251,
145740254,
107918352,
126632464,
145740261,
145739626,
145740269,
145740271,
145740275,
134834815,
145740277,
145740280,
145740284,
145740286,
145740290,
145740293,
145740300,
134062547,
145740306,
145740309,
145740314,
145740318,
101196175,
145740226,
145740330,
145740335,
145740339,
145740345,
145740349,
145740352,
145740356,
145740360,
145740361,
145740367,
145740372,
145740374,
145740378,
145740381,
101200352,
145740387,
145740390,
145740401,
145740403,
145740405,
145740411,
145740413,
145740419,
145740420,
145740423,
145740428,
145740433,
145740435,
145740438,
145740443,
145740448,
145740450,
145740453,
145740456,
145740458,
145740462,
145740467,
145740470,
145740471,
145740473,
145740474,
145740477,
145740479,
145740483,
145740487,
145740501,
145740508,
145740510,
145740511,
101471356,
145740513,
145740514,
145740520,
145740523,
145740527,
145740529,
145740530,
145740533,
145740536,
145740537,
145740540,
145740543,
145740545,
145740549,
145740554,
145740556,
145740558,
145740560,
145740581,
145740583,
139808084,
145740587,
145740590,
145740591,
145740592,
145740594,
145740596,
90758785,
145740602,
120768364,
145740618,
145740622,
145740625,
145740627,
145740629,
145740635,
145740638,
145740640,
145740642,
145740645,
145740651,
145740653,
145740655,
145740656,
145740657,
145740662,
145740665,
118127170,
145740672,
145740674,
145740678,
145740680,
145740684,
137846742,
145740689,
145740692,
145740696,
145740697,
145740700,
145740703,
145738125,
125067727,
145740709,
145740710,
145740712,
145740714,
145740717,
145740718,
145740719,
142645592,
145740723,
145740727,
145740729,
145740731,
145740733,
145740735,
145740738,
145740740,
141044653,
145740742,
80312535,
145740745,
125333075,
145740749,
145740752,
145740753,
145740754,
145740757,
145740767,
145740770,
145740774,
145740776,
145740793,
145740796,
145740798,
90720368,
145740805,
145740807,
145740810,
145740813,
145740817,
145740820,
145740823,
145740831,
145740833,
145740834,
145740837,
145740840,
145740844,
145740846,
145740849,
145740853,
145740858,
137819590,
145740865,
145740870,
145740873,
145740875,
145740879,
145740883,
145740885,
145740887,
145740893,
145737261,
145740901,
145739843,
145740906,
145740914,
145740923,
145740925,
145740927,
145740929,
145740933,
145740067,
145740938,
145740941,
145740942,
145740945,
145740948,
145740950,
145740951,
145740956,
145740960,
145740962,
145523723,
145740972,
145740973,
145740975,
145740978,
145740980,
145740982,
145740987,
145740992,
145740994,
145740998,
145741002,
145741003,
145741006,
145741008,
145741010,
145741012,
145741027,
145741028,
145741031,
145741037,
145741040,
145741043,
145741045,
145741048,
145741051,
145741053,
145741057,
145741059,
145741063,
145741064,
145741068,
145741073,
145741076,
145741080,
145741084,
145741087,
145741090,
145741092,
131328222,
145741095,
145741096,
145741099,
145741101,
145741114,
145741116,
145741118,
145741120,
145740651,
145741125,
145741126,
137838195,
145741132,
145741134,
145741145,
145741149,
145741151,
145741157,
145741160,
145741164,
139891006,
145741167,
145741171,
145741172,
145741173,
134549763,
145741178,
145741179,
145741183,
139427369,
145741198,
145741199,
145741201,
145741205,
145741208,
145741210,
145741215,
145741217,
145741219,
145741221,
145741224,
145741227,
145741228,
145741230,
145741231,
145741234,
145741237,
145741240,
145741245,
145741249,
145741251,
145741256,
145741260,
145741266,
145741271,
145741275,
145741278,
145741283,
145741288,
145741292,
145741293,
145741297,
145741303,
145741307,
145741311,
145741315,
145741318,
145741322,
145741325,
145741327,
145741330,
145741332,
145741334,
145741337,
145741338,
145741342,
145741179,
145741347,
145741348,
145741350,
145741353,
145741357,
145741360,
145741362,
132931513,
145741367,
145741371,
145741373,
145741375,
145741377,
145741379,
145741380,
145741008,
145741384,
145741385,
145741387,
145741390,
145741391,
145741392,
145741396,
145741397,
125088155,
145741403,
145741406,
145741410,
145741412,
145741416,
145741418,
145741420,
145741422,
145740106,
145741423,
145741425,
145741430,
145741435,
145741439,
145741442,
145741445,
145741448,
145741457,
145741458,
145741460,
145741461,
90523892,
145741466,
145741470,
145741473,
145741481,
101208280,
145741487,
145741490,
145741492,
145741495,
145741501,
145741505,
145741511,
145741516,
145741518,
145741521,
145741525,
145741527,
145741528,
145741529,
145741530,
145741543,
145741549,
145741550,
145741555,
145741556,
145741558,
145741561,
145741562,
145741565,
145741568,
145741571,
145741573,
145741579,
145741580,
145741582,
145741584,
145741587,
145741590,
145741592,
145741594,
145739436,
145741601,
145741603,
145741607,
145741609,
145741612,
145741616,
145741619,
145741620,
145741623,
145741627,
145741629,
145741633,
145741636,
145741640,
145741643,
145741644,
145741646,
141492301,
145741653,
145741655,
145741657,
145741660,
145741662,
145741665,
145741670,
145741672,
93304276,
145741679,
145741682,
126929507,
145741688,
145741693,
145741696,
145741699,
145737427,
145741711,
145741714,
145741716,
145741720,
145741722,
145741724,
145741725,
145741727,
145741734,
145741736,
145741737,
145741739,
145741742,
145741744,
145741746,
145741748,
145741751,
145741757,
145741758,
119914832,
145741764,
145741767,
145741769,
145741772,
145741774,
141057338,
145741776,
145741778,
145741779,
145741783,
145741785,
145741787,
145741789,
145741792,
145741799,
145737485,
145741805,
134322053,
124484747,
145741812,
145741818,
145741822,
145741824,
132510733,
108115868,
145741828,
145741830,
145741833,
145741839,
145741842,
145740300,
145741845,
145741847,
145741848,
145741852,
145741854,
145741857,
145741860,
145741865,
145741868,
145741873,
145741874,
145741877,
145741880,
145741883,
145741889,
145741892,
145741897,
145741899,
145741904,
145741909,
145741920,
145741924,
145741927,
145741931,
145741934,
145741937,
145741940,
145741942,
145741943,
145741948,
145741951,
145741953,
145741961,
90562242,
145741965,
145741969,
145741972,
145741974,
145741977,
145741979,
145741984,
145741988,
145741991,
134552803,
145737916,
145741998,
145742001,
145742003,
145742009,
145742012,
145742013,
145742016,
145742021,
145742025,
145742029,
102152740,
145742036,
145742043,
145742047,
145742049,
100998973,
145742055,
145742060,
145742061,
145742065,
145742070,
145742072,
145742075,
145742077,
145742082,
145742087,
145742089,
145742093,
126906197,
145742102,
145742105,
145742111,
145742116,
145742119,
145742125,
145742130,
92597731,
145740280,
145742135,
145742137,
145742139,
145742142,
145742149,
145742150,
145742153,
145742157,
145742160,
145742162,
145742164,
145742166,
145742170,
145742173,
145742176,
145742177,
145742180,
145742185,
145742189,
145742191,
145742193,
145742195,
145742203,
145742206,
145742210,
145742213,
145742216,
145742219,
145742221,
145742222,
145742225,
145742229,
125334051,
145742235,
145742237,
145742252,
145742256,
145742260,
105632372,
145742264,
145742268,
145742270,
145742275,
145742277,
145742281,
145742285,
145742288,
145742290,
145742292,
145742297,
145742299,
145742302,
145742303,
145742309,
145742311,
145742313,
145742316,
145742320,
145742322,
123788498,
145742328,
145742332,
145742334,
145742337,
145742341,
145742346,
145742348,
145742351,
145742354,
145742359,
145742363,
145742365,
145742372,
145742376,
145742377,
145742150,
145742383,
145742001,
126959985,
145742391,
145742393,
145742397,
145742398,
145742400,
145742402,
145742405,
145742407,
145742413,
145742416,
145742419,
145742424,
145742427,
145742430,
145742433,
145742434,
144647126,
145742438,
145742441,
145742444,
145742445,
145742448,
145742452,
145742453,
145742455,
145742457,
145742462,
145742464,
145742469,
145742472,
145742474,
139393964,
145742482,
145742486,
145742488,
145742494,
145742496,
145742498,
145742501,
145742505,
145742507,
145742511,
145742513,
145742515,
145742519,
118128344,
145742527,
145742530,
145742536,
145742539,
145742545,
145742550,
145742551,
125378615,
145742553,
145739964,
145742561,
145742566,
145742571,
145742578,
145742583,
145742585,
145742589,
145742593,
145742596,
145742599,
145742601,
95801111,
145742605,
145742607,
145742610,
145742635,
145742637,
145742639,
145742641,
145742645,
145742648,
145742649,
145742652,
145742654,
145742658,
101993997,
145742662,
145742664,
145742666,
145742669,
145742671,
145742674,
145742676,
145742679,
145742688,
145737423,
145742694,
145742698,
126376481,
145742700,
145742703,
145742707,
145742710,
145742713,
145742714,
145742715,
145742720,
145742721,
145742726,
145742741,
145742742,
86619081,
145742747,
145742752,
145742753,
145742756,
145742759,
145742762,
145742766,
145742771,
145742775,
145742779,
145742782,
145742793,
145742800,
145742801,
145742803,
145742808,
145742810,
145742812,
145742816,
145742817,
145742818,
145742828,
101946828,
145740745,
145742837,
101202712,
145742845,
125338454,
145737569,
145742851,
145742853,
99405662,
145742861,
145742865,
145742869,
145742880,
145742883,
145742885,
145742891,
145742894,
145742898,
145742899,
145742900,
145742902,
145742905,
140851833,
145742918,
145742930,
145742933,
145742935,
145742937,
145742938,
145742940,
145742943,
145738755,
145742951,
145742954,
145742959,
145742963,
145742965,
145742968,
145742975,
145742976,
145742978,
145742982,
145742984,
145742986,
145742991,
145742996,
145743004,
145743008,
145743012,
145743017,
145743019,
145743024,
145743028,
145743031,
145743036,
145743039,
145743042,
145743044,
145743045,
145743047,
145743051,
145743052,
145743055,
145743058,
120818334,
145743066,
145743069,
145743073,
145743076,
145743077,
145742585,
145743082,
145743086,
145743088,
145743089,
145743092,
145743093,
145743096,
145743102,
145743105,
145743110,
145740810,
145743120,
145743122,
145743126,
145743128,
145743137,
145743142,
145743144,
145743147,
145743151,
145743154,
145743156,
145743160,
145743162,
145743167,
145743172,
145743173,
145741833,
145738136,
145743179,
90918537,
145743183,
145737778,
145743188,
145743192,
145743196,
145743201,
145743206,
145743208,
81431671,
145743211,
145743217,
145743222,
145743226,
145743229,
145743232,
145743233,
145743235,
145743239,
145743246,
145743248,
145743252,
145743256,
145743260,
145743267,
145743268,
145738762,
145743275,
145743284,
145743288,
145743290,
132527876,
145743295,
145743300,
145743303,
145743307,
145743309,
145743312,
145737731,
145743315,
145743319,
145743322,
145743325,
145743326,
145743329,
107917224,
145743341,
145743343,
145743346,
144669720,
145743350,
145737300,
145743364,
145743368,
145743372,
145743374,
145743378,
145743382,
145743383,
145738225,
145743400,
145743405,
145743409,
145743410,
145743417,
145743421,
145743424,
145743428,
145743430,
145743433,
145743439,
145743442,
145743446,
90558868,
145743453,
145743457,
145743458,
145743459,
145743465,
145743468,
145743473,
145743475,
145743478,
145743483,
145743486,
145743491,
145743529,
145743532,
145743534,
145743045,
145743540,
145743553,
145743555,
145743558,
145743559,
145743562,
145743563,
145743583,
145743588,
145743592,
145743596,
145743600,
145743603,
145743608,
145743613,
145743618,
145743620,
145743621,
145743624,
145743628,
145743632,
145737256,
145743636,
145743638,
145743642,
145743643,
145743647,
145738879,
145743651,
145743654,
145743656,
145743663,
145743667,
145743670,
145743672,
145743674,
145743676,
145743679,
145743680,
135915354,
109555032,
145743688,
145743691,
145743697,
125361843,
145743702,
145743708,
145743708,
125271594,
145743716,
145743718,
145743720,
145743722,
145743724,
145743725,
145743732,
102477229,
145743735,
145743739,
145743741,
145743744,
145743748,
145743752,
145743756,
145743759,
145743762,
145743765,
145743766,
145743770,
145738566,
145743776,
145742605,
145738479,
145743783,
145743787,
145743792,
145743795,
145743798,
145743803,
145743807,
101196971,
126617340,
145743834,
145743839,
145743368,
145743844,
145743849,
145743856,
145743858,
145743861,
145743865,
145743868,
145743871,
145743875,
145743877,
145738225,
145743883,
145743885,
145743889,
145743891,
145743895,
127122537,
};

void main(int argc, char* argv[])
{

	std::map<int,int> m;
	int iCount=sizeof(a)/sizeof(int);
	for(int ii=0;ii<iCount;ii++)
	{
		m[a[ii]]++;
	}
	std::map<int,int>::iterator it=m.begin();
	for(;it!=m.end();it++)
	{
		if(it->second>1)
		{
			std::cout<<it->first<<" "<<it->second<<"\n";
		}
	}
}
//KaAAABoAAAAqoAAAMwAAAC6gAAAKAAAAMKAAAAUAAAARpAAACgAAABKkAAAFAAAAFKQAAAIAAAAVpAAABQAAABekAAACAAAAGKQAAAoAAAD6pwAADAAAAA==