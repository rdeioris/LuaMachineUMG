// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaProxySlot.h"
#include "Components/ContentWidget.h"
#include "LuaDelegate.h"
#include "LuaState.h"

ULuaState* ULuaProxySlot::GetLuaState()
{
	return Cast<ULuaState>(GetOuter());
}

FLuaValue ULuaProxySlot::LuaMetaMethodToString_Implementation()
{
	return FString::Printf(TEXT("LuaProxySlot@%p"), this);
}

FLuaValue ULuaProxySlot::LuaMetaMethodIndex_Implementation(const FString& Key)
{
	if (IsKnownProperty(Key))
	{
		return GetLuaState()->GetLuaValueFromProperty(Slot, *Key);
	}

	return FLuaValue();
}

bool ULuaProxySlot::LuaMetaMethodNewIndex_Implementation(const FString& Key, FLuaValue Value)
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

bool ULuaProxySlot::IsKnownProperty(const FString& Key)
{
	static const TSet<FName> KnownProperties = {
		"Padding",
		"Size",
		"LayoutData",
		"bAutoSize",
	};

	return KnownProperties.Contains(FName(Key));
}
