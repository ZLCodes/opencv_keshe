
// opencv_kesheDlg.h: 头文件
//
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "CvvImage.h"
#include "afxwin.h"
using namespace cv;
#pragma once


// CopencvkesheDlg 对话框
class CopencvkesheDlg : public CDialog
{
// 构造
public:
	CopencvkesheDlg(CWnd* pParent = NULL);	// 标准构造函数
	void DrawPicToHDC(IplImage *img, UINT ID);
	Mat currentSrc;
	Mat out_image;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENCV_KESHE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedNiu();
	void NiuQu(float Xc,float Yc,float Alpha);
	void BoDong(float Ax, float Ay,float Tx, float Ty);
	void QiuXing(float X, float Y, float P,float Rmax);
	float Xc;
	float Yc;
	float Alpha;
	CEdit Xedit;
	CEdit Yedit;
	CEdit AlphaEdit;
	float Ax;
	float Ay;
	float Tx;
	float Ty;
	afx_msg void OnBnClickedBo();
	float X;
	float Y;
	float P;
	afx_msg void OnBnClickedQiu();
	float Rmax;
	CComboBox m_com;
	afx_msg void OnBnClickedSave();
};
