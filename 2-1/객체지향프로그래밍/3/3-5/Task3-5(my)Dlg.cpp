#include "stdafx.h"
#include "Task3-5(my).h"
#include "Task3-5(my)Dlg.h"
#include "afxdialogex.h"

#include "SnakeCtrl.h"//<<<<<<<<<<

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static SnakeCtrl * mHead; //Declare variable for using data every where
static Food* mFood; //Declare variable for using data every where
static int rectsize(20); //Declare size of rectangle or other shape
static int Getbody = 3; //The value of snake size
static int GetTime = 0; //The value of Time
static int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0; //For used makes timer

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
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
CTask35myDlg::CTask35myDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TASK35MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CTask35myDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CTask35myDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()

ON_WM_CREATE()
ON_WM_KEYDOWN()
ON_WM_KEYDOWN()
END_MESSAGE_MAP()
BOOL CTask35myDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
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
	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);
	return TRUE;
}
void CTask35myDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX){
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
		CDialogEx::OnSysCommand(nID, lParam);
}
HCURSOR CTask35myDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/////////////////////////////////////////////////////////////////////////////////////



void CTask35myDlg::OnPaint() //The function that makes field, snake, food and timer
{
	CPaintDC dc(this);

	DrawGameView(&dc); //Draw field
	DrawSnake(&dc); //Draw Snake
	DrawFood(&dc); //Draw Food
	DrawTime2(&dc); //Draw timer
	if (Check() == 0)
		EndBox();
}

BOOL CTask35myDlg::Check() //The function for checking HitBody, Hitwall and Eat food
{
	if (HitBody(mHead) || HitWall(mHead)) //If hit body or hit wall return FALSE
		return FALSE;
	
	if (EatFood(&mHead, mFood)) //If EatFood function return true, practice the function
	{
		++Getbody; //add 1 to Getbody
		KillTimer(1); //stop the timer of ID 1
		SetTimer(1, 200, NULL); //start timer of ID 1 that work 200micro seconds 
	}
	return 1; //return 1
}

void CTask35myDlg::LoadGame(void) //The function for load data
{
	DeleteSnake(&mHead); //Delete information of snake
	CreateSnake(&mHead); //Create information of snake
	CreateFood(&mFood); //Create information of Food
}

void CTask35myDlg::DrawGameView(CDC * pDC) //The function draws field
{
	int StrLen; //The value for drawing string
	wchar_t Str[50]; //The value for save string

	CPen pen; //The variable for drawing Rectangular border color
	pen.CreatePen(PS_SOLID, 1, RGB(140, 140, 140)); //The color of gray
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush; //The variable for filling color of rectangle
	brush.CreateSolidBrush(RGB(0, 0, 0)); //The color of black
	CBrush* oldBrush = pDC->SelectObject(&brush);

	pDC->Rectangle(-10, -10, 2000, 2000); //The background of black
	pDC->SelectObject(oldBrush);
	brush.DeleteObject(); //delete information of brush

	int a = 0, b = 1, count = 0;

	for (; a <= 21; a, a++) //Draw Left
	{//The Shape of wall
		brush.CreateSolidBrush(RGB(0, 0, 0));
		oldBrush = pDC->SelectObject(&brush);
		pDC->Rectangle(0, a * 20, 20, 20 + (a * 20));
		pDC->SelectObject(oldBrush);
		brush.DeleteObject();

		brush.CreateSolidBrush(RGB(140, 140, 140));
		oldBrush = pDC->SelectObject(&brush);
		pDC->Rectangle(5, 5 + (a * 20), 15, 15 + (a * 20));
		pDC->SelectObject(oldBrush);
		brush.DeleteObject();
	}

	for (a = 0; a < 30; a++) //Draw Top
	{//The Shape of wall
		brush.CreateSolidBrush(RGB(0, 0, 0));
		oldBrush = pDC->SelectObject(&brush);
		pDC->Rectangle(20 + (a * 20), 0, 40 + (a * 20), 20);
		pDC->SelectObject(oldBrush);
		brush.DeleteObject();

		brush.CreateSolidBrush(RGB(140, 140, 140));
		oldBrush = pDC->SelectObject(&brush);
		pDC->Rectangle(25 + (a * 20), 5, 35 + (a * 20), 15);
		pDC->SelectObject(oldBrush);
		brush.DeleteObject();
	}

	for (a = 0; a < 30; a++) //Draw Bottom
	{//The Shape of wall
		brush.CreateSolidBrush(RGB(0, 0, 0));
		oldBrush = pDC->SelectObject(&brush);
		pDC->Rectangle(20 + (a * 20), 420, 40 + (a * 20), 440);
		pDC->SelectObject(oldBrush);
		brush.DeleteObject();

		brush.CreateSolidBrush(RGB(140, 140, 140));
		oldBrush = pDC->SelectObject(&brush);
		pDC->Rectangle(25 + (a * 20), 425, 35 + (a * 20), 435);
		pDC->SelectObject(oldBrush);
		brush.DeleteObject();
	}

	for (a = 0; a <= 21; a, a++) //Draw Right
	{//The Shape of wall
		brush.CreateSolidBrush(RGB(0, 0, 0));
		oldBrush = pDC->SelectObject(&brush);
		pDC->Rectangle(620, a * 20, 640, 20 + (a * 20));
		pDC->SelectObject(oldBrush);
		brush.DeleteObject();

		brush.CreateSolidBrush(RGB(140, 140, 140));
		oldBrush = pDC->SelectObject(&brush);
		pDC->Rectangle(625, 5 + (a * 20), 635, 15 + (a * 20));
		pDC->SelectObject(oldBrush);
		brush.DeleteObject();
	}
	pen.DeleteObject();	//Delete information of pen

	StrLen = wsprintf(Str, L"Size of Snake : %d", Getbody); //Save information of string
	pDC->SetTextColor(RGB(102, 51, 153)); //The color of purple
	pDC->SetBkColor(RGB(0, 0, 0));
	pDC->TextOut(250, 440, Str, StrLen); //print string
}

void CTask35myDlg::DrawSnake(CDC * pDC) //The function draws snake
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 255, 0)); //The color of light green
	CPen* oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	CBrush* oldBrush = pDC->SelectObject(&brush);

	SnakeCtrl* tmp = mHead; //Save mHead to tmp
	SnakeCtrl* tail; //Declare tail


	for (; tmp->next != NULL; tmp = tmp->next); //For saving information of tail
	tail = tmp; //Save tmp to tail

	tmp = mHead; //Save mHead to tmp

	for (; tmp != NULL; tmp = tmp->next) //The function draws Snake
	{
		if (tmp == mHead) //If mHead is tmp, practice the function
		{
			brush.CreateSolidBrush(RGB(0, 255, 0));
			oldBrush = pDC->SelectObject(&brush);

			if (mHead->direction == VK_LEFT) //If head's dirction if Left, practice the function
			{
				POINT ar[] = { rectsize*tmp->posx, (rectsize*tmp->posy) + 10, //This function for drawing triangle
					(rectsize*tmp->posx) + 20, rectsize*tmp->posy,
					(rectsize*tmp->posx) + 20,(rectsize*tmp->posy) + 20 };
				pDC->Polygon(ar, 3);
			}
			else if (mHead->direction == VK_RIGHT) //If head's dirction if Right, practice the function
			{
				POINT ar[] = { (rectsize*tmp->posx) + 20, (rectsize*tmp->posy) + 10, //This function for drawing triangle
					rectsize*tmp->posx, (rectsize*tmp->posy) + 20,
					rectsize*tmp->posx,rectsize*tmp->posy };
				pDC->Polygon(ar, 3);
			}
			else if (mHead->direction == VK_UP) //If head's dirction if Up, practice the function
			{
				POINT ar[] = { (rectsize*tmp->posx) + 10, rectsize*tmp->posy, //This function for drawing triangle
					rectsize*tmp->posx, (rectsize*tmp->posy) + 20,
					(rectsize*tmp->posx) + 20,(rectsize*tmp->posy) + 20 };
				pDC->Polygon(ar, 3);
			}
			else if (mHead->direction == VK_DOWN) //If head's dirction if Down, practice the function
			{
				POINT ar[] = { (rectsize*tmp->posx) + 10, (rectsize*tmp->posy) + 20, //This function for drawing triangle
					rectsize*tmp->posx, rectsize*tmp->posy,
					(rectsize*tmp->posx) + 20,rectsize*tmp->posy };
				pDC->Polygon(ar, 3);
			}
			brush.DeleteObject(); //Delete information of brush
		}

		else if (tmp == tail) //If tmp is tail
		{
			CString str1; //The value for saving string
			CRect rect; //The value is information of rectangle

			str1 = _T("<>"); //The shpae of tail
			GetClientRect(&rect);

			rect.top = rect.top + tmp->posy*rectsize; //The position of shape
			rect.bottom = rect.bottom + tmp->posy*rectsize; //The position of shape
			rect.right = rect.right + tmp->posx*rectsize; //The position of shape
			rect.left = rect.left + tmp->posx*rectsize; //The position of shape

			pDC->SetTextColor(RGB(0, 255, 0)); //The color of string
			pDC->SetBkColor(RGB(0, 0, 0)); //The color of box
			pDC->DrawText(str1, &rect, 0); //print string
		}

		else if (tmp != tail&&tmp != mHead) //This function draws body
		{
			brush.CreateSolidBrush(RGB(0, 0, 0)); //The rectangle's background color is black
			oldBrush = pDC->SelectObject(&brush);

			pDC->Ellipse(rectsize*tmp->posx, rectsize*tmp->posy, rectsize*(tmp->posx + 1), rectsize*(tmp->posy + 1));
			pDC->Ellipse((rectsize*tmp->posx) + 5, (rectsize*tmp->posy) + 5,
				(rectsize*(tmp->posx + 1)) - 5, (rectsize*(tmp->posy + 1) - 5)); //The function draws two circle

			brush.DeleteObject(); //delete brush
		}
	}
	brush.DeleteObject(); //delete brush
}

void CTask35myDlg::DrawFood(CDC * pDC) //The function draws Food
{
	CClientDC dc(this);
	CBrush brush;
	CBrush* oldBrush = pDC->SelectObject(&brush);

	CString str1; //The value for saving string
	CRect rect; //The value is information of rectangle

	str1 = _T("♥"); //The shpae of Food
	GetClientRect(&rect);

	Food* tmp = mFood; //Declare tmp and Save mFood to tmp

	rect.top = rect.top + tmp->posy*rectsize; //The position of shape
	rect.bottom = rect.bottom + tmp->posy*rectsize; //The position of shape
	rect.right = rect.right + tmp->posx*rectsize; //The position of shape
	rect.left = rect.left + tmp->posx*rectsize; //The position of shape

	dc.SetTextColor(RGB(255, 0, 0)); //The color of Food
	dc.SetBkColor(RGB(0, 0, 0)); //The color of box
	dc.DrawText(str1,&rect, 0); //print string
}

void CTask35myDlg::DrawTime1(CDC * pDC) //The function draws timer
{
	int StrLen; //The value for Saveing information of timer
	wchar_t Str[50]; //The value for save string

	++GetTime; //Add 1 to GetTime

	if (GetTime == 10) //This algorithm for drawing timer
	{
		GetTime = 0;
		++a5;
	}
	else if (a5 == 6)
	{
		a5 = 0;
		++a4;
	}
	else if (a4 == 10)
	{
		a4 = 0;
		++a3;
	}
	else if (a3 == 6)
	{
		a3 = 0;
		++a2;
	}
	else if (a2 == 10)
	{
		a2 = 0;
		++a1;
	}

	StrLen = wsprintf(Str, L"%d%d : %d%d : %d%d", a1, a2, a3, a4, a5, GetTime); //The information of timer
	pDC->SetTextColor(RGB(0, 255, 255)); //The color of string is sky blue
	pDC->SetBkColor(RGB(0, 0, 0)); //The color of box is black
	pDC->TextOut(0, 440, Str, StrLen); //print string
}

void CTask35myDlg::DrawTime2(CDC * pDC) //The function draws timer
{
	int StrLen; //The value for Saveing information of timer
	wchar_t Str[50]; //The value for save string

	StrLen = wsprintf(Str, L"%d%d : %d%d : %d%d", a1, a2, a3, a4, a5, GetTime); //The information of timer
	pDC->SetTextColor(RGB(0, 255, 255)); //The color of string is sky blue
	pDC->SetBkColor(RGB(0, 0, 0)); //The color of box is black
	pDC->TextOut(0, 440, Str, StrLen); //print string
}

void CTask35myDlg::OnTimer(UINT_PTR nIDEvent) //This is a function that will be executed every fixed time of ID.
{
	CClientDC dc(this);
	if (nIDEvent == 1) //If ID is 1, practice the function at the appointed time
	{
		SendMessage(WM_KEYDOWN, NULL, NULL); //Practice the function of KEYDOWN
		DrawSnake(&dc);
	}
	if (nIDEvent == 2) //If ID is 2, practice the function at the appointed time
	{
		DrawTime1(&dc); //Show the clock
	}
	CDialogEx::OnTimer(nIDEvent);
}

int CTask35myDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) //The function practices when compile the program
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	MessageBox(L"Game start", MB_OK); //show the "Game start" at box that contain OK button
	SetTimer(1, 200, NULL); //Set time 200micro secnod and ID is 1
	SetTimer(2, 1000, NULL); //Set time 1 secnod and ID is 2
	LoadGame(); //Load the information of game
	return 0; //return 0
}

void CTask35myDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) //Function to execute when direction key is pressed
{
	CClientDC dc(this);
	int StrLen; //The value for Saveing information of timer
	wchar_t Str[50]; //The value for save string

	if (mHead->direction - nChar != 0x02 && mHead->direction - nChar != -0x02) //This function prevents you from reversing direction
	{
		if (Check() == 1)
			MoveSnake(nChar, mHead);//The function that moves the snake

		if (Check() == 0) //If check() return FALSE, practice the function
		{
			KillTimer(1); //kill time that's ID is 1
			KillTimer(2); //kill time that's ID is 2

			if (nChar == 0x59) //If nChar is y, practice the function
			{
				Getbody = 3; //reset the Getbody
				GetTime = 0; //reset the GetTime
				a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0; //resert the value
				LoadGame(); //Load new Game
				SetTimer(1, 200, NULL); //Set timer
				SetTimer(2, 1000, NULL); //Set other timer that needed shows clock
			}

			else if (nChar == 0x4E) //If nChar is n, practice the function
			{
				DeleteSnake(&mHead); //Delete information of snake
				exit(0); //End program
			}
		}
		InvalidateRgn(NULL, FALSE); //This function erases the original data.
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}

void  CTask35myDlg::EndBox()
{
	int StrLen; //The value for Saveing information of timer
	wchar_t Str[50]; //The value for save string
	CClientDC dc(this);
	StrLen = wsprintf(Str, L"Game Over");
	dc.SetTextColor(RGB(255, 255, 255)); //The color of string is sky blue
	dc.SetBkColor(RGB(0, 0, 0)); //The color of box is black
	dc.TextOut(270, 190, Str, StrLen); //print string

	StrLen = wsprintf(Str, L"One more game ? y / n"); //The information of timer
	dc.SetTextColor(RGB(255, 255, 255)); //The color of string is sky blue
	dc.SetBkColor(RGB(0, 0, 0)); //The color of box is black
	dc.TextOut(230, 230, Str, StrLen); //print string
}

BOOL CTask35myDlg::PreTranslateMessage(MSG* pMsg)
{
	//This function initializes the data of the other key when KEYDOWN does not work and helps KEYDOWN function again.
	BOOL bCtrl = FALSE;
	BOOL bAlt = FALSE;
	BOOL bShift = FALSE;

	BYTE keyState[256] = { 0 , };

	switch (pMsg->message)
	{
	case WM_KEYDOWN:
	{
		GetKeyboardState(keyState);
		bCtrl = (keyState[VK_LCONTROL] & 0x80) != 0 ? TRUE : FALSE;
		bAlt = (keyState[VK_LMENU] & 0x80) != 0 ? TRUE : FALSE;
		bShift = (keyState[VK_LMENU] & 0x80) != 0 ? TRUE : FALSE;
		if (bShift == TRUE&&bCtrl == TRUE&&pMsg->wParam == 0x4f)
		{
		}
		break;
	}
	case WM_KEYUP:
		break;
	}
	return FALSE;
}

