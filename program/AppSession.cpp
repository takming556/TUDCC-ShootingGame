#include <memory>
#include "DxLib.h"
#include "class.h"

using std::make_unique;


AppSession::AppSession() :
	now_scene(Scene::TITLE),
	game_conductor(make_unique<GameConductor>()),
	last_screenflipped_clock(1),		//0による除算を防止するため、あえて1で初期化
	clock_keeper_for_measure_fps(0),
	flip_count(0)
{
}


void AppSession::update() {

	get_keyinput_state();
	respond_to_keyinput();

	switch (now_scene) {
	case Scene::TITLE:
		DxLib::DrawGraph(0, 0, ImageHandles::SCREEN_BACKGROUND, TRUE);
		DxLib::DrawRotaGraph(Screen::SCREEN_RESOLUTION_X / 2, Screen::SCREEN_RESOLUTION_Y / 2, 0.19, 0, ImageHandles::ICHIGOCHAN_CONCEPTUAL, TRUE);
		DxLib::DrawFormatStringToHandle(350, 650, Colors::MAZENTA, FontHandles::DSEG14, "PRESS Z TO DIVE");
		break;
	case Scene::GAMING:
		game_conductor->update();
		break;
	case Scene::RESULT:
		break;
	case Scene::RANKING:
		break;
	}

	if (DebugParams::DEBUG_FLAG == true) DebugParams::DRAW();

	LONGLONG now_clock = DxLib::GetNowHiPerformanceCount();
	DebugParams::SLEEP_TIME = (last_screenflipped_clock + ((1.0 / SettingParams::LIMIT_FPS) * 1000 * 1000) - now_clock) / 1000;
	DxLib::WaitTimer(DebugParams::SLEEP_TIME);

	LONGLONG screenflip_postpone_time = 1.0 / SettingParams::LIMIT_FPS * 1000 * 1000;
	if (now_clock > last_screenflipped_clock + screenflip_postpone_time) {
		DxLib::ScreenFlip();		//裏画面の内容を表画面に反映
		DxLib::ClearDrawScreen();	//裏画面をクリア
		LONGLONG delta_time = now_clock - last_screenflipped_clock;
		DebugParams::INSTANT_FPS = 1.0 * 1000 * 1000 / delta_time;
		flip_count++;
		last_screenflipped_clock = DxLib::GetNowHiPerformanceCount();
	}

	if (DxLib::GetNowCount() > clock_keeper_for_measure_fps + 1000) {
		DebugParams::ACTUAL_FPS = flip_count;
		flip_count = 0;
		clock_keeper_for_measure_fps = DxLib::GetNowCount();
	}
}


void AppSession::get_keyinput_state() {
	DxLib::GetHitKeyStateAll(KeyPushFlags::KEY_BUFFER);
}


void AppSession::respond_to_keyinput() {

	if (KeyPushFlags::F3 == false && KeyPushFlags::KEY_BUFFER[KEY_INPUT_F3] == 1) {
		KeyPushFlags::F3 = true;
		DebugParams::DEBUG_FLAG = !(DebugParams::DEBUG_FLAG);
	}
	if (KeyPushFlags::F3 == true && KeyPushFlags::KEY_BUFFER[KEY_INPUT_F3] == 0) {
		KeyPushFlags::F3 = false;
	}

	switch (now_scene) {
	case Scene::TITLE:
		if (KeyPushFlags::KEY_BUFFER[KEY_INPUT_Z] == 1) {
			now_scene = Scene::GAMING;
			DxLib::PlaySoundMem(SoundHandles::FORWARD, DX_PLAYTYPE_NORMAL);
		}
		break;
	}
}