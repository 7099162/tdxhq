#pragma once

//=====================loginlbs==================
/* ��
//��¼��һ�������ݸ�ʽ
//Э�̻�ȡ��¼��������ַ�Ͷ˿�
DWORD dwSize;//����С
DWORD ProtolNum;//Э��� 0x00001401
WORD  wStatus;//0x00C8
DWORD Version;//0x60900000 Э��汾
DWORD unknow;//0XFFFFFFFF

WORD  wUserNameLen;//�û�����
char  UserName[ wUserNameLen ];//�û���

WORD  wUnknow;//0x 0000
DWORD  wLangId;// 0x 0804 = 2052

DWORD  dwUnknowLen;//δ֪���鳤��
DWORD Unknow[ dwUnknowLen ];//δ֪����

DWORD  dwIPLen;//IP�����С
DWORD  IP[ dwIPLen ]; //IP ����

DWORD  dwIP2Len;
DWORD  IP2[ dwIP2Len ];
*/

/* ��
//���ص�¼��������ַ�Ͷ˿�
DWORD dwSize;//����С
DWORD ProtolNum;//Э��� 0x0000 1501
DWORD  dwStatus;//0x0000 00C8
DWORD  dwStatus2;//0x0000 00C8 ���ؽ��

DWORD dwIPsize;//IP����

	DWROD dwIP;//IP��ַ
	DWORD dwUnknow;//δ֪
	WORD  wUnknow;//δ֪
	DWORD dwPortSize;
	WORD  wPort[ dwPortSize ];

	DWROD dwIP;//IP��ַ
	DWORD dwUnknow;//δ֪
	WORD  wUnknow;//δ֪
	DWORD dwPortSize;
	WORD  wPort[ dwPortSize ];

DWORD dwUnknow;//δ֪
DWORD dwUnknow;//δ֪ 0x 00 12 00 01
DWORD dwIP;//����WANIP
DWORD dwUnknow;//δ֪
DWORD dwUnknow;//δ֪
*/
//=====================loginlbs==================





//====================dologinlink===============
/*�ڶ����ݰ�
//��
//=======Э����Կ========
DWORD dwSize;
DWORD dwProtocal;//0x 00001104
WORD  wRes;// 0x 00c8
WORD  wKey_N_Size;//0x 0040
char key_n[wKey_N_Size];
WORD  wKeySize;
char key_e[wKey_e_Size];
*/

//��
//====================dologinlink===============



#include <sys/types.h>

#if defined(_MSC_VER)
	//
	// Windows/Visual C++
	//
	typedef signed __int8			int8;
	typedef unsigned __int8			uint8;
	typedef signed __int16			int16;
	typedef unsigned __int16		uint16;
	typedef signed __int32			int32;
	typedef unsigned __int32		uint32;
	typedef signed __int64			int64;
	typedef unsigned __int64		uint64;
#endif


#ifdef _STLP_HASH_MAP
	#define HashMap ::std::hash_map
#else
	#define HashMap ::stdext::hash_map
#endif