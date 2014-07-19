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

void GenerateFile(const std::string& sClassName,const std::string& sHeadTag,const std::string& sTemplateFile,const std::string& sCodeFile)
{
	FILE * file=fopen(sTemplateFile.c_str(),"rb");
	if(!file)
	{
		std::cout<<"Can not read from "<<sTemplateFile<<std::endl;
		return;
	}
	long length = 0;
	fseek( file, 0, SEEK_END );
	length = ftell( file );
	fseek( file, 0, SEEK_SET );

	char * buffer=new char[length+1];
	int size=fread(buffer, length, 1, file );	
	buffer[length]=0;
	std::string sContent=buffer;
	delete buffer;

	int iIndex=sContent.find("#CLASSNAME");
	while(iIndex!=std::string::npos)
	{
		sContent.replace(sContent.begin()+iIndex,sContent.begin()+iIndex+10,sClassName);
		iIndex=sContent.find("#CLASSNAME");
	}

	iIndex=sContent.find("#HEADTAG");
	while(iIndex!=std::string::npos)
	{
		sContent.replace(sContent.begin()+iIndex,sContent.begin()+iIndex+8,sHeadTag);
		iIndex=sContent.find("#HEADTAG");
	}
	fclose( file );

	FILE * outFile=fopen(sCodeFile.c_str(),"wb");
	if(!outFile)
	{
		std::cout<<"Can not write to file "<<sCodeFile<<std::endl;
		return;
	}
	fwrite(sContent.c_str(),sContent.size(),1,outFile);
	fclose(outFile);
	std::cout<<"File "<<sCodeFile<<"....OK!"<<std::endl;

}
void main(int argc, char* argv[])
{
	if(argc<2)
	{
		std::cout<<"usage:GenCode ClassName "<<std::endl;
		return;
	}
	std::string sClassName=argv[1];
	std::string sHeadTag=sClassName;
	std::transform(sHeadTag.begin(), sHeadTag.end(), sHeadTag.begin(), toupper);
	std::string sFileHeader=sClassName+".h";
	std::string sFileCpp=sClassName+".cpp";
	
	GenerateFile(sClassName,sHeadTag,"Template.h",sClassName+".h");
	std::cout<<"------------------------------------------------------"<<std::endl;
	GenerateFile(sClassName,sHeadTag,"Template.cpp",sClassName+".cpp");
	
}