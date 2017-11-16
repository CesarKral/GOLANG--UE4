// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorA.generated.h"

UCLASS()
class CPPHTTP_API AActorA : public AActor
{
	GENERATED_BODY()
	
public:	

	AActorA();

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "UE4 Http")
		void sendStr();
	UFUNCTION(BlueprintCallable, Category = "UE4 Http")
		void getStr();
	UFUNCTION(BlueprintCallable, Category = "UE4 Http")
		void sendJson();
	UFUNCTION(BlueprintCallable, Category = "UE4 Http")
		void getJson();
	
};
