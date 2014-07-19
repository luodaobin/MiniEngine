del mm.exe
cl mm.cpp  /I "../boost_1_54_0" -DBOOST_DATE_TIME_NO_LIB -DBOOST_REGEX_NO_LIB /EHsc  /link /DEBUG  /PDB:"./c.pdb"  /LIBPATH:D:\workspace\boost_1_54_0\stage\lib
mm.exe