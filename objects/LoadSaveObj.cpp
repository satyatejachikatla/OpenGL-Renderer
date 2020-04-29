#include <LoadSaveObj.h>

namespace objects {

	std::shared_ptr<LoadedObjectData> LoadObject(const char* filename) {

		std::ifstream stream(filename);

		if(stream.fail())
			return nullptr;


		std::string line;

		std::shared_ptr<LoadedObjectData> object = std::make_shared<LoadedObjectData>();
		std::vector<glm::vec2> texture_coords;
		std::vector<glm::vec3> normals;

		while(getline(stream,line)) {
			std::stringstream ss;
			std::string type;

			ss << line;

			ss >> type;

			if(type == "o") {
				ss >> object->name;
			} else if(type == "v") {
				Vertex t;
				ss >> t.vertexCoords.x >> t.vertexCoords.y >> t.vertexCoords.z; 
				object->vertices.push_back(t);
			} else if(type == "vt") {
				glm::vec2 t;
				ss >> t.x >> t.y; 
				texture_coords.push_back(t);
			} else if(type == "vn") {
				glm::vec3 t;
				ss >> t.x >> t.y >> t.z; 
				normals.push_back(t);
			} else if(type == "vn") {
				glm::vec3 t;
				ss >> t.x >> t.y >> t.z; 
				normals.push_back(t);
			} else if(type == "f") {
			// Spcial case for f , to read all the object faces and populate he vertices
				do {
					std::stringstream().swap(ss);
					ss << line;
					ss >> type;

//					std::cout << ss.str() << std::endl;

					std::string p1;
					std::string p2;
					std::string p3;

					unsigned int vertex_index;
					unsigned int texture_coordinate_index;
					unsigned int normal_index;

					ss >> p1 >> p2 >> p3;

					std::replace( p1.begin(), p1.end(), '/', ' ');
					std::replace( p2.begin(), p2.end(), '/', ' ');
					std::replace( p3.begin(), p3.end(), '/', ' ');

					std::stringstream pss;
					pss << p1 <<" "<< p2 <<" "<< p3 ;
//					std::cout << p1 << p2 << p3  << std::endl;
//					std::cout << pss.str() << std::endl;
//					return nullptr;

					for(int face_idx=0 ; face_idx<3 ; face_idx++){
						pss >> vertex_index >> texture_coordinate_index >> normal_index;
						object->vertices[vertex_index-1].textureCoords = texture_coords[texture_coordinate_index-1];
						object->vertices[vertex_index-1].normal = normals[normal_index-1];

						object->indices.push_back(vertex_index-1);
					}

				}while(getline(stream,line));
				break; // End out while
			} else {
				std::cerr <<__PRETTY_FUNCTION__ <<  ":" << ": Unknown type : " << type << " " << std::endl;
			}
		}

		return object;
	}
}

#ifdef UNIT_TEST
	//g++ -DUNIT_TEST -I. -I.. -I../infra -I../vendor LoadSaveObj.cpp
	int main() {
		std::shared_ptr<objects::LoadedObjectData> temp = objects::LoadObject("./objs/stall.obj");

		if(!temp) {
			std::cout << "Failed" <<std::endl;
			return -1;
			
		}
		std::cout << "Vertices count:" << temp->vertices.size() << std::endl;

		for(int i=0;i<temp->vertices.size();i++) {
			std::cout << glm::to_string(temp->vertices[i].vertexCoords) << std::endl;
		}

		std::cout << "Indices  count:" << temp->indices.size()  << std::endl;
		for(int i=0;i<temp->indices.size();i++) {
			std::cout << temp->indices[i] << " " << temp->indices[i+1] << " " << temp->indices[i+2] << std::endl;
		}
		return 0;
	}
#endif