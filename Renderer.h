#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "glErrors.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Renderer {
public:
	void Clear() const;
	void Draw(const VertexArray& va,const IndexBuffer& ib,const Shader& shader);
};

#endif /* __RENDERER_H__ */
