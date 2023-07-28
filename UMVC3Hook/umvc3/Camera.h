#pragma once
#include "../utils.h"
#include "Matrix.h"
#include "Vector.h"

class UMVC3MainCamera {
public:
	char pad[160];
	Matrix mat;
	char _pad[64];
	Matrix mat2;
};

class UMVC3GameCamera {
public:
	char pad[72];
	float mAspect;
	float mFOV;
	Vector mCameraPos;
	char  _pad[4];    
	Vector mCameraUp;
	char  __pad[4]; 
	Vector mCameraUnk; 
	Vector mTargetPos; 
};

extern UMVC3GameCamera* TheCamera;

UMVC3MainCamera* GetMainCamera();

VALIDATE_OFFSET(UMVC3MainCamera, mat, 160);
VALIDATE_OFFSET(UMVC3MainCamera, mat2, 288);
VALIDATE_OFFSET(UMVC3GameCamera, mCameraPos, 80);
VALIDATE_OFFSET(UMVC3GameCamera, mFOV, 76);
VALIDATE_OFFSET(UMVC3GameCamera, mTargetPos, 124);