// HQTESTDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "HQTEST.h"
#include "HQTESTDlg.h"
#include "Config.h"
#include "..\TDXHQ\TDXHQ.h"
#include "Quotation.h"
#include "..\include\mysql.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_NC (WM_USER+1001)

CConfig cfg;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CHQTESTDlg �Ի���




CHQTESTDlg::CHQTESTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHQTESTDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHQTESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MESSAGE, m_lstbox_msg);
}

BEGIN_MESSAGE_MAP(CHQTESTDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CHQTESTDlg::OnBnClickedButton1)
	ON_WM_SIZE()
	ON_MESSAGE(WM_NC,OnNotifyIcon)
	ON_WM_CLOSE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CHQTESTDlg ��Ϣ�������

BOOL CHQTESTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	NotifyIcon.cbSize=sizeof(NOTIFYICONDATA);
	NotifyIcon.hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	NotifyIcon.hWnd=m_hWnd;
	lstrcpy(NotifyIcon.szTip,_T("NotifyIcon Test"));
	NotifyIcon.uCallbackMessage=WM_NC;
	NotifyIcon.uFlags=NIF_ICON | NIF_MESSAGE | NIF_TIP;
	Shell_NotifyIcon(NIM_ADD,&NotifyIcon);


	MYSQL *sock;
	sock = mysql_init(0);//��ʼ��ָ��
	if (!sock)
	{
		AfxMessageBox("���ݿ��ʼ��ʧ�ܣ�");
		return 0;
	}
	
	//connection
	if (!mysql_real_connect(sock, cfg.g_cs_mysql_host, cfg.g_cs_mysql_user ,cfg.g_cs_mysql_password, cfg.g_cs_mysql_dbname, cfg.g_cs_mysql_port, NULL, 0))
	{
		AfxMessageBox("���ݿ�����ʧ�ܣ������������"); 
		return 0;
	}

	MYSQL_RES *results;//��ѯ���������
	MYSQL_ROW record;//��ѯ���������

	if(mysql_query(sock,"select * from watching"))//����my_sql��Ҫ�Ƕ��ֽڵ��ַ�������
	{
		AfxMessageBox("��ѯʧ�ܣ�"); 
		return 0;
	}
	results=mysql_store_result(sock);
	int iRows=0;
	int k=0;
	CString str;
	ZeroMemory( stockcode , sizeof( STOCKCODE ) * 3000 );
	while(record = mysql_fetch_row(results))
	{
		str= CA2W(record[0], CP_ACP);//code   CA2W�����ַ�����ASCII��ת��Ϊ���ַ�����Unicode��
		strncpy( stockcode[ iRows].code , str ,6 );

		//str= CA2W(record[1], CP_ACP);//name
		//TRACE( str );
		str= CA2W(record[2], CP_ACP);//market
		strncpy( stockcode[ iRows].market , str , 1 );

		iRows++;
	}
	m_istock = iRows;
	mysql_free_result( results );
	mysql_close( sock );
	
	int i;
	int stockpertread =  m_istock/TREADNUM;
	for(i = 0 ; i < TREADNUM - 1;i ++ )
	{
		CQuotation * quo = new CQuotation( i, & stockcode[ i * stockpertread ], stockpertread);
		quo->CreateThread();
		pquo[ i ] = quo;
	}
	if( i * stockpertread < m_istock )
	{
		CQuotation * quo = new CQuotation(i, & stockcode[ i * stockpertread ], m_istock - i * stockpertread );
		quo->CreateThread();
		pquo[ i ] = quo;
	}

	SYSTEMTIME st;
	CString strDate,strTime;
	GetLocalTime(&st);
	preMin = st.wMinute ;

	TDXHQ_Init( 0, 0 );

	SetTimer( 1 , 1000, NULL );
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CHQTESTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHQTESTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CHQTESTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CHQTESTDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for( int i=0;i< 100;i ++)
		m_lstbox_msg.AddString("sssss");

}

LRESULT CHQTESTDlg::OnNotifyIcon(WPARAM wParam,LPARAM IParam)
{
	if ((IParam == WM_LBUTTONDOWN) || (IParam == WM_RBUTTONDOWN))
	{ 
		//ModifyStyleEx(0,WS_EX_TOPMOST);
		ShowWindow( SW_SHOWNORMAL );//SW_SHOW SW_SHOWNORMAL
		//Shell_NotifyIcon(NIM_DELETE, &NotifyIcon);//��������ͼ��
	}
	return FALSE;
}

void CHQTESTDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}

void CHQTESTDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialog::OnClose();
}

LRESULT CHQTESTDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	switch(message) //�ж���Ϣ����
	{ 
	case WM_SYSCOMMAND: 
		//�����ϵͳ��Ϣ 
		if(wParam==SC_MINIMIZE)
		{ 
			//���յ���С����Ϣʱ���������� 
			AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE); 
			return 0; 
		} 
		if(wParam==SC_CLOSE)
		{
			::Shell_NotifyIcon(NIM_DELETE,&NotifyIcon); //�ر�ʱɾ��ϵͳ����ͼ��
		}
		break;
	}

	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL IsTraderTime()
{
	SYSTEMTIME st;
	CString strDate,strTime;
	GetLocalTime(&st);
	//strDate.Format("%.4d-%.2d-%2.d wd:%.1d\n",st.wYear,st.wMonth,st.wDay,st.wDayOfWeek);
	//TRACE( strDate );
	//strTime.Format("%.2d:%.2d:%.2d\n",st.wHour,st.wMinute,st.wSecond);
	//TRACE( strTime );

	CTime t_1_start(st.wYear,st.wMonth,st.wDay,9,25,01);
	CTime t_1_end(st.wYear,st.wMonth,st.wDay,11,30,30);

	CTime t_2_start(st.wYear,st.wMonth,st.wDay,13,00,01);
	CTime t_2_end(st.wYear,st.wMonth,st.wDay,15,00,01);

	CTime t_now( st.wYear,st.wMonth,st.wDay,st.wHour ,st.wMinute , st.wSecond );

	if( (st.wDayOfWeek >=1) && (st.wDayOfWeek <=5) )
	{
		if( ( (t_now > t_1_start) && (t_now < t_1_end) ) ||
			( (t_now > t_2_start) && (t_now < t_2_end) ) )
		{
			//CQuotation quo;

			return TRUE;
		}
		else
			return FALSE;
	}
	else
	{
		return FALSE;
	}

}

void CHQTESTDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if( IsTraderTime() )
	{
		SYSTEMTIME st;
		CString strDate,strTime;
		GetLocalTime(&st);
		if( preMin != st.wMinute )
		{
			//new minute
			preMin = st.wMinute;
			//if( preMin % 5 == 0)
			//{
				for( int i = 0 ; i< TREADNUM ; i ++ )
				{
					pquo[i]->g_bGetQuotation = TRUE;
				}
			//}
		}

	}

	CDialog::OnTimer(nIDEvent);
}
