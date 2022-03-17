// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueGameSetting.h"

URogueGameSetting::URogueGameSetting() {
	bUseVSync = true;
	FrameRateLimit = 240.f;
}

void URogueGameSetting::ChangeVSync(bool Check) {
	bUseVSync = Check;
}