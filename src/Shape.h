#pragma once
#ifndef _SHAPE_H_
#define _SHAPE_H_

#include <string>
#include <vector>
#include <memory>
#include <glm/gtc/type_ptr.hpp>
#include <tiny_obj_loader/tiny_obj_loader.h>

class Program;

class Shape
{
public:
	Shape();
	virtual ~Shape();
	void reverseNormals();
	void populateNorBuf(size_t i, glm::vec3 normal);
	void normalizeNorBuf();
	void computeNormals();
	void createShape(tinyobj::shape_t & shape);
	void Init(bool norMap);
	void scale(glm::vec3 scaleFactor);
	void measure();
	void draw(const std::shared_ptr<Program> prog, bool norMap) const;
	void ComputeTex();
	void ComputeTanBN();
	glm::vec3 min;
	glm::vec3 max;
	
private:
	std::vector<unsigned int> eleBuf;
	std::vector<float> posBuf;
	std::vector<float> norBuf;
	std::vector<float> texBuf;
	std::vector<float> tanBuf;
	std::vector<float> BNBuf;
	unsigned eleBufID;
	unsigned posBufID;
	unsigned norBufID;
	unsigned texBufID;
	unsigned tanBufID;
	unsigned BNBufID;
   unsigned vaoID;
};

#endif
