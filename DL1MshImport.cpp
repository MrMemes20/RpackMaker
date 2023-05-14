// DL1MshImport.cpp : This file contains the 'main' function. Program execution begins and ends there.
//



#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include <TlHelp32.h>
#include <vector>
#include <stdlib.h>
#include <winternl.h>
#include <set>
#include <stdlib.h>
#include <intrin.h>
#include "include\zlib\zlib.h"

using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::ifstream;
using std::cin;

void importmsh()
{
	////////////////////////////////////////////////////////
	// TWEAK THESE VALUES TO MATCH YOUR INPUT FILES SIZES //

	char inp1[0x2e2943];
	char inp2[0x01];
	char inp3[0x01];
	char inp4[0x01];
	char inp5[0x01];
	char out1[0x2e2943];
	char out2[0x01];
	char out3[0x01];
	char out4[0x01];
	char out5[0x01];

	////////////////////////////////////////////////////////
	
	//0x2e2943

	ifstream is;
	ofstream os;

	is.open("input1.tmp", std::ios::binary); // Header of file (down to .scr)
	is.read(reinterpret_cast<char*>(&inp1), sizeof(inp1));
	int dfcounter = 0;
	z_stream strm;
	os.open("temp1.tmp", std::ios::binary);
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = 0x2e2943;
	strm.avail_out = 0x2e2943;
	strm.next_in = (Bytef *)inp1;
	strm.next_out = (Bytef *)out1;
	deflateInit(&strm, Z_DEFAULT_COMPRESSION);
	//const unsigned char dict1[] = "ÿÿÿÿ";
	//Bytef *dict1a = 0;
	//Bytef bytef1a = 0xFF;
	//deflateSetDictionary(&strm, dict1, 0x100);

		deflate(&strm, Z_NO_FLUSH);
		deflateEnd(&strm);
		//deflateGetDictionary(&strm, dict1a, (uInt*) 0x100);

		os.write(reinterpret_cast<char*>(&out1), sizeof(out1));

	
	//os.close();
	//os.open("dictionary1.tmp", std::ios::binary);
	//os.write(reinterpret_cast<char*>(&strm.next_in), 0x100);
	//os.close();

	is.open("input2.tmp", std::ios::binary); // Materials
	is.read(reinterpret_cast<char*>(&inp2), sizeof(inp2));
	system("pause");
	z_stream strm2;
	strm2.zalloc = Z_NULL;
	strm2.zfree = Z_NULL;
	strm2.opaque = Z_NULL;
	strm2.avail_in = 0x2e2943;
	strm2.avail_out = 0x2e2943;
	strm2.next_in = (Bytef*)inp2;
	strm2.next_out = (Bytef*)out2;
	deflateInit(&strm2, Z_DEFAULT_COMPRESSION);
	deflate(&strm2, Z_NO_FLUSH);
	deflateEnd(&strm2);
	os.open("temp2.tmp", std::ios::binary);
	os.write(reinterpret_cast<char*>(&out2), sizeof(out2));

	is.open("input3.tmp", std::ios::binary); // Under materials (unknown)
	is.read(reinterpret_cast<char*>(&inp3), sizeof(inp3));

	z_stream strm3;
	strm3.zalloc = Z_NULL;
	strm3.zfree = Z_NULL;
	strm3.opaque = Z_NULL;
	strm3.avail_in = 0x2e2943;
	strm3.avail_out = 0x2e2943;
	strm3.next_in = (Bytef*)inp3;
	strm3.next_out = (Bytef*)out3;
	deflateInit(&strm3, Z_DEFAULT_COMPRESSION);
	deflate(&strm3, Z_NO_FLUSH);
	deflateEnd(&strm3);
	os.open("temp3.tmp", std::ios::binary);
	os.write(reinterpret_cast<char*>(&out3), sizeof(out3));

	is.open("input4.tmp", std::ios::binary); // Vertex Buffer
	is.read(reinterpret_cast<char*>(&inp4), sizeof(inp4));

	z_stream strm4;
	strm4.zalloc = Z_NULL;
	strm4.zfree = Z_NULL;
	strm4.opaque = Z_NULL;
	strm4.avail_in = 0x2e2943;
	strm4.avail_out = 0x2e2943;
	strm4.next_in = (Bytef*)inp4;
	strm4.next_out = (Bytef*)out4;
	deflateInit(&strm4, Z_DEFAULT_COMPRESSION);
	deflate(&strm4, Z_NO_FLUSH);
	deflateEnd(&strm4);
	os.open("temp4.tmp", std::ios::binary);
	os.write(reinterpret_cast<char*>(&out4), sizeof(out4));

	is.open("input5.tmp", std::ios::binary); // Face Buffer
	is.read(reinterpret_cast<char*>(&inp5), sizeof(inp5));

	z_stream strm5;
	strm5.zalloc = Z_NULL;
	strm5.zfree = Z_NULL;
	strm5.opaque = Z_NULL;
	strm5.avail_in = 0x2e2943;
	strm5.avail_out = 0x2e2943;
	strm5.next_in = (Bytef*)inp5;
	strm5.next_out = (Bytef*)out5;
	deflateInit(&strm5, Z_DEFAULT_COMPRESSION);
	deflate(&strm5, Z_NO_FLUSH);
	deflateEnd(&strm5);
	os.open("temp5.tmp", std::ios::binary);
	os.write(reinterpret_cast<char*>(&out5), sizeof(out5));

}

void MakePack()
{
	ifstream is;
	ofstream os;
	is.open("fixfile.fix", std::ios::binary);
	BYTE fixstor[0xd80];
	is.read(reinterpret_cast<char*>(&fixstor), sizeof(fixstor));
	os.open("fixtemp.tmp", std::ios::binary);
	os.write(reinterpret_cast<char*>(&fixstor), sizeof(fixstor));
	is.close();
	os.close();
	is.open("fixfile2.fix", std::ios::binary);
	os.open("fixtemp2.tmp", std::ios::binary);
	BYTE fixstor2[0x78];
	is.read(reinterpret_cast<char*>(&fixstor2), sizeof(fixstor2));
	os.write(reinterpret_cast<char*>(&fixstor2), sizeof(fixstor2));
	is.close();
	os.close();
	is.open("fixfile3.fix", std::ios::binary);
	os.open("fixtemp3.tmp", std::ios::binary);
	BYTE fixstor3[0x17c];
	is.read(reinterpret_cast<char*>(&fixstor3), sizeof(fixstor3));
	os.write(reinterpret_cast<char*>(&fixstor3), sizeof(fixstor3));
	is.close();
	os.close();
	cout << "Enter name of input mesh:" << endl;
	string var4;
	cin >> var4;
	is.open(var4 + ".msh", std::ios::binary);
	os.open("temp1.tmp", std::ios::binary);

	BYTE d1;
	BYTE d2;
	BYTE d3;
	BYTE d4;
	BYTE d1a;
	BYTE d2a;
	BYTE d3a;
	BYTE d4a;
	BYTE d1b;
	BYTE d2b;
	BYTE d3b;
	BYTE d4b;
	BYTE d1c;
	BYTE d2c;
	BYTE d3c;
	BYTE d4c;
	BYTE d1ba;
	BYTE d2ba;
	BYTE d3ba;
	BYTE d4ba;
	BYTE d1ca;
	BYTE d2ca;
	BYTE d3ca;
	BYTE d4ca;
	BYTE d3cb;
	BYTE d4cb;
	BYTE stor1;
	int hold0 = 0;
	int hold0a = 0;
	while (1)
	{
		is.read(reinterpret_cast<char*>(&d1), sizeof(d1));
		is.read(reinterpret_cast<char*>(&d2), sizeof(d2));
		is.read(reinterpret_cast<char*>(&d3), sizeof(d3));
		is.read(reinterpret_cast<char*>(&d4), sizeof(d4));
		is.read(reinterpret_cast<char*>(&d1a), sizeof(d1a));
		is.read(reinterpret_cast<char*>(&d2a), sizeof(d2a));
		is.read(reinterpret_cast<char*>(&d3a), sizeof(d3a));
		is.seekg(-6, SEEK_CUR);
		if (d1 == 0x64 && d2 == 0x65 && d3 == 0x66 && d4 == 0x61 && d1a == 0x75 && d2a == 0x6c && d3a == 0x74)
		{
			is.seekg(-0x18, SEEK_CUR);
			for (int quickvar1 = 0; quickvar1 < 0x1e; quickvar1++)
			{
				
				is.read(reinterpret_cast<char*>(&stor1), sizeof(stor1));
				os.write(reinterpret_cast<char*>(&stor1), sizeof(stor1));
				
			}
			hold0 = hold0 + 0x1d;
			break;
		}
	}
	os.close();
	os.open("temp1a.tmp");
	while (1)
	{
		is.read(reinterpret_cast<char*>(&d1), sizeof(d1));
		is.read(reinterpret_cast<char*>(&d2), sizeof(d2));
		is.read(reinterpret_cast<char*>(&d3), sizeof(d3));
		is.read(reinterpret_cast<char*>(&d4), sizeof(d4));
		is.read(reinterpret_cast<char*>(&d1a), sizeof(d1a));
		is.read(reinterpret_cast<char*>(&d2a), sizeof(d2a));
		is.read(reinterpret_cast<char*>(&d3a), sizeof(d3a));
		is.read(reinterpret_cast<char*>(&d4a), sizeof(d4a));
		is.read(reinterpret_cast<char*>(&d1b), sizeof(d1b));
		is.read(reinterpret_cast<char*>(&d2b), sizeof(d2b));
		is.read(reinterpret_cast<char*>(&d3b), sizeof(d3b));
		is.read(reinterpret_cast<char*>(&d4b), sizeof(d4b));
		is.read(reinterpret_cast<char*>(&d1c), sizeof(d1c));
		is.read(reinterpret_cast<char*>(&d2c), sizeof(d2c));
		is.read(reinterpret_cast<char*>(&d3c), sizeof(d3c));
		is.read(reinterpret_cast<char*>(&d4c), sizeof(d4c));
		is.read(reinterpret_cast<char*>(&d1ba), sizeof(d1b));
		is.read(reinterpret_cast<char*>(&d2ba), sizeof(d2b));
		is.read(reinterpret_cast<char*>(&d3ba), sizeof(d3b));
		is.read(reinterpret_cast<char*>(&d4ba), sizeof(d4b));
		is.read(reinterpret_cast<char*>(&d1ca), sizeof(d1c));
		is.read(reinterpret_cast<char*>(&d2ca), sizeof(d2c));
		is.read(reinterpret_cast<char*>(&d3ca), sizeof(d3c));
		is.read(reinterpret_cast<char*>(&d4ca), sizeof(d4c));
		is.read(reinterpret_cast<char*>(&d3cb), sizeof(d3c));
		is.read(reinterpret_cast<char*>(&d4cb), sizeof(d4c));
		is.seekg(-26, SEEK_CUR);
		hold0a++;
		
		if (d1 != 0 && d2 != 0 && d3 != 0 && d4 != 0 && d1a != 0 && d2a != 0 && d3a != 0 && d4a != 0 && d1b != 0 && d2b != 0 && d3b != 0 && d4b != 0 && d1c != 0 && d2c != 0 && d3c != 0 && d4c != 0 && d1ba != 0 && d2ba != 0 && d3ba != 0 && d4ba != 0 && d1ca != 0 && d2ca != 0 && d3ca != 0 && d4ca != 0 && d3cb != 0 && d4cb != 0)
		{
			/*
			for (int quickvar1 = 0; quickvar1 < 25; quickvar1++)
			{
				is.read(reinterpret_cast<char*>(&stor1), sizeof(stor1));
				os.write(reinterpret_cast<char*>(&stor1), sizeof(stor1));
				hold0a = hold0a + 25;
			}
			*/
			break;
		}
		is.read(reinterpret_cast<char*>(&stor1), sizeof(stor1));
		os.write(reinterpret_cast<char*>(&stor1), sizeof(stor1));
	}
	
	os.close();
	os.open("temp2.tmp", std::ios::binary);
	int hold1 = 0;
	while (1)
	{
		is.read(reinterpret_cast<char*>(&d1), sizeof(d1));
		is.read(reinterpret_cast<char*>(&d2), sizeof(d2));
		is.read(reinterpret_cast<char*>(&d3), sizeof(d3));
		is.read(reinterpret_cast<char*>(&d4), sizeof(d4));
		is.read(reinterpret_cast<char*>(&d1a), sizeof(d1a));
		is.read(reinterpret_cast<char*>(&d2a), sizeof(d2a));
		is.read(reinterpret_cast<char*>(&d3a), sizeof(d3a));
		is.read(reinterpret_cast<char*>(&d4a), sizeof(d4a));
		is.read(reinterpret_cast<char*>(&d1b), sizeof(d1b));
		is.read(reinterpret_cast<char*>(&d2b), sizeof(d2b));
		is.read(reinterpret_cast<char*>(&d3b), sizeof(d3b));
		is.read(reinterpret_cast<char*>(&d4b), sizeof(d4b));
		is.seekg(-12, SEEK_CUR);
		is.read(reinterpret_cast<char*>(&stor1), sizeof(stor1));
		
		
		if (d1 == 0x40 && d2 == 0x01 && d3 == 0 && d4 == 0)
		{
			/*
			for (int quickvar1 = 0; quickvar1 < 11; quickvar1++)
			{
				is.read(reinterpret_cast<char*>(&stor1), sizeof(stor1));
				os.write(reinterpret_cast<char*>(&stor1), sizeof(stor1));
				hold1 = hold1 + 11;
			}
			*/
			break;
		}
		hold1++;
		os.write(reinterpret_cast<char*>(&stor1), sizeof(stor1));
	}
	os.close();
	os.open("temp3.tmp", std::ios::binary);
	while (1)
	{
		is.read(reinterpret_cast<char*>(&d1), sizeof(d1));
		is.read(reinterpret_cast<char*>(&d2), sizeof(d2));
		is.read(reinterpret_cast<char*>(&d3), sizeof(d3));
		is.read(reinterpret_cast<char*>(&d4), sizeof(d4));
		is.read(reinterpret_cast<char*>(&d1a), sizeof(d1a));
		is.read(reinterpret_cast<char*>(&d2a), sizeof(d2a));
		is.read(reinterpret_cast<char*>(&d3a), sizeof(d3a));
		is.read(reinterpret_cast<char*>(&d4a), sizeof(d4a));
		is.read(reinterpret_cast<char*>(&d1b), sizeof(d1b));
		is.read(reinterpret_cast<char*>(&d2b), sizeof(d2b));
		is.read(reinterpret_cast<char*>(&d3b), sizeof(d3b));
		is.read(reinterpret_cast<char*>(&d4b), sizeof(d4b));
		is.seekg(-12, SEEK_CUR);
		is.read(reinterpret_cast<char*>(&stor1), sizeof(stor1));
		if (d1 == 0x00 && d2 == 0x00 && d3 == 0x01 && d4 == 0x00 && d1a == 0x02 && d2a == 0x00)
		{
			/*
			for (int quickvar1 = 0; quickvar1 < 11; quickvar1++)
			{
				is.read(reinterpret_cast<char*>(&stor1), sizeof(stor1));
				os.write(reinterpret_cast<char*>(&stor1), sizeof(stor1));
				hold1 = hold1 + 11;
			}
			*/
			os.write(reinterpret_cast<char*>(&stor1), sizeof(stor1));
			break;
		}
	}
	int hold2 = 0;
	while (1)
	{
		is.read(reinterpret_cast<char*>(&d1), sizeof(d1));
		is.read(reinterpret_cast<char*>(&d2), sizeof(d2));
		is.read(reinterpret_cast<char*>(&d3), sizeof(d3));
		is.read(reinterpret_cast<char*>(&d4), sizeof(d4));
		is.read(reinterpret_cast<char*>(&d1a), sizeof(d1a));
		is.read(reinterpret_cast<char*>(&d2a), sizeof(d2a));
		is.read(reinterpret_cast<char*>(&d3a), sizeof(d3a));
		is.read(reinterpret_cast<char*>(&d4a), sizeof(d4a));
		is.read(reinterpret_cast<char*>(&d1b), sizeof(d1b));
		is.read(reinterpret_cast<char*>(&d2b), sizeof(d2b));
		is.read(reinterpret_cast<char*>(&d3b), sizeof(d3b));
		is.read(reinterpret_cast<char*>(&d4b), sizeof(d4b));
		is.seekg(-12, SEEK_CUR);
		is.read(reinterpret_cast<char*>(&stor1), sizeof(stor1));
		
		
		if (d1 == 0x51 && d2 == 0x01 && d3 == 0 && d4 == 0)
		{
			/*
			for (int quickvar1 = 0; quickvar1 < 11; quickvar1++)
			{
				is.read(reinterpret_cast<char*>(&stor1), sizeof(stor1));
				os.write(reinterpret_cast<char*>(&stor1), sizeof(stor1));
				hold2 = hold2 + 11;
			}
			*/
			break;
		}
		hold2++;
		os.write(reinterpret_cast<char*>(&stor1), sizeof(stor1));
	}
	os.close();
	BYTE underheader1[8] = { 0x01, 0,0,0, 0x12, 0, 0x02, 0x12};
	string var2;
	cout << "Input name:" << endl;
	cin >> var2;
	os.open(var2 + ".rpack", std::ios::binary);
	BYTE header1[20] = { 0x52, 0x50, 0x36, 0x4C, 0x01, 0x00, 0x00, 0x00,  0, 0, 0, 0, 0x05, 0, 0, 0, 0x05, 0, 0, 0 };
	os.write(reinterpret_cast<char*>(&header1), sizeof(header1));
	BYTE header2[4] = { 0x01, 0, 0, 0 };
	os.write(reinterpret_cast<char*>(&header2), sizeof(header2));
	cout << "Input size:" << endl;
	int var3;
	cin >> var3;
	//int var3bswap;
	//var3bswap = std::byteswap(var3);
	//var3bswap = var3 << 4;
	os.write(reinterpret_cast<char*>(&var3), sizeof(var3));
	os.write(reinterpret_cast<char*>(&header2), sizeof(header2));
	os.write(reinterpret_cast<char*>(&underheader1), sizeof(underheader1));
	int uhoffset1 = 264;
	//int uhoffset1bswap = std::byteswap(uhoffset1);
	//uhoffset1bswap = uhoffset1 << 4;
	os.write(reinterpret_cast<char*>(&uhoffset1), sizeof(uhoffset1));
	BYTE underheader1b[4] = { 0x54, 0xA3, 0x2C, 0 };
	os.write(reinterpret_cast<char*>(&underheader1b), sizeof(underheader1b));
	int uhsize1 = 78;
	os.write(reinterpret_cast<char*>(&uhsize1), sizeof(uhsize1));
	BYTE underheader1c[4] = { 0xBA, 0x09, 0x08, 0 };
	os.write(reinterpret_cast<char*>(&underheader1c), sizeof(underheader1c));
	BYTE underheader2[4] = { 0x10, 0x00, 0x04, 0x02 };
	os.write(reinterpret_cast<char*>(&underheader2), sizeof(underheader2));
	int uhoffset2 = uhoffset1 + uhsize1;
	os.write(reinterpret_cast<char*>(&uhoffset2), sizeof(uhoffset2));
	BYTE underheader2b[4] = { 0x40, 0x34, 0x2C, 06 };
	os.write(reinterpret_cast<char*>(&underheader2b), sizeof(underheader2b));
	int uhsize2 = 3456;
	os.write(reinterpret_cast<char*>(&uhsize2), sizeof(uhsize2));
	BYTE underheader2c[4] = { 0x63, 0x14, 0x0F, 00 };
	os.write(reinterpret_cast<char*>(&underheader2c), sizeof(underheader2c));
	BYTE underheader3[4] = { 0x11, 0x00, 0x02, 0x02 };
	os.write(reinterpret_cast<char*>(&underheader3), sizeof(underheader3));
	int uhoffset3 = uhoffset1 + uhsize1 + uhsize2;
	os.write(reinterpret_cast<char*>(&uhoffset3), sizeof(uhoffset3));
	BYTE underheader3b[4] = { 0x44, 0x29, 0x2E, 00 };
	os.write(reinterpret_cast<char*>(&underheader3b), sizeof(underheader3b));
	int uhsize3 = 78;
	os.write(reinterpret_cast<char*>(&uhsize3), sizeof(uhsize3));
	BYTE underheader3c[4] = { 0x63, 0x14, 0x0F, 00 };
	os.write(reinterpret_cast<char*>(&underheader3c), sizeof(underheader3c));
	BYTE underheader4[4] = { 0xF0, 00, 0x02, 0x02 };
	os.write(reinterpret_cast<char*>(&underheader4), sizeof(underheader4));
	int uhoffset4 = uhoffset1 + uhsize1 + uhsize2 + uhsize3;
	os.write(reinterpret_cast<char*>(&uhoffset4), sizeof(uhoffset4));
	BYTE underheader4b[4] = { 0x4D, 0x5D, 0xBB, 05 };
	os.write(reinterpret_cast<char*>(&underheader4b), sizeof(underheader4b));
	int uhsize4 = hold1 - 1;
	os.write(reinterpret_cast<char*>(&uhsize4), sizeof(uhsize4));
	BYTE underheader4c[4] = { 0x61, 0x14, 0x01, 00 };
	os.write(reinterpret_cast<char*>(&underheader4c), sizeof(underheader4c));
	BYTE underheader5[4] = { 0xF1, 00, 0x02, 0x02 };
	os.write(reinterpret_cast<char*>(&underheader5), sizeof(underheader5));
	int uhoffset5 = uhoffset1 + uhsize1 + uhsize2 + uhsize3 + uhsize4 - 1;
	os.write(reinterpret_cast<char*>(&uhoffset5), sizeof(uhoffset5));
	BYTE underheader5b[4] = { 0x7C, 0x72, 0x84, 0x03 };
	os.write(reinterpret_cast<char*>(&underheader5b), sizeof(underheader5b));
	int uhsize5 = hold2;
	os.write(reinterpret_cast<char*>(&uhsize5), sizeof(uhsize5));
	BYTE underheader5c[4] = { 0x61, 0x14, 0x01, 00 };
	os.write(reinterpret_cast<char*>(&underheader5c), sizeof(underheader5c));
	BYTE underheaderfill1[48] = { 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	os.write(reinterpret_cast<char*>(&underheaderfill1), sizeof(underheaderfill1));
	BYTE list1[12] = { 00, 00, 00, 00, 01, 00, 02, 00, 00, 00, 00, 00 };
	BYTE list2[12] = { 00, 00, 00, 00, 00, 00, 02, 00, 00, 00, 00, 00 };
	BYTE list3[12] = { 00, 00, 00, 00, 02, 00, 02, 00, 00, 00, 00, 00 };
	BYTE list4[12] = { 00, 00, 00, 00, 03, 00, 02, 00, 00, 00, 00, 00 };
	BYTE list5[12] = { 00, 00, 00, 00, 04, 00, 02, 00, 00, 00, 00, 00 };
	os.write(reinterpret_cast<char*>(&list1), sizeof(list1));
	os.write(reinterpret_cast<char*>(&uhsize1), sizeof(uhsize1));
	os.write(reinterpret_cast<char*>(&list2), sizeof(list2));
	os.write(reinterpret_cast<char*>(&uhsize2), sizeof(uhsize2));
	os.write(reinterpret_cast<char*>(&list3), sizeof(list3));
	os.write(reinterpret_cast<char*>(&uhsize3), sizeof(uhsize3));
	os.write(reinterpret_cast<char*>(&list4), sizeof(list4));
	os.write(reinterpret_cast<char*>(&uhsize4), sizeof(uhsize4));
	os.write(reinterpret_cast<char*>(&list5), sizeof(list5));
	os.write(reinterpret_cast<char*>(&uhsize5), sizeof(uhsize5));
	is.close();
	is.open("fixtemp2.tmp", std::ios::binary);
	BYTE s1[78];
	is.read(reinterpret_cast<char*>(&s1), sizeof(s1));
	os.write(reinterpret_cast<char*>(&s1), sizeof(s1));
	is.close();
	is.open("fixtemp.tmp", std::ios::binary);
	BYTE s2[3456];
	is.read(reinterpret_cast<char*>(&s2), sizeof(s2));
	os.write(reinterpret_cast<char*>(&s2), sizeof(s2));
	is.close();
	is.open("fixtemp3.tmp", std::ios::binary);
	BYTE s3[78];
	is.read(reinterpret_cast<char*>(&s3), sizeof(s3));
	os.write(reinterpret_cast<char*>(&s3), sizeof(s3));
	is.close();
	is.open("temp2.tmp", std::ios::binary);
	BYTE s4;
	while (1)
	{
		is.read(reinterpret_cast<char*>(&s4), sizeof(s4));
		
		if (is.eof() != 0)
		{
			break;
		}
		os.write(reinterpret_cast<char*>(&s4), sizeof(s4));
	}
	is.close();
	is.open("temp3.tmp", std::ios::binary);
	while (1)
	{
		is.read(reinterpret_cast<char*>(&s4), sizeof(s4));

		if (is.eof() != 0)
		{
			break;
		}
		os.write(reinterpret_cast<char*>(&s4), sizeof(s4));
	}
}

int main()
{
	string r1;
	cin >> r1;
	if (r1 == "importmsh")
	{
		importmsh();
	}
	if (r1 == "MakePack")
	{
		MakePack();
	}
	
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
