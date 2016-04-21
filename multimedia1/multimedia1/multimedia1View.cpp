
// multimedia1View.cpp : Cmultimedia1View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "multimedia1.h"
#endif

#include "multimedia1Doc.h"
#include "multimedia1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cmultimedia1View

IMPLEMENT_DYNCREATE(Cmultimedia1View, CView)

BEGIN_MESSAGE_MAP(Cmultimedia1View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Cmultimedia1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Cmultimedia1View ����/�Ҹ�

Cmultimedia1View::Cmultimedia1View()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

Cmultimedia1View::~Cmultimedia1View()
{
}

BOOL Cmultimedia1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// Cmultimedia1View �׸���

void Cmultimedia1View::OnDraw(CDC* /*pDC*/)
{
	Cmultimedia1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// Cmultimedia1View �μ�


void Cmultimedia1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Cmultimedia1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void Cmultimedia1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void Cmultimedia1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}

void Cmultimedia1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Cmultimedia1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Cmultimedia1View ����

#ifdef _DEBUG
void Cmultimedia1View::AssertValid() const
{
	CView::AssertValid();
}

void Cmultimedia1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cmultimedia1Doc* Cmultimedia1View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cmultimedia1Doc)));
	return (Cmultimedia1Doc*)m_pDocument;
}
#endif //_DEBUG


// Cmultimedia1View �޽��� ó����
