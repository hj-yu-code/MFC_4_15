
// CHomeWorkDoc.h: CCHomeWorkDoc 클래스의 인터페이스
//


#pragma once

#include <vector>
using namespace std;

class CDrawLine {
public:
	COLORREF m_penColor;
	int m_nWidth;
	// LOGPEN m_pen;
	vector<CPoint> m_array;
public:
	void clear() {
		m_array.clear();
	}
	void DrawAll(CDC* pDC) const {
		pDC->MoveTo(m_array[0]);

		CPen pen(PS_SOLID, m_nWidth, m_penColor);
		CPen* pOldpen = pDC->SelectObject(&pen);

		for (const CPoint& pt : m_array) {
			pDC->LineTo(pt);
		}
		pDC->SelectObject(pOldpen);
	}
	void DrawLastLine(CDC *pDC, CPoint& point) {

		CPen pen(PS_SOLID, m_nWidth, m_penColor);
		CPen* pOldpen = pDC->SelectObject(&pen);

		pDC->MoveTo(m_array[m_array.size() - 1]);
		pDC->LineTo(point);

		pDC->SelectObject(pOldpen);
	}
	void push_back(const CPoint& point) {
		m_array.push_back(point);
	}
};

class CCHomeWorkDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CCHomeWorkDoc() noexcept;
	DECLARE_DYNCREATE(CCHomeWorkDoc)

// 특성입니다.
public:
	//vector<CPoint> m_array;
	//vector<vector<CPoint>> m_lines;

	CDrawLine m_line;
	vector<CDrawLine> m_lines;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CCHomeWorkDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual void DeleteContents();
	afx_msg void OnColorGreen();
	afx_msg void OnUpdateColorGreen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateIndicatorColor(CCmdUI* pCmdUI);
};
