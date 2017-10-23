#include "CircleMeshVbo.h"
#define PI 3.14f

void CircleMeshVbo::loadData()
{
	//VBO data
	GLfloat vertexData[724];
	vertexData[0] = 0.0f;
	vertexData[1] = 0.0f;
	for (int i = 0; i < 360; i++)
	{
		vertexData[(2 * i) + 2] = cosf(PI*(i + 1) / 180.0f);
		vertexData[(2 * i) + 3] = sinf(PI*(i + 1) / 180.0f);
	}
	vertexData[722] = cosf(PI / 180.0f);
	vertexData[723] = sinf(PI / 180.0f);

	GLfloat colorData[1086];
		for (int i = 0; i < 362; i++) {

			colorData[(3 * i)] = 0.5f;
			colorData[(3 * i) + 1] = 0.5f;
			colorData[(3 * i) + 2] = 0.0f;
			
		}

	//Create VBO
	glGenBuffers(1, &(this->posVboId));
	glBindBuffer(GL_ARRAY_BUFFER, this->posVboId);
	glBufferData(GL_ARRAY_BUFFER, 2 * 362 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

	glGenBuffers(1, &(this->colorVboId));
	glBindBuffer(GL_ARRAY_BUFFER, this->colorVboId);
	glBufferData(GL_ARRAY_BUFFER, 3 * 362 * sizeof(GLfloat), colorData, GL_STATIC_DRAW);


}

CircleMeshVbo::CircleMeshVbo()
{
}

string CircleMeshVbo::getMeshName()
{
	return "Circle";
}

void CircleMeshVbo::render()
{
	if (this->posAttribId != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, this->posVboId);
		glVertexAttribPointer(this->posAttribId, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	}
	if (this->colorAttribId != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, this->colorVboId);
		glVertexAttribPointer(this->colorAttribId, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
	}
	glDrawArrays(GL_TRIANGLE_FAN, 0, 362);
}

void CircleMeshVbo::gridRender() {
	if (this->posAttribId != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, this->posVboId);
		glVertexAttribPointer(this->posAttribId, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	}

	if (this->colorAttribId != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, this->colorVboId);
		glVertexAttribPointer(this->colorAttribId, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
	}

	glDrawArrays(GL_LINE_LOOP, 1, 360);
}
