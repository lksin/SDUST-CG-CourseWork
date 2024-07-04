
// OpenGLView.cpp: COpenGLView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "OpenGL.h"
#endif

#include "OpenGLDoc.h"
#include "OpenGLView.h"
#include "DlgInpputPath.h"
#include "DlgPic.h"
#include "test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

const int PI = 3.1415926535;
float simulatedTime = 0.0f; // 从0点开始模拟时间
float timeSpeed = 0.1f; // 时间变化速度，可以根据需要调整
// COpenGLView

IMPLEMENT_DYNCREATE(COpenGLView, CView)

BEGIN_MESSAGE_MAP(COpenGLView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_COMMAND(ID_OPENRAWFILE, &COpenGLView::OnOpenrawfile)
	ON_COMMAND(ID_LINES, &COpenGLView::OnLines)
	ON_COMMAND(ID_TRIANGLES, &COpenGLView::OnTriangles)
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_LIGHTING, &COpenGLView::OnLighting)
	ON_COMMAND(ID_32780, &COpenGLView::OnReadDem)
	ON_COMMAND(ID_32781, &COpenGLView::OnDrawTexture)
	ON_COMMAND(ID_32783, &COpenGLView::OnDrawRoad)
	ON_COMMAND(ID_32784, &COpenGLView::OnDijkstra)
	ON_COMMAND(ID_32785, &COpenGLView::OnDij)
	ON_COMMAND(ID_32786, &COpenGLView::OnPic)
	ON_COMMAND(ID_TEST_TEST, &COpenGLView::OnTestTest)
END_MESSAGE_MAP()

// COpenGLView 构造/析构

COpenGLView::COpenGLView() noexcept
{
	// TODO: 在此处添加构造代码
	this->m_GLPixelIndex = 0;
	this->m_hGLContext = NULL;

	faceRender = true;
	lightingRender = false;

	cameraX = 2000;
	cameraY = 1000;
	cameraZ = 2000;

	lookx = -100.0;
	looky = -50.0;
	lookz = -100.0;

	textureEnable = false;
	RoadEnable = false;
	filter = 0;

}

COpenGLView::~COpenGLView()
{
}

BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

	return CView::PreCreateWindow(cs);
}

void COpenGLView::updateLighting()
{
	// 将时间转换为角度，假设一天是360度
	float angle = (simulatedTime / 24.0f) * 2 * PI;

	// 计算光源位置
	GLfloat m_lightPos[4];
	m_lightPos[0] = 1500.0f * cos(angle);   // X
	m_lightPos[1] = 5000.0f * sin(angle);   // Y
	m_lightPos[2] = -1000.0f;              // Z
	m_lightPos[3] = 1.0f;                  // W (方向光)

	glLightfv(GL_LIGHT0, GL_POSITION, m_lightPos); // 更新光源位置

	// 更新模拟时间
	simulatedTime += timeSpeed;
	if (simulatedTime >= 24.0f)
	{
		simulatedTime = 0.0f; // 一天结束，重置时间
	}
	Invalidate();
}
// COpenGLView 绘图

void COpenGLView::OnDraw(CDC* pDC)
{
	COpenGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (lightingRender)
	{
		GLfloat m_lightAmb[4];    //环境光参数
		GLfloat m_lightDif[4];    //漫射光参数
		GLfloat m_lightSpe[4];    //镜面反射光参数
		GLfloat m_shininess;

		m_lightAmb[0] = 5.2f;   m_lightAmb[1] = 5.2f;
		m_lightAmb[2] = 5.2f;   m_lightAmb[3] = 3.0f;

		m_lightDif[0] = 5.0f;   m_lightDif[1] = 5.0f;
		m_lightDif[2] = 5.0f;   m_lightDif[3] = 5.0f;

		m_lightSpe[0] = 1.0f;   m_lightSpe[1] = 1.0f;
		m_lightSpe[2] = 1.0f;   m_lightSpe[3] = 1.0f;
		m_shininess = 50.0;

		glLightfv(GL_LIGHT0, GL_AMBIENT, m_lightAmb);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, m_lightDif);
		glLightfv(GL_LIGHT0, GL_SPECULAR, m_lightSpe);

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		glEnable(GL_COLOR_MATERIAL); //启动颜色材质, 允许使用颜色材质
		glEnable(GL_NORMALIZE);  //法向量单位化
		glEnable(GL_POLYGON_SMOOTH);
		glShadeModel(GL_SMOOTH);

		// 更新光源位置
		//updateLighting();
	}
	else
	{
		glDisable(GL_LIGHTING);
	}

	glLoadIdentity();									// Reset The Matrix
	gluLookAt(cameraX, cameraY, cameraZ, cameraX + lookx, cameraY + looky, cameraZ + lookz, 0, 1, 0);	// This Determines Where The Camera's Position And View Is
	glEnable(GL_DEPTH_TEST);
	//RenderHeightMap(g_HeightMap);						// Render The Height Map
	RenderNewMap();

	if (textureEnable)  //是否贴图
	{
		glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
		glBindTexture(GL_TEXTURE_2D, texture[filter]);
		glEnable(GL_BLEND);  //打开混合
		LoadGLTextures();
	}
	else
	{
		glDisable(GL_TEXTURE_2D);
	}
	if (RoadEnable) {
		// 启用平滑线
		glEnable(GL_LINE_SMOOTH);
		drawRoad(g_HeightMap);
		// 禁用平滑线
		glDisable(GL_LINE_SMOOTH);
	}
	else {
		glDisable(GL_LINE_SMOOTH);
	}

	if(dij) drawPointsDijkstra(p_start, p_end);
	glFlush();
	SwapBuffers(pDC->m_hDC);
}


// COpenGLView 打印

BOOL COpenGLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void COpenGLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void COpenGLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// COpenGLView 诊断

#ifdef _DEBUG
void COpenGLView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLDoc* COpenGLView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLDoc)));
	return (COpenGLDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLView 消息处理程序


int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	HWND hWnd = this->GetSafeHwnd();
	hDC = ::GetDC(hWnd);
	if (this->SetWindowPixelFormat(hDC) == FALSE)
	{
		return 0;
	}
	if (this->CreateViewGLContext(hDC) == FALSE)
	{
		return 0;
	}


	return 0;
}


bool COpenGLView::SetWindowPixelFormat(HDC hDC)
{
	// TODO: 在此处添加实现代码.
	PIXELFORMATDESCRIPTOR pixelDesc =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER | PFD_SUPPORT_GDI,
		PFD_TYPE_RGBA,
		24,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	this->m_GLPixelIndex = ChoosePixelFormat(hDC, &pixelDesc);
	if (this->m_GLPixelIndex == 0)
	{
		this->m_GLPixelIndex = 1;
		if (DescribePixelFormat(hDC, this->m_GLPixelIndex, sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc) == 0)
		{
			return FALSE;
		}
	}

	if (SetPixelFormat(hDC, this->m_GLPixelIndex, &pixelDesc) == FALSE)
	{
		return FALSE;
	}
	return TRUE;
}


bool COpenGLView::CreateViewGLContext(HDC hDC)
{
	// TODO: 在此处添加实现代码.
	this->m_hGLContext = wglCreateContext(hDC);
	if (this->m_hGLContext == NULL)
	{//创建失败
		return FALSE;
	}

	if (wglMakeCurrent(hDC, this->m_hGLContext) == FALSE)
	{//选为当前RC失败
		return FALSE;
	}

	return TRUE;
}


void COpenGLView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	if (wglGetCurrentContext() != NULL)
	{
		wglMakeCurrent(NULL, NULL);
	}
	if (this->m_hGLContext != NULL)
	{
		wglDeleteContext(this->m_hGLContext);
		this->m_hGLContext = NULL;
	}
}


void COpenGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	GLsizei width, height;
	width = cx;
	height = cy;
	if (cy == 0)
	{
		aspect = (GLdouble)width;
	}
	else
	{
		aspect = (GLdouble)width / (GLdouble)height;
	}
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);	//投影变换
	glLoadIdentity();
	gluPerspective(60, aspect, 0.1, 8000);	//设置视景体
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void COpenGLView::OnOpenrawfile()
{
	// TODO: 在此添加命令处理程序代码
	CString   g_app_path;
	GetModuleFileName(NULL, g_app_path.GetBuffer(MAX_PATH), MAX_PATH);
	g_app_path.ReleaseBuffer();
	int   len = g_app_path.GetLength();
	//滤去文件名称，只保留路径   
	for (int i = 0; i <= len - 1; i++)
	{
		if (g_app_path.Right(1) != "\\")
			g_app_path.Delete(len - 1 - i, 1);
		else
		{
			g_app_path.Delete(len - 1 - i, 1);
			break;
		}
	}
	CString filepath = g_app_path + "\\data\\Terrain1.raw";

	char* a = (LPSTR)(LPCTSTR)filepath;

	LoadRawFile(a, MAP_SIZE * MAP_SIZE, g_HeightMap);	// (NEW)
}


void COpenGLView::LoadRawFile(LPSTR strName, int nSize, BYTE* pHeightMap)
{
	// TODO: 在此处添加实现代码.
	FILE* pFile = NULL;

	// Open The File In Read / Binary Mode.
	pFile = fopen(strName, "rb");

	// Check To See If We Found The File And Could Open It
	if (pFile == NULL)
	{
		// Display Error Message And Stop The Function
		AfxMessageBox("Can't Find The Height Map!");
		return;
	}

	fread(pHeightMap, 1, nSize, pFile);

	// After We Read The Data, It's A Good Idea To Check If Everything Read Fine
	int result = ferror(pFile);

	// Check If We Received An Error
	if (result)
	{
		AfxMessageBox("Failed To Get Data!");
	}

	// Close The File.
	fclose(pFile);
	Invalidate();
}

void COpenGLView::RenderHeightMap(BYTE pHeightMap[])
{
	// TODO: 在此处添加实现代码.
	int X = 0, Y = 0;						// 设置循环变量
	int x, y, z;
	int x1, y1, z1;
	int x2, y2, z2;
	if (!pHeightMap) return;					// 确认高度图存在

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	for (X = 0; X < MAP_SIZE; X += STEP_SIZE)
	{
		for (Y = 0; Y < MAP_SIZE; Y += STEP_SIZE)
		{
			if (faceRender)						// 选择渲染模式
				glBegin(GL_TRIANGLES);		// 渲染为三角形
			else
				glBegin(GL_LINE_LOOP);		// 渲染为线框

				//求(x,z)处的顶点
			x = X * CELL_SIZE;
			y = Height(pHeightMap, X, Y) * CELL_SIZE;
			z = Y * CELL_SIZE;
			//求(x,z+1)处的顶点
			x1 = X * CELL_SIZE;
			y1 = Height(pHeightMap, X, Y + STEP_SIZE) * CELL_SIZE;
			z1 = (Y + STEP_SIZE) * CELL_SIZE;
			//求(x+1,z+1)处的顶点
			x2 = (X + STEP_SIZE) * CELL_SIZE;
			y2 = Height(pHeightMap, X + STEP_SIZE, Y + STEP_SIZE) * CELL_SIZE;
			z2 = (Y + STEP_SIZE) * CELL_SIZE;

			SetNormal(x, y, z, x1, y1, z1, x2, y2, z2);
			// 设置顶点颜色
			SetVertexColor(x, y / CELL_SIZE, z);
			glVertex3i(x, y, z);
			SetVertexColor(x1, y1 / CELL_SIZE, z1);
			glVertex3i(x1, y1, z1);
			SetVertexColor(x2, y2 / CELL_SIZE, z2);
			glVertex3i(x2, y2, z2);
			glEnd();

			if (faceRender)						// 选择渲染模式
				glBegin(GL_TRIANGLES);		// 渲染为三角形
			else
				glBegin(GL_LINE_LOOP);		// 渲染为直线
				//求(x,z)处的顶点
			x = X * CELL_SIZE;
			y = Height(pHeightMap, X, Y) * CELL_SIZE;
			z = Y * CELL_SIZE;

			//求(x+1,z+1)处的顶点
			x1 = (X + STEP_SIZE) * CELL_SIZE;
			y1 = Height(pHeightMap, X + STEP_SIZE, Y + STEP_SIZE) * CELL_SIZE;
			z1 = (Y + STEP_SIZE) * CELL_SIZE;

			//求(x+1,z)处的顶点
			x2 = (X + STEP_SIZE) * CELL_SIZE;
			y2 = Height(pHeightMap, X + STEP_SIZE, Y) * CELL_SIZE;
			z2 = Y * CELL_SIZE;

			SetNormal(x, y, z, x1, y1, z1, x2, y2, z2);
			SetVertexColor(x, y / CELL_SIZE, z);
			glVertex3i(x, y, z);
			SetVertexColor(x1, y1 / CELL_SIZE, z1);
			glVertex3i(x1, y1, z1);
			SetVertexColor(x2, y2 / CELL_SIZE, z2);
			glVertex3i(x2, y2, z2);
			glEnd();
		}
	}
}
void COpenGLView::RenderNewMap() {
	int X, Y;
	int x, y, z, x1, y1, z1, x2, y2, z2;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	int row = DemStruct.row;   //DEM行数
	int col = DemStruct.col;   //DEM列数
	float stepX = DemStruct.xStep;   //x方向间隔
	float stepY = DemStruct.yStep;   //y方向间隔
	int scale = DemStruct.scale;   //z放大倍数
	float CX = 1 / (row * stepX);
	float CY = 1 / (col * stepY);

	for (X = 0; X < row - 1; X++)
	{
		for (Y = 0; Y < col - 1; Y++)
		{
			if (faceRender)// 选择渲染模式
				glBegin(GL_TRIANGLES);// 渲染为三角形
			else
				glBegin(GL_LINE_LOOP);// 渲染为直线

			//求(x,z)处的顶点
			x = X * stepX;
			y = m_height[X][Y] / scale;
			z = Y * stepY;

			//求(x,z+1)处的顶点
			x1 = X * stepX;
			y1 = m_height[X][Y + 1] / scale;
			z1 = (Y + 1) * stepY;

			//求(x+1,z+1)处的顶点
			x2 = (X + 1) * stepX;
			y2 = m_height[X + 1][Y + 1] / scale;
			z2 = (Y + 1) * stepY;

			SetNormal(x, y, z, x1, y1, z1, x2, y2, z2);
			SetVertexColor(x, y / CELL_SIZE, z);
			glTexCoord2f(x * CX, z * CY);
			glVertex3i(x, y, z);
			SetVertexColor(x1, y1 / CELL_SIZE, z1);
			glTexCoord2f(x1 * CX, z1 * CY);
			glVertex3i(x1, y1, z1);
			SetVertexColor(x2, y2 / CELL_SIZE, z2);
			glTexCoord2f(x2 * CX, z2 * CY);
			glVertex3i(x2, y2, z2);

			if (faceRender)// 选择渲染模式
				glBegin(GL_TRIANGLES);// 渲染为三角形
			else
				glBegin(GL_LINE_LOOP);// 渲染为直线

			//求(x,z)处的顶点
			x = X * stepX;
			y = m_height[X][Y] / scale;
			z = Y * stepY;

			//求(x+1,z+1)处的顶点
			x1 = (X + 1) * stepX;
			y1 = m_height[X + 1][Y + 1] / scale;
			z1 = (Y + 1) * stepY;

			//求(x+1,z)处的顶点
			x2 = (X + 1) * stepX;
			y2 = m_height[X + 1][Y] / scale;
			z2 = Y * stepY;

			SetNormal(x, y, z, x1, y1, z1, x2, y2, z2);
			SetVertexColor(x, y / CELL_SIZE, z);
			glTexCoord2f(x * CX, z * CY);
			glVertex3i(x, y, z);
			SetVertexColor(x1, y1 / CELL_SIZE, z1);
			glTexCoord2f(x1 * CX, z1 * CY);
			glVertex3i(x1, y1, z1);
			SetVertexColor(x2, y2 / CELL_SIZE, z2);
			glTexCoord2f(x2 * CX, z2 * CY);
			glVertex3i(x2, y2, z2);
			glEnd();
		}
	}
}
int COpenGLView::Height(BYTE* pHeightMap, int X, int Y)
{
	// TODO: 在此处添加实现代码.
	int x = X % MAP_SIZE;
	int y = Y % MAP_SIZE;

	if (!pHeightMap) return 0;

	return pHeightMap[(y * MAP_SIZE) + x];
}


void COpenGLView::SetNormal(int x, int y, int z, int x1, int y1, int z1, int x2, int y2, int z2)
{
	// TODO: 在此处添加实现代码.
	CVector p1(x, y, z);
	CVector p2(x1, y1, z1);
	CVector p3(x2, y2, z2);
	CVector vec1 = p1 - p2;
	CVector vec2 = p3 - p2;
	CVector vNormal;
	//向量叉积公式：u × v = { u2v3-v2u3 , u3v1-v3u1 , u1v2-u2v1 }
	vNormal.x = ((vec1.y * vec2.z) - (vec1.z * vec2.y));
	vNormal.y = ((vec1.z * vec2.x) - (vec1.x * vec2.z));
	vNormal.z = ((vec1.x * vec2.y) - (vec1.y * vec2.x));
	Normalize(vNormal);
	glNormal3f(vNormal.x, vNormal.y, vNormal.z);
}


void COpenGLView::SetVertexColor(int x, int y, int z)
{
	// TODO: 在此处添加实现代码.
	float fColor = ((float)y / 255.0f);
	//if (x == 0)
	//	glColor3f(1.0, 0, 0);		//红色为X轴
	//else if (z == 0)
	//	glColor3f(1.0, 1.0, 0.0);		//黄色为Z轴
	//else
		glColor3f(fColor, fColor, fColor);
	/*
	//按高程分级设色
	if(y < 25)a
		glColor3f(0.0, 0.5, 0.0);
	else if ((y >= 25)&&(y<50))
		glColor3f(0.0, 0.6, 0.0);
	else if ((y >= 50)&&(y<75))
		glColor3f(0.0, 0.7, 0.0);
	else if ((y >= 75)&&(y<100))
		glColor3f(0.0, 0.8, 0.0);
	else
		glColor3f(fColor, fColor, fColor);
	*/



}


void COpenGLView::OnLines()
{
	// TODO: 在此添加命令处理程序代码
	faceRender = false;
	Invalidate();
}


void COpenGLView::OnTriangles()
{
	// TODO: 在此添加命令处理程序代码
	faceRender = true;
	Invalidate();
}


void COpenGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nChar == 87)							// Is the UP ARROW key Being Pressed?
	{
		cameraX = cameraX + lookx;
		cameraZ = cameraZ + lookz;
		Invalidate();
	}
	if (nChar == 83)
	{
		cameraX = cameraX - lookx;
		cameraZ = cameraZ - lookz;
		Invalidate();
	}
	if (nChar == 68) {
		cameraX = cameraX - lookz;
		cameraZ = cameraZ + lookx;
		Invalidate();
	}
	if (nChar == 65) {
		cameraX = cameraX + lookz;
		cameraZ = cameraZ - lookx;
		Invalidate();
	}
	if (nChar == 69)
	{
		float theta = 3.14159265 / 36.0;
		lookx = lookx * cos(-theta) + lookz * sin(-theta);
		lookz = -lookx * sin(-theta) + lookz * cos(-theta);
		Invalidate();
	}
	if (nChar == 81)
	{
		float theta = 3.14159265 / 36.0;
		lookx = lookx * cos(theta) + lookz * sin(theta);
		lookz = -lookx * sin(theta) + lookz * cos(theta);
		Invalidate();
	}

	if (nChar == 84)
	{
		looky = looky + 5;
		Invalidate();
	}

	if (nChar == 71)
	{
		looky = looky - 5;
		Invalidate();
	}

	if (nChar == VK_DOWN) //S键
	{
		cameraY -= 60;
		Invalidate();
	}

	if (nChar == VK_UP)//W键
	{
		cameraY += 60;
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL COpenGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (zDelta > 0)
	{
		cameraX -= lookx;
		cameraY -= looky;
		cameraZ -= lookz;

		Invalidate();
	}
	if (zDelta < 0)
	{
		cameraX += lookx;
		cameraY += looky;
		cameraZ += lookz;

		Invalidate();
	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


BOOL COpenGLView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return true;	//避免闪烁
	return CView::OnEraseBkgnd(pDC);
}


void COpenGLView::OnLighting()
{
	// TODO: 在此添加命令处理程序代码
	if (lightingRender)
	{
		lightingRender = false;
		AfxGetMainWnd()->GetMenu()->ModifyMenu(ID_LIGHTING, MF_BYCOMMAND, ID_LIGHTING, _T("打开灯光"));
	}
	else
	{
		lightingRender = true;
		AfxGetMainWnd()->GetMenu()->ModifyMenu(ID_LIGHTING, MF_BYCOMMAND, ID_LIGHTING, _T("关闭灯光"));
	}
	Invalidate();
}



void COpenGLView::OnReadDem()
{
	// TODO: 在此添加命令处理程序代码
	LPSTR filepath = "E:\\TXX\\实习相关数据代码\\DEM.txt";
	LoadDem(filepath);
}

void COpenGLView::LoadDem(LPSTR file) {
	ifstream in(file);
	in >> DemStruct.DataMark;
	in >> DemStruct.version;
	in >> DemStruct.unit;
	in >> DemStruct.x0;
	in >> DemStruct.y0;
	in >> DemStruct.x1;
	in >> DemStruct.y1;
	in >> DemStruct.xStep;
	in >> DemStruct.yStep;
	in >> DemStruct.row;
	in >> DemStruct.col;
	in >> DemStruct.scale;
	row = DemStruct.row;
	int col = DemStruct.col;
	m_height = new float* [row];
	for (int i = 0; i < row; i++) {
		m_height[i] = new float[col];
		for (int j = 0; j < col; j++) {
			in >> m_height[i][j];
		}
	}
	in.close();
	Invalidate();
}

int COpenGLView::LoadGLTextures()
{
	// TODO: 在此处添加实现代码.
	int Status = false;									// Status Indicator
	AUX_RGBImageRec* TextureImage[1];					// Create Storage Space For The Texture
	memset(TextureImage, 0, sizeof(void*) * 1);           	// Set The Pointer To NULL
	CString filepath;
	//指定bmp图像。bmp宽度最好是能被100整除，如400、600等，否则可能出现贴图错误。建议使用格式工厂对图片格式和宽度进行转换。
	filepath = "E:\\TXX\\实习相关数据代码\\RS.bmp";
	char* a = (LPSTR)(LPCTSTR)filepath;

	if (TextureImage[0] = LoadBMP(a))
	{
		Status = TRUE;									// Set The Status To TRUE

		glGenTextures(3, &texture[0]);					// Create Three Textures

		// Create Nearest Filtered Texture
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
	}

	if (TextureImage[0])								// If Texture Exists
	{
		if (TextureImage[0]->data)						// If Texture Image Exists
		{
			free(TextureImage[0]->data);				// Free The Texture Image Memory
		}

		free(TextureImage[0]);							// Free The Image Structure
	}

	return Status;										// Return The Status

}

AUX_RGBImageRec* COpenGLView::LoadBMP(char* Filename)
{
	// TODO: 在此处添加实现代码.
	FILE* File = NULL;									// File Handle

	if (!Filename)										// Make Sure A Filename Was Given
	{
		return NULL;									// If Not Return NULL
	}

	File = fopen(Filename, "r");							// Check To See If The File Exists

	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoad(Filename);				// Load The Bitmap And Return A Pointer
	}

	return NULL;										// If Load Failed Return NULL
}

void COpenGLView::OnDrawTexture()
{
	// TODO: 在此添加命令处理程序代码
	textureEnable = true;
	Invalidate();
}





void COpenGLView::OnDrawRoad()
{
	// TODO: 在此添加命令处理程序代码
	RoadEnable = true;
	readRoadData("E:\\TXX\\实习相关数据代码\\road.txt");
	Invalidate();
}


void COpenGLView::readRoadData(LPSTR strName)
{
	// TODO: 在此处添加实现代码.
	ifstream in(strName);
	in >> Road.vexnum;//读入点数
	in >> Road.arcnum;//边数
	int vex = Road.vexnum;
	int arc = Road.arcnum;
	for (int i = 0; i < vex; i++)//存入顶点值x，y，z
	{
		in >> Road.vexs[i].name;
		in >> Road.vexs[i].x >> Road.vexs[i].y >> Road.vexs[i].z;
	}
	for (int i = 0; i < vex; i++) //初始化将边的权值赋值为最大值
	{
		for (int j = 0; j <= vex; j++)
		{
			Road.arcs[i][j] = INF;
		}
	}
	int s = 0, e = 0, q = 0;
	for (int i = 0; i < arc; i++) //输入边的权值
	{
		in >> s >> e >> q;
		Road.arcs[e - 1][s - 1] = Road.arcs[s - 1][e - 1] = q;
	}
	in.close();
	Invalidate();
}

void COpenGLView::drawRoad(BYTE pRoadMap[])
{
	// TODO: 在此处添加实现代码.
	int x, y, z;

	if (!pRoadMap) return;	// 确认高度图存在

	int vexnum = Road.vexnum;
	int arcnum = Road.arcnum;
	glPointSize(10);
	glBegin(GL_POINTS);
	for (int i = 0; i < vexnum; i++) //画点
	{
		x = Road.vexs[i].x;
		y = Road.vexs[i].y;
		z = Road.vexs[i].z;
		glColor3f(1, 0.2, 0);
		glVertex3f(y, z + 10, x);
		//glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, Road.vexs[i].name);
	}
	glEnd();

	// 在点旁边绘制点的名称
	for (int i = 0; i < vexnum; i++)
	{
		x = Road.vexs[i].x;
		y = Road.vexs[i].y;
		z = Road.vexs[i].z;
		glColor3f(1, 1, 0); // 设置字体颜色
		glRasterPos3f(y, z + 10, x); // 设置文本位置

		const char* name = Road.vexs[i].name.c_str(); // 转换 string 为 const char*
		for (const char* c = name; *c != '\0'; c++)
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c); // 使用 GLUT 绘制字符
		}
	}

	for (int i = 0; i < vexnum; i++)  //绘制路线（边） 
	{
		for (int j = 0; j < vexnum; j++)
		{
			if (Road.arcs[i][j] == INF);//只要边的权值不是最大值就画，人话：两边有链接就画图
			else
			{
				glLineWidth(5);
				glColor3f(1, 0, 0.3); //修改线段颜色
				glBegin(GL_LINES);
				glVertex3f(Road.vexs[i].y, Road.vexs[i].z + 10, Road.vexs[i].x);
				glVertex3f(Road.vexs[j].y, Road.vexs[j].z + 10, Road.vexs[j].x);
				glEnd();
			}
		}
	}
}


void COpenGLView::OnDijkstra()
{}

void COpenGLView::drawPointsDijkstra(int start, int end) //dijkstra算法+绘图，传入start 和 end 两个参数
{
	bool S[MAXN];
	int D[MAXN], i, min, j, w, k, m;
	int path[MAXN];
	for (i = 0; i < Road.vexnum; i++)
	{
		S[i] = false;
		D[i] = Road.arcs[start][i];
	}
	S[start] = true;
	D[start] = 0;
	for (i = 0; i < Road.vexnum; i++)
		if (D[i] == INF)path[i] = -1;
		else path[i] = start;
	for (i = 1; i < Road.vexnum; i++)
	{
		min = INF;
		for (j = 0; j < Road.vexnum; j++)
			if (!S[j] && D[j] < min)
			{
				min = D[j];
				k = j;
			}
		S[k] = true;
		for (w = 0; w < Road.vexnum; w++)
			if (!S[w] && D[k] + Road.arcs[k][w] < D[w])
			{
				D[w] = min + Road.arcs[k][w];
				path[w] = k;
			}
	}
	int f = end;
	while (f != start && f != -1) //绘图部分，主要利用遍历path数组（存储直接前驱结点）的思想挨个找点
	{
		glLineWidth(6);
		glColor3f(1, 1, 0);
		glBegin(GL_LINES);
		glVertex3f(Road.vexs[f].y, Road.vexs[f].z + 13, Road.vexs[f].x);
		glVertex3f(Road.vexs[path[f]].y, Road.vexs[path[f]].z + 13, Road.vexs[path[f]].x);
		f = path[f];
		glEnd();
	}
}

void COpenGLView::OnDij()
{
	// TODO: 在此添加命令处理程序代码
	DlgInpputPath Dlg;
	if (RoadEnable == false) MessageBox(_T("未读入路网！"));
	else
	{
		if (Dlg.DoModal() == IDOK)
		{
			p_start = Dlg.m_start - 1;
			p_end = Dlg.m_end - 1;
			dij = true;
			Invalidate();
		}
	}
}


void COpenGLView::OnPic()
{
	// TODO: 在此添加命令处理程序代码
	DlgPic Dlg;
	int x = 0, y = 0;
	if (RoadEnable == false) MessageBox(_T("未读入路网！"));
	else
	{
		if (Dlg.DoModal() == IDOK)
		{
			/*Dlg.SetStartEnd(p_start, p_end);*/
			p_start = Dlg.m_x - 1;
			p_end = Dlg.m_y - 1;
			dij = true;
			Invalidate();
		}
	}
}


void COpenGLView::OnTestTest()
{
	// TODO: 在此添加命令处理程序代码
	test Dlg;
	int x = 0;
	if (Dlg.DoModal() == IDOK)
	{
		/*Dlg.SetStartEnd(p_start, p_end);*/
		x = Dlg.a;
	}
}
