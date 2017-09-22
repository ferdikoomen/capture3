#ifndef CAPTURE3_RENDER_COMPONENT_H
#define CAPTURE3_RENDER_COMPONENT_H


#include <cmath>
#include <QtWidgets/QWidget>
#include <QtWidgets/QOpenGLWidget>
#include <QtGui/QOpenGLBuffer>
#include <QtGui/QOpenGLVertexArrayObject>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QMatrix4x4>
#include <QtGui/QScreen>
#include <QtGui/QKeyEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>
#include <QtGui/QResizeEvent>
#include <QtCore/QTime>
#include <QtCore/QFile>


#include "../../../constants/ResourceConstants.h"


namespace Capture3
{
	class RenderComponent : public QOpenGLWidget
	{
		Q_OBJECT

		public:
			RenderComponent(
				const unsigned int width,
				const unsigned int height
			);

			virtual ~RenderComponent();

			virtual int heightForWidth(int width) const;

			virtual QSize sizeHint() const;

			void setData(
				const std::vector<float> &positions,
				const std::vector<float> &colors,
				const unsigned int countPoints = 0,
				const unsigned int countLines = 0,
				const unsigned int countTriangles = 0,
				const unsigned int offsetPoints = 0,
				const unsigned int offsetLines = 0,
				const unsigned int offsetTriangles = 0
			);

			void setPointSize(const float value);

			void setLineSize(const float value);

			void reset();

		protected:
			virtual void initializeGL();

			virtual void resizeGL(int width, int height);

			virtual void paintGL();

			virtual void mousePressEvent(QMouseEvent *event);

			virtual void mouseReleaseEvent(QMouseEvent *event);

			virtual void mouseMoveEvent(QMouseEvent *event);

			virtual void wheelEvent(QWheelEvent *event);

		private:
			void createBuffers();

			void updateCamera();

			QOpenGLShaderProgram program;
			QOpenGLShader *vertextShader;
			QOpenGLShader *fragmentShader;
			QFile vertextShaderFile;
			QFile fragmentShaderFile;
			QMatrix4x4 cameraMatrix;
			QMatrix4x4 worldMatrix;
			QMatrix4x4 projectionMatrix;
			QMatrix4x4 matrix;
			const float *dataPositions;
			const float *dataColors;
			unsigned int dataCount;
			unsigned int dataCountPoints;
			unsigned int dataCountLines;
			unsigned int dataCountTriangles;
			unsigned int dataOffsetPoints;
			unsigned int dataOffsetLines;
			unsigned int dataOffsetTriangles;
			QOpenGLVertexArrayObject vao;
			QOpenGLBuffer vboPositions;
			QOpenGLBuffer vboColors;
			const float background;
			bool invalidated;
			int attrPosition;
			int attrColor;
			int attrMatrix;
			double cameraAlpha;
			double cameraBeta;
			double cameraRadius;
			double cameraX;
			double cameraY;
			double cameraZ;
			const double ratio;
			int viewportWidth;
			int viewportHeight;
			bool mouseLeftDown;
			bool mouseRightDown;
			int mousePosX;
			int mousePosY;
			float pointSize;
			float lineSize;
	};
}

#endif // CAPTURE3_RENDER_COMPONENT_H
