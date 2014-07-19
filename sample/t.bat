del t.exe
cl t.cpp  /I "../boost_1_54_0" -DBOOST_DATE_TIME_NO_LIB -DBOOST_REGEX_NO_LIB /EHsc /Zi /link /DEBUG  /PDB:"./t.pdb"  /LIBPATH:D:\workspace\boost_1_54_0\stage\lib libzlib.lib
t.exe