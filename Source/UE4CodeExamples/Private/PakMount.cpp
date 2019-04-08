// Fill out your copyright notice in the Description page of Project Settings.

#include "PakMount.h"

#include "HAL/PlatformFilemanager.h"
#include "IPlatformFilePak.h"
// Sets default values
APakMount::APakMount()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APakMount::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APakMount::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APakMount::MountPak()
{
    //第一步
    //FPlatformFileManager::Get()返回单例
    //GetPlatformFile()返回相应平台的PlatformFile，即处理相应平台文件读写的对象
    //因此在Windows平台，这里返回的是FWindowsPlatformFile的实例
	IPlatformFile& InnerPlatform = FPlatformFileManager::Get().GetPlatformFile();

    //第二步
    //这里创建了一个FPakPlatformFile，但是未指定当前使用什么平台去读写这个文件
	FPakPlatformFile* PakPlatformFile = new FPakPlatformFile();

    //第三步
    //使用相应平台的PlatformFile去初始化PakPlatformFile
    //第二个参数是命令行参数，一般都为空
	PakPlatformFile->Initialize(&InnerPlatform, TEXT(""));

    //第四步
    //再将当前PlatformFile设置为"相应平台下pak文件读写"的模式
	FPlatformFileManager::Get().SetPlatformFile(*PakPlatformFile);
	

    const FString pakFilename = TEXT("D:\\ExamplePak.pak");


    TSharedPtr<IFileHandle> PakHandle = MakeShareable(InnerPlatform.OpenRead(*pakFilename));
	if (!PakHandle.IsValid())
        return;

    //创建FPakFile对象,同样使用相应平台的PlatformFile初始化
    //第二个参数是pak文件名称
    //第三个参数是是否有符号？
    FPakFile* Pak = new FPakFile(&InnerPlatform,*pakFilename, false);

    //具体Mount方法可以参考函数 FPakPlatformFile::Mount
    //但是其中有大量多余内容(例如版本编号处理),可以调用其中最核心的部分SetMountPoint
    Pak->SetMountPoint(*FPaths::EngineContentDir());


    //bool bResult = PakPlatformFile->Mount(*FString(TEXT("D:\\ExamplePak.pak")), PakOrder, *FPaths::EngineContentDir());

	// if (bResult)
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 50.f, FColor::Red, FString::Printf(TEXT("EngineContentDir '%s'"), *FPaths::EngineContentDir()));

	// }
} 