// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Actions/Factors/AJBUtilityFactorBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAJBUtilityFactorBase() {}

// ********** Begin Cross Module References ********************************************************
AJBUTILITYAIPLUGIN_API UClass* Z_Construct_UClass_UAJBUtilityFactorBase();
AJBUTILITYAIPLUGIN_API UClass* Z_Construct_UClass_UAJBUtilityFactorBase_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_AJBUtilityAIPlugin();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UAJBUtilityFactorBase ****************************************************
void UAJBUtilityFactorBase::StaticRegisterNativesUAJBUtilityFactorBase()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UAJBUtilityFactorBase;
UClass* UAJBUtilityFactorBase::GetPrivateStaticClass()
{
	using TClass = UAJBUtilityFactorBase;
	if (!Z_Registration_Info_UClass_UAJBUtilityFactorBase.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AJBUtilityFactorBase"),
			Z_Registration_Info_UClass_UAJBUtilityFactorBase.InnerSingleton,
			StaticRegisterNativesUAJBUtilityFactorBase,
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
	return Z_Registration_Info_UClass_UAJBUtilityFactorBase.InnerSingleton;
}
UClass* Z_Construct_UClass_UAJBUtilityFactorBase_NoRegister()
{
	return UAJBUtilityFactorBase::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UAJBUtilityFactorBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Actions/Factors/AJBUtilityFactorBase.h" },
		{ "ModuleRelativePath", "Public/Actions/Factors/AJBUtilityFactorBase.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAJBUtilityFactorBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UAJBUtilityFactorBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_AJBUtilityAIPlugin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAJBUtilityFactorBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAJBUtilityFactorBase_Statics::ClassParams = {
	&UAJBUtilityFactorBase::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAJBUtilityFactorBase_Statics::Class_MetaDataParams), Z_Construct_UClass_UAJBUtilityFactorBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAJBUtilityFactorBase()
{
	if (!Z_Registration_Info_UClass_UAJBUtilityFactorBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAJBUtilityFactorBase.OuterSingleton, Z_Construct_UClass_UAJBUtilityFactorBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAJBUtilityFactorBase.OuterSingleton;
}
UAJBUtilityFactorBase::UAJBUtilityFactorBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAJBUtilityFactorBase);
UAJBUtilityFactorBase::~UAJBUtilityFactorBase() {}
// ********** End Class UAJBUtilityFactorBase ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Actions_Factors_AJBUtilityFactorBase_h__Script_AJBUtilityAIPlugin_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAJBUtilityFactorBase, UAJBUtilityFactorBase::StaticClass, TEXT("UAJBUtilityFactorBase"), &Z_Registration_Info_UClass_UAJBUtilityFactorBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAJBUtilityFactorBase), 23083507U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Actions_Factors_AJBUtilityFactorBase_h__Script_AJBUtilityAIPlugin_2444227446(TEXT("/Script/AJBUtilityAIPlugin"),
	Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Actions_Factors_AJBUtilityFactorBase_h__Script_AJBUtilityAIPlugin_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Actions_Factors_AJBUtilityFactorBase_h__Script_AJBUtilityAIPlugin_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
