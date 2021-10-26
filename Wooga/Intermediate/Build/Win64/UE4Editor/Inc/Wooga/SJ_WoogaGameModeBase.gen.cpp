// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Wooga/Public/SJ_WoogaGameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeSJ_WoogaGameModeBase() {}
// Cross Module References
	WOOGA_API UClass* Z_Construct_UClass_ASJ_WoogaGameModeBase_NoRegister();
	WOOGA_API UClass* Z_Construct_UClass_ASJ_WoogaGameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_Wooga();
	ENGINE_API UClass* Z_Construct_UClass_USoundBase_NoRegister();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	WOOGA_API UClass* Z_Construct_UClass_ASJ_HowToGrabUIActor_NoRegister();
	WOOGA_API UClass* Z_Construct_UClass_ASJ_HowToFireUIActor_NoRegister();
	WOOGA_API UClass* Z_Construct_UClass_ASJ_HowToFireNextUIActor_NoRegister();
	WOOGA_API UClass* Z_Construct_UClass_ASJ_Hologram_NoRegister();
	WOOGA_API UClass* Z_Construct_UClass_ASJ_GuidLine_NoRegister();
	ENGINE_API UClass* Z_Construct_UClass_UHapticFeedbackEffect_Base_NoRegister();
// End Cross Module References
	void ASJ_WoogaGameModeBase::StaticRegisterNativesASJ_WoogaGameModeBase()
	{
	}
	UClass* Z_Construct_UClass_ASJ_WoogaGameModeBase_NoRegister()
	{
		return ASJ_WoogaGameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_uiSound_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_uiSound;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_howToGrabActor_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_howToGrabActor;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_howToFireUIActor_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_howToFireUIActor;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_howToFireNextUIActor_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_howToFireNextUIActor;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_fireDisCoveryHologram_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_fireDisCoveryHologram;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_goToCollectGuideLine_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_goToCollectGuideLine;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_currentTime_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_currentTime;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_destroyTime_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_destroyTime;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_changeStateDelayTime_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_changeStateDelayTime;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_temporaryTime_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_temporaryTime;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_watchHaptic_MetaData[];
#endif
		static const UE4CodeGen_Private::FObjectPropertyParams NewProp_watchHaptic;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_Wooga,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "SJ_WoogaGameModeBase.h" },
		{ "ModuleRelativePath", "Public/SJ_WoogaGameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_uiSound_MetaData[] = {
		{ "Category", "Sound" },
		{ "Comment", "// UI Sound\n" },
		{ "ModuleRelativePath", "Public/SJ_WoogaGameModeBase.h" },
		{ "ToolTip", "UI Sound" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_uiSound = { "uiSound", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASJ_WoogaGameModeBase, uiSound), Z_Construct_UClass_USoundBase_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_uiSound_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_uiSound_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_howToGrabActor_MetaData[] = {
		{ "Category", "UI" },
		{ "ModuleRelativePath", "Public/SJ_WoogaGameModeBase.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_howToGrabActor = { "howToGrabActor", nullptr, (EPropertyFlags)0x0014000000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASJ_WoogaGameModeBase, howToGrabActor), Z_Construct_UClass_ASJ_HowToGrabUIActor_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_howToGrabActor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_howToGrabActor_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_howToFireUIActor_MetaData[] = {
		{ "Category", "UI" },
		{ "ModuleRelativePath", "Public/SJ_WoogaGameModeBase.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_howToFireUIActor = { "howToFireUIActor", nullptr, (EPropertyFlags)0x0014000000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASJ_WoogaGameModeBase, howToFireUIActor), Z_Construct_UClass_ASJ_HowToFireUIActor_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_howToFireUIActor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_howToFireUIActor_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_howToFireNextUIActor_MetaData[] = {
		{ "Category", "UI" },
		{ "ModuleRelativePath", "Public/SJ_WoogaGameModeBase.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_howToFireNextUIActor = { "howToFireNextUIActor", nullptr, (EPropertyFlags)0x0014000000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASJ_WoogaGameModeBase, howToFireNextUIActor), Z_Construct_UClass_ASJ_HowToFireNextUIActor_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_howToFireNextUIActor_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_howToFireNextUIActor_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_fireDisCoveryHologram_MetaData[] = {
		{ "Category", "Hologram" },
		{ "ModuleRelativePath", "Public/SJ_WoogaGameModeBase.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_fireDisCoveryHologram = { "fireDisCoveryHologram", nullptr, (EPropertyFlags)0x0014000000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASJ_WoogaGameModeBase, fireDisCoveryHologram), Z_Construct_UClass_ASJ_Hologram_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_fireDisCoveryHologram_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_fireDisCoveryHologram_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_goToCollectGuideLine_MetaData[] = {
		{ "Category", "GuideLine" },
		{ "Comment", "// ???? ???\xd2\xb7? ?\xcc\xb5??\xcf\xb1? ???? ???\xcc\xb5? ????\n" },
		{ "ModuleRelativePath", "Public/SJ_WoogaGameModeBase.h" },
		{ "ToolTip", "???? ???\xd2\xb7? ?\xcc\xb5??\xcf\xb1? ???? ???\xcc\xb5? ????" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_goToCollectGuideLine = { "goToCollectGuideLine", nullptr, (EPropertyFlags)0x0014000000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASJ_WoogaGameModeBase, goToCollectGuideLine), Z_Construct_UClass_ASJ_GuidLine_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_goToCollectGuideLine_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_goToCollectGuideLine_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_currentTime_MetaData[] = {
		{ "ModuleRelativePath", "Public/SJ_WoogaGameModeBase.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_currentTime = { "currentTime", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASJ_WoogaGameModeBase, currentTime), METADATA_PARAMS(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_currentTime_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_currentTime_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_destroyTime_MetaData[] = {
		{ "ModuleRelativePath", "Public/SJ_WoogaGameModeBase.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_destroyTime = { "destroyTime", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASJ_WoogaGameModeBase, destroyTime), METADATA_PARAMS(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_destroyTime_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_destroyTime_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_changeStateDelayTime_MetaData[] = {
		{ "ModuleRelativePath", "Public/SJ_WoogaGameModeBase.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_changeStateDelayTime = { "changeStateDelayTime", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASJ_WoogaGameModeBase, changeStateDelayTime), METADATA_PARAMS(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_changeStateDelayTime_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_changeStateDelayTime_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_temporaryTime_MetaData[] = {
		{ "ModuleRelativePath", "Public/SJ_WoogaGameModeBase.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_temporaryTime = { "temporaryTime", nullptr, (EPropertyFlags)0x0010000000000000, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASJ_WoogaGameModeBase, temporaryTime), METADATA_PARAMS(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_temporaryTime_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_temporaryTime_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_watchHaptic_MetaData[] = {
		{ "Category", "Haptic" },
		{ "ModuleRelativePath", "Public/SJ_WoogaGameModeBase.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_watchHaptic = { "watchHaptic", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(ASJ_WoogaGameModeBase, watchHaptic), Z_Construct_UClass_UHapticFeedbackEffect_Base_NoRegister, METADATA_PARAMS(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_watchHaptic_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_watchHaptic_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_uiSound,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_howToGrabActor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_howToFireUIActor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_howToFireNextUIActor,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_fireDisCoveryHologram,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_goToCollectGuideLine,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_currentTime,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_destroyTime,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_changeStateDelayTime,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_temporaryTime,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::NewProp_watchHaptic,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ASJ_WoogaGameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::ClassParams = {
		&ASJ_WoogaGameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::PropPointers),
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_ASJ_WoogaGameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_ASJ_WoogaGameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(ASJ_WoogaGameModeBase, 198928363);
	template<> WOOGA_API UClass* StaticClass<ASJ_WoogaGameModeBase>()
	{
		return ASJ_WoogaGameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_ASJ_WoogaGameModeBase(Z_Construct_UClass_ASJ_WoogaGameModeBase, &ASJ_WoogaGameModeBase::StaticClass, TEXT("/Script/Wooga"), TEXT("ASJ_WoogaGameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(ASJ_WoogaGameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
