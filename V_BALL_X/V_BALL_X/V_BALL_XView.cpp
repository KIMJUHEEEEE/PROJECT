
// V_BALL_XView.cpp: CVBALLXView 클래스의 구현
//
#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "V_BALL_X.h"
#endif

#include "V_BALL_XDoc.h"
#include "V_BALL_XView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define STEP 7//한번 스텝마다 5씩

// CVBALLXView

IMPLEMENT_DYNCREATE(CVBALLXView, CFormView)

BEGIN_MESSAGE_MAP(CVBALLXView, CFormView)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
//	ON_WM_ERASEBKGND()
ON_WM_CREATE()
ON_WM_TIMER()
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_BUTTON1, &CVBALLXView::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON2, &CVBALLXView::OnBnClickedButton2)
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CVBALLXView 생성/소멸

CVBALLXView::CVBALLXView()
	: CFormView(IDD_V_BALL_X_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	start = FALSE;
	choice = 0;
	szSoundPath = _T("./kakao.wav");
	PlaySound(szSoundPath, AfxGetInstanceHandle(), SND_ASYNC);
	////////////////png파일 로드/////////////
	kakao.Load(L"kakaogame.png");
	m_ball.Load(L"ball.png");
	m_lionr.Load(L"lionr.png");
	m_lionl.Load(L"lionl.png");
	m_appeachr.Load(L"appeachr.png");
	m_appeachl.Load(L"appeachl.png");
	m_tuber.Load(L"tuber.png");
	m_tubel.Load(L"tubel.png");
	score_l.Load(L"0.png");
	score_r.Load(L"0.png");
	effect.Load(L"effect.bmp");
	gameove.Load(L"gameover.png");
	choice_a.Load(L"choice_a.png");
	choice_l.Load(L"choice_l.png");
	choice_t.Load(L"choice_t.png");
	nMx = nMy = STEP;
	/////////////////////////////////////////
	count_r = 0;
	count_l = 0;
	////////캐릭터 움직임 좌표///////////////
	m_charactorx_r = 11;
	m_charactorx_l = 11;
	m_up_r = 11;
	m_up_l = 11;
	////////////////////////////////////////
	m_bally = 50;
	m_ballx = 60;
	////////////////////////////////////////
}

CVBALLXView::~CVBALLXView()
{
}

void CVBALLXView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CVBALLXView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CVBALLXView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CVBALLXView 진단

#ifdef _DEBUG
void CVBALLXView::AssertValid() const
{
	CFormView::AssertValid();
}

void CVBALLXView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CVBALLXDoc* CVBALLXView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVBALLXDoc)));
	return (CVBALLXDoc*)m_pDocument;
}
#endif //_DEBUG


// CVBALLXView 메시지 처리기


void CVBALLXView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CFormView::OnPaint()을(를) 호출하지 마십시오.
	if (!start) {
		kakao.Draw(dc, 0, 0);
	}
	else {
		if (choice==0) {
			choice_a.Draw(dc, 350, 250);
			choice_l.Draw(dc, 620, 250);
			choice_t.Draw(dc, 930, 250);
		}
		else  {
			//////////////////////////배경bmp그리기/////////////////////////////////////
			HANDLE bmp;
			CBitmap cBitmap;
			BITMAP bmpinfo;
			CDC memdc;
			bmp = LoadImage(NULL, L"net.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			cBitmap.Attach(bmp);
			cBitmap.GetBitmap(&bmpinfo);
			memdc.CreateCompatibleDC(&dc);
			memdc.SelectObject(bmp);

			/////////////////////png파일 그리기/////////////////////////////////////
			score();
			if (count_r == 3 || count_l == 3) {
				gameove.Draw(memdc, 600, 100);
				if (count_l == 3) {
					if (choice == 1)
					{
						m_appeachr.Load(L"appeach_win.png");
						m_appeachl.Load(L"appeach_lose.png");
					}
					if (choice == 2) {
						m_lionr.Load(L"lion_win.png");
						m_lionl.Load(L"lion_lose.png");
					}
					if (choice == 3)
					{
						m_tuber.Load(L"tube_win.png");
						m_tubel.Load(L"tube_lose.png");
					}
				}
				if (count_r == 3) {
					if (choice == 1)
					{
						m_appeachl.Load(L"appeach_win.png");
						m_appeachr.Load(L"appeach_lose.png");
					}
					if (choice == 2) {
						m_lionl.Load(L"lion_win.png");
						m_lionr.Load(L"lion_lose.png");
					}
					if (choice == 3)
					{
						m_tubel.Load(L"tube_win.png");
						m_tuber.Load(L"tube_lose.png");
					}
				}
			}
			score_l.Draw(memdc, 50, 10);
			score_r.Draw(memdc, 1460, 10);
			m_ball.Draw(memdc, m_ballx, m_bally);
			if (choice == 2)
			{
				m_lionr.Draw(memdc, 1400 + m_charactorx_r, 440 + m_up_r);
				m_lionl.Draw(memdc, 50 + m_charactorx_l, 440 + m_up_l);
			}
			if (choice == 1)
			{
				m_appeachr.Draw(memdc, 1400 + m_charactorx_r, 440 + m_up_r);
				m_appeachl.Draw(memdc, 50 + m_charactorx_l, 440 + m_up_l);
			}
			if (choice == 3)
			{
				m_tuber.Draw(memdc, 1400 + m_charactorx_r, 440 + m_up_r);
				m_tubel.Draw(memdc, 50 + m_charactorx_l, 440 + m_up_l);
			}

			///////////////////////////////////////////////////////////////////////
			dc.BitBlt(0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, &memdc, 0, 0, SRCCOPY);
			memdc.DeleteDC();
			cBitmap.DeleteObject();
			////////////////////////////////////////////////////////////////////////

			/////////////Double Buffering////////////////////////////////////////
			CDC* pDC = &dc;
			CRect rect;
			GetClientRect(&rect);
			CBitmap bmp_;
			memdc.CreateCompatibleDC(pDC);
			bmp_.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
			memdc.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);
			pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY); //다시 한번 더 그리기
			/////////////////////////////////////////////////////////////////////////
		}
	}
}
///////////////////공 움직이기///////////////////////////////////////////////
int CVBALLXView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetTimer(1, 10, NULL); //0.01초 마다 OnTimer
	//Invalidate(FALSE);
	return 0;
}

void CVBALLXView::OnDestroy()
{
	CFormView::OnDestroy();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	KillTimer(1);
}

void CVBALLXView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CClientDC dc(this);
	CRect r; //창 정보
	GetClientRect(&r); //창 정보를 받아옴
	if (start == TRUE) {
		if (choice != 0) {
			m_ballx += nMx; // +STEP
			m_bally += nMy; // +STEP
		}
		if ((m_ballx >= m_charactorx_l + 50 + m_lionl.GetWidth() / 2) && (m_ballx <= m_lionl.GetWidth() + m_charactorx_l + 50) &&//왼쪽의 오른쪽
			(m_bally + 102 >= 440 + m_up_l) && (m_bally + 102 <= m_up_l + 440 + m_lionl.GetHeight() / 2)){// 위
			//			effect.Draw(dc, m_ballx-50,m_bally+50);
			if (nMx > 0 && nMy > 0) {
				nMy = nMy * (-1);
				
			}
			if (nMx < 0 && nMy > 0) {
				nMy = nMy * (-1); nMx = nMx * (-1);
			}
		}
		if ((m_ballx  >= m_charactorx_l + m_lionl.GetWidth() / 2) && (m_ballx <= m_lionl.GetWidth() + m_charactorx_l ) &&//왼쪽의 오른쪽
			(m_bally+102 > 440 + m_up_l + m_lionl.GetHeight() / 2) && (m_bally+102 <= m_up_l + 440 + m_lionl.GetHeight())) {// 아래
			if (nMx < 0 && nMy > 0) {
				nMx = nMx * (-1);
			}
		}
		if ((m_ballx + 25 >= m_charactorx_l ) && (m_ballx+25 <= m_lionl.GetWidth() / 2 + m_charactorx_l ) &&// 왼쪽의 왼쪽
			(m_bally+102  >= 440 + m_up_l) && (m_bally+102  <= m_up_l + 440 + m_lionl.GetHeight() / 2)) { //위
		//	effect.Draw(dc, m_ballx+50,m_bally+50);
			if (nMx > 0 && nMy > 0) {
				nMx = nMx * (-1);
				nMy = nMy * (-1);
			}
			if (nMx < 0 && nMy > 0) {
				nMy = nMy * (-1);
			}
		}
		if ((m_ballx +25 >= m_charactorx_l ) && (m_ballx+25 <= m_lionl.GetWidth() / 2 + m_charactorx_l) &&//왼쪽의 왼쪽
			(m_bally+102> 440 + m_up_l + m_lionl.GetHeight() / 2) && (m_bally+102 <= m_up_l + 440 + m_lionl.GetHeight())) {//  아래
			if (nMx > 0 && nMy > 0) {
				nMx = nMx * (-1);
			}
		}
		if ((m_ballx >= m_charactorx_r + 1400 + m_lionr.GetWidth() / 2) && (m_ballx+120 <= m_lionr.GetWidth() + m_charactorx_r + 1400) &&// 오른쪽의 오른쪽
			(m_bally + 102 >= 440 + m_up_r) && (m_bally + 102 <= m_up_r + 440 + m_lionr.GetHeight() / 2)) {// 오른쪽의 아래
		//	effect.Draw(dc, m_ballx + 50, m_bally + 50);
			if (nMx > 0 && nMy > 0) {
				nMy = nMy * (-1);
			}
			if (nMx < 0 && nMy > 0) {
				nMy = nMy * (-1); nMx = nMx * (-1);
			}
		}
		if ((m_ballx >= m_charactorx_r + 1400 + m_lionr.GetWidth() / 2) && (m_ballx <= m_lionr.GetWidth() + m_charactorx_r + 1400) && // 오른쪽의 오른쪽
			(m_bally >= 440 + m_up_r + m_lionr.GetHeight() / 2) && (m_bally <= m_up_r + 440 + m_lionr.GetHeight())) { // 오른쪽의 위
			if (nMx < 0 && nMy > 0) {
				nMx = nMx * (-1);
			}
		}
		if ((m_ballx + 102 >= m_charactorx_r + 1400) && (m_ballx <= m_lionr.GetWidth() / 2 + m_charactorx_r + 1400) &&// 오른쪽의 왼쪽
			(m_bally + 102 >= 440 + m_up_r) && (m_bally + 102 <= m_up_r + 440 + m_lionr.GetHeight() / 2)) { //오른쪽의 아래
		//	effect.Draw(dc, m_ballx - 50, m_bally + 50);
			if (nMx > 0 && nMy > 0) {
				nMx = nMx * (-1);
				nMy = nMy * (-1);
			}
			if (nMx < 0 && nMy > 0) {
				nMy = nMy * (-1);
			}
		}
		if ((m_ballx + 102 >= m_charactorx_r + 1400) && (m_ballx <= m_lionr.GetWidth() / 2 + m_charactorx_r + 1400) && //오른쪽의 왼쪽
			(m_bally >= 440 + m_up_r + m_lionr.GetHeight() / 2) && (m_bally <= m_up_r + 440 + m_lionr.GetHeight())) { // 오른쪽 위
			if (nMx > 0 && nMy > 0) {
				nMx = nMx * (-1);
			}
		}
		if (m_bally >= 550)
		{
			nMy = nMy * (-1);
			if (m_ballx <= 750) {
				count_l++;
				check[0] = 1; check[1] = 0;
				KillTimer(1);
			}
			if (m_ballx >= 750) {
				count_r++;
				check[0] = 0; check[1] = 1;
				KillTimer(1);
			}
			if (count_l <= 3 && check[0] == 1) {
				m_ballx = 1400; // +STEP
				m_bally = 50; // +STEPd
				SetTimer(1, 10, NULL);
			}
			if (count_r <= 3 && check[1] == 1) {
				m_ballx = 60; // +STEP
				m_bally = 50; // +STEPd
				SetTimer(1, 10, NULL);
			}
			if (count_r >= 3 || count_l >=3) {
				KillTimer(1);
			}
		}
		if (m_ballx >= r.right - 30) //오른쪽에 부딪치면 왼쪽으로 튀기게
		{
			nMx = nMx * (-1);
		}
		if (m_bally <= r.top) //위쪽에 부딪치면 아래쪽으로 튀기게
		{
			nMy = nMy * (-1);
		}
		if (m_ballx <= r.left + 30) //왼쪽에 부딪치면 오른쪽으로 튀기게
		{
			nMx = nMx * (-1);
		}
		if (m_bally > 180)/////네트
		{
			if (m_ballx + 50 > 830 && m_ballx + 50 < 838)
			{
				nMx = nMx * (-1);
			}

		}
		if (450 + m_up_r < 461) {
		if(choice==2)
			m_lionr.Load(L"lion_jump_r.png");
		if(choice==1)
				m_appeachr.Load(L"appeach_jump_r.png");
		if (choice == 3)
			m_tuber.Load(L"tube_jump_r.png");
		m_up_r += 8;
		}
		else {
		if(choice==2)
			m_lionr.Load(L"lionr.png");
		if(choice==1)
				m_appeachr.Load(L"appeachr.png");
		if (choice == 3)
			m_tuber.Load(L"tuber.png");

		}
		if (450 + m_up_l < 461) {
		if (choice == 2) 
			m_lionl.Load(L"lion_jump_l.png");

		if (choice == 1)
			m_appeachl.Load(L"appeach_jump_l.png");
		if (choice == 3)
			m_tubel.Load(L"tube_jump_l.png");

		m_up_l += 8;
		}
		else {
			if(choice==2)
				m_lionl.Load(L"lionl.png");
			if(choice==1)
				m_appeachl.Load(L"appeachl.png");
			if (choice == 3)
				m_tubel.Load(L"tubel.png");
		}
		Invalidate(FALSE);
		CFormView::OnTimer(nIDEvent);
	}
}
////////////////////////////////////////////////////////////////////////////


/////////////////////////키보드 받아오기////////////////////////////////////
BOOL CVBALLXView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	BYTE keystate[256] = { 0 };
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
	{
		//GetKeyboardState(keystate);
		if (pMsg->wParam == VK_LEFT) //화살표 <-
		{
			check[0] = 1;
			check[1] = 0;
			m_charactorx_r = m_charactorx_r - 60;
			if (m_charactorx_r < -600)
			{
				m_charactorx_r = m_charactorx_r + 60;
			}
			Invalidate(FALSE);
		}
		if (pMsg->wParam == VK_UP && (450 + m_up_r) >= 461) {
			if (check[0] == 1) {
				m_up_r = m_up_r - 250;
				m_charactorx_r = m_charactorx_r - 60;
				Invalidate(FALSE);
			}
			if (check[1] == 1) {
				m_up_r = m_up_r - 250;
				m_charactorx_r = m_charactorx_r + 60;
				Invalidate(FALSE);
			}
			if (check[0] == 0 && check[1] == 0) {
				m_up_r = m_up_r - 250;
				Invalidate(FALSE);
			}
		}
		if (pMsg->wParam == VK_RIGHT) //화살표 ->
		{
			check[0] = 0;
			check[1] = 1;
			m_charactorx_r = m_charactorx_r + 60;
			if (m_charactorx_r > 80)
			{
				m_charactorx_r = m_charactorx_r - 60;
			}
			Invalidate(FALSE);
		}
		if (pMsg->wParam == 'w' || pMsg->wParam == 'W' && (450 + m_up_l) >= 461) {//화살표 a
			if (check[2] == 1) {
				m_up_l = m_up_l - 250;
				m_charactorx_l = m_charactorx_l - 60;
				Invalidate(FALSE);
			}
			if (check[3] == 1) {
				m_up_l = m_up_l - 250;
				m_charactorx_l = m_charactorx_l + 60;
				Invalidate(FALSE);
			}
			if (check[2] == 0 && check[3] == 0) {
				m_up_l = m_up_l - 250;
				Invalidate(FALSE);
			}
		}
		if (pMsg->wParam == 'a' || pMsg->wParam == 'A') {//화살표 a
			check[2] = 1;
			check[3] = 0;
			m_charactorx_l = m_charactorx_l - 60;
			if (m_charactorx_l+50 <-10)
			{
				m_charactorx_l = m_charactorx_l + 60;
			}
			Invalidate(FALSE);
		}
		if (pMsg->wParam == 'd' || pMsg->wParam == 'D') { //화살표 d
			check[2] = 0;
			check[3] = 1;
			m_charactorx_l = m_charactorx_l + 60;
			if (50 + m_charactorx_l > 720)
			{
				m_charactorx_l = m_charactorx_l - 60;
			}
			Invalidate(FALSE);
		}
	}
	case WM_KEYUP: break;
	}

	return CFormView::PreTranslateMessage(pMsg);
}
//////////////////////////////////////////////////////////////////////////

void CVBALLXView::score() {
	if (count_l == 1) {
		score_r.Detach();
		score_r.Load(L"1.png");
	}
	if (count_r == 1) {
		score_l.Detach();
		score_l.Load(L"1.png");
	}
	if (count_l == 2) {
		score_r.Detach();
		score_r.Load(L"2.png");
	}
	if (count_r == 2) {
		score_l.Detach();
		score_l.Load(L"2.png");
	}
	if (count_l == 3) {
		score_r.Detach();
		score_r.Load(L"3.png");
	}
	if (count_r == 3) {
		score_l.Detach();
		score_l.Load(L"3.png");
	}

}


void CVBALLXView::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	start = TRUE;
	GetDlgItem(IDC_BUTTON1)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(FALSE);
	szSoundPath = _T("./pika.wav");
	PlaySound(szSoundPath, AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP); // 무한
}


void CVBALLXView::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MessageBox(_T("방향키 - 1P : W,A,S,D    2P : →,←,↑,↓\n"
		"공격키 - 1P : Space Bar 2P : Shift\n"));
}


void CVBALLXView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if ((point.x > 350&&point.x<600))
		if(point.y>250&&point.y<400)
			choice = 1;
	if (point.x > 620 && point.x < 850)
		if (point.y > 250 && point.y < 400)
			choice = 2;
	if (point.x > 910 && point.x < 1320)
		if (point.y > 250 && point.y < 400)
			choice = 3;
	CFormView::OnLButtonDown(nFlags, point);
}
