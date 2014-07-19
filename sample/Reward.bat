del Reward.exe
cl Reward.cpp  /I "../boost_1_54_0" -DBOOST_DATE_TIME_NO_LIB -DBOOST_REGEX_NO_LIB /EHsc  /link /DEBUG  /PDB:"./m.pdb"  /LIBPATH:D:\workspace\boost_1_54_0\stage\lib libzlib.lib
Reward.exe