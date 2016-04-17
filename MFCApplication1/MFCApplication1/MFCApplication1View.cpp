
// MFCApplication1View.cpp : CMFCApplication1View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
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

// CMFCApplication1View ����/�Ҹ�

CMFCApplication1View::CMFCApplication1View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.


}

CMFCApplication1View::~CMFCApplication1View()
{
}

//BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
//{
//	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
//	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
//
//}

// CMFCApplication1View �׸���
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

void CMFCApplication1View::OnDraw(CDC* pDC)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(!pDoc) 
		return;
	int num;
	int tmp[9];
	
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
		for (int y = 0; y < pDoc->height; y++) for (int x = 0; x < pDoc->width; x++)
		{
			pDoc->tmpImg[y][x] = pDoc->resultImg[y][x];
		}
		if (dilation == 1 && erosion == 0)
			num = 8;
		else if (dilation == 0 && erosion == 1)
			num = 0;

		
		for (int y = 1; y < (pDoc->height)-1; y++) for (int x = 1; x < (pDoc->width)-1; x++)
		{
			/*if (y == 0 || y == (pDoc->height) - 1 || x == 0 || x == (pDoc->width) - 1)
				pDoc->resultImg[y][x] = pDoc->tmpImg[y][x];*/
			//else
			//{
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
			//}
		}

		if (pDoc->channel == 1)
		{
			for (int y = 0; y<pDoc->height; y++) for (int x = 0; x<pDoc->width; x++)
				pDC->SetPixel(x, y, RGB(pDoc->resultImg[y][x], pDoc->resultImg[y][x], pDoc->resultImg[y][x]));
		}
	}

		
	/*	else if (pDoc->channel == 3)
		{
			for (int y = 0; y<pDoc->height; y++) for (int x = 0; x<pDoc->width; x++)
				pDC->SetPixel(x, y, RGB(pDoc->resultImg[y][x * 3], pDoc->resultImg[y][x * 3 + 1], pDoc->resultImg[y][x * 3 + 2]));
		}*/
	
	/*CString strData;
	strData.Format(_T("X:%03d, Y:%03d"), m_ptLeft.x, m_ptLeft.y);
	pDC->TextOutA(0,0,strData);*/
	/*m_ImgSample.AlphaBlend(pDC->m_hDC, 0, 0, 50);
	CRgn Rgn;
	Rgn.CreateEllipticRgn(m_rectVisible.left, m_rectVisible.top, m_rectVisible.right, m_rectVisible.bottom);
	pDC->SelectClipRgn(&Rgn);
	m_ImgSample.BitBlt(pDC->m_hDC, 0, 0);*/
}

void CMFCApplication1View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: �� ���� ��ü ũ�⸦ ����մϴ�.
	viewmode = 0;
	sizeTotal.cx = 2048;
	sizeTotal.cy = 1024;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CMFCApplication1View �μ�


void CMFCApplication1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
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


// CMFCApplication1View ����

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View �޽��� ó����


void CMFCApplication1View::Onmatch()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->match();

	Invalidate(FALSE);
}


int CMFCApplication1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.

	/*for (int i = 50; i < m_ImgSample.GetHeight; i++)
		for (int j = 50; j < m_ImgSample.GetWidth; i++)
		{
			m_ImgSample.SetPixel(i, j,0);
		}*/
	
	return 0;
}

void CMFCApplication1View::OnIdok()
{
	// TODO: ���⿡ ��� ó���� �ڵ带 �߰��մϴ�.

}

void CMFCApplication1View::OnBnClickedCheck1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CMFCApplication1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch (nChar)
	{
	case VK_LEFT:  break;
	case VK_DOWN: erosion = 1; dilation = 0; viewmode = 1; break;
	case VK_UP: erosion = 0; dilation = 1; viewmode = 1; break;
	case VK_RIGHT:  break;
	}
	Invalidate();
	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}




void CMFCApplication1View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (nChar == ' ')
	{
		viewmode = 0;
	}
	Invalidate();
	CScrollView::OnChar(nChar, nRepCnt, nFlags);
}
