
// MFCToolView.cpp : CMFCToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCTool.h"
#endif

#include "MFCToolDoc.h"
#include "MFCToolView.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCToolView

IMPLEMENT_DYNCREATE(CMFCToolView, CView)

BEGIN_MESSAGE_MAP(CMFCToolView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCToolView 생성/소멸

CMFCToolView::CMFCToolView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCToolView::~CMFCToolView()
{
	
}

BOOL CMFCToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCToolView 그리기

void CMFCToolView::OnDraw(CDC* /*pDC*/)
{
	CMFCToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	
}


// CMFCToolView 인쇄

BOOL CMFCToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCToolView 진단

#ifdef _DEBUG
void CMFCToolView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCToolView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

void CMFCToolView::Render(void)
{
	Engine::Render_Begin(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));

	m_pRcTex->Render_Buffer();

	Engine::Render_End();
}

CMFCToolDoc* CMFCToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCToolDoc)));
	return (CMFCToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCToolView 메시지 처리기


void CMFCToolView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	//장치 초기화
	if (FAILED(Engine::Ready_GraphicDev(m_hWnd,
		Engine::MODE_WIN,
		WINCX,
		WINCY,
		&m_pDeviceClass)))
		return;

	m_pDeviceClass->AddRef();
	m_pGraphicDev = m_pDeviceClass->GetDevice();

	//폼뷰생성

	CMainFrame* pMainFrame = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());

	RECT rcMain = {};

	// 주의 사항 - 애는 스크린 좌표를 얻어옴. 즉 스크린에서 100, 100에 생성되면 레프트 탑은 100, 100 되겠다 그래서 0,0 으로 옮겨버릴꺼야 .
	pMainFrame->GetWindowRect(&rcMain);

	SetRect(&rcMain, 0, 0, rcMain.right - rcMain.left, rcMain.bottom - rcMain.top);

	RECT rcView{};
	// 애는 클라좌표. 즉 좌측 상단이 0, 0에서 시작. 
	GetClientRect(&rcView);
	int iWidth = rcMain.right - rcView.right;
	int iHeight = rcMain.bottom - rcView.bottom;

	pMainFrame->SetWindowPos(nullptr, 0, 0, WINCX + iWidth, WINCY + iHeight, SWP_NOZORDER);

	Engine::Reserve_ContainerSize(Engine::ID_END);

	Engine::Ready_Buffer(m_pGraphicDev, Engine::ID_STATIC, L"Buffer_RcTex", Engine::BUFFER_RCTEX);
	m_pRcTex = Engine::CRcTex::Create(m_pGraphicDev);

	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);


	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}
