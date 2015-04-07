
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

		GLuint& vbo_id_n = _submeshes[submesh]->normal_buffer_id;
		GLuint& vbo_id_t = _submeshes[submesh]->uv_buffer_id;
		GLuint& vbo_id_v = _submeshes[submesh]->vertex_buffer_id;
		GLuint& vbo_id_i = _submeshes[submesh]->index_buffer_id;

		std::vector<Vector3>& vertices = _submeshes[submesh]->vertices;
		std::vector<Vector2>& uvs = _submeshes[submesh]->uvs;
		std::vector<Vector3>& normals = _submeshes[submesh]->normals;
		std::vector<unsigned int>& indices = _submeshes[submesh]->indices;

		if (indices.size() > 0 && vertices.size() > 0)
		{
			//NORMALS
			if (_submeshes[submesh]->normals.size() > 0)
			{
				if (vbo_id_n == 0)
				{
					glGenBuffersARB(1, &vbo_id_n);
					glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo_id_n);
					glBufferDataARB(GL_ARRAY_BUFFER_ARB, normals.size() * sizeof(Vector3), &normals[0], _vboUsage);
				}
				else if (_submeshes[submesh]->_updateNormals)
				{
					glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo_id_n);
					glBufferSubData(GL_ARRAY_BUFFER_ARB, 0, normals.size() * sizeof(Vector3), &normals[0]);
				}

				normals.clear();
				_submeshes[submesh]->_updateNormals = false;
			}

			// TEX COORDS
			if (_submeshes[submesh]->uvs.size() > 0)
			{
				if (vbo_id_t == 0)
				{
					glGenBuffersARB(1, &vbo_id_t);
				}
				else if (_submeshes[submesh]->_updateTexCoords)
				{
					glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo_id_t);
					glBufferSubData(GL_ARRAY_BUFFER_ARB, 0, uvs.size() * sizeof(Vector2), &uvs[0]);
				}

				uvs.clear();
				_submeshes[submesh]->_updateTexCoords = false;
			}

			//VERTICES
			if (vbo_id_v == 0)
			{
				glGenBuffersARB(1, &vbo_id_v);
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo_id_v);
				glBufferDataARB(GL_ARRAY_BUFFER_ARB, vertices.size() * sizeof(Vector3), &vertices[0], _vboUsage);
			}
			else
			{
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo_id_v);
				glBufferSubData(GL_ARRAY_BUFFER_ARB, 0, vertices.size() * sizeof(Vector3), &vertices[0]);
			}

			vertices.clear();
			_submeshes[submesh]->_updateVertices = false;

			//INDICES
			if (vbo_id_i == 0)
			{
				glGenBuffersARB(1, &vbo_id_i);
				glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, vbo_id_i);
				glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, indices.size() * sizeof(unsigned int), &indices[0], _vboUsage);
			}
			else
			{
				glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, vbo_id_i);
				glBufferSubData(GL_ELEMENT_ARRAY_BUFFER_ARB, 0, indices.size() * sizeof(unsigned int), &indices[0]);
			}

			indices.clear();
			_submeshes[submesh]->_updateIndices = false;
		}
	}
}

void Mesh::deleteAllBuffers(int submesh)
{
	if (isVBOSupported())
	{
		GLuint& vbo_id_n = _submeshes[submesh]->normal_buffer_id;
		GLuint& vbo_id_t =     _submeshes[submesh]->uv_buffer_id;
		GLuint& vbo_id_v = _submeshes[submesh]->vertex_buffer_id;
		GLuint& vbo_id_i =  _submeshes[submesh]->index_buffer_id;

		if (vbo_id_n > 0){glDeleteBuffersARB(1, &vbo_id_n);vbo_id_n = 0;}
		if (vbo_id_t > 0){glDeleteBuffersARB(1, &vbo_id_t);vbo_id_t = 0;}
		if (vbo_id_v > 0){glDeleteBuffersARB(1, &vbo_id_v);vbo_id_v = 0;}
		if (vbo_id_i > 0){glDeleteBuffersARB(1, &vbo_id_i);vbo_id_i = 0;}
	}
}

void Mesh::draw(int submesh)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//if hardware supports VBOs
	if (isVBOSupported())
	{
		GLuint& vbo_id_n = _submeshes[submesh]->normal_buffer_id;
		GLuint& vbo_id_t = _submeshes[submesh]->uv_buffer_id;
		GLuint& vbo_id_v = _submeshes[submesh]->vertex_buffer_id;
		GLuint& vbo_id_i = _submeshes[submesh]->index_buffer_id;

		if (_submeshes[submesh]->_updateVBO())
			genBuffers(submesh);

		if (vbo_id_i > 0 && vbo_id_v > 0)
		{
			if (vbo_id_n > 0)
			{
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo_id_n);
				glNormalPointer(GL_FLOAT, 0, 0);
			}
			if (vbo_id_t > 0)
			{
				glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo_id_t);
				glTexCoordPointer(2, GL_FLOAT, 0, 0);
			}

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo_id_v);
			glVertexPointer(3, GL_FLOAT, 0, 0);

			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, vbo_id_i);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

			glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
		}

	}
	else
	{
		std::vector<Vector3>& vertices = getVertices(submesh);
		std::vector<Vector2>& uvs = getUVs(submesh);
		std::vector<Vector3>& normals = getNormals(submesh);
		std::vector<unsigned int>& indices = getIndices(submesh);

		if (vertices.size() > 0 && indices.size() > 0)
		{
			if (uvs.size() > 0) glTexCoordPointer(2, GL_FLOAT, 0, &uvs[0]);
			if (normals.size() > 0)	glNormalPointer(GL_FLOAT, 0, &normals[0]);

			glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices[0]);
		}
	}

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

std::vector<Vector3> Mesh::getVertices(int submesh) const
{
	if (submesh >= (int)_submeshes.size())
	{
		printf("There is no submesh at index %d\n", submesh);
		return std::vector<Vector3>();
	}

	smart_pointer<SubMesh> subMesh = _submeshes[submesh];

	if (isVBOSupported())
	{
		std::vector<Vector3> data(subMesh->vertex_count);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, subMesh->vertex_buffer_id);
		glGetBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, data.size()*sizeof(Vector3), data.data());
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
		return data;
	}
	else
	{
		return subMesh->vertices;
	}
}

std::vector<Vector2> Mesh::getUVs(int submesh) const
{
	if (submesh >= (int)_submeshes.size())
	{
		printf("There is no submesh at index %d\n", submesh);
		return std::vector<Vector2>();
	}

	smart_pointer<SubMesh> subMesh = _submeshes[submesh];

	if (isVBOSupported())
	{
		std::vector<Vector2> data(subMesh->uv_count);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, subMesh->uv_buffer_id);
		glGetBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, data.size()*sizeof(Vector2), data.data());
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
		return data;
	}
	else
	{
		return subMesh->uvs;
	}
}

std::vector<Vector3> Mesh::getNormals(int submesh) const
{
	if (submesh >= (int)_submeshes.size())
	{
		printf("There is no submesh at index %d\n", submesh);
		return std::vector<Vector3>();
	}

	smart_pointer<SubMesh> subMesh = _submeshes[submesh];

	if (isVBOSupported())
	{
		std::vector<Vector3> data(subMesh->normal_count);
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, subMesh->normal_buffer_id);
		glGetBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, data.size()*sizeof(Vector3), data.data());
		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
		return data;
	}
	else
	{
		return subMesh->normals;
	}
}

std::vector<unsigned int> Mesh::getIndices(int submesh)const
{
	if (submesh >= (int)_submeshes.size())
	{
		printf("There is no submesh at index %d\n", submesh);
		return std::vector<unsigned int>();
	}

	smart_pointer<SubMesh> subMesh = _submeshes[submesh];

	if (isVBOSupported())
	{
		std::vector<unsigned int> data(subMesh->index_count);
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, subMesh->index_buffer_id);
		glGetBufferSubDataARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0, data.size()*sizeof(unsigned int), data.data());
		glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, 0);
		return data;
	}
	else
	{
		return subMesh->indices;
	}
}

void Mesh::setVertices(std::vector<Vector3> vertices, int submesh)
{
	if (submesh >= (int)_submeshes.size())
	{
		printf("There is no submesh at index %d\n", submesh);
		return;
	}

	if (_submeshes[submesh]->vertex_buffer_id != 0 && _submeshes[submesh]->vertices.size() != vertices.size())
	{
		glDeleteBuffersARB(1, &_submeshes[submesh]->vertex_buffer_id);
		_submeshes[submesh]->vertex_buffer_id = 0;
	}

	_submeshes[submesh]->_updateVertices = true;
	_submeshes[submesh]->vertices = vertices;
	_submeshes[submesh]->vertex_count = vertices.size();
}

void Mesh::setUVs(std::vector<Vector2> uvs, int submesh)
{
	if (submesh >= (int)_submeshes.size())
	{
		printf("There is no submesh at index %d\n", submesh);
		return;
	}

	if (_submeshes[submesh]->uv_buffer_id != 0 && _submeshes[submesh]->uvs.size() != uvs.size())
	{
		glDeleteBuffersARB(1, &_submeshes[submesh]->uv_buffer_id);
		_submeshes[submesh]->uv_buffer_id = 0;
	}

	_submeshes[submesh]->_updateTexCoords = true;
	_submeshes[submesh]->uvs = uvs;
	_submeshes[submesh]->uv_count = uvs.size();
}

void Mesh::setNormals(std::vector<Vector3> normals, int submesh)
{
	if (submesh >= (int)_submeshes.size())
	{
		printf("There is no submesh at index %d\n", submesh);
		return;

	}
	if (_submeshes[submesh]->normal_buffer_id != 0 && _submeshes[submesh]->normals.size() != normals.size())
	{
		glDeleteBuffersARB(1, &_submeshes[submesh]->normal_buffer_id);
		_submeshes[submesh]->normal_buffer_id = 0;
	}

	_submeshes[submesh]->_updateNormals = true;
	_submeshes[submesh]->normals = normals;
	_submeshes[submesh]->normal_count = normals.size();
}

void Mesh::setIndices(std::vector<unsigned int> indices, int submesh)
{
	if (submesh >= (int)_submeshes.size())
	{
		printf("There is no submesh at index %d\n", submesh);
		return;
	}

	if (_submeshes[submesh]->index_buffer_id != 0 && _submeshes[submesh]->indices.size() != indices.size())
	{
		glDeleteBuffersARB(1, &_submeshes[submesh]->index_buffer_id);
		_submeshes[submesh]->index_buffer_id = 0;
	}

	_submeshes[submesh]->_updateIndices = true;
	_submeshes[submesh]->indices = indices;
	_submeshes[submesh]->index_count = indices.size();
}

void Mesh::clear()
{
	for (int i = 0; i < (int)_submeshes.size(); i++)
	{
		smart_pointer<SubMesh>& m = _submeshes[i];

		deleteAllBuffers(i);
		m->vertices.clear(); m->vertex_count = 0;
		m->uvs.clear(); m->uv_count = 0;
		m->normals.clear(); m->normal_count = 0;
		m->indices.clear(); m->index_count = 0;
	}
}