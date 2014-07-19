del srv.exe
cl srv.cpp  /I "../../boost_1_55_0" -DBOOST_DATE_TIME_NO_LIB -DBOOST_REGEX_NO_LIB /EHsc  /link /DEBUG  /PDB:"./srv.pdb"  /LIBPATH:D:\workspace\boost_1_55_0\stage\lib
srv.exe