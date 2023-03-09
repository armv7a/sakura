#include "../../../client.h"

int Sakura::Menu::currentAlphaFade;
int Sakura::Menu::itemWidth = 245;
int tab = 0;
int ragebottab = 0, legitbottab = 0, visualstab = 0, misctab = 0, colorstab = 0;

bool bShowMenu = false;
bool keysmenu[256];
bool changewindowfocus = true;
bool snowflakesFirst = false;
bool rainFirst = false;

ImFont* Sakura::Menu::Fonts::defaultFont = nullptr;
ImFont* Sakura::Menu::Fonts::icons = nullptr;
ImFont* Sakura::Menu::Fonts::titleTabFont = nullptr;
ImFont* Sakura::Menu::Fonts::titleCheatFont = nullptr;
ImFont* Sakura::Menu::Fonts::weaponsFont = nullptr;

char nickname[32];
char chatspam[128];

//const char* listbox_sub1[] = { "GLOCK18", "P228", "DEAGLE", "ELITE", "FIVESEVEN", "USP" }; Glock-18\0P228\0Deagle\0Dual Elites\0Five-seven\0Usp\0
//const char* listbox_sub2[] = { "AWP", "SCOUT", "G3SG1", "SG550" }; Awp\0Scout\G3SG1\0SG550\0
//const char* listbox_sub3[] = { "M4A1", "GALIL", "FAMAS", "AUG", "AK47", "SG552" }; M4A1\0Galil\0Famas\0Aug\0AK-47\0SG552\0
//const char* listbox_sub4[] = { "XM1014", "M3" }; XM1014\0M3\0
//const char* listbox_sub5[] = { "M249" };
//const char* listbox_sub6[] = { "TMP", "P90", "MP5N", "MAC10", "UMP45" }; Tmp\0P90\0Mp5\0Mac10\0Ump45\0
//const char* listbox_section[] = { "Pistol", "Sniper", "Rifle", "Shotgun", "Machine Gun", "Submachine Gun" }; Pistols\0Snipers\0Rifles\0Shotguns\0Machine guns\0Submachine guns\0

const char* menu_texts[] = {
	"Hello there",
	"WP GG",
	"Missing something?",
	"Config issue",
	"Loooooooooool",
	"<3",
	"Be calm",
	"Soooooooooooo",
	"It was bad idea",
	"Get backtracked",
	":(",
	":)",
	"Thanks to b#"
};

int perviousText = -1;

ImColor Sakura::Menu::GetMenuColor(float alpha)
{
	if (cvar.rainbow_menu)
		return ImColor(color_blue, color_green, color_red, alpha);

	return ImColor(cvar.visual_menu_color[0], cvar.visual_menu_color[1], cvar.visual_menu_color[2], alpha);
}

const char* getRandomText()
{
	if (perviousText >= 0)
		return menu_texts[perviousText];

	perviousText = rand() % IM_ARRAYSIZE(menu_texts);
	return menu_texts[perviousText];
}

char* Sakura::Menu::GetHitboxName(int hitbox)
{
	switch (hitbox)
	{
	case 0: return "Belt";
	case 1: return "Left Thigh";
	case 2: return "Left Tibia";
	case 3: return "Left Foot";
	case 4: return "Right Thigh";
	case 5: return "Right Tibia";
	case 6: return "Right Foot";
	case 7: return "Stomach";
	case 8: return "Lower chest";
	case 9: return "Upper chest";
	case 10: return "Neck";
	case 11: return "Head";
	case 12: return "Left Shoulder";
	case 13: return "Left Elbow";
	case 14: return "Left Arm";
	case 15: return "Left Hand";
	case 16: return "Right Shoulder";
	case 17: return "Right Elbow";
	case 18: return "Right Arm";
	case 19: return "Right Hand";
	default: return "Unknown";
	}
}

char* KeyEventChar(int Key)
{
	switch (Key)
	{
	case K_TAB: return "Tab";
	case K_ENTER: return "Enter";
	case K_ESCAPE: return "Escape";
	case K_SPACE: return "Space";
	case K_0: return "0";
	case K_1: return "1";
	case K_2: return "2";
	case K_3: return "3";
	case K_4: return "4";
	case K_5: return "5";
	case K_6: return "6";
	case K_7: return "7";
	case K_8: return "8";
	case K_9: return "9";
	case K_A: return "A";
	case K_B: return "B";
	case K_C: return "C";
	case K_D: return "D";
	case K_E: return "E";
	case K_F: return "F";
	case K_G: return "G";
	case K_H: return "H";
	case K_I: return "I";
	case K_J: return "J";
	case K_K: return "K";
	case K_L: return "L";
	case K_M: return "M";
	case K_N: return "N";
	case K_O: return "O";
	case K_P: return "P";
	case K_Q: return "Q";
	case K_R: return "R";
	case K_S: return "S";
	case K_T: return "T";
	case K_U: return "U";
	case K_V: return "V";
	case K_W: return "W";
	case K_X: return "X";
	case K_Y: return "Y";
	case K_Z: return "Z";
	case K_BACKSPACE: return "Backspace";
	case K_UPARROW: return "Up Arrow";
	case K_DOWNARROW: return "Down Arrow";
	case K_LEFTARROW: return "Left Arrow";
	case K_RIGHTARROW: return "Right Arrow";
	case K_ALT: return "Alt";
	case K_CTRL: return "Ctrl";
	case K_SHIFT: return "Shift";
	case K_F1: return "F1";
	case K_F2: return "F2";
	case K_F3: return "F3";
	case K_F4: return "F4";
	case K_F5: return "F5";
	case K_F6: return "F6";
	case K_F7: return "F7";
	case K_F8: return "F8";
	case K_F9: return "F9";
	case K_F10: return "F10";
	case K_F11: return "F11";
	case K_F12: return "F12";
	case K_INS: return "Insert";
	case K_DEL: return "Delete";
	case K_PGDN: return "Page Down";
	case K_PGUP: return "Page Up";
	case K_HOME: return "Home";
	case K_END: return "End";
	case K_CAPSLOCK: return "Capslock";
	case K_MWHEELDOWN: return "Wheel Down";
	case K_MWHEELUP: return "Wheel Up";
	case K_MOUSE1: return "Mouse 1";
	case K_MOUSE2: return "Mouse 2";
	case K_MOUSE3: return "Mouse 3";
	case K_MOUSE4: return "Mouse 4";
	case K_MOUSE5: return "Mouse 5";
	}
	return "Unknown Ok";
}
	
void Sakura::Menu::HudKeyBind(float& key, const char* keyname, ImVec2 size, bool old)
{
	char str[256];
	char* buttonText;
	ImVec4 buttonColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

	if (key == -2)
	{
		for (unsigned int i = 0; i < 255; i++)
		{
			if (keysmenu[i])
			{
				if (i == K_ESCAPE || i == cvar.gui_key)
				{
					key = -1;
					break;
				}
				key = i;
			}
		}
	}

	if (key == -1)
	{
		buttonText = "No key";
		buttonColor = ImVec4(1.0f, 0.3f, 0.3f, 1.0f);
	}
	else if (key == -2)
	{
		buttonText = "Press key";
		buttonColor = ImVec4(1.0f, 1.0f, 0.3f, 1.0f);
	}
	else
	{
		buttonText = KeyEventChar(key);
		buttonColor = ImVec4(0.3f, 1.0f, 0.3f, 1.0f);
	}

	ImGui::Text(keyname);
	ImGui::PushStyleColor(ImGuiCol_Text, buttonColor);
	sprintf(str, "[%s]##%s", buttonText, keyname);

	if (old)
	{
		if (ImGui::Button(str, size))
		{
			if (key == -1)
				key = -2;
			else
				key = -1;
		}
	}
	else
	{
		if (Sakura::Menu::Widgets::Button(str, size))
		{
			if (key == -1)
				key = -2;
			else
				key = -1;
		}
	}

	ImGui::PopStyleColor();

	/*bool clicked = false;
	char str[256];

	if (key == -2)
	{
		for (unsigned int i = 0; i < 255; i++)
		{
			if (keysmenu[i])
			{
				if (i == K_ESCAPE || i == cvar.gui_key)
				{
					key = -1;
					break;
				}
				key = i;
			}
		}
	}
	
	if (key == -1)
	{
		ImGui::Text(keyname);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
		sprintf(str, "[No key]##%s", keyname);

		if (Sakura::Menu::Widgets::Button(str, ImVec2(ImGui::GetWindowSize().x - 6, 0)))
			clicked = true;
		ImGui::PopStyleColor();
	}
	else if (key == -2)
	{
		ImGui::Text(keyname);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.3f, 1.0f));
		sprintf(str, "[Press key]##%s", keyname);
		if (Sakura::Menu::Widgets::Button(str, ImVec2(ImGui::GetWindowSize().x - 6, 0)))
			clicked = true;
		ImGui::PopStyleColor();
	}
	else
	{
		ImGui::Text(keyname);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.3f, 1.0f, 0.3f, 1.0f));
		sprintf(str, "[%s]##%s", KeyEventChar(key), keyname);
		if (Sakura::Menu::Widgets::Button(str, ImVec2(ImGui::GetWindowSize().x - 6, 0)))
			clicked = true;
		ImGui::PopStyleColor();
	}

	if (clicked)
	{
		if (key == -1)
			key = -2;
		else
			key = -1;
	}*/
}

void Sakura::Menu::HudMenuBind(float& key)
{
	bool clicked = false;
	static float restorekey;
	if (key != -1)
		restorekey = key;
	if (key == -1)
	{
		for (unsigned int i = 0; i < 255; i++)
		{
			if (keysmenu[i])
			{
				if (i == K_MOUSE1 || i == K_ESCAPE) break;
				key = i;
			}
		}
	}
	
	if (key == -1)
	{
		ImGui::Text(/*Menu Key*/XorStr<0x56, 9, 0x2215152F>("\x1B\x32\x36\x2C\x7A\x10\x39\x24" + 0x2215152F).s);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.3f, 1.0f));
		if(Sakura::Menu::Widgets::Button(/*[Press key]*/XorStr<0xF2, 12, 0x42CD80D7>("\xA9\xA3\x86\x90\x85\x84\xD8\x92\x9F\x82\xA1" + 0x42CD80D7).s, ImVec2(ImGui::GetWindowSize().x - 6, 0)))
			clicked = true;
		ImGui::PopStyleColor();
	}
	else
	{
		ImGui::Text(/*Menu Key*/XorStr<0xE3, 9, 0x08372CD0>("\xAE\x81\x8B\x93\xC7\xA3\x8C\x93" + 0x08372CD0).s);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
		char str[256];
		sprintf(str, "[%s]", KeyEventChar(key));
		if (Sakura::Menu::Widgets::Button(str, ImVec2(ImGui::GetWindowSize().x - 6, 0)))
			clicked = true;
		ImGui::PopStyleColor();
	}

	if (clicked)
	{
		if (key == -1)
			key = restorekey;
		else
			key = -1;
	}
}

int Sakura::Menu::CheckWeapon(float global, float sub)
{
	if (global == 0 && (sub == 0 || sub == 1 || sub == 2 || sub == 3 || sub == 4 || sub == 5))
	{
		if (sub == 0) return WEAPON_GLOCK18;
		if (sub == 1) return WEAPON_P228;
		if (sub == 2) return WEAPON_DEAGLE;
		if (sub == 3) return WEAPON_ELITE;
		if (sub == 4) return WEAPON_FIVESEVEN;
		if (sub == 5) return WEAPON_USP;
	}
	else if (global == 1 && (sub == 0 || sub == 1 || sub == 2 || sub == 3))
	{
		if (sub == 0) return WEAPON_AWP;
		if (sub == 1) return WEAPON_SCOUT;
		if (sub == 2) return WEAPON_G3SG1;
		if (sub == 3) return WEAPON_SG550;
	}
	else if (global == 2 && (sub == 0 || sub == 1 || sub == 2 || sub == 3 || sub == 4 || sub == 5))
	{
		if (sub == 0) return WEAPON_M4A1;
		if (sub == 1) return WEAPON_GALIL;
		if (sub == 2) return WEAPON_FAMAS;
		if (sub == 3) return WEAPON_AUG;
		if (sub == 4) return WEAPON_AK47;
		if (sub == 5) return WEAPON_SG552;
	}
	else if (global == 3 && (sub == 0 || sub == 1))
	{
		if (sub == 0) return WEAPON_XM1014;
		if (sub == 1) return WEAPON_M3;
	}
	else if (global == 4 && sub == 0)
	{
		if (sub == 0) return WEAPON_M249;
	}
	else if (global == 5 && (sub == 0 || sub == 1 || sub == 2 || sub == 3 || sub == 4))
	{
		if (sub == 0) return WEAPON_TMP;
		if (sub == 1) return WEAPON_P90;
		if (sub == 2) return WEAPON_MP5N;
		if (sub == 3) return WEAPON_MAC10;
		if (sub == 4) return WEAPON_UMP45;
	}
	else return 0;
}

void CheckSubSection(float& global, float& sub)
{
	if (global == 0 && sub > 5) sub = 5;
	if (global == 1 && sub > 3) sub = 3;
	if (global == 2 && sub > 5) sub = 5;
	if (global == 3 && sub > 1) sub = 1;
	if (global == 4 && sub > 0) sub = 0;
	if (global == 5 && sub > 4) sub = 4;
}

void DrawCategoryButtons()
{
	ImGui::Spacing();
	ImGui::Spacing();

	switch (tab)
	{
	case 0:
		if (Sakura::Menu::Widgets::SubTab(/*Aimbot*/XorStr<0x47, 7, 0x68C0C7BA>("\x06\x21\x24\x28\x24\x38" + 0x68C0C7BA).s, ImVec2(150, 25), ragebottab == 0 ? true : false))
			ragebottab = 0;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Anti Aim*/XorStr<0x77, 9, 0xC9FE72E0>("\x36\x16\x0D\x13\x5B\x3D\x14\x13" + 0xC9FE72E0).s, ImVec2(150, 25), ragebottab == 1 ? true : false))
			ragebottab = 1;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Fake Lag*/XorStr<0x2C,9,0xDCD958A0>("\x6A\x4C\x45\x4A\x10\x7D\x53\x54"+0xDCD958A0).s, ImVec2(150, 25), ragebottab == 2 ? true : false))
			ragebottab = 2;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Speedhack*/XorStr<0x13, 10, 0x5277386C>("\x40\x64\x70\x73\x73\x70\x78\x79\x70" + 0x5277386C).s, ImVec2(150, 25), ragebottab == 3 ? true : false))
			ragebottab = 3;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Hitboxes*/XorStr<0x19, 9, 0x804A07C0>("\x51\x73\x6F\x7E\x72\x66\x7A\x53" + 0x804A07C0).s, ImVec2(150, 25), ragebottab == 4 ? true : false))
			ragebottab  = 4;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Priority Hitboxes*/XorStr<0x89, 18, 0x0411F866>("\xD9\xF8\xE2\xE3\xFF\xE7\xFB\xE9\xB1\xDA\xFA\xE0\xF7\xF9\xEF\xFD\xEA" + 0x0411F866).s, ImVec2(150, 25), ragebottab == 5 ? true : false))
			ragebottab = 5;
		break;
	case 1:
		if (Sakura::Menu::Widgets::SubTab(/*Aimbot*/XorStr<0x5A, 7, 0x7C571BB6>("\x1B\x32\x31\x3F\x31\x2B" + 0x7C571BB6).s, ImVec2(150, 25), legitbottab == 0 ? true : false))
			legitbottab = 0;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Triggerbot*/XorStr<0x0F, 11, 0x26F86A38>("\x5B\x62\x78\x75\x74\x71\x67\x74\x78\x6C" + 0x26F86A38).s, ImVec2(150, 25), legitbottab == 1 ? true : false))
			legitbottab = 1;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Perfect Silent*/XorStr<0x7D, 15, 0xEFE97515>("\x2D\x1B\x0D\xE6\xE4\xE1\xF7\xA4\xD6\xEF\xEB\xED\xE7\xFE" + 0xEFE97515).s, ImVec2(150, 25), legitbottab == 2 ? true : false))
			legitbottab = 2;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Recoil*/XorStr<0xB3, 7, 0x2BFB339E>("\xE1\xD1\xD6\xD9\xDE\xD4" + 0x2BFB339E).s, ImVec2(150, 25), legitbottab == 3 ? true : false))
			legitbottab = 3;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Knifebot*/XorStr<0xD0, 9, 0x4B190BD1>("\x9B\xBF\xBB\xB5\xB1\xB7\xB9\xA3" + 0x4B190BD1).s, ImVec2(150, 25), legitbottab == 4 ? true : false))
			legitbottab = 4;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Hitboxes*/XorStr<0x20, 9, 0x8140E0C7>("\x68\x48\x56\x41\x4B\x5D\x43\x54" + 0x8140E0C7).s, ImVec2(150, 25), legitbottab == 5 ? true : false))
			legitbottab = 5;
		break;
	case 2:
		if (Sakura::Menu::Widgets::SubTab(/*Player*/XorStr<0x73, 7, 0x401FCABE>("\x23\x18\x14\x0F\x12\x0A" + 0x401FCABE).s, ImVec2(150, 25), visualstab == 0 ? true : false))
			visualstab = 0;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Local*/XorStr<0x14, 6, 0x94C33886>("\x58\x7A\x75\x76\x74" + 0x94C33886).s, ImVec2(150, 25), visualstab == 1 ? true : false))
			visualstab = 1;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*World*/XorStr<0x31, 6, 0x49BAEB00>("\x66\x5D\x41\x58\x51" + 0x49BAEB00).s, ImVec2(150, 25), visualstab == 2 ? true : false))
			visualstab = 2;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Radar*/XorStr<0xB1, 6, 0xB39A2D33>("\xE3\xD3\xD7\xD5\xC7" + 0xB39A2D33).s, ImVec2(150, 25), visualstab == 3 ? true : false))
			visualstab = 3;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Skins*/XorStr<0x92, 6, 0x481899D7>("\xC1\xF8\xFD\xFB\xE5" + 0x481899D7).s, ImVec2(150, 25), visualstab == 4 ? true : false))
			visualstab = 4;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Removals*/XorStr<0xA8, 9, 0x05010633>("\xFA\xCC\xC7\xC4\xDA\xCC\xC2\xDC" + 0x05010633).s, ImVec2(150, 25), visualstab == 5 ? true : false))
			visualstab = 5;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Sound*/XorStr<0xB7, 6, 0xB37B6E61>("\xE4\xD7\xCC\xD4\xDF" + 0xB37B6E61).s, ImVec2(150, 25), visualstab == 6 ? true : false))
			visualstab = 6;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Menu*/XorStr<0x3A, 5, 0xAAEE34F2>("\x77\x5E\x52\x48" + 0xAAEE34F2).s, ImVec2(150, 25), visualstab == 7 ? true : false))
			visualstab = 7;
		break;
	case 3:
		if (Sakura::Menu::Widgets::SubTab(/*HNS*/XorStr<0xAE, 4, 0xD61C59C6>("\xE6\xE1\xE3" + 0xD61C59C6).s, ImVec2(150, 25), misctab == 0 ? true : false))
			misctab = 0;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Keybindings*/XorStr<0xDB, 12, 0x9DC793B5>("\x90\xB9\xA4\xBC\xB6\x8E\x85\x8B\x8D\x83\x96" + 0x9DC793B5).s, ImVec2(150, 25), misctab == 1 ? true : false))
			misctab = 1;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Player List*/XorStr<0x7D, 12, 0x9BE9C82C>("\x2D\x12\x1E\xF9\xE4\xF0\xA3\xC8\xEC\xF5\xF3" + 0x9BE9C82C).s, ImVec2(150, 25), misctab == 2 ? true : false))
			misctab = 2;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Backtrack*/XorStr<0x4F, 10, 0x184CC124>("\x0D\x31\x32\x39\x27\x26\x34\x35\x3C" + 0x184CC124).s, ImVec2(150, 25), misctab == 3 ? true : false))
			misctab = 3;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Anti AFK*/XorStr<0x9D, 9, 0x24E0E5B1>("\xDC\xF0\xEB\xC9\x81\xE3\xE5\xEF" + 0x24E0E5B1).s, ImVec2(150, 25), misctab == 4 ? true : false))
			misctab = 4;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*SID Changer*/XorStr<0x5A, 12, 0x6783DE5A>("\x09\x12\x18\x7D\x1D\x37\x01\x0F\x05\x06\x16" + 0x6783DE5A).s, ImVec2(150, 25), misctab == 5 ? true : false))
			misctab = 5;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Route*/XorStr<0xDC, 6, 0x779C08FC>("\x8E\xB2\xAB\xAB\x85" + 0x779C08FC).s, ImVec2(150, 25), misctab == 6 ? true : false))
			misctab = 6;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Notifications*/XorStr<0x83, 14, 0x55ED0DA5>("\xCD\xEB\xF1\xEF\xE1\xE1\xEA\xEB\xFF\xE5\xE2\xE0\xFC" + 0x55ED0DA5).s, ImVec2(150, 25), misctab == 7 ? true : false))
			misctab = 7;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Name Stealer*/XorStr<0x6F, 13, 0x654059D0>("\x21\x11\x1C\x17\x53\x27\x01\x13\x16\x14\x1C\x08" + 0x654059D0).s, ImVec2(150, 25), misctab == 8 ? true : false))
			misctab = 8;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Chat spammer*/XorStr<0x4E, 13, 0xA7689533>("\x0D\x27\x31\x25\x72\x20\x24\x34\x3B\x3A\x3D\x2B" + 0xA7689533).s, ImVec2(150, 25), misctab == 9 ? true : false))
			misctab = 9;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Config*/XorStr<0xF0, 7, 0x5A2FD6CC>("\xB3\x9E\x9C\x95\x9D\x92" + 0x5A2FD6CC).s, ImVec2(150, 25), misctab == 10 ? true : false))
			misctab = 10;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Info*/XorStr<0x81, 5, 0xC7F5B620>("\xC8\xEC\xE5\xEB" + 0xC7F5B620).s, ImVec2(150, 25), misctab == 11 ? true : false))
			misctab = 11;
		break;
	case 4:
		if (Sakura::Menu::Widgets::SubTab(/*Player Esp*/XorStr<0x50, 11, 0xFB675EA9>("\x00\x3D\x33\x2A\x31\x27\x76\x12\x2B\x29" + 0xFB675EA9).s, ImVec2(150, 25), colorstab == 0 ? true : false))
			colorstab = 0;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Player Glow*/XorStr<0xFA, 12, 0x492B990C>("\xAA\x97\x9D\x84\x9B\x8D\x20\x46\x6E\x6C\x73" + 0x492B990C).s, ImVec2(150, 25), colorstab == 1 ? true : false))
			colorstab = 1;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Player Chams*/XorStr<0xE5, 13, 0x67E5F89D>("\xB5\x8A\x86\x91\x8C\x98\xCB\xAF\x85\x8F\x82\x83" + 0x67E5F89D).s, ImVec2(150, 25), colorstab == 2 ? true : false))
			colorstab = 2;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Player Light*/XorStr<0x97, 13, 0xC08D8CDF>("\xC7\xF4\xF8\xE3\xFE\xEE\xBD\xD2\xF6\xC7\xC9\xD6" + 0xC08D8CDF).s, ImVec2(150, 25), colorstab == 3 ? true : false))
			colorstab = 3;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*World*/XorStr<0x39, 6, 0x5038EE1A>("\x6E\x55\x49\x50\x59" + 0x5038EE1A).s, ImVec2(150, 25), colorstab == 4 ? true : false))
			colorstab = 4;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Player Backtrack*/XorStr<0x8C, 17, 0xAC251604>("\xDC\xE1\xEF\xF6\xF5\xE3\xB2\xD1\xF5\xF6\xFD\xE3\xEA\xF8\xF9\xF0" + 0xAC251604).s, ImVec2(150, 25), colorstab == 5 ? true : false))
			colorstab = 5;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Local*/XorStr<0x5D, 6, 0x466B0D2F>("\x11\x31\x3C\x01\x0D" + 0x466B0D2F).s, ImVec2(150, 25), colorstab == 6 ? true : false))
			colorstab = 6;

		ImGui::Spacing();

		if (Sakura::Menu::Widgets::SubTab(/*Menu*/XorStr<0x28, 5, 0x065EA3AD>("\x65\x4C\x44\x5E" + 0x065EA3AD).s, ImVec2(150, 25), colorstab == 7 ? true : false))
			colorstab = 7;
		break;
	}
}

void DrawButtons()
{
	if (Sakura::Menu::Widgets::Tab(/*a*/XorStr<0x25, 2, 0x2D9B042A>("\x44" + 0x2D9B042A).s, /*Ragebot*/XorStr<0x44, 8, 0xCE68DBE4>("\x16\x24\x21\x22\x2A\x26\x3E" + 0xCE68DBE4).s, ImVec2(85, 50), tab == 0 ? true : false))
		tab = 0;
	ImGui::SameLine();
	if (Sakura::Menu::Widgets::Tab(/*b*/XorStr<0xE8, 2, 0xE67E61AB>("\x8A" + 0xE67E61AB).s, /*Legitbot*/XorStr<0x2A, 9, 0xDE7F5068>("\x66\x4E\x4B\x44\x5A\x4D\x5F\x45" + 0xDE7F5068).s, ImVec2(85, 50), tab == 1 ? true : false))
		tab = 1;
	ImGui::SameLine();
	if (Sakura::Menu::Widgets::Tab(/*c*/XorStr<0x3C, 2, 0x26CDB6DF>("\x5F" + 0x26CDB6DF).s, /*Visuals*/XorStr<0x1F, 8, 0xF63CB178>("\x49\x49\x52\x57\x42\x48\x56" + 0xF63CB178).s, ImVec2(80, 50), tab == 2 ? true : false))
		tab = 2;
	ImGui::SameLine();
	if (Sakura::Menu::Widgets::Tab(/*d*/XorStr<0x36, 2, 0x50F89261>("\x52" + 0x50F89261).s, /*Miscellaneous*/XorStr<0xB1, 14, 0x5ACAC934>("\xFC\xDB\xC0\xD7\xD0\xDA\xDB\xD9\xD7\xDF\xD4\xC9\xCE" + 0x5ACAC934).s, ImVec2(115, 50), tab == 3 ? true : false))
		tab = 3;
	ImGui::SameLine();
	if (Sakura::Menu::Widgets::Tab(/*f*/XorStr<0x4E, 2, 0x8DC459AD>("\x28" + 0x8DC459AD).s, /*Colors*/XorStr<0x26, 7, 0xB6BCB496>("\x65\x48\x44\x46\x58\x58" + 0xB6BCB496).s, ImVec2(75, 50), tab == 4 ? true : false))
		tab = 4;
}

void DrawTab()
{
	switch (tab)
	{
	case 0:
		switch (ragebottab)
		{
		case 0:
			Sakura::Menu::Tabs::Rage::Aimbot();
			break;
		case 1:
			Sakura::Menu::Tabs::Rage::AntiAim();
			break;
		case 2:
			Sakura::Menu::Tabs::Rage::FakeLag();
			break;
		case 3:
			Sakura::Menu::Tabs::Rage::Speedhack();
			break;
		case 4:
			Sakura::Menu::Tabs::Misc::ModelHitboxes();
			break;
		case 5:
			Sakura::Menu::Tabs::Misc::SelectedHitboxes();
			break;
		}

		break;
	case 1:

		if (legitbottab == 0 || legitbottab == 1 || legitbottab == 2 || legitbottab == 3)
		{
			CheckSubSection(cvar.menu_legit_global_section, cvar.menu_legit_sub_section);

			if (Sakura::Menu::Widgets::SubSubTab(/*J*/XorStr<0x07, 2, 0x1193F7AB>("\x4D" + 0x1193F7AB).s, /*Pistols*/XorStr<0xD1, 8, 0x2478CA3A>("\x81\xBB\xA0\xA0\xBA\xBA\xA4" + 0x2478CA3A).s, ImVec2(70, 30), cvar.menu_legit_global_section == 0 ? true : false, Sakura::Menu::Fonts::weaponsFont))
				cvar.menu_legit_global_section = 0;
			ImGui::SameLine();
			if (Sakura::Menu::Widgets::SubSubTab(/*S*/XorStr<0x44, 2, 0x53B8FCBC>("\x17" + 0x53B8FCBC).s, /*Snipers*/XorStr<0x9D, 8, 0x88A36CA2>("\xCE\xF0\xF6\xD0\xC4\xD0\xD0" + 0x88A36CA2).s, ImVec2(80, 30), cvar.menu_legit_global_section == 1 ? true : false, Sakura::Menu::Fonts::weaponsFont))
				cvar.menu_legit_global_section = 1;
			ImGui::SameLine();
			if (Sakura::Menu::Widgets::SubSubTab(/*A*/XorStr<0xA6, 2, 0x78CCF0CB>("\xE7" + 0x78CCF0CB).s, /*Rifles*/XorStr<0x82, 7, 0x1BD311A6>("\xD0\xEA\xE2\xE9\xE3\xF4" + 0x1BD311A6).s, ImVec2(80, 30), cvar.menu_legit_global_section == 2 ? true : false, Sakura::Menu::Fonts::weaponsFont))
				cvar.menu_legit_global_section = 2;
			ImGui::SameLine();
			if (Sakura::Menu::Widgets::SubSubTab(/*P*/XorStr<0xE9, 2, 0xD848AC79>("\xB9" + 0xD848AC79).s, /*Shotguns*/XorStr<0xE5, 9, 0x98726950>("\xB6\x8E\x88\x9C\x8E\x9F\x85\x9F" + 0x98726950).s, ImVec2(80, 30), cvar.menu_legit_global_section == 3 ? true : false, Sakura::Menu::Fonts::weaponsFont))
				cvar.menu_legit_global_section = 3;
			ImGui::SameLine();
			if (Sakura::Menu::Widgets::SubSubTab(/*L*/XorStr<0x84, 2, 0x6BCA3C62>("\xC8" + 0x6BCA3C62).s, /*Machine guns*/XorStr<0x28, 13, 0xEBD54C47>("\x65\x48\x49\x43\x45\x43\x4B\x0F\x57\x44\x5C\x40" + 0xEBD54C47).s, ImVec2(80, 30), cvar.menu_legit_global_section == 4 ? true : false, Sakura::Menu::Fonts::weaponsFont))
				cvar.menu_legit_global_section = 4;
			ImGui::SameLine();
			if (Sakura::Menu::Widgets::SubSubTab(/*N*/XorStr<0x77, 2, 0xA2A289CA>("\x39" + 0xA2A289CA).s, /*Submachine guns*/XorStr<0x10, 16, 0xBEB79C29>("\x43\x64\x70\x7E\x75\x76\x7E\x7E\x76\x7C\x3A\x7C\x69\x73\x6D" + 0xBEB79C29).s, ImVec2(85, 30), cvar.menu_legit_global_section == 5 ? true : false, Sakura::Menu::Fonts::weaponsFont))
				cvar.menu_legit_global_section = 5;

			switch (static_cast<int>(cvar.menu_legit_global_section))
			{
			case 0: // pistols
				if (Sakura::Menu::Widgets::SubSubTab(/*J*/XorStr<0x1B, 2, 0x366E25FB>("\x51" + 0x366E25FB).s, /*Glock-18*/XorStr<0x17, 9, 0x3E402049>("\x50\x74\x76\x79\x70\x31\x2C\x26" + 0x3E402049).s, ImVec2(80, 30), cvar.menu_legit_sub_section == 0 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 0;
				ImGui::SameLine();
				if (Sakura::Menu::Widgets::SubSubTab(/*O*/XorStr<0x34, 2, 0x9579515B>("\x7B" + 0x9579515B).s, /*P-228*/XorStr<0x9C, 6, 0x3D582574>("\xCC\xB0\xAC\xAD\x98" + 0x3D582574).s, ImVec2(80, 30), cvar.menu_legit_sub_section == 1 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 1;
				ImGui::SameLine();
				if (Sakura::Menu::Widgets::SubSubTab(/*D*/XorStr<0xBF, 2, 0x0DE185A2>("\xFB" + 0x0DE185A2).s, /*Desert deagle*/XorStr<0x1B, 14, 0xD5566809>("\x5F\x79\x6E\x7B\x6D\x54\x01\x46\x46\x45\x42\x4A\x42" + 0xD5566809).s, ImVec2(80, 30), cvar.menu_legit_sub_section == 2 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 2;
				ImGui::SameLine();
				if (Sakura::Menu::Widgets::SubSubTab(/*E*/XorStr<0x46, 2, 0x710B50B5>("\x03" + 0x710B50B5).s, /*Dual berettas*/XorStr<0x59, 14, 0x50365BA0>("\x1D\x2F\x3A\x30\x7D\x3C\x3A\x12\x04\x16\x17\x05\x16" + 0x50365BA0).s, ImVec2(80, 30), cvar.menu_legit_sub_section == 3 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 3;
				ImGui::SameLine();
				if (Sakura::Menu::Widgets::SubSubTab(/*G*/XorStr<0xF5, 2, 0xEBD96B5F>("\xB2" + 0xEBD96B5F).s, /*Five-seven*/XorStr<0xDB, 11, 0xF64421C8>("\x9D\xB5\xAB\xBB\xF2\x93\x84\x94\x86\x8A" + 0xF64421C8).s, ImVec2(80, 30), cvar.menu_legit_sub_section == 4 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 4;
				ImGui::SameLine();
				if (Sakura::Menu::Widgets::SubSubTab(/*U*/XorStr<0x1D, 2, 0x3124DF01>("\x48" + 0x3124DF01).s, /*Usp*/XorStr<0x16, 4, 0xEBCFCC42>("\x43\x64\x68" + 0xEBCFCC42).s, ImVec2(80, 30), cvar.menu_legit_sub_section == 5 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 5;
				break;
			case 1: // snipers
				if (Sakura::Menu::Widgets::SubSubTab(/*C*/XorStr<0x75, 2, 0xB0A8FE51>("\x36" + 0xB0A8FE51).s, /*AWP*/XorStr<0xB4, 4, 0xB1983D22>("\xF5\xE2\xE6" + 0xB1983D22).s, ImVec2(120, 30), cvar.menu_legit_sub_section == 0 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 0;
				ImGui::SameLine();
				if (Sakura::Menu::Widgets::SubSubTab(/*S*/XorStr<0xDD, 2, 0x6A4B0757>("\x8E" + 0x6A4B0757).s, /*Scout*/XorStr<0xCC, 6, 0xBAECF2E6>("\x9F\xAE\xA1\xBA\xA4" + 0xBAECF2E6).s, ImVec2(120, 30), cvar.menu_legit_sub_section == 1 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 1;
				ImGui::SameLine();
				if (Sakura::Menu::Widgets::SubSubTab(/*H*/XorStr<0xCE, 2, 0xDF442BCC>("\x86" + 0xDF442BCC).s, /*G3SG1*/XorStr<0x34, 6, 0xA2E62F6B>("\x73\x06\x65\x70\x09" + 0xA2E62F6B).s, ImVec2(120, 30), cvar.menu_legit_sub_section == 2 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 2;
				ImGui::SameLine();
				if (Sakura::Menu::Widgets::SubSubTab(/*Q*/XorStr<0x56, 2, 0xFC8F7933>("\x07" + 0xFC8F7933).s, /*SG550*/XorStr<0x7B, 6, 0xA20BE07A>("\x28\x3B\x48\x4B\x4F" + 0xA20BE07A).s, ImVec2(120, 30), cvar.menu_legit_sub_section == 3 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 3;
				break;
			case 2: // rifles
				if (Sakura::Menu::Widgets::SubSubTab(/*K*/XorStr<0xB3, 2, 0xC1C21D22>("\xF8" + 0xC1C21D22).s, /*M4A1*/XorStr<0xCF, 5, 0x62ADDEC7>("\x82\xE4\x90\xE3" + 0x62ADDEC7).s, ImVec2(80, 30), cvar.menu_legit_sub_section == 0 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 0;
				ImGui::SameLine();
				if (Sakura::Menu::Widgets::SubSubTab(/*I*/XorStr<0xE6, 2, 0x8C2AAD4A>("\xAF" + 0x8C2AAD4A).s, /*Galil*/XorStr<0xBE, 6, 0x84F98779>("\xF9\xDE\xAC\xA8\xAE" + 0x84F98779).s, ImVec2(80, 30), cvar.menu_legit_sub_section == 1 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 1;
				ImGui::SameLine();
				if (Sakura::Menu::Widgets::SubSubTab(/*F*/XorStr<0xDD, 2, 0x463E1080>("\x9B" + 0x463E1080).s, /*Famas*/XorStr<0xB0, 6, 0x0B810601>("\xF6\xD0\xDF\xD2\xC7" + 0x0B810601).s, ImVec2(80, 30), cvar.menu_legit_sub_section == 2 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 2;
				ImGui::SameLine();
				if (Sakura::Menu::Widgets::SubSubTab(/*B*/XorStr<0x3D, 2, 0x42616576>("\x7F" + 0x42616576).s, /*Aug*/XorStr<0xEE, 4, 0x17695421>("\xAF\x9A\x97" + 0x17695421).s, ImVec2(80, 30), cvar.menu_legit_sub_section == 3 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 3;
				ImGui::SameLine();
				if (Sakura::Menu::Widgets::SubSubTab(/*A*/XorStr<0x6B, 2, 0x982B48B2>("\x2A" + 0x982B48B2).s, /*AK-47*/XorStr<0xBE, 6, 0x083D2F4B>("\xFF\xF4\xED\xF5\xF5" + 0x083D2F4B).s, ImVec2(80, 30), cvar.menu_legit_sub_section == 4 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 4;
				ImGui::SameLine();
				if (Sakura::Menu::Widgets::SubSubTab(/*R*/XorStr<0xD0, 2, 0x912A7965>("\x82" + 0x912A7965).s, /*SG552*/XorStr<0xD6, 6, 0x6B217C62>("\x85\x90\xED\xEC\xE8" + 0x6B217C62).s, ImVec2(80, 30), cvar.menu_legit_sub_section == 5 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 5;
				break;
			case 3: // shotguns
				if (Sakura::Menu::Widgets::SubSubTab(/*V*/XorStr<0x18,2,0xC145890E>("\x4E"+0xC145890E).s, /*XM1014*/XorStr<0xA9, 7, 0x9AA15A7B>("\xF1\xE7\x9A\x9C\x9C\x9A" + 0x9AA15A7B).s, ImVec2(265, 30), cvar.menu_legit_sub_section == 0 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 0;
				ImGui::SameLine();
				if (Sakura::Menu::Widgets::SubSubTab(/*P*/XorStr<0x76, 2, 0x10C93ABC>("\x26" + 0x10C93ABC).s, /*M3*/XorStr<0x6D, 3, 0xFCD02E83>("\x20\x5D" + 0xFCD02E83).s, ImVec2(265, 30), cvar.menu_legit_sub_section == 1 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 1;
				break;
			case 4: // machine guns
				if (Sakura::Menu::Widgets::SubSubTab(/*L*/XorStr<0x3B, 2, 0xFE306131>("\x77" + 0xFE306131).s, /*M249*/XorStr<0x4A, 5, 0xB2C14093>("\x07\x79\x78\x74" + 0xB2C14093).s, ImVec2(530, 30), cvar.menu_legit_sub_section == 0 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 0;
				break;
			case 5: // submachine guns
				if (Sakura::Menu::Widgets::SubSubTab(/*a*/XorStr<0x8D, 2, 0x1EB76F2E>("\xEC" + 0x1EB76F2E).s, /*Tmp*/XorStr<0xFB, 4, 0xF29825C0>("\xAF\x91\x8D" + 0xF29825C0).s, ImVec2(120, 30), cvar.menu_legit_sub_section == 0 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 0;
				ImGui::SameLine();
				if (Sakura::Menu::Widgets::SubSubTab(/*N*/XorStr<0xB3, 2, 0xC1A727BC>("\xFD" + 0xC1A727BC).s, /*P90*/XorStr<0x50, 4, 0xCFBC0891>("\x00\x68\x62" + 0xCFBC0891).s, ImVec2(120, 30), cvar.menu_legit_sub_section == 1 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 1;
				ImGui::SameLine();
				if (Sakura::Menu::Widgets::SubSubTab(/*b*/XorStr<0xEC, 2, 0x5027F728>("\x8E" + 0x5027F728).s, /*Mp5*/XorStr<0xEC, 4, 0xB8B980A2>("\xA1\x9D\xDB" + 0xB8B980A2).s, ImVec2(120, 30), cvar.menu_legit_sub_section == 2 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 2;
				ImGui::SameLine();
				if (Sakura::Menu::Widgets::SubSubTab(/*M*/XorStr<0x6A, 2, 0x81E72E7A>("\x27" + 0x81E72E7A).s, /*Mac10*/XorStr<0xF1, 6, 0xA84884ED>("\xBC\x93\x90\xC5\xC5" + 0xA84884ED).s, ImVec2(120, 30), cvar.menu_legit_sub_section == 3 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 3;
				ImGui::SameLine();
				if (Sakura::Menu::Widgets::SubSubTab(/*T*/XorStr<0x42, 2, 0xE48746C6>("\x16" + 0xE48746C6).s, /*Ump45*/XorStr<0x60, 6, 0xC92D2960>("\x35\x0C\x12\x57\x51" + 0xC92D2960).s, ImVec2(120, 30), cvar.menu_legit_sub_section == 4 ? true : false, Sakura::Menu::Fonts::weaponsFont))
					cvar.menu_legit_sub_section = 4;
				break;
			}

			//ImGui::BeginChild(/*##lweapon1*/XorStr<0xBC, 11, 0xB95E8E0E>("\x9F\x9E\xD2\xC8\xA5\xA0\xB2\xAC\xAA\xF4" + 0xB95E8E0E).s, ImVec2(250, 40));
			//{
			//	//ImGui::PushItemWidth(Sakura::Menu::itemWidth + 5);
			//	//Sakura::Menu::Widgets::Combo(/*Weapon category*/XorStr<0x37, 16, 0x572D301F>("\x60\x5D\x58\x4A\x54\x52\x1D\x5D\x5E\x34\x24\x25\x2C\x36\x3C" + 0x572D301F).s, &cvar.menu_legit_global_section, /*Pistols\0Snipers\0Rifles\0Shotguns\0Machine guns\0Submachine guns\0*/XorStr<0xC4, 62, 0xD4C50B6A>("\x94\xAC\xB5\xB3\xA7\xA5\xB9\xCB\x9F\xA3\xA7\xBF\xB5\xA3\xA1\xD3\x86\xBC\xB0\xBB\xBD\xAA\xDA\x88\xB4\xB2\xAA\xB8\x95\x8F\x91\xE3\xA9\x84\x85\x8F\x81\x87\x8F\xCB\x8B\x98\x80\x9C\xF0\xA2\x87\x91\x99\x94\x95\x9F\x91\x97\x9F\xDB\x9B\x88\x90\x8C\x00" + 0xD4C50B6A).s);
			//	//ImGui::PopItemWidth();
			//}
			//ImGui::EndChild();
			//ImGui::SameLine();
			//ImGui::BeginChild(/*##lweapon2*/XorStr<0x2E, 11, 0xAE3DD1A8>("\x0D\x0C\x5C\x46\x57\x52\x44\x5A\x58\x05" + 0xAE3DD1A8).s, ImVec2(250, 40));
			//{
			//	ImGui::PushItemWidth(Sakura::Menu::itemWidth + 5);
			//	if (cvar.menu_legit_global_section == 0) Sakura::Menu::Widgets::Combo(/*Weapon*/XorStr<0x8C, 7, 0x59A0CCCD>("\xDB\xE8\xEF\xFF\xFF\xFF" + 0x59A0CCCD).s, &cvar.menu_legit_sub_section, /*Glock-18\0P228\0Deagle\0Dual Elites\0Five-seven\0Usp\0*/XorStr<0x02, 49, 0x42BA9433>("\x45\x6F\x6B\x66\x6D\x2A\x39\x31\x0A\x5B\x3E\x3F\x36\x0F\x54\x74\x73\x74\x78\x70\x16\x53\x6D\x78\x76\x3B\x59\x71\x77\x6B\x45\x52\x22\x65\x4D\x53\x43\x0A\x5B\x4C\x5C\x4E\x42\x2D\x7B\x5C\x40\x31" + 0x42BA9433).s);
			//	if (cvar.menu_legit_global_section == 1) Sakura::Menu::Widgets::Combo(/*Weapon*/XorStr<0xA3, 7, 0x4BC745F0>("\xF4\xC1\xC4\xD6\xC8\xC6" + 0x4BC745F0).s, &cvar.menu_legit_sub_section, /*Awp\0Scout\0G3SG1\0SG550\0*/XorStr<0x3B, 23, 0x5B25F9E0>("\x7A\x4B\x4D\x3E\x6C\x23\x2E\x37\x37\x44\x02\x75\x14\x0F\x78\x4A\x18\x0B\x78\x7B\x7F\x50" + 0x5B25F9E0).s);
			//	if (cvar.menu_legit_global_section == 2) Sakura::Menu::Widgets::Combo(/*Weapon*/XorStr<0xFE, 7, 0xB574A82A>("\xA9\x9A\x61\x71\x6D\x6D" + 0xB574A82A).s, &cvar.menu_legit_sub_section, /*M4A1\0Galil\0Famas\0Aug\0AK-47\0SG552\0*/XorStr<0xA1, 34, 0xBD2E952D>("\xEC\x96\xE2\x95\xA5\xE1\xC6\xC4\xC0\xC6\xAB\xEA\xCC\xC3\xCE\xC3\xB1\xF3\xC6\xD3\xB5\xF7\xFC\x95\x8D\x8D\xBB\xEF\xFA\x8B\x8A\xF2\xC1" + 0xBD2E952D).s);
			//	if (cvar.menu_legit_global_section == 3) Sakura::Menu::Widgets::Combo(/*Weapon*/XorStr<0xBF, 7, 0x4D7E9BAF>("\xE8\xA5\xA0\xB2\xAC\xAA" + 0x4D7E9BAF).s, &cvar.menu_legit_sub_section, /*XM1014\0M3\0*/XorStr<0x29, 11, 0x20725BEB>("\x71\x67\x1A\x1C\x1C\x1A\x2F\x7D\x02\x32" + 0x20725BEB).s);
			//	if (cvar.menu_legit_global_section == 4) Sakura::Menu::Widgets::Combo(/*Weapon*/XorStr<0x73, 7, 0x98922951>("\x24\x11\x14\x06\x18\x16" + 0x98922951).s, &cvar.menu_legit_sub_section, /*M249\0*/XorStr<0xEA, 6, 0x0F7F0EC4>("\xA7\xD9\xD8\xD4\xEE" + 0x0F7F0EC4).s);
			//	if (cvar.menu_legit_global_section == 5) Sakura::Menu::Widgets::Combo(/*Weapon*/XorStr<0x52, 7, 0x6116DB37>("\x05\x36\x35\x25\x39\x39" + 0x6116DB37).s, &cvar.menu_legit_sub_section, /*Tmp\0P90\0Mp5\0Mac10\0Ump45\0*/XorStr<0xC3, 25, 0x7F14DE9D>("\x97\xA9\xB5\xC6\x97\xF1\xF9\xCA\x86\xBC\xF8\xCE\x82\xB1\xB2\xE3\xE3\xD4\x80\xBB\xA7\xEC\xEC\xDA" + 0x7F14DE9D).s);
			//	ImGui::PopItemWidth();
			//}
			//ImGui::EndChild();
		}
		
		switch (legitbottab)
		{
		case 0:
			Sakura::Menu::Tabs::Legit::Aimbot();
			break;
		case 1:
			Sakura::Menu::Tabs::Legit::Triggerbot();
			break;
		case 2:
			Sakura::Menu::Tabs::Legit::PerfectSilent();
			break;
		case 3:
			Sakura::Menu::Tabs::Legit::Recoil();
			break;
		case 4:
			Sakura::Menu::Tabs::Legit::Knifebot();
			break;
		case 5:
			Sakura::Menu::Tabs::Legit::Hitboxes();
			break;
		}
		break;
	case 2:
		switch (visualstab)
		{
		case 0:
			Sakura::Menu::Tabs::Visuals::Player();
			break;
		case 1:
			Sakura::Menu::Tabs::Visuals::Local();
			break;
		case 2:
			Sakura::Menu::Tabs::Visuals::World();
			break;
		case 3:
			Sakura::Menu::Tabs::Visuals::Radar();
			break;
		case 4:
			Sakura::Menu::Tabs::Visuals::Skins();
			break;
		case 5:
			Sakura::Menu::Tabs::Visuals::Removals();
			break;
		case 6:
			Sakura::Menu::Tabs::Visuals::Sound();
			break;
		case 7:
			Sakura::Menu::Tabs::Visuals::Other();
			break;
		}
		break;
	case 3:
		switch (misctab)
		{
		case 0:
			Sakura::Menu::Tabs::Misc::Kreedz();
			break;
		case 1:
			Sakura::Menu::Tabs::Misc::Keybindings();
			break;
		case 2:
			Sakura::Menu::Tabs::Misc::PlayerList();
			break;
		case 3:
			Sakura::Menu::Tabs::Misc::Backtrack();
			break;
		case 4:
			Sakura::Menu::Tabs::Misc::AntiAFK();
			break;
		case 5:
			Sakura::Menu::Tabs::Misc::SidChanger();
			break;
		case 6:
			Sakura::Menu::Tabs::Misc::Route();
			break;
		case 7:
			Sakura::Menu::Tabs::Misc::Notify();
			break;
		case 8:
			Sakura::Menu::Tabs::Misc::NameStealer();
			break;
		case 9:
			Sakura::Menu::Tabs::Misc::ChatSpammer();
			break;
		case 10:
			Sakura::Menu::Tabs::Misc::Config();
			break;
		case 11:
			Sakura::Menu::Tabs::Misc::Information();
			break;
		}
		break;
	case 4:
		switch (colorstab)
		{
		case 0:
			Sakura::Menu::Tabs::Colors::PlayerEsp();
			break;
		case 1:
			Sakura::Menu::Tabs::Colors::PlayerGlow();
			break;
		case 2:
			Sakura::Menu::Tabs::Colors::PlayerChams();
			break;
		case 3:
			Sakura::Menu::Tabs::Colors::PlayerLight();
			break;
		case 4:
			Sakura::Menu::Tabs::Colors::World();
			break;
		case 5:
			Sakura::Menu::Tabs::Colors::Backtrack();
			break;
		case 6:
			Sakura::Menu::Tabs::Colors::Local();
			break;
		case 7:
			Sakura::Menu::Tabs::Colors::Menu();
			break;
		}
		break;
	}
}

void DrawMenuWindow()
{
	static float alpha = 0.f;
	static float snowflakesFirst = false;

	if (alpha > 1.f)
		alpha = 1.f;

	if (alpha < 0.f)
		alpha = 0.f;

	if (bShowMenu && alpha < 1.f)
		alpha += 0.16;
	else if(!bShowMenu && alpha > 0.f)
		alpha -= 0.16;

	Sakura::Menu::currentAlphaFade = alpha * 255;

	if (!bShowMenu && alpha == 0)
	{
		perviousText = -1;
		return;
	}

	// raining effect
	ImGui::SetNextWindowSize({ ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y });
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, cvar.visual_menu_bg_opacity + alpha - 0.77f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
	ImGui::Begin(/*##bgmenu*/XorStr<0xBF, 9, 0x59E6729E>("\x9C\xE3\xA3\xA5\xAE\xA1\xAB\xB3" + 0x59E6729E).s, nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoInputs);
	{
		if (cvar.visual_menu_raining)
		{
			ImDrawList* rainingDraw = ImGui::GetWindowDrawList();
			ImVec2 rainingPos = ImGui::GetWindowPos();

			static const int num_raining = 500;
			static float snowflakes_x[num_raining];
			static float snowflakes_y[num_raining];
			static float snowflakes_size[num_raining];
			static float snowflakes_speed[num_raining];
			static float rain_x[num_raining];
			static float rain_y[num_raining];
			static float rain_size[num_raining];
			static float rain_speed[num_raining];
			static float rain_opacity[num_raining];
			static float rain_wind[num_raining];
			static ImVec2 viewer_pos = ImVec2(ImGui::GetIO().DisplaySize.x * 0.f, ImGui::GetIO().DisplaySize.y * 0.5f);

			switch (static_cast<int>(cvar.visual_menu_raining_type))
			{
			case 0:
				if (!snowflakesFirst)
				{
					for (int i = 0; i < num_raining; i++)
					{
						snowflakes_x[i] = ImGui::GetIO().DisplaySize.x * (float)rand() / RAND_MAX;
						//snowflakes_y[i] = -5;
						snowflakes_y[i] = ImGui::GetIO().DisplaySize.y * (float)rand() / RAND_MAX * -1.0f;
						snowflakes_size[i] = ImGui::GetIO().DisplaySize.x * 0.01 * (float)rand() / RAND_MAX;
						float speed_range = ImGui::GetIO().DisplaySize.y * 0.01;
						float min_speed = ImGui::GetIO().DisplaySize.y * 0.005;
						snowflakes_speed[i] = min_speed + (i * speed_range / num_raining);
						//snowflakes_speed[i] = ((float)rand() / RAND_MAX) * snowflakes_size[i] * 2;
						rain_wind[i] = ((float)rand() / RAND_MAX) * ImGui::GetIO().DisplaySize.x * 0.002; // add some horizontal movement to the drops
					}

					snowflakesFirst = true;
				}

				for (int i = 0; i < cvar.visual_menu_raining_count; i++)
				{
					rainingDraw->AddCircleFilled({ rainingPos.x + snowflakes_x[i], rainingPos.y + snowflakes_y[i] }, snowflakes_size[i], Sakura::Colors::White());

					float minAngle = M_PI / 4;
					float maxAngle = 3 * M_PI / 4;
					float angle = minAngle + (float)rand() / RAND_MAX * (maxAngle - minAngle);

					snowflakes_y[i] += (snowflakes_speed[i] * sin(angle)) * cvar.visual_menu_raining_speed_multipler;

					if (snowflakes_y[i] > ImGui::GetIO().DisplaySize.y + 5)
						snowflakes_y[i] = -5;
				}
				break;
			case 1:
				if (!rainFirst)
				{
					for (int i = 0; i < num_raining; i++)
					{
						rain_x[i] = ImGui::GetIO().DisplaySize.x * (float)rand() / RAND_MAX;
						rain_y[i] = ImGui::GetIO().DisplaySize.y * (float)rand() / RAND_MAX * -1.0f;

						rain_size[i] = ImGui::GetIO().DisplaySize.x * 0.04 * (float)rand() / RAND_MAX;

						float speed_range = ImGui::GetIO().DisplaySize.y * 0.01;
						float min_speed = ImGui::GetIO().DisplaySize.y * 0.005;
						rain_speed[i] = min_speed + (i * speed_range / num_raining);

						rain_opacity[i] = 0.3f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.7f));

						float wind_range = ImGui::GetIO().DisplaySize.x * 0.002;
						rain_wind[i] = (float)rand() / RAND_MAX * wind_range - wind_range / 2.0f;
					}

					rainFirst = true;
				}

				for (int i = 0; i < cvar.visual_menu_raining_count; i++)
				{
					float start_x = rain_x[i];
					float start_y = rain_y[i];
					float end_x = start_x + rain_wind[i]; // apply the horizontal movement to the drop's position
					float end_y = start_y + rain_size[i];

					float length_range = ImGui::GetIO().DisplaySize.y * 0.02;
					float min_length = ImGui::GetIO().DisplaySize.y * 0.01;
					float length = min_length + (i * length_range / num_raining);
					end_y = start_y + length;

					// compute distance and angle between raindrop and viewer
					float dx = rain_x[i] - viewer_pos.x;
					float dy = rain_y[i] - viewer_pos.y;
					float distance = sqrt(dx * dx + dy * dy);
					float angle = atan2(dy, dx);

					// adjust opacity based on distance and viewing angle
					float opacity = 0.7f - (distance / ImGui::GetIO().DisplaySize.y) * (0.7f - 0.3f);
					opacity *= cos(angle);

					rainingDraw->AddLine({ rainingPos.x + start_x, rainingPos.y + start_y }, { rainingPos.x + end_x, rainingPos.y + end_y + rain_size[i] }, ImColor(0.89f, 0.89f, 0.89f, opacity));

					rain_x[i] += 0.01f * rain_size[i] + rain_wind[i];
					rain_y[i] += rain_speed[i] * cvar.visual_menu_raining_speed_multipler;

					if (rain_y[i] > ImGui::GetIO().DisplaySize.y + 10)
						rain_y[i] = -10;
					if (rain_x[i] > ImGui::GetIO().DisplaySize.x + 10)
						rain_x[i] = -10;
					if (rain_x[i] < -10)
						rain_x[i] = ImGui::GetIO().DisplaySize.x + 10;
				}
				break;
			}
		}

	}
	ImGui::End();
	ImGui::PopStyleVar(2);
	
	if (Sakura::Lua::scripts.size() > 0)
	{
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
		ImGui::Begin(/*Sakura - Lua Scripts*/XorStr<0xBB, 21, 0x73438C7B>("\xE8\xDD\xD6\xCB\xCD\xA1\xE1\xEF\xE3\x88\xB0\xA7\xE7\x9B\xAA\xB8\xA2\xBC\xB9\xBD" + 0x73438C7B).s, nullptr, ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::BeginTabBar(/*luascripts*/XorStr<0xCE, 11, 0x0006A541>("\xA2\xBA\xB1\xA2\xB1\xA1\xBD\xA5\xA2\xA4" + 0x0006A541).s, ImGuiTabBarFlags_NoTooltip);
		for (size_t i = 0; i < Sakura::Lua::scripts.size(); ++i)
		{
			auto& script = Sakura::Lua::scripts[i];

			if (!script.HasCallback(Sakura::Lua::SAKURA_CALLBACK_TYPE::SAKURA_CALLBACK_AT_RENDERING_MENU))
				continue;

			auto& callbacks = script.GetCallbacks(Sakura::Lua::SAKURA_CALLBACK_TYPE::SAKURA_CALLBACK_AT_RENDERING_MENU);
			for (const auto& callback : callbacks)
			{
				try
				{
					callback();
				}
				catch (luabridge::LuaException const& error)
				{
					if (script.GetState())
					{
						LogToFile("Error has occured in the lua: %s", error.what());
						script.RemoveAllCallbacks();
					}
				}
			}
		}
		ImGui::EndTabBar();
		ImGui::End();
		ImGui::PopStyleVar();
	}

	const char* text = getRandomText();

	auto flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar;
	
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, alpha);
	ImGui::SetNextWindowSize({ 720, 490 });
	ImGui::Begin(/*##menu*/XorStr<0x9A, 7, 0x2A9A8C6C>("\xB9\xB8\xF1\xF8\xF0\xEA" + 0x2A9A8C6C).s, nullptr, flags);
	{
		ImDrawList* draw = ImGui::GetWindowDrawList();
		ImVec2 pos = ImGui::GetWindowPos();

		// 19, 22, 26
		// 25, 30, 35
		// 45, 50, 55
		draw->AddRectFilled({ pos.x, pos.y }, { pos.x + 720, pos.y + 50 }, ImColor((int)(cvar.visual_menu_color_header[0] * 255), (int)(cvar.visual_menu_color_header[1] * 255), (int)(cvar.visual_menu_color_header[2] * 255), Sakura::Menu::currentAlphaFade), 6.f, ImDrawCornerFlags_Top);
		draw->AddRectFilled({ pos.x, pos.y + 50 }, { pos.x + 720, pos.y + 490 }, ImColor((int)(cvar.visual_menu_color_items[0] * 255), (int)(cvar.visual_menu_color_items[1] * 255), (int)(cvar.visual_menu_color_items[2] * 255), Sakura::Menu::currentAlphaFade), 6.f, ImDrawCornerFlags_All);
		draw->AddRectFilled({ pos.x, pos.y + 470 }, { pos.x + 720, pos.y + 490 }, ImColor((int)(cvar.visual_menu_color_footer[0] * 255), (int)(cvar.visual_menu_color_footer[1] * 255), (int)(cvar.visual_menu_color_footer[2] * 255), Sakura::Menu::currentAlphaFade), 6.f, ImDrawCornerFlags_Bot);

		draw->AddText({ pos.x + 10, pos.y + 470 + 10 - ImGui::CalcTextSize(text).y / 2 }, ImColor(250, 250, 250, Sakura::Menu::currentAlphaFade), text);
		draw->AddText({ pos.x + 710 - ImGui::CalcTextSize(SAKURA_VERSION).x, pos.y + 470 + 10 - ImGui::CalcTextSize(SAKURA_VERSION).y / 2 }, ImColor(250, 250, 250, Sakura::Menu::currentAlphaFade), SAKURA_VERSION);

		ImGui::PushFont(Sakura::Menu::Fonts::icons);
		ImGui::SetCursorPos({ 20,25 - ImGui::CalcTextSize(/*P*/XorStr<0x6A, 2, 0x100FA605>("\x3A" + 0x100FA605).s).y / 2 });
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(cvar.visual_menu_color_logo[0], cvar.visual_menu_color_logo[1], cvar.visual_menu_color_logo[2], 1.f));
		ImGui::Text(/*P*/XorStr<0x6A, 2, 0x100FA605>("\x3A" + 0x100FA605).s);
		ImGui::PopStyleColor();
		ImGui::PopFont();

		ImGui::SameLine();

		ImGui::PushFont(Sakura::Menu::Fonts::titleCheatFont);
		ImGui::SetCursorPos({ 50,25 - ImGui::CalcTextSize(/*Sakura*/XorStr<0xA4,7,0x0D9D1D33>("\xF7\xC4\xCD\xD2\xDA\xC8" + 0x0D9D1D33).s).y / 2 });
		ImGui::Text(/*Sakura*/XorStr<0xA4, 7, 0x0D9D1D33>("\xF7\xC4\xCD\xD2\xDA\xC8" + 0x0D9D1D33).s);
		ImGui::PopFont();

		ImGui::SetCursorPos({ 200,0 });
		ImGui::BeginGroup();
		{
			DrawButtons();
		}
		ImGui::EndGroup();

		ImGui::SetCursorPos({ 10,60 });
		ImGui::BeginGroup();
		{
			DrawCategoryButtons();
		}
		ImGui::EndGroup();

		static bool checkboxbool = false;
		static int sliderint = 254;
		static int comboint = 1;
		static float coloredit[3] = { 0.f,0.f,0.f };

		ImGui::SetCursorPos({ 170,60 });
		ImGui::BeginGroup();
		{
			ImGui::BeginChild(/*##items*/XorStr<0x05, 8, 0x42ADB240>("\x26\x25\x6E\x7C\x6C\x67\x78" + 0x42ADB240).s, { 530, 400 });
			{
				// 30, 35, 40
				draw->AddRectFilled(ImGui::GetWindowPos(), { ImGui::GetWindowPos().x + 530,ImGui::GetWindowPos().y + 400 }, ImColor((int)(cvar.visual_menu_color_widgets[0] * 255), (int)(cvar.visual_menu_color_widgets[1] * 255), (int)(cvar.visual_menu_color_widgets[2] * 255), Sakura::Menu::currentAlphaFade - 55), 8.f);

				ImGui::PushFont(Sakura::Menu::Fonts::titleTabFont);
				ImGui::SetCursorPos({ 10,10 });
				ImGui::BeginGroup();
				{
					DrawTab();
				}
				ImGui::EndGroup();
				ImGui::PopFont();
			}
			ImGui::EndChild();
		}
		ImGui::EndGroup();
	}
	ImGui::End();
	ImGui::PopStyleVar();

	//ImGui::ShowDemoWindow();
}