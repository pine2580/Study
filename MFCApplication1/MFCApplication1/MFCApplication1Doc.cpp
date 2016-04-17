
// MFCApplication1Doc.cpp : CMFCApplication1Doc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"
#include <string.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplication1Doc

IMPLEMENT_DYNCREATE(CMFCApplication1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplication1Doc, CDocument)
END_MESSAGE_MAP()


// CMFCApplication1Doc 생성/소멸

CMFCApplication1Doc::CMFCApplication1Doc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMFCApplication1Doc::~CMFCApplication1Doc()
{
}

BOOL CMFCApplication1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}

unsigned char **ImageCalloc(int width, int height, int channel)
{
	unsigned char** image = (unsigned char **)calloc(height, sizeof(unsigned char *));

	for (int i = 0; i<height; i++)
		image[i] = (unsigned char *)calloc(width*channel, sizeof(unsigned char));

	return(image);
}


// CMFCApplication1Doc serialization

void CMFCApplication1Doc::Serialize(CArchive& ar)
{
	int i, j;
	CFile *fp = ar.GetFile();
	CString fname = fp->GetFilePath();

	if (ar.IsStoring() == TRUE)
	{

	}
	else //파일 오픈 버튼을 눌렀을 때
	{
		IplImage* image = cvLoadImage(ar.m_strFileName, CV_LOAD_IMAGE_UNCHANGED);
		width = image->width;
		height = image->height;
		channel = image->nChannels;
		inputImg = ImageCalloc(width, height, channel);
		resultImg = ImageCalloc(width, height, channel);
		
		for (i = 0; i<height; i++) for (j = 0; j<width; j++)
			inputImg[i][j] = CV_IMAGE_ELEM(image, unsigned char, i, j);
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMFCApplication1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CMFCApplication1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCApplication1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCApplication1Doc 진단

#ifdef _DEBUG
void CMFCApplication1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCApplication1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCApplication1Doc 명령
unsigned char** ReadImage(char *name, int& width, int& height, int& channel)
{
	int i, j;
	IplImage* image = cvLoadImage(name, CV_LOAD_IMAGE_GRAYSCALE); // CV_LOAD_IMAGE_GRAYSCALE

	width = image->width;
	height = image->height;
	channel = image->nChannels;

	unsigned char** inputImg = (unsigned char**)ImageCalloc(width, height, channel);

	if (channel == 1)
	{
		for (i = 0; i<height; i++) for (j = 0; j<width; j++)
			inputImg[i][j] = CV_IMAGE_ELEM(image, unsigned char, i, j);
	}

	else if (channel == 3)
	{
		for (i = 0; i<height; i++) for (j = 0; j<width; j++)
		{
			inputImg[i][j * 3 + 2] = image->imageData[image->widthStep * i + j * 3];//B  
			inputImg[i][j * 3 + 1] = image->imageData[image->widthStep * i + j * 3 + 1]; //G
			inputImg[i][j * 3] = image->imageData[image->widthStep * i + j * 3 + 2]; //R  
		}
	}
	cvReleaseImage(&image);

	return(inputImg);

}


void CMFCApplication1Doc::match()
{
	int i, j;
	//unsigned char **img_in = ReadImage("크기변환송중기.jpg", width, height, channel);
	unsigned char **img_in = ReadImage("input.bmp", width, height, channel);
	inputImg = ImageCalloc(width, height, channel);
	//view_mode = 1;
	for (i = 0; i < height; i++) for (j = 0; j < width*channel; j++)
		inputImg[i][j] = img_in[i][j];

	//unsigned char **img_out = ReadImage("꾸미기_송중기.jpg", width, height, channel);
	resultImg = ImageCalloc(width, height, channel);
	//view_mode = 1;
	/*for (i = 0; i < height; i++) for (j = 0; j < width*channel; j++)
		resultImg[i][j] = img_out[i][j];*/

	tmpImg = ImageCalloc(width, height, channel);
	/*CString string;
	string.Format(_T(":)"));
	AfxMessageBox(string);*/
	
}
