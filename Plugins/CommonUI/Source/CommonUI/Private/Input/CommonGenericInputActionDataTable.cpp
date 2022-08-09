// Copyright Epic Games, Inc. All Rights Reserved.

#include "Input/CommonGenericInputActionDataTable.h"
#include "CommonUITypes.h"
#include "UObject/UObjectHash.h"

UCommonGenericInputActionDataTable::UCommonGenericInputActionDataTable()
{
	RowStruct = FCommonInputActionDataBase::StaticStruct();
}

void UCommonGenericInputActionDataTable::PostLoad()
{
	Super::PostLoad();

	TArray<UClass*> ProcessorClasses;
	GetDerivedClasses(UCommonInputActionDataProcessor::StaticClass(), ProcessorClasses, false);

	for (UClass* ProcessorClass : ProcessorClasses)
	{
		if (UCommonInputActionDataProcessor* ProcessorCDO = Cast<UCommonInputActionDataProcessor>(ProcessorClass->GetDefaultObject()))
		{
			ProcessorCDO->ProcessInputActions(this);
		}
	}
}

void UCommonInputActionDataProcessor::ProcessInputActions(UCommonGenericInputActionDataTable* InputActionDataTable)
{
}
