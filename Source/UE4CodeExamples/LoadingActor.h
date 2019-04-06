// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LoadingActor.generated.h"

UCLASS()
class UE4CODEEXAMPLES_API ALoadingActor : public AActor
{
	GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ALoadingActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Loading)
    TSoftObjectPtr<UTexture2D> MyTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Loading)
    TSoftObjectPtr<UStaticMesh> MyMesh;

	UPROPERTY()
	class UStaticMeshComponent* MyStaticMeshComp;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MyCube;

    UPROPERTY(EditAnywhere,Category=Loading)
    UMaterialInterface* Mat;

    UPROPERTY(EditAnywhere,Category=Loading)
    TArray<TSoftObjectPtr<UStaticMesh>> MeshesToLoad;


    //同步加载
	UFUNCTION(BlueprintCallable,Category=Loading)
	void LoadSync();

    UFUNCTION(BlueprintCallable,Category=Loading)
	void LoadASync();

    UFUNCTION()
    void LoadCallback();



    class UMyGameInstance* MyGI;

private:
    UMaterialInstanceDynamic* DynMat;

    void LoadMeshSync();
    void LoadTextureSync();
};
