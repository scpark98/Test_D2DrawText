
// Test_D2DrawTextDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Test_D2DrawText.h"
#include "Test_D2DrawTextDlg.h"
#include "afxdialogex.h"

#include "Common/Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestD2DrawTextDlg 대화 상자



CTestD2DrawTextDlg::CTestD2DrawTextDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_D2DRAWTEXT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestD2DrawTextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TEXT, m_edit_text);
	DDX_Control(pDX, IDC_COMBO_FONT, m_combo_font);
	DDX_Control(pDX, IDC_CHECK_SHOW_TEXT, m_check_show_text);
	DDX_Control(pDX, IDC_CHECK_SHOW_SHADOW, m_check_show_shadow);
	DDX_Control(pDX, IDC_STATIC_TEXT_AREA, m_static_text_area);
	DDX_Control(pDX, IDC_SLIDER_FONT_SIZE, m_slider_font_size);
	DDX_Control(pDX, IDC_COMBO_BACK_IMAGE, m_combo_back_image);
}

BEGIN_MESSAGE_MAP(CTestD2DrawTextDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTestD2DrawTextDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTestD2DrawTextDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT_TEXT, &CTestD2DrawTextDlg::OnEnChangeEditText)
	ON_CBN_SELCHANGE(IDC_COMBO_FONT, &CTestD2DrawTextDlg::OnCbnSelchangeComboFont)
	ON_BN_CLICKED(IDC_CHECK_SHOW_TEXT, &CTestD2DrawTextDlg::OnBnClickedCheckShowText)
	ON_BN_CLICKED(IDC_CHECK_SHOW_SHADOW, &CTestD2DrawTextDlg::OnBnClickedCheckShowShadow)
	ON_BN_CLICKED(IDC_RADIO_LEFT, &CTestD2DrawTextDlg::OnBnClickedRadioLeft)
	ON_BN_CLICKED(IDC_RADIO_CENTER, &CTestD2DrawTextDlg::OnBnClickedRadioCenter)
	ON_BN_CLICKED(IDC_RADIO_RIGHT, &CTestD2DrawTextDlg::OnBnClickedRadioRight)
	ON_BN_CLICKED(IDC_RADIO_TOP, &CTestD2DrawTextDlg::OnBnClickedRadioTop)
	ON_BN_CLICKED(IDC_RADIO_VCENTER, &CTestD2DrawTextDlg::OnBnClickedRadioVcenter)
	ON_BN_CLICKED(IDC_RADIO_BOTTOM, &CTestD2DrawTextDlg::OnBnClickedRadioBottom)
	ON_WM_WINDOWPOSCHANGED()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_REGISTERED_MESSAGE(Message_CSCSliderCtrl, &CTestD2DrawTextDlg::on_message_CSCSliderCtrl)
	ON_CBN_SELCHANGE(IDC_COMBO_BACK_IMAGE, &CTestD2DrawTextDlg::OnCbnSelchangeComboBackImage)
END_MESSAGE_MAP()


// CTestD2DrawTextDlg 메시지 처리기

BOOL CTestD2DrawTextDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_resize.Create(this);
	m_resize.Add(IDC_STATIC_TEXT_AREA, 0, 0, 100, 100);

	//m_d2dc.init(m_static_text_area.m_hWnd);
	m_d2dc.init(m_hWnd);

	m_edit_text.set_text(theApp.GetProfileString(_T("setting"), _T("text"), _T("한글 텍스트\r\nSecond Line.")));

	m_combo_font.set_as_font_combo();
	m_combo_font.set_line_height(14);

	m_slider_font_size.set_style(CSCSliderCtrl::style_thumb_round);
	m_slider_font_size.set_range(4, 400);
	m_slider_font_size.set_pos(theApp.GetProfileInt(_T("setting"), _T("font size"), 20));

	m_align = theApp.GetProfileInt(_T("setting"), _T("align"), DT_CENTER);
	m_valign = theApp.GetProfileInt(_T("setting"), _T("valign"), DT_VCENTER);

	CheckDlgButton(IDC_RADIO_LEFT, m_align == DT_LEFT ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_RADIO_CENTER, m_align == DT_CENTER ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_RADIO_RIGHT, m_align == DT_RIGHT ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_RADIO_TOP, m_valign == DT_TOP ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_RADIO_VCENTER, m_valign == DT_VCENTER ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton(IDC_RADIO_BOTTOM, m_valign == DT_BOTTOM ? BST_CHECKED : BST_UNCHECKED);

	//배경이미지 파일들 로딩
	m_combo_back_image.set_line_height(14);
	std::deque<CString> back_image_files = find_all_files(get_exe_directory(true) + _T("back_image"), _T("*"), FILE_EXTENSION_IMAGE);
	for (int i = 0; i < back_image_files.size(); i++)
	{
		//static local 변수로 선언하여 m_img_back.push_back(img); 하게되면 shallow copy되므로 소멸 시 에러가 발생한다.
		//반드시 new로 할당받아서 넣고 프로그램 종료 시 해제할 것.
		//std::make_unique로 변경 후 종료 시 해제 작업 또한 불필요함.
		auto img = std::make_unique<CSCD2Image>();
		HRESULT hr = img->load(m_d2dc.get_WICFactory(), m_d2dc.get_d2dc(), back_image_files[i]);
		if (hr == S_OK)
		{
			m_img_back.push_back(std::move(img));
			m_combo_back_image.add(get_part(back_image_files[i], fn_name));
		}
	}
	m_back_index = theApp.GetProfileInt(_T("setting"), _T("back_index"), -1);
	m_combo_back_image.set_cur_sel(m_back_index);

	RestoreWindowPosition(&theApp, this);	RestoreWindowPosition(&theApp, this);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTestD2DrawTextDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTestD2DrawTextDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//이 한줄을 안써주면 컨트롤을 클릭해도 화면이 갱신되지 않는다.
		CPaintDC dc(this);


		CRect rc;

		GetClientRect(rc);

		ID2D1DeviceContext* d2dc = m_d2dc.get_d2dc();
		D2D1_SIZE_F dc_size = m_d2dc.get_size();

		d2dc->BeginDraw();
		d2dc->SetTransform(D2D1::Matrix3x2F::Identity());

		//black으로 칠한 후
		//d2dc->Clear(D2D1::ColorF(D2D1::ColorF::White));
		d2dc->Clear(get_sys_d2color(COLOR_3DFACE));

		ID2D1SolidColorBrush* br;
		d2dc->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &br);

		//배경그림을 그리고 (비율을 유지한 채 가로 또는 세로에 맞게 확대/축소하여 그림)
		if (m_back_index >= 0)
			m_img_back[m_back_index]->draw(d2dc, CRect_to_d2Rect(m_text_area), eSCD2Image_DRAW_MODE::draw_mode_stretch);

		draw_rect(d2dc, m_text_area, Gdiplus::Color::DimGray);

		m_text_rect = draw_text(d2dc, m_text_area, m_edit_text.get_text(), m_combo_font.get_text(), (float)m_slider_font_size.GetPos(), DWRITE_FONT_WEIGHT_NORMAL, Gdiplus::Color::Red, Gdiplus::Color::Black, m_align | m_valign, m_show_text, m_show_shadow);
		draw_rect(d2dc, m_text_rect, Gdiplus::Color::Red);

		HRESULT hr = d2dc->EndDraw();

		if (SUCCEEDED(hr))
			hr = m_d2dc.get_swapchain()->Present(0, 0);
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTestD2DrawTextDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestD2DrawTextDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}

void CTestD2DrawTextDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	//std::make_unique로 할당받았으므로 직접 해제하는 코드는 불필요하다.
	//for (int i = 0; i < m_img_back.size(); i++)
	//{
	//	delete m_img_back[i];
	//}

	CDialogEx::OnCancel();
}

void CTestD2DrawTextDlg::OnEnChangeEditText()
{
	theApp.WriteProfileString(_T("setting"), _T("text"), m_edit_text.get_text());
	Invalidate();
}

void CTestD2DrawTextDlg::OnCbnSelchangeComboFont()
{
	Invalidate();
}

void CTestD2DrawTextDlg::OnBnClickedCheckShowText()
{
	m_show_text = (m_check_show_text.GetCheck() == BST_CHECKED);
	Invalidate();
}

void CTestD2DrawTextDlg::OnBnClickedCheckShowShadow()
{
	m_show_shadow = (m_check_show_shadow.GetCheck() == BST_CHECKED);
	Invalidate();
}

void CTestD2DrawTextDlg::OnBnClickedRadioLeft()
{
	m_align = DT_LEFT;
	theApp.WriteProfileInt(_T("setting"), _T("align"), m_align);
	Invalidate();
}

void CTestD2DrawTextDlg::OnBnClickedRadioCenter()
{
	m_align = DT_CENTER;
	theApp.WriteProfileInt(_T("setting"), _T("align"), m_align);
	Invalidate();
}

void CTestD2DrawTextDlg::OnBnClickedRadioRight()
{
	m_align = DT_RIGHT;
	theApp.WriteProfileInt(_T("setting"), _T("align"), m_align);
	Invalidate();
}

void CTestD2DrawTextDlg::OnBnClickedRadioTop()
{
	m_valign = DT_TOP;
	theApp.WriteProfileInt(_T("setting"), _T("valign"), m_valign);
	Invalidate();
}

void CTestD2DrawTextDlg::OnBnClickedRadioVcenter()
{
	m_valign = DT_VCENTER;
	theApp.WriteProfileInt(_T("setting"), _T("valign"), m_valign);
	Invalidate();
}

void CTestD2DrawTextDlg::OnBnClickedRadioBottom()
{
	m_valign = DT_BOTTOM;
	theApp.WriteProfileInt(_T("setting"), _T("valign"), m_valign);
	Invalidate();
}

void CTestD2DrawTextDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_d2dc.get_d2dc() == nullptr)
		return;

	m_static_text_area.GetWindowRect(m_text_area);
	ScreenToClient(m_text_area);

	CRect rc;
	GetClientRect(rc);
	m_d2dc.on_size_changed(rc.Width(), rc.Height());

	Invalidate();

	SaveWindowPosition(&theApp, this);
}

void CTestD2DrawTextDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_static_text_area.m_hWnd == NULL)
		return;

	m_static_text_area.GetWindowRect(m_text_area);
	ScreenToClient(m_text_area);

	//m_d2dc.on_size_changed(m_text_area.Width(), m_text_area.Height());
	m_d2dc.on_size_changed(cx, cy);

	Invalidate();
	//InvalidateRect(m_text_area, FALSE);
}

BOOL CTestD2DrawTextDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return FALSE;
	return CDialogEx::OnEraseBkgnd(pDC);
}

LRESULT CTestD2DrawTextDlg::on_message_CSCSliderCtrl(WPARAM wParam, LPARAM lParam)
{
	CSCSliderCtrlMsg* msg = (CSCSliderCtrlMsg*)wParam;

	if (msg->pThis = &m_slider_font_size)
	{
		theApp.WriteProfileInt(_T("setting"), _T("font size"), msg->pos);
		Invalidate();
	}

	return 0;
}

void CTestD2DrawTextDlg::OnCbnSelchangeComboBackImage()
{
	m_back_index = m_combo_back_image.GetCurSel();
	if (m_back_index < 0 || m_back_index >= m_combo_back_image.GetCount())
		return;

	theApp.WriteProfileInt(_T("setting"), _T("back_index"), m_back_index);
	Invalidate();
}
