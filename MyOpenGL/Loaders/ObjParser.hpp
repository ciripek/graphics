#pragma once

// Based on sroccaserra's (https://sourceforge.net/users/sroccaserra/) Obj loader
// http://sourceforge.net/projects/objloader/

#include <fstream>
#include <glm/glm.hpp>
#include <map>
#include <vector>

#include "Mesh.hpp"

class ObjParser final
{
public:
	static Mesh* parse(const char* fileName);

private:
	struct indexedVert {
		int v, vt, vn;
		indexedVert(int v, int vt, int vn) : v(v), vt(vt), vn(vn) {};
		bool operator<(const indexedVert& rhs) const {
			return v<rhs.v || (v == rhs.v && (vt<rhs.vt || (vt == rhs.vt && vn<rhs.vn)));
		}
	};
		
	ObjParser() = default;

	bool processLine();
	bool skipCommentLine();
	void skipLine();
	void addIndexedVertex(const indexedVert& vertex);

	Mesh* mesh = nullptr;
	std::ifstream ifs;

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texcoords;

	unsigned int nIndexedVerts = 0;
	std::map<indexedVert, unsigned int> vertexIndices;
};
