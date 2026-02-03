
// Test_D2DrawTextDlg.h: 헤더 파일
//

#pragma once

#include <memory>
#include "Common/ResizeCtrl.h"
#include "Common/CEdit/SCEdit/SCEdit.h"
#include "Common/CComboBox/SCComboBox/SCComboBox.h"
#include "Common/directx/CSCD2Context/SCD2Context.h"
#include "Common/directx/CSCD2Image/SCD2Image.h"
#include "Common/CSliderCtrl/SCSliderCtrl/SCSliderCtrl.h"

// CTestD2DrawTextDlg 대화 상자
class CTestD2DrawTextDlg : public CDialogEx
{
// 생성입니다.
public:
	CTestD2DrawTextDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CResizeCtrl			m_resize;

	CSCD2Context		m_d2dc;

	CRect				m_text_area;	//텍스트를 출력시킬 영역 (IDC_STATIC_TEXT_AREA)
	CRect				m_text_rect;	//실제 텍스트가 출력된 영역
	UINT				m_align = DT_LEFT;
	UINT				m_valign = DT_TOP;
	bool				m_show_text = true;
	bool				m_show_shadow = true;

	int					m_back_index = -1;
	std::deque<std::unique_ptr<CSCD2Image>>	m_img_back;

	LRESULT				on_message_CSCSliderCtrl(WPARAM wParam, LPARAM lParam);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_D2DRAWTEXT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeEditText();
	afx_msg void OnCbnSelchangeComboFont();
	afx_msg void OnBnClickedCheckShowText();
	afx_msg void OnBnClickedCheckShowShadow();
	afx_msg void OnBnClickedRadioLeft();
	afx_msg void OnBnClickedRadioCenter();
	afx_msg void OnBnClickedRadioRight();
	afx_msg void OnBnClickedRadioTop();
	afx_msg void OnBnClickedRadioVcenter();
	afx_msg void OnBnClickedRadioBottom();
	CSCEdit m_edit_text;
	CSCComboBox m_combo_font;
	CButton m_check_show_text;
	CButton m_check_show_shadow;
	CStatic m_static_text_area;
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CSCSliderCtrl m_slider_font_size;
	CSCComboBox m_combo_back_image;
	afx_msg void OnCbnSelchangeComboBackImage();
};
