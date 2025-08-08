// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Actions/Actions/AJBUtilityActionBlueprintBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAJBUtilityActionBlueprintBase() {}

// ********** Begin Cross Module References ********************************************************
AJBUTILITYAIPLUGIN_API UClass* Z_Construct_UClass_UAJBUtilityActionBase();
AJBUTILITYAIPLUGIN_API UClass* Z_Construct_UClass_UAJBUtilityActionBlueprintBase();
AJBUTILITYAIPLUGIN_API UClass* Z_Construct_UClass_UAJBUtilityActionBlueprintBase_NoRegister();
UPackage* Z_Construct_UPackage__Script_AJBUtilityAIPlugin();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UAJBUtilityActionBlueprintBase *******************************************
void UAJBUtilityActionBlueprintBase::StaticRegisterNativesUAJBUtilityActionBlueprintBase()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UAJBUtilityActionBlueprintBase;
UClass* UAJBUtilityActionBlueprintBase::GetPrivateStaticClass()
{
	using TClass = UAJBUtilityActionBlueprintBase;
	if (!Z_Registration_Info_UClass_UAJBUtilityActionBlueprintBase.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AJBUtilityActionBlueprintBase"),
			Z_Registration_Info_UClass_UAJBUtilityActionBlueprintBase.InnerSingleton,
			StaticRegisterNativesUAJBUtilityActionBlueprintBase,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UAJBUtilityActionBlueprintBase.InnerSingleton;
}
UClass* Z_Construct_UClass_UAJBUtilityActionBlueprintBase_NoRegister()
{
	return UAJBUtilityActionBlueprintBase::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UAJBUtilityActionBlueprintBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Actions/Actions/AJBUtilityActionBlueprintBase.h" },
		{ "ModuleRelativePath", "Public/Actions/Actions/AJBUtilityActionBlueprintBase.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAJBUtilityActionBlueprintBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UAJBUtilityActionBlueprintBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UAJBUtilityActionBase,
	(UObject* (*)())Z_Construct_UPackage__Script_AJBUtilityAIPlugin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAJBUtilityActionBlueprintBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAJBUtilityActionBlueprintBase_Statics::ClassParams = {
	&UAJBUtilityActionBlueprintBase::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAJBUtilityActionBlueprintBase_Statics::Class_MetaDataParams), Z_Construct_UClass_UAJBUtilityActionBlueprintBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAJBUtilityActionBlueprintBase()
{
	if (!Z_Registration_Info_UClass_UAJBUtilityActionBlueprintBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAJBUtilityActionBlueprintBase.OuterSingleton, Z_Construct_UClass_UAJBUtilityActionBlueprintBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAJBUtilityActionBlueprintBase.OuterSingleton;
}
UAJBUtilityActionBlueprintBase::UAJBUtilityActionBlueprintBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAJBUtilityActionBlueprintBase);
UAJBUtilityActionBlueprintBase::~UAJBUtilityActionBlueprintBase() {}
// ********** End Class UAJBUtilityActionBlueprintBase *********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Actions_Actions_AJBUtilityActionBlueprintBase_h__Script_AJBUtilityAIPlugin_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAJBUtilityActionBlueprintBase, UAJBUtilityActionBlueprintBase::StaticClass, TEXT("UAJBUtilityActionBlueprintBase"), &Z_Registration_Info_UClass_UAJBUtilityActionBlueprintBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAJBUtilityActionBlueprintBase), 740918916U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Actions_Actions_AJBUtilityActionBlueprintBase_h__Script_AJBUtilityAIPlugin_2313949674(TEXT("/Script/AJBUtilityAIPlugin"),
	Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Actions_Actions_AJBUtilityActionBlueprintBase_h__Script_AJBUtilityAIPlugin_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Actions_Actions_AJBUtilityActionBlueprintBase_h__Script_AJBUtilityAIPlugin_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
