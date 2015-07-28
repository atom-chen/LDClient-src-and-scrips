 /*@@

	Copyright (c) Beijing Second Laboratory Game Studio. All rights reserved. 
	
	Created_datetime : 	2013-6-7 14:23
	
	File Name :	NNDB.h
	
	Author : zhuhuangqing; 
	
	Description : ���ݿ��ɾ�Ĳ����������ֵ�Եķ�ʽ;
	
	Change List :
				������;
				1,�����޸Ĳ�������SetDataToDB("1", "testData");
				2,��ѯ��������GetDataFromDB("1");
				3,ɾ����������DelDataFromDB("1");
@@*/

#ifndef NNDB_H
#define NNDB_H


#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
//#include "sqlite3.h"
#endif
#include <string>
#include <stdio.h>
using namespace std;

class NNDB
{

public:
	static NNDB* getInstance();
	/* @brief �����޸ļ�¼;
     */
	bool			SetData( const char* key, const char* value );

	/* @brief ��ȡ��¼;
     */
	const char*		GetData( const char* key );

	/* @brief ɾ����¼;
     */
	bool			delData( const char* key );

protected:
	/* @brief ��ʼ��DB;
     */
	bool			_initDB( void );

	/* @brief �ͷ�DB;
     */
	void			_freeDB( void );

	/* @brief ��ʼ����;
     */
	bool			_initTables( void );
	

protected:
	NNDB( void );
	~NNDB( void );

private:
	static NNDB           *m_instance;
	bool			m_hasInit;						// �Ƿ��Ѿ���ʼ����;
	std::string		m_storagePath;					// �洢·���������DB��·��;
#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	//sqlite3*		m_dbPtr;						// ���ݿ�ָ��;
	//sqlite3_stmt*	m_stmt_select;					// ��ѯԤ����;	
	//sqlite3_stmt*	m_stmt_remove;					// ɾ��Ԥ����;
	//sqlite3_stmt*	m_stmt_update;					// ��������Ԥ����;
#endif
};
#endif