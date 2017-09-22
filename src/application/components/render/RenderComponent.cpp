#include "RenderComponent.h"


namespace Capture3
{

	RenderComponent::RenderComponent(
		const unsigned int width,
		const unsigned int height
	) :
		QOpenGLWidget(),

		// OpenGL program
		program(),

		// Matrix
		cameraMatrix(),
		worldMatrix(),
		projectionMatrix(),

		// Data
		dataPositions(nullptr),
		dataColors(nullptr),
		dataCount(0),
		dataCountPoints(0),
		dataCountLines(0),
		dataCountTriangles(0),
		dataOffsetPoints(0),
		dataOffsetLines(0),
		dataOffsetTriangles(0),
		vao(),
		vboPositions(QOpenGLBuffer::VertexBuffer),
		vboColors(QOpenGLBuffer::VertexBuffer),
		background(40.0f / 255.0f),

		// Shader files
		vertextShaderFile(FILE_SHADER_VERTEX),
		fragmentShaderFile(FILE_SHADER_FRAGMENT),

		// Camera properties
		cameraAlpha(150),
		cameraBeta(225),
		cameraRadius(2.5),
		cameraX(1.3),
		cameraY(1.3),
		cameraZ(1.3),
		mouseLeftDown(false),
		mouseRightDown(false),
		mousePosX(0),
		mousePosY(0),

		// Point and line size
		pointSize(2.0f),
		lineSize(2.0f),

		// View properties
		ratio((double) width / (double) height),
		viewportWidth(0),
		viewportHeight(0),

		// Initialized
		invalidated(false)
	{
		// Setup for aspect ratio scaling
		setFocusPolicy(Qt::NoFocus);
		QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		sizePolicy.setHeightForWidth(true);
		setSizePolicy(sizePolicy);
		setMinimumSize(1, 1);

		// Set projection matrix
		projectionMatrix.setToIdentity();
		projectionMatrix.perspective(45.0f, (float) ratio, 0.01f, 100.0f);
		cameraMatrix.setToIdentity();
		cameraMatrix.translate(0, 0, 0);
		updateCamera();
	}


	RenderComponent::~RenderComponent()
	{
		vboPositions.destroy();
		vboColors.destroy();
		vao.deleteLater();
		program.deleteLater();
		vertextShaderFile.deleteLater();
		fragmentShaderFile.deleteLater();
		dataPositions = nullptr;
		dataColors = nullptr;
	}


	int RenderComponent::heightForWidth(int width) const
	{
		return (int) std::round(width / ratio);
	}


	QSize RenderComponent::sizeHint() const
	{
		int w = width();
		return {w, heightForWidth(w)};
	}


	void RenderComponent::setData(
		const std::vector<float> &positions,
		const std::vector<float> &colors,
		const unsigned int countPoints,
		const unsigned int countLines,
		const unsigned int countTriangles,
		const unsigned int offsetPoints,
		const unsigned int offsetLines,
		const unsigned int offsetTriangles
	)
	{
		// Store positions and colors
		dataPositions = positions.data();
		dataColors = colors.data();
		dataCountPoints = countPoints;
		dataCountLines = countLines;
		dataCountTriangles = countTriangles;
		dataOffsetPoints = offsetPoints;
		dataOffsetLines = offsetLines;
		dataOffsetTriangles = offsetTriangles;
		dataCount = countPoints + countLines + countTriangles;
		invalidated = true;

		if (isEnabled() && isVisible()) {
			update();
		}
	}


	void RenderComponent::setPointSize(const float value)
	{
		pointSize = value;
	}


	void RenderComponent::setLineSize(const float value)
	{
		lineSize = value;
	}


	void RenderComponent::reset()
	{
		dataPositions = nullptr;
		dataColors = nullptr;
		dataCount = 0;
		dataCountPoints = 0;
		dataCountLines = 0;
		dataCountTriangles = 0;
		dataOffsetPoints = 0;
		dataOffsetLines = 0;
		dataOffsetTriangles = 0;
		invalidated = true;

		if (isEnabled() && isVisible()) {
			update();
		}
	}


	void RenderComponent::initializeGL()
	{
		// Create shaders
		vertextShaderFile.open(QFile::ReadOnly);
		fragmentShaderFile.open(QFile::ReadOnly);
		vertextShader = new QOpenGLShader(QOpenGLShader::Vertex);
		fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
		vertextShader->compileSourceCode(vertextShaderFile.readAll());
		fragmentShader->compileSourceCode(fragmentShaderFile.readAll());
		vertextShaderFile.close();
		fragmentShaderFile.close();

		// Create shader program
		program.addShader(vertextShader);
		program.addShader(fragmentShader);
		program.link();

		// Get attribute positions
		attrPosition = program.attributeLocation("vertexPosition");
		attrColor = program.attributeLocation("vertexColor");
		attrMatrix = program.uniformLocation("matrix");

		// Create buffers
		createBuffers();
	}


	void RenderComponent::createBuffers()
	{
		// Create vertex array object (needed for modern openGL)
		vao.destroy();
		vao.create();
		vao.bind();

		// Create positions buffer
		vboPositions.destroy();
		vboPositions.create();
		vboPositions.setUsagePattern(QOpenGLBuffer::StaticDraw);
		vboPositions.bind();
		if (dataPositions != nullptr) {
			vboPositions.allocate(dataPositions, dataCount * 3 * sizeof(float));
		}
		program.enableAttributeArray(attrPosition);
		program.setAttributeBuffer(attrPosition, GL_FLOAT, 0, 3);

		// Create colors buffer
		vboColors.destroy();
		vboColors.create();
		vboColors.setUsagePattern(QOpenGLBuffer::StaticDraw);
		vboColors.bind();
		if (dataColors != nullptr) {
			vboColors.allocate(dataColors, dataCount * 3 * sizeof(float));
		}
		program.enableAttributeArray(attrColor);
		program.setAttributeBuffer(attrColor, GL_FLOAT, 0, 3);

		// Release everything
		vboPositions.release();
		vboColors.release();
		vao.release();
	}


	void RenderComponent::resizeGL(int width, int height)
	{
		// Store size
		viewportWidth = width;
		viewportHeight = height;
	}


	void RenderComponent::paintGL()
	{
		// Check if we need to create new buffers
		if (invalidated) {
			invalidated = false;
			createBuffers();
		}

		// Resize viewport
		const int r = window()->devicePixelRatio();
		glViewport(0, 0, viewportWidth * r, viewportHeight * r);
		glClearColor(background, background, background, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_POINT_SIZE);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_LINE_WIDTH); // Note: Not always supported!
		glPointSize(pointSize * (float) r);
		glLineWidth(lineSize * (float) r);

		// Only bind when we have items to draw
		if (dataCount > 0) {

			// Bind all
			vao.bind();
			program.bind();

			// Update matrix
			program.setUniformValue(attrMatrix, matrix);

			// Draw points
			glDrawArrays(GL_POINTS, dataOffsetPoints, dataCountPoints);
			glDrawArrays(GL_LINES, dataOffsetLines, dataCountLines);
			glDrawArrays(GL_TRIANGLES, dataOffsetTriangles, dataCountTriangles);

			// Release all
			program.release();
			vao.release();
		}
	}


	void RenderComponent::mousePressEvent(QMouseEvent *event)
	{
		mouseLeftDown = (event->button() == Qt::LeftButton);
		mouseRightDown = (event->button() == Qt::RightButton);
		mousePosX = event->x();
		mousePosY = event->y();
		event->accept();
	}


	void RenderComponent::mouseReleaseEvent(QMouseEvent *event)
	{
		mouseLeftDown = false;
		mouseRightDown = false;
		event->accept();
	}


	void RenderComponent::mouseMoveEvent(QMouseEvent *event)
	{
		// Move camera
		if (mouseLeftDown) {
			cameraAlpha += (mousePosY - event->y());
			cameraBeta += (mousePosX - event->x());
			updateCamera();
			update();
		} else if (mouseRightDown) {
			cameraRadius -= (mousePosY - event->y()) / (50.0 / cameraRadius);
			updateCamera();
			update();
		}

		// Save mouse position
		mousePosX = event->x();
		mousePosY = event->y();
		event->accept();
	}


	void RenderComponent::wheelEvent(QWheelEvent *event)
	{
		event->ignore();
	}


	void RenderComponent::updateCamera()
	{
		// Cap camera position
		cameraAlpha = cameraAlpha < 95.0 ? 95.0 : cameraAlpha > 265.0 ? 265.0 : cameraAlpha;
		cameraRadius = cameraRadius < 0.1 ? 0.1 : cameraRadius > 10.0 ? 10.0 : cameraRadius;

		// Calculate positions based on simple orb control
		const double deg2rad = M_PI / 180.0;
		cameraX = cameraRadius * std::cos(cameraAlpha * deg2rad) * std::cos(cameraBeta * deg2rad);
		cameraY = cameraRadius * std::cos(cameraAlpha * deg2rad) * std::sin(cameraBeta * deg2rad);
		cameraZ = cameraRadius * std::sin(cameraAlpha * deg2rad);

		// Update matrix
		cameraMatrix = QMatrix4x4();
		cameraMatrix.lookAt(
			QVector3D((float) cameraX, (float) cameraY, (float) cameraZ),
			QVector3D(0.0f, 0.0f, 0.0f),
			QVector3D(0.0f, 0.0f, 1.0f)
		);

		// Calculate final matrix
		matrix = projectionMatrix * cameraMatrix * worldMatrix;
	}
}