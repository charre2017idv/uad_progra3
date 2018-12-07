#pragma once
#include "../Include/CCamera.h"
#include "../Include/CVector3.h"
#include "CVector3.h"
class CCamera
{
public:
	CCamera();
	~CCamera();
public: 
	CVector3 m_bounds[4];
	// Camera points
	// referente a m_objectPosition
	CVector3 m_leftUp    = { -0.1, 1.0, 0.0 };
	CVector3 m_rightDown = { -1.0, 0.1, 0.0 };
	
	// Camara Joel
private: 
	CVector3 m_pos;     // Getter for each one
	CVector3 m_lookAt;	// Getter for each one
	CVector3 m_right;	// Getter for each one
	float m_nearPlane;	// Getter for each one
	float m_farPlane;   // Getter for each one
	bool m_2D;
public:
	// CTor / DTor
	void moveCamera(CVector3 delta);
	void panCamera(CVector3 delta);

	CVector3 getPos() { return m_pos; }
	CVector3 getLookAt() { return m_lookAt; }
	CVector3 getRight() { return m_right; }
	float getNearPlane() { return m_nearPlane; }
	float getFarPlane() { return m_nearPlane; }


public: 
	void virtualCamera();
private:

};

