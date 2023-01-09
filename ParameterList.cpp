/*
 * ParameterList.cpp
 *
 *  Created on: 23.12.2022
 *      Author: melah
 */

#include "ParameterList.h"

ParameterList* ParameterList::instance = nullptr;

ParameterList::ParameterList():m_head(nullptr), m_tail(nullptr),
								paraIdField(nullptr),
								paraEntryCount(0), paraInFieldCount(0){
	if(ParameterList::instance == nullptr)
		ParameterList::instance = this;
}
ParameterList::~ParameterList(){

}
ParameterList::ParamEntry::ParamEntry(uint32_t id, Parameter* param):
										id(id), para(param), next(nullptr){
	//next = nullptr;
}
ParameterList::ParamEntry::ParamEntry(uint32_t id, Parameter* param, ParamEntry* next):
										id(id), para(param), next(next){

}
ParameterList::ParamEntry::~ParamEntry(){

}

/*******************************************************************************
 * Diese Routine fügt ein Parameter am Anfang der Liste hinzu.
 ******************************************************************************/
void ParameterList::addParaToHead(uint32_t id, Parameter* param){
	this->m_head = new ParamEntry( id, param, this->m_head );
	this->paraEntryCount += 1;
}

/*******************************************************************************
 * Diese Routine fügt ein Parameter am Ende der Liste hinzu.
 ******************************************************************************/
void ParameterList::addParaToTail(uint32_t id, Parameter* param){
	this->m_tail->next = new ParamEntry( id, param );
	this->m_tail = this->m_tail->next;
	this->paraEntryCount += 1;
}

void ParameterList::addParaBetweenHeadAndTail(uint32_t id, Parameter* param){
	if(this->paraEntryCount == 0) return;

	auto headParaId = this->m_head->para->getValue()->getId();
	auto tailParaId = this->m_tail->para->getValue()->getId();
	auto paraId = param->getValue()->getId();

	uint32_t lowIndex = 0;
	uint32_t highIndex = this->paraEntryCount - 1;

	ParamEntry* entry = this->m_head;
		while( entry != nullptr ) {
			auto lowParaId = entry->para->getValue()->getId();
			auto highParaId = entry->next->para->getValue()->getId();

			if((paraId > lowParaId) && (paraId < highParaId)) {
				entry->next = new ParamEntry( id, param, entry->next );
				entry->next->id = this->paraEntryCount;
				this->paraEntryCount += 1;
				return;
			}
			entry = entry->next;
		}
}

ParameterList::ParamEntry** ParameterList::getParaIdField() {

	ParameterList::ParamEntry** listField =
								new ParameterList::ParamEntry*[this->paraEntryCount];

	ParamEntry* entry = this->m_head;
	for( uint32_t i = 0; i< this->paraEntryCount; i++ ) {
		assert( entry != nullptr );
		listField[i] = entry;
		entry = entry->next;
		this->paraInFieldCount++;
	}

	return listField;
}

void ParameterList::createParaIdField(){
	if(this->paraIdField == nullptr){
		this->paraIdField = getParaIdField();
	}else{
		delete this->paraIdField;
		this->paraIdField = getParaIdField();
	}

}

void ParameterList::addPara( uint32_t id, Parameter* para ){
	//prüfen ob das objekt gültig ist
	if(para == nullptr) return;

    auto paraId = para->getValue()->getId();
	//falls die Liste leer ist, dann wird den erste Eintrag hinzugefügt.
	if( this->m_head == nullptr ) {
			this->m_head = new ParamEntry( id, para );
			this->m_tail = this->m_head;
			this->paraEntryCount = 1;
			return;
	}

	auto headParaId = this->m_head->para->getValue()->getId();
	auto tailParaId = this->m_tail->para->getValue()->getId();
	//falls die Liste nicht leer ist
	//Parameter muss am Anfang hinzugefügt werden wenn die Id der neuen
	//Parameter kleiner als die Id von Parameter am Anfang der Liste ist.
	if(paraId < headParaId){
		//Parameter am Anfang hinzufügen
		addParaToHead(id, para);
		return;
	}

	//Parameter muss am Ende hinzugefügt werden wenn die Id der neuen
	//Parameter größer als die Id von Parameter am Ende der Liste ist.
	if(paraId > tailParaId){
		//Parameter am Ende hinzufügen
		addParaToTail(id, para);
		return;
	}

	addParaBetweenHeadAndTail(id, para);
}

Parameter* ParameterList::geParameterById(uint32_t id){
	if(this->paraEntryCount == 0) return nullptr;
	if(this->paraInFieldCount == 0) return nullptr;
	if(this->paraIdField == nullptr) return nullptr;

	auto headParaId = this->m_head->para->getValue()->getId();
	auto tailParaId = this->m_tail->para->getValue()->getId();
	auto paraId = id;

	uint32_t lowIndex = 0;
	uint32_t highIndex = this->paraEntryCount - 1;

	while(lowIndex <= highIndex){
		uint32_t middle = lowIndex + (highIndex - lowIndex)/2;

		auto middleParaId = this->paraIdField[middle]->para->getValue()->getId();
		if(middleParaId == paraId){
			return this->paraIdField[middle]->para;
		}
		if(middleParaId > paraId){
			highIndex = middle - 1;
		}else if(middleParaId < paraId){
			lowIndex = middle + 1;
		}

		if((lowIndex + 1) == highIndex){
			if(this->paraIdField[lowIndex]->para->getValue()->getId() == paraId)
				return this->paraIdField[lowIndex]->para;
			else if(this->paraIdField[highIndex]->para->getValue()->getId() == paraId)
				return this->paraIdField[highIndex]->para;
			else
				break;
		}


	}
	//falls der Parameter nicht gefunden wurde.
	return nullptr;
}
