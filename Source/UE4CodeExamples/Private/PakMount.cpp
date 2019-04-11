// Fill out your copyright notice in the Description page of Project Settings.

#include "PakMount.h"
#include "MyGameInstance.h"
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
    MyGI = Cast<UMyGameInstance>(GetGameInstance());
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


	const FString PakFileFullName = TEXT("D:\\ExamplePak.pak");

    //测试用MountPoint
    FString MountPoint(FPaths::EngineContentDir());


	//创建FPakFile对象,同样使用相应平台的PlatformFile初始化
	//第二个参数是pak文件的完整路径+名称
	//第三个参数是是否有符号？
	FPakFile* Pak = new FPakFile(&InnerPlatform, *PakFileFullName, false);


	if (Pak->IsValid())
	{

		//具体Mount方法可以参考函数 FPakPlatformFile::Mount
		//但是其中有大量多余内容(例如版本编号处理)
		//Pak->SetMountPoint(*MountPoint);

		PakPlatformFile->Mount(*PakFileFullName,1000,*MountPoint);


/*  可选项，绑定以后自动使用Visitor 遍历一次
        //声明一个继承自FDirectoryVisitor的类，用于遍历所有的内容
		class Dump : public IPlatformFile::FDirectoryVisitor
		{
            public:
			const FString mp_PakName;
			TArray<FString> Files;

			Dump(const FString& PakFileFullName ) :
				mp_PakName(PakFileFullName)
			{
			}
			virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)
			{
				UE_LOG(LogTemp, Log, TEXT("%s"), FilenameOrDirectory);
				return true;
			}
		};

		Dump* Visitor = new Dump(PakFileFullName);

        触发MountPak绑定的事件
		if (FCoreDelegates::OnMountPak.Execute(PakFileFullName, 0, Visitor))
		{
			
		}

*/

		TArray<FString> Files;
			Pak->FindFilesAtPath(Files, *(Pak->GetMountPoint()), true, false, true);

            for(auto File : Files)
            {
                FString Filename, FileExtn;
                int32 LastSlashIndex;
                File.FindLastChar(*TEXT("/"), LastSlashIndex);
                FString FileOnly = File.RightChop(LastSlashIndex + 1); //remove the full size since we want the slash gone too.
                FileOnly.Split(TEXT("."), &Filename, &FileExtn);

                if (FileExtn == TEXT("uasset"))
                {
                    File = FileOnly.Replace(TEXT("uasset"), *Filename);
					File = TEXT("/Engine/")+File;
                    ObjectPaths.AddUnique(FSoftObjectPath(File));
					ObjectPtrs.AddUnique(FSoftObjectPtr(ObjectPaths[ObjectPaths.Num()-1]));
                }
                
            }

            MyGI->GetStreamableManager().RequestAsyncLoad(ObjectPaths,FStreamableDelegate::CreateUObject(this,&APakMount::CreateAllChildren));
	}

}

void APakMount::CreateAllChildren()
{
    UE_LOG(LogTemp,Log,TEXT("finished loading assets"));
}