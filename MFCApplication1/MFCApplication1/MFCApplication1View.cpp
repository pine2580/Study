
// MFCApplication1View.cpp : CMFCApplication1View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#endif
#include "MFCApplication1.h"
#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#include <atlimage.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CScrollView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
//	ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
ON_WM_PAINT()
ON_COMMAND(ID_match, &CMFCApplication1View::Onmatch)
ON_WM_PAINT()
ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONUP()
ON_WM_CREATE()
ON_COMMAND(IDOK, &CMFCApplication1View::OnIdok)
ON_BN_CLICKED(IDC_CHECK1, &CMFCApplication1View::OnBnClickedCheck1)
ON_WM_KEYDOWN()
ON_WM_CHAR()
END_MESSAGE_MAP()

// CMFCApplication1View 생성/소멸

CMFCApplication1View::CMFCApplication1View()
{
	// TODO: 여기에 생성 코드를 추가합니다.


}

CMFCApplication1View::~CMFCApplication1View()
{
}

//BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
//{
//	// TODO: CREATESTRUCT cs를 수정하여 여기에서
//	//  Window 클래스 또는 스타일을 수정합니다.
//
//}

// CMFCApplication1View 그리기
void swap(int *a, int* b)
{
	int buff = *a;
	*a = *b;
	*b = buff;
}
void bubbling(int *A, int num)
{
	for (int i = 0; i < num - 1; i++)
	{
		if (A[i]>A[i + 1])
			swap(&A[i], &A[i + 1]);
	}

}
void BubbleSort(int *A, int num)
{
	for (int i = 0; i < num - 2; i++)
		bubbling(A, num - i);
}
void CMFCApplication1View::dilation_erosion(int num)
{
	int tmp[9];
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	for (int y = 0; y < pDoc->height; y++) for (int x = 0; x < pDoc->width; x++)
	{
		pDoc->tmpImg[y][x] = pDoc->resultImg[y][x];
	}

	for (int y = 1; y < (pDoc->height) - 1; y++) for (int x = 1; x < (pDoc->width) - 1; x++)
	{
		tmp[0] = pDoc->tmpImg[y - 1][x - 1];
		tmp[1] = pDoc->tmpImg[y - 1][x];
		tmp[2] = pDoc->tmpImg[y - 1][x + 1];
		tmp[3] = pDoc->tmpImg[y][x - 1];
		tmp[4] = pDoc->tmpImg[y][x];
		tmp[5] = pDoc->tmpImg[y][x + 1];
		tmp[6] = pDoc->tmpImg[y + 1][x - 1];
		tmp[7] = pDoc->tmpImg[y + 1][x];
		tmp[8] = pDoc->tmpImg[y + 1][x + 1];
		BubbleSort(tmp, 9);
		pDoc->resultImg[y][x] = tmp[num];
	}
}
void CMFCApplication1View::OnDraw(CDC* pDC)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc) 
		return;
	if (viewmode == 0)
	{
		for (int y = 0; y < pDoc->height; y++) for (int x = 0; x < pDoc->width; x++)
		{
			pDoc->resultImg[y][x] = pDoc->inputImg[y][x];
		}
		if (pDoc->channel == 1)
		{
			for (int y = 0; y<pDoc->height; y++) for (int x = 0; x<pDoc->width; x++)
				pDC->SetPixel(x, y, RGB(pDoc->inputImg[y][x], pDoc->inputImg[y][x], pDoc->inputImg[y][x]));
		}
	}
	else if (viewmode == 1)
	{
		
		if (dilation == 1 && erosion == 0)//팽창
			dilation_erosion(num);
		else if (dilation == 0 && erosion == 1)//침식
			dilation_erosion(num);

		//if (pDoc->channel == 1)
		//{
			for (int y = 0; y<pDoc->height; y++) for (int x = 0; x<pDoc->width; x++)
				pDC->SetPixel(x, y, RGB(pDoc->resultImg[y][x], pDoc->resultImg[y][x], pDoc->resultImg[y][x]));
		//}
	}	
	/*	else if (pDoc->channel == 3)
		{
			for (int y = 0; y<pDoc->height; y++) for (int x = 0; x<pDoc->width; x++)
				pDC->SetPixel(x, y, RGB(pDoc->resultImg[y][x * 3], pDoc->resultImg[y][x * 3 + 1], pDoc->resultImg[y][x * 3 + 2]));
		}*/	
}

void CMFCApplication1View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	viewmode = 0;
	sizeTotal.cx = 2048;
	sizeTotal.cy = 1024;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CMFCApplication1View 인쇄


void CMFCApplication1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMFCApplication1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication1View 진단

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View 메시지 처리기


void CMFCApplication1View::Onmatch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->match();

	Invalidate(FALSE);
}


int CMFCApplication1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	/*for (int i = 50; i < m_ImgSample.GetHeight; i++)
		for (int j = 50; j < m_ImgSample.GetWidth; i++)
		{
			m_ImgSample.SetPixel(i, j,0);
		}*/
	
	return 0;
}

void CMFCApplication1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)
	{
	case VK_LEFT:  break;
	case VK_DOWN: erosion = 1; dilation = 0; viewmode = 1; num = 1; break;
	case VK_UP: erosion = 0; dilation = 1; viewmode = 1; num = 8; break;
	case VK_RIGHT:  break;
	}
	Invalidate();
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}




void CMFCApplication1View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nChar == ' ')
	{
		viewmode = 0;
	}
	Invalidate();
	CScrollView::OnChar(nChar, nRepCnt, nFlags);
}
