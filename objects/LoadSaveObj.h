#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <algorithm>

#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <VertexBufferLayout.h>


namespace objects {

	struct LoadedObjectData {
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::string name;
	};

	std::shared_ptr<LoadedObjectData> LoadObject(const char* filename);
}
