/*
 * ParameterList.h
 *
 *  Created on: 23.12.2022
 *      Author: melah
 */

#ifndef PARAMETERLIST_H_
#define PARAMETERLIST_H_


typedef ParameterData::Parameter Parameter;

class ParameterList{
public:
	class ParamEntry{
	public:
		ParamEntry(uint32_t id, Parameter* param);
		ParamEntry(uint32_t id, Parameter* param, ParamEntry* next);
		~ParamEntry();

		uint32_t id;

		Parameter* para;
		ParamEntry* next;
	};

private:
	/*******************************************************
	 * Zeiger auf das eigene Objekt
	********************************************************/
	static ParameterList* instance;

	/*******************************************************
	 * Zeiger auf dem erste Eintrag in der Liste
	********************************************************/
	ParamEntry* m_head;

	/*******************************************************
	 * Zeiger auf dem letzte Eintrag in der Liste
	********************************************************/
	ParamEntry* m_tail;

	/*******************************************************************************
	 * Datenfeld mit den Zeigern auf die Einträge, die die Parameter verwalten.
	 *
	 * Über dieses Datenfeld werden die Parameter, die im Gerät benötigt werden,
	 * gesucht.
	 ******************************************************************************/
	ParamEntry** paraIdField;
	uint32_t paraInFieldCount;

	/*******************************************************************************
	 * Anzahl der Parameter, die in der Liste hinterlegt wurden.
	 ******************************************************************************/
	uint32_t paraEntryCount;

	/*******************************************************************************
	 * Diese Routine fügt ein Parameter am Anfang der Liste hinzu.
	 ******************************************************************************/
	void addParaToHead(uint32_t id, Parameter* param);

	/*******************************************************************************
	 * Diese Routine fügt ein Parameter am Ende der Liste hinzu.
	 ******************************************************************************/
	void addParaToTail(uint32_t id, Parameter* param);

	/*******************************************************************************
	 * Diese Routine fügt ein Parameter zwischen den Anfang und das Ende der
	 * Liste hinzu.
	 ******************************************************************************/
	void addParaBetweenHeadAndTail(uint32_t id, Parameter* param);

	ParamEntry** getParaIdField();



public:
	ParameterList();
	virtual ~ParameterList();
	void addPara( uint32_t id, Parameter* para );
	Parameter* geParameterById(uint32_t id);
	void removePara( uint32_t id );

	void createParaIdField();
};






#endif /* PARAMETERLIST_H_ */
