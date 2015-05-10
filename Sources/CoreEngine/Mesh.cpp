
#include "Mesh.h"
#include "Utils.h"

Mesh::Mesh(const Mesh& other)
{

	setSubMeshCount(other.getSubMeshCount());

	for (int i = 0; i < getSubMeshCount(); i++)
	{
		setVertices(other.getVertices(i));
		setNormals(other.getNormals(i));
		setUVs(other.getUVs(i));
		setIndices(other.getIndices(i));
	}
}

Mesh::Mesh()
{
	std::cout << "Mesh created" << std::endl;
}

Mesh::~Mesh()
{
	for (int i = 0; i < getSubMeshCount(); i++)
		deleteAllBuffers(i);

	std::cout << "~~~~Mesh" << std::endl;
}

void Mesh::genBuffers(int submesh)
{
	if (isVBOSupported())
	{
		//TODO implement functionality which can choose best memory type based on vbo change frequency

		GLuint& vbo_id_n = submeshes_[submesh]->normal_buffer_id;
		GLuint& vbo_id_t = submeshes_[submesh]->uv_buffer_id;
		GLuint& vbo_id_v = submeshes_[submesh]->vertex_buffer_id;
		GLuint& vbo_id_i = submeshes_[submesh]->index_buffer_id;

		std::vector<Vector3>& vertices = submeshes_[submesh]->vertices;
		std::vector<Vector2>& uvs = submeshes_[submesh]->uvs;
		std::vector<Vector3>& normals = submeshes_[submesh]->normals;
		std::vector<unsigned int>& indices = submeshes_[submesh]->indices;

		//NORMALS
		if (submeshes_[submesh]->_updateNormals && submeshes_[submesh]->normals.size() > 0)
		{
			printf("UPDATING NORMALS\n");
			if (vbo_id_n == 0)
			{
				glGenBuffers(1, &vbo_id_n);
				glBindBuffer(GL_ARRAY_BUFFER, vbo_id_n);
				glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(Vector3), &normals[0], vboUsage_);
			}
			else
			{
				glBindBuffer(GL_ARRAY_BUFFER, vbo_id_n);
				glBufferSubData(GL_ARRAY_BUFFER, 0, normals.size() * sizeof(Vector3), &normals[0]);
			}

			normals.clear();
			submeshes_[submesh]->_updateNormals = false;
		}

		// TEX COORDS
		if (submeshes_[submesh]->_updateTexCoords && submeshes_[submesh]->uvs.size() > 0)
		{
			printf("UPDATING UVS\n");
			if (vbo_id_t == 0)
			{
				glGenBuffers(1, &vbo_id_t);
				glBindBuffer(GL_ARRAY_BUFFER, vbo_id_t);
				glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(Vector2), &uvs[0], vboUsage_);
			}
			else
			{
				glBindBuffer(GL_ARRAY_BUFFER, vbo_id_t);
				glBufferSubData(GL_ARRAY_BUFFER, 0, uvs.size() * sizeof(Vector2), &uvs[0]);
			}

			uvs.clear();
			submeshes_[submesh]->_updateTexCoords = false;
		}

		//VERTICES
		if (submeshes_[submesh]->_updateVertices && submeshes_[submesh]->indices.size() > 0)
		{
			printf("UPDATING VERTICES\n");
			if (vbo_id_v == 0)
			{
				glGenBuffers(1, &vbo_id_v);
				glBindBuffer(GL_ARRAY_BUFFER, vbo_id_v);
				glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vector3), &vertices[0], vboUsage_);
			}
			else
			{
				glBindBuffer(GL_ARRAY_BUFFER, vbo_id_v);
				glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vector3), &vertices[0]);
			}

			vertices.clear();
			submeshes_[submesh]->_updateVertices = false;
		}

		//INDICES
		if (submeshes_[submesh]->_updateIndices && submeshes_[submesh]->indices.size() > 0)
		{
			printf("UPDATING INDICES\n");
			if (vbo_id_i == 0)
			{
				glGenBuffers(1, &vbo_id_i);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_id_i);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], vboUsage_);
			}
			else
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_id_i);
				glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned int), &indices[0]);
			}

			indices.clear();
			submeshes_[submesh]->_updateIndices = false;
		}
	}
}

void Mesh::deleteAllBuffers(int submesh)
{
	if (isVBOSupported())
	{
		GLuint& vbo_id_n = submeshes_[submesh]->normal_buffer_id;
		GLuint& vbo_id_t =     submeshes_[submesh]->uv_buffer_id;
		GLuint& vbo_id_v = submeshes_[submesh]->vertex_buffer_id;
		GLuint& vbo_id_i =  submeshes_[submesh]->index_buffer_id;

		if (vbo_id_n > 0){glDeleteBuffers(1, &vbo_id_n);vbo_id_n = 0;}
		if (vbo_id_t > 0){glDeleteBuffers(1, &vbo_id_t);vbo_id_t = 0;}
		if (vbo_id_v > 0){glDeleteBuffers(1, &vbo_id_v);vbo_id_v = 0;}
		if (vbo_id_i > 0){glDeleteBuffers(1, &vbo_id_i);vbo_id_i = 0;}
	}
}

void Mesh::draw(int submesh)
{	
	//TEMP read fields from material;
	GLuint vertexAttrib = 0;
	GLuint texCoordAttrib = 1;
	GLuint normalAttrib = 2;

	GLuint vertex_count = submeshes_[submesh]->vertex_count;
	GLuint uv_count = submeshes_[submesh]->uv_count;
	GLuint normal_count = submeshes_[submesh]->normal_count;
	GLuint index_count = submeshes_[submesh]->index_count;

	if (vertex_count > 0)	glEnableVertexAttribArray(vertexAttrib);
	if (uv_count > 0)		glEnableVertexAttribArray(texCoordAttrib);
	if (normal_count > 0)	glEnableVertexAttribArray(normalAttrib);

	//if hardware supports VBOs
	if (isVBOSupported())
	{
		//std::cout << "***Draw using VBO***" << std::endl;

		if (submeshes_[submesh]->_updateVBO())
			genBuffers(submesh);

		if (vertex_count > 0 && index_count > 0)
		{
			if (uv_count > 0)
			{
				//std::cout << "BIND TEXCOORD BUFFER: " << _submeshes[submesh]->uv_count << std::endl;
				glBindBuffer(GL_ARRAY_BUFFER, submeshes_[submesh]->uv_buffer_id);
				glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, false, 0, 0);
			}

			if (normal_count > 0)
			{
				//std::cout << "BIND NORMAL BUFFER: " << _submeshes[submesh]->normal_count << std::endl;
				glBindBuffer(GL_ARRAY_BUFFER, submeshes_[submesh]->normal_buffer_id);
				glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, false, 0, 0);
			}

			//std::cout << "BIND VERTEX BUFFER: " << _submeshes[submesh]->vertex_count << std::endl;
			glBindBuffer(GL_ARRAY_BUFFER, submeshes_[submesh]->vertex_buffer_id);
			glVertexAttribPointer(vertexAttrib, 3, GL_FLOAT, false, 0, 0);

			//std::cout << "BIND INDEX BUFFER: " << _submeshes[submesh]->index_count << std::endl;
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, submeshes_[submesh]->index_buffer_id);
			glDrawElements(GL_TRIANGLES, submeshes_[submesh]->index_count, GL_UNSIGNED_INT, 0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
	else
	{
		std::cout << "***Draw using VERTEX ARRAYS***" << std::endl;

		std::vector<Vector3>& vertices = submeshes_[submesh]->vertices;
		std::vector<Vector2>& uvs = submeshes_[submesh]->uvs;
		std::vector<Vector3>& normals = submeshes_[submesh]->normals;
		std::vector<unsigned int>& indices = submeshes_[submesh]->indices;

		if (vertex_count > 0 && index_count > 0)
		{
			if (uv_count > 0)		glVertexAttribPointer(texCoordAttrib, 2, GL_FLOAT, false, 0, &uvs[0]);
			if (normal_count > 0)	glVertexAttribPointer(normalAttrib, 3, GL_FLOAT, false, 0, &normals[0]);

			glVertexAttribPointer(vertexAttrib, 3, GL_FLOAT, false, 0, &vertices[0]);
			glDrawElements(GL_TRIANGLES, submeshes_[submesh]->index_count, GL_UNSIGNED_INT, &indices[0]);
		}
	}

	if (vertex_count)		glDisableVertexAttribArray(vertexAttrib);
	if (uv_count)		glDisableVertexAttribArray(texCoordAttrib);
	if (normal_count)	glDisableVertexAttribArray(normalAttrib);
}

std::vector<Vector3> Mesh::getVertices(int submesh) const
{
	if (submesh >= (int)submeshes_.size())
	{
		printf("There is no submesh at index %d\n", submesh);
		return std::vector<Vector3>();
	}

	smart_pointer<SubMesh> subMesh = submeshes_[submesh];

	if (isVBOSupported())
	{
		std::vector<Vector3> data(subMesh->vertex_count);
		glBindBuffer(GL_ARRAY_BUFFER, subMesh->vertex_buffer_id);

// 		glGetVertexAttribPointerv(0, GL_VERTEX_ATTRIB_ARRAY_POINTER, );
// 		std::cout << "DOUBLE POINTER " << data.size() << std::endl;
		
	//	glGetBufferSubData(GL_ARRAY_BUFFER, 0, data.size()*sizeof(Vector3), data.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);


		return data;
	}
	else
	{
		return subMesh->vertices;
	}
}

std::vector<Vector2> Mesh::getUVs(int submesh) const
{
	if (submesh >= (int)submeshes_.size())
	{
		printf("There is no submesh at index %d\n", submesh);
		return std::vector<Vector2>();
	}

	smart_pointer<SubMesh> subMesh = submeshes_[submesh];

	if (isVBOSupported())
	{
		std::vector<Vector2> data(subMesh->uv_count);
		glBindBuffer(GL_ARRAY_BUFFER, subMesh->uv_buffer_id);
		//glGetBufferSubData(GL_ARRAY_BUFFER, 0, data.size()*sizeof(Vector2), data.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return data;
	}
	else
	{
		return subMesh->uvs;
	}
}

std::vector<Vector3> Mesh::getNormals(int submesh) const
{
	if (submesh >= (int)submeshes_.size())
	{
		printf("There is no submesh at index %d\n", submesh);
		return std::vector<Vector3>();
	}

	smart_pointer<SubMesh> subMesh = submeshes_[submesh];

	if (isVBOSupported())
	{
		std::vector<Vector3> data(subMesh->normal_count);
		glBindBuffer(GL_ARRAY_BUFFER, subMesh->normal_buffer_id);
		//glGetBufferSubData(GL_ARRAY_BUFFER, 0, data.size()*sizeof(Vector3), data.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		return data;
	}
	else
	{
		return subMesh->normals;
	}
}

std::vector<unsigned int> Mesh::getIndices(int submesh)const
{
	if (submesh >= (int)submeshes_.size())
	{
		printf("There is no submesh at index %d\n", submesh);
		return std::vector<unsigned int>();
	}

	smart_pointer<SubMesh> subMesh = submeshes_[submesh];

	if (isVBOSupported())
	{
		std::vector<unsigned int> data(subMesh->index_count);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, subMesh->index_buffer_id);
		//glGetBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, data.size()*sizeof(unsigned int), data.data());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		return data;
	}
	else
	{
		return subMesh->indices;
	}
}

void Mesh::setVertices(std::vector<Vector3> vertices, int submesh)
{
	if (submesh >= (int)submeshes_.size())
	{
		printf("There is no submesh at index %d\n", submesh);
		return;
	}

	if (submeshes_[submesh]->vertex_buffer_id != 0 && submeshes_[submesh]->vertices.size() != vertices.size())
	{
		glDeleteBuffers(1, &submeshes_[submesh]->vertex_buffer_id);
		submeshes_[submesh]->vertex_buffer_id = 0;
	}

	submeshes_[submesh]->_updateVertices = true;
	submeshes_[submesh]->vertices = vertices;
	submeshes_[submesh]->vertex_count = vertices.size();
}

void Mesh::setUVs(std::vector<Vector2> uvs, int submesh)
{
	if (submesh >= (int)submeshes_.size())
	{
		printf("There is no submesh at index %d\n", submesh);
		return;
	}

	if (submeshes_[submesh]->uv_buffer_id != 0 && submeshes_[submesh]->uvs.size() != uvs.size())
	{
		glDeleteBuffers(1, &submeshes_[submesh]->uv_buffer_id);
		submeshes_[submesh]->uv_buffer_id = 0;
	}

	submeshes_[submesh]->_updateTexCoords = true;
	submeshes_[submesh]->uvs = uvs;
	submeshes_[submesh]->uv_count = uvs.size();
}

void Mesh::setNormals(std::vector<Vector3> normals, int submesh)
{
	if (submesh >= (int)submeshes_.size())
	{
		printf("There is no submesh at index %d\n", submesh);
		return;

	}
	if (submeshes_[submesh]->normal_buffer_id != 0 && submeshes_[submesh]->normals.size() != normals.size())
	{
		glDeleteBuffers(1, &submeshes_[submesh]->normal_buffer_id);
		submeshes_[submesh]->normal_buffer_id = 0;
	}

	submeshes_[submesh]->_updateNormals = true;
	submeshes_[submesh]->normals = normals;
	submeshes_[submesh]->normal_count = normals.size();
}

void Mesh::setIndices(std::vector<unsigned int> indices, int submesh)
{
	if (submesh >= (int)submeshes_.size())
	{
		printf("There is no submesh at index %d\n", submesh);
		return;
	}

	if (submeshes_[submesh]->index_buffer_id != 0 && submeshes_[submesh]->indices.size() != indices.size())
	{
		glDeleteBuffers(1, &submeshes_[submesh]->index_buffer_id);
		submeshes_[submesh]->index_buffer_id = 0;
	}

	submeshes_[submesh]->_updateIndices = true;
	submeshes_[submesh]->indices = indices;
	submeshes_[submesh]->index_count = indices.size();
}

void Mesh::clear()
{
	for (int i = 0; i < (int)submeshes_.size(); i++)
	{
		smart_pointer<SubMesh>& m = submeshes_[i];

		deleteAllBuffers(i);
		m->vertices.clear(); m->vertex_count = 0;
		m->uvs.clear(); m->uv_count = 0;
		m->normals.clear(); m->normal_count = 0;
		m->indices.clear(); m->index_count = 0;
	}
}