#include "../../client.h"

int Sakura::Lua::ScriptsCount = 0;
int Sakura::Lua::currentScriptIndex = 0;

std::vector<Sakura::Lua::LuaScripts> Sakura::Lua::scripts;

Vector Sakura::Lua::Game::vLastConvertedVector(0, 0, 0);

void Sakura::Lua::Hooks::RegisterCallBack(UINT type, luabridge::LuaRef f)
{
	if (type < 0 || type >= SAKURA_CALLBACK_ALL_CALLBACKS)
		return;

	Sakura::Lua::scripts[currentScriptIndex].RegisterCallback(type, f);
}

void Sakura::Lua::Game::SendPacket(bool status)
{
	bSendpacket(status);
}

DWORD Sakura::Lua::Game::InitSound(const char* filename)
{
	char temp[256];
	sprintf(temp, "%s%s", hackdir, filename);
	return BASS_StreamCreateFile(FALSE, temp, 0, 0, 0);
}

void Sakura::Lua::Game::SoundPlay(const DWORD sound, const float volume)
{
	BASS_ChannelSetAttribute(sound, BASS_ATTRIB_VOL, volume / 100.f);
	BASS_ChannelPlay(sound, true);
}

void Sakura::Lua::Game::CreateVisibleEntity(const int entityType, cl_entity_s* entity)
{
	g_Engine.CL_CreateVisibleEntity(entityType, entity);
}

bool Sakura::Lua::Game::WorldToScreen(Vector& in)
{
	return ::WorldToScreen((float*)in, (float*)Sakura::Lua::Game::vLastConvertedVector);
}

Vector Sakura::Lua::Game::GetLastConvertedToScreenVector()
{
	return Sakura::Lua::Game::vLastConvertedVector;
}

DWORD Sakura::Lua::Game::GetTime()
{
	return GetTickCount();
}

int Sakura::Lua::LocalPlayer::GetIndex()
{
	return pmove->player_index + 1;
}

int Sakura::Lua::LocalPlayer::GetTeam()
{
	return g_Local.iTeam;
}

int Sakura::Lua::LocalPlayer::GetFlags()
{
	return pmove->flags;
}

bool Sakura::Lua::LocalPlayer::CheckFlag(const int flag)
{
	return (pmove->flags & flag);
}

int Sakura::Lua::LocalPlayer::GetButtons()
{
	return pmove->cmd.buttons;
}

bool Sakura::Lua::LocalPlayer::CheckButton(const usercmd_s* cmd, const int button)
{
	return (cmd->buttons & button);
}

void Sakura::Lua::LocalPlayer::PressButton(usercmd_s* cmd, const int button)
{
	cmd->buttons |= button;
}

void Sakura::Lua::LocalPlayer::ReleaseButton(usercmd_s* cmd, const int button)
{
	cmd->buttons &= ~button;
}

bool Sakura::Lua::LocalPlayer::IsAlive()
{
	return Sakura::Player::Local::IsAlive();
}

bool Sakura::Lua::LocalPlayer::IsScoped()
{
	return g_Local.bScoped;
}

void Sakura::Lua::LocalPlayer::FixMoveStart(usercmd_s* cmd)
{
	::FixMoveStart(cmd);
}

void Sakura::Lua::LocalPlayer::FixMoveEnd(usercmd_s* cmd)
{
	::FixMoveEnd(cmd);
}

Vector Sakura::Lua::LocalPlayer::GetViewAngles()
{
	return pmove->angles;
}

void Sakura::Lua::LocalPlayer::SetViewAngles(Vector angles)
{
	pmove->angles = angles;
}

Vector Sakura::Lua::LocalPlayer::GetEyePosition()
{
	return pmove->origin + pmove->view_ofs;
}

bool Sakura::Lua::LocalPlayer::IsCurWeaponKnife()
{
	return ::IsCurWeaponKnife();
}

bool Sakura::Lua::LocalPlayer::IsCurWeaponPistol()
{
	return ::IsCurWeaponPistol();
}

bool Sakura::Lua::LocalPlayer::IsCurWeaponNade()
{
	return ::IsCurWeaponNade();
}

bool Sakura::Lua::LocalPlayer::IsCurWeaponSniper()
{
	return ::IsCurWeaponSniper();
}

bool Sakura::Lua::LocalPlayer::IsCurWeaponRifle()
{
	return ::IsCurWeaponRifle();
}

bool Sakura::Lua::LocalPlayer::IsCurWeaponShotGun()
{
	return ::IsCurWeaponShotGun();
}

bool Sakura::Lua::LocalPlayer::IsCurWeaponMachineGun()
{
	return ::IsCurWeaponMachineGun();
}

bool Sakura::Lua::LocalPlayer::IsCurWeaponSubMachineGun()
{
	return ::IsCurWeaponSubMachineGun();
}

void Sakura::Lua::LocalPlayer::ExecuteCommand(const char* command, const char* value)
{
	char fullCommand[64];
	sprintf(fullCommand, "%s \"%s\"", command, value);
	g_Engine.pfnClientCmd(fullCommand);
}

std::string Sakura::Lua::LocalPlayer::GetCommandString(const char* command)
{
	char fullCommand[64];
	sprintf(fullCommand, "%s", command);
	return g_Engine.pfnGetCvarString(fullCommand);
}

int Sakura::Lua::LocalPlayer::GetCommandFloat(const char* command)
{
	char fullCommand[64];
	sprintf(fullCommand, "%s", command);
	return g_Engine.pfnGetCvarFloat(fullCommand);
}

std::string Sakura::Lua::LocalPlayer::GetWeaponName()
{
	if (Sakura::Player::Local::IsAlive())
	{
		switch (g_Local.weapon.m_iWeaponID)
		{
		case WEAPON_P228:		return "P228"; break;
		case WEAPON_SCOUT:		return "Scout"; break;
		case WEAPON_XM1014:		return "XM1014"; break;
		case WEAPON_MAC10:		return "Mac10"; break;
		case WEAPON_AUG:		return "Aug"; break;
		case WEAPON_ELITE:		return "Elite"; break;
		case WEAPON_FIVESEVEN:	return "Five-seven"; break;
		case WEAPON_UMP45:		return "Ump45"; break;
		case WEAPON_SG550:		return "SG550"; break;
		case WEAPON_GALIL:		return "Galil"; break;
		case WEAPON_FAMAS:		return "Famas"; break;
		case WEAPON_USP:		return "Usp"; break;
		case WEAPON_GLOCK18:	return "Glock-18"; break;
		case WEAPON_AWP:		return "AWP"; break;
		case WEAPON_MP5N:		return "MP5"; break;
		case WEAPON_M249:		return "M249"; break;
		case WEAPON_M3:			return "M3"; break;
		case WEAPON_M4A1:		return "M4a1"; break;
		case WEAPON_TMP:		return "Tmp"; break;
		case WEAPON_G3SG1:		return "G3SG1"; break;
		case WEAPON_DEAGLE:		return "Deagle"; break;
		case WEAPON_SG552:		return "SG552"; break;
		case WEAPON_AK47:		return "AK-47"; break;
		case WEAPON_P90:		return "P90"; break;
		case WEAPON_HEGRENADE:	return "he"; break;
		case WEAPON_SMOKEGRENADE: return"sg"; break;
		case WEAPON_FLASHBANG:	return "fh"; break;
		case WEAPON_KNIFE:		return "knife"; break;
		default:				return "Unknown"; break;
		}
	}

	return "Unknown";
}

int Sakura::Lua::Player::GetTeam(int index)
{
	return g_Player[index].iTeam;
}

Vector Sakura::Lua::Player::GetOrigin(int index)
{
	return PlayerEsp[index].origin;
}

std::string Sakura::Lua::Player::GetName(int index)
{
	player_info_s* player = g_Studio.PlayerInfo(index - 1);
	return player->name;
}

std::string Sakura::Lua::Player::GetModelName(int index)
{
	return PlayerEsp[index].model;
}

int Sakura::Lua::Player::GetDistance(int index)
{
	Vector vDifference = PlayerEsp[index].origin - Sakura::Lua::LocalPlayer::GetEyePosition();
	int iDistance = int(vDifference.Length() / 22.0f);
	return iDistance;
}

float Sakura::Lua::Player::GetActualDistance(int index)
{
	Vector vDifference = PlayerEsp[index].origin - Sakura::Lua::LocalPlayer::GetEyePosition();
	return vDifference.Length();
}

int Sakura::Lua::Player::GetPing(int index)
{
	player_info_s* player = g_Studio.PlayerInfo(index - 1);
	return player->ping;
}

bool Sakura::Lua::Player::IsAlive(int index)
{
	return ::Sakura::Player::IsAlive(index);
}

void Sakura::Lua::Notify::Create(const char* szTitle, const int secondsDisplay = 3)
{
	Toast::Create({ secondsDisplay, szTitle });
}

void Sakura::Lua::ImGui::Menu(const char* szTitle, luabridge::LuaRef lfFunction)
{
	if (::ImGui::BeginTabItem(szTitle, 0, 0))
	{
		try
		{
			lfFunction();
		}
		catch (luabridge::LuaException const& error)
		{
			LogToFile("Lua script error: %s", error.what());
			Toast::Create({ 7, "An error occured in lua script! Check the logs!" });
		}
	}
	::ImGui::EndTabItem();
}

void Sakura::Lua::ImGui::Window(const char* szTitle, ImGuiWindowFlags flags, luabridge::LuaRef lfFunction)
{
	if (::ImGui::Begin(szTitle, 0, flags))
	{
		try
		{
			lfFunction();
		}
		catch (luabridge::LuaException const& error)
		{
			LogToFile("Lua script error: %s", error.what());
			Toast::Create({ 7, "An error occured in lua script! Check the logs!" });
		}
	}
	::ImGui::End();
}

void Sakura::Lua::ImGui::Text(const char* szText)
{
	::ImGui::Text(szText);
}

bool Sakura::Lua::ImGui::Button(const char* szText)
{
	return ::ImGui::Button(szText);
}

bool Sakura::Lua::ImGui::Checkbox(const char* szText, bool bCurrentValue)
{
	bool bTheValue = bCurrentValue;
	::ImGui::Checkbox(szText, &bTheValue);
	return bTheValue;
}

void Sakura::Lua::ImGui::SameLine()
{
	::ImGui::SameLine();
}

void Sakura::Lua::ImGui::Spacing()
{
	::ImGui::Spacing();
}

int Sakura::Lua::ImGui::Combo(const char* szText, int iCurrentValue, const char* szOptions)
{
	int iTheValue = iCurrentValue;
	::ImGui::Combo(szText, &iTheValue, szOptions);
	return iTheValue;
}

int Sakura::Lua::ImGui::SliderInt(const char* szText, int iTheValue, int iMinimium, int iMaximum)
{
	::ImGui::SliderInt(szText, &iTheValue, iMinimium, iMaximum);
	return iTheValue;
}

float Sakura::Lua::ImGui::KeyBind(const char* szText, int iKey)
{
	float iTheKey = iKey;
	::Sakura::Menu::HudKeyBind(iTheKey, szText, {}, true);
	return iTheKey;
}

ImVec2 Sakura::Lua::ImGui::GetWindowSize()
{
	return ::ImGui::GetWindowSize();
}

void Sakura::Lua::ImGui::Drawings::AddRect(ImVec2& start, ImVec2& end, ImColor& color, float rounding, int corners, float thickness)
{
	::ImGui::GetWindowDrawList()->AddRect(start, end, color, rounding, corners, thickness);
}
void Sakura::Lua::ImGui::Drawings::AddLine(ImVec2& start, ImVec2& end, ImColor& color, float thickness)
{
	::ImGui::GetWindowDrawList()->AddLine(start, end, color, thickness);
}

void Sakura::Lua::ImGui::Drawings::AddText(ImVec2& position, ImColor& color, const char* szText)
{
	::ImGui::GetWindowDrawList()->AddText(position, color, szText);
}

void Sakura::Lua::ImGui::Drawings::AddRectFilled(ImVec2& start, ImVec2& end, ImColor& color, float rounding, int corners)
{
	::ImGui::GetWindowDrawList()->AddRectFilled(start, end, color, rounding, corners);
}

//position_history_t* Sakura::Lua::Helpers::get_position_history(cl_entity_s* ent) {
//	return ent->ph;
//}
//
//Vector* Sakura::Lua::Helpers::get_attachment(cl_entity_s* ent) {
//	return ent->attachment;
//}
//
//byte* Sakura::Lua::Helpers::get_prevseqblending(latchedvars_t* latched) {
//	return latched->prevseqblending;
//}
//
//byte* Sakura::Lua::Helpers::get_prevcontroller(latchedvars_t* latched) {
//	return latched->prevcontroller;
//}
//
//byte* Sakura::Lua::Helpers::get_prevblending(latchedvars_t* latched) {
//	return latched->prevblending;
//}
//
//byte* Sakura::Lua::Helpers::get_controller(entity_state_t* entityState) {
//	return entityState->controller;
//}
//
//byte* Sakura::Lua::Helpers::get_blending(entity_state_t* entityState) {
//	return entityState->blending;
//}
//
//byte* get_pad(mplane_t* a) {
//	return a->pad;
//}

void DefineLuaGlobal(lua_State* L, const char* name, int value)
{
	lua_pushinteger(L, value);
	lua_setglobal(L, name);
}

bool Sakura::Lua::Init(lua_State* L)
{
	/*Sakura::Lua::pLuaState = luaL_newstate();

	if (!Sakura::Lua::pLuaState)
	{
		Sakura::Lua::Hooks::RemoveAllCallbacks();
		c_Offset.Error("Couldn't initalize lua.");
		return false;
	}
	else
		Sakura::Lua::Hooks::RemoveAllCallbacks();*/

	//luaL_openlibs(Sakura::Lua::pLuaState);

	luabridge::getGlobalNamespace(L)

		.beginClass<ImVec2>("ImVec2")
			.addConstructor<void(*)(float, float)>()
			.addProperty("x", &ImVec2::x)
			.addProperty("y", &ImVec2::y)
		.endClass()

		.beginClass<ImVec4>("ImVec4")
			.addConstructor<void(*)(float, float, float, float)>()
			.addProperty("x", &ImVec4::x)
			.addProperty("y", &ImVec4::y)
			.addProperty("z", &ImVec4::z)
			.addProperty("w", &ImVec4::w)
		.endClass()

		.beginClass<ImColor>("ImColor")
			.addConstructor<void(*)(int, int, int, int)>()
			.addProperty("Value", &ImColor::Value)
		.endClass()

		.beginClass<Vector2D>("Vector2D")
			.addConstructor<void(*)(float, float)>()
			.addProperty("x", &Vector2D::x)
			.addProperty("y", &Vector2D::y)
			.addFunction("Length", &Vector2D::Length)
			.addFunction("Normalize", &Vector2D::Normalize)
			.addFunction("__add", &Vector2D::operator+)
			.addFunction("__sub", &Vector2D::operator-)
			.addFunction("__mul", &Vector2D::operator*)
			.addFunction("__div", &Vector2D::operator/)
		.endClass()

		.beginClass<Vector>("Vector")
			.addConstructor<void(*)(float, float, float)>()
			.addProperty("x", &Vector::x)
			.addProperty("y", &Vector::y)
			.addProperty("z", &Vector::z)
			.addFunction("Length", &Vector::Length)
			.addFunction("Length2D", &Vector::Length2D)
			.addFunction("Normalize", &Vector::Normalize)
			.addFunction("IsZero", &Vector::IsZero)
			.addFunction("IsZero2D", &Vector::IsZero2D)
			.addFunction("Make2D", &Vector::Make2D)
		.endClass()

		.beginClass<usercmd_s>("usercmd")
			.addProperty("lerp_msec", &usercmd_s::lerp_msec)
			.addProperty("msec", &usercmd_s::msec)
			.addProperty("viewangles", &usercmd_s::viewangles)
			.addProperty("forwardmove", &usercmd_s::forwardmove)
			.addProperty("sidemove", &usercmd_s::sidemove)
			.addProperty("upmove", &usercmd_s::upmove)
			.addProperty("lightlevel", &usercmd_s::lightlevel)
			.addProperty("buttons", &usercmd_s::buttons)
			.addProperty("impulse", &usercmd_s::impulse)
			.addProperty("weaponselect", &usercmd_s::weaponselect)
			.addProperty("impact_index", &usercmd_s::impact_index)
			.addProperty("impact_position", &usercmd_s::impact_position)
		.endClass()

		/*.beginClass<position_history_t>("position_history_t")
			.addProperty("animtime", &position_history_t::animtime)
			.addProperty("origin", &position_history_t::origin)
			.addProperty("angles", &position_history_t::angles)
		.endClass()*/

		/*.beginClass<mouth_t>("mouth_t")
			.addProperty("mouthopen", &mouth_t::mouthopen)
			.addProperty("sndcount", &mouth_t::sndcount)
			.addProperty("sndavg", &mouth_t::sndavg)
		.endClass()*/

		/*.beginClass<latchedvars_t>("latchedvars_t")
			.addProperty("prevanimtime", &latchedvars_t::prevanimtime)
			.addProperty("sequencetime", &latchedvars_t::sequencetime)
			.addFunction("get_prevseqblending", &Sakura::Lua::Helpers::get_prevseqblending)
			.addProperty("prevorigin", &latchedvars_t::prevorigin)
			.addProperty("prevangles", &latchedvars_t::prevangles)
			.addProperty("prevsequence", &latchedvars_t::prevsequence)
			.addProperty("prevframe", &latchedvars_t::prevframe)
			.addFunction("get_prevcontroller", &Sakura::Lua::Helpers::get_prevcontroller)
			.addFunction("get_prevblending", &Sakura::Lua::Helpers::get_prevblending)
		.endClass()*/

		/*.beginClass<modtype_t>("modtype_t")
			
			.addData("mod_brush", modtype_t::mod_brush)
			.addProperty("mod_sprite", 1)
			.addProperty("mod_alias", 2)
			.addProperty("mod_studio", 3)
		.endClass()

		.beginClass<model_s>("model_s")
			.addProperty("name", &model_s::name)
			.addProperty("needload", &model_s::needload)
			.addProperty("type", &model_s::type)
		.endClass()*/

		/*.beginClass<mplane_t>("mplane_t")
			.addProperty("normal", &mplane_t::normal)
			.addProperty("dist", &mplane_t::dist)
			.addProperty("type", &mplane_t::type)
			.addProperty("signbits", &mplane_t::signbits)
			.addFunction("get_pad", &get_pad)
		.endClass()*/

		/*.beginClass<entity_state_t>("entity_state")
			.addProperty("entityType", &entity_state_t::entityType)
			.addProperty("number", &entity_state_t::number)
			.addProperty("msg_time", &entity_state_t::msg_time)
			.addProperty("messagenum", &entity_state_t::messagenum)
			.addProperty("origin", &entity_state_t::origin)
			.addProperty("angles", &entity_state_t::angles)
			.addProperty("modelindex", &entity_state_t::modelindex)
			.addProperty("sequence", &entity_state_t::sequence)
			.addProperty("frame", &entity_state_t::frame)
			.addProperty("colormap", &entity_state_t::colormap)
			.addProperty("skin", &entity_state_t::skin)
			.addProperty("solid", &entity_state_t::solid)
			.addProperty("effects", &entity_state_t::effects)
			.addProperty("scale", &entity_state_t::scale)
			.addProperty("eflags", &entity_state_t::eflags)
			.addProperty("rendermode", &entity_state_t::rendermode)
			.addProperty("renderamt", &entity_state_t::renderamt)
			.addProperty("rendercolor", &entity_state_t::rendercolor)
			.addProperty("renderfx", &entity_state_t::renderfx)
			.addProperty("movetype", &entity_state_t::movetype)
			.addProperty("animtime", &entity_state_t::animtime)
			.addProperty("framerate", &entity_state_t::framerate)
			.addProperty("body", &entity_state_t::body)
			.addFunction("get_controller", &Sakura::Lua::Helpers::get_controller)
			.addFunction("get_blending", &Sakura::Lua::Helpers::get_blending)
			.addProperty("velocity", &entity_state_t::velocity)
			.addProperty("mins", &entity_state_t::mins)
			.addProperty("maxs", &entity_state_t::maxs)
			.addProperty("aiment", &entity_state_t::aiment)
			.addProperty("owner", &entity_state_t::owner)
			.addProperty("friction", &entity_state_t::friction)
			.addProperty("gravity", &entity_state_t::gravity)
			.addProperty("team", &entity_state_t::team)
			.addProperty("playerclass", &entity_state_t::playerclass)
			.addProperty("health", &entity_state_t::health)
			.addProperty("spectator", &entity_state_t::spectator)
			.addProperty("weaponmodel", &entity_state_t::weaponmodel)
			.addProperty("gaitsequence", &entity_state_t::gaitsequence)
			.addProperty("basevelocity", &entity_state_t::basevelocity)
			.addProperty("usehull", &entity_state_t::usehull)
			.addProperty("oldbuttons", &entity_state_t::oldbuttons)
			.addProperty("onground", &entity_state_t::onground)
			.addProperty("iStepLeft", &entity_state_t::iStepLeft)
			.addProperty("flFallVelocity", &entity_state_t::flFallVelocity)
			.addProperty("fov", &entity_state_t::fov)
			.addProperty("weaponanim", &entity_state_t::weaponanim)
			.addProperty("startpos", &entity_state_t::startpos)
			.addProperty("endpos", &entity_state_t::endpos)
			.addProperty("impacttime", &entity_state_t::impacttime)
			.addProperty("starttime", &entity_state_t::starttime)
			.addProperty("iuser1", &entity_state_t::iuser1)
			.addProperty("iuser2", &entity_state_t::iuser2)
			.addProperty("iuser3", &entity_state_t::iuser3)
			.addProperty("iuser4", &entity_state_t::iuser4)
			.addProperty("fuser1", &entity_state_t::fuser1)
			.addProperty("fuser2", &entity_state_t::fuser2)
			.addProperty("fuser3", &entity_state_t::fuser3)
			.addProperty("fuser4", &entity_state_t::fuser4)
			.addProperty("vuser1", &entity_state_t::vuser1)
			.addProperty("vuser2", &entity_state_t::vuser2)
			.addProperty("vuser3", &entity_state_t::vuser3)
			.addProperty("vuser4", &entity_state_t::vuser4)
		.endClass()*/

		//.beginClass<cl_entity_s>("entity")
		//	.addProperty("index", &cl_entity_s::index)
		//	.addProperty("player", &cl_entity_s::player)
		//	.addProperty("baseline", &cl_entity_s::baseline)
		//	.addProperty("prevstate", &cl_entity_s::prevstate)
		//	.addProperty("curstate", &cl_entity_s::curstate)
		//	.addProperty("current_position", &cl_entity_s::current_position)
		//	.addFunction("get_position_history", &Sakura::Lua::Helpers::get_position_history)
		//	.addProperty("mouth", &cl_entity_s::mouth)
		//	.addProperty("latched", &cl_entity_s::latched)
		//	.addProperty("lastmove", &cl_entity_s::lastmove)
		//	.addProperty("origin", &cl_entity_s::origin)
		//	.addProperty("angles", &cl_entity_s::angles)
		//	.addFunction("get_attachment", &Sakura::Lua::Helpers::get_attachment)
		//	.addProperty("trivial_accept", &cl_entity_s::trivial_accept)
		//	//.addProperty("model", &cl_entity_s::model)
		//	//.addProperty("efrag", &cl_entity_s::efrag)
		//	//.addProperty("topnode", &cl_entity_s::topnode)
		//	.addProperty("syncbase", &cl_entity_s::syncbase)
		//	.addProperty("visframe", &cl_entity_s::visframe)
		//	//.addProperty("cvFloorColor", &cl_entity_s::cvFloorColor)
		//.endClass()

		.beginNamespace("Hooks")
			.addFunction("Register", &Sakura::Lua::Hooks::RegisterCallBack)
		.endNamespace()

		.beginNamespace("Game")
			.addFunction("WorldToScreen", &Sakura::Lua::Game::WorldToScreen)
			.addFunction("GetLastConvertedToScreenVector", &Sakura::Lua::Game::GetLastConvertedToScreenVector)
			.addFunction("SendPacket", &Sakura::Lua::Game::SendPacket)
			.addFunction("LoadSound", &Sakura::Lua::Game::InitSound)
			.addFunction("PlaySound", &Sakura::Lua::Game::SoundPlay)
			.addFunction("GetTime", &Sakura::Lua::Game::GetTime)
			//.addFunction("CreateVisibleEntity", &Sakura::Lua::Game::CreateVisibleEntity)
		.endNamespace()

		.beginNamespace("ImGui")
			.addFunction("Menu", &Sakura::Lua::ImGui::Menu)
			//.addFunction("End", &Sakura::Lua::ImGui::End)
			.addFunction("Window", &Sakura::Lua::ImGui::Window)
			//.addFunction("WindowEnd", &Sakura::Lua::ImGui::WindowEnd)
			.addFunction("Text", &Sakura::Lua::ImGui::Text)
			.addFunction("Button", &Sakura::Lua::ImGui::Button)
			.addFunction("Checkbox", &Sakura::Lua::ImGui::Checkbox)
			.addFunction("SameLine", &Sakura::Lua::ImGui::SameLine)
			.addFunction("Combo", &Sakura::Lua::ImGui::Combo)
			.addFunction("Slider", &Sakura::Lua::ImGui::SliderInt)
			.addFunction("KeyBind", &Sakura::Lua::ImGui::KeyBind)
			.addFunction("GetWindowSize", &Sakura::Lua::ImGui::GetWindowSize)
		.endNamespace()

		.beginNamespace("Render")
			.addFunction("AddRect", &Sakura::Lua::ImGui::Drawings::AddRect)
			.addFunction("AddLine", &Sakura::Lua::ImGui::Drawings::AddLine)
			.addFunction("AddText", &Sakura::Lua::ImGui::Drawings::AddText)
			.addFunction("AddRectFilled", &Sakura::Lua::ImGui::Drawings::AddRectFilled)
		.endNamespace()

		.beginNamespace("LocalPlayer")
			.addFunction("GetIndex", &Sakura::Lua::LocalPlayer::GetIndex)
			.addFunction("GetTeam", &Sakura::Lua::LocalPlayer::GetTeam)
			.addFunction("GetFlags", &Sakura::Lua::LocalPlayer::GetFlags)
			.addFunction("CheckFlag", &Sakura::Lua::LocalPlayer::CheckFlag)
			.addFunction("GetButtons", &Sakura::Lua::LocalPlayer::GetButtons)
			.addFunction("CheckButton", &Sakura::Lua::LocalPlayer::CheckButton)
			.addFunction("PressButton", &Sakura::Lua::LocalPlayer::PressButton)
			.addFunction("ReleaseButton", &Sakura::Lua::LocalPlayer::ReleaseButton)
			.addFunction("GetViewAngles", &Sakura::Lua::LocalPlayer::GetViewAngles)
			.addFunction("SetViewAngles", &Sakura::Lua::LocalPlayer::SetViewAngles)
			.addFunction("IsAlive", &Sakura::Lua::LocalPlayer::IsAlive)
			.addFunction("IsScoped", &Sakura::Lua::LocalPlayer::IsScoped)

			.addFunction("IsCurWeaponKnife", &Sakura::Lua::LocalPlayer::IsCurWeaponKnife)
			.addFunction("IsCurWeaponPistol", &Sakura::Lua::LocalPlayer::IsCurWeaponPistol)
			.addFunction("IsCurWeaponNade", &Sakura::Lua::LocalPlayer::IsCurWeaponNade)
			.addFunction("IsCurWeaponSniper", &Sakura::Lua::LocalPlayer::IsCurWeaponSniper)
			.addFunction("IsCurWeaponRifle", &Sakura::Lua::LocalPlayer::IsCurWeaponRifle)
			.addFunction("IsCurWeaponShotGun", &Sakura::Lua::LocalPlayer::IsCurWeaponShotGun)
			.addFunction("IsCurWeaponMachineGun", &Sakura::Lua::LocalPlayer::IsCurWeaponMachineGun)
			.addFunction("IsCurWeaponSubMachineGun", &Sakura::Lua::LocalPlayer::IsCurWeaponSubMachineGun)

			.addFunction("GetWeaponName", &Sakura::Lua::LocalPlayer::GetWeaponName)
			.addFunction("GetCommandString", &Sakura::Lua::LocalPlayer::GetCommandString)
			.addFunction("GetCommandFloat", &Sakura::Lua::LocalPlayer::GetCommandFloat)
			.addFunction("ExecuteCommand", &Sakura::Lua::LocalPlayer::ExecuteCommand)

			.addFunction("FixMoveStart", &Sakura::Lua::LocalPlayer::FixMoveStart)
			.addFunction("FixMoveEnd", &Sakura::Lua::LocalPlayer::FixMoveEnd)
		.endNamespace()

		.beginNamespace("Player")
			.addFunction("GetTeam", &Sakura::Lua::Player::GetTeam)
			.addFunction("GetOrigin", &Sakura::Lua::Player::GetOrigin)
			.addFunction("GetName", &Sakura::Lua::Player::GetName)
			.addFunction("GetModelName", &Sakura::Lua::Player::GetModelName)
			.addFunction("GetDistance", &Sakura::Lua::Player::GetDistance)
			.addFunction("GetActualDistance", &Sakura::Lua::Player::GetActualDistance)
			.addFunction("GetPing", &Sakura::Lua::Player::GetPing)
			.addFunction("IsAlive", &Sakura::Lua::Player::IsAlive)
		.endNamespace()

		.beginNamespace("Notify")
			.addFunction("Create", &Sakura::Lua::Notify::Create)
		.endNamespace()
		;

	DefineLuaGlobal(L, "SAKURA_MENU_RENDER", SAKURA_CALLBACK_AT_RENDERING_MENU);
	DefineLuaGlobal(L, "SAKURA_WINDOW_RENDER", SAKURA_CALLBACK_AT_RENDERING_WINDOW);
	DefineLuaGlobal(L, "SAKURA_BACKGROUND_RENDER", SAKURA_CALLBACK_AT_RENDERING_BACKGROUND);
	DefineLuaGlobal(L, "SAKURA_CLIENT_MOVE", SAKURA_CALLBACK_AT_CLIENT_MOVE);
	DefineLuaGlobal(L, "SAKURA_CLIENT_BIND", SAKURA_CALLBACK_AT_CLIENT_BIND);
	//DefineLuaGlobal(L, "SAKURA_CALLBACK_AT_CLIENT_ADDENTITY", SAKURA_CALLBACK_AT_CLIENT_ADDENTITY);
	DefineLuaGlobal(L, "SAKURA_DEATH_MESSAGE", SAKURA_CALLBACK_AT_DEATH_MESSAGE);
	DefineLuaGlobal(L, "SAKURA_NEWROUND_MESSAGE", SAKURA_CALLBACK_AT_RESETHUD_MESSAGE);
	DefineLuaGlobal(L, "SAKURA_SELFDAMAGE_MESSAGE", SAKURA_CALLBACK_AT_DAMAGE_MESSAGE);
	DefineLuaGlobal(L, "SAKURA_CALLBACK_AT_INIT_BASS", SAKURA_CALLBACK_AT_INIT_BASS);

	DefineLuaGlobal(L, "ENTITY_TYPE_NORMAL", ENTITY_TYPE_NORMAL);
	DefineLuaGlobal(L, "ENTITY_TYPE_PLAYER", ENTITY_TYPE_PLAYER);

	DefineLuaGlobal(L, "FL_FLY", FL_FLY);
	DefineLuaGlobal(L, "FL_SWIM", FL_SWIM);
	DefineLuaGlobal(L, "FL_CONVEYOR", FL_CONVEYOR);
	DefineLuaGlobal(L, "FL_CLIENT", FL_CLIENT);
	DefineLuaGlobal(L, "FL_INWATER", FL_INWATER);
	DefineLuaGlobal(L, "FL_MONSTER", FL_MONSTER);
	DefineLuaGlobal(L, "FL_GODMODE", FL_GODMODE);
	DefineLuaGlobal(L, "FL_NOTARGET", FL_NOTARGET);
	DefineLuaGlobal(L, "FL_SKIPLOCALHOST", FL_SKIPLOCALHOST);
	DefineLuaGlobal(L, "FL_ONGROUND", FL_ONGROUND);
	DefineLuaGlobal(L, "FL_PARTIALGROUND", FL_PARTIALGROUND);
	DefineLuaGlobal(L, "FL_WATERJUMP", FL_WATERJUMP);
	DefineLuaGlobal(L, "FL_FROZEN", FL_FROZEN);
	DefineLuaGlobal(L, "FL_FAKECLIENT", FL_FAKECLIENT);
	DefineLuaGlobal(L, "FL_DUCKING", FL_DUCKING);
	DefineLuaGlobal(L, "FL_FLOAT", FL_FLOAT);
	DefineLuaGlobal(L, "FL_GRAPHED", FL_GRAPHED);
	DefineLuaGlobal(L, "FL_IMMUNE_WATER", FL_IMMUNE_WATER);
	DefineLuaGlobal(L, "FL_IMMUNE_SLIME", FL_IMMUNE_SLIME);
	DefineLuaGlobal(L, "FL_IMMUNE_LAVA", FL_IMMUNE_LAVA);
	DefineLuaGlobal(L, "FL_PROXY", FL_PROXY);
	DefineLuaGlobal(L, "FL_ALWAYSTHINK", FL_ALWAYSTHINK);
	DefineLuaGlobal(L, "FL_BASEVELOCITY", FL_BASEVELOCITY);
	DefineLuaGlobal(L, "FL_MONSTERCLIP", FL_MONSTERCLIP);
	DefineLuaGlobal(L, "FL_ONTRAIN", FL_ONTRAIN);
	DefineLuaGlobal(L, "FL_WORLDBRUSH", FL_WORLDBRUSH);
	DefineLuaGlobal(L, "FL_SPECTATOR", FL_SPECTATOR);
	DefineLuaGlobal(L, "FL_CUSTOMENTITY", FL_CUSTOMENTITY);
	DefineLuaGlobal(L, "FL_KILLME", FL_KILLME);
	DefineLuaGlobal(L, "FL_DORMANT", FL_DORMANT);

	DefineLuaGlobal(L, "K_TAB", K_TAB);
	DefineLuaGlobal(L, "K_ENTER", K_ENTER);
	DefineLuaGlobal(L, "K_ESCAPE", K_ESCAPE);
	DefineLuaGlobal(L, "K_SPACE", K_SPACE);
	DefineLuaGlobal(L, "K_0", K_0);
	DefineLuaGlobal(L, "K_1", K_1);
	DefineLuaGlobal(L, "K_2", K_2);
	DefineLuaGlobal(L, "K_3", K_3);
	DefineLuaGlobal(L, "K_4", K_4);
	DefineLuaGlobal(L, "K_5", K_5);
	DefineLuaGlobal(L, "K_6", K_6);
	DefineLuaGlobal(L, "K_7", K_7);
	DefineLuaGlobal(L, "K_8", K_8);
	DefineLuaGlobal(L, "K_9", K_9);
	DefineLuaGlobal(L, "K_A", K_A);
	DefineLuaGlobal(L, "K_B", K_B);
	DefineLuaGlobal(L, "K_C", K_C);
	DefineLuaGlobal(L, "K_D", K_D);
	DefineLuaGlobal(L, "K_E", K_E);
	DefineLuaGlobal(L, "K_F", K_F);
	DefineLuaGlobal(L, "K_G", K_G);
	DefineLuaGlobal(L, "K_H", K_H);
	DefineLuaGlobal(L, "K_I", K_I);
	DefineLuaGlobal(L, "K_J", K_J);
	DefineLuaGlobal(L, "K_K", K_K);
	DefineLuaGlobal(L, "K_L", K_L);
	DefineLuaGlobal(L, "K_M", K_M);
	DefineLuaGlobal(L, "K_N", K_N);
	DefineLuaGlobal(L, "K_O", K_O);
	DefineLuaGlobal(L, "K_P", K_P);
	DefineLuaGlobal(L, "K_Q", K_Q);
	DefineLuaGlobal(L, "K_R", K_R);
	DefineLuaGlobal(L, "K_S", K_S);
	DefineLuaGlobal(L, "K_T", K_T);
	DefineLuaGlobal(L, "K_U", K_U);
	DefineLuaGlobal(L, "K_V", K_V);
	DefineLuaGlobal(L, "K_W", K_W);
	DefineLuaGlobal(L, "K_X", K_X);
	DefineLuaGlobal(L, "K_Y", K_Y);
	DefineLuaGlobal(L, "K_Z", K_Z);
	DefineLuaGlobal(L, "K_BACKSPACE", K_BACKSPACE);
	DefineLuaGlobal(L, "K_UPARROW", K_UPARROW);
	DefineLuaGlobal(L, "K_DOWNARROW", K_DOWNARROW);
	DefineLuaGlobal(L, "K_LEFTARROW", K_LEFTARROW);
	DefineLuaGlobal(L, "K_RIGHTARROW", K_RIGHTARROW);
	DefineLuaGlobal(L, "K_ALT", K_ALT);
	DefineLuaGlobal(L, "K_CTRL", K_CTRL);
	DefineLuaGlobal(L, "K_SHIFT", K_SHIFT);
	DefineLuaGlobal(L, "K_F1", K_F1);
	DefineLuaGlobal(L, "K_F2", K_F2);
	DefineLuaGlobal(L, "K_F3", K_F3);
	DefineLuaGlobal(L, "K_F4", K_F4);
	DefineLuaGlobal(L, "K_F5", K_F5);
	DefineLuaGlobal(L, "K_F6", K_F6);
	DefineLuaGlobal(L, "K_F7", K_F7);
	DefineLuaGlobal(L, "K_F8", K_F8);
	DefineLuaGlobal(L, "K_F9", K_F9);
	DefineLuaGlobal(L, "K_F10", K_F10);
	DefineLuaGlobal(L, "K_F11", K_F11);
	DefineLuaGlobal(L, "K_F12", K_F12);
	DefineLuaGlobal(L, "K_INS", K_INS);
	DefineLuaGlobal(L, "K_DEL", K_DEL);
	DefineLuaGlobal(L, "K_PGDN", K_PGDN);
	DefineLuaGlobal(L, "K_PGUP", K_PGUP);
	DefineLuaGlobal(L, "K_HOME", K_HOME);
	DefineLuaGlobal(L, "K_END", K_END);
	DefineLuaGlobal(L, "K_KP_HOME", K_KP_HOME);
	DefineLuaGlobal(L, "K_KP_UPARROW", K_KP_UPARROW);
	DefineLuaGlobal(L, "K_KP_PGUP", K_KP_PGUP);
	DefineLuaGlobal(L, "K_KP_LEFTARROW", K_KP_LEFTARROW);
	DefineLuaGlobal(L, "K_KP_5", K_KP_5);
	DefineLuaGlobal(L, "K_KP_RIGHTARROW", K_KP_RIGHTARROW);
	DefineLuaGlobal(L, "K_KP_END", K_KP_END);
	DefineLuaGlobal(L, "K_KP_DOWNARROW", K_KP_DOWNARROW);
	DefineLuaGlobal(L, "K_KP_PGDN", K_KP_PGDN);
	DefineLuaGlobal(L, "K_KP_ENTER", K_KP_ENTER);
	DefineLuaGlobal(L, "K_KP_INS", K_KP_INS);
	DefineLuaGlobal(L, "K_KP_DEL", K_KP_DEL);
	DefineLuaGlobal(L, "K_KP_SLASH", K_KP_SLASH);
	DefineLuaGlobal(L, "K_KP_MINUS", K_KP_MINUS);
	DefineLuaGlobal(L, "K_KP_PLUS", K_KP_PLUS);
	DefineLuaGlobal(L, "K_CAPSLOCK", K_CAPSLOCK);
	DefineLuaGlobal(L, "K_MWHEELDOWN", K_MWHEELDOWN);
	DefineLuaGlobal(L, "K_MWHEELUP", K_MWHEELUP);
	DefineLuaGlobal(L, "K_MOUSE1", K_MOUSE1);
	DefineLuaGlobal(L, "K_MOUSE2", K_MOUSE2);
	DefineLuaGlobal(L, "K_MOUSE3", K_MOUSE3);
	DefineLuaGlobal(L, "K_MOUSE4", K_MOUSE4);
	DefineLuaGlobal(L, "K_MOUSE5", K_MOUSE5);
	DefineLuaGlobal(L, "K_PAUSE", K_PAUSE);

	DefineLuaGlobal(L, "IN_ATTACK", IN_ATTACK);
	DefineLuaGlobal(L, "IN_JUMP", IN_JUMP);
	DefineLuaGlobal(L, "IN_DUCK", IN_DUCK);
	DefineLuaGlobal(L, "IN_FORWARD", IN_FORWARD);
	DefineLuaGlobal(L, "IN_BACK", IN_BACK);
	DefineLuaGlobal(L, "IN_USE", IN_USE);
	DefineLuaGlobal(L, "IN_CANCEL", IN_CANCEL);
	DefineLuaGlobal(L, "IN_LEFT", IN_LEFT);
	DefineLuaGlobal(L, "IN_RIGHT", IN_RIGHT);
	DefineLuaGlobal(L, "IN_MOVELEFT", IN_MOVELEFT);
	DefineLuaGlobal(L, "IN_MOVERIGHT", IN_MOVERIGHT);
	DefineLuaGlobal(L, "IN_ATTACK2", IN_ATTACK2);
	DefineLuaGlobal(L, "IN_RUN", IN_RUN);
	DefineLuaGlobal(L, "IN_RELOAD", IN_RELOAD);
	DefineLuaGlobal(L, "IN_ALT1", IN_ALT1);
	DefineLuaGlobal(L, "IN_SCORE", IN_SCORE);

	DefineLuaGlobal(L, "ImGuiWindowFlags_None", ImGuiWindowFlags_None);
	DefineLuaGlobal(L, "ImGuiWindowFlags_NoTitleBar", ImGuiWindowFlags_NoTitleBar);
	DefineLuaGlobal(L, "ImGuiWindowFlags_NoResize", ImGuiWindowFlags_NoResize);
	DefineLuaGlobal(L, "ImGuiWindowFlags_NoMove", ImGuiWindowFlags_NoMove);
	DefineLuaGlobal(L, "ImGuiWindowFlags_NoScrollbar", ImGuiWindowFlags_NoScrollbar);
	DefineLuaGlobal(L, "ImGuiWindowFlags_NoScrollWithMouse", ImGuiWindowFlags_NoScrollWithMouse);
	DefineLuaGlobal(L, "ImGuiWindowFlags_NoCollapse", ImGuiWindowFlags_NoCollapse);
	DefineLuaGlobal(L, "ImGuiWindowFlags_AlwaysAutoResize", ImGuiWindowFlags_AlwaysAutoResize);
	DefineLuaGlobal(L, "ImGuiWindowFlags_NoBackground", ImGuiWindowFlags_NoBackground);
	DefineLuaGlobal(L, "ImGuiWindowFlags_NoSavedSettings", ImGuiWindowFlags_NoSavedSettings);
	DefineLuaGlobal(L, "ImGuiWindowFlags_NoMouseInputs", ImGuiWindowFlags_NoMouseInputs);
	DefineLuaGlobal(L, "ImGuiWindowFlags_MenuBar", ImGuiWindowFlags_MenuBar);
	DefineLuaGlobal(L, "ImGuiWindowFlags_HorizontalScrollbar", ImGuiWindowFlags_HorizontalScrollbar);
	DefineLuaGlobal(L, "ImGuiWindowFlags_NoFocusOnAppearing", ImGuiWindowFlags_NoFocusOnAppearing);
	DefineLuaGlobal(L, "ImGuiWindowFlags_NoBringToFrontOnFocus", ImGuiWindowFlags_NoBringToFrontOnFocus);
	DefineLuaGlobal(L, "ImGuiWindowFlags_AlwaysVerticalScrollbar", ImGuiWindowFlags_AlwaysVerticalScrollbar);
	DefineLuaGlobal(L, "ImGuiWindowFlags_AlwaysHorizontalScrollbar", ImGuiWindowFlags_AlwaysHorizontalScrollbar);
	DefineLuaGlobal(L, "ImGuiWindowFlags_AlwaysUseWindowPadding", ImGuiWindowFlags_AlwaysUseWindowPadding);
	DefineLuaGlobal(L, "ImGuiWindowFlags_NoNavInputs", ImGuiWindowFlags_NoNavInputs);
	DefineLuaGlobal(L, "ImGuiWindowFlags_NoNavFocus", ImGuiWindowFlags_NoNavFocus);
	DefineLuaGlobal(L, "ImGuiWindowFlags_UnsavedDocument", ImGuiWindowFlags_UnsavedDocument);
	DefineLuaGlobal(L, "ImGuiWindowFlags_NoNav", ImGuiWindowFlags_NoNav);
	DefineLuaGlobal(L, "ImGuiWindowFlags_NoDecoration", ImGuiWindowFlags_NoDecoration);
	DefineLuaGlobal(L, "ImGuiWindowFlags_NoInputs", ImGuiWindowFlags_NoInputs);

	return true;
}

int panic_function(lua_State* L)
{
	const char* error_msg = lua_tostring(L, -1);
	const char* source_file = lua_tostring(L, 2);
	int line_number = lua_tointeger(L, 3);
	LogToFile("Lua script error: %s (%s:%d)", error_msg, source_file, line_number);
	//Toast::Create({ 7, "An error occured in lua script! Check the logs!" });
	return 0;
}

void Sakura::Lua::Reload()
{
	scripts.clear();

	const std::string hackDir = hackdir;
	const std::string scriptExtension = ".lua";

	for (const auto& p : std::filesystem::recursive_directory_iterator(hackDir + "\\scripts\\"))
	{
		if (p.path().extension() != scriptExtension)
			continue;

		lua_State* L = luaL_newstate();

		if (!L)
		{
			LogToFile("Error creating Lua state for script: %s", p.path().filename().string().c_str());
			continue;
		}

		luaL_openlibs(L);

		Init(L);

		lua_atpanic(L, panic_function);

		if (luaL_loadfile(L, p.path().string().c_str()) != LUA_OK)
		{
			const char* error_msg = lua_tostring(L, -1);
			LogToFile("Error loading Lua script: %s", error_msg);
			lua_close(L);
			continue;
		}

		LuaScripts script(L);
		scripts.push_back(script);

		if (lua_pcall(L, 0, 0, 0) != LUA_OK)
		{
			const char* error_msg = lua_tostring(L, -1);
			LogToFile("Error running Lua script: %s", error_msg);
			lua_close(L);
			continue;
		}

		currentScriptIndex++;

		LogToFile("Loaded Lua script: %s", p.path().filename().string().c_str());
		ScriptsCount++;
	}

	/*if (Sakura::Lua::pLuaState)
	{
		lua_close(Sakura::Lua::pLuaState);
		Sakura::Lua::pLuaState = 0;
	}

	if (Sakura::Lua::Init())
	{
		const std::string hackDir = hackdir;
		const std::string scriptExtension = ".lua";

		lua_atpanic(Sakura::Lua::pLuaState, panic_function);

		for (const auto& p : std::filesystem::recursive_directory_iterator(hackDir + "\\scripts\\"))
		{
			std::string temp = p.path().stem().string() + scriptExtension;

			if (p.path().extension() == scriptExtension)
			{
				if (luaL_loadfile(Sakura::Lua::pLuaState, p.path().string().c_str()) == LUA_OK)
				{
					if (lua_pcall(Sakura::Lua::pLuaState, 0, 0, 0) == LUA_OK)
					{
						LogToFile("Loaded Lua script: %s", p.path().filename().string().c_str());
						ScriptsCount++;
					}
				}
				else
				{
					const char* error_msg = lua_tostring(Sakura::Lua::pLuaState, -1);
					LogToFile("Error loading Lua script: %s", error_msg);
					Toast::Create({ 7, "An error occured in lua script! Check the logs!" });
				}
			}
		}
	}*/
}