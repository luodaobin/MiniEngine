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

#include <string>
class Base64
{

public:

	// 63rd char used for Base64 code
	static const char  CHAR_63 = '+';

	// 64th char used for Base64 code
	static const char  CHAR_64 = '/';

	// Char used for padding
	static const char CHAR_PAD = '=';

public:

	// Encodes binary data to Base64 code
	// Returns size of encoded data.
	static int Encode(const unsigned char* inData, int dataLength, std::string& outCode);

	// Decodes Base64 code to binary data
	// Returns size of decoded data.
	static int Decode(const std::string& inCode, unsigned char* outData);

	// Returns maximum size of decoded data based on size of Base64 code.
	static int GetDataLength(int codeLength);

	// Returns maximum length of Base64 code based on size of uncoded data.
	static int GetCodeLength(int dataLength);

};

// Encodes binary data to Base64 code
// Returns size of encoded data.
int Base64::Encode(const unsigned char* inData, int dataLength, std::string& outCode)
{


	// output buffer which holds code during conversation
	int len = GetCodeLength( dataLength );
	char* out = new char[ len ];

	// charachers used by Base64
	static const char alph[] = 
	{ 
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
		'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
		'0','1','2','3','4','5','6','7','8','9',CHAR_63,CHAR_64
	};

	// mask - first six bits
	const int mask = 0x3F;

	// used as temp 24-bits buffer
	union
	{
		unsigned char bytes[ 4 ];
		unsigned int block;
	} buffer;

	// coversation is done by taking three bytes at time of input data int temp
	// then four six-bits values are extracted, converted to base64 characters
	// and at the end they are written to output buffer
	for( int i = 0, j = 0, left = dataLength; i < dataLength; i += 3, j += 4, left -= 3 )
	{
		//------------------------
		// filling temp buffer

		// get first byte and puts it at MSB position in temp buffer
		buffer.bytes[ 2 ] = inData[ i ];

		// more data left?
		if( left > 1 )
		{
			// get second byte and puts it at middle position in temp buffer
			buffer.bytes[ 1 ] = inData[ i + 1 ];
			// more data left?
			if( left > 2 )
				// get third byte and puts it at LSB position in temp buffer
				buffer.bytes[ 0 ] = inData[ i + 2 ];
			else
				// zero-padding of input data (last bytes)
				buffer.bytes[ 0 ] = 0;
		}
		else
		{
			// zero-padding of input data (last two bytes)
			buffer.bytes[ 1 ] = 0;
			buffer.bytes[ 0 ] = 0;
		}

		//------------------------
		// constructing code from temp buffer
		// and putting it in output buffer

		// extract first and second six-bit value from temp buffer
		// and convert is to base64 character
		out[ j ] = alph[ ( buffer.block >> 18 ) & mask ];
		out[ j + 1 ] = alph[ ( buffer.block >> 12 ) & mask ];
		// more data left?
		if( left > 1 )
		{
			// extract third six-bit value from temp buffer
			// and convert it to base64 character
			out[ j + 2 ] = alph[ ( buffer.block >> 6 ) & mask ];
			// more data left?
			if( left > 2 )
				// extract forth six-bit value from temp buffer
				// and convert it to base64 character
				out[ j + 3 ] = alph[ buffer.block & mask ];
			else
				// pad output code
				out[ j + 3 ] = CHAR_PAD;
		}
		else
		{
			// pad output code
			out[ j + 2 ] = CHAR_PAD;
			out[ j + 3 ] = CHAR_PAD;
		}
	}

	outCode.clear();
	outCode.append( out, len );
	delete[] out;
	return len;
}

// Decodes Base64 code to binary data
// Returns size of decoded data.
int Base64::Decode(const std::string& inCode, unsigned char * outData)
{

	// used as temp 24-bits buffer
	union
	{
		unsigned char bytes[ 4 ];
		unsigned int block;
	} buffer;
	buffer.block = 0;

	// number of decoded bytes
	int j = 0;

	for(unsigned  int i = 0; i < inCode.size(); i++ )
	{
		// position in temp buffer
		int m = i % 4;

		wchar_t x = inCode[ i ];
		int val = 0;

		// converts base64 character to six-bit value
		if( x >= 'A' && x <= 'Z' )
			val = x - 'A';
		else if( x >= 'a' && x <= 'z' )
			val = x - 'a' + 'Z' - 'A' + 1;
		else if( x >= '0' && x <= '9' )
			val = x - '0' + ( 'Z' - 'A' + 1 ) * 2;
		else if( x == CHAR_63 )
			val = 62;
		else if( x == CHAR_64 )
			val = 63;

		// padding chars are not decoded and written to output buffer
		if( x != CHAR_PAD )
			buffer.block |= val << ( 3 - m ) * 6;
		else
			m--;

		// temp buffer is full or end of code is reached
		// flushing temp buffer
		if( m == 3 || x == CHAR_PAD )
		{
			// writes byte from temp buffer (combined from two six-bit values) to output buffer
			outData[ j++ ] = buffer.bytes[ 2 ];
			// more data left?
			if( x != CHAR_PAD || m > 1 )
			{
				// writes byte from temp buffer (combined from two six-bit values) to output buffer
				outData[ j++ ] = buffer.bytes[ 1 ];
				// more data left?
				if( x != CHAR_PAD || m > 2 )
					// writes byte from temp buffer (combined from two six-bit values) to output buffer
					outData[ j++ ] = buffer.bytes[ 0 ];
			}

			// restarts temp buffer
			buffer.block = 0;
		}

		// when padding char is reached it is the end of code
		if( x == CHAR_PAD )
			break;
	}

	return j;
}

// Returns maximum size of decoded data based on size of Base64 code.
int Base64::GetDataLength(int codeLength)
{
	return codeLength - codeLength / 4;
}

// Returns maximum length of Base64 code based on size of uncoded data.
int Base64::GetCodeLength(int dataLength)
{
	int len = dataLength + dataLength / 3 + (int)( dataLength % 3 != 0 );

	// output code size must be multiple of 4 bytes
	if( len % 4 )
		len += 4 - len % 4;

	return len;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CardPieces		// 玩家的卡牌碎片数据
{
	int m_nCardId;
	int m_nNum;

	CardPieces()
	{
		memset(this, 0, sizeof(*this));
	}
};
void main(int argc, char* argv[])
{
	std::string sDecodeString="VgEAAAEAAAC5AQAAAQAAAHEDAAABAAAAAAQAAAoAAAAWBAAAAgAAAD8FAAABAAAA+gUAABQAAAD6pwAAMAAAAA==";
	//std::string sDecodeString="KaAAABoAAAAqoAAAMwAAAC6gAAAKAAAAMKAAAAUAAAARpAAACgAAABKkAAAFAAAAFKQAAAIAAAAVpAAABQAAABekAAACAAAAGKQAAAoAAAD6pwAADAAAAA==";
	int nTotalNum=11;
	CardPieces* pPieces = new CardPieces[nTotalNum];
	Base64::Decode( sDecodeString,(unsigned char *)pPieces);
	for ( int i = 0; i < nTotalNum; i++)
	{
		std::cout<<"["<<pPieces[i].m_nCardId<<"]"<<pPieces[i].m_nNum<<std::endl;
		
	}
	
}
//KaAAABoAAAAqoAAAMwAAAC6gAAAKAAAAMKAAAAUAAAARpAAACgAAABKkAAAFAAAAFKQAAAIAAAAVpAAABQAAABekAAACAAAAGKQAAAoAAAD6pwAADAAAAA==