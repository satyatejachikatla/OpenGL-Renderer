#include <Sphere.h>

#include <GL/glew.h>
#include <imgui/imgui.h>
#include <Camera.h>
#include <Lighting.h>

#include <math.h>
#include <cmath>

namespace objects {

	Sphere::Sphere(const char* img) : Object(){


		unsigned int  sectorCount = 100;
		unsigned int  stackCount  = 100;
		float         radius      = 1.0f;

/* Copied from http://www.songho.ca/opengl/gl_sphere.html */

		float x, y, z, xy;                              // vertex position
		float nx, ny, nz, lengthInv = 1.0f / radius;    // vertex normal
		float s, t;                                     // vertex texCoord

		float sectorStep = 2 * M_PI / sectorCount;
		float stackStep = M_PI / stackCount;
		float sectorAngle, stackAngle;

		for(int i = 0; i <= stackCount; ++i)
		{
			stackAngle = M_PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
			xy = radius * cosf(stackAngle);             // r * cos(u)
			z = radius * sinf(stackAngle);              // r * sin(u)

			// add (sectorCount+1) vertices per stack
			// the first and last vertices have same position and normal, but different tex coords
			for(int j = 0; j <= sectorCount; ++j)
			{

				Vertex v;

				sectorAngle = j * sectorStep;           // starting from 0 to 2pi

				// vertex position (x, y, z)
				x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
				y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
				v.vertexCoords.x = x;
				v.vertexCoords.y = y;
				v.vertexCoords.z = z;

				// normalized vertex normal (nx, ny, nz)
				nx = x * lengthInv;
				ny = y * lengthInv;
				nz = z * lengthInv;
				v.normal.x = nx;
				v.normal.y = ny;
				v.normal.z = nz;

				// vertex tex coord (s, t) range between [0, 1]
				s = (float)j / sectorCount;
				t = (float)i / stackCount;
				v.textureCoords.x = s;
				v.textureCoords.y = t;

				v.color = glm::vec3(1.0f,1.0f,1.0f);
				v.textureId = 0;

				m_Vertices.push_back(v);
			}
		}

		/* Default Index Ordering */
		std::vector<unsigned int> indices;
		int k1, k2;
		for(int i = 0; i < stackCount; ++i)
		{
			k1 = i * (sectorCount + 1);     // beginning of current stack
			k2 = k1 + sectorCount + 1;      // beginning of next stack

			for(int j = 0; j < sectorCount; ++j, ++k1, ++k2)
			{
				// 2 triangles per sector excluding first and last stacks
				// k1 => k2 => k1+1
				if(i != 0)
				{
					indices.push_back(k1);
					indices.push_back(k2);
					indices.push_back(k1 + 1);
				}

				// k1+1 => k2 => k2+1
				if(i != (stackCount-1))
				{
					indices.push_back(k1 + 1);
					indices.push_back(k2);
					indices.push_back(k2 + 1);
				}
			}
		}

/* Copied ends */

		m_VAO = std::make_unique<VertexArray>();
		m_VBO = std::make_unique<VertexBuffer>(m_Vertices.data(),m_Vertices.size()*sizeof(Vertex));

		VertexBufferLayout layout;
		layout.VertexLayoutAutoFill();

		m_VAO->AddBuffer(*m_VBO,layout);

		m_Shader = std::make_unique<Shader>("./objects/shaders/Sphere.shader");
		m_Shader->Bind();

		m_Texture = std::make_unique<Texture>(img);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices.data(),indices.size());

		/*
		for(int i =0 ;i < 24 ; i++) {
			std::cout << "Vertex " << i << std::endl;
			std::cout <<glm::to_string(m_Vertices[i].vertexCoords)<<std::endl;
			std::cout <<glm::to_string(m_Vertices[i].color)<<std::endl;
			std::cout <<glm::to_string(m_Vertices[i].textureCoords)<<std::endl;
			std::cout <<m_Vertices[i].textureId<<std::endl;
		}
		*/
	}

	Sphere::~Sphere(){
		
	}

	void Sphere::OnUpdate(){
		Object::OnUpdate();
	}

	void Sphere::OnRender(){

		glm::mat4 m = m_Model;

		std::vector<Shader*> shader_list;
		shader_list.push_back(m_Shader.get());

		Camera* camera = Camera::getCurrentCamera();
		if(camera)
			camera->OnRender(shader_list);

		m_Shader->Bind();

		/* Material Properties */
		m_Shader->SetUniform1f("u_Material.selectColor",0.0f);
		m_Shader->SetUniform1f("u_Material.shininess",32.0f);
		m_Shader->SetUniform1i("u_Material.texture",0);

		m_Shader->SetUniform1i("u_Material.isSpecularMap",0);
		m_Shader->SetUniform1i("u_Material.specularMap",0);

		m_Shader->SetUniformMat4f("u_M",m);

		m_Texture->Bind(0);



		/* Draw Call */
		m_Renderer.Draw(*m_VAO,*m_IndexBuffer,*m_Shader);

	}
	void Sphere::OnImGuiRender(){
		Object::OnImGuiRender();
	}

}