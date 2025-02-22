
// V_BALL_XView.h: CVBALLXView 클래스의 인터페이스
//

#pragma once
#include <atlimage.h>
#pragma comment(lib, "winmm")
#include <mmsystem.h>

class CVBALLXView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CVBALLXView();
	DECLARE_DYNCREATE(CVBALLXView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_V_BALL_X_FORM };
#endif
public:
	int nX, nY; //원의 중심
	int nMx, nMy; //무빙 x,y;

// 특성입니다.
public:
	CVBALLXDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CVBALLXView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	//////png파일 변수///////////
	CImage m_ball;
	CImage m_lionr;
	CImage m_lionl;
	CImage m_appeachr;
	CImage m_appeachl;
	CImage m_tuber;
	CImage m_tubel;
	CImage score_l;
	CImage score_r;
	CImage gameove;
	CImage kakao;
	CImage choice_l;
	CImage choice_t;
	CImage choice_a;
	CImage effect;
	////////////////////////////
	afx_msg void OnPaint();
	///////////키보드이벤트관련 변수 함수///////
	int m_charactorx_r;
	int m_charactorx_l;
	int m_up_r;
	int m_up_l;
	int check[4];
	virtual BOOL PreTranslateMessage(MSG* pMsg);
    //////////////////공움직이기 변수///////////////////////////
	int m_ballx;
	int m_bally;
	int count_l;
	int count_r;
	int win[2];
	////////////////////////////////////////////
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	void score();
	CString szSoundPath;
	bool start;
	int choice;
//	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // V_BALL_XView.cpp의 디버그 버전
inline CVBALLXDoc* CVBALLXView::GetDocument() const
   { return reinterpret_cast<CVBALLXDoc*>(m_pDocument); }
#endif

