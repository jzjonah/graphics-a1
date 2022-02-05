#include "headers.h"
#include "drawbuffer.h"
#include "worldDefs.h"

#define FLEA_SPEED   -1.0


class Flea {

	
	static GLuint VAO;
	static vec2 fleaGeometry[];

public:
	vec2 pos;

	Flea(vec2 _pos) {
		pos = _pos;

		if (VAO == NULL)
			generateVAOs();

	}
	void generateVAOs();
	void draw(mat4& worldToViewTransform);
	void move(float elapsedTime);;
};