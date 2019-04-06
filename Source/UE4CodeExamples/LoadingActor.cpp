// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadingActor.h"
#include "Components/StaticMeshComponent.h"
#include "MyGameInstance.h"

// Sets default values
ALoadingActor::ALoadingActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    MyStaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
    RootComponent = MyStaticMeshComp;

    MyCube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TextureCube"));
    MyCube->SetupAttachment(MyStaticMeshComp);
	MyCube->SetRelativeLocation(FVector(100.0f,0,0));

	AutoReceiveInput = EAutoReceiveInput::Type::Player0;



}

// Called when the game starts or when spawned
void ALoadingActor::BeginPlay()
{
    Super::BeginPlay();

    MyGI = Cast<UMyGameInstance>(GetGameInstance());
}

// Called every frame
void ALoadingActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


void ALoadingActor::LoadSync()
{
    LoadMeshSync();
    LoadTextureSync();	
}

void ALoadingActor::LoadMeshSync()
{
    //加载Mesh
    FSoftObjectPath MyStaticMeshPath = MyMesh.ToSoftObjectPath();
    
    if(!MyStaticMeshPath.IsValid())
        return;

    MyGI->GetStreamableManager().RequestSyncLoad(MyStaticMeshPath);

    //获取加载后的资源方法1————直接使用MyMesh.Get()获取加载后的资源
    MyStaticMeshComp->SetStaticMesh(MyMesh.Get());
}

void ALoadingActor::LoadTextureSync()
{
    //加载Texture2D
    FSoftObjectPath MyTexturePath = MyTexture.ToSoftObjectPath();

	if (!MyTexturePath.IsValid())
		return;

    //获取加载后的资源方法2————借助FStreamableHandle来获取加载后的资源，可以看到方法较为麻烦
    TSharedPtr<FStreamableHandle> TextureLoadHandle = MyGI->GetStreamableManager().RequestSyncLoad(MyTexturePath);
    TArray<UObject*> LoadedAssets;
    TextureLoadHandle->GetLoadedAssets(LoadedAssets);
    if (TextureLoadHandle->HasLoadCompleted()) {
        UE_LOG(LogTemp, Warning, TEXT("LoadedAssets Number:%d"), LoadedAssets.Num());

        for (int32 i = 0; i < LoadedAssets.Num(); ++i) {
            UTexture2D* TempTexture = static_cast<UTexture2D*>(LoadedAssets[i]);
            if (TempTexture) {
                DynMat = UMaterialInstanceDynamic::Create(Mat,this,"NewMat");
                DynMat->SetTextureParameterValue("MainTexture",TempTexture);
                if(DynMat)
                {
                    MyCube->SetMaterial(0,DynMat);
                }
            }
        }
    }
}


void ALoadingActor::LoadASync()
{
    TArray<FSoftObjectPath> AssetsPaths;
    for(TSoftObjectPtr<UStaticMesh>& AssetPtr : MeshesToLoad)
    {
        AssetsPaths.AddUnique(AssetPtr.ToSoftObjectPath());
    }

    MyGI->GetStreamableManager().RequestAsyncLoad(AssetsPaths,FStreamableDelegate::CreateUObject(this,&ALoadingActor::LoadCallback));
}



void ALoadingActor::LoadCallback()
{
    for(int16 i = 0; i<MeshesToLoad.Num();++i)
    {
        UE_LOG(LogTemp,Warning,TEXT("Here"));
        UStaticMeshComponent* NewComp = NewObject<UStaticMeshComponent>(this);
        if(!NewComp) 
        {
            return;
        }
        NewComp->SetStaticMesh(MeshesToLoad[i].Get());
        NewComp->AttachToComponent(MyStaticMeshComp,FAttachmentTransformRules(EAttachmentRule::KeepRelative,true));
        NewComp->SetRelativeLocation(FVector(0,(i+1)*100.0f,0));
        NewComp->RegisterComponent();
    }    
}