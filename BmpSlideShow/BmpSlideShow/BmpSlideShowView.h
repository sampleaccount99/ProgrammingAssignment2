
// BmpSlideShowView.h : interface of the CBmpSlideShowView class
//

#pragma once
#include "afx.h"


class CBmpSlideShowView : public CView
{
protected: // create from serialization only
	CBmpSlideShowView();
	DECLARE_DYNCREATE(CBmpSlideShowView)

// Attributes
public:
	CBmpSlideShowDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CBmpSlideShowView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
private:
	CString m_strFolderPath;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	void SetpDc(CDC* pDC);
private:
	CDC* m_pDC;
public:
	virtual void OnInitialUpdate();
private:
	CString m_strFirstFile;
	CFileFind finder;

};

#ifndef _DEBUG  // debug version in BmpSlideShowView.cpp
inline CBmpSlideShowDoc* CBmpSlideShowView::GetDocument() const
   { return reinterpret_cast<CBmpSlideShowDoc*>(m_pDocument); }
#endif

