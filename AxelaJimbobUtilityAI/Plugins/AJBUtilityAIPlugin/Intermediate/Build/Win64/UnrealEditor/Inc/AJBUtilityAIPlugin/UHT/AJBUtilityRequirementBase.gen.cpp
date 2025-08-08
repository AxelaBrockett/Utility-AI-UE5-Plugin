// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Actions/Requirements/AJBUtilityRequirementBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAJBUtilityRequirementBase() {}

// ********** Begin Cross Module References ********************************************************
AJBUTILITYAIPLUGIN_API UClass* Z_Construct_UClass_UAJBUtilityRequirementBase();
AJBUTILITYAIPLUGIN_API UClass* Z_Construct_UClass_UAJBUtilityRequirementBase_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
UPackage* Z_Construct_UPackage__Script_AJBUtilityAIPlugin();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UAJBUtilityRequirementBase ***********************************************
void UAJBUtilityRequirementBase::StaticRegisterNativesUAJBUtilityRequirementBase()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UAJBUtilityRequirementBase;
UClass* UAJBUtilityRequirementBase::GetPrivateStaticClass()
{
	using TClass = UAJBUtilityRequirementBase;
	if (!Z_Registration_Info_UClass_UAJBUtilityRequirementBase.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AJBUtilityRequirementBase"),
			Z_Registration_Info_UClass_UAJBUtilityRequirementBase.InnerSingleton,
			StaticRegisterNativesUAJBUtilityRequirementBase,
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
	return Z_Registration_Info_UClass_UAJBUtilityRequirementBase.InnerSingleton;
}
UClass* Z_Construct_UClass_UAJBUtilityRequirementBase_NoRegister()
{
	return UAJBUtilityRequirementBase::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UAJBUtilityRequirementBase_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "IncludePath", "Actions/Requirements/AJBUtilityRequirementBase.h" },
		{ "ModuleRelativePath", "Public/Actions/Requirements/AJBUtilityRequirementBase.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAJBUtilityRequirementBase>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UAJBUtilityRequirementBase_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UObject,
	(UObject* (*)())Z_Construct_UPackage__Script_AJBUtilityAIPlugin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAJBUtilityRequirementBase_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAJBUtilityRequirementBase_Statics::ClassParams = {
	&UAJBUtilityRequirementBase::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAJBUtilityRequirementBase_Statics::Class_MetaDataParams), Z_Construct_UClass_UAJBUtilityRequirementBase_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAJBUtilityRequirementBase()
{
	if (!Z_Registration_Info_UClass_UAJBUtilityRequirementBase.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAJBUtilityRequirementBase.OuterSingleton, Z_Construct_UClass_UAJBUtilityRequirementBase_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAJBUtilityRequirementBase.OuterSingleton;
}
UAJBUtilityRequirementBase::UAJBUtilityRequirementBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAJBUtilityRequirementBase);
UAJBUtilityRequirementBase::~UAJBUtilityRequirementBase() {}
// ********** End Class UAJBUtilityRequirementBase *************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Actions_Requirements_AJBUtilityRequirementBase_h__Script_AJBUtilityAIPlugin_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAJBUtilityRequirementBase, UAJBUtilityRequirementBase::StaticClass, TEXT("UAJBUtilityRequirementBase"), &Z_Registration_Info_UClass_UAJBUtilityRequirementBase, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAJBUtilityRequirementBase), 48135242U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Actions_Requirements_AJBUtilityRequirementBase_h__Script_AJBUtilityAIPlugin_2676332928(TEXT("/Script/AJBUtilityAIPlugin"),
	Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Actions_Requirements_AJBUtilityRequirementBase_h__Script_AJBUtilityAIPlugin_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Actions_Requirements_AJBUtilityRequirementBase_h__Script_AJBUtilityAIPlugin_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
