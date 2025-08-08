// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Components/AJBUtilityComponent.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAJBUtilityComponent() {}

// ********** Begin Cross Module References ********************************************************
AIMODULE_API UClass* Z_Construct_UClass_UBrainComponent();
AJBUTILITYAIPLUGIN_API UClass* Z_Construct_UClass_UAJBUtilityComponent();
AJBUTILITYAIPLUGIN_API UClass* Z_Construct_UClass_UAJBUtilityComponent_NoRegister();
UPackage* Z_Construct_UPackage__Script_AJBUtilityAIPlugin();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UAJBUtilityComponent *****************************************************
void UAJBUtilityComponent::StaticRegisterNativesUAJBUtilityComponent()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_UAJBUtilityComponent;
UClass* UAJBUtilityComponent::GetPrivateStaticClass()
{
	using TClass = UAJBUtilityComponent;
	if (!Z_Registration_Info_UClass_UAJBUtilityComponent.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AJBUtilityComponent"),
			Z_Registration_Info_UClass_UAJBUtilityComponent.InnerSingleton,
			StaticRegisterNativesUAJBUtilityComponent,
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
	return Z_Registration_Info_UClass_UAJBUtilityComponent.InnerSingleton;
}
UClass* Z_Construct_UClass_UAJBUtilityComponent_NoRegister()
{
	return UAJBUtilityComponent::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UAJBUtilityComponent_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n * \n */" },
#endif
		{ "HideCategories", "Sockets Collision" },
		{ "IncludePath", "Components/AJBUtilityComponent.h" },
		{ "ModuleRelativePath", "Public/Components/AJBUtilityComponent.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAJBUtilityComponent>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UAJBUtilityComponent_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBrainComponent,
	(UObject* (*)())Z_Construct_UPackage__Script_AJBUtilityAIPlugin,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAJBUtilityComponent_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAJBUtilityComponent_Statics::ClassParams = {
	&UAJBUtilityComponent::StaticClass,
	"Engine",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x00B000A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAJBUtilityComponent_Statics::Class_MetaDataParams), Z_Construct_UClass_UAJBUtilityComponent_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAJBUtilityComponent()
{
	if (!Z_Registration_Info_UClass_UAJBUtilityComponent.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAJBUtilityComponent.OuterSingleton, Z_Construct_UClass_UAJBUtilityComponent_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAJBUtilityComponent.OuterSingleton;
}
UAJBUtilityComponent::UAJBUtilityComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAJBUtilityComponent);
UAJBUtilityComponent::~UAJBUtilityComponent() {}
// ********** End Class UAJBUtilityComponent *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Components_AJBUtilityComponent_h__Script_AJBUtilityAIPlugin_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAJBUtilityComponent, UAJBUtilityComponent::StaticClass, TEXT("UAJBUtilityComponent"), &Z_Registration_Info_UClass_UAJBUtilityComponent, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAJBUtilityComponent), 2261936245U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Components_AJBUtilityComponent_h__Script_AJBUtilityAIPlugin_4227822706(TEXT("/Script/AJBUtilityAIPlugin"),
	Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Components_AJBUtilityComponent_h__Script_AJBUtilityAIPlugin_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_marti_Documents_Portfolio_Utility_AI_GitPull_Utility_AI_UE5_Plugin_AxelaJimbobUtilityAI_Plugins_AJBUtilityAIPlugin_Source_AJBUtilityAIPlugin_Public_Components_AJBUtilityComponent_h__Script_AJBUtilityAIPlugin_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
