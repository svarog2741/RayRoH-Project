#pragma once

#include "weaponcustompistol.h"
#include "script_export_space.h"
#include "Weapon.h"

class CBinocularsVision;

class CWeaponSVD :
	public CWeaponCustomPistol
{
	typedef CWeaponCustomPistol inherited;
protected:
	virtual void switch2_Fire();
	virtual void OnAnimationEnd(u32 state);
public:
	CWeaponSVD(void);
	virtual ~CWeaponSVD(void);

	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CWeaponSVD)
#undef script_type_list
#define script_type_list save_type_list(CWeaponSVD)


/*
---------------------------------------------------------------------
-------------------By RayRoH aka svarog2741--------------------------
---------------------------------------------------------------------
*/

class CWeaponSVD_n :
	public CWeaponCustomPistol
{
	typedef CWeaponCustomPistol inherited;
protected:
	virtual void switch2_Fire();
	virtual void OnAnimationEnd(u32 state);
	HUD_SOUND		sndZoomIn;
	HUD_SOUND		sndZoomOut;
	float			m_fRTZoomFactor; //run-time zoom factor
	bool			m_bVision;
public:
	virtual bool	Action(s32 cmd, u32 flags);
	virtual void	OnZoomIn();
	virtual void	OnZoomOut();
	virtual	void	ZoomInc();
	virtual	void	ZoomDec();
	CBinocularsVision*					m_binoc_vision;
	CWeaponSVD_n(void);
	virtual ~CWeaponSVD_n(void);

	DECLARE_SCRIPT_REGISTER_FUNCTION
};
add_to_type_list(CWeaponSVD_n)
#undef script_type_list
#define script_type_list save_type_list(CWeaponSVD_n)
