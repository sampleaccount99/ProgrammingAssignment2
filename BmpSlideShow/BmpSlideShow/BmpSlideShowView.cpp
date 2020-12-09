
// BmpSlideShowView.cpp : implementation of the CBmpSlideShowView class
// SDI Application to slideshow bmp files with 3 seconds delay
// Name :	Navaneeth K
// Date :	07/12/2020

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BmpSlideShow.h"
#endif

#include "BmpSlideShowDoc.h"
#include "BmpSlideShowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMER_ID 1234
#define TIMER_DELAY 3000

// CBmpSlideShowView

IMPLEMENT_DYNCREATE(CBmpSlideShowView, CView)

BEGIN_MESSAGE_MAP(CBmpSlideShowView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CBmpSlideShowView construction/destruction

CBmpSlideShowView::CBmpSlideShowView()
	: m_strFolderPath(_T(""))
	, m_pDC(NULL)
{
	// TODO: add construction code here

}

CBmpSlideShowView::~CBmpSlideShowView()
{
}

BOOL CBmpSlideShowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBmpSlideShowView drawing

void CBmpSlideShowView::OnDraw(CDC* pDC)
{
	CBmpSlideShowDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	SetpDc(pDC);
	if (!m_strFolderPath.IsEmpty())
	{
		CString strExt = m_strFolderPath.Right(3);
		strExt.MakeLower();
		if (_T("bmp") == strExt)
		{
			HANDLE hBitMap = ::LoadImage(0, m_strFolderPath,
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

			if (NULL != hBitMap)
			{
				CBitmap bmBitmap;
				bmBitmap.Attach((HBITMAP)hBitMap);

				BITMAP bmHdr;
				bmBitmap.GetBitmap(&bmHdr);

				CDC dcMem;
				dcMem.CreateCompatibleDC(m_pDC);
				HGDIOBJ hOldBitmap = dcMem.SelectObject(bmBitmap);

				CRect rectClient;
				GetClientRect(&rectClient);
				
				CPoint pt (200, 50);

				m_pDC->BitBlt (pt.x, pt.y, bmHdr.bmWidth, bmHdr.bmHeight, &dcMem, 0, 0, SRCCOPY);

				dcMem.SelectObject(hOldBitmap);
				DeleteObject(bmBitmap.Detach());
				bmBitmap.DeleteObject();
			}
		}
	}
}


// CBmpSlideShowView printing

BOOL CBmpSlideShowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBmpSlideShowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBmpSlideShowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CBmpSlideShowView diagnostics

#ifdef _DEBUG
void CBmpSlideShowView::AssertValid() const
{
	CView::AssertValid();
}

void CBmpSlideShowView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBmpSlideShowDoc* CBmpSlideShowView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBmpSlideShowDoc)));
	return (CBmpSlideShowDoc*)m_pDocument;
}
#endif //_DEBUG


// CBmpSlideShowView message handlers


void CBmpSlideShowView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (TIMER_ID == nIDEvent)
	{
		GetDocument()->UpdateAllViews(NULL);
		if (finder.FindNextFile())
		{
			m_strFolderPath = finder.GetFilePath();
		}
		else
		{
			m_strFolderPath = m_strFirstFile;
			m_strFolderPath += _T("\\*.bmp");
			finder.FindFile(m_strFolderPath);
		}
	}

	CView::OnTimer(nIDEvent);
}


void CBmpSlideShowView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	KillTimer(TIMER_ID);
}


void CBmpSlideShowView::SetpDc(CDC* pDC)
{
	m_pDC = pDC;
}

void CBmpSlideShowView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class

	CFolderPickerDialog dlgFolderPicker(NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, this, sizeof(OPENFILENAME));
	if (dlgFolderPicker.DoModal() == IDOK)
	{
		m_strFolderPath = dlgFolderPicker.GetPathName();
		m_strFirstFile = m_strFolderPath;
		m_strFolderPath += _T("\\*.bmp");
		finder.FindFile(m_strFolderPath);
	}
	SetTimer(TIMER_ID, TIMER_DELAY, NULL);
}
