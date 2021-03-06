
// opencv_kesheDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "opencv_keshe.h"
#include "opencv_kesheDlg.h"
#include "afxdialogex.h"
#include<cstring>
//#include<string.h>
#include"opencv2/core/core.hpp"
#include"opencv2/highgui/highgui.hpp"
#include<iostream>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//void StrtCh(char *q,CString p)
//{
//	int i;
//	for (i = 0; i < p.GetLength(); ++i)
//		q[i] = p[i];
//	q[i] = '\0';
//}

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CopencvkesheDlg 对话框



CopencvkesheDlg::CopencvkesheDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OPENCV_KESHE_DIALOG, pParent)
	, Xc(0)
	, Yc(0)
	, Alpha(0)
	, Ax(0)
	, Ay(0)
	, Tx(0)
	, Ty(0)
	, X(0)
	, Y(0)
	, P(0)
	, Rmax(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CopencvkesheDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, Xc);
	DDX_Text(pDX, IDC_EDIT3, Yc);
	DDX_Text(pDX, IDC_EDIT4, Alpha);
	DDX_Control(pDX, IDC_EDIT2, Xedit);
	DDX_Control(pDX, IDC_EDIT3, Yedit);
	DDX_Control(pDX, IDC_EDIT4, AlphaEdit);
	DDX_Text(pDX, IDC_EDIT5, Ax);
	DDX_Text(pDX, IDC_EDIT6, Ay);
	DDX_Text(pDX, IDC_EDIT7, Tx);
	DDX_Text(pDX, IDC_EDIT8, Ty);
	DDX_Text(pDX, IDC_EDIT9, X);
	DDX_Text(pDX, IDC_EDIT10, Y);
	DDX_Text(pDX, IDC_EDIT11, P);
	DDX_Text(pDX, IDC_EDIT12, Rmax);
	DDX_Control(pDX, IDC_COMBO1, m_com);
}

BEGIN_MESSAGE_MAP(CopencvkesheDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, &CopencvkesheDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_NIU, &CopencvkesheDlg::OnBnClickedNiu)
	ON_BN_CLICKED(IDC_BO, &CopencvkesheDlg::OnBnClickedBo)
	ON_BN_CLICKED(IDC_QIU, &CopencvkesheDlg::OnBnClickedQiu)
	ON_BN_CLICKED(IDC_SAVE, &CopencvkesheDlg::OnBnClickedSave)
END_MESSAGE_MAP()


// CopencvkesheDlg 消息处理程序

BOOL CopencvkesheDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	m_com.AddString(_T("最近邻域插值"));
	m_com.AddString(_T("双线性插值"));
	m_com.SetCurSel(0);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CopencvkesheDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CopencvkesheDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CopencvkesheDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CopencvkesheDlg::OnBnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	//选择图片
	CFileDialog fileDlg(TRUE, _T("png"), NULL, 0, _T("image Files(*.bmp; *.jpg;*.png)|*.JPG;*.PNG;*.BMP|All Files (*.*) |*.*||"), this);
	fileDlg.DoModal();
	//获取图片路径和图片名称
	CString strFilePath = fileDlg.GetPathName();
	CString strFileName = fileDlg.GetFileName();
	const char* str = new char[strFilePath.GetLength()+1];
	//判断路径不为空
	
	if (strFilePath == _T("")) return;

	CStringA strA(strFilePath.GetBuffer(0));
	strFilePath.ReleaseBuffer();
	string s = strA.GetBuffer(0);
	str = s.c_str();

	IplImage *image = NULL; //原始图像
	if (image) cvReleaseImage(&image);
	image = cvLoadImage(str, 1); //显示图片
	currentSrc = imread(str, CV_LOAD_IMAGE_COLOR);
	DrawPicToHDC(image, IDC_STATIC);
}
void CopencvkesheDlg::DrawPicToHDC(IplImage *img, UINT ID)
{
	CDC *pDC = GetDlgItem(ID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	CRect rect1;
	GetDlgItem(ID)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(img); // 复制图片
	int height, width;
	height = img->height;
	width = img->width;
	if (width <= rect.Width()&& height <= rect.Width())
	{
		rect1 = CRect(rect.TopLeft(), CSize(width, height));
	}
	else
	{
		float xScale = (float)rect.Width() / (float)width;
		float yScale = (float)rect.Height() / (float)height;
		float ScaleIndex = (xScale >= yScale?xScale: yScale);
		rect1 = CRect(rect.TopLeft(), CSize((int)width*ScaleIndex, (int)height*ScaleIndex));
	}
	cimg.DrawToHDC(hDC, &rect1); // 将图片绘制到显示控件的指定区域内
	ReleaseDC(pDC);
}

void CopencvkesheDlg::OnBnClickedNiu()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!currentSrc.data)
	{
		AfxMessageBox(_T("请先打开一张图片"));
		return;
	}
	UpdateData(true);
	if (Xc == 0 && Yc == 0)
	{
		Xc = currentSrc.cols/2;
		Yc = currentSrc.rows/2;
	}
	if (Yc>currentSrc.rows || Xc > currentSrc.cols)
	{
		AfxMessageBox(_T("坐标越界！"));
		return;
	}
	NiuQu(Xc, Yc, Alpha);
}


void CopencvkesheDlg::NiuQu(float Xc, float Yc, float Alpha)
{
	Mat map1, map2;
	int xc, yc;
	float rmax, dx, dy, r, beta, alpha;
	xc = Xc;
	yc = Yc;
	//xc = currentSrc.cols / 2;
	//yc = currentSrc.rows / 2;
	alpha = Alpha;
	rmax = 0;
	map1.create(currentSrc.size(), CV_32FC1);
	map2.create(currentSrc.size(), CV_32FC1);
	out_image.create(currentSrc.size(), currentSrc.type());
	for (int i = 0; i<currentSrc.rows; i++)
		for (int j = 0; j < currentSrc.cols; j++)
		{
			dx = j - xc;
			dy = i - yc;
			r = sqrt(dx*dx + dy * dy);
			if (rmax < r)
				rmax = r;
		}
	for (int i = 0; i < currentSrc.rows; i++)
	{
		float * p = map1.ptr<float>(i);
		float * q = map2.ptr<float>(i);
		dy = i - yc;
		for (int j = 0; j < currentSrc.cols; j++)
		{
			dx = j - xc;

			r = sqrt(dx*dx + dy * dy);

			beta = atan2(dx, dy) + alpha * (rmax - r) / rmax;
			if (r <= rmax)
			{
				p[j] = xc + r * cos(beta);
				q[j] = yc + r * sin(beta);
			}
			else
			{
				p[j] = j;
				q[j] = i;
			}

		}
	}
	if(m_com.GetCurSel()==0)
		remap(currentSrc, out_image, map1, map2, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar());
	else
		remap(currentSrc, out_image, map1, map2, INTER_NEAREST, BORDER_CONSTANT, Scalar());
	IplImage* image;
	image = &IplImage(out_image);
	DrawPicToHDC(image, IDC_STATIC);

}

void CopencvkesheDlg::BoDong(float Ax, float Ay,float Tx, float Ty)
{
	Mat map1, map2;
	map1.create(currentSrc.size(), CV_32FC1);
	map2.create(currentSrc.size(), CV_32FC1);
	out_image.create(currentSrc.size(), currentSrc.type());
	for (int i = 0; i < currentSrc.rows; i++)
	{
		float * p = map1.ptr<float>(i);
		float * q = map2.ptr<float>(i);
		for (int j = 0; j < currentSrc.cols; j++)
		{
			p[j] = j + Ax * sin(6.28*i / Tx);
			q[j] = i + Ay * sin(6.28*j / Ty);
		}
	}
	if (m_com.GetCurSel() == 0)
		remap(currentSrc, out_image, map1, map2, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar());
	else
		remap(currentSrc, out_image, map1, map2, INTER_NEAREST, BORDER_CONSTANT, Scalar());
	IplImage* image;
	image = &IplImage(out_image);
	DrawPicToHDC(image, IDC_STATIC);
}


void CopencvkesheDlg::OnBnClickedBo()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!currentSrc.data)
	{
		AfxMessageBox(_T("请先打开一张图片"));
		return;
	}
	UpdateData(true);
	BoDong(Ax, Ay, Tx, Ty);
}


void CopencvkesheDlg::OnBnClickedQiu()
{
	// TODO: 在此添加控件通知处理程序代码
	if(!currentSrc.data)
	{
		AfxMessageBox(_T("请先打开一张图片"));
		return;
	}
	UpdateData(true);
	if (X == 0 && Y == 0)
	{
		X = currentSrc.cols/2;
		Y = currentSrc.rows/2;
	}
	QiuXing(X, Y, P,Rmax);
}

void CopencvkesheDlg::QiuXing(float X, float Y, float P,float Rmax)
{
	if (P==0)
	{
		AfxMessageBox(_T("P不能为0！"));
		return;
	}
	Mat map1, map2;
	int xc, yc;
	float rmax, dx, dy, r, betax,betay,z;
	xc = X;
	yc = Y;
	rmax = Rmax;
	map1.create(currentSrc.size(), CV_32FC1);
	map2.create(currentSrc.size(), CV_32FC1);
	out_image.create(currentSrc.size(), currentSrc.type());
	
	for (int i = 0; i < currentSrc.rows; i++)
	{
		float * p = map1.ptr<float>(i);
		float * q = map2.ptr<float>(i);
		dy = i - yc;
		for (int j = 0; j < currentSrc.cols; j++)
		{
			dx = j - xc;

			r = sqrt(dx*dx + dy * dy);
			z = sqrt(rmax*rmax - r * r);
			betax = (1 - 1 / P)*(asin((dx / sqrt(dx*dx+z*z))));
			betay = (1 - 1 / P)*(asin((dy / sqrt(dy*dy + z * z))));
			if (r <= rmax)
			{
				p[j] = j - z * tan(betax);
				q[j] =i - z*tan(betay);
			}
			else
			{
				p[j] = j;
				q[j] = i;
			}

		}
	}
	if (m_com.GetCurSel() == 0)
		remap(currentSrc, out_image, map1, map2, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar());
	else
		remap(currentSrc, out_image, map1, map2, INTER_NEAREST, BORDER_CONSTANT, Scalar());
	IplImage* image;
	image = &IplImage(out_image); 
	DrawPicToHDC(image, IDC_STATIC);
}

void CopencvkesheDlg::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
	if (out_image.data != NULL)
	{
		CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			(LPCTSTR)_TEXT("All Files (*.*)|*.*||"),
			AfxGetMainWnd());    //构造文件另存为对话框
		CString FilePathName;
		if (dlg.DoModal() == IDOK)         //判断是否按下"保存"按钮
		{
			FilePathName = dlg.GetPathName(); //获得文件保存路径
		}
		else
		{
			return;
		}
		string filePath = CT2A(FilePathName);
		imwrite(filePath, out_image);
		AfxMessageBox(_T("保存成功！"));
	}
	else
		AfxMessageBox(_T("没有可保存的图片！"));
}
