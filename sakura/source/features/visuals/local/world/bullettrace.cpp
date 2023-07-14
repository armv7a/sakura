#include "../../../../client.h"

int localLastAmmo;

void BulletTrace::Local(struct usercmd_s* cmd)
{
	if (!cvar.visual_bullet_trace_local)
		return;

	if (!Sakura::ScreenShot::IsVisuals())
		return;

	int g_iShotsFired = g_Local.weapon.m_iShotsFired;

	if (g_iShotsFired > localLastAmmo || CanAttack() && !IsFreezePeriod() && cmd->buttons & IN_ATTACK && IsCurWeaponSniper())
	{
		Vector vForward;
		Vector vAngle = cmd->viewangles;
		Vector vEye = pmove->origin + pmove->view_ofs;

		g_Engine.pfnAngleVectors(vAngle, vForward, NULL, NULL);

		int beamindex = g_Engine.pEventAPI->EV_FindModelIndex("sprites/laserbeam.spr");
		pmtrace_t tr;

		g_Engine.pEventAPI->EV_SetTraceHull(2);

		Vector vEnd = vEye + vForward * 8192;

		g_Engine.pEventAPI->EV_PlayerTrace(vEye, vEnd, PM_GLASS_IGNORE, -1, &tr);
		g_Engine.pEfxAPI->R_BeamPoints(vEye, tr.endpos, beamindex, cvar.visual_bullet_trace_local_liveness, cvar.visual_bullet_trace_local_thickness, 0, cvar.visual_bullet_trace_local_color[3], 2, 0, 0, cvar.visual_bullet_trace_local_color[0], cvar.visual_bullet_trace_local_color[1], cvar.visual_bullet_trace_local_color[2]);
	}

	if (g_iShotsFired > 600)
		g_iShotsFired = 1;

	localLastAmmo = g_iShotsFired;
}

void BulletTrace::Enemy(struct cl_entity_s* ent)
{
	if (cvar.visual_bullet_trace || cvar.visual_line_of_sight)
	{
		int beamindex = g_Engine.pEventAPI->EV_FindModelIndex("sprites/laserbeam.spr");

		Vector vecStart, vecEnd, vecEnd2, vecForward;

		pmtrace_t tr;
		pmtrace_t tr2;

		// angles, forward, right, up
		g_Engine.pfnAngleVectors(ent->angles, vecForward, NULL, NULL);
		vecForward.z = -vecForward.z;

		vecStart = g_Player[ent->index].vEye;
		vecEnd = vecStart + vecForward * 8192;
		vecEnd2 = vecStart + vecForward * cvar.visual_line_of_sight_distance;

		g_Engine.pEventAPI->EV_SetTraceHull(2);
		g_Engine.pEventAPI->EV_PlayerTrace(vecStart, vecEnd, PM_GLASS_IGNORE, -1, &tr);
		g_Engine.pEventAPI->EV_PlayerTrace(vecStart, vecEnd2, PM_GLASS_IGNORE, -1, &tr2);

		if (cvar.visual_line_of_sight)
		{
			g_Engine.pEfxAPI->R_BeamPoints(vecStart, tr2.endpos, beamindex, 0.001f, 0.9f, 0, 32, 2, 0, 0, cvar.visual_line_of_sight_color[0], cvar.visual_line_of_sight_color[1], cvar.visual_line_of_sight_color[2]);
		}

		if (cvar.visual_bullet_trace)
		{
			int seq = Cstrike_SequenceInfo[ent->curstate.sequence];

			if (seq == SEQUENCE_SHOOT)
			{
				ImRGBA playerBeamColor = Sakura::Colors::GetTeamColor(ent->index);

				g_Engine.pEfxAPI->R_BeamPoints(vecStart, tr.endpos, beamindex, 0.001f, 0.9f, 0, 32, 2, 0, 0, playerBeamColor.r, playerBeamColor.g, playerBeamColor.b);
			}
		}
	}
}