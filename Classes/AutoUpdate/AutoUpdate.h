
#ifndef __AUTO_UPDATE_H__
#define __AUTO_UPDATE_H__
#include "cocos2d.h"
#include <pthread.h>
//#include <curl/curl.h>
//#include "curl/easy.h"
#include <string>
using namespace cocos2d;
#define M_SIZE								1048576
#define BUFFER_SIZE							8192							
#define MAX_FILENAME						512
#include "UpdateLayer.h"

typedef void (CCObject::*SEL_UpdateCallBackFunc)(UpdateUnit unit);
#define updatecallback_selector(_SELECTOR) (SEL_UpdateCallBackFunc)(&_SELECTOR)
class AutoUpdate : public CCObject
{
public:
	/* @brief ������ڣ��������µ��߳�;
	 * ����ios�в�����ʹ�����߳�ȥ���ӷ���������ֹ���̼߳��������Դ˴��ᵥ��һ���߳��������ļ�����;
     */
	bool			AutoUpdateVersion(CCObject*obj, SEL_UpdateCallBackFunc fun);
	//void* beginUpdateVersion( void *arg );
	/* @brief ����Ƿ����µİ汾;
     */
	int		CheckUpdate( void );

	/* @brief ����;
     */
    int		Update( void );
	static AutoUpdate* getInstance();
public:
	/* @brief ��ȡURL;
     */
	//inline const char* GetUrl( void ) const { return m_url.c_str(); };
    
    /* @brief ����URL;
     */
	void SetUrl( const char* url );

	/* @brief ��ȡ��ԴURL;
     */
	inline const char* GetResUrl( void ) const { return m_resUrl.c_str(); };
    
    /* @brief ������Դ��URL;
     */
	inline void SetResUrl( const char* resUrl ) { m_resUrl = resUrl; };
    
    /* @brief ��ȡ�汾URL.
     */
	inline const char* GetVersionFileUrl( void ) const { return m_versionFileUrl.c_str(); };
    
    /* @brief ���ð汾��URL.
     */
    inline void SetVersionFileUrl( const char* versionFileUrl )  { m_versionFileUrl = versionFileUrl; };

	/* @brief ��ȡ�洢��ַ;
     */
    inline const char* GetStoragePath( void ) const { return m_storagePath.c_str(); };

	/* @brief ���ô洢��ַ;
     */
    void SetStoragePath( const char* storagePath );
    
    /* @brief ��ȡ��ǰ�汾;
     */
    std::string GetVersion( void );
    
    /* @brief ɾ����¼�İ汾;
     */
    void DeleteVersion( void );

	void			_setSearchPath( void );																	// ���ò�ѯ·��;

	//std::string		_generateMd5( const char* fileName );													// ����NNMD5��;
	bool			_uncompress( std::string outFileName, std::string strFileIndex = "" );					// ��ѹ;
	void HandleSaveVersion();						// �����̱߳���汾�ţ�ֻAndroidʹ��
	int getDownVersion();
	int getDownCount();
	int getTotalZipCount();
public:
	AutoUpdate( void );
	~AutoUpdate( void );

	bool			_downLoad(std::string outFileName);														// �����ļ�;
	void			_checkStoragePath( void );																// ���洢·��������洢��·������/�������/;
	bool			_checkRes(std::string outFileName,std::string willDownMD5);								// �����Դ�Ƿ�����;																// �Ƚ���ԴNNMD5��;
	void			_deleteFile( const char* fileName );													// ɾ��ָ���ļ�;
	bool			_isExistDirectory( const char* path );													// �Ƿ���Ŀ¼;
	bool			_createDirectory( const char* path );													// ����Ŀ¼;
	
	bool			_delOldRes( void );																		// ɾ������Դ;

private:
    std::string		m_storagePath;					// �洢·���������ص�·��;
    std::string		m_willDownVersion;				// ��Ҫ���µ���Դ�汾��Ϣ;
    std::string		m_resUrl;						// ��Դ����URL��ַ;(��̬�仯��)
    std::string		m_versionFileUrl;				// �汾�ļ�����URL��ַ;
	std::string		m_url;							// �汾�����ļ�ǰ׺����url��������.zip������
	std::map<std::string, UpdateContent>
					m_needUpdateTable;				// ��Ҫ��������;
	
	std::string		m_compressPath;					// ѹ��·��;
	int             m_recordedVersion;              // ���ذ汾�ţ�ֻAndroidʹ��
	std::string     m_willDownVersionToSave;        // Ҫ���浽���صİ汾�ţ�ֻAndroidʹ��

public:
	SEL_UpdateCallBackFunc m_callBackFun;
	CCObject * m_obj;
	SEL_UpdateCallBackFunc m_callBackFun1;
	int				m_count;						// ���´���;
	int				m_zipFileCount;					// ��Ҫ����zip�ļ�����;
	std::vector<UpdateContent> m_updateList;
	static AutoUpdate*m_instance;
};
#endif