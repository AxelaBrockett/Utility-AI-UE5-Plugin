// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "DataAssets/AJBUtilityDataAsset.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAJBUtilityDataAsset() {}

// ********** Begin Cross Module References ********************************************************
AJBUTILITYAIPLUGIN_API UClass* Z_Construct_UClass_UAJBUtilityDataAsset();
AJBUTILITYAIPLUGIN_API UClass* Z_Construct_UClass_UAJBUtilityDataAsset_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UDataAsset();
UPackage* Z_Construct_UPackage__Script_AJBUtilityAIPlugin();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UAJBUtilityDataAsset *****************************************************
void UAJBUtilityDataAsset::StaticRegisterNativesUAJBUtilityDataAsset()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UAJBUtilityDataAsset;
UClass* UAJBUtilityDataAsset::GetPrivateStaticClass()
{
	using TClass = UAJBUtilityDataAsset;
	if (!Z_Registration_Info_UClass_UAJBUtilityDataAsset.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AJBUtilityDataAsset"),
			Z_Registration_Info_UClass_UAJBUtilityDataAsset.InnerSingleton,
			StaticRegisterNativesUAJBUtilityDataAsset,
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
	return Z_Registration_Info_UClass_UAJBUtilityDataAsset.InnerSingleton;
}
UClass* Z_Construct_UClass_UAJBUtilityDataAsset_NoRegister()
{
	return UAJBUtilityDataAsset::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UAJBUtilityDataAsset_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "DataAssets/AJBUtilityDataAsset.h" },
		{ "ModuleRelativePath", "Public/DataAssets/AJBUtilityDataAsset.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAJBUtilityDataAsset>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UAJBUtilityDataAsset_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UDataAsset,
	(UObject* (*)())Z_Construct_UPackage__Script_AJBUtilityAIPlugin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAJBUtilityDataAsset_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAJBUtilityDataAsset_Statics::ClassParams = {
	&UAJBUtilityDataAsset::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAJBUtilityDataAsset_Statics::Class_MetaDataParams), Z_Construct_UClass_UAJBUtilityDataAsset_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAJBUtilityDataAsset()
{
	if (!Z_Registration_Info_UClass_UAJBUtilityDataAsset.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAJBUtilityDataAsset.OuterSingleton, Z_Construct_UClass_UAJBUtilityDataAsset_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAJBUtilityDataAsset.OuterSingleton;
}
UAJBUtilityDataAsset::UAJBUtilityDataAsset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAJBUtilityDataAsset);
UAJBUtilityDataAsset::~UAJBUtilityDataAsset() {}
// ********** End Class UAJBUtilityDataAsset *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_DataAssets_AJBUtilityDataAsset_h__Script_AJBUtilityAIPlugin_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAJBUtilityDataAsset, UAJBUtilityDataAsset::StaticClass, TEXT("UAJBUtilityDataAsset"), &Z_Registration_Info_UClass_UAJBUtilityDataAsset, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAJBUtilityDataAsset), 2349893168U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_DataAssets_AJBUtilityDataAsset_h__Script_AJBUtilityAIPlugin_1581908006(TEXT("/Script/AJBUtilityAIPlugin"),
	Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_DataAssets_AJBUtilityDataAsset_h__Script_AJBUtilityAIPlugin_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_DataAssets_AJBUtilityDataAsset_h__Script_AJBUtilityAIPlugin_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
