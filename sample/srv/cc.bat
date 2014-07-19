del cc.exe
cl cc.cpp md5.cpp  /I "../../boost_1_55_0" -DBOOST_DATE_TIME_NO_LIB -DBOOST_REGEX_NO_LIB /EHsc  /link /DEBUG  /PDB:"./cc.pdb"  /LIBPATH:D:\workspace\boost_1_55_0\stage\lib
cc.exe