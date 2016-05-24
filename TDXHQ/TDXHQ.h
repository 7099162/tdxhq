// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� TDXHQ_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// TDXHQ_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

#ifdef TDXHQ_EXPORTS
#define TDXHQ_API  extern "C"  __declspec(dllexport)
#else
#define TDXHQ_API  extern "C"  __declspec(dllimport)
#endif

#define  TDXHQ_ERROR_OK   -1
#define  TDXHQ_ERROR_SEND -2
#define  TDXHQ_ERROR_RECV -3
#define	 TDXHQ_ERROR_CONT -4
#define  TDXHQ_ERROR_COFG -5

TDXHQ_API int TDXHQ_Init(DWORD dwChoiceFast ,DWORD dwAutoCon );

TDXHQ_API int TDXHQ_Connect( );

TDXHQ_API int TDXHQ_DisConnect(int conID );

/// ��ȡ֤ȯָ����Χ�ĵ�K������
///Category:K������, 0->5����K��    1->15����K��    2->30����K��  3->1СʱK��    4->��K��  5->��K��  6->��K��  7->1����  8->1����K��  9->��K��  10->��K��  11->��K��
///Market:�г�����,   0->����     1->�Ϻ�
///Zqdm:֤ȯ����
///Start:��Χ�Ŀ�ʼλ��,���һ��K��λ����0, ǰһ����1, ��������
///Count:��Χ�Ĵ�С��APIִ��ǰ,��ʾ�û�Ҫ�����K����Ŀ, APIִ�к�,������ʵ�ʷ��ص�K����Ŀ, ���ֵ800
///Result:��APIִ�з��غ�Result�ڱ����˷��صĲ�ѯ����, ��ʽΪ������ݣ�������֮��ͨ��\n�ַ��ָ������֮��ͨ��\t�ָ���һ��Ҫ����1024*1024�ֽڵĿռ䡣����ʱΪ���ַ�����
///ErrInfo:��APIִ�з��غ�������������˴�����Ϣ˵����һ��Ҫ����256�ֽڵĿռ䡣û����ʱΪ���ַ�����
/// returns:�ɹ�����true, ʧ�ܷ���false
TDXHQ_API int TDXHQ_GetSecurityBars( int connID,WORD Category, WORD Market, char* Zqdm, WORD Start, WORD& Count, char szResult[]);

TDXHQ_API int TDXHQ_GetSecurityQuotes(int connID,WORD Market, char* Zqdm, WORD& Count, char szResult[]);//��ȡ�̿��嵵����