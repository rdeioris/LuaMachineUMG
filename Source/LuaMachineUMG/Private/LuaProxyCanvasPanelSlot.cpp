// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaProxyCanvasPanelSlot.h"
#include "LuaDelegate.h"
#include "LuaState.h"
#include "Components/CanvasPanelSlot.h"

ULuaState* ULuaProxyCanvasPanelSlot::GetLuaState()
{
	return Cast<ULuaState>(GetOuter());
}

FLuaValue ULuaProxyCanvasPanelSlot::LuaMetaMethodToString_Implementation()
{
	return FString::Printf(TEXT("LuaProxySlot@%p"), this);
}

FLuaValue ULuaProxyCanvasPanelSlot::LuaMetaMethodIndex_Implementation(const FString& Key)
{
	if (IsKnownProperty(Key))
	{
		return GetLuaState()->GetLuaValueFromProperty(Slot, *Key);
	}

	return FLuaValue();
}

bool ULuaProxyCanvasPanelSlot::LuaMetaMethodNewIndex_Implementation(const FString& Key, FLuaValue Value)
{
	bool bSuccess = false;
	if (IsKnownProperty(Key))
	{
		bSuccess = GetLuaState()->SetPropertyFromLuaValue(Slot, *Key, Value);
	}

	if (bSuccess)
	{
		Slot->SynchronizeProperties();
	}

	return bSuccess;
}

bool ULuaProxyCanvasPanelSlot::IsKnownProperty(const FString& Key)
{
	static const TSet<FName> KnownProperties = {
		"Padding",
		"Size",
		"LayoutData",
		"bAutoSize",
	};

	return KnownProperties.Contains(FName(Key));
}
