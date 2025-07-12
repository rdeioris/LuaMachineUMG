// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaUserDataInterface.h"
#include "Components/PanelSlot.h"
#include "LuaProxyCanvasPanelSlot.generated.h"

class UCanvasPanelSlot;

UCLASS()
class LUAMACHINEUMG_API ULuaProxyCanvasPanelSlot : public UVisual, public ILuaUserDataInterface
{
	GENERATED_BODY()

public:
	FLuaValue LuaMetaMethodIndex_Implementation(const FString& Key) override;

	bool LuaMetaMethodNewIndex_Implementation(const FString& Key, FLuaValue Value) override;

	FLuaValue LuaMetaMethodToString_Implementation() override;

	UPROPERTY()
	UCanvasPanelSlot* Slot;

	ULuaState* GetLuaState();

private:
	static bool IsKnownProperty(const FString& Key);
};
