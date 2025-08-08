// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Actions/Actions/AJBUtilityActionBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAJBUtilityActionBase() {}

// ********** Begin Cross Module References ********************************************************
AJBUTILITYAIPLUGIN_API UClass* Z_Construct_UClass_UAJBUtilityActionBase();
AJBUTILITYAIPLUGIN_API UClass* Z_Construct_UClass_UAJBUtilityActionBase_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_AJBUtilityAIPlugin();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UAJBUtilityActionBase ****************************************************
void UAJBUtilityActionBase::StaticRegisterNativesUAJBUtilityActionBase()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UAJBUtilityActionBase;
UClass* UAJBUtilityActionBase::GetPrivateStaticClass()
{
	using TClass = UAJBUtilityActionBase;
	if (!Z_Registration_Info_UClass_UAJBUtilityActionBase.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AJBUtilityActionBase"),
			Z_Registration_Info_UClass_UAJBUtilityActionBase.InnerSingleton,
			StaticRegisterNativesUAJBUtilityActionBase,
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
	return Z_Registration_Info_UClass_UAJBUtilityActionBase.InnerSingleton;
}
UClass* Z_Construct_UClass_UAJBUtilityActionBase_NoRegister()
{
	return UAJBUtilityActionBase::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UAJBUtilityActionBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Actions/Actions/AJBUtilityActionBase.h" },
		{ "ModuleRelativePath", "Public/Actions/Actions/AJBUtilityActionBase.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAJBUtilityActionBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UAJBUtilityActionBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_AJBUtilityAIPlugin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAJBUtilityActionBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAJBUtilityActionBase_Statics::ClassParams = {
	&UAJBUtilityActionBase::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAJBUtilityActionBase_Statics::Class_MetaDataParams), Z_Construct_UClass_UAJBUtilityActionBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAJBUtilityActionBase()
{
	if (!Z_Registration_Info_UClass_UAJBUtilityActionBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAJBUtilityActionBase.OuterSingleton, Z_Construct_UClass_UAJBUtilityActionBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAJBUtilityActionBase.OuterSingleton;
}
UAJBUtilityActionBase::UAJBUtilityActionBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAJBUtilityActionBase);
UAJBUtilityActionBase::~UAJBUtilityActionBase() {}
// ********** End Class UAJBUtilityActionBase ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Actions_Actions_AJBUtilityActionBase_h__Script_AJBUtilityAIPlugin_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAJBUtilityActionBase, UAJBUtilityActionBase::StaticClass, TEXT("UAJBUtilityActionBase"), &Z_Registration_Info_UClass_UAJBUtilityActionBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAJBUtilityActionBase), 1749284199U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Actions_Actions_AJBUtilityActionBase_h__Script_AJBUtilityAIPlugin_1935464903(TEXT("/Script/AJBUtilityAIPlugin"),
	Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Actions_Actions_AJBUtilityActionBase_h__Script_AJBUtilityAIPlugin_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Actions_Actions_AJBUtilityActionBase_h__Script_AJBUtilityAIPlugin_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
