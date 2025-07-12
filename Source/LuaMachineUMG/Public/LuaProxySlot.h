// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LuaUserDataInterface.h"
#include "Components/PanelSlot.h"
#include "LuaProxySlot.generated.h"

UCLASS()
class LUAMACHINEUMG_API ULuaProxySlot : public UVisual, public ILuaUserDataInterface
{
	GENERATED_BODY()

public:
	FLuaValue LuaMetaMethodIndex_Implementation(const FString& Key) override;

	bool LuaMetaMethodNewIndex_Implementation(const FString& Key, FLuaValue Value) override;

	FLuaValue LuaMetaMethodToString_Implementation() override;

	UPROPERTY()
	UPanelSlot* Slot;

	ULuaState* GetLuaState();

private:
	bool IsKnownProperty(const FString& Key);
};
