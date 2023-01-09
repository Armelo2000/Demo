//============================================================================
// Name        : CoreParam.cpp
// Author      : Armel
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include <array>
#include "ParameterList.h"
using namespace std;

using custombyte = unsigned char ;

template< typename T > std::array< custombyte, sizeof(T) >  to_bytes( const T& object )
{
    std::array< custombyte, sizeof(T) > bytes ;

    const custombyte* begin = reinterpret_cast< const custombyte* >( std::addressof(object) ) ;
    const custombyte* end = begin + sizeof(T) ;
    std::copy( begin, end, std::begin(bytes) ) ;

    return bytes ;
}

class MemoryData{
	static const uint8_t OFFSET = 6;
public:
	MemoryData(uint32_t id, uint8_t valueSize, uint8_t valueCnt): ownId(id),
	byteCount(valueSize*valueCnt), size(valueSize), paraSetCount(valueCnt){
		ptByteData = new uint8_t[valueSize*valueCnt + OFFSET];
	}
	~MemoryData(){
		delete ptByteData;
	}

	uint8_t *ptByteData;
	uint32_t ownId;
	uint32_t *value;
	uint16_t byteCount;
	uint8_t size;
	uint8_t paraSetCount;

	void buildFrame(){
		if(byteCount > 0){
			//ID
			for(int i=0; i<4; i++){
				ptByteData[i] = (ownId >> (i*8)) & 0xFF;
			}
			//size
			ptByteData[4] = (size & 0xFF);
			//Paraset
			ptByteData[5] = (paraSetCount & 0xFF);
			uint8_t *tmpValue = (uint8_t *)value;
			for(int i=0; i<byteCount; i++){
				ptByteData[i+OFFSET] = tmpValue[i];
			}

		}
	}
};

class Param{
public:
	uint32_t id;
	uint32_t *value;
	uint32_t *defaultValue;

	void buildFrame(){

	}
};


int main() {
	Test *ptTest = new Test();
/*
	uint32_t data[4] = {12, 90, 5, 345};
	uint32_t defaultdata[4] = {230, 18, 76, 190};
	Param pa;
	Param* p = &pa;
	p->id = 120;
	p->value = data;
	p->defaultValue = defaultdata;

	MemoryData *mData = new MemoryData(100, 4, 4);
	mData->value = data;
	mData->buildFrame();

	auto c = to_bytes(data);
	auto b = to_bytes(pa);
*/

	auto param1 = ptTest->buildParameter1(125);
	auto param2 = ptTest->buildParameter2(305);
	auto param3 = ptTest->buildParameter3(15);
	auto param4 = ptTest->buildParameter4(202);

	auto id = param1->getValue()->getId();
	auto size = param1->getValue()->getSize();
 	auto value = param1->getValue();


	ParameterList* paraList = new ParameterList();
	paraList->createParaIdField();
	paraList->addPara(0, param1);
	paraList->addPara(0, param2);
	paraList->addPara(0, param3);
	paraList->addPara(0, param4);


	paraList->createParaIdField();
	paraList->createParaIdField();
	auto p1 = paraList->geParameterById(param1->getValue()->getId());
	auto p2 = paraList->geParameterById(param2->getValue()->getId());
	auto p3 = paraList->geParameterById(param3->getValue()->getId());
	auto p4 = paraList->geParameterById(param4->getValue()->getId());
	auto p1Val = p1->getValue();
	auto piMem = p1->getMemory();

	cout << "" << endl; // prints 
	return 0;
}
