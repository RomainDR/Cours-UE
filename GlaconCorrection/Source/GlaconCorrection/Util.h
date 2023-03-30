#pragma once

#include "Kismet/KismetMathLibrary.h"

#define LOG(cat, msg, ...) UE_LOG(cat, Display, TEXT(msg), __VA_ARGS__);
#define LOG_W(cat, msg, ...) UE_LOG(cat, Warning,  TEXT(msg), __VA_ARGS__);
#define LOG_E(cat, msg, ...) UE_LOG(cat, Error,  TEXT(msg), __VA_ARGS__);
#define LOG_SCREEN(time, color, msg, ...) GEngine->AddOnScreenDebugMessage(-1, time, color, FString::Printf(TEXT(msg), __VA_ARGS__));

/*
DECLARE_LOG_CATEGORY_EXTERN(P1, Log, All);
DEFINE_LOG_CATEGORY(P1);

DECLARE_LOG_CATEGORY_EXTERN(CCC, Log, All);
DEFINE_LOG_CATEGORY(CCC);
*/

#define WORLD GetWorld()
#define DELTATIME WORLD->DeltaTimeSeconds

#define USE_DEBUG 1

#define DRAW_SPHERE(from, radius, color, size) \
	 if(USE_DEBUG) DrawDebugSphere(WORLD, from, radius, 20, color, false, -1, 0, size);
#define DRAW_BOX(from, extends, color, size) \
	if(USE_DEBUG) DrawDebugBox(WORLD, from, extends, color, false, -1, 0, size);
#define DRAW_LINE(from, to, color, size) \
	if(USE_DEBUG) DrawDebugLine(WORLD, from, to, color, false, -1, 0, size);
#define DRAW_TEXT(from, text, color, size) \
	if(USE_DEBUG) DrawDebugString(WORLD, from, text, nullptr, color, DELTATIME, false, size);

#define LERP_COLOR(from, to, t) UKismetMathLibrary::LinearColorLerp(from.ReinterpretAsLinear(), to.ReinterpretAsLinear(), t).ToFColor(true);

#define TO_CHAR(string) *string
#define TO_STRING(notString) notString.ToString()
#define TO_CHAR_STR(text) TO_CHAR(TO_STRING(text))


#define BIND(del, owner, method) del.AddDynamic(owner, &method)
#define INVOKE(del) del.Broadcast();
#define INVOKE_PARAM(del, ...) del.Broadcast(__VA_ARGS__);


#define LERP(A,B,T) FMath::Lerp(A,B,T)
#define COLOR(C) FColor::C

#define CREATE(type, name) CreateDefaultSubobject<type>(name);
#define ATTACH_TO(owner, to) owner->SetupAttachment(to);

#define OWNER GetOwner()

#define FPC WORLD->GetFirstPlayerController()