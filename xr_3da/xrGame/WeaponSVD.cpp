#include "pch_script.h"
#include "weaponsvd.h"

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
#include "xr_level_controller.h"
#include "level.h"

void GetZoomData(const float scope_factor, float& delta, float& min_zoom_factor)
{
	float def_fov = float(g_fov);
	float min_zoom_k = 0.3f;
	float zoom_step_count = 3.0f;
	float delta_factor_total = def_fov - scope_factor;
	VERIFY(delta_factor_total>0);
	min_zoom_factor = def_fov - delta_factor_total*min_zoom_k;
	delta = (delta_factor_total*(1 - min_zoom_k)) / zoom_step_count;

}

CWeaponSVD_n::CWeaponSVD_n(void) : CWeaponCustomPistol("SVD")
{
}

CWeaponSVD_n::~CWeaponSVD_n(void)
{
}

void CWeaponSVD_n::switch2_Fire()
{
	m_bFireSingleShot = true;
	bWorking = false;
	m_bPending = true;
	m_iShotNum = 0;
	m_bStopedAfterQueueFired = false;

}

bool CWeaponSVD_n::Action(s32 cmd, u32 flags)
{
	switch(cmd)
	{
	case kWPN_ZOOM:
		return inherited::Action(kWPN_ZOOM, flags);
	}

	return inherited::Action(cmd, flags);
}

void CWeaponSVD_n::OnAnimationEnd(u32 state)
{
	switch (state)
	{
	case eFire:	{
		m_bPending = false;
	}break;	// End of reload animation
	}
	inherited::OnAnimationEnd(state);
}

void CWeaponSVD_n::OnZoomIn()
{
	if (H_Parent() && !IsZoomed())
	{
		HUD_SOUND::StopSound(sndZoomOut);
		bool b_hud_mode = (Level().CurrentEntity() == H_Parent());
		HUD_SOUND::PlaySound(sndZoomIn, H_Parent()->Position(), H_Parent(), b_hud_mode);
		if (m_bVision && !m_binoc_vision)
		{
			//.VERIFY			(!m_binoc_vision);
			m_binoc_vision = xr_new<CBinocularsVision>(this);
		}
	}

	inherited::OnZoomIn();
	m_fZoomFactor = m_fRTZoomFactor;

}

void CWeaponSVD_n::OnZoomOut()
{
	if (H_Parent() && IsZoomed() && !IsRotatingToZoom())
	{
		HUD_SOUND::StopSound(sndZoomIn);
		bool b_hud_mode = (Level().CurrentEntity() == H_Parent());
		HUD_SOUND::PlaySound(sndZoomOut, H_Parent()->Position(), H_Parent(), b_hud_mode);
		VERIFY(m_binoc_vision);
		xr_delete(m_binoc_vision);

		m_fRTZoomFactor = m_fZoomFactor;//store current
	}


	inherited::OnZoomOut();
}
void CWeaponSVD_n::ZoomInc()
{
	float delta, min_zoom_factor;
	GetZoomData(m_fScopeZoomFactor, delta, min_zoom_factor);

	m_fZoomFactor -= delta;
	clamp(m_fZoomFactor, m_fScopeZoomFactor, min_zoom_factor);
}

void CWeaponSVD_n::ZoomDec()
{
	float delta, min_zoom_factor;
	GetZoomData(m_fScopeZoomFactor, delta, min_zoom_factor);

	m_fZoomFactor += delta;
	clamp(m_fZoomFactor, m_fScopeZoomFactor, min_zoom_factor);
}

using namespace luabind;

#pragma optimize("s",on)
void CWeaponSVD_n::script_register(lua_State *L)
{
	module(L)
		[
			class_<CWeaponSVD, CGameObject>("CWeaponSVD_n")
			.def(constructor<>())
		];
}

