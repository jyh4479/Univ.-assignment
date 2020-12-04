#pragma once
class CTask35myDlg : public CDialogEx
{
public:
	CTask35myDlg(CWnd* pParent = NULL);	
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TASK35MY_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	BOOL Check();
	void LoadGame(void);
	void DrawGameView(CDC * pDC);
	void DrawSnake(CDC * pDC);
	void DrawFood(CDC * pDc);
	void DrawTime1(CDC * pDC);
	
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void DrawTime2(CDC * pDC);
	void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	
	BOOL PreTranslateMessage(MSG * pMsg);
	void EndBox();
};
