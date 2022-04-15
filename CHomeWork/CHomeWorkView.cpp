
// CHomeWorkView.cpp: CCHomeWorkView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "CHomeWork.h"
#endif

#include "CHomeWorkDoc.h"
#include "CHomeWorkView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCHomeWorkView

IMPLEMENT_DYNCREATE(CCHomeWorkView, CView)

BEGIN_MESSAGE_MAP(CCHomeWorkView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// CCHomeWorkView 생성/소멸

CCHomeWorkView::CCHomeWorkView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CCHomeWorkView::~CCHomeWorkView()
{
}

BOOL CCHomeWorkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CCHomeWorkView 그리기

void CCHomeWorkView::OnDraw(CDC* pDC)
{
	CCHomeWorkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	for (const CDrawLine& line : pDoc->m_lines) { // 여러줄 그릴 수 있게 하기
		line.DrawAll(pDC);
		
	}
}


// CCHomeWorkView 인쇄

BOOL CCHomeWorkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CCHomeWorkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CCHomeWorkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CCHomeWorkView 진단

#ifdef _DEBUG
void CCHomeWorkView::AssertValid() const
{
	CView::AssertValid();
}

void CCHomeWorkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCHomeWorkDoc* CCHomeWorkView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCHomeWorkDoc)));
	return (CCHomeWorkDoc*)m_pDocument;
}
#endif //_DEBUG


// CCHomeWorkView 메시지 처리기


void CCHomeWorkView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CCHomeWorkDoc* pDoc = GetDocument();

	SetCapture();

	pDoc->m_line.m_array.clear();
	pDoc->m_line.m_array.push_back(point);

	CView::OnLButtonDown(nFlags, point);
}


void CCHomeWorkView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CCHomeWorkDoc* pDoc = GetDocument();

	ReleaseCapture();

	pDoc->m_lines.push_back(pDoc->m_line); // 줄 넣기

	pDoc->SetModifiedFlag(); // button up 한 상태 이후 저장하기

	CView::OnLButtonUp(nFlags, point);
}

#include "MainFrm.h"
void CCHomeWorkView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if ((nFlags & MK_LBUTTON) == MK_LBUTTON) {

		CCHomeWorkDoc* pDoc = GetDocument();
		CClientDC dc(this);

		pDoc->m_line.DrawLastLine(&dc, point);

		pDoc->m_line.push_back(point);
	}

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	pMainFrame->SetMousePositionOutput(point);

	CView::OnMouseMove(nFlags, point);
}
