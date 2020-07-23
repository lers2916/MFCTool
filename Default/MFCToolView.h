
// MFCToolView.h : CMFCToolView Ŭ������ �������̽�
//

#pragma once

#include "Export_Function.h"

#include "RcTex.h"

class CMFCToolDoc;
class CRcTex;

class CMFCToolView : public CView
{
protected: // serialization������ ��������ϴ�.
	CMFCToolView();
	DECLARE_DYNCREATE(CMFCToolView)

// Ư���Դϴ�.
public:
	CMFCToolDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
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
// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // MFCToolView.cpp�� ����� ����
inline CMFCToolDoc* CMFCToolView::GetDocument() const
   { return reinterpret_cast<CMFCToolDoc*>(m_pDocument); }
#endif

