#include "../../client.h"

int Sakura::Lua::ScriptsCount = 0;
int Sakura::Lua::currentScriptIndex = 0;

std::vector<Sakura::Lua::LuaScripts> Sakura::Lua::scripts;

std::vector<HSAMPLE> Sakura::Lua::Sounds;

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

	HSAMPLE sample = BASS_SampleLoad(false, temp, 0, 0, 60000, 0);

	if (!sample)
		Sakura::Log::File("Failed to load sound '%s' from lua. Error code: %i.", filename, BASS_ErrorGetCode());

	Sounds.push_back(sample);

	return sample;
}

void Sakura::Lua::Game::SoundPlay(DWORD sound, const float volume)
{
	BASS_SAMPLE sampleInfo;
	BASS_SampleGetInfo(sound, &sampleInfo);

	sampleInfo.volume = volume;
	BASS_SampleSetInfo(sound, &sampleInfo);

	HCHANNEL channel = BASS_SampleGetChannel(sound, false);

	BASS_ChannelPlay(channel, false);
}

bool Sakura::Lua::Game::CreateVisibleEntity(const int entityType, const int entityIndexToCopy, Vector origin, const bool checkPlayerEntity)
{
	cl_entity_s* entity = g_Engine.GetEntityByIndex(entityIndexToCopy);

	if (!entity)
		return false;

	if (checkPlayerEntity && !entity->player)
		return false;

	entity->origin = origin;

	g_Engine.CL_CreateVisibleEntity(entityType, entity);

	return true;
}

void Sakura::Lua::Game::CreateBeamPoint(Vector start, Vector end, const ImColor color, const float life, const float width, const float amplitude, const float speed, const int startFrame, const float framerate)
{
	int beamindex = g_Engine.pEventAPI->EV_FindModelIndex("sprites/laserbeam.spr");

	g_Engine.pEfxAPI->R_BeamPoints(start, end, beamindex, life, width, amplitude, color.Value.w, speed, startFrame, framerate, color.Value.x, color.Value.y, color.Value.z);
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

int Sakura::Lua::LocalPlayer::GetHealth()
{
	return g_Local.iPrevHealth;
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

Vector Sakura::Lua::LocalPlayer::GetOrigin()
{
	return pmove->origin;
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

float Sakura::Lua::LocalPlayer::GetCommandFloat(const char* command)
{
	char fullCommand[64];
	sprintf(fullCommand, "%s", command);
	return g_Engine.pfnGetCvarFloat(fullCommand);
}

int Sakura::Lua::LocalPlayer::GetCommandInt(const char* command)
{
	char fullCommand[64];
	sprintf(fullCommand, "%s", command);
	return static_cast<int>(g_Engine.pfnGetCvarFloat(fullCommand));
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
		case WEAPON_HEGRENADE:	return "HE Grenade"; break;
		case WEAPON_SMOKEGRENADE: return"SG Grenade"; break;
		case WEAPON_FLASHBANG:	return "Flashbang"; break;
		case WEAPON_KNIFE:		return "Knife"; break;
		default:				return "Unknown"; break;
		}
	}

	return "Unknown";
}

int Sakura::Lua::LocalPlayer::GetWeaponID()
{
	return g_Local.weapon.m_iWeaponID;
}

int Sakura::Lua::Player::GetTeam(int index)
{
	if (index < 1 || index >= 32)
		return 0;

	return g_Player[index].iTeam;
}

Vector Sakura::Lua::Player::GetOrigin(int index)
{
	if (index < 1 || index >= 32)
		return Vector(9999, 0, 0);

	cl_entity_s* player = g_Engine.GetEntityByIndex(index);
	return player->origin;
}

int Sakura::Lua::Player::GetHealth(int index)
{
	if (index < 1 || index >= 32)
		return 0;

	return g_Player[index].iHealth;
}

std::string Sakura::Lua::Player::GetName(int index)
{
	if (index < 1 || index >= 32)
		return "Unknown";

	player_info_s* player = g_Studio.PlayerInfo(index - 1);
	return player->name;
}

std::string Sakura::Lua::Player::GetModelName(int index)
{
	if (index < 1 || index >= 32)
		return "Unknown";

	return PlayerEsp[index].model;
}

int Sakura::Lua::Player::GetDistance(int index)
{
	if (index < 1 || index >= 32)
		return 0;

	cl_entity_s* player = g_Engine.GetEntityByIndex(index);

	Vector vDifference = player->origin - Sakura::Lua::LocalPlayer::GetEyePosition();
	int iDistance = int(vDifference.Length() / 22.0f);
	return iDistance;
}

float Sakura::Lua::Player::GetActualDistance(int index)
{
	if (index < 1 || index >= 32)
		return 0;

	cl_entity_s* player = g_Engine.GetEntityByIndex(index);

	Vector vDifference = player->origin - Sakura::Lua::LocalPlayer::GetEyePosition();
	return vDifference.Length();
}

int Sakura::Lua::Player::GetPing(int index)
{
	if (index < 1 || index >= 32)
		return 0;

	player_info_s* player = g_Studio.PlayerInfo(index - 1);
	return player->ping;
}

bool Sakura::Lua::Player::IsAlive(int index)
{
	if (index < 1 || index >= 32)
		return 0;

	return ::Sakura::Player::IsAlive(index);
}

void Sakura::Lua::Notify::Create(const char* szTitle, const int secondsDisplay = 3)
{
	Toast::Create({ secondsDisplay, szTitle });
}

//void Sakura::Lua::ImGui::Menu(const char* szTitle, luabridge::LuaRef lfFunction)
//{
//	if (::ImGui::BeginTabItem(szTitle, 0, 0))
//	{
//		try
//		{
//			lfFunction();
//		}
//		catch (luabridge::LuaException const& error)
//		{
//			LogToFile("Lua script error: %s", error.what());
//		}
//		::ImGui::EndTabItem();
//	}
//}

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
			Sakura::Log::File("Lua script error: %s", error.what());
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

ImColor Sakura::Lua::ImGui::Color(const char* szText, ImColor& color)
{
	::Sakura::Menu::Widgets::ColorEdit(szText, (float*)&color, ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaBar);
	return color;
}

ImVec2 Sakura::Lua::ImGui::CalcTextSize(const char* label)
{
	return ::ImGui::CalcTextSize(label);
}

ImVec2 Sakura::Lua::ImGui::GetWindowSize()
{
	return ::ImGui::GetWindowSize();
}

void Sakura::Lua::ImGui::Drawings::AddRect(ImVec2& start, ImVec2& end, ImColor& color, float rounding, int flags, float thickness)
{
	::ImGui::GetWindowDrawList()->AddRect(start, end, color, rounding, flags, thickness);
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

//void Sakura::Lua::Settings::SaveInt(const std::string name, int value)
//{
//	LogToFile("Saving int from lua: %i", value);
//	std::string luacvar = "lua_" + name;
//	AddCvarFloat(luacvar.c_str(), &value);
//}
//
//void Sakura::Lua::Settings::SaveFloat(const std::string name, float value)
//{
//	LogToFile("Saving float from lua: %.1f", value);
//	std::string luacvar = "lua_" + name;
//	AddCvarFloat(luacvar.c_str(), &value);
//}
//
//void Sakura::Lua::Settings::SaveBool(const std::string name, bool value)
//{
//	LogToFile("Saving bool from lua: %.0f", &value);
//	std::string luacvar = "lua_" + name;
//	AddCvarFloat(luacvar.c_str(), &value);
//}
//
//int Sakura::Lua::Settings::LoadInt(const std::string name, const int value)
//{
//	std::string luacvar = "lua_" + name;
//
//	for (names.it_start(); names.it_running(); names.it_next())
//	{
//		if (strcmp(names.str, luacvar.c_str()) != 0)
//			continue;
//
//		int index = names.num;
//
//		if (entries[index].data == nullptr)
//			break;
//
//		int* floatPtr = static_cast<int*>(entries[index].data);
//		return *floatPtr;
//	}
//
//	return value; // return the default value
//}
//
//float Sakura::Lua::Settings::LoadFloat(const std::string name, const float value)
//{
//	std::string luacvar = "lua_" + name;
//
//	for (names.it_start(); names.it_running(); names.it_next())
//	{
//		if (strcmp(names.str, luacvar.c_str()) != 0)
//			continue;
//
//		int index = names.num;
//
//		if (entries[index].data == nullptr)
//			break;
//
//		float* floatPtr = static_cast<float*>(entries[index].data);
//		return *floatPtr;
//	}
//
//	return value; // return the default value
//}
//
//bool Sakura::Lua::Settings::LoadBool(const std::string name, const bool value)
//{
//	std::string luacvar = "lua_" + name;
//
//	for (names.it_start(); names.it_running(); names.it_next())
//	{
//		if (strcmp(names.str, luacvar.c_str()) != 0)
//			continue;
//
//		int index = names.num;
//
//		if (entries[index].data == nullptr)
//			break;
//
//		bool* floatPtr = static_cast<bool*>(entries[index].data);
//		return *floatPtr;
//	}
//
//	return value; // return the default value
//}

void Sakura::Lua::DynamicSound::ChangeNextSoundVolume(float volume)
{
	::Sakura::Esp::ChangeDynamicSoundVolume(volume);
}

void DefineLuaGlobal(lua_State* L, const char* name, int value)
{
	lua_pushinteger(L, value);
	lua_setglobal(L, name);
}

bool Sakura::Lua::Init(lua_State* L)
{
	luabridge::enableExceptions(L);
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

		/*.beginClass<colorVec>("colorVec")
			.addProperty("r", &colorVec::r)
			.addProperty("g", &colorVec::g)
			.addProperty("b", &colorVec::b)
			.addProperty("a", &colorVec::a)
		.endClass()*/

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
			.addFunction("CreateVisibleEntity", &Sakura::Lua::Game::CreateVisibleEntity)
			.addFunction("CreateBeamPoint", &Sakura::Lua::Game::CreateBeamPoint)
			.addFunction("ChangeNextSoundVolume", &Sakura::Lua::DynamicSound::ChangeNextSoundVolume)
		.endNamespace()

		.beginNamespace("ImGui")
			//.addFunction("Menu", &Sakura::Lua::ImGui::Menu)
			.addFunction("Window", &Sakura::Lua::ImGui::Window)
			.addFunction("Text", &Sakura::Lua::ImGui::Text)
			.addFunction("Button", &Sakura::Lua::ImGui::Button)
			.addFunction("Checkbox", &Sakura::Lua::ImGui::Checkbox)
			.addFunction("SameLine", &Sakura::Lua::ImGui::SameLine)
			.addFunction("Combo", &Sakura::Lua::ImGui::Combo)
			.addFunction("Slider", &Sakura::Lua::ImGui::SliderInt)
			.addFunction("KeyBind", &Sakura::Lua::ImGui::KeyBind)
			.addFunction("Color", &Sakura::Lua::ImGui::Color)

			.addFunction("GetWindowSize", &Sakura::Lua::ImGui::GetWindowSize)
			.addFunction("CalcTextSize", &Sakura::Lua::ImGui::CalcTextSize)
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
			.addFunction("GetOrigin", &Sakura::Lua::LocalPlayer::GetOrigin)
			.addFunction("GetHealth", &Sakura::Lua::LocalPlayer::GetHealth)
			.addFunction("GetViewAngles", &Sakura::Lua::LocalPlayer::GetViewAngles)
			.addFunction("SetViewAngles", &Sakura::Lua::LocalPlayer::SetViewAngles)
			.addFunction("IsAlive", &Sakura::Lua::LocalPlayer::IsAlive)
			.addFunction("IsScoped", &Sakura::Lua::LocalPlayer::IsScoped)
			.addFunction("IsInGame", &Sakura::Player::Local::InGame)

			.addFunction("IsCurWeaponKnife", &Sakura::Lua::LocalPlayer::IsCurWeaponKnife)
			.addFunction("IsCurWeaponPistol", &Sakura::Lua::LocalPlayer::IsCurWeaponPistol)
			.addFunction("IsCurWeaponNade", &Sakura::Lua::LocalPlayer::IsCurWeaponNade)
			.addFunction("IsCurWeaponSniper", &Sakura::Lua::LocalPlayer::IsCurWeaponSniper)
			.addFunction("IsCurWeaponRifle", &Sakura::Lua::LocalPlayer::IsCurWeaponRifle)
			.addFunction("IsCurWeaponShotGun", &Sakura::Lua::LocalPlayer::IsCurWeaponShotGun)
			.addFunction("IsCurWeaponMachineGun", &Sakura::Lua::LocalPlayer::IsCurWeaponMachineGun)
			.addFunction("IsCurWeaponSubMachineGun", &Sakura::Lua::LocalPlayer::IsCurWeaponSubMachineGun)

			.addFunction("GetWeaponName", &Sakura::Lua::LocalPlayer::GetWeaponName)
			.addFunction("GetWeaponID", &Sakura::Lua::LocalPlayer::GetWeaponID)
			.addFunction("GetCommandString", &Sakura::Lua::LocalPlayer::GetCommandString)
			.addFunction("GetCommandFloat", &Sakura::Lua::LocalPlayer::GetCommandFloat)
			.addFunction("GetCommandInt", &Sakura::Lua::LocalPlayer::GetCommandInt)
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
			.addFunction("GetHealth", &Sakura::Lua::Player::GetHealth)
			.addFunction("IsAlive", &Sakura::Lua::Player::IsAlive)
		.endNamespace()

		/*.beginNamespace("Settings")
			.addFunction("SaveInt", &Sakura::Lua::Settings::SaveInt)
			.addFunction("SaveFloat", &Sakura::Lua::Settings::SaveFloat)
			.addFunction("SaveBool", &Sakura::Lua::Settings::SaveBool)

			.addFunction("LoadInt", &Sakura::Lua::Settings::LoadInt)
			.addFunction("LoadFloat", &Sakura::Lua::Settings::LoadFloat)
			.addFunction("LoadBool", &Sakura::Lua::Settings::LoadBool)
		.endNamespace()*/

		.beginNamespace("Notify")
			.addFunction("Create", &Sakura::Lua::Notify::Create)
		.endNamespace()
		;

	DefineLuaGlobal(L, "SAKURA_MENU_RENDER", SAKURA_CALLBACK_AT_RENDERING_MENU);
	DefineLuaGlobal(L, "SAKURA_WINDOW_RENDER", SAKURA_CALLBACK_AT_RENDERING_WINDOW);
	DefineLuaGlobal(L, "SAKURA_BACKGROUND_RENDER", SAKURA_CALLBACK_AT_RENDERING_BACKGROUND);
	DefineLuaGlobal(L, "SAKURA_CLIENT_MOVE", SAKURA_CALLBACK_AT_CLIENT_MOVE);
	DefineLuaGlobal(L, "SAKURA_CLIENT_BIND", SAKURA_CALLBACK_AT_CLIENT_BIND);
	DefineLuaGlobal(L, "SAKURA_DEATH_MESSAGE", SAKURA_CALLBACK_AT_DEATH_MESSAGE);
	DefineLuaGlobal(L, "SAKURA_NEWROUND_MESSAGE", SAKURA_CALLBACK_AT_RESETHUD_MESSAGE);
	DefineLuaGlobal(L, "SAKURA_SELFDAMAGE_MESSAGE", SAKURA_CALLBACK_AT_DAMAGE_MESSAGE);
	DefineLuaGlobal(L, "SAKURA_ADD_ENTITY", SAKURA_CALLBACK_AT_ADDENTITY);
	DefineLuaGlobal(L, "SAKURA_DYNAMICSOUND_PLAY", SAKURA_CALLBACK_AT_DYNAMICSOUND);
	DefineLuaGlobal(L, "SAKURA_SOUND_INIT", SAKURA_CALLBACK_AT_INIT_BASS);
	//DefineLuaGlobal(L, "SAKURA_LOAD_CONFIG", SAKURA_CALLBACK_AT_LOAD_CONFIG);
	//DefineLuaGlobal(L, "SAKURA_SAVE_CONFIG", SAKURA_CALLBACK_AT_SAVE_CONFIG);

	DefineLuaGlobal(L, "TEAM_TT", TEAM_TT);
	DefineLuaGlobal(L, "TEAM_CT", TEAM_CT);

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

	DefineLuaGlobal(L, "WEAPON_NONE", WEAPON_NONE);
	DefineLuaGlobal(L, "WEAPON_P228", WEAPON_P228);
	DefineLuaGlobal(L, "WEAPON_GLOCK", WEAPON_GLOCK);
	DefineLuaGlobal(L, "WEAPON_SCOUT", WEAPON_SCOUT);
	DefineLuaGlobal(L, "WEAPON_HEGRENADE", WEAPON_HEGRENADE);
	DefineLuaGlobal(L, "WEAPON_XM1014", WEAPON_XM1014);
	DefineLuaGlobal(L, "WEAPON_C4", WEAPON_C4);
	DefineLuaGlobal(L, "WEAPON_MAC10", WEAPON_MAC10);
	DefineLuaGlobal(L, "WEAPON_AUG", WEAPON_AUG);
	DefineLuaGlobal(L, "WEAPON_SMOKEGRENADE", WEAPON_SMOKEGRENADE);
	DefineLuaGlobal(L, "WEAPON_ELITE", WEAPON_ELITE);
	DefineLuaGlobal(L, "WEAPON_FIVESEVEN", WEAPON_FIVESEVEN);
	DefineLuaGlobal(L, "WEAPON_UMP45", WEAPON_UMP45);
	DefineLuaGlobal(L, "WEAPON_SG550", WEAPON_SG550);
	DefineLuaGlobal(L, "WEAPON_GALIL", WEAPON_GALIL);
	DefineLuaGlobal(L, "WEAPON_FAMAS", WEAPON_FAMAS);
	DefineLuaGlobal(L, "WEAPON_USP", WEAPON_USP);
	DefineLuaGlobal(L, "WEAPON_GLOCK18", WEAPON_GLOCK18);
	DefineLuaGlobal(L, "WEAPON_AWP", WEAPON_AWP);
	DefineLuaGlobal(L, "WEAPON_MP5N", WEAPON_MP5N);
	DefineLuaGlobal(L, "WEAPON_M249", WEAPON_M249);
	DefineLuaGlobal(L, "WEAPON_M3", WEAPON_M3);
	DefineLuaGlobal(L, "WEAPON_M4A1", WEAPON_M4A1);
	DefineLuaGlobal(L, "WEAPON_TMP", WEAPON_TMP);
	DefineLuaGlobal(L, "WEAPON_G3SG1", WEAPON_G3SG1);
	DefineLuaGlobal(L, "WEAPON_FLASHBANG", WEAPON_FLASHBANG);
	DefineLuaGlobal(L, "WEAPON_DEAGLE", WEAPON_DEAGLE);
	DefineLuaGlobal(L, "WEAPON_SG552", WEAPON_SG552);
	DefineLuaGlobal(L, "WEAPON_AK47", WEAPON_AK47);
	DefineLuaGlobal(L, "WEAPON_KNIFE", WEAPON_KNIFE);
	DefineLuaGlobal(L, "WEAPON_P90", WEAPON_P90);
	DefineLuaGlobal(L, "WEAPON_SHIELDGUN", WEAPON_SHIELDGUN);

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

void Sakura::Lua::Reload()
{
	if (scripts.size() > 0)
	{
		currentScriptIndex = 0;
		ScriptsCount = 0;

		for (auto& script : scripts)
		{
			script.RemoveAllCallbacks();
			lua_close(script.GetState());
		}

		scripts.clear();
	}

	const std::string hackDir = hackdir;
	const std::string scriptExtension = /*.lua*/XorStr<0x27, 5, 0x52E70E20>("\x09\x44\x5C\x4B" + 0x52E70E20).s;
	std::string scriptsLoaded;

	for (const auto& p : std::filesystem::recursive_directory_iterator(hackDir + /*\\scripts\\*/XorStr<0xA3, 10, 0x25B9F64A>("\xFF\xD7\xC6\xD4\xCE\xD8\xDD\xD9\xF7" + 0x25B9F64A).s))
	{
		if (p.path().extension() != scriptExtension)
			continue;

		lua_State* L = luaL_newstate();

		if (!L)
		{
			Sakura::Lua::Error(/*Error creating Lua state for script: %s*/XorStr<0x99, 40, 0x12146F81>("\xDC\xE8\xE9\xF3\xEF\xBE\xFC\xD2\xC4\xC3\xD7\xCD\xCB\xC1\x87\xE4\xDC\xCB\x8B\xDF\xD9\xCF\xDB\xD5\x91\xD4\xDC\xC6\x95\xC5\xD4\xCA\xD0\xCA\xCF\x86\x9D\x9B\xCC" + 0x12146F81).s, p.path().filename().string().c_str());
			continue;
		}

		luaL_openlibs(L);

		Init(L);

		if (luaL_loadfile(L, p.path().string().c_str()) != LUA_OK)
		{
			const char* error_msg = lua_tostring(L, -1);
			Sakura::Lua::Error(/*Error loading Lua script: %s*/XorStr<0x98, 29, 0xAA02A755>("\xDD\xEB\xE8\xF4\xEE\xBD\xF2\xF0\xC1\xC5\xCB\xCD\xC3\x85\xEA\xD2\xC9\x89\xD9\xC8\xDE\xC4\xDE\xDB\x8A\x91\x97\xC0" + 0xAA02A755).s, error_msg);
			lua_close(L);
			continue;
		}

		LuaScripts script(L, p.path().filename().string());
		scripts.push_back(script);

		if (lua_pcall(L, 0, 0, 0) != LUA_OK)
		{
			const char* error_msg = lua_tostring(L, -1);
			Sakura::Lua::Error(/*Error running Lua script: %s*/XorStr<0xE6, 29, 0x45A06148>("\xA3\x95\x9A\x86\x98\xCB\x9E\x98\x80\x81\x99\x9F\x95\xD3\xB8\x80\x97\xD7\x8B\x9A\x88\x92\x8C\x89\xC4\xDF\x25\x72" + 0x45A06148).s, error_msg);
			lua_close(L);
			continue;
		}

		currentScriptIndex++;
		ScriptsCount++;

		scriptsLoaded += /* - */XorStr<0xFA, 4, 0x8CF978D3>("\xDA\xD6\xDC" + 0x8CF978D3).s;
		scriptsLoaded += p.path().filename().string();
		scriptsLoaded += /*\n*/XorStr<0x14, 2, 0x6E034713>("\x1E" + 0x6E034713).s;
	}

	Sakura::Log::File(/*%s (%d): \n%s*/XorStr<0x74, 13, 0xF313DFA4>("\x51\x06\x56\x5F\x5D\x1D\x53\x41\x5C\x77\x5B\x0C" + 0xF313DFA4).s, ScriptsCount > 1 ? /*Loaded scripts*/XorStr<0x4D, 15, 0x7D9CE133>("\x01\x21\x2E\x34\x34\x36\x73\x27\x36\x24\x3E\x28\x2D\x29" + 0x7D9CE133).s : /*Loaded script*/XorStr<0x27, 14, 0x7EC8B322>("\x6B\x47\x48\x4E\x4E\x48\x0D\x5D\x4C\x42\x58\x42\x47" + 0x7EC8B322).s, ScriptsCount, scriptsLoaded);
}