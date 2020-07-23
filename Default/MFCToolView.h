
// MFCToolView.h : CMFCToolView 클래스의 인터페이스
//

#pragma once

#include "Export_Function.h"

#include "RcTex.h"

class CMFCToolDoc;
class CRcTex;

class CMFCToolView : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCToolView();
	DECLARE_DYNCREATE(CMFCToolView)

// 특성입니다.
public:
	CMFCToolDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMFCToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void Render(void);

protected:

private:
	Engine::CGraphicDev*		m_pDeviceClass = nullptr;
	LPDIRECT3DDEVICE9			m_pGraphicDev = nullptr;
	Engine::CRcTex*				m_pRcTex = nullptr;
// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // MFCToolView.cpp의 디버그 버전
inline CMFCToolDoc* CMFCToolView::GetDocument() const
   { return reinterpret_cast<CMFCToolDoc*>(m_pDocument); }
#endif

