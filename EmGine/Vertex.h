#pragma once

#include <GL/glew.h>

namespace EmGine{

struct Position{

	Position(){}
	Position(float X, float Y) : x(X), y(Y){}
	float x;
	float y;
};

struct UV{

	UV(){}
	UV(float U, float V) :u(U), v(V){}
	float u;
	float v;
};

struct ColorRGBA8{

	ColorRGBA8(): r(0), g(0), b(0), a(0){}
	ColorRGBA8(GLubyte R, GLubyte G, GLubyte B, GLubyte A) :
		r(R), g(G), b(B), a(A){}
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

struct Vertex{

	Vertex(){}
	Vertex(Position POSITION, ColorRGBA8 COLOR, UV UV) :
		position(POSITION), color(COLOR), uv(UV){}
	Position position;
	ColorRGBA8 color;
	UV uv;

	void setColor(ColorRGBA8 aColor){

		color = aColor;
	}

	void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a){

		color.r = r;
		color.g = g;
		color.b = b;
		color.a = a;
	}

	void setPosition(Position aPosition){

		position = aPosition;
	}

	void setPosition(float x, float y){

		position.x = x;
		position.y = y;
	}

	void setUV(UV aUV){

		uv = aUV;
	}

	void setUV(float u, float v){

		uv.u = u;
		uv.v = v;
	}
};

}