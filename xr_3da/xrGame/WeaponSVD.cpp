#include "pch_script.h"
#include "weaponsvd.h"
//#include "WeaponBinocularsVision.cpp"

//#include "WeaponBinocularsVision.h"
CWeaponSVD::CWeaponSVD(void) : CWeaponCustomPistol("SVD")
{
}

CWeaponSVD::~CWeaponSVD(void)
{
}

void CWeaponSVD::switch2_Fire	()
{
	m_bFireSingleShot			= true;
	bWorking					= false;
	m_bPending					= true;
	m_iShotNum					= 0;
	m_bStopedAfterQueueFired	= false;

}

void CWeaponSVD::OnAnimationEnd(u32 state) 
{
	switch(state) 
	{
	case eFire:	{
		m_bPending = false;
		}break;	// End of reload animation
	}
	inherited::OnAnimationEnd(state);
}

using namespace luabind;

#pragma optimize("s",on)
void CWeaponSVD::script_register	(lua_State *L)
{
	module(L)
	[
		class_<CWeaponSVD,CGameObject>("CWeaponSVD")
			.def(constructor<>())
	];
}

/*
---------------------------------------------------------------------
-------------------By RayRoH aka svarog2741--------------------------
---------------------------------------------------------------------
*/
#pragma todo("By RayRoH aka svarog2741")
#pragma todo("Ёкспериментальна€ правка")