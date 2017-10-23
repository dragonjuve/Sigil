#include "MapMeshVbo.h"

void MapMeshVbo::loadData()
{
	//VBO data
	GLfloat vertexData[] =
	{
		-0.5f, -0.5f,
		0.5f, -0.5f,
		0.5f,  0.5f,
		-0.5f,  0.5f
	};

	GLfloat textureData[] =
	{
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f,  1.0f,
		0.0f,  1.0f
	};

	//Create VBO
	glGenBuffers(1, &(this->posVboId));
	glBindBuffer(GL_ARRAY_BUFFER, this->posVboId);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

	//Create VBO
	glGenBuffers(1, &(this->textureId));
	glBindBuffer(GL_ARRAY_BUFFER, this->textureId);
	glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), textureData, GL_STATIC_DRAW);

}

MapMeshVbo::MapMeshVbo():MapMeshVbo(5,5)
{
}

MapMeshVbo::MapMeshVbo(int sizeRow,int sizeCol)
{
	this->color = new glm::vec4*[sizeRow];
	for (int i = 0; i < sizeRow; i++)
	{
		this->color[i] = new glm::vec4[sizeCol];
		for (int j = 0; j < sizeCol; j++)
		{
			this->color[i][j] = glm::vec4(0.4f, 0.4f, 0.4f,-1.0f);
		}
	}
}

string MapMeshVbo::getMeshName()
{
	return "Map";
}

void MapMeshVbo::render()
{
	if (this->posAttribId != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, this->posVboId);
		glVertexAttribPointer(this->posAttribId, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

		glBindBuffer(GL_ARRAY_BUFFER, this->textureId);
		glVertexAttribPointer(this->textureAttribId, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	}
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
void MapMeshVbo::gridRender()
{
	if (this->posAttribId != -1) {
		glBindBuffer(GL_ARRAY_BUFFER, this->posVboId);
		glVertexAttribPointer(this->posAttribId, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
	}
	glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void MapMeshVbo::setColor(int x, int y, glm::vec3 color)
{
	this->color[x][y] = glm::vec4(color,-1.0f);
}

void MapMeshVbo::setTexture(int x, int y, GLuint textureId)
{
	this->color[x][y].w = textureId;
}

void MapMeshVbo::setAttribId(GLuint posId, GLuint textureId)
{
	this->posAttribId = posId;
	this->textureAttribId = textureId;
}