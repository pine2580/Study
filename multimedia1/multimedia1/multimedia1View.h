
// multimedia1View.h : Cmultimedia1View Ŭ������ �������̽�
//

#pragma once


class Cmultimedia1View : public CView
{
protected: // serialization������ ��������ϴ�.
	Cmultimedia1View();
	DECLARE_DYNCREATE(Cmultimedia1View)

// Ư���Դϴ�.
public:
	Cmultimedia1Doc* GetDocument() const;

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
	virtual ~Cmultimedia1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // multimedia1View.cpp�� ����� ����
inline Cmultimedia1Doc* Cmultimedia1View::GetDocument() const
   { return reinterpret_cast<Cmultimedia1Doc*>(m_pDocument); }
#endif
