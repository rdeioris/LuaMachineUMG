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
	if (Key == "Padding" || Key == "Size" || Key == "LayoutData" || Key == "bAutoSize")
	{
		return GetLuaState()->GetLuaValueFromProperty(Slot, *Key);
	}

	return FLuaValue();
}

bool ULuaProxyCanvasPanelSlot::LuaMetaMethodNewIndex_Implementation(const FString& Key, FLuaValue Value)
{
	bool bSuccess = false;
	if (Key == "Padding" || Key == "Size" || Key == "LayoutData" || Key == "bAutoSize")
	{
		bSuccess = GetLuaState()->SetPropertyFromLuaValue(Slot, *Key, Value);
	}

	if (bSuccess)
	{
		Slot->SynchronizeProperties();
	}

	return bSuccess;
}
