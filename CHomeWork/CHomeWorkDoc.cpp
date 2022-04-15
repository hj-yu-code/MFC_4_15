
// CHomeWorkDoc.cpp: CCHomeWorkDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "CHomeWork.h"
#endif

#include "CHomeWorkDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCHomeWorkDoc

IMPLEMENT_DYNCREATE(CCHomeWorkDoc, CDocument)

BEGIN_MESSAGE_MAP(CCHomeWorkDoc, CDocument)
	ON_COMMAND(IDM_COLOR_GREEN, &CCHomeWorkDoc::OnColorGreen)
	ON_UPDATE_COMMAND_UI(IDM_COLOR_GREEN, &CCHomeWorkDoc::OnUpdateColorGreen)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_COLOR, &CCHomeWorkDoc::OnUpdateIndicatorColor)
END_MESSAGE_MAP()


// CCHomeWorkDoc 생성/소멸

CCHomeWorkDoc::CCHomeWorkDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CCHomeWorkDoc::~CCHomeWorkDoc()
{
}

BOOL CCHomeWorkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.
	m_line.m_nWidth = 10;
	m_line.m_penColor = RGB(255, 0, 0); // tnwjd

	return TRUE;
}




// CCHomeWorkDoc serialization

void CCHomeWorkDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		ar << m_lines.size();
		for (const CDrawLine& line : m_lines) {
			ar << line.m_nWidth;
			ar << line.m_penColor;
			ar << line.m_array.size();
			for (const CPoint pt : line.m_array) {
				ar << pt.x;
				ar << pt.y;
			}
		}
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		int lines_size, array_size;
		CPoint pt;
		ar >> lines_size;
		for (int i = 0; i < lines_size; i++) {
			// ar.Read(&m_line.m_pen, sizeof(m_line.m_pen)); // 구조체는 이렇게 읽는게 더 빠름. 관리하기도 좋음.

			ar >> m_line.m_nWidth;
			ar >> m_line.m_penColor;
			ar >> array_size;
			m_line.clear();
			m_line.m_array.resize(array_size);
			ar.Read(&m_line.m_array[0], sizeof(CPoint) * array_size); // 한번에 넣기
			/*for (int j = 0; j < array_size; j++) {
				ar >> pt.x;
				ar >> pt.y;
				m_line.m_array.push_back(pt);
			}*/
			m_lines.push_back(m_line);
		}
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CCHomeWorkDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CCHomeWorkDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CCHomeWorkDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCHomeWorkDoc 진단

#ifdef _DEBUG
void CCHomeWorkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCHomeWorkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCHomeWorkDoc 명령


void CCHomeWorkDoc::DeleteContents()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_line.clear();
	m_lines.clear();

	CDocument::DeleteContents();
}


void CCHomeWorkDoc::OnColorGreen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_line.m_penColor = RGB(0, 255, 0);
}


void CCHomeWorkDoc::OnUpdateColorGreen(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	pCmdUI->SetCheck(m_line.m_penColor == RGB(0, 255, 0));
}


void CCHomeWorkDoc::OnUpdateIndicatorColor(CCmdUI* pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	switch (m_line.m_penColor) {
	case RGB(255, 0, 0):
		pCmdUI->SetText(_T("빨간색"));
		break;
	case RGB(0, 255, 0):
		pCmdUI->SetText(_T("초록색"));
		break;
	case RGB(0, 0, 255):
		pCmdUI->SetText(_T("파랑색"));
		break;
	default:
		pCmdUI->SetText(_T(""));
		break;
	}
}
