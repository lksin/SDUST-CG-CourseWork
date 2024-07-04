
// OpenGLView.h: COpenGLView 类的接口
//

#pragma once
#include <gl\gl.h> 
#include <gl\glu.h> 
#include <gl\glut.h> 
#include <gl\GLAUX.H>
#include "Vector.h"

#include <math.h>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

#define		MAP_SIZE	1024
#define		CELL_SIZE	2					// 相邻顶点的距离	
#define		STEP_SIZE	4					// 相邻顶点的距离	
#define		MAXN		200
#define 	INF 	   0x3f3f3f3f

class COpenGLView : public CView
{
protected: // 仅从序列化创建
	COpenGLView() noexcept;
	DECLARE_DYNCREATE(COpenGLView)

// 特性
public:
	COpenGLDoc* GetDocument() const;
	GLdouble aspect;	//视口宽高比 width/height
	BYTE g_HeightMap[MAP_SIZE * MAP_SIZE];		// 保存高度数据
	bool faceRender;		//true为表面渲染，false为线渲染
	bool lightingRender;
	GLfloat cameraX, cameraY, cameraZ;	//视点位置
	GLfloat lookx, looky, lookz;		//视线方向
	bool textureEnable = false;
	bool RoadEnable = false;
	void updateLighting();
public:
	struct DemStruct {
		string DataMark;
		float version;
		string unit;
		float x0, y0, x1, y1, xStep, yStep;
		int row, col, scale;
	}DemStruct;

	typedef struct VertexType  //存储图的信息
	{
		string name;
		float x;
		float y;
		float z;
	}VertexType;      //定义结点

	typedef struct AMGraph
	{
		VertexType vexs[200];
		int arcs[MAXN][MAXN];   //邻接矩阵
		int vexnum, arcnum;    //顶点、边的个数 
	}AMGrpah;
	AMGrpah Road;


	void COpenGLView::LoadDem(LPSTR file);
	void readRoadData(LPSTR file);
	void drawRoad(BYTE pRoadMap[]);
	void drawPointsDijkstra(int start, int end);

protected:
	int LoadGLTextures();
	GLuint	filter;				// Which Filter To Use
	GLuint	texture[3];			// Storage For 3 Textures
	AUX_RGBImageRec* LoadBMP(char* Filename);
// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
private:
	float** m_height;
	int row;

// 实现
public:
	virtual ~COpenGLView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	HDC hDC;
	int m_GLPixelIndex;
	HGLRC m_hGLContext;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	bool SetWindowPixelFormat(HDC hDC);
	bool CreateViewGLContext(HDC hDC);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnOpenrawfile();
	void LoadRawFile(LPSTR strName, int nSize, BYTE* pHeightMap);
	void RenderHeightMap(BYTE pHeightMap[]);
	void RenderNewMap();
	int Height(BYTE* pHeightMap, int X, int Y);
	void SetNormal(int x, int y, int z, int x1, int y1, int z1, int x2, int y2, int z2);
	void SetVertexColor(int x, int y, int z);
	//virtual void LoadDemFile(LPSTR strName);
	afx_msg void OnLines();
	afx_msg void OnTriangles();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLighting();
	afx_msg void OnReadDem();
	afx_msg void OnDrawTexture();
	afx_msg void OnDrawRoad();
	afx_msg void OnDijkstra();
};

#ifndef _DEBUG  // OpenGLView.cpp 中的调试版本
inline COpenGLDoc* COpenGLView::GetDocument() const
   { return reinterpret_cast<COpenGLDoc*>(m_pDocument); }
#endif

